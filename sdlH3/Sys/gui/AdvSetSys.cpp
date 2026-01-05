#include "AdvSetSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"


#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>


static std::tuple<std::vector<std::vector<SDL_Texture *>>,
                  std::vector<SDL_FRect>, std::vector<bool>,
                  std::vector<std::function<void()>>>
buttonInfo() {
  std::vector<std::vector<SDL_Texture *>> textures;
  std::vector<SDL_FRect> r;
  std::vector<bool> dis;
  std::vector<std::function<void()>> func;
  textures.push_back(Global::defCache["iOKAY.def/0"]);

  return {textures, r, dis, func};
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 481) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 487) / 2)};
  auto texture = Global::pcxCache["Sysopbck.pcx"][Global::playerId];
  posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

enum ButtonType : uint8_t {
  buttonSysopb1,
  buttonSysopb2,
  buttonSysopb3,
  buttonSysopb4,
  buttonSysopb5,
  buttonSysopb6,
  buttonSysopb7,
  buttonSysopb8,
  buttonSysopb9,
  buttonSysopb10,
  buttonSysopb11,
  buttonSysopb12,
  buttonSysopb13,
  buttonSysopb14,

  buttonLoad,
  buttonSave,
  buttonRstrt,
  buttonMain,
  buttonQuit,
  buttonRetrn,

  Length,
};

static void drawButton() {
  std::vector<SDL_Texture *> buttons[] = {
      Global::defCache["SYSOPB1.DEF/0"], Global::defCache["SYSOPB2.DEF/0"],
      Global::defCache["SYSOPB3.DEF/0"], Global::defCache["SYSOPB4.DEF/0"],
      Global::defCache["SYSOPB5.DEF/0"], Global::defCache["SYSOPB6.DEF/0"],
      Global::defCache["SYSOPB7.DEF/0"], Global::defCache["SYSOPB8.DEF/0"],
      Global::defCache["SYSOPB9.DEF/0"], Global::defCache["SYSOB10.DEF/0"],
      Global::defCache["SYSOB11.DEF/0"], Global::defCache["SYSOB12.DEF/0"],
      Global::defCache["SYSOB13.DEF/0"], Global::defCache["SYSOPCHK.DEF/0"],
      Global::defCache["SOLOAD.DEF/0"],  Global::defCache["SOSAVE.DEF/0"],
      Global::defCache["SORSTRT.DEF/0"], Global::defCache["SOMAIN.DEF/0"],
      Global::defCache["soquit.DEF/0"],  Global::defCache["soretrn.DEF/0"]};

  SDL_FRect posRect;
  SDL_Texture *texture;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 481) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 487) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};

  for (uint8_t i = 0; i < 4; i++) {
    posRect = {leftUp.x + 28 + i * 48, leftUp.y + 77, 46, 32};
    if (Global::gameSets[(uint8_t)Enum::GAMESET::MY_HERO_SPEED] == i) {
      texture = buttons[i][2];
    } else {
      if (SDL_PointInRectFloat(&point, &posRect) &&
          Window::mouseState & SDL_BUTTON_LMASK) {
        texture = buttons[i][1];
      } else {
        texture = buttons[i][0];
      }
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }

  for (uint8_t i = 0; i < 4; i++) {
    posRect = {leftUp.x + 28 + i * 48, leftUp.y + 144, 46, 32};
    if (Global::gameSets[(uint8_t)Enum::GAMESET::OTHER_HERO_SPEED] == i) {
      texture = buttons[i + 4][2];
    } else {
      if (SDL_PointInRectFloat(&point, &posRect) &&
          Window::mouseState & SDL_BUTTON_LMASK) {
        texture = buttons[i + 4][1];
      } else {
        texture = buttons[i + 4][0];
      }
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }

  for (uint8_t i = 0; i < 3; i++) {
    posRect = {leftUp.x + 28 + i * 64, leftUp.y + 211, 62, 32};
    if (Global::gameSets[(uint8_t)Enum::GAMESET::MAP_SPEED] == i) {
      texture = buttons[i + 8][2];
    } else {
      if (SDL_PointInRectFloat(&point, &posRect) &&
          Window::mouseState & SDL_BUTTON_LMASK) {
        texture = buttons[i + 8][1];
      } else {
        texture = buttons[i + 8][0];
      }
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }

  for (uint8_t i = 0; i < 2; i++) {
    posRect = {leftUp.x + 28 + i * 96, leftUp.y + 278, 94, 32};
    if (Global::gameSets[(uint8_t)Enum::GAMESET::ANIMATE_EFFECT] == i) {
      texture = buttons[i + 11][2];
    } else {
      if (SDL_PointInRectFloat(&point, &posRect) &&
          Window::mouseState & SDL_BUTTON_LMASK) {
        texture = buttons[i + 11][1];
      } else {
        texture = buttons[i + 11][0];
      }
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }

  for (uint8_t i = 0; i < 2; i++) {
    posRect = {leftUp.x + 26 + Global::gameSets[(uint8_t)Enum::GAMESET::MUSIC1 + i],
               leftUp.y + 357 + i * 65, 20, 40};
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
    posRect.x += 1;
    posRect.y += 1;
    posRect.w -= 2;
    posRect.h -= 2;
    SDL_SetRenderDrawColor(Window::renderer, 173, 175, 157, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
  }

  for (uint8_t i = 0; i < 6; i++) {
    posRect = {leftUp.x + 246, leftUp.y + 55 + i * 32, 32, 24};
    if (Global::gameSets[(uint8_t)Enum::GAMESET::HERO_TIP + i] == 1) {
      texture = buttons[ButtonType::buttonSysopb14][1];
    } else {
      texture = buttons[ButtonType::buttonSysopb14][0];
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_SetRenderDrawColor(Window::renderer, 255, 0, 0, 128); //
    // SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
    // SDL_RenderFillRect(Window::renderer, &posRect);
  }

  for (uint8_t i = 0; i < 6; i++) {
    auto col = i / 2;
    auto row = i % 2;
    posRect = {leftUp.x + 246 + row * 110, leftUp.y + 297 + col * 59, 100, 48};
    if (SDL_PointInRectFloat(&point, &posRect) &&
        Window::mouseState & SDL_BUTTON_LMASK) {
      texture = buttons[i + ButtonType::buttonLoad][0];
    } else {
      texture = buttons[i + ButtonType::buttonLoad][1];
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_SetRenderDrawColor(Window::renderer, 255, 0, 0, 128); //
    // SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
    // SDL_RenderFillRect(Window::renderer, &posRect);
  }
}

static void save() {}

bool AdvSetSys::run() {
  drawBackGround();
  drawButton();

  return true;
}

static void close() { World::exitScrn(); }

bool AdvSetSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    close();
    break;
  }
  default:
    break;
  }
  return true;
}