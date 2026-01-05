#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <vector>
struct FreeGuildSys {
  static bool run();
  static bool keyUp(uint16_t key);

  static bool leftMouseUp(float x, float y);
};