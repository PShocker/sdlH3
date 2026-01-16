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
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/LevelUpSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static bool visitBuild(uint8_t i, uint8_t bId) {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  if (townComp->heroEnt[i].has_value()) {
    auto heroEnt = townComp->heroEnt[i].value();
    auto &heroComp = registry.get<HeroComp>(heroEnt);
    if (townComp->visitHeros[bId].contains(heroComp.portrait)) {
      return true;
    }
  }
  return false;
}

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

static std::pair<uint8_t, uint8_t> studyPrim(uint8_t i) {
  uint8_t r0 = 0xff;
  uint8_t r1 = 0xff;
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  if (townComp->heroEnt[i].has_value()) {
    switch (townComp->id) {
    case (uint8_t)TownCfg::Faction::CONFLUX: {
      if (visitBuild(1, (uint8_t)TownCfg::Building::SPECIAL_10)) {
        r0 = 0;
        r1 = 1;
      }
      break;
    }
    }
  }
  return {r0, r1};
}

static uint32_t studyExp(uint8_t i) {
  uint32_t r = 0;
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  if (townComp->heroEnt[i].has_value()) {
    switch (townComp->id) {
    case (uint8_t)TownCfg::Faction::CONFLUX: {
      r = 1000;
      break;
    }
    }
  }
  return r;
}

static uint32_t studyMana(uint8_t i) {
  uint32_t r = 0;
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  if (townComp->heroEnt[i].has_value()) {
    switch (townComp->id) {
    case (uint8_t)TownCfg::Faction::CONFLUX: {
      r = 1000;
      break;
    }
    }
  }
  return r;
}
static void close() { World::exitScrn(); }

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

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TownLearnSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

const SDL_FRect spelPos[] = {{}, {}, {}, {}};

static bool drawSpel() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto s = studySpel(1);
  if (!s.empty()) {
    uint8_t i = 0;
    for (auto sId : s) {
      if (i > std::size(spelPos)) {
        break;
      }
      auto posRect = spelPos[i];
      posRect.x += leftUp.x;
      posRect.y += leftUp.y;
      auto textures = Global::defCache["Spells.DEF/0"];
      auto texture = textures[sId];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      i++;
    }
    return true;
  }
  return false;
}

const SDL_FRect primPos = {bakW / 2 - 41, bakH / 3, 82, 93};

static bool drawPrim() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto p = studyPrim(1);
  if (p.first != 0xff) {
    auto id = p.first;
    auto val = p.second;
    auto texture = Global::defCache["PSKILL.def/0"][id];
    posRect = {leftUp.x + primPos.x, leftUp.y + primPos.y, primPos.w,
               primPos.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2,
                            posRect.y + posRect.h + 4, val);
    return true;
  }
  return false;
}

static bool drawExp() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto e = studyExp(1);
  if (e != 0) {
    auto texture = Global::defCache["PSKILL.def/0"][4];
    posRect = {leftUp.x + primPos.x, leftUp.y + primPos.y, primPos.w,
               primPos.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2,
                            posRect.y + posRect.h + 4, e);
    return true;
  }
  return false;
}

static bool drawMana() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto m = studyMana(1);
  if (m != 0) {
    auto texture = Global::defCache["PSKILL.def/0"][5];
    posRect = {leftUp.x + primPos.x, leftUp.y + primPos.y, primPos.w,
               primPos.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2,
                            posRect.y + posRect.h + 4, m);
    return true;
  }
  return false;
}

bool TownLearnSys::run() {
  drawBackGround();
  uint8_t r = 0;
  if (drawSpel()) {
    r++;
  }
  if (drawPrim()) {
    r++;
  }
  if (drawExp()) {
    r++;
  }
  if (drawMana()) {
    r++;
  }
  drawButton();
  if (r == 0) {
    close();
    return false;
  }

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
