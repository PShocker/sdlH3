#include "WindMillSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/WindMillComp.h"
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
  auto &wComp =
      World::registrys[World::level].get<WindMillComp>(Global::goalEnt);
  return wComp.resources.empty();
}

static void receive() {
  World::exitScrn();
  Global::advVisted[Global::playerId][World::level].insert(Global::goalEnt);
  if (!visited()) {
    auto &wComp =
        World::registrys[World::level].get<WindMillComp>(Global::goalEnt);
    auto id = wComp.resources[0].first;
    auto num = wComp.resources[0].second;
    Global::resources[Global::playerId][id] += num;
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

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::WINDMILL]);

  return;
}

const SDL_FRect rPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  if (visited()) {
    FreeTypeSys::drawCenter(posRect.x + 41, posRect.y + 96, strPool[744]);
  } else {
    auto &wComp =
        World::registrys[World::level].get<WindMillComp>(Global::goalEnt);
    auto id = wComp.resources[0].first;
    auto texture = Global::defCache["RESOUR82.def/0"][id];
    posRect = {leftUp.x + rPosition.x, leftUp.y + rPosition.y, rPosition.w,
               rPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
    auto count = wComp.resources[0].second;
    FreeTypeSys::drawCenter(posRect.x + 41, posRect.y + 96, count);
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == WindMillSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool WindMillSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickRes(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + rPosition.x, leftUp.y + rPosition.y, rPosition.w,
             rPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto wComp =
        World::registrys[World::level].get<WindMillComp>(Global::goalEnt);
    auto id = wComp.resources[0].first;
    HeroScrSys::showResConfirm(clickType, id);
    return true;
  }
  return false;
}

bool WindMillSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool WindMillSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickRes(clickType)) {
    return false;
  }
  return true;
}

bool WindMillSys::keyUp(uint16_t key) {
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