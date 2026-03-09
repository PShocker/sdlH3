#include "NetWork/NetWork.h"
#include "NetWork/MushRoom.h"
#include "Sys/NetWorkSys.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <ranges>
#include <string>
#include <uv.h>

static uv_udp_t server_socket = {};
static uint32_t server_port = 0;
static uv_loop_t *loop = nullptr;
static uv_timer_t say_heartbeat_timer;
static uv_timer_t fresh_client_timer;

const static std::string mushroom_ip = "127.0.0.1";
const static uint32_t mushroom_port = 8888;

static bool sayHello() {
  NetworkHelloRequest r = {.version = 1};
  auto *packet = (NetworkPacket *)malloc(sizeof(NetworkPacket) + sizeof(r));
  packet->magic = 0x1234;
  packet->timestamp = static_cast<uint64_t>(time(nullptr));
  packet->type = PACKET_HELLO_REQUEST;
  packet->data_len = sizeof(r);
  memcpy(packet->data, &r, packet->data_len);
  NetWork::sendUDP((uint8_t *)(packet), sizeof(*packet) + packet->data_len,
                   mushroom_ip, mushroom_port);
  free(packet);
  return true;
}

static bool sayEnter() {
  auto *packet = (NetworkPacket *)malloc(sizeof(NetworkPacket));
  packet->magic = 0x1234;
  packet->timestamp = static_cast<uint64_t>(time(nullptr));
  packet->type = PACKET_ENTER_REQUEST;
  packet->data_len = 0;
  NetWork::sendUDP((uint8_t *)(packet), sizeof(*packet), mushroom_ip,
                   mushroom_port);
  free(packet);
  return true;
}

static void sayHeartBeat(uv_timer_t *handle) {
  auto *packet = (NetworkPacket *)malloc(sizeof(NetworkPacket));
  packet->magic = 0x1234;
  packet->timestamp = static_cast<uint64_t>(time(nullptr));
  packet->type = PACKET_HEARTBEAT_REQUEST;
  packet->data_len = 0;

  NetWork::sendUDP((uint8_t *)(packet), sizeof(*packet), mushroom_ip,
                   mushroom_port);
  //  除此之外，外需要广播给所有的在线用户
  for (const auto &[ip, port] : NetWork::clients | std::views::keys) {
    NetWork::sendUDP((uint8_t *)(packet), sizeof(*packet), ip, port);
  }
  free(packet);

  return;
}

static void sayHost(uint32_t ip, uint16_t port) {
  NetworkHostRequest r = {.scene = NetWork::scene};
  auto *packet = (NetworkPacket *)malloc(sizeof(NetworkPacket) + sizeof(r));
  packet->magic = 0x1234;
  packet->timestamp = static_cast<uint64_t>(time(nullptr));
  packet->type = NETWORK_EVENT_HOST;
  packet->data_len = sizeof(r);
  memcpy(packet->data, &r, packet->data_len);

  NetWork::sendUDP((uint8_t *)(packet), sizeof(&packet) + packet->data_len, ip,
                   port);
  free(packet);
  return;
}

static void freshClient(uv_timer_t *handle) {
  uint64_t now = static_cast<uint64_t>(time(nullptr));
  std::erase_if(NetWork::clients, [=](const auto &item) {
    const auto &[key, client] = item;
    // 检查是否超时
    auto duration = now - client.heartbeat;
    return duration >= NetWork::heartbeat_interval * 10;
  });
}

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

  auto packet = (const NetworkPacket *)(buf->base);

  auto addr_in = (const struct sockaddr_in *)addr;
  ipClient client = {
      .ip = (uint32_t)(addr_in->sin_addr.s_addr),
      .port = ntohs(addr_in->sin_port),
      .timestamp = packet->timestamp,
      .heartbeat = packet->timestamp,
  };

  // dispatch
  switch (packet->type) {
  case PACKET_HELLO_RESPONSE: {
    auto r = (const NetworkHelloResponse *)packet->data;
    NetWork::heartbeat_interval = r->heartbeat_interval;
    sayEnter();
    // 创建定时器
    auto interval = NetWork::heartbeat_interval * 1000;
    uv_timer_init(loop, &say_heartbeat_timer);
    uv_timer_start(&say_heartbeat_timer, sayHeartBeat, 0, interval);
    // 创建定时器
    uv_timer_init(loop, &fresh_client_timer);
    uv_timer_start(&fresh_client_timer, freshClient, 0, interval);
    break;
  }
  case PACKET_ENTER_RESPONSE: {
    auto r = (const NetworkEnterResponse *)packet->data;
    auto key = std::make_pair(r->ip, r->port);
    ipClient ct = {
        .ip = r->ip,
        .port = r->port,
        .heartbeat = static_cast<uint64_t>(time(nullptr)),
    };
    std::unique_lock lock(NetWork::clients_mutex);
    NetWork::clients.insert({key, ct});
    break;
  }
  case PACKET_HEARTBEAT_REQUEST: {
    auto key = std::make_pair(client.ip, client.port);
    std::unique_lock lock(NetWork::clients_mutex);
    NetWork::clients[key].heartbeat = static_cast<uint64_t>(time(nullptr));
    break;
  }
  case PACKET_JOIN_REQUEST: {
    auto r = (const NetworkJoinRequest *)packet->data;
    ipClient ct = {
        .ip = r->ip,
        .port = r->port,
        .heartbeat = static_cast<uint64_t>(time(nullptr)),
    };
    auto key = std::make_pair(client.ip, client.port);
    std::unique_lock lock(NetWork::clients_mutex);
    NetWork::clients.insert({key, client});
    sayHost(r->ip, r->port);
    break;
  }
  // mushroom pack end
  case NETWORK_EVENT_HOST: {
    auto r = (const NetworkHostRequest *)packet->data;
    std::unique_lock lock(NetWork::hosts_mutex);
    NetWork::hosts[r->scene] = {client.ip, client.port};
    break;
  }
  case NETWORK_EVENT_HOST_EXIT: {
    auto r = (const NetworkHostExitRequest *)packet->data;
    std::unique_lock lock(NetWork::hosts_mutex);
    NetWork::hosts.erase(r->scene);
    break;
  }
  default: {
    break;
  }
  }

  char sender_ip[17] = {0};
  int sender_port = 0;
  if (addr) {
    uv_ip4_name((const struct sockaddr_in *)addr, sender_ip, 16);
    sender_port = ntohs(((const struct sockaddr_in *)addr)->sin_port);
  }
  printf("Received %ld bytes from %s:%d\n", nread, sender_ip, sender_port);

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

static void on_async_send(uv_async_t *handle) {
  std::unique_lock lock(NetWork::send_mutex); // 独占锁，写时互斥
  for (auto r : NetWork::sendVector) {
    auto ip = r.first.first;
    auto port = r.first.second;
    auto packet = r.second;
    auto data_len = packet->data_len;
    if (ip == 0 && port == 0) {
      // 广播
      std::shared_lock lock(NetWork::clients_mutex); // 读锁
      for (const auto &[ip, port] : NetWork::clients | std::views::keys) {
        NetWork::sendUDP((uint8_t *)(packet), sizeof(NetworkPacket) + data_len,
                         ip, port);
      }
    } else {
      NetWork::sendUDP((uint8_t *)(packet), sizeof(NetworkPacket) + data_len,
                       ip, port);
    }
    free(packet);
  }
  NetWork::sendVector.clear();
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

  uv_async_init(loop, &async_handle, on_async_send);
  // 6. 运行事件循环
  uv_run(loop, UV_RUN_DEFAULT);
}