#pragma once

#include "Comp/HeroComp.h"
#include <cstdint>
#include <optional>
#include <string>
struct HeroScrSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool leftMouseDown(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static int32_t heroPrim(HeroComp &hComp, uint8_t i);
  static int32_t heroMaxMana(HeroComp &hComp);
  static int32_t heroMor(HeroComp &hComp);
  static int32_t heroLuk(HeroComp &hComp);
  static int32_t heroSight(HeroComp &hComp);

  static int8_t heroSecLevel(HeroComp &hComp, uint8_t i);

  static void showResConfirm(uint8_t clickType, uint16_t i);
  static void showArtifactComfirm(uint16_t i);
  static void showPrimComfirm(uint8_t clickType, uint16_t i);
  static void showSpeConfirm(uint8_t clickType, uint16_t i);
  static void showLukComfirm(uint8_t clickType, HeroComp &hComp);
  static void showLukComfirm(uint8_t clickType);
  static void showMorComfirm(uint8_t clickType, HeroComp &hComp);
  static void showMorComfirm(uint8_t clickType);
  static void showExpComfirm(uint8_t clickType, HeroComp &hComp);
  static void showExpComfirm(uint8_t clickType);
  static void showManaComfirm(uint8_t clickType);
  static void showManaComfirm(uint8_t clickType, HeroComp &hComp);
  static void showSecSkiComfirm(uint8_t clickType, uint16_t id, uint16_t i);
  static void showHeroBiosComfirm(uint8_t clickType, uint16_t i);
};