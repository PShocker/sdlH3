#include "WhirlPoolSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "CameraSys.h"
#include "Comp/HeroComp.h"
#include "Comp/WhirlpoolComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/HeroSys.h"
#include "Sys/gui/CursorSys.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static void closeScrn() { World::exitScrn(); }

static void enter() {
  closeScrn();
  auto &registry = World::registrys[World::level];
  auto &wComp = registry.get<WhirlpoolComp>(Global::goalEnt);
  if (wComp.goalEnt.empty()) {
    return;
  }
  auto goalMono = wComp.goalEnt[std::rand() % wComp.goalEnt.size()];

  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();

  registry.get<HeroComp>(Global::heroEnt).curEnt = goalMono;

  auto goalX = registry.get<WhirlpoolComp>(goalMono).x;
  auto goalY = registry.get<WhirlpoolComp>(goalMono).y;

  World::iterateSystems.push_back([goalX, goalY]() {
    HeroSys::heroTelePort(Global::heroEnt, goalX, goalY);
    CameraSys::focus(goalX * 32 + 16, goalY * 32 + 16);
    Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
    CursorSys::clearHeroPath();
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
}

void WhirlPoolSys::init() {
  buttons.clear();
  {
    Button button;
    button.textures = Global::defCache["iOKAY.def/0"];
    button.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    button.clickFunc = enter;
    button.disableFunc = []() { return false; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }
  {
    Button button;
    button.textures = Global::defCache["ICANCEL.DEF/0"];
    button.r = {bakW / 2 - 32 + 48, bakH - 60, 64, 30};
    button.clickFunc = closeScrn;
    button.disableFunc = []() { return false; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  auto oName = strPool[927 + ObjectType::WHIRLPOOL];

  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15, oName);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == WhirlPoolSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, WhirlPoolSys::buttons);
}

bool WhirlPoolSys::run() {
  drawBackGround();
  drawButton();
  return true;
}

bool WhirlPoolSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, WhirlPoolSys::buttons,
                              clickType)) {
    return false;
  }
  return true;
}

bool WhirlPoolSys::keyUp(uint16_t key) { return true; }