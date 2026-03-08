#pragma once

#include <cstdint>

enum NETWORL_EVENT_TYPE : uint8_t {
  NETWORK_EVENT_NONE,
  NETWORK_EVENT_HOST,
  NETWORK_EVENT_HERO_MOVE,
};

struct NetWorkSys {
  static void enterScene(uint32_t scene);
  static void run();
};