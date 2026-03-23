#pragma once

#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
struct StablesSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool keyUp(uint16_t key);
};