#pragma once

#include <cstdint>
struct NetEvent {
  //   networkEvent
  static void inScene(uint32_t scene, uint32_t seed, uint64_t hId,
                      uint64_t cId);
  static void heroMove(uint8_t por, uint8_t level, uint8_t x, uint8_t y);
  static void heroGoal(uint8_t por, uint8_t type, uint8_t level, uint8_t x,
                       uint8_t y);
  static void heroRecruit(uint8_t por, uint8_t level, uint8_t x, uint8_t y);
  static void heroDismiss(uint8_t por);
  static void heroTeleport(uint8_t por, uint8_t level, uint8_t x, uint8_t y);
  static void endTurn(uint64_t cId);
};