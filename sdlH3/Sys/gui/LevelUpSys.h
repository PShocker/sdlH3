#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
struct LevelUpSys {
  static bool run();
  static bool keyUp(uint16_t key);

  static bool prepareLvlUp(HeroComp &heroComp);
  static void studySecSki(HeroComp &heroComp,uint8_t sId);

  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
};