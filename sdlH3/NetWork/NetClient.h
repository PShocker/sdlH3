#pragma once

#include "uv.h"
#include <cstdint>
struct NetClient {
  static void sendHeartBeat(uv_timer_t *handle);
  static void sendLogin();
  static void sendInScene(uint32_t scene);
  static void sendExit();
};