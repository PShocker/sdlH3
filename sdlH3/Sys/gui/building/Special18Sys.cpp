#include "Special18Sys.h"

#include "Comp/HeroComp.h"
#include "Comp/TownComp.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/AdvPopSys.h"
#include "Sys/gui/TownSys.h"
#include "World/World.h"
#include <cstdint>
#include <utility>

static std::pair<float, float> bakWH() {
  float bakW = 480;
  float bakH = 300;
  return {bakW, bakH};
}
static void close() {}

static void receive() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto id = townComp->id;
}

static std::vector<Button> buttonInfo() {
  auto [bakW, bakH] = bakWH();
  std::vector<Button> v;

  Button b;
  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  //   b.func = receive;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void draw() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto id = townComp->id;
}

static void drawButton() {
  auto [bakW, bakH] = bakWH();
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == Special18Sys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool Special18Sys::run() {
  draw();
  drawButton();
  return true;
}

void Special18Sys::visit() {
}