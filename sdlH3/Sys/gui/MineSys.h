#pragma once

#include <cstdint>
struct MineSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
};