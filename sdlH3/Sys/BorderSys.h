#pragma once

#include <cstdint>
struct BorderSys {
  static void drawMaskWithHole(float holeX, float holeY, float holeWidth,
                               float holeHeight, uint8_t alpha);
  static bool run();
};