#pragma once

#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
struct ConfirmSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool keyUp(uint16_t key);
};