
#include "Comp/HeroComp.h"
#include "Comp/PositionComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Set/SpellSet.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/CursorSys.h"
#include "Sys/gui/SpellSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <any>
#include <cstdint>
#include <utility>

void SpellSet::ScuttleBoat(std::any data) {
  World::enterAdvScrn();
  Global::cursorType = (uint8_t)Enum::CURSOR::SPELL;
  Global::cursorSpellIndex = (uint8_t)Enum::CRADVNTR::SCUTTLE_BOAT;
  Global::cursorSpellRange = 1;
  Global::cursorSpellGoal = ObjectType::BOAT;
  AdvMapSys::heroFocus();

  Global::cursorSpellBack = []() {
    auto &registry = World::registrys[World::level];
    auto heroPair =
        Global::heros[Global::playerId][Global::herosIndex[Global::playerId]];
    auto heroEnt = heroPair.second;
    auto heroComp = &registry.get<HeroComp>(heroEnt);
    auto skillLevel = SpellSys::spellLevel(heroComp, 0);
    auto manaCost = SpellSet::spells[0].manaCost[skillLevel.second];
    heroComp->mana -= manaCost;
    World::iterateSystemsBak.push_back(World::iterateSystems);
    World::iterateSystems.pop_back();
    World::iterateSystems.push_back([]() {
      auto &registry = World::registrys[World::level];
      SDL_FPoint point = {Global::viewPort.x + Window::mouseX,
                          Global::viewPort.y + Window::mouseY};
      auto p = CursorSys::goalPoint(point);
      uint8_t goalX = p.x;
      uint8_t goalY = p.y;
      auto [_, ent] = CursorSys::choose(false, goalX * 32 - Global::viewPort.x,
                                        goalY * 32 - Global::viewPort.y);
      registry.destroy(ent);
      World::needSort = true;
      Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
      CursorSys::clearHeroPath();
      return true;
    });
    Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                        Global::viewPort.h - 47};
    World::iterateSystems.push_back(World::enterFadeScrn);
  };
  return;
}