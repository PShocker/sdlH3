#pragma once
#include <cstdint>
#include <unordered_set>
struct KnoTreeComp {
  std::unordered_set<uint8_t> visitHeros;
  std::vector<std::pair<uint8_t, uint8_t>> resources;
};