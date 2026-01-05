#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <utility>
struct ArtifactsOfHeroSys {
  static void drawBackPack(HeroComp *heroComp, int32_t x, int32_t y,
                           uint8_t index = 0);
  static void drawBackPackBorder(int32_t x, int32_t y, uint8_t index);
  static void drawEquip(HeroComp *heroComp, int32_t x, int32_t y);
  static void drawEquipBorder(int32_t x, int32_t y, uint8_t index);
  static void drawArtSlot(uint8_t artId, int32_t x, int32_t y);
  static std::pair<uint8_t, uint16_t>
  clickBackPack(HeroComp *heroComp, int32_t x, int32_t y, uint8_t index = 0);
  static std::pair<uint8_t, uint16_t> clickEquip(HeroComp *heroComp, int32_t x,
                                                 int32_t y);
  static int8_t clickPage(HeroComp *heroComp, int32_t x, int32_t y,
                          uint8_t index = 0);
};