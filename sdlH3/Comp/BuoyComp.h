#pragma once
#include <cstdint>
#include <unordered_set>
struct BuoyComp {
  std::unordered_set<uint8_t> visitHeros;
};