#pragma once

#include <cstdint>
#include <utility>
#include <vector>
struct WaterWheelComp {
  std::vector<std::pair<uint8_t, uint64_t>> resources;
};