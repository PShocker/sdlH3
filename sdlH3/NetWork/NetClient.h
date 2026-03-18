#pragma once

#include "uv.h"
#include <cstdint>
struct NetClient {
  static void sendHeartBeat();
  static void sendLogin();
  static void sendInScene(uint32_t scene);
  static void sendExit();
  static void sendHeroMove(uint8_t por, uint8_t level, uint8_t x, uint8_t y);
  static void sendHeroGoal(uint8_t por, uint8_t type, uint8_t level, uint8_t x,
                           uint8_t y);
  static void sendHeroRecruit(uint8_t por, uint8_t level, uint8_t x, uint8_t y);
  static void sendHeroDismiss(uint8_t por);
  static void sendHeroTeleport(uint8_t por, uint8_t level, uint8_t x,
                               uint8_t y);
};