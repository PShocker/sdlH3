#include "HeroListSys.h"
#include "Cfg/HeroCfg.h"
#include "Comp/HeroComp.h"
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
  b.textures = Global::defCache["IAM012.DEF/0"];
  b.r = {static_cast<float>(x), static_cast<float>(y), 64, 16};
  b.disable = page > 0 ? false : true;
  b.func = [&]() { page -= 1; };
  v.push_back(b);

  b.textures = Global::defCache["IAM013.DEF/0"];
  b.r = {static_cast<float>(x), static_cast<float>(y + 16 + 32 * length), 64,
         16};
  b.disable =
      (page + length) >= Global::heros[Global::playerId].size() ? true : false;
  b.func = [&]() { page += 1; };
  v.push_back(b);

  return v;
}

void HeroListSys::draw(int32_t x, int32_t y, int32_t length, uint8_t page,
                       uint8_t i, uint8_t playerId, bool top) {
  SDL_FRect posRect = {static_cast<float>(x + 8), static_cast<float>(y + 16),
                       48, 32};
  for (uint8_t m = 0; m < length; m++) {
    auto index = m + page;
    if (index >= Global::heros[Global::playerId].size()) {
      break;
    }
    auto &[level, heroEnt] = Global::heros[Global::playerId][index];
    auto &registry = World::registrys[level];
    auto hComp = &registry.get<HeroComp>(heroEnt);
    auto texture = Global::pcxCache[HeroCfg::heroSmallPor[hComp->portrait]][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == i) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
    // drawMovement
    texture = Global::defCache["IMOBIL.def/0"]
                              [std::min((int)hComp->movement / 100, 25)];
    SDL_FRect pRect = {posRect.x - 6, posRect.y, 6, 30};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &pRect);

    texture =
        Global::defCache["IMANA.def/0"][std::min((int)hComp->mana / 5, 25)];
    pRect = {posRect.x + 49, posRect.y, 6, 30};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &pRect);
    posRect.y += 32;
  }

  auto v = buttonInfo(x, y, length, page, i, playerId);
  AdvMapSys::drawButtons(0, 0, top, v);
  return;
}

bool HeroListSys::click(int32_t x, int32_t y, int32_t length, uint8_t &page,
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
  SDL_FRect posRect = {static_cast<float>(x + 8), static_cast<float>(y + 16),
                       48, 32};
  for (uint8_t m = 0; m < length; m++) {
    auto index = m + page;
    if (index >= Global::heros[Global::playerId].size()) {
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