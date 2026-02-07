#include "TownBuildSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/TempleComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"

static float bakW = 450;
static float bakH = 340;

static void close() { World::exitScrn(); }

static void buy() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  b.func = buy;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 521) / 2};
  auto texture = Global::pcxCache["TPUBUILD.pcx"][Global::playerId];
  posRect = {leftUp.x, leftUp.y, 395, 521};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  //   auto strPool = *Lang::strPool[Global::langIndex];
  //   FreeTypeSys::setSize(13);
  //   FreeTypeSys::setColor(240, 224, 104, 255);
  //   FreeTypeSys::drawCenter(x, y - bakH / 2 + 15,
  //                           strPool[926 +
  //                           (uint8_t)ObjectType::TREASURE_CHEST]);

  return;
}

static void drawBuild() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto texture = Global::defCache["imrl82.def/0"][4];
  //   posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y,
  //   morPosition.w,
  //              morPosition.h};
  //   SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  //   SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  //   SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TownBuildSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool TownBuildSys::run() {
  drawBackGround();
  drawBuild();
  drawButton();
  return true;
}

bool TownBuildSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool TownBuildSys::keyUp(uint16_t key) {
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