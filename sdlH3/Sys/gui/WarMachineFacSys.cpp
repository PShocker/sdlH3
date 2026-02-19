#include "WarMachineFacSys.h"

#include "Comp/HeroComp.h"
#include "Comp/WarMachineFacComp.h"
#include "CreatureSys.h"
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

  auto wComp = registry.get<WarMachineFacComp>(Global::goalEnt);
  auto mId = wComp.warMachines[Global::dweIndex];
  auto aId = CreatureSet::fullCreatures[mId]->experience;
  auto slot = CreatureSet::fullCreatures[mId]->abilities.at(Enum::WAR_MACHINE);
  auto value = std::any_cast<Enum::ARTIFACT_SLOT>(slot);
  auto &hComp = registry.get<HeroComp>(Global::heroEnt);
  if (hComp.artifacts[value] != 0xffff) {
    return;
  } else {
    hComp.artifacts[value] = aId;
    auto cost = CreatureSet::fullCreatures[mId]->cost;
    for (int i = 0; i < Global::resources[Global::playerId].size(); ++i) {
      auto &res = Global::resources[Global::playerId][i];
      res -= cost[i];
    }
    Global::dweSliderNum = 0;
  }
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

  auto count = 1;
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

static void drawWarMachine(float x, float y, uint16_t id, uint16_t group,
                           uint16_t index, uint8_t colorType) {
  auto defPath = CreatureSet::fullCreatures[id]->graphics.animation;
  auto textures = Global::defCache[defPath + "/" + std::to_string(group)];
  auto texture = textures[index];
  SDL_FRect srcRect;
  if (CreatureSet::fullCreatures[id]->abilities.contains(Enum::DOUBLE_WIDE)) {
    srcRect = {165, 145, 100, 130};
  } else {
    srcRect = {145, 145, 100, 130};
  }
  SDL_FRect posRect{x, y, 100, 130};
  // 色彩混合
  auto pal = SDL_GetTexturePalette(texture);
  SDL_Color originColor = pal->colors[5];
  // pal->colors[5] = CreatureCfg::ovColor[colorType];
  pal->colors[5] = CreatureSet::ovColor[colorType];
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  pal->colors[5] = originColor;
}

void WarMachineFacSys::drawMachineBak(float x, float y, uint16_t id,
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
  if (colorType != 0xff) {
    SDL_RenderRect(Window::renderer, &posRect);
  }
  drawWarMachine(x, y, id, group, index, CreatureSet::OV_COLOR_TRANSPARENCY);
}

static void drawWarMachines() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto wComp =
      World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto mhs = wComp.warMachines;
  int size = mhs.size();
  // 100x120
  auto pos = DwellingSys::creatruePos(size);
  for (uint8_t i = 0; i < size; i++) {
    auto p = pos[i];
    auto group = Global::dweGroup[i];
    auto id = mhs[i];
    auto defPath = CreatureSet::fullCreatures[id]->graphics.animation;
    auto textures = Global::defCache[defPath + "/" + std::to_string(group)];
    auto index = Global::dweFrameIndex[i] % textures.size();
    auto colorType = Global::dweIndex == i ? 1 : 0;
    WarMachineFacSys::drawMachineBak(leftUp.x + p.x, leftUp.y + p.y, id, group,
                                     index, colorType);
  }
}

static void drawButton() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == WarMachineFacSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawCost() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto wComp =
      &World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto mId = wComp->warMachines[Global::dweIndex];
  auto cost = CreatureSet::fullCreatures[mId]->cost;
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
  auto &registry = World::registrys[World::level];
  auto wComp = &registry.get<WarMachineFacComp>(Global::goalEnt);
  auto mId = wComp->warMachines[Global::dweIndex];
  auto aId = CreatureSet::fullCreatures[mId]->experience;
  auto slot = CreatureSet::fullCreatures[mId]->abilities.at(Enum::WAR_MACHINE);
  auto value = std::any_cast<Enum::ARTIFACT_SLOT>(slot);
  auto &hComp = registry.get<HeroComp>(Global::heroEnt);
  if (hComp.artifacts[value] != 0xffff) {
    return 0;
  }
  auto cost = CreatureSet::fullCreatures[mId]->cost;
  uint32_t maxCount = UINT32_MAX;
  for (uint8_t i = 0; i < cost.size(); i++) {
    auto r = Global::resources[Global::playerId][i];
    if (cost[i] == 0) {
      continue;
    }
    maxCount = std::min(r / cost[i], maxCount);
  }
  uint32_t count = 1;
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

static void warAnimate() {
  auto wComp =
      World::registrys[World::level].get<WarMachineFacComp>(Global::goalEnt);
  auto mhs = wComp.warMachines;
  for (uint8_t i = 0; i < mhs.size(); i++) {
    auto &frameTime = Global::dweFrameTime[i];
    auto &frameIndex = Global::dweFrameIndex[i];
    auto &group = Global::dweGroup[i];
    auto id = mhs[i];
    CreatureSys::creAnimate(frameTime, frameIndex, group, id);
  }
}

bool WarMachineFacSys::run() {
  warAnimate();
  drawBackGround();
  drawWarMachines();
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
        } else {
          Global::dweIndex = i;
          toMax();
        }
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