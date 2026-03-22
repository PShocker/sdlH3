#include "TownListSys.h"
#include "Comp/TownComp.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "Sys/gui/AdvMapSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <vector>

void TownListSys::init(int32_t x, int32_t y, int32_t length, uint8_t &page,
                       uint8_t i, uint8_t playerId) {
  buttons.clear();
  {
    Button button;
    button.textures = Global::defCache["IAM014.DEF/0"];
    button.r = {static_cast<float>(x), static_cast<float>(y), 48, 16};
    button.clickFunc = [&]() { page -= 1; };
    button.disableFunc = [page]() { return page > 0 ? false : true; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }

  {
    Button button;
    button.textures = Global::defCache["IAM015.DEF/0"];
    button.r = {static_cast<float>(x), static_cast<float>(y + 16 + 32 * length),
                48, 16};
    button.clickFunc = [&]() { page += 1; };
    button.disableFunc = [page, length]() {
      return (page + length) >= Global::towns[Global::playerId].size();
    };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }
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

  TownListSys::init(x, y, length, page, i, playerId);
  AdvMapSys::drawButtons(0, 0, top, buttons);
  return;
}

bool TownListSys::click(int32_t x, int32_t y, int32_t length, uint8_t &page,
                        uint8_t &i, uint8_t playerId, uint8_t clickType) {
  bool r = false;
  auto pageBak = page;
  TownListSys::init(x, y, length, page, i, playerId);
  if (AdvMapSys::clickButtons(0, 0, buttons, clickType)) {
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