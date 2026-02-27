
#include "Comp/HeroComp.h"
#include "Comp/PositionComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Set/SpellSet.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/HeroSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/CursorSys.h"
#include "Sys/gui/SpellSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <any>
#include <cstdint>

void SpellSet::DimensionDoor(std::any data) {
  auto &registry = World::registrys[World::level];
  auto heroPair =
      Global::heros[Global::playerId][Global::herosIndex[Global::playerId]];
  auto heroEnt = heroPair.second;

  auto heroComp = &registry.get<HeroComp>(heroEnt);

  if (heroComp->moveType == HeroComp::BOAT) {
    float confirmbakW = 200;
    float confirmbakH = 200;
    Global::confirmdraw = [confirmbakW, confirmbakH]() {
      SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                        Global::viewPort.h / 2 - confirmbakH / 2};
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                              strPool[0]);
    };
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    auto type = ((uint8_t)Enum::SCNTYPE::MOD);
    World::enterConfirm(confirmbakW, confirmbakH, type);
    return;
  }

  World::enterAdvScrn();

  AdvMapSys::heroFocus();
  Global::cursorType = (uint8_t)Enum::CURSOR::SPELL;
  Global::cursorSpellIndex = (uint8_t)Enum::CRADVNTR::TELEPORT;
  Global::cursorSpellRange = 7;
  Global::cursorSpellGoal = ObjectType::LAND;

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

      HeroSys::heroTelePort(heroEnt, goalX, goalY);
      AdvMapSys::heroFocus();

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