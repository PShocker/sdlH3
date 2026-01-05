#pragma once

#include <cstdint>
#include <vector>
struct WarMachineFacSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
  static void drawMachine(float x, float y, uint16_t id, uint16_t group,
                           uint16_t index, uint8_t colorType);
  static uint32_t maxCount();
};