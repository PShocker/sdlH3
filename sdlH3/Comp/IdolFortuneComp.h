#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <unordered_set>
struct IdolFortuneComp {
  std::unordered_set<uint8_t> visitHeros;
};