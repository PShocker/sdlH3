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
#include <vector>

static float bakW = 800;
static float bakH = 556;

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  // b.func = receive;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 556) / 2};
  auto texture = Global::pcxCache["CMBKBCH.pcx"][0];
  SDL_FRect posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
                       static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  auto oName = strPool[927 + ObjectType::BUOY];

  return;
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == BattleSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool BattleSys::run() {
  drawBackGround();
  drawButton();
  return true;
}

bool BattleSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
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