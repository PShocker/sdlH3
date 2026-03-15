#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
struct HeroSys {
  static void heroTelePort(entt::entity heroEnt, uint8_t x, uint8_t y);
  static bool run();
};