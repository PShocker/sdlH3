#include "LearnStoneSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/LearnStoneComp.h"
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
#include <vector>

static float bakW = 450;
static float bakH = 340;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &lComp =
      World::registrys[World::level].get<LearnStoneComp>(Global::goalEnt);
  if (lComp.visitHeros.contains(heroComp.portrait)) {
    return true;
  } else {
    return false;
  }
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
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::LEARNING_STONE]);

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
  if (!visited()) {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[721]);

    auto texture = Global::defCache["PSKILL.def/0"][4];
    posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
               primPosition.w, primPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2,
                            posRect.y + posRect.h + 4, u"+1000 " + strPool[10]);

  } else {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[722]);
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == LearnStoneSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool LearnStoneSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickExp(uint8_t clickType) {
  if (!visited()) {
    SDL_FRect posRect;
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
               primPosition.w, primPosition.h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showExpComfirm(clickType);
      return true;
    }
  }
  return false;
}

bool LearnStoneSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool LearnStoneSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickExp(clickType)) {
    return true;
  }
  return true;
}

bool LearnStoneSys::keyUp(uint16_t key) {
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
