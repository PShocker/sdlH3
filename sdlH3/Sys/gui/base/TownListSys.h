#pragma once

#include "Comp/HeroComp.h"
#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
#include <optional>
#include <utility>
struct TownListSys {

  static inline std::vector<Button> buttons;

  static void init(int32_t x, int32_t y, int32_t length, uint8_t &page,
                   uint8_t i, uint8_t playerId);

  static void draw(int32_t x, int32_t y, int32_t length, uint8_t page,
                   uint8_t i, uint8_t playerId, bool top);
  static bool click(int32_t x, int32_t y, int32_t length, uint8_t &page,
                    uint8_t &i, uint8_t playerId, uint8_t clickType);
};