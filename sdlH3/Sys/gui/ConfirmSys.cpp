#include "ConfirmSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;

  auto bakW = Global::confirmBakW;
  auto bakH = Global::confirmBakH;
  if (bakW > 0 && bakH > 0) {
    AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);
  }
}

static void close() { World::exitScrn(); }

static void ok() {
  if (Global::confirmCallBack.has_value()) {
    Global::confirmCallBack.value()();
  } else {
    close();
  }
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;

  auto bakW = Global::confirmBakW;
  auto bakH = Global::confirmBakH;

  Button b;

  if (Global::confirmOnlyOK) {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    b.func = ok;
    b.disable = false;
    v.push_back(b);

  } else {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32 - 48, bakH - 60, 64, 30};
    b.func = ok;
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

static void drawButton() {
  if (Global::confirmType == (uint8_t)Enum::SCNTYPE::MOD) {

    auto bakW = Global::confirmBakW;
    auto bakH = Global::confirmBakH;

    SDL_FRect posRect;
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    auto v = buttonInfo();
    AdvMapSys::drawButtons(leftUp.x, leftUp.y, true, v);
  }
}

static void draw() { Global::confirmdraw(); }

bool ConfirmSys::run() {
  drawBackGround();
  drawButton();
  draw();
  return true;
}

bool ConfirmSys::leftMouseUp(float x, float y) {
  if (Global::confirmType == (uint8_t)Enum::SCNTYPE::MOD) {
    auto bakW = Global::confirmBakW;
    auto bakH = Global::confirmBakH;
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    auto v = buttonInfo();
    auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

    if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
      return false;
    }
  }
  return true;
}
bool ConfirmSys::keyUp(uint16_t key) {
  if (Global::confirmType == (uint8_t)Enum::SCNTYPE::MOD) {
    switch (key) {
    case SDL_SCANCODE_ESCAPE: {
      close();
      break;
    }
    default:
      break;
    }
  }
  return true;
}

bool ConfirmSys::rightMouseUp(float x, float y) {
  if (Global::confirmType == (uint8_t)Enum::SCNTYPE::POP) {
    World::iterateSystems.push_back([]() -> bool {
      World::exitScrn();
      return false;
    });
  }
  return false;
}