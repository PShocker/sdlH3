#include "BattleSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 800;
static float bakH = 600;

static const int BFIELD_WIDTH = 17;
static const int BFIELD_HEIGHT = 11;
static const int BFIELD_SIZE = BFIELD_WIDTH * BFIELD_HEIGHT;

// icm007.def
static void drawBackGround() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto texture = Global::pcxCache["CMBKBCH.pcx"][0];
  SDL_FRect posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
                       static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
  SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderRect(Window::renderer, &posRect);

  texture = Global::pcxCache["COPLACBR.pcx"][Global::playerId];
  posRect.y = leftUp.y + 556;
  posRect.w = texture->w;
  posRect.h = texture->h;
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  auto oName = strPool[927 + ObjectType::BUOY];

  return;
}
void BattleSys::init() {
  buttons.clear();
  {
   
  }
}
static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == BattleSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, BattleSys::buttons);
}

static SDL_FRect hexPositionLocal(uint32_t hex) {
  auto hexX = hex % BFIELD_WIDTH;
  auto hexY = hex / BFIELD_WIDTH;
  SDL_FRect r;
  r.x = 14 + ((hexY) % 2 == 0 ? 22 : 0) + 44 * hexX;
  r.y = 86 + 42 * hexY;
  r.w = 45;
  r.h = 52;
  return r;
}

static void drawCell() {
  for (int i = 0; i < BFIELD_SIZE; ++i) {
    if (i % BFIELD_WIDTH == 0)
      continue;
    if (i % BFIELD_WIDTH == BFIELD_WIDTH - 1)
      continue;
    auto r = hexPositionLocal(i);
    auto texture = Global::pcxCache["CCELLGRD.pcx"][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &r);
  }
}

bool BattleSys::run() {
  drawBackGround();
  drawButton();
  drawCell();
  return true;
}

bool BattleSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, BattleSys::buttons, clickType)) {
    return false;
  }
  return true;
}

bool BattleSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;
  return true;
}

bool BattleSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    break;
  }
  default:
    break;
  }
  return true;
}