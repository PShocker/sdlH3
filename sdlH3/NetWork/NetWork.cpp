#include "NetWork/NetWork.h"
#include "./protocol/Client.h"
#include "./protocol/Protocol.h"
#include "./protocol/Server.h"
#include "Global/Global.h"
#include "NetWork.h"
#include "NetWork/NetClient.h"
#include "NetWork/NetServer.h"
#include "NetWork/protocol/Protocol.h"
#include "flatbuffers/flatbuffer_builder.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ranges>
#include <string>
#include <uv.h>

static uv_udp_t server_socket = {};
static uint32_t server_port = 0;
static uv_loop_t *loop = nullptr;
static uv_timer_t send_heartbeat_timer;
static uv_timer_t fresh_heartbeat_timer;

// 将uint32 IP和uint16端口组合为uint64
static uint64_t CombineIPAndPort(uint32_t ip, uint16_t port) {
  // 将ip放入高32位，port放入低32位
  return ((uint64_t)ip << 32) | port;
}

// 分解uint64为IP和端口
static void SplitIPAndPort(uint64_t combined, uint32_t &ip, uint16_t &port) {
  ip = (uint32_t)(combined >> 32);      // 取高32位
  port = (uint16_t)(combined & 0xFFFF); // 取低16位（注意是16位，不是32位）
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

  auto addr_in = (const struct sockaddr_in *)addr;
  auto ip = (uint32_t)(addr_in->sin_addr.s_addr);
  auto port = ntohs(addr_in->sin_port);
  auto cId = CombineIPAndPort(ip, port);

  NetServer::handlePacket(cId, buf->base, nread);

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

bool NetWork::sendUDP(const uint8_t *data, size_t len, uint64_t cId) {
  uint32_t ip;
  uint16_t port;
  SplitIPAndPort(cId, ip, port);
  return sendUDP(data, len, ip, port);
}

bool NetWork::sendUDP(const uint8_t *data, size_t len, uint32_t ip,
                      uint16_t port) {
  auto buffer = (uint8_t *)malloc(len);
  memcpy(buffer, data, len);
  uv_udp_send_t *send_req = (uv_udp_send_t *)malloc(sizeof(uv_udp_send_t));
  send_req->data = buffer;

  sockaddr_in send_addr;
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = htons(port);
  send_addr.sin_addr.s_addr = ip;

  uv_buf_t buf = uv_buf_init((char *)buffer, len);

  // 使用在 main 中初始化好的目标地址 send_addr
  auto r = uv_udp_send(
      send_req, &server_socket, &buf, 1, (const sockaddr *)&send_addr,
      [](uv_udp_send_t *req, int status) {
        if (status < 0) {
          fprintf(stderr, "Send error: %s\n", uv_strerror(status));
        }
        free(req->data);
        free(req); // 释放发送请求
      });
  if (r < 0) {
    fprintf(stderr, "uv_udp_send error: %s\n", uv_strerror(r));
    free(send_req);
    return false;
  }
  return true;
}

bool NetWork::sendUDP(const uint8_t *data, size_t len, std::string ip,
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
  if (host_port == 0) {
    host_port = server_port;
  }
  // 4. 开始接收数据
  r = uv_udp_recv_start(&server_socket, alloc_cb, on_recv);
  if (r < 0) {
    fprintf(stderr, "Recv start error: %s\n", uv_err_name(r));
    std::abort();
  }
  uint32_t heartbeat_interval = 5000;

  printf("Started receiving on port %d...\n", server_port);
}

void NetWork::init(std::string host_ip, uint32_t host_port) {
  NetWork::host_ip = host_ip;
  NetWork::host_port = host_port;
  NetWork::init();
}

void NetWork::run() {
  NetClient::sendHeartBeat();
  NetServer::checkHeartBeat();
  // 6. 运行事件循环
  uv_run(loop, UV_RUN_NOWAIT);
}