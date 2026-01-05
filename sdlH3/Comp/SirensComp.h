#pragma once
#include <cstdint>
#include <unordered_set>
struct SirensComp {
  std::unordered_set<uint8_t> visitHeros;
};