#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <utility>
struct PlayersPanelSys {
  static void draw(int32_t x, int32_t y, uint8_t index);
  static uint8_t click(int32_t x, int32_t y);
};