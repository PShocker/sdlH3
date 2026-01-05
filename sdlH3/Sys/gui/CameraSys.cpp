#include "CameraSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "SDL3/SDL_scancode.h"
#include "Window/Window.h"
#include <algorithm>

void CameraSys::fixViewPort() {
  Global::viewPort.x = std::clamp(Global::viewPort.x, -Global::viewPort.w / 4,
                                  Global::mapW - 2 * Global::viewPort.w / 4);
  Global::viewPort.y = std::clamp(Global::viewPort.y, -Global::viewPort.h / 4,
                                  Global::mapH - 2 * Global::viewPort.h / 4);
}

void CameraSys::focus(int32_t x, int32_t y) {
  Global::viewPort.x = x - (Global::viewPort.w - 199) / 2;
  Global::viewPort.y = y - (Global::viewPort.h - 47) / 2;
  CameraSys::fixViewPort();
}

bool CameraSys::run() {
  if (Global::cursorType != (uint8_t)Enum::CURSOR::ADVENTURE) {
    return true;
  }
  auto keyboardState = Window::keyboardState;
  if (keyboardState[SDL_SCANCODE_UP]) {
    Global::viewPort.y -= 10;
  }
  if (keyboardState[SDL_SCANCODE_DOWN]) {
    Global::viewPort.y += 10;
  }
  if (keyboardState[SDL_SCANCODE_LEFT]) {
    Global::viewPort.x -= 10;
  }
  if (keyboardState[SDL_SCANCODE_RIGHT]) {
    Global::viewPort.x += 10;
  }

  fixViewPort();
  return true;
}