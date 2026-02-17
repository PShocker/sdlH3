#include "TownFortSys.h"
#include "AdvMapSys.h"

#include "Comp/DwellingComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/TownComp.h"
#include "CreatureSys.h"
#include "DwellingSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Set/CreatureSet.h"
#include "Set/FactionSet.h"
#include "Sys/FreeTypeSys.h"
#include "TownSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include <cstdint>
#include <iterator>

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["TPMAGE1.DEF/0"];
  b.r = {748, 556, 48, 40};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TownFortSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto dweSize = TownSys::townDweBuilds(level, townEnt).size();
  auto fotBakStr = dweSize == 8 ? "TPCASTL8.pcx" : "TPCASTL7.pcx";
  auto texture = Global::pcxCache[fotBakStr][Global::playerId];
  posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  auto fortLevel = TownSys::fortLevel(level, townEnt);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(17);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(leftUp.x + 400, leftUp.y,
                          strPool[3049 + fortLevel * 2]);
}

SDL_FRect slot7[] = {
    {10, 22, 386, 126},   {404, 22, 386, 126}, {10, 155, 386, 126},
    {404, 155, 386, 126}, {10, 288, 386, 126}, {404, 288, 386, 126},
    {206, 421, 386, 126},
};

SDL_FRect slot8[] = {
    {10, 22, 386, 126},   {404, 22, 386, 126},  {10, 155, 386, 126},
    {404, 155, 386, 126}, {10, 288, 386, 126},  {404, 288, 386, 126},
    {10, 421, 386, 126},  {404, 421, 386, 126},
};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto dweSize = TownSys::townDweBuilds(level, townEnt).size();
  auto dwes = TownSys::townDweBuilds(level, townEnt);
  SDL_FRect *slotPtr = slot7;
  uint8_t spBid;
  for (auto d : dwes) {
    if (d.bId == Enum::BUILD_SPECIAL_10 || d.bId == Enum::BUILD_SPECIAL_18 ||
        d.bId == Enum::BUILD_SPECIAL_19 || d.bId == Enum::BUILD_SPECIAL_20 ||
        d.bId == Enum::BUILD_SPECIAL_21) {
      slotPtr = slot8;
      spBid = d.bId;
      break;
    }
  }
  for (uint8_t i = 0; i < 8; i++) {
    auto bId = Enum::BUILD_DWELLING_UPGRADE_LEVEL_1 + i * 3;
    if (i > 4) {
      bId = Enum::BUILD_DWELLING_UPGRADE_LEVEL_6 + (i - 5) * 2;
    }
    uint16_t creatureId;
    if (i == 7) {
      if (slotPtr == slot8) {
        bId = spBid;
        auto dComp = registry.get<DwellingComp>(townComp->buildings[bId]);
        creatureId = dComp.creatures.back().first.back();
      } else {
        break;
      }
    } else if (townComp->buildings.contains(bId)) {
      creatureId =
          CreatureSet::townCreatures[townComp->id]->at(i * 2 + 1).index;
    } else {
      creatureId = CreatureSet::townCreatures[townComp->id]->at(i * 2).index;
      bId = bId - 1;
    }

    bool hasBuild = false;
    if (townComp->buildings.contains(bId) ||
        townComp->buildings.contains(bId - 1)) {
      hasBuild = true;
    }
    SDL_FRect posRect2 = {leftUp.x + slotPtr[i].x, leftUp.y + slotPtr[i].y,
                          slotPtr[i].w, slotPtr[i].h};
    auto texture = Global::pcxCache["TPCAINFO.pcx"][0];
    posRect = {posRect2.x + 261, posRect2.y + 3, static_cast<float>(texture->w),
               static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(248, 240, 216, 255);

    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::draw(posRect2.x + 287, posRect2.y + 4, strPool[2339]);
    FreeTypeSys::draw(posRect2.x + 287, posRect2.y + 24, strPool[2340]);
    FreeTypeSys::draw(posRect2.x + 287, posRect2.y + 45, strPool[2341]);
    FreeTypeSys::draw(posRect2.x + 287, posRect2.y + 65, strPool[2342]);
    FreeTypeSys::draw(posRect2.x + 287, posRect2.y + 86, strPool[2343]);
    FreeTypeSys::draw(posRect2.x + 287, posRect2.y + 106, strPool[2344]);

    auto v = CreatureSet::fullCreatures[creatureId]->attribute;
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 4, v.attack);   // atk
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 24, v.defense); // def
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 45,
                          FreeTypeSys::str(v.minDamage) + u"-" +
                              FreeTypeSys::str(v.maxDamage)); // dmg
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 65,
                          v.hitPoint);                                 // life
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 86, v.speed); // speed

    auto bStr = strPool[3043 + (int8_t)bId * 2];
    FreeTypeSys::drawCenter(posRect2.x + 79, posRect2.y + 90, bStr);

    auto tStr = FactionSet::fullFactions[townComp->id]->builds[bId].icon;
    texture = Global::pcxCache[tStr][0];
    posRect = {posRect2.x + 4, posRect2.y + 21, static_cast<float>(texture->w),
               static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    auto cStr = strPool[12 + creatureId];
    FreeTypeSys::drawCenter(posRect2.x + 79, posRect2.y, cStr);

    auto group = Global::townFortGroup[i];
    auto index = Global::townFortFrameIndex[i];
    DwellingSys::drawCreatureBak2(posRect2.x + 159, posRect2.y + 4, creatureId,
                                  group, index, 0xff);

    if (hasBuild) {
      auto iv = TownSys::townDweInc(level, townEnt, bId);
      uint32_t growth = 0;
      for (auto v : iv) {
        growth += v.num;
      }
      FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 106,
                            growth); // growth

      auto dComp = registry.get<DwellingComp>(townComp->buildings[bId]);
      auto remainStr =
          strPool[3797] + FreeTypeSys::str(dComp.creatures.back().second);
      FreeTypeSys::drawCenter(posRect2.x + 79, posRect2.y + 108, remainStr);
    }
  }
}

