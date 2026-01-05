#pragma once

#include <cstdint>
#include <vector>
struct DragonUtComp {
  uint8_t id;
  std::vector<std::pair<uint16_t, uint32_t>> guards;
  std::vector<uint8_t> artifacts;
};