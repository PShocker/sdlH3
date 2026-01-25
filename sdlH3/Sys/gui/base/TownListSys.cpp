#include "TownListSys.h"
#include "Comp/TownComp.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "Sys/gui/AdvMapSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <vector>

static std::vector<Button> buttonInfo(int32_t x, int32_t y, int32_t length,
                                      uint8_t &page, uint8_t i,
                                      uint8_t playerId) {
  std::vector<Button> v;
  Button b;
  b.textures = Global::defCache["IAM014.DEF/0"];
  b.r = {static_cast<float>(x), static_cast<float>(y), 48, 16};
  b.disable = page > 0 ? false : true;
  b.func = [&]() { page -= 1; };
  v.push_back(b);

  b.textures = Global::defCache["IAM015.DEF/0"];
  b.r = {static_cast<float>(x), static_cast<float>(y + 16 + 32 * length), 48,
         16};
  b.disable =
      (page + length) >= Global::towns[Global::playerId].size() ? true : false;
  b.func = [&]() { page += 1; };
  v.push_back(b);

  return v;
}

void TownListSys::draw(int32_t x, int32_t y, int32_t length, uint8_t page,
                       uint8_t i, uint8_t playerId, bool top) {
  // render small town PortraitsSmall
  SDL_FRect posRect = {static_cast<float>(x), static_cast<float>(y + 16), 48,
                       32};
  for (uint8_t m = 0; m < length; m++) {
    auto index = m + page;
    if (index >= Global::towns[Global::playerId].size()) {
      break;
    }
    auto &[level, townEnt] = Global::towns[Global::playerId][index];
    auto &registry = World::registrys[level];
    auto townComp = &registry.get<TownComp>(townEnt);
    auto texture = Global::defCache["ITPA.DEF/0"][2 + 2 * townComp->id];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == i) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
    posRect.y += 32;
  }

  auto v = buttonInfo(x, y, length, page, i, playerId);
  AdvMapSys::drawButtons(0, 0, top, v);
  return;
}

bool TownListSys::click(int32_t x, int32_t y, int32_t length, uint8_t &page,
                        uint8_t &i, uint8_t playerId, uint8_t clickType) {
  bool r = false;
  auto pageBak = page;
  auto v = buttonInfo(x, y, length, page, i, playerId);
  if (AdvMapSys::clickButtons(0, 0, v, clickType)) {
    r = true;
  }
  if (page != pageBak) {
    r = true;
  }

  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect = {static_cast<float>(x), static_cast<float>(y + 16), 48,
                       32};
  for (uint8_t m = 0; m < length; m++) {
    auto index = m + page;
    if (index >= Global::towns[Global::playerId].size()) {
      break;
    }
    if (SDL_PointInRectFloat(&point, &posRect)) {
      i = m;
      r = true;
      break;
    }
    posRect.y += 32;
  }
  return r;
}