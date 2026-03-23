#include "GarrisonSys.h"
#include "AdvMapSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "SDL3/SDL_rect.h"
#include "Window/Window.h"
#include "World/World.h"
#include <vector>

static void closeScrn() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> buttons;
  {
    Button button;
    button.textures = Global::defCache["IDV6432.DEF/0"];
    button.r = {88, 314, 64, 32};
    button.clickFunc = closeScrn;
    button.disableFunc = []() { return false; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }

  {
    Button button;
    button.textures = Global::defCache["IOK6432.DEF/0"];
    button.r = {399, 314, 64, 32};
    button.clickFunc = closeScrn;
    button.disableFunc = []() { return false; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }
  return buttons;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 549) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 396) / 2)};
  posRect = {leftUp.x, leftUp.y, 549, 396};
  auto texture = Global::pcxCache["GARRISON.PCX"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 549) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 396) / 2)};
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == GarrisonSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, buttonInfo());
}

bool GarrisonSys::run() {
  drawBackGround();
  drawButton();
  return true;
}

bool GarrisonSys::keyUp(uint16_t key) { return false; }

bool GarrisonSys::rightMouseUp(float x, float y) { return true; }

bool GarrisonSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 549) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 396) / 2)};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, buttonInfo(), clickType)) {
    return false;
  }
  return true;
}