#pragma once
#include <cstdint>
#include <vector>

struct ShipWreckComp {
  uint8_t id;
  std::vector<std::pair<uint16_t, uint32_t>> guards;
  std::vector<std::pair<uint8_t, uint8_t>> resources;
  std::vector<uint8_t> artifacts;
};