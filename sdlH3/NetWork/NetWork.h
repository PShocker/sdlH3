#pragma once

#include "NetWork/packet/MushRoom.h"
#include <cstdint>
#include <string>
struct NetWork {
  static void init();
  static bool sendUDP(uint8_t *data, size_t len, uint32_t ip, uint16_t port);
  static bool sendUDP(uint8_t *data, size_t len, std::string ip, uint16_t port);
};