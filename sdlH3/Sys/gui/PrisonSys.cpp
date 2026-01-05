#include "PrisonSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Cfg/HeroCfg.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PrisonComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 400;
static float bakH = 340;

static void receive() {
  auto registry = &World::registrys[World::level];
  Global::fadeCallBack = []() {
    World::LMouseUpSysBak.pop_back();
    World::LMouseDownSysBak.pop_back();
    World::RMouseUpSysBak.pop_back();
    World::RMouseDownSysBak.pop_back();
    World::keyUpSysBak.pop_back();
    Global::cursorBack.pop_back();
    return true;
  };
  World::iterateSystems.pop_back();
  World::iterateSystems.pop_back();
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystemsBak.back().push_back(CursorSys::run);
  World::iterateSystems.push_back([registry]() {
    auto heroComp =
        World::registrys[World::level].get<HeroComp>(Global::goalEnt);
    auto objectComp =
        World::registrys[World::level].get<ObjectComp>(Global::goalEnt);
    auto newHeroEnt =
        Ent::loadHero(heroComp, Global::playerId, objectComp.x + 1,
                      objectComp.y, World::level, 2, 0);
    Global::heros[Global::playerId].push_back({World::level, newHeroEnt});
    registry->destroy(Global::goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
  return;
}
static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

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
                          strPool[926 + (uint8_t)ObjectType::PRISON]);

  FreeTypeSys::setColor(255, 255, 255, 255);
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 40, strPool[684]);

  return;
}

const static SDL_FRect porPosition = {bakW / 2 - 29, 160, 58, 64};

void PrisonSys::draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto heroComp = World::registrys[World::level].get<HeroComp>(Global::goalEnt);
  auto portrait =
      heroComp.portrait == 0xff ? heroComp.subId : heroComp.portrait;
  auto texture = Global::pcxCache[HeroCfg::heroLargePor[portrait]][0];
  posRect = {leftUp.x + porPosition.x, leftUp.y + porPosition.y, porPosition.w,
             porPosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == PrisonSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool PrisonSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickPor(bool leftClick) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect = {leftUp.x + porPosition.x, leftUp.y + porPosition.y,
                       porPosition.w, porPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {

    if (leftClick) {
      auto &heroComp =
          World::registrys[World::level].get<HeroComp>(Global::goalEnt);
      HeroScrSys::showHeroBiosComfirm(leftClick, heroComp.portrait);
    } else {
      World::enterHeroScrn(World::level, Global::goalEnt,
                           (uint8_t)Enum::SCNTYPE::POP);
    }
    return true;
  }
  return false;
}

bool PrisonSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  if (clickPor(true)) {
    return false;
  }
  return true;
}

bool PrisonSys::rightMouseDown(float x, float y) {
  if (clickPor(false)) {
    return false;
  }
  return true;
}

bool PrisonSys::keyUp(uint16_t key) {
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