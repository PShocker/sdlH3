#include "Cfg/SpellCfg.h"
#include "Comp/HeroComp.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <any>
#include <cstdint>
#include <utility>

void Fly(std::any data) {
  World::enterAdvScrn();
  auto [heroEnt, level] = std::any_cast<std::pair<entt::entity, uint8_t>>(data);
  auto registry = &World::registrys[World::level];
  registry->get<HeroComp>(heroEnt).moveType = HeroComp::FLY;
  return;
}