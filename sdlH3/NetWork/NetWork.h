#pragma once

#include "NetWork/packet/MushRoom.h"
#include <cstdint>
struct NetWork {
  static void init();
  static bool sendUDP(const uint8_t *data, size_t length, ipClient &client);
};