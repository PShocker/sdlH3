#include "ShrineMagicSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/ShrineMagicComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SpellSys.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 480;
static float bakH = 300;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  // 判断是否有魔法书
  if (heroComp.artifacts[17] == 0xffff) {
    return true;
  }
  auto &smComp =
      World::registrys[World::level].get<ShrineMagicComp>(Global::goalEnt);
  // 获取智慧术等级
  int8_t wisdom = -1;
  for (auto secPair : heroComp.secSkills) {
    if (secPair.first == 7) {
      wisdom = secPair.second;
    }
  }
  if (smComp.level >= 2 && wisdom < 0) {
    return true;
  }
  return false;
}

static void receive() {
  World::exitScrn();
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &smComp =
      World::registrys[World::level].get<ShrineMagicComp>(Global::goalEnt);
  if (!visited()) {
    heroComp.spells.insert(smComp.spellId);
  }
  heroComp.visited.insert((uint8_t)ObjectType::SHRINE_OF_MAGIC_GESTURE);
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
  auto &sComp =
      World::registrys[World::level].get<ShrineMagicComp>(Global::goalEnt);
  FreeTypeSys::drawCenter(
      Global::viewPort.w / 2, y - bakH / 2 + 15,
      strPool[927 + (uint8_t)ObjectType::SHRINE_OF_MAGIC_INCANTATION +
              sComp.level]);

  return;
}

const SDL_FRect splPosition = {bakW / 2 - 41, bakH / 3, 83, 61};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  if (!visited()) {
    auto &sComp =
        World::registrys[World::level].get<ShrineMagicComp>(Global::goalEnt);
    auto texture = Global::defCache["SpellScr.def/0"][sComp.spellId];
    posRect = {leftUp.x + splPosition.x, leftUp.y + splPosition.y,
               splPosition.w, splPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40,
                            strPool[709 + sComp.level]);
  } else if (heroComp.artifacts[17] == 0xffff) {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[692]);
  } else {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[712]);
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == ShrineMagicSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool ShrineMagicSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickSpl(bool leftClick) {
  if (!visited()) {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    SDL_FRect posRect{leftUp.x + splPosition.x, leftUp.y + splPosition.y,
                      splPosition.w, splPosition.h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      auto &sComp =
          World::registrys[World::level].get<ShrineMagicComp>(Global::goalEnt);
      SpellSys::showSplComfirm(leftClick, sComp.spellId, 0);
      return true;
    }
  }
  return false;
}

bool ShrineMagicSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  if (clickSpl(true)) {
    return true;
  }
  return true;
}

bool ShrineMagicSys::rightMouseDown(float x, float y) {
  if (clickSpl(false)) {
    return true;
  }
  return true;
}

bool ShrineMagicSys::keyUp(uint16_t key) {
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