#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

// 重载 SDL_Point 的加法运算符
SDL_FPoint operator+(const SDL_FPoint &m, const SDL_FPoint &n);
// 重载 SDL_Point 的减法运算符
SDL_FPoint operator-(const SDL_FPoint &m, const SDL_FPoint &n);

bool operator==(const SDL_FPoint &m, const SDL_FPoint &n);

bool operator!=(const SDL_FPoint &m, const SDL_FPoint &n);

// 返回两个点的相对方向，0是正上方向
enum class DIRECTION : uint8_t {
  UP,
  UPRIGHT,
  RIGHT,
  DOWNRIGHT,
  DOWN,
  DOWNLEFT,
  LEFT,
  UPLEFT,
};
uint8_t direction(const SDL_FPoint &m, const SDL_FPoint &n);

uint16_t distance(const SDL_FPoint &m, const SDL_FPoint &n);
