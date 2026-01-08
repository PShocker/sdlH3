#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
struct MageGuildSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
};