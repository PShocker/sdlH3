#include "ViewWorldSys.h"
// VWorld.pcx
#include "AdvMapSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/RenderSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>

static void receive() {}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  // b.textures = Global::defCache["iOKAY.def/0"];
  // b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  // b.func = receive;
  // b.disable = false;
  // v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FPoint leftUp{Global::viewPort.w - 190, Global::viewPort.h - 381};
  auto texture = Global::pcxCache["VWorld.pcx"][0];
  SDL_FRect posRect = {Global::viewPort.w - 192, 194, 190, 381};
  SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
  return;
}

static void draw() {
  auto viewPort = Global::viewPort;
  auto scale = Global::viewWorldScale;
  auto centerX = Global::viewPort.x + Global::viewPort.w / 2;
  auto centerY = Global::viewPort.y + Global::viewPort.h / 2;
  Global::viewPort.w = Global::viewPort.w * scale;
  Global::viewPort.h = Global::viewPort.h * scale;
  Global::viewPort.x = centerX - Global::viewPort.w / 2;
  Global::viewPort.y = centerY - Global::viewPort.h / 2;
  auto texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_UNKNOWN,
                                   SDL_TEXTUREACCESS_TARGET, Global::viewPort.w,
                                   Global::viewPort.h);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(Window::renderer, texture);
  // render
  RenderSys::run();
  SDL_SetRenderTarget(Window::renderer, nullptr);
  SDL_FRect posRect = {0, 0, viewPort.w, viewPort.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  SDL_DestroyTexture(texture);
  Global::viewPort = viewPort;
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w - 190, Global::viewPort.h - 381};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == ViewWorldSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool ViewWorldSys::run() {
  drawBackGround();
  draw();
  // drawButton();
  return true;
}

bool ViewWorldSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w - 190, Global::viewPort.h - 381};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool ViewWorldSys::rightMouseDown(float x, float y) { return true; }

bool ViewWorldSys::keyUp(uint16_t key) {
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