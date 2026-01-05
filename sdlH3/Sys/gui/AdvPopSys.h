#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
struct AdvPopSys {
  static bool run();
  static void drawBackGround(float x, float y, float w, float h,
                             uint8_t playerId);
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool keyUp(uint16_t key);
};