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

struct NetClient {
  uint64_t id;
  sockaddr_in addr; // 客户端地址
  bool sceneMaster;
  uint8_t scene;
  uint8_t playerId;
  uint64_t heartbeat;
};

struct NetWork {
  static inline std::flat_map<uint64_t, NetClient> clients;
  static inline uint64_t cId;

  static void init();
  static void run();

  static bool sendUDP(const uint8_t *data, size_t len, uint64_t cId);
  static bool sendUDP(const uint8_t *data, size_t len, uint32_t ip,
                      uint16_t port);
  static bool sendUDP(const uint8_t *data, size_t len, std::string ip,
                      uint16_t port);
};