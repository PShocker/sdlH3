#include "PlayersPanelSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

const std::vector<SDL_Point> slotsPos = {
    {0, 0},    {83, 0},   {166, 0},   //
    {0, 118},  {83, 118}, {166, 118}, //
    {83, 236},
};

void PlayersPanelSys::draw(int32_t x, int32_t y, uint8_t index) {
  auto textures = Global::defCache["CREST58.def/0"];
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    auto texture = textures[i];
    posRect = {static_cast<float>(x + slotsPos[i].x+6),
               static_cast<float>(y + slotsPos[i].y+1),
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == i) {
      posRect = {static_cast<float>(x + slotsPos[i].x),
                 static_cast<float>(y + slotsPos[i].y), static_cast<float>(68),
                 static_cast<float>(88)};
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
  }
}

uint8_t PlayersPanelSys::click(int32_t x, int32_t y) {
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    posRect = {static_cast<float>(x + slotsPos[i].x),
               static_cast<float>(y + slotsPos[i].y), 68, 88};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      return i;
    }
  }
  return 0xff;
}