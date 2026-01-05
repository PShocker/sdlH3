#pragma once

#include "SDL3/SDL_rect.h"
#include <vector>
struct FogSys {
  static std::vector<SDL_Point> generateVerticalHexagon(int r);
  static bool run();
};