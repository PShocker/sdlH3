#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <optional>
struct GateComp {
  uint8_t x;
  uint8_t y;
  uint8_t level;
  int32_t order;

  entt::entity goalEnt;
};