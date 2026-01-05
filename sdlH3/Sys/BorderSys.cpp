#include "BorderSys.h"
#include "Global/Global.h"

#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include <cstdint>

void BorderSys::drawMaskWithHole(float holeX, float holeY, float holeWidth,
                                 float holeHeight, uint8_t alpha) {
  // 设置遮罩颜色（半透明黑色）
  SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, alpha);
  SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
  //  先求出矩形的相交部分,然后反向获取不相交的部分
  SDL_FRect holeRect = {holeX, holeY, holeWidth, holeHeight};
  SDL_FRect intersection;
  if (SDL_GetRectIntersectionFloat(&Global::viewPort, &holeRect,
                                   &intersection)) {
    auto texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_UNKNOWN,
                                     SDL_TEXTUREACCESS_TARGET,
                                     Global::viewPort.w, Global::viewPort.h);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(Window::renderer, texture);
    SDL_RenderClear(Window::renderer);
    SDL_FRect posRect;
    posRect = {intersection.x - Global::viewPort.x,
               intersection.y - Global::viewPort.y,
               static_cast<float>(intersection.w),
               static_cast<float>(intersection.h)};
    SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 0);
    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_NONE);
    SDL_RenderFillRect(Window::renderer, &posRect);
    SDL_SetRenderTarget(Window::renderer, nullptr);
    posRect = {0, 0, static_cast<float>(texture->w),
               static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_DestroyTexture(texture);
  } else {
    SDL_FRect posRect = {0, 0, static_cast<float>(Global::viewPort.w),
                         static_cast<float>(Global::viewPort.h)};
    SDL_RenderFillRect(Window::renderer, &posRect);
  }
}

bool BorderSys::run() {
  drawMaskWithHole(0, 0, Global::mapW, Global::mapH, 255);
  SDL_FRect posRect;
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  posRect = {-Global::viewPort.x, -Global::viewPort.y,
             static_cast<float>(Global::mapW),
             static_cast<float>(Global::mapH)};
  SDL_RenderRect(Window::renderer, &posRect);
  return true;
}