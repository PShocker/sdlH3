#include "ResourcesPanelSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

const std::vector<SDL_Point> slotsPos = {
    {0, 0},    {83, 0},  {166, 0},  //
    {0, 79},   {83, 79}, {166, 79}, //
    {83, 158},
};

void ResourcesPanelSys::draw(int32_t x, int32_t y, uint8_t index) {
  auto textures = Global::defCache["RESOURCE.def/0"];
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    auto texture = textures[i];
    posRect = {static_cast<float>(x + slotsPos[i].x + 20),
               static_cast<float>(y + slotsPos[i].y + 10),
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == i) {
      posRect = {static_cast<float>(x + slotsPos[i].x),
                 static_cast<float>(y + slotsPos[i].y), static_cast<float>(69),
                 static_cast<float>(66)};
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
  }
}

void ResourcesPanelSys::drawNum(int32_t x, int32_t y,
                                std::array<std::u16string, 7> &r) {
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    FreeTypeSys::drawCenter(x + slotsPos[i].x + 35, y + slotsPos[i].y + 46,
                            r[i]);
  }
}

uint8_t ResourcesPanelSys::click(int32_t x, int32_t y) {
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    posRect = {static_cast<float>(x + slotsPos[i].x),
               static_cast<float>(y + slotsPos[i].y), 69, 66};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      return i;
    }
  }
  return 0xff;
}