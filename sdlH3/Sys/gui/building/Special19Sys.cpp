#include "Special19Sys.h"
#include "Cfg/TownCfg.h"
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
  switch (id) {
  case (uint8_t)TownCfg::Faction::CASTLE: {
    auto bId = (uint8_t)TownCfg::Building::SPECIAL_10;
    auto i = TownSys::visitBuild(bId);
    if (i != 0xff) {
      auto heroEnt = townComp->heroEnt[i].value();
      auto heroComp = registry.get<HeroComp>(heroEnt);
      heroComp.primSkills[0] += 1;
      townComp->visitHeros[bId].insert(heroComp.portrait);
    }
    i = TownSys::visitBuild(bId);
    if (i == 0xff) {
      close();
    }
  }
  default: {
    break;
  }
  }
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
  switch (id) {
  case (uint8_t)TownCfg::Faction::CASTLE: {
    auto [bakW, bakH] = bakWH();
    auto x = Global::viewPort.w / 2;
    auto y = Global::viewPort.h / 2;
    AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    auto strPool = *Lang::strPool[Global::langIndex];
    std::u16string s = strPool[928];
    FreeTypeSys::drawCenter(x, y - bakH / 2 + 15, s);
  }
  default: {
    break;
  }
  }
}

static void drawButton() {
  auto [bakW, bakH] = bakWH();
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == Special19Sys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool Special19Sys::run() {
  draw();
  drawButton();
  return true;
}