#pragma once

#include "SDL3/SDL_rect.h"
#include <any>
#include <array>
#include <cstdint>
#include <flat_map>
#include <map>
#include <set>
#include <string>
#include <vector>

struct CreatureSetAttribute {
  uint32_t hitPoint;
  int32_t speed;
  int32_t attack;
  int32_t defense;
  int32_t maxDamage;
  int32_t minDamage;
  int32_t shots;
};

struct CreatureSetSound {
  std::string attack;
  std::string defend;
  std::string killed;
  std::string move;
  std::string shoot;
  std::string wince;
};

struct CreatureSetGraphics {
  std::string animation;
  std::string missile;
  std::string adventure;
};

struct CreatureSetSpell {
  uint8_t type;       // 魔法种类
  uint8_t power;      // 魔法强度
  uint8_t level;      // 魔法等级
  uint8_t spellPoint; // 释放次数
};

struct CreatureSetSpellEx {
  uint8_t type;  // 魔法种类
  uint8_t power; // 魔法强度
  uint8_t level; // 魔法等级
  float rate;    // 触发概率
};

struct CreatureSetI {
  uint16_t index;
  uint8_t level;
  bool female;
  uint8_t faction;
  std::vector<uint16_t> upgrades;
  CreatureSetGraphics graphics;
  CreatureSetSound sounds;
  CreatureSetAttribute attribute;
  std::flat_map<uint8_t, std::any> abilities;
  uint32_t growth;
  uint32_t experience;
  std::array<uint32_t, 7> cost;
  bool hasDoubleWeek;
};

struct HeroSetSpec {
  uint8_t id;
  uint8_t subId;
  int32_t val;
};

struct HeroSetI {
  uint8_t index;
  uint8_t clasz; // class
  bool female;
  std::vector<std::pair<uint8_t, uint8_t>> secSkill;
  std::vector<std::pair<uint8_t, uint8_t>> defaultCre;
  std::string smallPor;
  std::string largePor;
  std::vector<HeroSetSpec> spec;
  uint64_t experience;
  std::set<uint8_t> spells;
};

struct SpellAdventure {
  uint8_t goalType;
  uint8_t cursor;
  uint8_t range;
};

struct SpellI {
  uint8_t index;
  std::array<bool, 4> school;
  std::array<uint32_t, 4> manaCost;
  uint8_t level;
  uint8_t type;
  void (*func)(std::any);
  std::any extra;
};

struct ArtifactBonus {
  uint8_t src;  //
  uint8_t type; // Bonus type, corresponds to Enum::ARTIFACT_BONUS_TYPE
  uint8_t
      subType; // Subtype, e.g., PRIMARY_SKILL_ATTACK, SPELL_SCHOOL_FIRE, etc.
  int32_t val; // Bonus value
};

struct AdventureBonus {
  uint8_t src;  //
  uint8_t type; // Bonus type, corresponds to Enum::ARTIFACT_BONUS_TYPE
  uint8_t
      subType; // Subtype, e.g., PRIMARY_SKILL_ATTACK, SPELL_SCHOOL_FIRE, etc.
  int32_t val; // Bonus value
};

struct ArtifactI {
  uint8_t index; // Artifact ID, corresponds to Enum::ARTIFACT_ID
  std::vector<ArtifactBonus> bonus; // List of bonuses provided by the artifact
  uint32_t experience;              // Experience provided by the artifact
  uint32_t cost;                    // Purchase cost,Only Gold
  std::array<bool, 19> slot;        // Equip slots [0-18]
  std::vector<uint8_t> components;  // Combined artifact component IDs
};

struct FactionBuildIncome {
  uint32_t id;
  uint32_t minVal;
  uint32_t maxVal;
  uint8_t frequency;
};

struct FactionBuildBonus {
  uint32_t id;
  uint32_t subId;
  int32_t val;
  bool forceVisit;
  std::optional<uint8_t> frequency;
  std::optional<uint32_t> strIndex;
};

struct FactionBuild {
  int32_t id;
  std::string animation;
  int32_t x;
  int32_t y;
  int32_t z;
  std::string border;
  std::string area;
  std::string icon;
  std::vector<int32_t> require;
  std::array<uint32_t, 7> cost;
  std::vector<FactionBuildIncome> income;
  std::optional<int32_t> upgrades;
  bool autoMode;
  std::vector<FactionBuildBonus> bonus;
};

struct FactionSetI {
  uint8_t index;
  uint8_t nativeTerrain;
  std::array<std::string, 2> creatureBackground;
  std::vector<std::pair<std::string, SDL_FPoint>> puzzleMap;
  std::array<std::string, 5> mapObject;
  std::string musicTheme;
  std::string guildBackground;
  std::string townBackground;
  std::string guildWindow;
  std::string hallBackground;
  std::vector<std::vector<std::vector<int32_t>>> hallSlots;
  std::vector<uint16_t> blacksmith;
  std::vector<FactionBuild> builds;
};

struct ObjectSetSound {
  std::string ambient;
  std::string visit;
  std::vector<std::string> removal;
};

struct ObjectSetI {
  uint8_t index;
  ObjectSetSound sound;
  std::vector<std::pair<uint16_t, uint32_t>> guards; // <creatureType, amount>
  std::vector<uint16_t> creatures; // 生物类型ID列表，支持多级兵种
};

struct HeroClazz {
  uint8_t id;
  std::vector<uint8_t> lowPrimRate;
  std::vector<uint8_t> highPrimRate;
  std::vector<uint8_t> defaultPrim;
  std::vector<uint8_t> secSkillRate;
};