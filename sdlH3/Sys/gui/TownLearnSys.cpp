#include "TownLearnSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/SpellCfg.h"
#include "Cfg/TownCfg.h"
#include "Comp/HeroComp.h"
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

static std::set<uint8_t> studySpel(uint8_t i) {
  std::set<uint8_t> r;
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  const auto insertSpell = [&](uint8_t id) {
    if (townComp->buildings.contains(id)) {
      auto mEnt = townComp->buildings[id];
      auto &mComp = registry.get<MageGuildComp>(mEnt);
      r.insert(mComp.spells.begin(), mComp.spells.end());
    }
  };
  insertSpell((uint8_t)TownCfg::Building::MAGE_GUILD_1);
  insertSpell((uint8_t)TownCfg::Building::MAGE_GUILD_2);
  insertSpell((uint8_t)TownCfg::Building::MAGE_GUILD_3);
  insertSpell((uint8_t)TownCfg::Building::MAGE_GUILD_4);
  insertSpell((uint8_t)TownCfg::Building::MAGE_GUILD_5);
  // 智慧术
  if (townComp->heroEnt[i].has_value()) {
    auto heroEnt = townComp->heroEnt[i].value();
    auto &heroComp = registry.get<HeroComp>(heroEnt);
    int8_t wisdom = HeroScrSys::heroSecLevel(
        heroComp, (uint8_t)HeroCfg::SecondarySkill::WISDOM);
    std::set<uint8_t> intersection;
    if (wisdom == -1) {
      std::set<uint8_t> s;
      // 只能学习1-2级技能
      auto v1 = SpellCfg::SpellLevels[1];
      auto v2 = SpellCfg::SpellLevels[2];

      s.insert(v1.begin(), v1.end());
      s.insert(v2.begin(), v2.end());

      std::ranges::set_intersection(
          r, s, std::inserter(intersection, intersection.begin()));

    } else {
      std::set<uint8_t> s;
      for (auto i = 1; i <= wisdom + 3; i++) {
        auto v = SpellCfg::SpellLevels[i];
        s.insert(v.begin(), v.end());
      }
      std::ranges::set_intersection(
          r, s, std::inserter(intersection, intersection.begin()));
    }
    r.clear();
    std::ranges::set_difference(intersection, heroComp.spells,
                                std::inserter(r, r.begin()));
  }
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
  drawSpel();
  drawPrim();
  drawExp();
  drawMana();
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
