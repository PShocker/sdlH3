#pragma once

#include "NetWork/MushRoom.h"
#include "uv.h"
#include <atomic>
#include <cstdint>
#include <flat_map>
#include <shared_mutex>
#include <string>
#include <utility>
#include <vector>

struct NetWork {
  // key:ip,port
  static inline std::flat_map<std::pair<uint32_t, uint16_t>, ipClient> clients;
  static inline std::shared_mutex clients_mutex; // 读写锁
  static inline std::flat_map<uint32_t, std::pair<uint32_t, uint16_t>> hosts;
  static inline std::shared_mutex hosts_mutex; // 读写锁
  static inline std::atomic<uint32_t> scene = 0;
  static inline std::atomic<bool> isHost = false;
  static inline uint32_t heartbeat_interval = 0;

  static inline std::vector<
      std::pair<std::pair<uint32_t, uint16_t>, NetworkPacket *>>
      sendVector;
  static inline std::shared_mutex send_mutex; // 读写锁
  static inline std::vector<NetworkPacket *> recvVector;
  static inline std::shared_mutex recv_mutex; // 读写锁

  static inline uv_async_t async_handle;

  static void init();

  static void run();
  
  static void sayExit();

  static bool sendUDP(uint8_t *data, size_t len, uint32_t ip, uint16_t port);
  static bool sendUDP(uint8_t *data, size_t len, std::string ip, uint16_t port);
};