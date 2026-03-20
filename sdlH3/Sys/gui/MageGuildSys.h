#pragma once

#include "Sys/gui/AdvMapSys.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
struct MageGuildSys {
  static inline std::vector<Button> buttons;

  static void init();

  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static void study();
};