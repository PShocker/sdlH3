#include "WarMachineFacSys.h"
#include "Cfg/WarMachineCfg.h"
#include "Comp/WarMachineFacComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/base/SliderSys.h"
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

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  posRect = {leftUp.x, leftUp.y, 485, 395};
  auto texture = Global::pcxCache["TPrcrt.pcx"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  auto strPool = *Lang::strPool[Global::langIndex];

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  posRect = {leftUp.x + 172, leftUp.y + 222, 67, 42};
  SDL_RenderRect(Window::renderer, &posRect);
  FreeTypeSys::drawCenter(posRect.x + 34, posRect.y + 2, strPool[1859]);
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto count = wComp->warMachines[Global::dweIndex].second;
  FreeTypeSys::drawCenter(posRect.x + 34, posRect.y + 24, count);
  posRect = {leftUp.x + 246, leftUp.y + 222, 67, 42};
  SDL_RenderRect(Window::renderer, &posRect);
  FreeTypeSys::drawCenter(posRect.x + 34, posRect.y + 2, strPool[1857]);
  FreeTypeSys::drawCenter(posRect.x + 34, posRect.y + 24, Global::dweSliderNum);

  posRect = {leftUp.x + 64, leftUp.y + 222, 99, 76};
  SDL_RenderRect(Window::renderer, &posRect);
  FreeTypeSys::drawCenter(posRect.x + 50, posRect.y + 2, strPool[1858]);
  posRect = {leftUp.x + 322, leftUp.y + 222, 99, 76};
  SDL_RenderRect(Window::renderer, &posRect);
  FreeTypeSys::drawCenter(posRect.x + 50, posRect.y + 2, strPool[1860]);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(
      Global::viewPort.w / 2, posRect.y + 15,
      strPool[926 + (uint8_t)ObjectType::WAR_MACHINE_FACTORY]);
}

static void drawWarMachine() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto wComp =
      World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto mhs = wComp.warMachines;
  int size = mhs.size();
  // 100x120
  int per = (485 - size * 100) / (size + 1);
  for (uint8_t i = 0; i < size; i++) {
    auto x = leftUp.x + per * (i + 1) + i * 100;
    auto y = leftUp.y + 60;
    auto group = 2;
    auto id = mhs[i].first;
    auto defPath = WarMachineCfg::warMachineGraphics.at(id);
    auto textures = Global::defCache[defPath + "/" + std::to_string(group)];
    auto index = Global::dweFrameIndex % textures.size();
    auto colorType = Global::dweIndex == i ? 1 : 0;
    WarMachineFacSys::drawMachine(x, y, id, group, index, colorType);
  }
}

void WarMachineFacSys::drawMachine(float x, float y, uint16_t id,
                                   uint16_t group, uint16_t index,
                                   uint8_t colorType) {

  SDL_FRect posRect{x, y, 100, 130};

  auto texture = Global::pcxCache["TPCASNEU.pcx"][0];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  if (colorType == 1) {
    SDL_SetRenderDrawColor(Window::renderer, 255, 0, 0, 255);
  } else {
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  }
  SDL_RenderRect(Window::renderer, &posRect);
  auto defPath = WarMachineCfg::warMachineGraphics.at(id);
  auto textures = Global::defCache[defPath + "/" + std::to_string(group)];
  texture = textures[index];
  SDL_FRect srcRect;
  if (WarMachineCfg::machinedoubleWide[id]) {
    srcRect = {165, 145, 100, 130};
  } else {
    srcRect = {145, 145, 100, 130};
  }
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == WarMachineFacSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void dweAnimate() {
  Global::dweFrameTime += Window::deltaTime;
  if (Global::dweFrameTime >= 90) {
    Global::dweFrameTime = 0;
    Global::dweFrameIndex += 1;
    // if (condition) {
    // }
  }
}

static void drawCost() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto mId = wComp->warMachines[Global::dweIndex].first;
  auto cost = WarMachineCfg::machineCost.at(mId);
  std::vector<std::pair<uint8_t, uint8_t>> costVec;
  for (int8_t i = cost.size() - 1; i >= 0; i--) {
    if (cost[i] != 0) {
      costVec.push_back({i, cost[i]});
    }
  }
  int size = costVec.size();
  auto textures = Global::defCache["RESOURCE.def/0"];
  uint8_t m = 0;
  FreeTypeSys::setSize(12);
  FreeTypeSys::setColor(255, 255, 255, 255);
  for (auto posRect : {SDL_FRect{leftUp.x + 64, leftUp.y + 245, 32, 32},
                       SDL_FRect{leftUp.x + 322, leftUp.y + 245, 32, 32}}) {
    auto totalWidth = size * 32;
    auto padding = (99 - totalWidth) / (size + 1);
    for (auto i = 0; i < costVec.size(); i++) {
      auto texture = textures[costVec[i].first];
      SDL_FRect pRect{posRect.x + padding * (i + 1) + i * texture->w, posRect.y,
                      static_cast<float>(texture->w),
                      static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &pRect);
      if (m == 0) {
        FreeTypeSys::drawCenter(pRect.x + 16, pRect.y + 35, costVec[i].second);
      } else {
        FreeTypeSys::drawCenter(pRect.x + 16, pRect.y + 35,
                                Global::dweSliderNum * costVec[i].second);
      }
    }
    m++;
  }
}

uint32_t WarMachineFacSys::maxCount() {
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto mId = wComp->warMachines[Global::dweIndex].first;
  auto cost = WarMachineCfg::machineCost.at(mId);
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
static void drawSlider() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto count = WarMachineFacSys::maxCount();
  if (count != 0) {
    SliderSys::drawHor(leftUp.x + 176, leftUp.y + 279, 135,
                       Global::dweSliderNum / (float)count);
  } else {
    SliderSys::drawHor(leftUp.x + 176, leftUp.y + 279, 135, 0);
  }
}

bool WarMachineFacSys::run() {
  dweAnimate();
  drawBackGround();
  drawWarMachine();
  drawCost();
  drawButton();
  drawSlider();
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

static bool clickMachine(bool leftClick) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  int size = wComp->warMachines.size();
  // 100x120
  int per = (485 - size * 100) / (size + 1);
  for (uint8_t i = 0; i < size; i++) {
    auto x = leftUp.x + per * (i + 1) + i * 100;
    auto y = leftUp.y + 60;
    posRect = {x, y, 100, 130};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (leftClick) {
        if (Global::dweIndex == i) {
          World::enterWarMachine(wComp->warMachines[i],
                                 (uint8_t)Enum::CRETYPE::MOD_DWE);
        }
        Global::dweIndex = i;
      } else {
        World::enterWarMachine(wComp->warMachines[i],
                               (uint8_t)Enum::CRETYPE::POP_DWE);
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
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  // click slider
  if (clickSlider()) {
    return false;
  }
  if (clickMachine(true)) {
    return false;
  }
  return true;
}

bool WarMachineFacSys::rightMouseDown(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  if (clickMachine(false)) {
    return false;
  }
  return true;
}