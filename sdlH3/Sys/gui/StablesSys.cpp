#include "StablesSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "World/World.h"
#include <cstdint>

static float bakW = 450;
static float bakH = 340;

static void receive() {
  World::exitScrn();
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  if (!heroComp.visited.contains((uint8_t)ObjectType::STABLES)) {
    heroComp.movement += 100;
    heroComp.visitedLog.insert({(uint8_t)ObjectType::STABLES, 0});
  }
  heroComp.visited.insert((uint8_t)ObjectType::STABLES);
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures=Global::defCache["iOKAY.def/0"];
  b.r={bakW / 2 - 32, bakH - 60, 64, 30};
  b.func=receive;
  b.disable=false;
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

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == StablesSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool StablesSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

bool StablesSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool StablesSys::keyUp(uint16_t key) {
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