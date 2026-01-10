#include "OasisSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Comp/RalFlagComp.h"
#include "Enum/Enum.h"
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
  if (heroComp.visited.contains((uint8_t)ObjectType::OASIS)) {
    return true;
  } else {
    return false;
  }
}

static void receive() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &ralComp =
      World::registrys[World::level].get<RalFlagComp>(Global::goalEnt);
  if (!visited()) {
    heroComp.visited.insert((uint8_t)ObjectType::OASIS);
  }
  World::exitScrn();
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
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2,
                          strPool[926 + (uint8_t)ObjectType::OASIS]);
  return;
}

const SDL_FRect morPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto strPool = *Lang::strPool[Global::langIndex];
  if (visited()) {
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[2192]);
  } else {
    auto texture = Global::defCache["imrl82.def/0"][4];
    posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y,
               morPosition.w, morPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == OasisSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool OasisSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

bool OasisSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

static bool clickMor(uint8_t clickType) {
  if (!visited()) {
    SDL_FRect posRect;
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y,
               morPosition.w, morPosition.h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showLukComfirm(clickType);
      return true;
    }
  }
  return false;
}

bool OasisSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickMor(clickType)) {
    return true;
  }
  return true;
}

bool OasisSys::keyUp(uint16_t key) {
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