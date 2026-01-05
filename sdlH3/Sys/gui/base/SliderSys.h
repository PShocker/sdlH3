#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <utility>
struct SliderSys {
  static void drawHor(int32_t x, int32_t y, int32_t length, float p);
  static uint32_t clickHor(int32_t x, int32_t y, int32_t length, uint32_t num,
                           uint32_t count);

  static void drawVer(int32_t x, int32_t y, int32_t length, float p);
  static uint32_t clickVer(int32_t x, int32_t y, int32_t length, uint32_t num,
                           uint32_t count);
};