#pragma once

#include <cstdint>
struct HeroTradeSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool leftMouseDown(float x, float y);
  static bool rightMouseDown(float x, float y);

  static bool keyUp(uint16_t key);
};