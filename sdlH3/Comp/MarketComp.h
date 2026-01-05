#pragma once
#include <cstdint>
#include <vector>
struct MarketComp {
  uint8_t type;                    // 0:Res 1:Art
  std::vector<uint16_t> artifacts; // ART_BUY
};