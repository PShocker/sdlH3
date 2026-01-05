#include "KnoTreeSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Cfg/HeroCfg.h"
#include "Comp/HeroComp.h"
#include "Comp/KnoTreeComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/LevelUpSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <vector>

static float bakW = 480;
static float bakH = 300;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &kComp =
      World::registrys[World::level].get<KnoTreeComp>(Global::goalEnt);
  if (kComp.visitHeros.contains(heroComp.portrait)) {
    return true;
  } else {
    return false;
  }
}

static uint32_t maxCount() {
  auto &registry = World::registrys[World::level];
  auto &kComp = registry.get<KnoTreeComp>(Global::goalEnt);
  uint32_t maxCount = UINT32_MAX;
  auto resources = Global::resources[Global::playerId];
  for (uint8_t i = 0; i < kComp.resources.size(); i++) {
    auto r = kComp.resources[i];
    if (r.second == 0) {
      continue;
    }
    maxCount = std::min(resources[r.first] / r.second, maxCount);
  }
  return maxCount;
}

static void receive() {
  World::exitScrn();
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto exp = HeroCfg::heroLevelExp[heroComp.level] -
             HeroCfg::heroLevelExp[heroComp.level - 1];
  heroComp.exp += exp;
  if (LevelUpSys::prepareLvlUp(heroComp)) {
    World::enterLvlup(Global::heroEnt);
  }
}

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  if (maxCount() == 0 || visited()) {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    b.func = close;
    b.disable = false;
    v.push_back(b);

  } else {
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
  }

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(
      Global::viewPort.w / 2, y - bakH / 2 + 15,
      strPool[926 + (uint8_t)ObjectType::TREE_OF_KNOWLEDGE]);

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
  std::u16string s;
  if (!visited()) {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 3, leftUp.y + 40, s);

    auto texture = Global::defCache["PSKILL.def/0"][4];
    posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
               primPosition.w, primPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);

    auto &heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    auto exp = HeroCfg::heroLevelExp[heroComp.level] -
               HeroCfg::heroLevelExp[heroComp.level - 1];
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2,
                            posRect.y + posRect.h + 4,
                            u"+" + FreeTypeSys::str(exp) + u" " + strPool[10]);
  } else {
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == KnoTreeSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool KnoTreeSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickExp(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
             primPosition.w, primPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (leftClick) {
      HeroScrSys::showExpComfirm(leftClick);
    }
    return true;
  }
  return false;
}

bool KnoTreeSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool KnoTreeSys::rightMouseDown(float x, float y) {
  if (clickExp(false)) {
    return true;
  }
  return true;
}

bool KnoTreeSys::keyUp(uint16_t key) {
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