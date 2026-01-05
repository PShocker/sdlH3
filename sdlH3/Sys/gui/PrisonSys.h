#pragma once

#include <cstdint>
struct PrisonSys {
  static bool run();

  static void draw();

  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);

  static bool rightMouseDown(float x, float y);

  static bool keyUp(uint16_t key);
};