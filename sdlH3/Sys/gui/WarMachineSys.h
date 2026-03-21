#pragma once

#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
struct WarMachineSys {
  static inline std::vector<Button> buttons;

  static void init();

  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool keyUp(uint16_t key);

  static void warAnimate(uint64_t &warFrameTime, uint64_t &warFrameIndex,
                         uint64_t &warGroup, uint16_t warId);
};