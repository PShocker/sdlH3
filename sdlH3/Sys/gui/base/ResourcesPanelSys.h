#pragma once

#include <array>
#include <cstdint>
#include <string>
struct ResourcesPanelSys {
  static void draw(int32_t x, int32_t y, uint8_t index);
  static void drawNum(int32_t x, int32_t y, std::array<std::u16string, 7> &r);
  static uint8_t click(int32_t x, int32_t y);
};