#include "Sys/ui/base/SelectionMapSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"

void SelectionMapSys::drawBackGround(float x, float y) {
  auto texture = Global::pcxCache["CamCust.pcx"][0];
  SDL_FRect posRect{x, y, static_cast<float>(texture->w),
                    static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
}