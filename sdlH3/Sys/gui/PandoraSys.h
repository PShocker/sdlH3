#pragma once

#include "Sys/gui/AdvMapSys.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
struct PandoraSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool keyUp(uint16_t key);
};