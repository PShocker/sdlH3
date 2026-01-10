#pragma once

#include "SDL3/SDL_render.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

struct Button {
  std::vector<SDL_Texture *> textures;
  SDL_FRect r;
  bool disable;
  std::function<void()> func;
  std::u16string title = u"";
  std::u16string info = u"";
};

struct AdvMapSys {
  static void drawResBar(float x,float y);

  static void heroFocus();
  static void heroFocus(entt::entity heroEnt, uint8_t level);
  static void townFocus(entt::entity townEnt, uint8_t level);
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool leftMouseDown(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
  static bool keyDown(uint16_t key);
  static void drawButtons(float x, float y, bool press, std::vector<Button> &v);
  static bool clickButtons(float x, float y, std::vector<Button> &v,
                           uint8_t clickType);
  static bool drawButtonsText(float x, float y, float pX, float pY,
                              std::vector<Button> &v);
};
