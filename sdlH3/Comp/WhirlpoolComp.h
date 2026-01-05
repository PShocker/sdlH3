#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <vector>
struct WhirlpoolComp {
  uint8_t x;
  uint8_t y;
  int32_t order;

  std::vector<entt::entity> goalEnt;
};