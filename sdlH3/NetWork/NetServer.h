#pragma once

#include "uv.h"
#include <cstdint>
struct NetServer {
  static void sendLogin(uint64_t cId);
  static void sendInScene(uint64_t cId, uint32_t scene_id, uint64_t scene_host);
  static void sendHeroMove(uint64_t cId, uint8_t por, uint8_t x, uint8_t y);
  static void sendHeroTeleport(uint64_t cId, uint8_t por, uint8_t level,
                               uint8_t x, uint8_t y);
  static void handlePacket(uint64_t cId, void *buf);
};