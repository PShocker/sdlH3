#include "SwanPondSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Global/Global.h"

#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>

static float bakW = 450;
static float bakH = 340;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  if (heroComp.visited.contains((uint8_t)ObjectType::SWAN_POND)) {
    return true;
  } else {
    return false;
  }
}

static void receive() {
  World::exitScrn();
  if (!visited()) {
    auto &heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    heroComp.luck.push_back({(uint8_t)ObjectType::SWAN_POND, 1});
    heroComp.visited.insert((uint8_t)ObjectType::SWAN_POND);
    heroComp.visitedLog.insert({(uint8_t)ObjectType::SWAN_POND, 0});
    heroComp.movement = 0;
  }
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  b.func = receive;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::SWAN_POND]);
  return;
}

const SDL_FRect lukPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto texture = Global::defCache["ilck82.def/0"][4];
  posRect = {leftUp.x + lukPosition.x, leftUp.y + lukPosition.y, lukPosition.w,
             lukPosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == SwanPondSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool SwanPondSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickLuk(bool leftClick) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect{leftUp.x + lukPosition.x, leftUp.y + lukPosition.y,
                    lukPosition.w, lukPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (!leftClick) {
      HeroScrSys::showLukComfirm(leftClick);
    }
    return true;
  }
  return false;
}

bool SwanPondSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool SwanPondSys::rightMouseDown(float x, float y) {
  if (clickLuk(false)) {
    return true;
  }
  return true;
}

bool SwanPondSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    receive();
    break;
  }
  default:
    break;
  }
  return true;
}