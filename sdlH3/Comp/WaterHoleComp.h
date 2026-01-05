#pragma once
#include <cstdint>
#include <unordered_set>
struct WaterHoleComp {
  std::unordered_set<uint8_t> visitHeros;
};