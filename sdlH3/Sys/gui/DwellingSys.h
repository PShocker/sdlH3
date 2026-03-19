#pragma once

#include "SDL3/SDL_rect.h"
#include "Sys/gui/AdvMapSys.h"
#include <cstdint>
#include <vector>
struct DwellingSys {
  static inline std::vector<Button> buttons;

  static void init();
  static bool run();
  static void drawCreature(float x, float y, uint16_t id, uint16_t group,
                           uint16_t index, uint8_t colorType);
  static void drawCreatureBak(float x, float y, uint16_t id, uint16_t group,
                              uint16_t index, uint8_t colorType);
  static void drawCreatureBak2(float x, float y, uint16_t id, uint16_t group,
                               uint16_t index, uint8_t colorType);
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static uint32_t maxCount();
  static std::vector<SDL_Point> creatruePos(uint8_t size);
};