#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <string>
struct HeroScrSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool leftMouseDown(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static std::vector<std::pair<uint8_t, int8_t>>
  heroArtifactAbility(HeroComp &hComp, uint8_t i);
  static int32_t heroPrimAbility(HeroComp &hComp, uint8_t i);
  static int32_t heroMaxMana(HeroComp &hComp);
  static int32_t heroMor(HeroComp &hComp);
  static int32_t heroLuk(HeroComp &hComp);
  static int32_t heroSight(HeroComp &hComp);

  static void showResConfirm(bool leftClick, uint16_t i);
  static void showArtifactComfirm(uint16_t i);
  static void showPrimComfirm(bool leftClick, uint16_t i);
  static void showSpeConfirm(bool leftClick, uint16_t i);
  static void showLukComfirm(bool leftClick, HeroComp &hComp);
  static void showLukComfirm(bool leftClick);
  static void showMorComfirm(bool leftClick, HeroComp &hComp);
  static void showMorComfirm(bool leftClick);
  static void showExpComfirm(bool leftClick, HeroComp &hComp);
  static void showExpComfirm(bool leftClick);
  static void showManaComfirm(bool leftClick);
  static void showManaComfirm(bool leftClick, HeroComp &hComp);
  static void showSecSkiComfirm(bool leftClick, uint16_t id, uint16_t i);
  static void showHeroBiosComfirm(bool leftClick, uint16_t i);
};