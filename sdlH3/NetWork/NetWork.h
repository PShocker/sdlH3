#pragma once

#include "uv.h"
#include <atomic>
#include <cstdint>
#include <flat_map>
#include <semaphore>
#include <shared_mutex>
#include <string>
#include <utility>
#include <vector>

struct NetWork {
  static void init();
  static void run();

  static bool sendUDP(const uint8_t *data, size_t len, uint32_t ip, uint16_t port);
  static bool sendUDP(const uint8_t *data, size_t len, std::string ip, uint16_t port);
};