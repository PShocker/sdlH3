#include "SeaChestSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/ArtifactComp.h"
#include "Comp/SeaChestComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static void receive() {
  auto sComp =
      World::registrys[World::level].get<SeaChestComp>(Global::goalEnt);
  Global::fadeCallBack = [sComp]() {
    World::LMouseUpSysBak.pop_back();
    World::LMouseDownSysBak.pop_back();
    World::RMouseUpSysBak.pop_back();
    World::RMouseDownSysBak.pop_back();
    World::keyUpSysBak.pop_back();
    Global::cursorBack.pop_back();

    auto &registry = World::registrys[World::level];

    auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
    heroComp.artifactsInBackpack.push_back(sComp.artifacts[0]);
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
                          strPool[926 + (uint8_t)ObjectType::SEA_CHEST]);
  return;
}

const SDL_FRect artPosition = {bakW / 2 - 22, bakH / 3, 44, 44};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &sComp =
      World::registrys[World::level].get<SeaChestComp>(Global::goalEnt);
  auto texture = Global::defCache["Artifact.def/0"][sComp.artifacts[0]];
  posRect = {leftUp.x + artPosition.x, leftUp.y + artPosition.y, artPosition.w,
             artPosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == SeaChestSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool SeaChestSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickPrim(bool leftClick) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect{leftUp.x + artPosition.x, leftUp.y + artPosition.y,
                    artPosition.w, artPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (!leftClick) {
      auto &sComp =
          World::registrys[World::level].get<SeaChestComp>(Global::goalEnt);
      HeroScrSys::showArtifactComfirm(sComp.artifacts[0]);
    }
    return true;
  }
  return false;
}

bool SeaChestSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool SeaChestSys::rightMouseDown(float x, float y) {
  if (clickPrim(false)) {
    return true;
  }
  return true;
}

bool SeaChestSys::keyUp(uint16_t key) {
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