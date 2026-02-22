
#include "Comp/HeroComp.h"
#include "Comp/PositionComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "SDL3/SDL_rect.h"
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

void SpellSet::SummonBoat(std::any data) {
  World::enterAdvScrn();
  Global::cursorType = (uint8_t)Enum::CURSOR::SPELL;
  Global::cursorSpellIndex = (uint8_t)Enum::CRADVNTR::T1_SAIL;
  Global::cursorSpellRange = 1;
  Global::cursorSpellGoal = ObjectType::SEA;
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
    World::iterateSystems.push_back([heroEnt]() {
      auto &registry = World::registrys[World::level];
      auto positionComp = &registry.get<PositionComp>(heroEnt);
      uint8_t heroX = (positionComp->point.x / 32.0) + 1;
      uint8_t heroY = (positionComp->point.y / 32.0) + 1;
      SDL_FPoint point = {Global::viewPort.x + Window::mouseX,
                          Global::viewPort.y + Window::mouseY};
      auto p = CursorSys::goalPoint(point);
      uint8_t goalX = p.x;
      uint8_t goalY = p.y;
      goalX = std::clamp(goalX, (uint8_t)(heroX - 1), (uint8_t)(heroX + 1));
      goalY = std::clamp(goalY, (uint8_t)(heroY - 1), (uint8_t)(heroY + 1));
      Ent::loadBoat("AB01_.def", goalX + 1, goalY, World::level, 2, 0);
      Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
      CursorSys::clearHeroPath();
      return true;
    });
    Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                        Global::viewPort.h - 47};
    World::iterateSystems.push_back(World::enterFadeScrn);
  };
  return;
  return;
}