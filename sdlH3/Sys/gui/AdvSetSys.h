#pragma once

#include <cstdint>

struct AdvSetSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool keyUp(uint16_t key);
};