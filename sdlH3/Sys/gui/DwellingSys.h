#pragma once

#include <cstdint>
struct DwellingSys {
  static bool run();
  static void drawCreature(float x, float y, uint16_t id, uint16_t group,
                           uint16_t index, uint8_t colorType);
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static uint32_t maxCount();
};