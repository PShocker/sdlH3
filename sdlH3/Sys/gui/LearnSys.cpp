#include "LearnSys.h"
#include "AdvMapSys.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/SpellCfg.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SpellSys.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvPopSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <cstdlib>
#include <iterator>

static float bakW = 480;
static float bakH = 300;

static std::set<uint8_t> swapSpel(uint8_t i) {
  std::set<uint8_t> r;

  auto level0 = World::level;
  auto level1 = Global::goalLevel;
  auto &hComp0 = World::registrys[level0].get<HeroComp>(Global::heroEnt);
  auto &hComp1 = World::registrys[level1].get<HeroComp>(Global::goalEnt);
  int8_t learnLevel = -1;
  // 判断有没有学术
  auto l1 = HeroScrSys::heroSecLevel(
      hComp0, (uint8_t)HeroCfg::SecondarySkill::LEARNING);
  auto l2 = HeroScrSys::heroSecLevel(
      hComp1, (uint8_t)HeroCfg::SecondarySkill::LEARNING);
  learnLevel = std::max(l1, l2);
  if (learnLevel == -1) {
    return r;
  }

  auto studyLevel = learnLevel + 2;
  std::set<uint8_t> r0;

  for (auto &s : {hComp0.spells, hComp1.spells}) {
    for (uint8_t i = 0; i <= studyLevel; i++) {
      r0.insert(SpellCfg::SpellLevels[i].begin(),
                SpellCfg::SpellLevels[i].end());
    }
  }
  std::set<uint8_t> intersection;
  HeroComp *hComp = nullptr;
  if (i == 0) {
    hComp = &hComp0;
  } else {
    hComp = &hComp1;
  }
  auto w = HeroScrSys::heroSecLevel(*hComp,
                                    (uint8_t)HeroCfg::SecondarySkill::WISDOM);
  if (w == -1) {
    std::set<uint8_t> s;
    auto v1 = SpellCfg::SpellLevels[1];
    auto v2 = SpellCfg::SpellLevels[2];

    s.insert(v1.begin(), v1.end());
    s.insert(v2.begin(), v2.end());

    std::ranges::set_intersection(
        r0, s, std::inserter(intersection, intersection.begin()));

  } else {
    std::set<uint8_t> s;
    for (auto i = 1; i <= w + 3; i++) {
      auto v = SpellCfg::SpellLevels[i];
      s.insert(v.begin(), v.end());
    }
    std::ranges::set_intersection(
        r0, s, std::inserter(intersection, intersection.begin()));
  }
  std::ranges::set_difference(intersection, hComp->spells,
                              std::inserter(r, r.begin()));
  return r;
}

static uint8_t swapIndex() {
  uint8_t r = 0xff;
  auto s0 = swapSpel(0);
  auto s1 = swapSpel(1);
  if (!s0.empty()) {
    r = 0;
  }
  if (!s1.empty()) {
    r = 1;
  }
  return r;
}

static void ok() {
  World::exitScrn();
  World::enterHeroTrade(Global::heroEnt, Global::goalEnt, Global::goalLevel);
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  b.func = ok;
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
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15, strPool[930]);
  return;
}

const static SDL_FRect splSlot[16] = {
    {(float)(117), (float)(90), 78, 65},  {(float)(202), (float)(90), 78, 65},
    {(float)(117), (float)(165), 78, 65}, {(float)(202), (float)(165), 78, 65},
    {(float)(117), (float)(240), 78, 65}, {(float)(202), (float)(240), 78, 65},
    {(float)(117), (float)(315), 78, 65}, {(float)(202), (float)(315), 78, 65},

    {(float)(337), (float)(90), 78, 65},  {(float)(422), (float)(90), 78, 65},
    {(float)(337), (float)(165), 78, 65}, {(float)(422), (float)(165), 78, 65},
    {(float)(337), (float)(240), 78, 65}, {(float)(422), (float)(240), 78, 65},
    {(float)(337), (float)(315), 78, 65}, {(float)(422), (float)(315), 78, 65}};

static void drawSpell() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto index = swapIndex();
  auto s = swapSpel(index);
  auto strPool = *Lang::strPool[Global::langIndex];
  uint8_t i = 0;
  for (auto spelId : s) {
    if (i >= std::size(splSlot)) {
      break;
    }
    auto texture = Global::defCache["SpellScr.def/0"][spelId];
    posRect = {splSlot[i].x + leftUp.x, splSlot[i].x + leftUp.y, 78, 65};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[709]);
    i++;
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == LearnSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool LearnSys::run() {
  drawBackGround();
  drawSpell();
  drawButton();
  return true;
}

static bool clickSpell(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto index = swapIndex();
  auto s = swapSpel(index);
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  uint8_t i = 0;
  for (auto spelId : s) {
    if (i >= std::size(splSlot)) {
      break;
    }
    posRect = {splSlot[i].x + leftUp.x, splSlot[i].x + leftUp.y, 78, 65};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      SpellSys::showSplComfirm(clickType, spelId, 0);
      return true;
    }
    i++;
  }
  return false;
}

bool LearnSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickSpell(clickType)) {
    return false;
  }
  return true;
}

bool LearnSys::rightMouseDown(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool LearnSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    ok();
    break;
  }
  default:
    break;
  }
  return true;
}