#include "SliderSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include "World/World.h"
#include <algorithm>
#include <cstdint>
#include <vector>

void SliderSys::drawHor(int32_t x, int32_t y, int32_t length, float p) {
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto textures = Global::defCache["iGPCrDiv.def/0"];
  posRect = {static_cast<float>(x), static_cast<float>(y), 16, 16};
  auto texture = textures[0];
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (Window::mouseState & SDL_BUTTON_LMASK) {
      texture = textures[1];
    }
  }
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  posRect = {static_cast<float>(x + length - 16), static_cast<float>(y), 16,
             16};
  texture = textures[2];
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (Window::mouseState & SDL_BUTTON_LMASK) {
      texture = textures[3];
    }
  }
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  //   渲染slider
  texture = textures[4];
  auto sliderX = x + 16 + (length - 48) * p;
  posRect = {sliderX, static_cast<float>(y), static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

uint32_t SliderSys::clickHor(int32_t x, int32_t y, int32_t length, uint32_t num,
                             uint32_t count) {
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  const std::vector<SDL_FRect> buttonsPosition = {
      {static_cast<float>(x), static_cast<float>(y), 16, 16},
      {static_cast<float>(x + length - 16), static_cast<float>(y), 16, 16},
  };
  posRect = {buttonsPosition[0].x, buttonsPosition[0].y, 16, 16};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (num != 0) {
      num -= 1;
    }
  }
  posRect = {buttonsPosition[1].x, buttonsPosition[1].y, 16, 16};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (num < count) {
      num += 1;
    }
  }
  auto start = x + 16;
  auto end = x + length - 16;
  auto l = end - start;
  posRect = {static_cast<float>(start), static_cast<float>(y),
             static_cast<float>(l), 16};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto p = point.x - start;
    auto r = p / l;
    auto piece = 1 / (float)(count + 1);
    num = (r / piece);
  }
  return std::min(num, count);
}