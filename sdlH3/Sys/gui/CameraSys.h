#pragma once

#include <cstdint>
struct CameraSys {
  static void fixViewPort();
  static bool run();
  static void focus(int32_t x, int32_t y);
};