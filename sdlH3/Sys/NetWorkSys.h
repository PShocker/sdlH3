#pragma once

#include "NetWork/MushRoom.h"
#include <cstdint>
#include <flat_map>
#include <functional>

enum NETWORL_EVENT_TYPE : uint8_t {
  NETWORK_EVENT_NONE = 8,
  NETWORK_EVENT_HOST,
  NETWORK_EVENT_HOST_EXIT,
  NETWORK_EVENT_SCENE_EXIT,
  NETWORK_EVENT_HERO_MOVE,
};

#pragma pack(push, 1)
// 广播通知所有人，自己成为主机
struct NetworkHost {
  uint32_t scene;
};

struct NetworkHostExit {
  uint32_t scene;
};
struct NetworkSceneExit {
  uint32_t scene;
};
#pragma pack(pop)

struct NetWorkSys {
  static void queuePacket(uint32_t ip, uint16_t port, NetworkPacket *packet);

  static void exitScene();
  static void init();
  static void run();

  static inline std::flat_map<uint16_t,
                              std::function<void(NetworkPacket *packet)>>
      recvHandler;
};