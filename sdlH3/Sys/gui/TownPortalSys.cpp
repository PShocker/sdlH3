#include "TownPortalSys.h"
#include "AdvMapSys.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "Window/Window.h"
#include "World/World.h"

static void close() { World::exitScrn(); }
static void portal() { World::exitScrn(); }

std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {228, 402, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {15, 402, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 306) / 2,
                    (Global::viewPort.h - 469) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TownPortalSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 306) / 2,
                    (Global::viewPort.h - 469) / 2};
  auto texture = Global::pcxCache["TPGATE.pcx"][Global::playerId];
  posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawTowns() {
  SDL_FPoint leftUp{(Global::viewPort.w - 306) / 2,
                    (Global::viewPort.h - 469) / 2};
  SDL_FRect posRect{leftUp.x, leftUp.y, 48, 32};
  for (uint8_t i = 0; i < 5; i++) {
    auto index = i + Global::townPorPage;
    if (index >= Global::towns[Global::playerId].size()) {
      break;
    }
    auto &[level, townEnt] = Global::towns[Global::playerId][index];
    auto &registry = World::registrys[level];
    auto townComp = &registry.get<TownComp>(townEnt);
    auto texture = Global::defCache["ITPA.DEF/0"][2 + 2 * townComp->id];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == Global::townsIndex[Global::playerId]) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
    posRect.y += 32;
  }
}
bool TownPortalSys::run() {
  drawBackGround();
  drawTowns();
  drawButton();
  return true;
}

bool TownPortalSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    close();
    break;
  }
  default:
    break;
  }
  return true;
}

bool TownPortalSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}