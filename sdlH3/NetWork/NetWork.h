#pragma once

#include "NetWork/MushRoom.h"
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

  static inline std::binary_semaphore sem{0};
  // key:ip,port
  static inline std::atomic<uint32_t> scene = 0;
  static inline std::atomic<bool> isHost = false;
  static inline uint32_t heartbeat_interval = 0;

  static inline std::vector<NetworkPacket *> sendVector;
  static inline std::shared_mutex send_mutex; // 读写锁
  static inline std::vector<NetworkPacket *> recvVector;
  static inline std::shared_mutex recv_mutex; // 读写锁

  static inline uv_async_t async_handle;

  static void init();

  static void run();

  static void sayExit();

  static bool sendUDP(uint8_t *data, size_t len, uint32_t ip, uint16_t port);
  static bool sendUDP(uint8_t *data, size_t len, std::string ip, uint16_t port);

  static void acquire();
  static void release();
};