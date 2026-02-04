#include "TownFortSys.h"
#include "AdvMapSys.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "TownSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include <cstdint>

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
  for (uint8_t i = 0; i < dweSize; i++) {
    auto texture = Global::pcxCache["TPCAINFO.pcx"][0];
  }
}

bool TownFortSys::run() {
  drawBackGround();
  draw();
  drawButton();
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