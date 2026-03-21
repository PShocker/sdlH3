#pragma once

#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
struct TownFortSys {
  static inline std::vector<Button> buttons;

  static void init();

  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool keyUp(uint16_t key);
};