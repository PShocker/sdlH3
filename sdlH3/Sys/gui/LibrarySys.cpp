#include "LibrarySys.h"
#include "AdvPopSys.h"
#include "Comp/LibraryComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 600;
static float bakH = 340;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &lComp =
      World::registrys[World::level].get<LibraryComp>(Global::goalEnt);
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
  auto &lComp =
      World::registrys[World::level].get<LibraryComp>(Global::goalEnt);
  if (!lComp.visitHeros.contains(heroComp.portrait) && heroComp.level >= 10) {
    heroComp.primSkills[0] += 5;
    heroComp.primSkills[1] += 5;
    heroComp.primSkills[2] += 5;
    heroComp.primSkills[3] += 5;
    heroComp.visitedEnt.insert(Global::goalEnt);
  }
  lComp.visitHeros.insert(heroComp.portrait);
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
  FreeTypeSys::drawCenter(
      Global::viewPort.w / 2, y - bakH / 2 + 15,
      strPool[926 + (uint8_t)ObjectType::LIBRARY_OF_ENLIGHTENMENT]);
  return;
}

const auto totalWidth = 4 * 82;
const auto padding = (bakW - totalWidth) / (5);

const static std::vector<SDL_FRect> primPosition = {
    {padding * (1) + 0 * 82, bakH / 3, 82, 93},
    {padding * (2) + 1 * 82, bakH / 3, 82, 93},
    {padding * (3) + 2 * 82, bakH / 3, 82, 93},
    {padding * (4) + 3 * 82, bakH / 3, 82, 93},
};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};

  const auto totalWidth = 4 * 82;
  auto padding = (bakW - totalWidth) / (5);
  auto textures = Global::defCache["PSKILL.def/0"];
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  FreeTypeSys::setSize(12);
  FreeTypeSys::setColor(255, 255, 255, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  if (heroComp.level < 10) {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[653]);
  } else if (visited()) {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[652]);
  } else {
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[651]);
    for (auto i = 0; i < 4; i++) {
      auto texture = textures[i];
      SDL_FRect pRect{leftUp.x + primPosition[i].x,
                      leftUp.y + primPosition[i].y, primPosition[i].w,
                      primPosition[i].h};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &pRect);
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &pRect);
      FreeTypeSys::drawCenter(pRect.x + pRect.w / 2, pRect.y + pRect.h + 4,
                              u"+5 " + strPool[1 + i]);
    }
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == LibrarySys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool LibrarySys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickPrim(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < primPosition.size(); i++) {
    posRect = primPosition[i];
    posRect.x += leftUp.x;
    posRect.y += leftUp.y;
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showPrimComfirm(clickType, i);
      return true;
    }
  }
  return false;
}

bool LibrarySys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool LibrarySys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickPrim(clickType)) {
    return true;
  }
  return true;
}

bool LibrarySys::keyUp(uint16_t key) {
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