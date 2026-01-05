#pragma once
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <optional>
#include <vector>
struct MonolithComp {
  uint8_t x;
  uint8_t y;
  int32_t order;

  bool twoWay;
  bool entrance;
  uint8_t id;
  std::vector<entt::entity> goalEnt;
};