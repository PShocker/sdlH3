#include "TownHallSys.h"
#include "AdvMapSys.h"
#include "Cfg/TownCfg.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/TownComp.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
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

  posRect = {leftUp.x, leftUp.y, 800, 600};
  // auto texture = Global::defCache[TownCfg::hallBackgroundStr[]];
  // auto texture = TownGui::hallBackgrounds[playerIdComp->id][townComp->id];
  // SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawBuildIcon() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto buildings = townComp->buildings;
  auto slots = TownCfg::townHallSlots[townComp->id];
  uint16_t count = 0;
  // for (int row = 0; row < slots.size(); row++) {
  //   for (int col = 0; col < slots[row].size(); col++) {
  //     auto buildSlots = slots[row][col];
  //     SDL_Texture *texture = nullptr;
  //     for (int i = 0; i < buildSlots.size(); i++) {
  //       if (buildings.contains(buildSlots[i])) {
  //         if (i == buildSlots.size()) {
  //           texture = TownGui::buildingsIcons[townComp->id][count];
  //         } else if (i == buildSlots.size() - 1) {
  //           texture = TownGui::buildingsIcons[townComp->id]
  //                                            [count + buildSlots.size() - 1];
  //         } else {
  //           texture = TownGui::buildingsIcons[townComp->id][count + i + 1];
  //         }
  //         break;
  //       }
  //     }
  //     float posX = 402 - (float)slots[row].size() * 154 / 2 -
  //                  (slots[row].size() - 1) * 20 + 194 * col;
  //     float posY = 37 + 104 * (int)row;
  //     posRect = {leftUp.x + static_cast<float>(posX),
  //                leftUp.y + static_cast<float>(posY), 150, 70};
  //     SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  //   }
  //   count += slots[row].size();
  // }
  for (auto vec : TownCfg::townHallSlots[townComp->id]) {
  }
}

bool TownHallSys::run() {
  drawBackGround();
  drawBuildIcon();
  drawButton();
  return true;
}

bool TownHallSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}