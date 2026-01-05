#pragma once

#include <cstdint>
struct KingdomSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool keyUp(uint16_t key);
};