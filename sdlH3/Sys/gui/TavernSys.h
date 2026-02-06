#pragma once

#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
#include <vector>

struct TavernSys {
  static void refreshHero(uint8_t playerId, uint8_t index);

  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static std::vector<Button> buttonInfo();
};