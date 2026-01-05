#include "GarrisonSys.h"
#include "AdvMapSys.h"
#include "Global/Global.h"

#include "SDL3/SDL_rect.h"
#include "Window/Window.h"
#include "World/World.h"
#include <vector>

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["IDV6432.DEF/0"];
  b.r = {88, 314, 64, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["IOK6432.def/0"];
  b.r = {399, 314, 64, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 549) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 396) / 2)};
  posRect = {leftUp.x, leftUp.y, 549, 396};
  auto texture = Global::pcxCache["GARRISON.PCX"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 549) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 396) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == GarrisonSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool GarrisonSys::run() {
  drawBackGround();
  drawButton();
  return true;
}

bool GarrisonSys::keyUp(uint16_t key) { return false; }

bool GarrisonSys::rightMouseUp(float x, float y) { return true; }

bool GarrisonSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 549) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 396) / 2)};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}