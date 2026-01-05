#include "MineSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/MineComp.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"

static float bakW = 450;
static float bakH = 340;

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  auto &mineComp =
      World::registrys[World::level].get<MineComp>(Global::goalEnt);
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15, strPool[918 + mineComp.id]);

  FreeTypeSys::setColor(255, 255, 255, 255);
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 40, strPool[2192 + mineComp.id]);

  return;
}

const SDL_FRect minePosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto mineComp = World::registrys[World::level].get<MineComp>(Global::goalEnt);
  auto texture = Global::defCache["RESOUR82.def/0"][mineComp.id];
  posRect = {leftUp.x + minePosition.x, leftUp.y + minePosition.y,
             minePosition.w, minePosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == MineSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool MineSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickMine(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + minePosition.x, leftUp.y + minePosition.y,
             minePosition.w, minePosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (!leftClick) {
      // HeroScrSys::showLukComfirm(leftClick);
    }
    return true;
  }
  return false;
}

bool MineSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool MineSys::rightMouseDown(float x, float y) {
  if (clickMine(false)) {
    return true;
  }
  return true;
}

bool MineSys::keyUp(uint16_t key) {
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