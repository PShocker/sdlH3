#pragma once
#include "Enum/Enum.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct GenericSound {
  std::string ambient;
  std::string visit;
};

struct GenericData {
  uint8_t index;
  GenericSound sound;
  std::vector<std::pair<uint16_t, uint32_t>> guards; // <creatureType, amount>
  std::vector<uint16_t> creatures; // 生物类型ID列表，支持多级兵种
};