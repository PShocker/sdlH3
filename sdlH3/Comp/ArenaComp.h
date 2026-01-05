#pragma once
#include <cstdint>
#include <unordered_set>
struct ArenaComp {
  std::unordered_set<uint8_t> visitHeros;
};