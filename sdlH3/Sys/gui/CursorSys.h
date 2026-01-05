#pragma once

#include "SDL3/SDL_rect.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <utility>
struct CursorSys {
  static uint8_t astar(bool click);
  static std::pair<uint8_t, entt::entity> choose(bool click, float x, float y);
  static void clearHeroPath();
  static bool run();

  static bool leftMouseUp(float x, float y);
  static bool leftMouseDown(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);

  static SDL_Point goalPoint(SDL_FPoint point);
};