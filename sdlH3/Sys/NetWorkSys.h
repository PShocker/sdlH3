#pragma once

#include "NetWork/MushRoom.h"
#include <cstdint>
#include <flat_map>
#include <functional>

enum NETWORL_EVENT_TYPE : uint8_t {
  NETWORK_EVENT_NONE = 12,
  NETWORK_EVENT_HOST_ASK,
  NETWORK_EVENT_HOST,
  NETWORK_EVENT_SCENE_EXIT,
  NETWORK_EVENT_HERO_MOVE,
};

// 广播通知所有人，自己成为主机
struct NetworkHostAsk {
  uint32_t scene;
};

struct NetworkHost {
  uint32_t scene;
  uint32_t ip;
  uint16_t port;
};

struct NetWorkSys {
  static void queuePacket(NetworkPacket *packet);

  static void sendPacket();
  static void recvPacket();

  static void init();
  static void run();

  static inline std::flat_map<uint16_t,
                              std::function<void(NetworkPacket *packet)>>
      recvHandler;
};