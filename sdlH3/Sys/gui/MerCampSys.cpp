#include "MerCampSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/MarketComp.h"
#include "Comp/MarlettoComp.h"
#include "Comp/MerCampComp.h"
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
  auto &mComp =
      World::registrys[World::level].get<MerCampComp>(Global::goalEnt);
  if (mComp.visitHeros.contains(heroComp.portrait)) {
    return true;
  } else {
    return false;
  }
}

static void receive() {
  World::exitScrn();
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &mComp =
      World::registrys[World::level].get<MerCampComp>(Global::goalEnt);
  if (!visited()) {
    heroComp.primSkills[0] += 1;
    heroComp.visitedLog.insert({(uint8_t)ObjectType::MERCENARY_CAMP, 0});
  }
  mComp.visitHeros.insert(heroComp.portrait);
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
                          strPool[927 + (uint8_t)ObjectType::MERCENARY_CAMP]);
  return;
}

const SDL_FRect primPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  FreeTypeSys::setColor(255, 255, 255, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  if (visited()) {
    FreeTypeSys::drawCenter(leftUp.x, leftUp.y + 40, strPool[665]);
  } else {
    auto texture = Global::defCache["PSKILL.def/0"][0];
    posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
               primPosition.w, primPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);

    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2,
                            posRect.y + posRect.h + 4, u"+1 " + strPool[1]);

    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[664]);
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == MerCampSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool MerCampSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickAtk(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
             primPosition.w, primPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (!leftClick) {
      HeroScrSys::showPrimComfirm(leftClick, 0);
    }
    return true;
  }
  return false;
}

bool MerCampSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool MerCampSys::rightMouseDown(float x, float y) {
  if (clickAtk(false)) {
    return true;
  }
  return true;
}

bool MerCampSys::keyUp(uint16_t key) {
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