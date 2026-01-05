#include "Cfg/SpellCfg.h"

#include "Sys/gui/AdvMapSys.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <any>
#include <cstdint>
#include <utility>

void TownPortal(std::any data) {
  auto [heroEnt, level] = std::any_cast<std::pair<entt::entity, uint8_t>>(data);
  World::enterTownPortal();
  AdvMapSys::heroFocus();
  return;
}