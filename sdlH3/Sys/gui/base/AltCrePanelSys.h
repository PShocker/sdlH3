#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <utility>
struct AltCrePanelSys {
  static void draw(std::vector<std::pair<uint16_t, uint32_t>> &creVec,
                   int32_t x, int32_t y);
  static uint8_t click(int32_t x, int32_t y);

  static void drawBorder(int32_t x, int32_t y, uint8_t index);
};