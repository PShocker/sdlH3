#pragma once

#include "protocol/Protocol.h"
#include "uv.h"
#include <atomic>
#include <cstdint>
#include <flat_map>
#include <flat_set>
#include <semaphore>
#include <shared_mutex>
#include <string>
#include <utility>
#include <vector>

struct ClientInfo {
  uint64_t id;
  sockaddr_in addr; // 客户端地址
  bool sceneHost;
  uint8_t scene;
  uint8_t playerId;
  uint64_t heartbeat;
};

struct NetWork {
  static inline std::string host_ip = "127.0.0.1";
  static inline uint32_t host_port;
  const static uint8_t heartbeat_interval = 5;
  static inline flatbuffers::FlatBufferBuilder builder;
  static inline uint32_t seed = std::time(0);

  static inline std::flat_map<uint64_t, ClientInfo> clients;
  static inline std::flat_map<uint32_t, std::flat_set<uint64_t>> sceneClients;
  static inline std::flat_map<uint32_t, uint64_t> sceneHost;
  static inline uint64_t cId;

  static void init(std::string host_ip, uint32_t host_port);
  static void init();
  static void run();

  static bool sendUDP(const uint8_t *data, size_t len, uint64_t cId);
  static bool sendUDP(const uint8_t *data, size_t len, uint32_t ip,
                      uint16_t port);
  static bool sendUDP(const uint8_t *data, size_t len, std::string ip,
                      uint16_t port);
};