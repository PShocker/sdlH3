#include "SirensSys.h"
#include "AdvPopSys.h"

#include "Comp/SirensComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "Set/CreatureSet.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/LevelUpSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  if (heroComp.visited.contains((uint8_t)ObjectType::SIRENS)) {
    return true;
  }
  return false;
}
// 塞壬海妖
static void receive() {
  World::exitScrn();
  if (visited()) {
    return;
  }
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  uint32_t exp = 0;
  auto &sComp = World::registrys[World::level].get<SirensComp>(Global::goalEnt);
  for (auto &pair : heroComp.creatures) {
    if (pair.second > 0 && pair.second * 0.7 > 0) {
      auto creatureId = pair.first;
      auto num = pair.second;
      auto creExp = CreatureSet::fullCreatures[creatureId]->experience;
      exp += creExp * pair.second * 0.3;
      pair.second = pair.second * 0.7;
    }
  }
  heroComp.exp += exp;
  if (LevelUpSys::prepareLvlUp(heroComp)) {
    World::enterLvlup(Global::heroEnt);
  }
  heroComp.visited.insert((uint8_t)ObjectType::SIRENS);
  sComp.visitHeros.insert(heroComp.portrait);
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
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::SIRENS]);
  return;
}

const SDL_FRect primPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  if (visited()) {

  } else {
    auto texture = Global::defCache["PSKILL.def/0"][4];
    posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
               primPosition.w, primPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == SirensSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool SirensSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickExp(uint8_t clickType) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect{leftUp.x + primPosition.x, leftUp.y + primPosition.y,
                    primPosition.w, primPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    HeroScrSys::showExpComfirm(clickType);
    return true;
  }
  return false;
}

bool SirensSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool SirensSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickExp(clickType)) {
    return true;
  }
  return true;
}

bool SirensSys::keyUp(uint16_t key) {
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
