#include "ArtifactSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/ArtifactComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 500;
static float bakH = 340;

static void receive() {
  auto afComp =
      World::registrys[World::level].get<ArtifactComp>(Global::goalEnt);
  World::exitScrn();

  World::iterateSystems.pop_back();
  World::iterateSystems.pop_back();
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystemsBak.back().push_back(CursorSys::run);
  World::iterateSystems.push_back([afComp]() {
    auto &registry = World::registrys[World::level];
    registry.destroy(Global::goalEnt);
    World::needSort = true;

    auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
    heroComp.artifactsInBackpack.push_back(afComp.id);
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
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15, strPool[930]);
  return;
}

const SDL_FRect artPosition = {bakW / 2 - 22, bakH / 3, 44, 44};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &afComp =
      World::registrys[World::level].get<ArtifactComp>(Global::goalEnt);
  auto texture = Global::defCache["Artifact.def/0"][afComp.id];
  posRect = {leftUp.x + artPosition.x, leftUp.y + artPosition.y, artPosition.w,
             artPosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);

  auto strPool = *Lang::strPool[Global::langIndex];

  FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40,
                          strPool[450 + afComp.id]);

  FreeTypeSys::setColor(240, 224, 104, 255);

  FreeTypeSys::drawCenter(leftUp.x + bakW / 2, posRect.y + 50,
                          strPool[162 + afComp.id]);

  FreeTypeSys::setColor(255, 255, 255, 255);
  FreeTypeSys::drawCenter(leftUp.x + bakW / 2, posRect.y + 75,
                          strPool[306 + afComp.id]);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == ArtifactSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool ArtifactSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickArt(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + artPosition.x, leftUp.y + artPosition.y, artPosition.w,
             artPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto &afComp =
        World::registrys[World::level].get<ArtifactComp>(Global::goalEnt);
    HeroScrSys::showArtifactComfirm(afComp.id);
    return true;
  }
  return false;
}

bool ArtifactSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool ArtifactSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickArt(clickType)) {
    return false;
  }
  return true;
}

bool ArtifactSys::keyUp(uint16_t key) {
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