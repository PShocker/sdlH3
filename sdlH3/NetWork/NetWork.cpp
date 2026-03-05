#include "NetWork/NetWork.h"
#include "NetWork/packet/MushRoom.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <ranges>
#include <string>
#include <uv.h>

static uv_udp_t server_socket = {};
static uint32_t server_port = 0;
static uv_loop_t *loop = nullptr;

static std::vector<ipClient> clients;
static uint32_t heartbeat_interval = 0;

const static std::string mushroom_ip = "127.0.0.1";
const static uint32_t mushroom_port = 8888;

static bool sayHello() {
  NetworkHelloRequest r = {.version = 1};
  NetworkPacket pack = {
      .magic = 0x1234,
      .timestamp = static_cast<uint64_t>(time(nullptr)),
      .type = PACKET_HELLO_REQUEST,
      .data_len = sizeof(r),
  };
  memcpy(pack.data, &r, pack.data_len);
  NetWork::sendUDP((uint8_t *)(&pack), sizeof(pack) + pack.data_len,
                   mushroom_ip, mushroom_port);
  return true;
}

static bool sayEnter() {
  NetworkPacket pack = {
      .magic = 0x1234,
      .timestamp = static_cast<uint64_t>(time(nullptr)),
      .type = PACKET_ENTER_REQUEST,
      .data_len = 0,
  };
  NetWork::sendUDP((uint8_t *)(&pack), sizeof(pack) + pack.data_len,
                   mushroom_ip, mushroom_port);
  return true;
}

static bool sayHi() {}

// 接收回调：当收到数据时被调用
static void on_recv(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf,
                    const struct sockaddr *addr, unsigned flags) {
  if (nread < 0) {
    fprintf(stderr, "Read error: %s\n", uv_err_name(nread));
    uv_close((uv_handle_t *)handle, NULL);
    free(buf->base);
    return;
  }

  if (nread == 0) {
    // 没有数据或收到空包
    free(buf->base);
    return;
  }

  char sender_ip[17] = {0};
  int sender_port = 0;
  if (addr) {
    uv_ip4_name((const struct sockaddr_in *)addr, sender_ip, 16);
    sender_port = ntohs(((const struct sockaddr_in *)addr)->sin_port);
  }
  auto packet = (const NetworkPacket *)(buf->base);
  // dispatch
  switch (packet->type) {
  case PACKET_HELLO_RESPONSE: {
    auto r = (const NetworkHelloResponse *)packet->data;
    heartbeat_interval = r->heartbeat_interval;
    sayEnter();
    break;
  }
  case PACKET_ENTER_RESPONSE: {
    auto r = (const NetworkEnterResponse *)packet->data;
    ipClient client = {
        .ip = r->ip,
        .port = r->port,
    };
    clients.push_back(client);
    break;
  }
  default: {
    break;
  }
  }
  printf("Received %ld bytes from %s:%d: %.*s\n", nread, sender_ip, sender_port,
         (int)nread, buf->base);

  free(buf->base); // 释放由 alloc_cb 分配的内存
}

// 分配缓冲区回调
static void alloc_cb(uv_handle_t *handle, size_t suggested_size,
                     uv_buf_t *buf) {
  buf->base = (char *)malloc(suggested_size);
  buf->len = suggested_size;
}

bool NetWork::sendUDP(uint8_t *data, size_t len, uint32_t ip, uint16_t port) {
  uv_udp_send_t *send_req = (uv_udp_send_t *)malloc(sizeof(uv_udp_send_t));
  sockaddr_in send_addr;
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = htons(port);
  send_addr.sin_addr.s_addr = ip;

  uv_buf_t buf = uv_buf_init((char *)data, len);

  // 使用在 main 中初始化好的目标地址 send_addr
  auto r = uv_udp_send(
      send_req, &server_socket, &buf, 1, (const sockaddr *)&send_addr,
      [](uv_udp_send_t *req, int status) {
        if (status < 0) {
          fprintf(stderr, "Send error: %s\n", uv_strerror(status));
        }
        free(req); // 释放发送请求
      });
  if (r < 0) {
    fprintf(stderr, "uv_udp_send error: %s\n", uv_strerror(r));
    free(send_req);
    return false;
  }
  return true;
}

bool NetWork::sendUDP(uint8_t *data, size_t len, std::string ip,
                      uint16_t port) {
  sockaddr_in send_addr = {};
  uv_ip4_addr(ip.c_str(), port, &send_addr);
  return sendUDP(data, len, (uint32_t)(send_addr.sin_addr.s_addr), port);
}

void NetWork::init() {
  loop = uv_default_loop();
  // 1. 创建UDP句柄
  uv_udp_init(loop, &server_socket);

  // 绑定到 IPv4 和 IPv6
  struct sockaddr_in recv_addr;
  uv_ip4_addr("0.0.0.0", 0, &recv_addr);
  auto r = uv_udp_bind(&server_socket, (const struct sockaddr *)&recv_addr,
                       UV_UDP_REUSEADDR);
  if (r < 0) {
    std::abort();
  }
  // 4. 获取系统实际分配的端口号
  struct sockaddr_in assigned_addr;
  int namelen = sizeof(assigned_addr);
  r = uv_udp_getsockname(&server_socket, (struct sockaddr *)&assigned_addr,
                         &namelen);
  if (r) {
    fprintf(stderr, "Getsockname error: %s\n", uv_strerror(r));
    std::abort();
  }
  server_port = ntohs(assigned_addr.sin_port);
  // 4. 开始接收数据
  r = uv_udp_recv_start(&server_socket, alloc_cb, on_recv);
  if (r < 0) {
    fprintf(stderr, "Recv start error: %s\n", uv_err_name(r));
    std::abort();
  }
  printf("Started receiving on port %d...\n", server_port);

  // SAY HELLO
  sayHello();

  // 6. 运行事件循环
  uv_run(loop, UV_RUN_DEFAULT);
}