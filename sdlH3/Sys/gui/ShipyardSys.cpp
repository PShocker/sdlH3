#include "ShipyardSys.h"
#include "AdvMapSys.h"
#include "Comp/ObjectComp.h"
#include "Comp/PositionComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>

auto goldValue = 1000;
auto woodValue = 10;

static void close() { World::exitScrn(); }

static void buy() {
  auto &registry = World::registrys[World::level];

  std::unordered_set<int32_t> block;
  block.insert(Global::landBlock[World::level].begin(),
               Global::landBlock[World::level].end());
  block.insert(Global::rockBlock[World::level].begin(),
               Global::rockBlock[World::level].end());
  for (auto ent : registry.view<ObjectComp>()) {
    if (registry.get<PositionComp>(ent).z == INT32_MIN) {
      continue;
    }
    auto objectComp = &registry.get<ObjectComp>(ent);
    for (auto v : {objectComp->accessTiles, objectComp->blockTiles}) {
      for (auto i : v) {
        auto x = objectComp->x + i.first;
        auto y = objectComp->y + i.second;
        block.insert(x + y * Global::mapSize);
      }
    }
  }
  auto shipyObjectComp = registry.get<ObjectComp>(Global::goalEnt);
  // 方向数组
  const std::vector<SDL_Point> directions = {
      {-2, -1}, {-1, -1}, {0, -1}, {1, -1}, {2, -1}, //
      {-2, 0},  {2, 0},                              //
      {-2, 1},  {-1, 1},  {0, 1},  {1, 1},  {2, 1}}; //
  for (const auto &dir : directions) {
    auto m = shipyObjectComp.x + dir.x + shipyObjectComp.accessTiles[0].first;
    auto n = shipyObjectComp.y + dir.y + shipyObjectComp.accessTiles[0].second;
    if (!block.contains(m + n * Global::mapSize)) {
      Global::fadeCallBack = []() {
        World::LMouseUpSysBak.pop_back();
        World::LMouseDownSysBak.pop_back();
        World::RMouseUpSysBak.pop_back();
        World::RMouseDownSysBak.pop_back();
        World::keyUpSysBak.pop_back();
        Global::cursorBack.pop_back();
        return true;
      };
      World::iterateSystems.pop_back();
      World::iterateSystems.pop_back();
      World::iterateSystemsBak.push_back(World::iterateSystems);
      World::iterateSystemsBak.back().push_back(CursorSys::run);
      World::iterateSystems.push_back([m, n]() {
        Ent::loadBoat("AB01_.def", m + 1, n, World::level, 2, 0);
        Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
        return true;
      });
      Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                          Global::viewPort.h - 47};
      World::iterateSystems.push_back(World::enterFadeScrn);
      return;
    }
  }
}

static bool canBuy() {
  auto gold = Global::resources[Global::playerId][(uint8_t)Enum::RESTYPE::GOLD];
  auto wood = Global::resources[Global::playerId][(uint8_t)Enum::RESTYPE::WOOD];
  if (gold >= goldValue && wood >= woodValue) {
    return true;
  }
  return false;
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["IBY6432.DEF/0"];
  b.r = {42, 312, 64, 30};
  b.func = buy;
  b.disable = !canBuy();
  v.push_back(b);

  b.textures = Global::defCache["ICANCEL.DEF/0"];
  b.r = {224, 312, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 329) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 388) / 2)};
  posRect = {leftUp.x, leftUp.y, 329, 388};
  auto texture = Global::pcxCache["TPSHIP.PCX"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  texture = Global::pcxCache["TPSHIPBK.PCX"][0];
  posRect = {leftUp.x + 100, leftUp.y + 69, 128, 96};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 15,
                          strPool[926 + (uint8_t)ObjectType::SHIPYARD]);

  auto goldPic = Global::defCache["RESOURCE.def"][(uint8_t)Enum::RESTYPE::GOLD];
  auto woodPic = Global::defCache["RESOURCE.def"][(uint8_t)Enum::RESTYPE::WOOD];

  posRect = {leftUp.x + 100, leftUp.y + 244, static_cast<float>(goldPic->w),
             static_cast<float>(goldPic->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  posRect = {leftUp.x + 196, leftUp.y + 244, static_cast<float>(woodPic->w),
             static_cast<float>(woodPic->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  FreeTypeSys::drawCenter(leftUp.x + 118, leftUp.y + 294, goldValue);
  FreeTypeSys::drawCenter(leftUp.x + 212, leftUp.y + 294, woodValue);
}

static void drawButton() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 329) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 388) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == ShipyardSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}
bool ShipyardSys::run() {
  drawBackGround();
  drawButton();
  return true;
}

bool ShipyardSys::keyUp(uint16_t key) { return false; }

bool ShipyardSys::rightMouseUp(float x, float y) { return true; }

bool ShipyardSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 329) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 388) / 2)};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}