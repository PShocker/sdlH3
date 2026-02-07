#include "TownHallSys.h"
#include "AdvMapSys.h"
#include "Cfg/TownCfg.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["TPMAGE1.DEF/0"];
  b.r = {748, 556, 48, 40};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TownHallSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];

  auto townComp = &registry.get<TownComp>(townEnt);
  auto playerIdComp = &registry.get<PlayerIdComp>(townEnt);
  auto halBakStr = TownCfg::hallBackgroundStr[townComp->id];
  auto texture = Global::pcxCache[halBakStr][Global::playerId];
  posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawBuildIcon() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto &buildings = townComp->buildings;
  auto &slots = TownCfg::townHallSlots[townComp->id];
  for (int row = 0; row < slots.size(); row++) {
    auto &line = slots[row];
    for (int col = 0; col < line.size(); col++) {
      auto &slot = line[col];
      uint8_t bId = slot.back();
      for (auto i : slot) {
        if (!buildings.contains(i)) {
          bId = i;
          break;
        }
      }
      auto tStr = TownCfg::townBuildIcon[townComp->id].at(bId);
      auto texture = Global::pcxCache[tStr][0];
      float posX = 402 - (float)line.size() * 154 / 2 - (line.size() - 1) * 20 +
                   194 * col;
      float posY = 37 + 104 * (int)row;
      posRect = {leftUp.x + static_cast<float>(posX),
                 leftUp.y + static_cast<float>(posY), 150, 70};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

      auto textures = Global::defCache["TPTHBAR.def/0"];
      if (buildings.contains(bId)) {
        texture = textures[0];
      } else if (townComp->forbidBuildings.contains(bId)) {
        texture = textures[3];
      } else if (townComp->hasBuild) {
        texture = textures[2];
      } else {
        auto buildCost = TownCfg::townBuildCost[townComp->id].at(bId);
        auto resource = Global::resources[Global::playerId];
        uint8_t canBuy = 0;
        for (uint8_t i = 0; i < resource.size(); i++) {
          if (resource[i] >= buildCost[i]) {
            canBuy++;
          }
        }
        if (canBuy == resource.size()) {
          texture = textures[1];
        } else {
          texture = textures[2];
        }
      }
      posRect = {leftUp.x + static_cast<float>(posX) - 1,
                 leftUp.y + static_cast<float>(posY) + 71,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

      auto strPool = *Lang::strPool[Global::langIndex];
      auto bStr = strPool[3043 + (int8_t)bId * 2];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(255, 255, 255, 255);
      FreeTypeSys::drawCenter(posRect.x + 76, posRect.y, bStr);
    }
  }
}

static void drawResbar() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  AdvMapSys::drawResBar(leftUp.x + 3, leftUp.y + 575);
}

bool TownHallSys::run() {
  drawBackGround();
  drawBuildIcon();
  drawResbar();
  drawButton();
  return true;
}

static bool clickBuildIcon(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto &buildings = townComp->buildings;
  auto &slots = TownCfg::townHallSlots[townComp->id];
  for (int row = 0; row < slots.size(); row++) {
    auto &line = slots[row];
    for (int col = 0; col < line.size(); col++) {
      auto &slot = line[col];
      uint8_t bId = slot.back();
      for (auto i : slot) {
        if (!buildings.contains(i)) {
          bId = i;
          break;
        }
      }
      float posX = 402 - (float)line.size() * 154 / 2 - (line.size() - 1) * 20 +
                   194 * col;
      float posY = 37 + 104 * (int)row;
      posRect = {leftUp.x + static_cast<float>(posX),
                 leftUp.y + static_cast<float>(posY), 150, 88};
      SDL_FPoint point = {(float)(int)Window::mouseX,
                          (float)(int)Window::mouseY};

      if (SDL_PointInRectFloat(&point, &posRect)) {
        World::enterTownBuild(bId);
        return true;
      }
    }
  }
  return false;
}

bool TownHallSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickBuildIcon(clickType)) {
    return false;
  }
  return true;
}