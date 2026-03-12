#include "NetWork/NetWork.h"
#include "./protocol/Protocol_generated.h"
#include "flatbuffers/flatbuffer_builder.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <ranges>
#include <string>
#include <uv.h>

static uv_udp_t server_socket = {};
static uint32_t server_port = 0;
static uv_loop_t *loop = nullptr;
static uv_timer_t send_heartbeat_timer;
static uv_timer_t fresh_heartbeat_timer;

const static std::string host_ip = "127.0.0.1";
const static uint32_t host_port = 8888;

static void sendHeartBeat(uv_timer_t *handle) {
  // 1. 创建FlatBufferBuilder
  flatbuffers::FlatBufferBuilder builder;
  // 2. 获取当前时间戳（毫秒）
  uint64_t now = static_cast<uint64_t>(time(nullptr));
  // 3. 创建Heartbeat表
  auto heartbeat = CreateNetHeartbeat(builder, now);
  // 4. 创建网络包（最外层包装）
  auto packet = CreateNetPacket(builder,
                                NetPacketPayload_NetHeartbeat, // payload类型
                                heartbeat.Union() // 具体的payload数据
  );
  // 5. 完成构建（root_type是NetPacket）
  builder.Finish(packet);

  // 6. 获取构建好的数据
  const uint8_t *buffer = builder.GetBufferPointer();
  size_t size = builder.GetSize();
  NetWork::sendUDP(buffer, size, host_ip, host_port);
  return;
}

static void freshHeartBeat(uv_timer_t *handle) {
  // uint64_t now = static_cast<uint64_t>(time(nullptr));
  // std::erase_if(NetWork::clients, [=](const auto &item) {
  //   const auto &[key, client] = item;
  //   // 检查是否超时
  //   auto duration = now - client.heartbeat;
  //   return duration >= NetWork::heartbeat_interval * 10;
  // });
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
  auto packet = GetNetPacket(buf->base);
  if (!packet) {
    printf("无效的数据包\n");
    return;
  }
  // 4. 通过union的type判断具体类型
  switch (packet->payload_type()) {
  case NetPacketPayload_NetHeartbeat: {
    // 从union中获取NetHeartbeat
    auto heartbeat = packet->payload_as_NetHeartbeat();
    heartbeat->client_time();
    break;
  }
  default:
    break;
  }

  // auto addr_in = (const struct sockaddr_in *)addr;
  // ipClient client = {
  //     .ip = (uint32_t)(addr_in->sin_addr.s_addr),
  //     .port = ntohs(addr_in->sin_port),
  //     .timestamp = packet->timestamp,
  //     .heartbeat = packet->timestamp,
  // };

  // dispatch

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

bool NetWork::sendUDP(const uint8_t *data, size_t len, uint32_t ip,
                      uint16_t port) {
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
  // 4. 开始接收数据
  r = uv_udp_recv_start(&server_socket, alloc_cb, on_recv);
  if (r < 0) {
    fprintf(stderr, "Recv start error: %s\n", uv_err_name(r));
    std::abort();
  }
  uint32_t heartbeat_interval = 5000;

  printf("Started receiving on port %d...\n", server_port);
  uv_timer_init(loop, &send_heartbeat_timer);
  uv_timer_start(&send_heartbeat_timer, sendHeartBeat, 0, heartbeat_interval);
  // 创建定时器
  uv_timer_init(loop, &fresh_heartbeat_timer);
  uv_timer_start(&fresh_heartbeat_timer, freshHeartBeat, 0, heartbeat_interval);
  // 6. 运行事件循环
  uv_run(loop, UV_RUN_NOWAIT);
}