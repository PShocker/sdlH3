#include "CartographerSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
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

static void close() { World::exitScrn(); }

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
  close();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;
  auto &gold = Global::resources[Global::playerId][6];

  if (gold < 1000 || !need()) {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    b.func = close;
    b.disable = false;
    v.push_back(b);
  } else {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32 - 48, bakH - 60, 64, 30};
    b.func = buy;
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

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  FreeTypeSys::setSize(13);

  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15, strPool[937]);

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
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == CartographerSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool CartographerSys::run() {
  drawBackGround();
  drawButton();

  return true;
}

bool CartographerSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool CartographerSys::keyUp(uint16_t key) {
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