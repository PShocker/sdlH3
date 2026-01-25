#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <optional>
#include <utility>
struct HeroListSys {
  static void draw(int32_t x, int32_t y, int32_t length, uint8_t page,
                   uint8_t i, uint8_t playerId, bool top);
  static bool click(int32_t x, int32_t y, int32_t length, uint8_t &page,
                    uint8_t &i, uint8_t playerId, uint8_t clickType);
};