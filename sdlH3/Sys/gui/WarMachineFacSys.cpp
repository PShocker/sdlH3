#include "WarMachineFacSys.h"

#include "Comp/WarMachineFacComp.h"
#include "DwellingSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Set/CreatureSet.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/base/SliderSys.h"
#include "WarMachineSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

static void toMax() { Global::dweSliderNum = WarMachineFacSys::maxCount(); }

static void close() { World::exitScrn(); }

static void buy() {
  auto &registry = World::registrys[World::level];
  // 判断英雄身上是否可以放下这个生物
  World::enterConfirm(100, 100, ((uint8_t)Enum::SCNTYPE::MOD));
}

uint32_t WarMachineFacSys::maxCount() {
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto mId = wComp->warMachines[Global::dweIndex].first;
  auto cost = CreatureSet::fullCreatures[mId]->cost;
  uint32_t maxCount = UINT32_MAX;
  for (uint8_t i = 0; i < cost.size(); i++) {
    auto r = Global::resources[Global::playerId][i];
    if (cost[i] == 0) {
      continue;
    }
    maxCount = std::min(r / cost[i], maxCount);
  }
  auto count = wComp->warMachines[Global::dweIndex].second;
  return std::min(maxCount, count);
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["IRCBTNS.DEF/0"];
  b.r = {134, 313, 64, 32};
  b.func = toMax;
  if (WarMachineFacSys::maxCount() == 0) {
    b.disable = true;
  } else {
    b.disable = false;
  }
  v.push_back(b);

  b.textures = Global::defCache["IBY6432.DEF/0"];
  b.r = {212, 313, 64, 32};
  b.func = buy;
  if (Global::dweSliderNum == 0) {
    b.disable = true;
  } else {
    b.disable = false;
  }
  v.push_back(b);

  b.textures = Global::defCache["ICANCEL.DEF/0"];
  b.r = {290, 313, 64, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

bool WarMachineFacSys::run() {

  // warAnimate();
  // drawBackGround();
  // drawWarMachines();
  // drawCost();
  // drawButton();
  // drawSlider();
  return true;
}

bool WarMachineFacSys::keyUp(uint16_t key) { return false; }

static bool clickSlider() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto count = WarMachineFacSys::maxCount();
  if (auto num = SliderSys::clickHor(leftUp.x + 176, leftUp.y + 279, 135,
                                     Global::dweSliderNum, count);
      num != Global::dweSliderNum) {
    Global::dweSliderNum = num;
    return true;
  }
  return false;
}

static bool clickMachine(uint8_t clickType) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  int size = wComp->warMachines.size();
  // 100x120
  auto pos = DwellingSys::creatruePos(size);

  for (uint8_t i = 0; i < size; i++) {
    auto p = pos[i];
    posRect = {leftUp.x + p.x, leftUp.y + p.y, 100, 130};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      uint8_t creType;
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        if (Global::dweIndex == i) {
          creType = (uint8_t)Enum::CRETYPE::MOD_DWE;
          World::enterWarMachine(wComp->warMachines[i], creType);
        }
        Global::dweIndex = i;
      } else {
        creType = (uint8_t)Enum::CRETYPE::POP_DWE;
        World::enterWarMachine(wComp->warMachines[i], creType);
      }
      return false;
    }
  }
  return false;
}
bool WarMachineFacSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  // click slider
  if (clickSlider()) {
    return false;
  }
  if (clickMachine(clickType)) {
    return false;
  }
  return true;
}

bool WarMachineFacSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickMachine(clickType)) {
    return false;
  }
  return true;
}