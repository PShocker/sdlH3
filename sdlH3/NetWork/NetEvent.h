#pragma once

#include <cstdint>
struct NetEvent {
  //   networkEvent
  static void InScene(uint32_t scene);
  static void HeroMove(uint8_t por, uint8_t level, uint8_t x, uint8_t y);
  static void HeroTeleport(uint8_t por, uint8_t level, uint8_t x, uint8_t y);
};