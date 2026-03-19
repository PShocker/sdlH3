#pragma once

#include "Sys/gui/AdvMapSys.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <vector>
struct FreeGuildSys {
  
  static inline std::vector<Button> buttons;

  static void init();
  
  static bool run();
  static bool keyUp(uint16_t key);

  static bool leftMouseUp(float x, float y);
};