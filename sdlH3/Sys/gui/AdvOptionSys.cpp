#include "AdvOptionSys.h"
#include "AdvMapSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "Window/Window.h"
#include "World/World.h"
#include <vector>

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["ADVVIEW.DEF/0"];
  b.r = {24, 23, 49, 51};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ADVVIEW.DEF/0"];
  b.r = {24, 23, 49, 51};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ADVPUZ.DEF/0"];
  b.r = {24, 81, 49, 51};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ADVDIG.DEF/0"];
  b.r = {24, 139, 49, 51};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ADVINFO.DEF/0"];
  b.r = {24, 198, 49, 51};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ADVTURN.DEF/0"];
  b.r = {24, 257, 49, 51};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["IOK6432.DEF/0"];
  b.r = {203, 313, 64, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 289) / 2,
                    (Global::viewPort.h - 387) / 2};
  auto texture = Global::pcxCache["ADVOPTS.pcx"][Global::playerId];
  posRect = {static_cast<float>((int)leftUp.x),
             static_cast<float>((int)leftUp.y), static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 289) / 2,
                    (Global::viewPort.h - 387) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == AdvOptionSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool AdvOptionSys::run() {
  drawBackGround();
  drawButton();
  return true;
}

bool AdvOptionSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 289) / 2,
                    (Global::viewPort.h - 387) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool AdvOptionSys::keyUp(uint16_t key) {
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