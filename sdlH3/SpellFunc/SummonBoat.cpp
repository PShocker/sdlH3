#include "Cfg/SpellCfg.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "Sys/gui/AdvMapSys.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <any>
#include <cstdint>
#include <utility>

void SummonBoat(std::any data) {
  World::enterAdvScrn();
  auto [heroEnt, level] = std::any_cast<std::pair<entt::entity, uint8_t>>(data);
  Global::cursorType=(uint8_t)Enum::CURSOR::SPELL;
  Global::cursorIndex=(uint8_t)Enum::CRADVNTR::T1_SAIL;
  AdvMapSys::heroFocus();
  return;
}