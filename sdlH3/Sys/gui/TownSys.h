#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <vector>
struct TownSys {
  static void
  drawCreature(uint8_t i, std::vector<std::pair<uint16_t, uint32_t>> *creature);
  static void split();
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
};