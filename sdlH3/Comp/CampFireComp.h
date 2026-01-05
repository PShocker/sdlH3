#pragma once

#include <cstdint>
#include <vector>
struct CampFireComp {
  uint8_t id;
  std::vector<std::pair<uint8_t, uint64_t>> resources;
};