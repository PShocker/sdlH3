#include "TownFortSys.h"
#include "AdvMapSys.h"
#include "Cfg/TownCfg.h"
#include "Comp/DwellingComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/TownComp.h"
#include "DwellingSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
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
  SDL_FRect *slotPtr;
  if (dweSize == 7) {
    slotPtr = slot7;
  } else {
    slotPtr = slot8;
  }
  auto dwes = TownSys::townDweBuilds(level, townEnt);
  for (uint8_t i = 0; i < dweSize; i++) {
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

    auto dwe = dwes[i];
    auto dComp = registry.get<DwellingComp>(dwe.ent);
    auto creatureId = dComp.creatures.back().first.back();
    auto v = CreatureCfg::creatureAttr.at(creatureId);

    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 4, v[2]);  // atk
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 24, v[3]); // def
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 45,
                          FreeTypeSys::str(v[4]) + u"-" +
                              FreeTypeSys::str(v[5]));              // dmg
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 65, v[0]); // life
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 86, v[1]); // speed
    auto iv = TownSys::townDweInc(level, townEnt, dwe.bId);
    uint32_t growth = 0;
    for (auto v : iv) {
      growth += v.num;
    }
    FreeTypeSys::drawLeft(posRect2.x + 380, posRect2.y + 106,
                          growth); // growth

    auto tStr = TownCfg::townBuildIcon[townComp->id].at(dwe.bId);
    texture = Global::pcxCache[tStr][0];
    posRect = {posRect2.x + 4, posRect2.y + 21, static_cast<float>(texture->w),
               static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    auto bStr = strPool[3043 + (int8_t)dwe.bId * 2];
    FreeTypeSys::drawCenter(posRect2.x + 79, posRect2.y + 90, bStr);

    auto remainStr =
        strPool[3797] + FreeTypeSys::str(dComp.creatures.back().second);
    FreeTypeSys::drawCenter(posRect2.x + 79, posRect2.y + 108, remainStr);

    auto cStr = strPool[12 + creatureId];
    FreeTypeSys::drawCenter(posRect2.x + 79, posRect2.y, cStr);

    auto group = Global::townFortGroup[i];
    auto index = Global::townFortFrameIndex[i];
    DwellingSys::drawCreatureBak2(posRect2.x + 159, posRect2.y + 4, creatureId,
                                  group, index, 0xff);
  }
}

static void fortAnimate() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto dweSize = TownSys::townDweBuilds(level, townEnt).size();
  for (uint8_t i = 0; i < dweSize; i++) {
    Global::townFortFrameTime[i] += Window::deltaTime;
    if (Global::townFortFrameTime[i] >= 90) {
      Global::townFortFrameTime[i] = 0;
      Global::townFortFrameIndex[i] += 1;

      auto dwes = TownSys::townDweBuilds(level, townEnt);
      auto dwe = dwes[i];
      auto dComp = registry.get<DwellingComp>(dwe.ent);
      auto creatureId = dComp.creatures.back().first.back();

      auto group = Global::townFortGroup[i];

      auto textures =
          Global::defCache[CreatureCfg::creatureGraphics.at(creatureId) + "/" +
                           std::to_string(group)];
      if (Global::townFortFrameIndex[i] >= textures.size()) {
        Global::townFortFrameIndex[i] = 0;
        int arr[] = {0, 2, 3, 4};
        std::uniform_int_distribution<> distrib(0, std::size(arr) - 1);
        // 生成随机索引并选择元素
        int randomIndex = distrib(Global::gen);
        Global::townFortGroup[i] = arr[randomIndex];
      }
    }
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