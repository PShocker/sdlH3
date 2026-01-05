#pragma once

#include "SDL3/SDL_pixels.h"
#include <cstdint>
#include <string>
struct FreeTypeSys {
  static bool init(uint8_t i);
  static void setSize(uint8_t i);
  static void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  static float strWidth(const std::u16string &str);
  static float strWidth(int num);

  static void draw(float x, float y, const std::u16string &str);
  static void draw(float x, float y, const int num);
  static void drawCenter(float x, float y, const std::u16string &str);
  static void drawCenter(float x, float y, const int num);
  static void drawLeft(float x, float y, const std::u16string &str);
  static void drawLeft(float x, float y, const int num);

  static std::u16string str(int num);
  static std::u16string str(const char *u8Str);
};