#pragma once
#include <cstdint>
#include <vector>

struct ShipSurvivorComp {
  uint8_t id;
  std::vector<uint8_t> artifacts;
};