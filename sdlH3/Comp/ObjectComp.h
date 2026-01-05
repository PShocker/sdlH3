#pragma once

#include <cstdint>
#include <utility>
#include <vector>
struct ObjectComp {
  int16_t type;
  uint8_t x;
  uint8_t y;

  std::vector<std::pair<int16_t, int16_t>> blockTiles;
  std::vector<std::pair<int16_t, int16_t>> accessTiles;
};