#pragma once
#include <cstdint>
#include <vector>

struct SeaChestComp {
  uint8_t id;
  std::vector<std::pair<uint16_t, uint32_t>> guards;
  std::vector<std::pair<uint8_t, uint64_t>> resources;
  std::vector<uint8_t> artifacts;
};