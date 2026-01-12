#include "TownLearnSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Cfg/TownCfg.h"
#include "Comp/LearnStoneComp.h"
#include "Comp/MageGuildComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/LevelUpSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <map>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static std::vector<uint8_t> learnSpells() {
  std::vector<uint8_t> r;
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  const auto addSpell = [&](uint8_t id) {
    if (townComp->buildings.contains(id)) {
      auto mEnt = townComp->buildings[id];
      auto mComp = registry.get<MageGuildComp>(mEnt);
      r.insert(r.end(), mComp.spells.begin(), mComp.spells.end());
    }
  };
  addSpell((uint8_t)TownCfg::Building::MAGE_GUILD_1);
  addSpell((uint8_t)TownCfg::Building::MAGE_GUILD_2);
  addSpell((uint8_t)TownCfg::Building::MAGE_GUILD_3);
  addSpell((uint8_t)TownCfg::Building::MAGE_GUILD_4);
  addSpell((uint8_t)TownCfg::Building::MAGE_GUILD_5);
  // 智慧术
  return r;
}

static void receive() {
  World::exitScrn();
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &lrnComp =
      World::registrys[World::level].get<LearnStoneComp>(Global::goalEnt);
  if (!lrnComp.visitHeros.contains(heroComp.portrait)) {
    heroComp.exp += 1000;
    if (LevelUpSys::prepareLvlUp(heroComp)) {
      World::enterLvlup(Global::heroEnt);
    }
    heroComp.visitedLog.insert({(uint8_t)ObjectType::LEARNING_STONE, 0});
  }
  heroComp.visited.insert((uint8_t)ObjectType::LEARNING_STONE);
  lrnComp.visitHeros.insert(heroComp.portrait);
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

  return;
}

const SDL_FRect primPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TownLearnSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool TownLearnSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

bool TownLearnSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool TownLearnSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;
  return true;
}

bool TownLearnSys::keyUp(uint16_t key) {
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
