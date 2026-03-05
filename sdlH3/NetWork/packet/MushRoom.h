#pragma once
#include <cstdint>
#include <string>
#include <vector>

enum PACKET_TYPE {
  PACKET_HELLO_REQUEST,
  PACKET_HELLO_RESPONSE,
  PACKET_ENTER_REQUEST,
  PACKET_ENTER_RESPONSE,
};

struct ipClient {
  uint32_t ip;
  uint16_t port;
  uint64_t timestamp;
  uint64_t heartbeat;
};

#pragma pack(push, 1)
struct NetworkHelloRequest {
  uint32_t version; // 客户端版本号
};

struct NetworkHelloResponse {
  uint32_t heartbeat_interval; // 心跳间隔(秒)
};

struct NetworkEnterRequest {};

struct NetworkEnterResponse {
  uint32_t ip;
  uint16_t port;
};

struct NetworkPacket {
  uint16_t magic;     // 魔数
  uint64_t timestamp; // 时间戳
  uint16_t type;      // 包类型
  uint16_t data_len;
  uint8_t data[]; // 变长数据
};
#pragma pack(pop)
