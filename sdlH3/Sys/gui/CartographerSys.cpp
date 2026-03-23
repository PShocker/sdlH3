#include "CartographerSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 480;
static float bakH = 200;

static bool need() {
  auto playerId = Global::playerId;
  auto fogs = Global::fogs[playerId][World::level];
  auto land = Global::landBlock[World::level];
  bool need = false;
  for (auto i = 0; i < fogs.size(); i++) {
    if (fogs[i] == false) {
      if (land.contains(i)) {
        need = true;
        break;
      }
    }
  }
  return need;
}

static void closeScrn() { World::exitScrn(); }

static void buy() {
  auto &gold = Global::resources[Global::playerId][6];
  if (gold >= 1000) {
    auto land = Global::landBlock[World::level];
    auto playerId = Global::playerId;
    auto &fogs = Global::fogs[playerId][World::level];
    for (auto i : land) {
      fogs[i] = true;
    }
    gold -= 1000;
  }
  closeScrn();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> buttons;
  {
    Button button;
    button.textures = Global::defCache["iOKAY.def/0"];
    button.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    button.clickFunc = closeScrn;
    button.disableFunc = []() { return false; };
    button.showFunc = []() {
      auto &gold = Global::resources[Global::playerId][6];
      if (gold < 1000 || !need()) {
        return true;
      }
      return false;
    };
    buttons.push_back(button);
  }

  {
    Button button;
    button.textures = Global::defCache["iOKAY.def/0"];
    button.r = {bakW / 2 - 32 - 48, bakH - 60, 64, 30};
    button.clickFunc = buy;
    button.disableFunc = []() { return false; };
    button.showFunc = []() {
      auto &gold = Global::resources[Global::playerId][6];
      if (gold < 1000 || !need()) {
        return false;
      }
      return true;
    };
    buttons.push_back(button);
  }
  {
    Button button;
    button.textures = Global::defCache["ICANCEL.DEF/0"];
    button.r = {bakW / 2 - 32 + 48, bakH - 60, 64, 30};
    button.clickFunc = closeScrn;
    button.disableFunc = []() { return false; };
    button.showFunc = []() {
      auto &gold = Global::resources[Global::playerId][6];
      if (gold < 1000 || !need()) {
        return false;
      }
      return true;
    };
    buttons.push_back(button);
  }
  return buttons;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  FreeTypeSys::setSize(13);

  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  auto oName = strPool[927 + ObjectType::CARTOGRAPHER];
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15, oName);

  FreeTypeSys::setColor(255, 255, 255, 255);
  auto gold = Global::resources[Global::playerId][6];
  std::u16string s;
  if (gold < 1000) {
    s = strPool[618];
  } else if (need()) {
    s = strPool[616];
  } else {
    s = strPool[615];
  }
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 40, s);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == CartographerSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, buttonInfo());
}

bool CartographerSys::run() {
  drawBackGround();
  drawButton();

  return true;
}

bool CartographerSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, buttonInfo(),
                              clickType)) {
    return false;
  }
  return true;
}

bool CartographerSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    closeScrn();
    break;
  }
  default:
    break;
  }
  return true;
}