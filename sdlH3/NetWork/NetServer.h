#pragma once

#include "NetWork/protocol/Protocol.h"
#include "uv.h"
#include <cstdint>
struct NetServer {
  static void sendInScene(uint64_t cId, uint32_t seed, uint32_t scene_id,
                          uint64_t scene_host);
  static void sendHeroMove(uint64_t cId, uint8_t por, uint8_t level, uint8_t x,
                           uint8_t y);
  static void sendHeroGoal(uint64_t cId, uint8_t por, uint8_t type,
                           uint8_t level, uint8_t x, uint8_t y);
  static void sendHeroRecruit(uint64_t cId, uint8_t por, uint8_t level,
                              uint8_t x, uint8_t y);
  static void sendHeroDismiss(uint64_t cId, uint8_t por);
  static void sendHeroTeleport(uint64_t cId, uint8_t por, uint8_t level,
                               uint8_t x, uint8_t y);
  static void sendOutScene(uint64_t cId);

  static void dispatchPacket(uint64_t cId, const NetPacket *packet);
  static void recordPacket(void *buf, ssize_t nread);
  static void handlePacket(uint64_t cId, void *buf, ssize_t nread);
  
  static void checkHeartBeat();
};