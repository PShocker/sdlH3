#include "Point.h"
#include <cmath>
#include <cstdint>

SDL_FPoint operator+(const SDL_FPoint &m, const SDL_FPoint &n) {
  return {m.x + n.x, m.y + n.y};
}

SDL_FPoint operator-(const SDL_FPoint &m, const SDL_FPoint &n) {
  return {m.x - n.x, m.y - n.y};
}

bool operator==(const SDL_FPoint &m, const SDL_FPoint &n) {
  return m.x == n.x && m.y == n.y;
}

bool operator!=(const SDL_FPoint &m, const SDL_FPoint &n) {
  return !(m == n); // 复用 == 的实现
}

uint8_t direction(const SDL_FPoint &m, const SDL_FPoint &n) {
  bool left = (m.x < n.x);
  bool right = (m.x > n.x);
  bool up = (m.y < n.y);
  bool down = (m.y > n.y);
  DIRECTION direction;
  if (left && up) {
    direction = DIRECTION::UPLEFT;
  } else if (right && up) {
    direction = DIRECTION::UPRIGHT;
  } else if (left && down) {
    direction = DIRECTION::DOWNLEFT;
  } else if (right && down) {
    direction = DIRECTION::DOWNRIGHT;
  } else if (left) {
    direction = DIRECTION::LEFT;
  } else if (right) {
    direction = DIRECTION::RIGHT;
  } else if (up) {
    direction = DIRECTION::UP;
  } else if (down) {
    direction = DIRECTION::DOWN;
  }
  return (uint8_t)direction;
}

uint16_t distance(const SDL_FPoint &m, const SDL_FPoint &n) {
  auto dx = m.x - n.x;
  auto dy = m.y - n.y;
  return std::round(std::sqrt(dx * dx + dy * dy));
}