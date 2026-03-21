#pragma once

#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
#include <vector>

struct TavernSys {
  static inline std::vector<Button> buttons;

  static void init();

  static bool refreshHero(uint8_t playerId, uint8_t index);
  static bool refreshHero(uint8_t playerId, uint8_t index, uint8_t heroClasz);

  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
};