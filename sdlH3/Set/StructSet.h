#pragma once

#include <any>
#include <array>
#include <cstdint>
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
  uint8_t index;
  uint8_t level;
  bool female;
  uint8_t faction;
  std::vector<uint16_t> upgrades;
  CreatureSetGraphics graphics;
  CreatureSetSound sounds;
  CreatureSetAttribute attribute;
  std::map<uint8_t, std::any> abilities;
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

struct SpellData {
  uint8_t index;
  uint8_t school;
  std::array<uint8_t, 4> cost;
  uint8_t level;
  uint8_t type;
  void (*func)(std::any);
  std::any extra;
};
