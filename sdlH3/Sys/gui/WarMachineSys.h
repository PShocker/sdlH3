#pragma once

#include <cstdint>
struct WarMachineSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool keyUp(uint16_t key);

  static void warAnimate(uint64_t &warFrameTime, uint64_t &warFrameIndex,
                         uint64_t &warGroup, uint16_t warId);
};