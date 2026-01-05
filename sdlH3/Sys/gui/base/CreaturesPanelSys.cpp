#include "CreaturesPanelSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

const std::vector<SDL_Point> slotsPos = {{0, 0},   {83, 0},  {166, 0},  //
                                         {0, 98},  {83, 98}, {166, 98}, //
                                         {83, 196}};

void CreaturesPanelSys::draw(
    int32_t x, int32_t y, std::vector<std::pair<uint16_t, uint32_t>> &creVec) {
  auto textures = Global::defCache["TWCRPORT.def/0"];
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    auto pair = creVec[i];
    if (pair.second == 0) {
      continue;
    }
    auto texture = textures[pair.first + 2];
    posRect = {static_cast<float>(x + slotsPos[i].x),
               static_cast<float>(y + slotsPos[i].y),
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
}

uint8_t CreaturesPanelSys::click(int32_t x, int32_t y) {
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    posRect = {static_cast<float>(x + slotsPos[i].x),
               static_cast<float>(y + slotsPos[i].y), 58, 64};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      return i;
    }
  }
  return 0xff;
}

void CreaturesPanelSys::drawBorder(int32_t x, int32_t y, uint8_t index) {
  SDL_FRect posRect;
  posRect = {static_cast<float>(x + slotsPos[index].x),
             static_cast<float>(y + slotsPos[index].y), 58, 64};
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}