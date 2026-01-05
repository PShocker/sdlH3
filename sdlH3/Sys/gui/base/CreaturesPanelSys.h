#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <utility>
struct CreaturesPanelSys {
  static void draw(int32_t x, int32_t y,
                   std::vector<std::pair<uint16_t, uint32_t>> &creVec);
  static uint8_t click(int32_t x, int32_t y);

  static void drawBorder(int32_t x, int32_t y, uint8_t index);
};