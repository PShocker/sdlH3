#include "PandoraSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/PandorBoxComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Sys/gui/LevelUpSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static const float bakW = 450;
static const float bakH = 340;

enum PANDORA_TYPE {
  PANDORA_MESSAGE,
  PANDORA_CREATURE,
  PANDORA_EXP,
  PANDORA_MANA,
  PANDORA_MORALE,
  PANDORA_LUCK,
  PANDORA_RESOURCE,
  PANDORA_PRIMARY,
  PANDORA_SECSKILL,
  PANDORA_ARTIFACT,
  PANDORA_SPELL,
};

static uint8_t curReward() {
  auto pComp =
      World::registrys[World::level].get<PandorBoxComp>(Global::goalEnt);
  if (pComp.message != "") {
    return PANDORA_MESSAGE;
  }
  if (!pComp.creatures.empty()) {
    return PANDORA_CREATURE;
  }
  if (pComp.heroExperience != 0) {
    return PANDORA_EXP;
  }
  if (pComp.manaDiff != 0) {
    return PANDORA_MANA;
  }
  if (pComp.morale != 0) {
    return PANDORA_MORALE;
  }
  if (pComp.luck != 0) {
    return PANDORA_LUCK;
  }
  for (auto r : pComp.resources) {
    if (r != 0) {
      return PANDORA_RESOURCE;
    }
  }
  for (auto r : pComp.primary) {
    if (r != 0) {
      return PANDORA_PRIMARY;
    }
  }
  if (!pComp.secSkills.empty()) {
    return PANDORA_SECSKILL;
  }
  if (!pComp.spells.empty()) {
    return PANDORA_SPELL;
  }

  return 0xff;
}

static void receive() {
  auto type = curReward();
  Global::fadeCallBack = [type]() {
    World::LMouseUpSysBak.pop_back();
    World::LMouseDownSysBak.pop_back();
    World::RMouseUpSysBak.pop_back();
    World::RMouseDownSysBak.pop_back();
    World::keyUpSysBak.pop_back();
    Global::cursorBack.pop_back();

    auto &registry = World::registrys[World::level];
    if (type == PANDORA_EXP) {
      auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
      heroComp.exp += 1000;
      if (LevelUpSys::prepareLvlUp(heroComp)) {
        World::exitScrn();
        World::enterLvlup(Global::heroEnt);
        World::enterLvlup(Global::heroEnt);
      }
    }
    return true;
  };
  World::iterateSystems.pop_back();
  World::iterateSystems.pop_back();
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystemsBak.back().push_back(CursorSys::run);
  World::iterateSystems.push_back([]() {
    auto &registry = World::registrys[World::level];
    registry.destroy(Global::goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
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
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2,
                          strPool[926 + (uint8_t)ObjectType::PANDORAS_BOX]);
  return;
}

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto type = curReward();
  switch (type) {
  case PANDORA_MESSAGE: {
    break;
  }
  case PANDORA_CREATURE: {
    break;
  }
  case PANDORA_EXP: {
    auto texture = Global::defCache["PSKILL.def/0"][4];
    posRect = {leftUp.x + bakW / 2 - 41, leftUp.y + 145, 82, 93};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
    break;
  }
  case PANDORA_MANA: {
    break;
  }
  case PANDORA_MORALE: {
    break;
  }
  case PANDORA_LUCK: {
    break;
  }
  case PANDORA_RESOURCE: {
    break;
  }
  case PANDORA_PRIMARY: {
    break;
  }
  case PANDORA_SECSKILL: {
    break;
  }
  case PANDORA_SPELL: {
    break;
  }
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == PandoraSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool PandoraSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

bool PandoraSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool PandoraSys::keyUp(uint16_t key) {
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