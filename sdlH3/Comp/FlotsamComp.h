#pragma once

#include <cstdint>
#include <vector>
struct FlotsamComp {
  uint8_t id;
  std::vector<std::pair<uint8_t, uint64_t>> resources;
};