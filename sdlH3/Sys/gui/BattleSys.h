#pragma once

#include "Comp/HeroComp.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <utility>
#include <vector>

enum BATTLE_FIELD_TYPE {
  BATTLE_FIELD_TYPE_TOWN,
  BATTLE_FIELD_TYPE_HERO,
  BATTLE_FIELD_TYPE_MONSTER,
};

struct BattleScrn {
  uint8_t field;
  uint8_t type;
  bool tactics;
  std::vector<uint8_t> siege;
  std::vector<uint8_t> siegeBroken;
  std::vector<uint8_t> moat;
};

struct BattleHero {
  HeroComp *hComp;
  std::array<uint8_t, 4> primSkills;
  std::vector<std::pair<uint8_t, uint8_t>> secSkills;
  std::set<uint8_t> spells;
};

struct BattleCreature {
  uint16_t id;
  uint8_t action;
  uint32_t frameIndex;
  uint32_t frameTime;
  CreatureSetAttribute attribute;
  std::flat_map<uint8_t, std::any> abilities;
  uint32_t num;
  uint32_t pos;
  std::vector<std::pair<uint8_t, int32_t>> spelled;
  uint8_t playerId;
};

struct BattleSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);
};