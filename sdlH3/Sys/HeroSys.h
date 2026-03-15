#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
struct HeroSys {
  static void heroTelePort(entt::entity heroEnt, uint8_t x, uint8_t y);
  static bool run();

  // network
  static void NetHeroMove(uint8_t por,uint8_t x,uint8_t y);
};