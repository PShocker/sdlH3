#include "WitchHutSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Comp/WindMillComp.h"
#include "Comp/WitchHutComp.h"
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
  auto &hComp = World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &wComp =
      World::registrys[World::level].get<WitchHutComp>(Global::goalEnt);
  for (auto secId : hComp.secSkills) {
    if (secId.first == wComp.secId) {
      return true;
    }
  }
  return false;
}

static void receive() {
  auto &hComp = World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &wComp =
      World::registrys[World::level].get<WitchHutComp>(Global::goalEnt);
  if (hComp.secSkills.size() >= 8) {
    World::exitScrn();
    return;
  }
  for (auto secId : hComp.secSkills) {
    if (secId.first == wComp.secId) {
      World::exitScrn();
      return;
    }
  }
  hComp.secSkills.push_back({wComp.secId, 0});
  World::exitScrn();
}

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  if (visited()) {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    b.func = receive;
    b.disable = false;
    v.push_back(b);

  } else {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32 - 48, bakH - 60, 64, 30};
    b.func = receive;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["ICANCEL.DEF/0"];
    b.r = {bakW / 2 - 32 + 48, bakH - 60, 64, 30};
    b.func = close;
    b.disable = false;
    v.push_back(b);
  }

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::WITCH_HUT]);

  return;
}

const SDL_FRect secPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &wComp =
      World::registrys[World::level].get<WitchHutComp>(Global::goalEnt);
  auto texture = Global::defCache["SECSK82.def/0"][3 * (wComp.secId + 1)];
  posRect = {leftUp.x + secPosition.x, leftUp.y + secPosition.y, secPosition.w,
             secPosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == WitchHutSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool WitchHutSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickSecSki(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + secPosition.x, leftUp.y + secPosition.y, secPosition.w,
             secPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto &wComp =
        World::registrys[World::level].get<WitchHutComp>(Global::goalEnt);
    HeroScrSys::showSecSkiComfirm(leftClick, wComp.secId, 0);
    return true;
  }
  return false;
}

bool WitchHutSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool WitchHutSys::rightMouseDown(float x, float y) {
  if (clickSecSki(false)) {
    return true;
  }
  return true;
}

bool WitchHutSys::keyUp(uint16_t key) {
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