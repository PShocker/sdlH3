#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
struct SpellSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static std::pair<uint8_t, uint8_t> spellLevel(HeroComp *heroComp, uint8_t id);
  static void showSpellComfirm(uint8_t clickType, uint16_t id, uint16_t i);
};