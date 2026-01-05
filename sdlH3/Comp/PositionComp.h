#pragma once

#include "SDL3/SDL_rect.h"
#include <cstdint>
struct PositionComp {
  SDL_FPoint point;
  uint8_t flip;
  int64_t z;
};