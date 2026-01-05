#pragma once

#include <cstdint>
struct TavernSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
};