#include "DwellingSys.h"
#include "AdvMapSys.h"
#include "Cfg/CreatureCfg.h"
#include "Cfg/TownCfg.h"
#include "Comp/DwellingComp.h"
#include "Comp/HeroComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_pixels.h"
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

std::vector<SDL_Point> DwellingSys::creatruePos(uint8_t size) {
  std::vector<SDL_Point> v;
  switch (size) {
  case 2: {
    const auto centerX = 485 / 2;
    auto x0 = centerX - 50 - 70;
    auto x1 = centerX - 50 + 70;
    auto y = 60;
    v.push_back(SDL_Point{x0, y});
    v.push_back(SDL_Point{x1, y});
    break;
  }
  default: {
    auto per = (485 - size * 100) / (size + 1);
    for (uint8_t i = 0; i < size; i++) {
      auto x = per * (i + 1) + i * 100;
      auto y = 60;
      v.push_back(SDL_Point{x, y});
    }
    break;
  }
  }
  return v;
}

static std::vector<std::pair<uint16_t, uint32_t>> cres() {
  std::vector<std::pair<uint16_t, uint32_t>> v;
  auto level = World::level;
  auto creatures =
      World::registrys[level].get<DwellingComp>(Global::goalEnt).creatures;
  for (auto v0 : creatures) {
    for (auto v1 : v0.first) {
      v.push_back({v1, v0.second});
    }
  }
  return v;
}

static void toMax() { Global::dweSliderNum = DwellingSys::maxCount(); }

static void close() { World::exitScrn(); }

static void buy() {
  auto &registry = World::registrys[World::level];
  // 判断英雄身上是否可以放下这个生物
  auto creatures = cres();
  auto creatureId = creatures[Global::dweIndex].first;
  auto creatureNum = creatures[Global::dweIndex].second;
  std::vector<std::pair<uint16_t, uint32_t>> *cres;
  if (registry.all_of<HeroComp>(Global::heroEnt)) {
    auto heroComp = &registry.get<HeroComp>(Global::heroEnt);
    cres = &heroComp->creatures;
  } else {
    // townComp
    auto townComp = &registry.get<TownComp>(Global::heroEnt);
    cres = &townComp->garCreatures;
  }
  int8_t r = -1;
  for (uint8_t i = 0; i < cres->size(); i++) {
    if ((*cres)[i].first == creatureId) {
      r = i;
      break;
    }
  }
  if (r != -1) {
    (*cres)[r].second += creatureNum;
    close();
  } else if ((*cres).size() < 8) {
    for (uint8_t i = 0; i < (*cres).size(); i++) {
      if ((*cres)[i].first == 0xffff) {
        (*cres)[i] = {creatureId, creatureNum};
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
  auto creatures = cres();
  auto count = creatures[Global::dweIndex].second;
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
  auto creatures = cres();
  uint8_t size = creatures.size();
  // 100x120
  auto pos = DwellingSys::creatruePos(size);
  for (uint8_t i = 0; i < size; i++) {
    auto p = pos[i];
    auto id = creatures[i].first;
    auto defPath = CreatureCfg::creatureGraphics.at(id);
    auto group = 1;
    auto textures = Global::defCache[defPath + "/" + std::to_string(group)];
    auto index = Global::dweFrameIndex % textures.size();
    auto colorType = Global::dweIndex == i ? 1 : 0;
    DwellingSys::drawCreatureBak(leftUp.x + p.x, leftUp.y + p.y, id, group,
                                 index, colorType);
  }
}

void DwellingSys::drawCreature(float x, float y, uint16_t id, uint16_t group,
                               uint16_t index, uint8_t colorType) {
  // colorType指生物的描边颜色
  auto textures = Global::defCache[CreatureCfg::creatureGraphics.at(id) + "/" +
                                   std::to_string(group)];
  auto texture = textures[index];
  SDL_FRect srcRect;
  if (CreatureCfg::creatureExAttr[id][CreatureCfg::EX_ATTRIBUTE::DOUBLE_WIDE]) {
    srcRect = {165, 145, 100, 130};
  } else {
    srcRect = {145, 145, 100, 130};
  }
  SDL_FRect posRect{x, y, 100, 130};
  // 色彩混合
  auto pal = SDL_GetTexturePalette(texture);
  SDL_Color originColor = pal->colors[5];
  pal->colors[5] = CreatureCfg::ovColor[colorType];
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  pal->colors[5] = originColor;
}

void DwellingSys::drawCreatureBak(float x, float y, uint16_t id, uint16_t group,
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
  if (colorType != 0xff) {
    SDL_RenderRect(Window::renderer, &posRect);
  }
  drawCreature(x, y, id, group, index,
               (uint8_t)CreatureCfg::OV_COLOR::TRANSPARENCY);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
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

    auto creatures = cres();
    auto id = creatures.front().first;
    auto group = Global::dweGroup;

    auto textures = Global::defCache[CreatureCfg::creatureGraphics.at(id) +
                                     "/" + std::to_string(group)];
    if (Global::dweFrameIndex >= textures.size()) {
      Global::dweFrameIndex = 0;
      int arr[] = {0, 2, 3, 4};
      std::uniform_int_distribution<> distrib(0, std::size(arr) - 1);
      // 生成随机索引并选择元素
      int randomIndex = distrib(Global::gen);
      Global::dweGroup = arr[randomIndex];
    }
  }
}

static void drawCost() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  auto creatures = cres();
  auto id = creatures[Global::dweIndex].first;
  auto cost = CreatureCfg::creatureCost.at(id);
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
  auto creatures = cres();
  auto id = creatures[Global::dweIndex].first;
  auto cost = CreatureCfg::creatureCost.at(id);
  uint32_t maxCount = UINT32_MAX;
  for (uint8_t i = 0; i < cost.size(); i++) {
    auto r = Global::resources[Global::playerId][i];
    if (cost[i] == 0) {
      continue;
    }
    maxCount = std::min(r / cost[i], maxCount);
  }
  auto count = creatures[Global::dweIndex].second;
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

static bool clickCre(uint8_t clickType) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;

  auto creatures = cres();
  // click creature
  int size = creatures.size();
  // 100x120
  auto pos = DwellingSys::creatruePos(size);
  for (uint8_t i = 0; i < size; i++) {
    auto p = pos[i];
    posRect = {leftUp.x + p.x, leftUp.y + p.y, 100, 130};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        if (Global::dweIndex == i) {
          auto cre = creatures[i];
          World::enterCreature(cre, (uint8_t)Enum::CRETYPE::MOD_DWE);
        } else {
          Global::dweIndex = i;
        }
      } else {
        auto cre = creatures[i];
        World::enterCreature(cre, (uint8_t)Enum::CRETYPE::POP_DWE);
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
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickSlider()) {
    return false;
  }
  if (clickCre(clickType)) {
    return false;
  }
  return true;
}

bool DwellingSys::rightMouseDown(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 485) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 395) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  // click creature
  if (clickCre(clickType)) {
    return false;
  }
  return true;
}