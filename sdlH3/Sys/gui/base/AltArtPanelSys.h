#pragma once

#include <cstdint>
#include <utility>
struct AltArtPanelSys {
  static void draw(int32_t x, int32_t y);
  static std::pair<uint8_t, uint16_t> click(int32_t x, int32_t y);
};