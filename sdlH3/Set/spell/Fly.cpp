
#include "Comp/HeroComp.h"
#include "Set/SpellSet.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <any>
#include <cstdint>
#include <utility>

void SpellSet::Fly(std::any data) {
  World::enterAdvScrn();
  auto [heroEnt, level] = std::any_cast<std::pair<entt::entity, uint8_t>>(data);
  auto registry = &World::registrys[World::level];
  registry->get<HeroComp>(heroEnt).moveType = HeroComp::FLY;
  return;
}