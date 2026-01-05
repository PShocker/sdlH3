#pragma once
#include <cstdint>
#include <unordered_set>
struct RalFlagComp {
  std::unordered_set<uint8_t> visitHeros;
};