static void fortAnimate() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];

  uint8_t spBid = 0;
  auto dwes = TownSys::townDweBuilds(level, townEnt);
  for (auto d : dwes) {
    if (d.bId == Enum::BUILD_SPECIAL_10 || d.bId == Enum::BUILD_SPECIAL_18 ||
        d.bId == Enum::BUILD_SPECIAL_19 || d.bId == Enum::BUILD_SPECIAL_20 ||
        d.bId == Enum::BUILD_SPECIAL_21) {
      spBid = d.bId;
      break;
    }
  }

  for (uint8_t i = 0; i < 8; i++) {
    auto bId = Enum::BUILD_DWELLING_UPGRADE_LEVEL_1 + i * 3;
    if (i > 4) {
      bId = Enum::BUILD_DWELLING_UPGRADE_LEVEL_6 + (i - 5) * 2;
    }
    uint16_t creatureId;
    auto townComp = &registry.get<TownComp>(townEnt);
    if (i == 7) {
      if (spBid != 0) {
        auto dComp = registry.get<DwellingComp>(townComp->buildings[bId]);
        creatureId = dComp.creatures.back().first.back();
      } else {
        break;
      }
    } else if (townComp->buildings.contains(bId)) {
      creatureId =
          CreatureSet::townCreatures[townComp->id]->at(i * 2 + 1).index;
    } else {
      creatureId = CreatureSet::townCreatures[townComp->id]->at(i * 2).index;
    }
    CreatureSys::creAnimate(Global::townFortFrameTime[i],
                            Global::townFortFrameIndex[i],
                            Global::townFortGroup[i], creatureId);
  }
}

static void drawResbar() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  AdvMapSys::drawResBar(leftUp.x + 3, leftUp.y + 575);
}

bool TownFortSys::run() {
  drawBackGround();
  draw();
  drawButton();
  drawResbar();
  fortAnimate();
  return true;
}

static bool clickSlot(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto dweSize = TownSys::townDweBuilds(level, townEnt).size();
  auto dwes = TownSys::townDweBuilds(level, townEnt);
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect *slotPtr;
  if (dweSize == 7) {
    slotPtr = slot7;
  } else {
    slotPtr = slot8;
  }
  for (uint8_t i = 0; i < dweSize; i++) {
    posRect = {leftUp.x + slotPtr[i].x, leftUp.y + slotPtr[i].y, slotPtr[i].w,
               slotPtr[i].h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (townComp->heroEnt[0].has_value()) {
        World::enterDwe(townComp->heroEnt[0].value(), dwes[i].ent);
      } else {
        World::enterDwe(entt::null, dwes[i].ent);
      }
      return true;
    }
  }
  return false;
}

bool TownFortSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickSlot(clickType)) {
    return false;
  }
  return true;
}