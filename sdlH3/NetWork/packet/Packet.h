#pragma once
#include <cstdint>

#pragma pack(push, 1)
struct NetworkPacket {
  uint16_t magic;     // 魔数
  uint32_t timestamp; // 时间戳
  uint16_t type;      // 包类型
  uint16_t data_len;
  uint8_t data[]; // 变长数据
};
#pragma pack(pop) // 立即恢复