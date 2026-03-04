#include "NetWork/NetWork.h"
#include "NetWork/packet/Packet.h"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <uv.h>

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
  const NetworkPacket *packet =
      reinterpret_cast<const NetworkPacket *>(buf->base);

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

static uv_udp_t server_socket = {};
static uint32_t server_port = 0;
static uv_loop_t *loop = nullptr;

bool NetWork::send(const uint8_t *data, size_t length, std::string pos_addr_str,
                   uint32_t pos_port) {
  // 3. 准备目标地址（用于发送）
  uv_udp_send_t *send_req = (uv_udp_send_t *)malloc(sizeof(uv_udp_send_t));
  sockaddr_in send_addr = {};
  uv_ip4_addr(pos_addr_str.c_str(), pos_port, &send_addr);
  uv_buf_t buf = uv_buf_init((char *)data, length);

  // 使用在 main 中初始化好的目标地址 send_addr
  auto r = uv_udp_send(
      send_req, &server_socket, &buf, 1, (const struct sockaddr *)&send_addr,
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

void NetWork::init(std::string src_addr_str, uint32_t src_port) {
  server_port = src_port;
  loop = uv_default_loop();
  // 1. 创建UDP句柄
  uv_udp_init(loop, &server_socket);

  // 绑定到 IPv4 和 IPv6
  struct sockaddr_in recv_addr;
  uv_ip4_addr(src_addr_str.c_str(), server_port, &recv_addr);
  auto r = uv_udp_bind(&server_socket, (const struct sockaddr *)&recv_addr,
                       UV_UDP_REUSEADDR);
  if (r < 0) {
    std::abort();
  }
  // 4. 开始接收数据
  r = uv_udp_recv_start(&server_socket, alloc_cb, on_recv);
  if (r < 0) {
    fprintf(stderr, "Recv start error: %s\n", uv_err_name(r));
    std::abort();
  }
  printf("Started receiving on port %d...\n", server_port);

  // 5. 模拟发送消息：给自己发一条消息
  // 注意：实际应用中，你可能在收到某个事件或消息时调用 send_message
  NetworkPacket pack;
  pack.magic = (1234);
  pack.timestamp = (9872);
  pack.type = (1);
  std::string msg = "nihaoShocker!";
  memcpy(pack.data, msg.c_str(), msg.size());
  send(reinterpret_cast<const uint8_t *>(&pack), sizeof(pack), "127.0.0.1",
       8888);
  // 6. 运行事件循环
  uv_run(loop, UV_RUN_DEFAULT);
}