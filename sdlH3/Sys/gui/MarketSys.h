#pragma once

#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
struct MarketSys {
  static bool run();
  static bool keyUp(uint16_t key);

  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
};