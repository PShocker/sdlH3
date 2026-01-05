#include "FadeSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_render.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <optional>

bool FadeSys::run() {
  auto fadeTexture = Global::fadeTexture;
  auto fadeAlpha = Global::fadeAlpha;
  auto fadeSpeed = Global::fadeSpeed;
  SDL_SetTextureAlphaMod(fadeTexture, fadeAlpha);
  SDL_RenderTexture(Window::renderer, fadeTexture, nullptr, &Global::fadeRect);
  CursorSys::run();
  fadeAlpha -= Window::deltaTime * fadeSpeed;
  fadeAlpha = fadeAlpha < 0 ? 0 : fadeAlpha;
  Global::fadeAlpha = fadeAlpha;
  if (fadeAlpha <= 0) {
    if (Global::fadeCallBack.has_value()) {
      auto r = Global::fadeCallBack.value()();
      if (r) {
        Global::fadeCallBack = std::nullopt;
        World::exitScrn();
        return false;
      }
    } else {
      World::exitScrn();
      return false;
    }
  }
  return true;
}