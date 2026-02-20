#include "ScholarSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Comp/ScholarComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <utility>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static std::pair<uint8_t, uint8_t> bonuse() {
  std::pair<uint8_t, uint8_t> r = {0, 0};

  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &sComp =
      World::registrys[World::level].get<ScholarComp>(Global::goalEnt);

  if (sComp.primId.has_value()) {
    r.second = sComp.primId.value();
  } else if (sComp.secId.has_value()) {
    for (const auto &pair : heroComp.secSkills) {
      if (pair.first == sComp.secId.value()) {
        r = {0, 0};
        return r;
      }
    }
    r.first = 1;
    r.second = sComp.secId.value();
  } else {
    for (const auto &s : heroComp.spells) {
      if (s == sComp.splId.value()) {
        r = {0, 0};
        return r;
      }
    }
    r.first = 2;
    r.second = sComp.splId.value();
  }
  return r;
}

static void receive() {
  auto &sComp =
      World::registrys[World::level].get<ScholarComp>(Global::goalEnt);
  auto &registry = World::registrys[World::level];
  auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
  AdventureBonus bonus = {
      .src = ObjectType::SCHOLAR,
      .type = Enum::ADVENTURE_PRIMARY_SKILL,
      .val = 1,
  };
  bonus.subType = Enum::PRIMARY_SKILL_ATTACK;
  heroComp.adventureBonus.insert({Enum::ADVENTURE_PRIMARY_SKILL, bonus});
  World::exitScrn();
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.push_back([]() {
    auto &registry = World::registrys[World::level];
    registry.destroy(Global::goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
}

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32 - 48, bakH - 60, 64, 30};
  b.func = receive;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ICANCEL.DEF/0"];
  b.r = {bakW / 2 - 32 + 48, bakH - 60, 64, 30};
  b.func = close;
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
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15,
                          strPool[927 + (uint8_t)ObjectType::SCHOLAR]);
  FreeTypeSys::setColor(255, 255, 255, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 40,
                          strPool[697]);
  return;
}

const SDL_FRect sPosition = {bakW / 2 - 41, bakH / 3, 82, 93};
const SDL_FRect splPosition = {bakW / 2 - 29, bakH / 3, 58, 64};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto sComp = World::registrys[World::level].get<ScholarComp>(Global::goalEnt);
  SDL_Texture *texture;
  auto r = bonuse();
  switch (r.first) {
  case 0: {
    texture = Global::defCache["PSKILL.def/0"][r.second];
    posRect = {leftUp.x + sPosition.x, leftUp.y + sPosition.y, sPosition.w,
               sPosition.h};
    break;
  }
  case 1: {
    texture = Global::defCache["SECSK82.def/0"][r.second];
    posRect = {leftUp.x + sPosition.x, leftUp.y + sPosition.y, sPosition.w,
               sPosition.h};
    break;
  }
  case 2: {
    texture = Global::defCache["SpellBon.def/0"][r.second];
    posRect = {leftUp.x + splPosition.x, leftUp.y + splPosition.y,
               splPosition.w, splPosition.h};
    break;
  }
  }
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == ScholarSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool ScholarSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickBonuse(uint8_t clickType) {
  SDL_FRect pRect;
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto r = bonuse();
  switch (r.first) {
  case 0:
  case 1: {
    pRect = sPosition;
    break;
  }
  case 2: {
    pRect = splPosition;
    break;
  }
  }
  posRect = {leftUp.x + pRect.x, leftUp.y + pRect.y, pRect.w, pRect.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {

    return true;
  }
  return false;
}

bool ScholarSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool ScholarSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickBonuse(clickType)) {
    return true;
  }
  return true;
}

bool ScholarSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    close();
    break;
  }
  default:
    break;
  }
  return true;
}