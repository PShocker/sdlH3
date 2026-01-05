#include "DwellingSys.h"
#include "AdvMapSys.h"
#include "Cfg/CreatureCfg.h"
#include "Cfg/TownCfg.h"
#include "Comp/DwellingComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/base/SliderSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

static void toMax() { Global::dweSliderNum = DwellingSys::maxCount(); }

static void close() { World::exitScrn(); }

static void buy() {
  auto &registry = World::registrys[World::level];
  // 判断英雄身上是否可以放下这个生物
  auto dweComp = &registry.get<DwellingComp>(Global::goalEnt);
  auto creatureId = dweComp->creatures[Global::dweIndex].first;
  auto creatureNum = dweComp->creatures[Global::dweIndex].second;
  auto heroComp = &registry.get<HeroComp>(Global::heroEnt);
  int8_t r = -1;
  for (uint8_t i = 0; i < heroComp->creatures.size(); i++) {
    if (heroComp->creatures[i].first == creatureId) {
      r = i;
      break;
    }
  }
  if (r != -1) {
    heroComp->creatures[r].second += creatureNum;
    close();
  } else if (heroComp->creatures.size() < 8) {
    for (uint8_t i = 0; i < heroComp->creatures.size(); i++) {
      if (heroComp->creatures[i].first == 0xffff) {
        heroComp->creatures[i] = {creatureId, creatureNum};
        break;
      }
    }
    close();
  } else {
    World::enterConfirm(100, 100, ((uint8_t)Enum::SCNTYPE::MOD));
  }
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["IRCBTNS.DEF/0"];
  b.r = {134, 313, 64, 32};
  b.func = toMax;
  if (DwellingSys::maxCount() == 0) {
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
  auto dweComp =
      &World::registrys[World::level].get<DwellingComp>(Global::goalEnt);
  auto count = dweComp->creatures[Global::goalIndex].second;
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
}

static void drawCreatures() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto creatures = World::registrys[World::level]
                       .get<DwellingComp>(Global::goalEnt)
                       .creatures;
  int size = creatures.size();
  // 100x120
  int per = (485 - size * 100) / (size + 1);
  for (uint8_t i = 0; i < size; i++) {
    auto x = leftUp.x + per * (i + 1);
    auto y = leftUp.y + 60;
    auto id = creatures[i].first;
    auto defPath = CreatureCfg::creatureGraphics.at(id);
    auto group = 0;
    auto textures = Global::defCache[defPath + "/" + std::to_string(group)];
    auto index = Global::dweFrameIndex % textures.size();
    auto colorType = Global::goalIndex == i ? 1 : 0;
    DwellingSys::drawCreature(x, y, id, group, index, colorType);
  }
}

void DwellingSys::drawCreature(float x, float y, uint16_t id, uint16_t group,
                               uint16_t index, uint8_t colorType) {
  auto townIndex = CreatureCfg::creatureTowns.at(id);
  SDL_FRect posRect{x, y, 100, 130};
  auto texture = Global::pcxCache[TownCfg::creatureBackground[townIndex][1]][0];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  if (colorType == 1) {
    SDL_SetRenderDrawColor(Window::renderer, 255, 0, 0, 255);
  } else {
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  }
  SDL_RenderRect(Window::renderer, &posRect);
  auto textures = Global::defCache[CreatureCfg::creatureGraphics.at(id) + "/" +
                                   std::to_string(group)];
  texture = textures[index];
  SDL_FRect srcRect;
  if (CreatureCfg::creatureExAttr[id][CreatureCfg::EX_ATTRIBUTE::DOUBLE_WIDE]) {
    srcRect = {165, 145, 100, 130};
  } else {
    srcRect = {145, 145, 100, 130};
  }
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == DwellingSys::run);
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
  auto dweComp =
      &World::registrys[World::level].get<DwellingComp>(Global::goalEnt);
  auto creature = dweComp->creatures[Global::goalIndex].first;
  auto cost = CreatureCfg::creatureCost.at(creature);
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

uint32_t DwellingSys::maxCount() {
  auto dweComp =
      &World::registrys[World::level].get<DwellingComp>(Global::goalEnt);
  auto creature = dweComp->creatures[Global::goalIndex].first;
  auto cost = CreatureCfg::creatureCost.at(creature);
  uint32_t maxCount = UINT32_MAX;
  for (uint8_t i = 0; i < cost.size(); i++) {
    auto r = Global::resources[Global::playerId][i];
    if (cost[i] == 0) {
      continue;
    }
    maxCount = std::min(r / cost[i], maxCount);
  }
  auto count = dweComp->creatures[Global::goalIndex].second;
  return std::min(maxCount, count);
}

static void drawSlider() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto dweComp =
      &World::registrys[World::level].get<DwellingComp>(Global::goalEnt);
  auto count = DwellingSys::maxCount();
  if (count != 0) {
    SliderSys::drawHor(leftUp.x + 176, leftUp.y + 279, 135,
                       Global::dweSliderNum / (float)count);
  } else {
    SliderSys::drawHor(leftUp.x + 176, leftUp.y + 279, 135, 0);
  }
}

bool DwellingSys::run() {
  dweAnimate();
  drawBackGround();
  drawCreatures();
  drawCost();
  drawButton();
  drawSlider();
  return true;
}

bool DwellingSys::keyUp(uint16_t key) { return false; }

static bool clickSlider() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  // click slider
  auto dweComp =
      &World::registrys[World::level].get<DwellingComp>(Global::goalEnt);
  auto count = DwellingSys::maxCount();
  if (auto num = SliderSys::clickHor(leftUp.x + 176, leftUp.y + 279, 135,
                                     Global::dweSliderNum, count);
      num != Global::dweSliderNum) {
    Global::dweSliderNum = num;
    return true;
  }
  return false;
}

static bool clickCre(bool leftClick) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;

  auto dweComp =
      &World::registrys[World::level].get<DwellingComp>(Global::goalEnt);
  // click creature
  int size = dweComp->creatures.size();
  // 100x120
  int per = (485 - size * 100) / (size + 1);
  for (uint8_t i = 0; i < size; i++) {
    auto x = leftUp.x + per * (i + 1);
    auto y = leftUp.y + 60;
    posRect = {x, y, 100, 130};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (leftClick) {
        if (Global::goalIndex == i) {
          World::enterCreature(dweComp->creatures[i],
                               (uint8_t)Enum::CRETYPE::MOD_DWE);
        } else {
          Global::goalIndex = i;
        }
      } else {
        World::enterCreature(dweComp->creatures[i],
                             (uint8_t)Enum::CRETYPE::POP_DWE);
      }
      return true;
    }
  }
  return false;
}

bool DwellingSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  if (clickSlider()) {
    return false;
  }
  if (clickCre(true)) {
    return false;
  }
  return true;
}

bool DwellingSys::rightMouseDown(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  // click creature
  if (clickCre(false)) {
    return false;
  }
  return true;
}