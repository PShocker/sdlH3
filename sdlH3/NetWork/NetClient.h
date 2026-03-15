#pragma once

#include "uv.h"
#include <cstdint>
struct NetClient {
  static void sendHeartBeat(uv_timer_t *handle);
  static void sendLogin();
  static void sendInScene(uint32_t scene);
  static void sendExit();
  static void sendHeroMove(uint8_t por, uint8_t x, uint8_t y);
};