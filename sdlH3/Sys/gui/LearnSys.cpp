#include "LearnSys.h"
#include "AdvMapSys.h"
#include "Cfg/SpellCfg.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SpellSys.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvPopSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <cstdlib>

static float bakW = 480;
static float bakH = 300;

static std::vector<uint8_t> learnSpells() {
  auto level0 = World::level;
  auto level1 = Global::goalLevel;
  auto hComp0 = &World::registrys[level0].get<HeroComp>(Global::heroEnt);
  auto hComp1 = &World::registrys[level1].get<HeroComp>(Global::goalEnt);
  int8_t learnLevel = -1;
  // 判断有没有学术
  for (auto v2 : {hComp0->secSkills, hComp1->secSkills}) {
    for (auto v1 : v2) {
      if (v1.first == 21) {
        learnLevel = std::max(learnLevel, (int8_t)v1.second);
      }
    }
  }
  auto studyLevel = learnLevel + 2;
  std::vector<uint8_t> r0;
  std::vector<uint8_t> r1;
  for (uint8_t i = 0; i <= studyLevel; i++) {
    auto v = SpellCfg::SpellLevels[i];
    std::ranges::sort(v);
    std::ranges::set_intersection(hComp0->spells, v, std::back_inserter(r0));
  }
  for (uint8_t i = 0; i <= studyLevel; i++) {
    auto v = SpellCfg::SpellLevels[i];
    std::ranges::sort(v);
    std::ranges::set_intersection(hComp1->spells, v, std::back_inserter(r1));
  }
  std::vector<uint8_t> result;
  if (Global::goalIndex == 0) {
    std::ranges::set_difference(r0, r1, std::back_inserter(result));
  } else {
    std::ranges::set_difference(r1, r0, std::back_inserter(result));
  }
  return result;
}

static uint8_t learnIndex() {
  uint8_t r = 0;
  auto n = Global::goalIndex;
  Global::goalIndex = 0;
  auto v0 = learnSpells();
  Global::goalIndex = 1;
  auto v1 = learnSpells();

  return 0xff;
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
  auto v = learnSpells();
  auto strPool = *Lang::strPool[Global::langIndex];
  for (uint8_t i = 0; i < 8; i++) {
    if (i < v.size()) {
      auto texture = Global::defCache["SpellScr.def/0"][v[i]];
      posRect = {splSlot[i].x + leftUp.x, splSlot[i].x + leftUp.y, 78, 65};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[709]);
    }
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
  auto v = learnSpells();
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < 8; i++) {
    if (i < v.size()) {
      posRect = {splSlot[i].x + leftUp.x, splSlot[i].x + leftUp.y, 78, 65};
      if (SDL_PointInRectFloat(&point, &posRect)) {
        SpellSys::showSplComfirm(clickType, v[i], 0);
        return true;
      }
    }
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
  if (clickSpell(true)) {
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