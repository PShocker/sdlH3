#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct ArtifactPanelSys {
  static void draw(int32_t x, int32_t y, std::vector<uint16_t> &artifacts,
                   uint8_t index);
  static void drawNum(int32_t x, int32_t y, std::array<std::u16string, 7> &r);
  static uint8_t click(int32_t x, int32_t y);
};