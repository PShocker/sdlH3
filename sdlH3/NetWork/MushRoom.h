#pragma once
#include <cstdint>
#include <string>
#include <vector>

enum MUSHROOM_PACKET_TYPE {
  PACKET_HELLO_REQUEST,
  PACKET_HELLO_RESPONSE,
  PACKET_HEARTBEAT_REQUEST,
  PACKET_HEARTBEAT_RESPONSE,
  PACKET_BYE_REQUEST,
  PACKET_BYE_RESPONSE,
  PACKET_REGISTER_REQUEST,
  PACKET_REGISTER_RESPONSE,
  PACKET_UNREGISTER_REQUEST,
  PACKET_UNREGISTER_RESPONSE,
  PACKET_HOST_REQUEST,
  PACKET_HOST_RESPONSE,
  PACKET_UNHOST_REQUEST,
  PACKET_UNHOST_RESPONSE,
};

enum MUSHROOM_CAST_TYPE {
  CAST_UNICAST,
  CAST_BROADCAST,
};

struct NetworkHelloRequest {
  uint32_t version; // 客户端版本号
};

struct NetworkHelloResponse {
  uint32_t heartbeat_interval; // 心跳间隔(秒)
};

struct NetworkPacket {
  uint16_t magic;     // 魔数
  uint64_t timestamp; // 时间戳

  uint32_t cast_ip;   // IPv4地址
  uint16_t cast_port; // 端口号
  uint8_t cast_type;  // 组播类型

  uint16_t type;     // 包类型
  uint32_t sub_type; // 包类型2
  uint16_t data_len;
  uint8_t data[]; // 变长数据
};