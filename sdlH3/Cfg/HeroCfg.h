#pragma once

#include "Cfg/CreatureCfg.h"
#include "Cfg/SpellCfg.h"
#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
struct HeroCfg {

  enum class Specialty : uint8_t {
    // 技能类特长
    SECONDARY_SKILL,      // 对应二级技能 (如：archery, armorer, logistics等)
    SPECIFIC_SPELL_POWER, // 特定法术效果增强 (firstAid, resurrection等)
    SPECIAL_SPELL_LEV,    // 特定法术等级提升 (frostRing, chainLightning等)
    SPECIAL_PECULIAR_ENCHANT,    // 特殊附魔效果 (weakness, prayer, stoneSkin等)
    SPECIAL_FIXED_VALUE_ENCHANT, // 固定值附魔 (fortune等)

    // 生物类特长
    CREATURE, // 特定生物增强

    // 属性类特长
    PRIMARY_SKILL,                 // 主要属性 (攻击、防御)
    GENERAL_DAMAGE_PREMY,          // 通用伤害加成
    GENERAL_DAMAGE_REDUCTION,      // 通用伤害减免
    MAGIC_RESISTANCE,              // 魔法抗性
    MANA_REGENERATION,             // 法力恢复
    MANA_PER_KNOWLEDGE_PERCENTAGE, // 知识百分比增加法力
    LEARN_BATTLE_SPELL_CHANCE,     // 战斗中学法术几率
    SPELL_DAMAGE,                  // 法术伤害
    UNDEAD_RAISE_PERCENTAGE,       // 亡灵召唤百分比
    STACKS_SPEED,                  // 部队速度
    MOVEMENT,                      // 移动力
    PERCENTAGE_DAMAGE_BOOST,       // 百分比伤害提升

    // 资源类特长
    GENERATE_RESOURCE, // 资源生成 (gold, mercury, sulfur等)
    ESTATES,           // 理财术相关

    // 特殊类特长
    SPECIAL_UPGRADE,           // 特殊升级 (如：archer升级为sharpshooter)
    SPECIFIC_SPELL_DAMAGE,     // 特定法术伤害 (fireWall, magicArrow等)
    SPECIAL_ADD_VALUE_ENCHANT, // 特殊数值附加附魔 (disruptingRay等)
    CREATURE_DAMAGE,           // 生物伤害

    // 复合类特长
    COMPOSITE, // 复合特长 (多个效果组合)

    NONE, // 无特长
  };

  enum class SecondarySkill : uint8_t {
    PATHFINDING = 0,
    ARCHERY = 1,
    LOGISTICS = 2,
    SCOUTING = 3,
    DIPLOMACY = 4,
    NAVIGATION = 5,
    LEADERSHIP = 6,
    WISDOM = 7,
    MYSTICISM = 8,
    LUCK = 9,
    BALLISTICS = 10,
    EAGLE_EYE = 11,
    NECROMANCY = 12,
    ESTATES = 13,
    FIRE_MAGIC = 14,
    AIR_MAGIC = 15,
    WATER_MAGIC = 16,
    EARTH_MAGIC = 17,
    SCHOLAR = 18,
    TACTICS = 19,
    ARTILLERY = 20,
    LEARNING = 21,
    OFFENCE = 22,
    ARMORER = 23,
    INTELLIGENCE = 24,
    SORCERY = 25,
    RESISTANCE = 26,
    FIRST_AID = 27
  };

  const static inline std::vector<std::pair<uint8_t, std::vector<int32_t>>>
      heroSpec = {
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::ARCHERY, 5}},
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::ARCHER,
            (uint8_t)CreatureCfg::Creature::MARKSMAN, 5}},
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::GRIFFIN,
            (uint8_t)CreatureCfg::Creature::ROYAL_GRIFFIN, 5}},
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::NAVIGATION, 5}},
          {(uint8_t)Specialty::GENERATE_RESOURCE,
           {(uint8_t)6, 350}}, // lordHaart
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::SWORDSMAN,
            (uint8_t)CreatureCfg::Creature::CRUSADER, 5}}, // sorsha
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::BALLISTA, 5}}, // christian
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::CAVALIER,
            (uint8_t)CreatureCfg::Creature::CHAMPION, 5}}, // tyris
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::FIRST_AID, 5}}, // tyris
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::Bless, 5}}, // adela
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::Weakness, 5}}, // cuthbert
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::FrostRing, 5}}, // adelaide
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::MONK,
            (uint8_t)CreatureCfg::Creature::ZEALOT, 5}}, // ingham
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::EAGLE_EYE, 5}}, // sanya
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::Prayer, 5}},                    // loynis
          {(uint8_t)Specialty::GENERATE_RESOURCE, {(uint8_t)6, 350}}, // caitlin
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::ARMORER, 5}}, // mephala
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::DWARF,
            (uint8_t)CreatureCfg::Creature::BATTLE_DWARF, 5}},        // ufretin
          {(uint8_t)Specialty::GENERATE_RESOURCE, {(uint8_t)6, 350}}, // jenova
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::DENDROID_GUARD,
            (uint8_t)CreatureCfg::Creature::DENDROID_SOLDIER, 5}}, // ryland
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::RESISTANCE, 5}}, // thorgrim
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::WOOD_ELF,
            (uint8_t)CreatureCfg::Creature::GRAND_ELF, 5}}, // ivor
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::UNICORN,
            (uint8_t)CreatureCfg::Creature::WAR_UNICORN, 5}}, // clancy
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::LOGISTICS, 5}}, // kyrre
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::Slayer, 5}}, // cuthbert
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::Cure, 5}}, // uland
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::INTELLIGENCE, 5}}, // elleshar
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::FIRST_AID, 5}}, // gem
          {(uint8_t)Specialty::SECONDARY_SKILL,
           {(uint8_t)SecondarySkill::EAGLE_EYE, 5}}, // malcom
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::Fortune, 5}}, // melodia
          {(uint8_t)Specialty::SPECIFIC_SPELL_POWER,
           {(uint8_t)SpellCfg::Spell::IceBolt, 5}}, // alagar
          {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::PEGASUS,
            (uint8_t)CreatureCfg::Creature::SILVER_PEGASUS, 5}}, // aeris
             {(uint8_t)Specialty::CREATURE,
           {(uint8_t)CreatureCfg::Creature::STONE_GARGOYLE,
            (uint8_t)CreatureCfg::Creature::OBSIDIAN_GARGOYLE, 5}}, // piquedram
  };

  enum class Pro : uint8_t {
    KNIGHT = 0,
    CLERIC = 1,
    RANGER = 2,
    DRUID = 3,
    ALCHEMIST = 4,
    WIZARD = 5,
    DEMON = 6,
    HERETIC = 7,
    DEATH_KNIGHT = 8,
    NECROMANCER = 9,
    OVERLORD = 10,
    WARLOCK = 11,
    BARBARIAN = 12,
    BATTLE_MAGE = 13,
    BEASTMASTER = 14,
    WITCH = 15,
    ELEMENTALIST = 16,
    PLANESWALKER = 17,
  };

  enum class SecondaryLevel : uint8_t { BASIC = 0, ADVANCED = 1, EXPERT = 2 };

  const static inline std::vector<std::vector<std::pair<uint8_t, uint8_t>>>
      heroSecSkills = {
          // 0-23: 基础英雄
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 0
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 1
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 2
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::NAVIGATION,
            (uint8_t)SecondaryLevel::BASIC}}, // 3
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ESTATES,
            (uint8_t)SecondaryLevel::BASIC}}, // 4
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 5
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 6
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 7
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRST_AID,
            (uint8_t)SecondaryLevel::BASIC}}, // 8
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::DIPLOMACY,
            (uint8_t)SecondaryLevel::BASIC}}, // 9
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ESTATES,
            (uint8_t)SecondaryLevel::BASIC}}, // 10
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 11
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 12
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 13
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 14
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 15
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 16
          {{(uint8_t)SecondarySkill::LUCK, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 17
          {{(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 18
          {{(uint8_t)SecondarySkill::DIPLOMACY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 19
          {{(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 20
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 21
          {{(uint8_t)SecondarySkill::PATHFINDING,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 22
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LOGISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 23

          // 24-31: Druid英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 24
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::ADVANCED},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 25
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 26
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRST_AID,
            (uint8_t)SecondaryLevel::BASIC}}, // 27
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 28
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LUCK,
            (uint8_t)SecondaryLevel::BASIC}}, // 29
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 30
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 31

          // 32-39: 更多Druid相关英雄
          {{(uint8_t)SecondarySkill::SCOUTING, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 32
          {{(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 33
          {{(uint8_t)SecondarySkill::MYSTICISM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 34
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 35
          {{(uint8_t)SecondarySkill::MYSTICISM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 36
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 37
          {{(uint8_t)SecondarySkill::MYSTICISM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 38
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 39

          // 40-47: Wizard英雄
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 40
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 41
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 42
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 43
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 44
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 45
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::DIPLOMACY,
            (uint8_t)SecondaryLevel::BASIC}}, // 46
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 47

          // 48-55: 更多Wizard相关英雄
          {{(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 48
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 49
          {{(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 50
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 51
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 52
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 53
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LOGISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 54
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 55

          // 56-63: Heretic英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 56
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 57
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 58
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 59
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 60
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 61
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 62
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 63

          // 64-71: Death Knight英雄
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 64
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 65
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 66
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 67
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 68
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 69
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 70
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 71

          // 72-79: Necromancer英雄
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 72
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::BASIC}}, // 73
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 74
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 75
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 76
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 77
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 78
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 79

          // 80-87: Overlord英雄
          {{(uint8_t)SecondarySkill::SCOUTING, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 80
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 81
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 82
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 83
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 84
          {{(uint8_t)SecondarySkill::LOGISTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 85
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 86
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 87

          // 88-95: Warlock英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 88
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 89
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 90
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 91
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 92
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 93
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 94
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 95

          // 96-103: 更多Warlock相关英雄
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 96
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 97
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 98
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 99
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::PATHFINDING,
            (uint8_t)SecondaryLevel::BASIC}}, // 100
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 101
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 102
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 103

          // 104-111: Battlemage英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 104
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 105
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LOGISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 106
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 107
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 108
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 109
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 110
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 111

          // 112-119: Beastmaster英雄
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 112
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 113
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 114
          {{(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 115
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 116
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::PATHFINDING,
            (uint8_t)SecondaryLevel::BASIC}}, // 117
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 118
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 119

          // 120-127: Witch英雄
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 120
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 121
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::NAVIGATION,
            (uint8_t)SecondaryLevel::BASIC}}, // 122
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRST_AID,
            (uint8_t)SecondaryLevel::BASIC}}, // 123
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 124
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 125
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 126
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 127

          // 128-135: Planeswalker英雄
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 128
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 129
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 130
          {{(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 131
          {{(uint8_t)SecondarySkill::LOGISTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 132
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 133
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 134
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 135

          // 136-143: Elementalist英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRE_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 136
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::AIR_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 137
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::WATER_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 138
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EARTH_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 139
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRE_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 140
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::AIR_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 141
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::WATER_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 142
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EARTH_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 143

          // 144-155: 特殊战役英雄
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 144
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRE_MAGIC,
            (uint8_t)SecondaryLevel::EXPERT}}, // 145
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 146
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 147
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 148
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 149
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 150
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 151
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 152
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 153
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 154
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}} // 155
  };

  const static inline std::vector<uint8_t> heroPro = {
      (uint8_t)Pro::KNIGHT,       // orrin (index: 0)
      (uint8_t)Pro::KNIGHT,       // valeska (index: 1)
      (uint8_t)Pro::KNIGHT,       // edric (index: 2)
      (uint8_t)Pro::KNIGHT,       // sylvia (index: 3)
      (uint8_t)Pro::KNIGHT,       // lordHaart (index: 4)
      (uint8_t)Pro::KNIGHT,       // sorsha (index: 5)
      (uint8_t)Pro::KNIGHT,       // christian (index: 6)
      (uint8_t)Pro::KNIGHT,       // tyris (index: 7)
      (uint8_t)Pro::CLERIC,       // rion (index: 8)
      (uint8_t)Pro::CLERIC,       // adela (index: 9)
      (uint8_t)Pro::CLERIC,       // cuthbert (index: 10)
      (uint8_t)Pro::CLERIC,       // adelaide (index: 11)
      (uint8_t)Pro::CLERIC,       // ingham (index: 12)
      (uint8_t)Pro::CLERIC,       // sanya (index: 13)
      (uint8_t)Pro::CLERIC,       // loynis (index: 14)
      (uint8_t)Pro::CLERIC,       // caitlin (index: 15)
      (uint8_t)Pro::RANGER,       // mephala (index: 16)
      (uint8_t)Pro::RANGER,       // ufretin (index: 17)
      (uint8_t)Pro::RANGER,       // jenova (index: 18)
      (uint8_t)Pro::RANGER,       // ryland (index: 19)
      (uint8_t)Pro::RANGER,       // thorgrim (index: 20)
      (uint8_t)Pro::RANGER,       // ivor (index: 21)
      (uint8_t)Pro::RANGER,       // clancy (index: 22)
      (uint8_t)Pro::RANGER,       // kyrre (index: 23)
      (uint8_t)Pro::DRUID,        // coronius (index: 24)
      (uint8_t)Pro::DRUID,        // uland (index: 25)
      (uint8_t)Pro::DRUID,        // elleshar (index: 26)
      (uint8_t)Pro::DRUID,        // gem (index: 27)
      (uint8_t)Pro::DRUID,        // malcom (index: 28)
      (uint8_t)Pro::DRUID,        // melodia (index: 29)
      (uint8_t)Pro::DRUID,        // alagar (index: 30)
      (uint8_t)Pro::DRUID,        // aeris (index: 31)
      (uint8_t)Pro::ALCHEMIST,    // piquedram (index: 32)
      (uint8_t)Pro::ALCHEMIST,    // thane (index: 33)
      (uint8_t)Pro::ALCHEMIST,    // josephine (index: 34)
      (uint8_t)Pro::ALCHEMIST,    // neela (index: 35)
      (uint8_t)Pro::ALCHEMIST,    // torosar (index: 36)
      (uint8_t)Pro::ALCHEMIST,    // fafner (index: 37)
      (uint8_t)Pro::ALCHEMIST,    // rissa (index: 38)
      (uint8_t)Pro::ALCHEMIST,    // iona (index: 39)
      (uint8_t)Pro::WIZARD,       // astral (index: 40)
      (uint8_t)Pro::WIZARD,       // halon (index: 41)
      (uint8_t)Pro::WIZARD,       // serena (index: 42)
      (uint8_t)Pro::WIZARD,       // daremyth (index: 43)
      (uint8_t)Pro::WIZARD,       // theodorus (index: 44)
      (uint8_t)Pro::WIZARD,       // solmyr (index: 45)
      (uint8_t)Pro::WIZARD,       // cyra (index: 46)
      (uint8_t)Pro::WIZARD,       // aine (index: 47)
      (uint8_t)Pro::DEMON,        // fiona (index: 48)
      (uint8_t)Pro::DEMON,        // rashka (index: 49)
      (uint8_t)Pro::DEMON,        // marius (index: 50)
      (uint8_t)Pro::DEMON,        // ignatius (index: 51)
      (uint8_t)Pro::DEMON,        // octavia (index: 52)
      (uint8_t)Pro::DEMON,        // calh (index: 53)
      (uint8_t)Pro::DEMON,        // pyre (index: 54)
      (uint8_t)Pro::DEMON,        // nymus (index: 55)
      (uint8_t)Pro::HERETIC,      // ayden (index: 56)
      (uint8_t)Pro::HERETIC,      // xyron (index: 57)
      (uint8_t)Pro::HERETIC,      // axsis (index: 58)
      (uint8_t)Pro::HERETIC,      // olema (index: 59)
      (uint8_t)Pro::HERETIC,      // calid (index: 60)
      (uint8_t)Pro::HERETIC,      // ash (index: 61)
      (uint8_t)Pro::HERETIC,      // zydar (index: 62)
      (uint8_t)Pro::HERETIC,      // xarfax (index: 63)
      (uint8_t)Pro::DEATH_KNIGHT, // straker (index: 64)
      (uint8_t)Pro::DEATH_KNIGHT, // vokial (index: 65)
      (uint8_t)Pro::DEATH_KNIGHT, // moandor (index: 66)
      (uint8_t)Pro::DEATH_KNIGHT, // charna (index: 67)
      (uint8_t)Pro::DEATH_KNIGHT, // tamika (index: 68)
      (uint8_t)Pro::DEATH_KNIGHT, // isra (index: 69)
      (uint8_t)Pro::DEATH_KNIGHT, // clavius (index: 70)
      (uint8_t)Pro::DEATH_KNIGHT, // galthran (index: 71)
      (uint8_t)Pro::NECROMANCER,  // septienna (index: 72)
      (uint8_t)Pro::NECROMANCER,  // aislinn (index: 73)
      (uint8_t)Pro::NECROMANCER,  // sandro (index: 74)
      (uint8_t)Pro::NECROMANCER,  // nimbus (index: 75)
      (uint8_t)Pro::NECROMANCER,  // thant (index: 76)
      (uint8_t)Pro::NECROMANCER,  // xsi (index: 77)
      (uint8_t)Pro::NECROMANCER,  // vidomina (index: 78)
      (uint8_t)Pro::NECROMANCER,  // nagash (index: 79)
      (uint8_t)Pro::OVERLORD,     // lorelei (index: 80)
      (uint8_t)Pro::OVERLORD,     // arlach (index: 81)
      (uint8_t)Pro::OVERLORD,     // dace (index: 82)
      (uint8_t)Pro::OVERLORD,     // ajit (index: 83)
      (uint8_t)Pro::OVERLORD,     // damacon (index: 84)
      (uint8_t)Pro::OVERLORD,     // gunnar (index: 85)
      (uint8_t)Pro::OVERLORD,     // synca (index: 86)
      (uint8_t)Pro::OVERLORD,     // shakti (index: 87)
      (uint8_t)Pro::WARLOCK,      // alamar (index: 88)
      (uint8_t)Pro::WARLOCK,      // jaegar (index: 89)
      (uint8_t)Pro::WARLOCK,      // malekith (index: 90)
      (uint8_t)Pro::WARLOCK,      // jeddite (index: 91)
      (uint8_t)Pro::WARLOCK,      // geon (index: 92)
      (uint8_t)Pro::WARLOCK,      // deemer (index: 93)
      (uint8_t)Pro::WARLOCK,      // sephinroth (index: 94)
      (uint8_t)Pro::WARLOCK,      // darkstorn (index: 95)
      (uint8_t)Pro::BARBARIAN,    // yog (index: 96)
      (uint8_t)Pro::BARBARIAN,    // gurnisson (index: 97)
      (uint8_t)Pro::BARBARIAN,    // jabarkas (index: 98)
      (uint8_t)Pro::BARBARIAN,    // shiva (index: 99)
      (uint8_t)Pro::BARBARIAN,    // gretchin (index: 100)
      (uint8_t)Pro::BARBARIAN,    // krellion (index: 101)
      (uint8_t)Pro::BARBARIAN,    // cragHack (index: 102)
      (uint8_t)Pro::BARBARIAN,    // tyraxor (index: 103)
      (uint8_t)Pro::BATTLE_MAGE,  // gird (index: 104)
      (uint8_t)Pro::BATTLE_MAGE,  // vey (index: 105)
      (uint8_t)Pro::BATTLE_MAGE,  // dessa (index: 106)
      (uint8_t)Pro::BATTLE_MAGE,  // terek (index: 107)
      (uint8_t)Pro::BATTLE_MAGE,  // zubin (index: 108)
      (uint8_t)Pro::BATTLE_MAGE,  // gundula (index: 109)
      (uint8_t)Pro::BATTLE_MAGE,  // oris (index: 110)
      (uint8_t)Pro::BATTLE_MAGE,  // saurug (index: 111)
      (uint8_t)Pro::BEASTMASTER,  // bron (index: 112)
      (uint8_t)Pro::BEASTMASTER,  // drakon (index: 113)
      (uint8_t)Pro::BEASTMASTER,  // wystan (index: 114)
      (uint8_t)Pro::BEASTMASTER,  // tazar (index: 115)
      (uint8_t)Pro::BEASTMASTER,  // alkin (index: 116)
      (uint8_t)Pro::BEASTMASTER,  // korbac (index: 117)
      (uint8_t)Pro::BEASTMASTER,  // gerwulf (index: 118)
      (uint8_t)Pro::BEASTMASTER,  // broghild (index: 119)
      (uint8_t)Pro::WITCH,        // mirlanda (index: 120)
      (uint8_t)Pro::WITCH,        // rosic (index: 121)
      (uint8_t)Pro::WITCH,        // voy (index: 122)
      (uint8_t)Pro::WITCH,        // verdish (index: 123)
      (uint8_t)Pro::WITCH,        // merist (index: 124)
      (uint8_t)Pro::WITCH,        // styg (index: 125)
      (uint8_t)Pro::WITCH,        // andra (index: 126)
      (uint8_t)Pro::WITCH,        // tiva (index: 127)
      (uint8_t)Pro::PLANESWALKER, // pasis (index: 128)
      (uint8_t)Pro::PLANESWALKER, // thunar (index: 129)
      (uint8_t)Pro::PLANESWALKER, // ignissa (index: 130)
      (uint8_t)Pro::PLANESWALKER, // lacus (index: 131)
      (uint8_t)Pro::PLANESWALKER, // monere (index: 132)
      (uint8_t)Pro::PLANESWALKER, // erdamon (index: 133)
      (uint8_t)Pro::PLANESWALKER, // fiur (index: 134)
      (uint8_t)Pro::PLANESWALKER, // kalt (index: 135)
      (uint8_t)Pro::ELEMENTALIST, // luna (index: 136)
      (uint8_t)Pro::ELEMENTALIST, // brissa (index: 137)
      (uint8_t)Pro::ELEMENTALIST, // ciele (index: 138)
      (uint8_t)Pro::ELEMENTALIST, // labetha (index: 139)
      (uint8_t)Pro::ELEMENTALIST, // inteus (index: 140)
      (uint8_t)Pro::ELEMENTALIST, // aenain (index: 141)
      (uint8_t)Pro::ELEMENTALIST, // gelare (index: 142)
      (uint8_t)Pro::ELEMENTALIST, // grindan (index: 143)
      (uint8_t)Pro::KNIGHT,       // sirMullich (index: 144) - class: knight
      (uint8_t)Pro::WITCH,        // adrienne (index: 145) - class: witch
      (uint8_t)Pro::KNIGHT,       // catherine (index: 146) - class: knight
      (uint8_t)Pro::WIZARD,       // dracon (index: 147) - class: wizard
      (uint8_t)Pro::RANGER,       // gelu (index: 148) - class: ranger
      (uint8_t)Pro::BARBARIAN,    // kilgor (index: 149) - class: barbarian
      (uint8_t)
          Pro::DEATH_KNIGHT,   // undeadHaart (index: 150) - class: deathknight
      (uint8_t)Pro::OVERLORD,  // mutare (index: 151) - class: overlord
      (uint8_t)Pro::KNIGHT,    // roland (index: 152) - class: knight
      (uint8_t)Pro::OVERLORD,  // mutareDrake (index: 153) - class: overlord
      (uint8_t)Pro::BARBARIAN, // boragus (index: 154) - class: barbarian
      (uint8_t)Pro::DEMON,     // xeron (index: 155) - class: demoniac
  };

  // HCTRAITS.TXT
  const static inline std::vector<std::array<uint8_t, 4>> heroPrimarySkills = {
      {2, 2, 1, 1}, // 索引 0: Knight
      {1, 0, 2, 2}, // 索引 1: Cleric
      {1, 3, 1, 1}, // 索引 2: Ranger
      {0, 2, 1, 2}, // 索引 3: Druid
      {1, 1, 2, 2}, // 索引 4: Alchemist
      {0, 0, 2, 3}, // 索引 5: Wizard
      {2, 2, 1, 1}, // 索引 6: Demon
      {1, 1, 2, 1}, // 索引 7: Heretic
      {1, 2, 2, 1}, // 索引 8: Death Knight
      {1, 0, 2, 2}, // 索引 9: Necromancer
      {2, 2, 1, 1}, // 索引 10: Overlord
      {0, 0, 3, 2}, // 索引 11: Warlock
      {4, 0, 1, 1}, // 索引 12: Barbarian
      {2, 1, 1, 1}, // 索引 13: Battle Mage
      {0, 4, 1, 1}, // 索引 14: Beastmaster
      {0, 1, 2, 2}, // 索引 15: Witch
      {3, 1, 1, 1}, // 索引 16: Elementalist
      {0, 0, 3, 3}  // 索引 17: Planeswalker
  };

  const static inline std::vector<std::vector<uint8_t>> heroLowLevelChance = {
      {35, 45, 10, 10}, // 索引 0: Knight
      {20, 15, 30, 35}, // 索引 1: Cleric
      {35, 45, 10, 10}, // 索引 2: Ranger
      {10, 20, 35, 35}, // 索引 3: Druid
      {30, 30, 20, 20}, // 索引 4: Alchemist
      {10, 10, 40, 40}, // 索引 5: Wizard
      {35, 35, 15, 15}, // 索引 6: Demon
      {15, 15, 35, 35}, // 索引 7: Heretic
      {30, 25, 20, 25}, // 索引 8: Death Knight
      {15, 15, 35, 35}, // 索引 9: Necromancer
      {35, 35, 15, 15}, // 索引 10: Overlord
      {10, 10, 50, 30}, // 索引 11: Warlock
      {55, 35, 5, 5},   // 索引 12: Barbarian
      {30, 20, 25, 25}, // 索引 13: Battle Mage
      {30, 50, 10, 10}, // 索引 14: Beastmaster
      {5, 15, 40, 40},  // 索引 15: Witch
      {45, 25, 15, 15}, // 索引 16: Elementalist
      {15, 15, 35, 35}  // 索引 17: Planeswalker
  };

  const static inline std::vector<std::vector<uint8_t>> heroHighLevelChance = {
      {30, 30, 20, 20}, // 索引 0: Knight
      {20, 20, 30, 30}, // 索引 1: Cleric
      {30, 30, 20, 20}, // 索引 2: Ranger
      {20, 20, 30, 30}, // 索引 3: Druid
      {30, 30, 20, 20}, // 索引 4: Alchemist
      {30, 20, 20, 30}, // 索引 5: Wizard
      {30, 30, 20, 20}, // 索引 6: Demon
      {20, 20, 30, 30}, // 索引 7: Heretic
      {25, 25, 25, 25}, // 索引 8: Death Knight
      {25, 25, 25, 25}, // 索引 9: Necromancer
      {30, 30, 20, 20}, // 索引 10: Overlord
      {20, 20, 30, 30}, // 索引 11: Warlock
      {30, 30, 20, 20}, // 索引 12: Barbarian
      {25, 25, 25, 25}, // 索引 13: Battle Mage
      {30, 30, 20, 20}, // 索引 14: Beastmaster
      {20, 20, 30, 30}, // 索引 15: Witch
      {30, 30, 20, 20}, // 索引 16: Elementalist
      {25, 25, 25, 25}  // 索引 17: Planeswalker
  };

  const static inline std::vector<std::vector<uint8_t>> heroSecondarySkills = {
      // 0: Knight
      {4, 5, 5, 4, 4, 8, 10, 3, 2, 3, 8, 2, 0, 6,
       1, 3, 4, 2, 1, 7, 5,  4, 7, 5, 1, 1, 5, 2},
      // 1: Cleric
      {2, 3, 4, 3, 7, 5, 2, 7, 4, 5, 4, 6, 0, 3,
       2, 4, 4, 3, 6, 2, 2, 4, 4, 3, 6, 5, 2, 10},
      // 2: Ranger
      {7, 8, 5, 7, 4, 3, 6, 3, 3, 6, 4, 2, 0, 2,
       0, 1, 3, 3, 1, 5, 6, 4, 5, 8, 2, 2, 9, 3},
      // 3: Druid
      {5, 5, 5, 2, 4, 2, 2, 8, 6, 9, 4, 7, 0, 3,
       1, 2, 4, 4, 8, 1, 1, 4, 1, 3, 7, 6, 1, 7},
      // 4: Alchemist
      {4, 5, 6, 4, 3, 3, 3, 6,  4, 2, 6, 3, 0, 4,
       1, 4, 2, 3, 3, 4, 4, 10, 6, 8, 4, 3, 5, 2},
      // 5: Wizard
      {2, 2, 2, 2, 4, 1, 4, 10, 8, 4, 4,  8, 0, 5,
       2, 6, 3, 3, 9, 1, 1, 4,  1, 1, 10, 8, 0, 7},
      // 6: Demon
      {4, 6, 10, 5, 4, 4, 3, 4, 2, 2, 7, 3, 0, 3,
       4, 2, 1,  3, 2, 6, 5, 4, 8, 7, 2, 3, 6, 2},
      // 7: Heretic
      {4, 4, 3, 3, 3, 2, 2, 8, 10, 2, 6, 4, 0, 2,
       5, 3, 2, 4, 5, 4, 4, 4, 4,  4, 6, 6, 3, 5},
      // 8: Death Knight
      {4, 5, 5, 4, 2, 8, 0, 6, 4, 1, 7, 4, 10, 0,
       1, 2, 3, 4, 2, 5, 5, 4, 7, 5, 5, 4, 5,  0},
      // 9: Necromancer
      {6, 2, 4, 2, 4, 5, 0, 8, 6, 1, 5, 7, 10, 3,
       2, 3, 3, 8, 6, 2, 3, 4, 3, 2, 6, 6, 1,  0},
      // 10: Overlord
      {5, 6, 8, 5, 3, 4,  8, 3, 3, 1, 7, 2, 0, 4,
       2, 1, 0, 3, 1, 10, 8, 4, 8, 6, 1, 2, 6, 1},
      // 11: Warlock
      {2, 2, 2, 2, 4, 4, 3, 10, 8, 2, 6, 8,  0, 5,
       5, 2, 2, 5, 8, 1, 1, 4,  1, 1, 8, 10, 0, 6},
      // 12: Barbarian
      {8, 7, 7, 8, 1, 2, 5, 2, 3,  3, 8, 2, 0, 2,
       2, 3, 0, 3, 1, 8, 8, 4, 10, 6, 1, 1, 6, 1},
      // 13: Battle Mage
      {4, 4, 9, 4, 3, 0, 4, 6, 4, 2, 6, 5, 0, 1,
       3, 3, 3, 3, 4, 5, 4, 4, 8, 4, 5, 6, 4, 4},
      // 14: Beastmaster
      {8, 7, 8, 7, 1, 8, 5, 2, 2, 2,  7, 1, 0, 1,
       0, 1, 2, 3, 1, 6, 8, 4, 5, 10, 1, 1, 5, 6},
      // 15: Witch
      {2, 3, 3, 2, 2, 6, 1, 8, 8, 4, 8, 10, 0, 1,
       3, 3, 3, 3, 7, 1, 1, 4, 2, 4, 7, 8,  0, 8},
      // 16: Elementalist
      {6, 8, 8, 6, 2, 5, 3, 2, 3, 2, 8, 2, 0, 3,
       3, 2, 2, 3, 1, 8, 8, 8, 9, 5, 1, 1, 2, 1},
      // 17: Planeswalker
      {2, 2, 2, 2, 4, 4, 3, 8, 8, 2, 4, 8, 0, 3,
       6, 6, 6, 6, 8, 1, 1, 4, 1, 1, 8, 8, 0, 4}};

  const static inline std::vector<std::vector<std::pair<uint16_t, uint32_t>>>
      heroCreatures = {
          // === 城堡英雄 (0-15) ===
          // 0: 欧灵
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 1: 威尔斯凯
          {{(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7}},
          // 2: 艾得力克
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 3: 斯尔维亚
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 4: 罗德-哈特（城堡版本）
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 5: 索萨
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 6: 克里斯丁
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::BALLISTA, 1},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 7: 塔里斯
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 8: 瑞恩
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::FIRST_AID_TENT, 1},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 9: 阿德拉
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 10: 库斯伯特
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 11: 艾德里得
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 12: 因海姆
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 13: 塞亚
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 14: 罗尼斯
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 15: 凯特琳
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},

          // === 壁垒英雄 (16-31) ===
          // 16: 孟斐拉
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 17: 尤佛瑞汀
          {{(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5}},
          // 18: 杰诺娃
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 19: 罗伊德
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 20: 索格灵
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 21: 伊沃
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 22: 克兰
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 23: 凯琳
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 24: 克洛尼斯
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 25: 尤兰德
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 26: 艾丽莎
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 27: 珍尼
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::FIRST_AID_TENT, 1},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 28: 马尔凯姆
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 29: 马洛迪亚
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 30: 艾拉戈
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},
          // 31: 艾丽斯
          {{(uint16_t)CreatureCfg::Creature::CENTAUR, 24},
           {(uint16_t)CreatureCfg::Creature::DWARF, 5},
           {(uint16_t)CreatureCfg::Creature::WOOD_ELF, 6}},

          // === 塔楼英雄 (32-47) ===
          // 32: 匹克杰姆
          {{(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5}},
          // 33: 塞恩
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 34: 琼斯菲尔
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 2},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 35: 妮拉
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 4},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 36: 特洛萨
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::BALLISTA, 1},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 37: 法佛纳
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 38: 瑞萨
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 39: 罗娜
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 40: 艾斯却尔
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 41: 海伦
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 42: 塞瑞纳
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 43: 黛瑞丝
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 44: 塞德洛斯
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 45: 索姆拉
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 46: 塞瑞
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},
          // 47: 埃尔尼
          {{(uint16_t)CreatureCfg::Creature::GREMLIN, 40},
           {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE, 5},
           {(uint16_t)CreatureCfg::Creature::IRON_GOLEM, 3}},

          // === 地狱英雄 (48-63) ===
          // 48: 斐欧纳
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 49: 瑞斯卡
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 50: 玛利斯
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 51: 伊格纳蒂斯
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::IMP, 25}},
          // 52: 奥格塔维亚
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 53: 卡尔
          {{(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::GOG, 7}},
          // 54: 斐瑞
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::BALLISTA, 1},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 55: 纳美斯
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 56: 艾登
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 57: 希瑞尔
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 58: 艾西斯
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 59: 奥力马
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 60: 卡利德
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 61: 艾许
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 62: 泽达
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},
          // 63: 夏洛克斯
          {{(uint16_t)CreatureCfg::Creature::IMP, 25},
           {(uint16_t)CreatureCfg::Creature::GOG, 7},
           {(uint16_t)CreatureCfg::Creature::HELL_HOUND, 4}},

          // === 墓园英雄 (64-79) ===
          // 64: 斯强克
          {{(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6}},
          // 65: 德加尔
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 66: 摩多
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 67: 查玛
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 68: 塔米克
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 69: 艾莎
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 70: 克劳维斯
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 71: 凯瑟瑞
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::SKELETON, 30}},
          // 72: 史蒂芬
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 73: 艾斯瑞
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 74: 山德鲁
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 75: 尼姆巴斯
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 76: 山特
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 77: 希斯
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 78: 维德尼娜
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 79: 纳格斯
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},

          // === 地牢英雄 (80-95) ===
          // 80: 罗勒雷
          {{(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6}},
          // 81: 艾拉切
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::BALLISTA, 1},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 82: 戴斯
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 83: 艾杰特
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 84: 黛玛克
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 85: 耿纳
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 86: 希力卡
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 87: 莎克特
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40}},
          // 88: 艾玛
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 89: 杰格
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 90: 马尔克斯
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 91: 杰德特
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 92: 吉恩
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 93: 蒂玛
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 94: 萨费罗斯
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 95: 达克斯多
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},

          // === 据点英雄 (96-111) ===
          // 96: 约克
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 97: 格尼森
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::BALLISTA, 1},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 98: 杰巴克斯
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::ORC, 6},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 99: 希娃
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 100: 格兰切尔
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::GOBLIN, 25}},
          // 101: 克洛林
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 102: 肯洛-哈格
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 103: 塔洛希尔
          {{(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7}},
          // 104: 哥德
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 105: 维尔
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 106: 德萨
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 107: 特洛克
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 108: 祖宾
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 109: 干德鲁
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 110: 奥力斯
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 111: 塞瑞格
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},

          // === 要塞英雄 (112-127) ===
          // 112: 布朗
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 113: 鲁肯
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::GNOLL, 20}},
          // 114: 维斯特
          {{(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7}},
          // 115: 泰泽
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 116: 阿尔金
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 117: 克巴斯
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4},
           {(uint16_t)CreatureCfg::Creature::DRAGON_FLY, 4}},
          // 118: 格伍夫
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::BALLISTA, 1},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 119: 布鲁菲德
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 120: 麦林德
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 121: 罗斯可
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 122: 傅尔
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 123: 威迪斯
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::FIRST_AID_TENT, 1},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 124: 马利斯（要塞）
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 125: 斯蒂格
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 126: 安洁儿
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 127: 蒂娃
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},

          // === 元素城英雄 (128-143) ===
          // 128: 帕里斯
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 3}},
          // 129: 索尔那
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 130: 依格尼萨
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 131: 拉克斯
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 2}},
          // 132: 莫奈尔
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 3}},
          // 133: 埃德蒙
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 134: 费拉
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 135: 凯尔特
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 2}},
          // 136: 露娜
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 137: 博丽斯
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 138: 萨丽尔
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 139: 兰贝斯
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 140: 恩托斯
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 141: 阿奈尔
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 142: 格雷尔
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},
          // 143: 格兰登
          {{(uint16_t)CreatureCfg::Creature::PIXIE, 25},
           {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL, 5},
           {(uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, 3}},

          // === 特殊英雄 (144-160) ===
          // 144: 姆拉克爵士
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 145: 埃德妮
          {{(uint16_t)CreatureCfg::Creature::GNOLL, 20},
           {(uint16_t)CreatureCfg::Creature::LIZARDMAN, 7},
           {(uint16_t)CreatureCfg::Creature::SERPENT_FLY, 4}},
          // 146: 凯瑟琳
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 147: 德肯
          {{(uint16_t)CreatureCfg::Creature::ENCHANTER, 6},
           {(uint16_t)CreatureCfg::Creature::ENCHANTER, 3},
           {(uint16_t)CreatureCfg::Creature::ENCHANTER, 1}},
          // 148: 格鲁
          {{(uint16_t)CreatureCfg::Creature::SHARPSHOOTER, 6},
           {(uint16_t)CreatureCfg::Creature::SHARPSHOOTER, 3},
           {(uint16_t)CreatureCfg::Creature::SHARPSHOOTER, 1}},
          // 149: 科尔格
          {{(uint16_t)CreatureCfg::Creature::GOBLIN, 25},
           {(uint16_t)CreatureCfg::Creature::WOLF_RIDER, 7},
           {(uint16_t)CreatureCfg::Creature::ORC, 6}},
          // 150: 罗德-哈特（墓园版本）
          {{(uint16_t)CreatureCfg::Creature::SKELETON, 30},
           {(uint16_t)CreatureCfg::Creature::ZOMBIE, 6},
           {(uint16_t)CreatureCfg::Creature::WIGHT, 6}},
          // 151: 摩莉尔（地牢）
          {{(uint16_t)CreatureCfg::Creature::TROGLODYTE, 40},
           {(uint16_t)CreatureCfg::Creature::HARPY, 6},
           {(uint16_t)CreatureCfg::Creature::BEHOLDER, 4}},
          // 152: 罗兰德
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 153: 巨龙摩莉尔（城堡？）
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 154: 伯拉格
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},
          // 155: 塞尔伦
          {{(uint16_t)CreatureCfg::Creature::PIKEMAN, 20},
           {(uint16_t)CreatureCfg::Creature::ARCHER, 7},
           {(uint16_t)CreatureCfg::Creature::GRIFFIN, 3}},

          // === 最后的英雄索引到160 ===
          // 156-160: 预留位置或特殊英雄
          {},
          {},
          {},
          {},
          {}};

  const static inline uint64_t heroLevelExp[] = {
      0,      // 等级1
      1000,   // 等级2
      2000,   // 等级3
      3200,   // 等级4
      4600,   // 等级5
      6200,   // 等级6
      8000,   // 等级7
      10000,  // 等级8
      12200,  // 等级9
      14700,  // 等级10
      17500,  // 等级11
      20600,  // 等级12
      24320,  // 等级13
      28784,  // 等级14
      34140,  // 等级15
      40468,  // 等级16
      48022,  // 等级17
      57226,  // 等级18
      68471,  // 等级19
      82165,  // 等级20
      98798,  // 等级21
      118757, // 等级22
      142508, // 等级23
      171009, // 等级24
      205210, // 等级25
      246252, // 等级26
      295502, // 等级27
      354602, // 等级28
      425522, // 等级29
      510626  // 等级30
  };
  const static inline std::string heroSmallPor[] = {
      // Knight (KN)
      "HPS000KN.pcx", "HPS001KN.pcx", "HPS002KN.pcx", "HPS003KN.pcx",
      "HPS004KN.pcx", "HPS005KN.pcx", "HPS006KN.pcx", "HPS007KN.pcx",

      // Cleric (CL)
      "HPS008CL.pcx", "HPS009CL.pcx", "HPS010CL.pcx", "HPS011CL.pcx",
      "HPS012CL.pcx", "HPS013CL.pcx", "HPS014CL.pcx", "HPS015CL.pcx",

      // Ranger (RN)
      "HPS016RN.pcx", "HPS017RN.pcx", "HPS018RN.pcx", "HPS019RN.pcx",
      "HPS020RN.pcx", "HPS021RN.pcx", "HPS022RN.pcx", "HPS023RN.pcx",

      // Druid (DR)
      "HPS024DR.pcx", "HPS025DR.pcx", "HPS026DR.pcx", "HPS027DR.pcx",
      "HPS028DR.pcx", "HPS029DR.pcx", "HPS030DR.pcx", "HPS031DR.pcx",

      // Alchemist (AL)
      "HPS032AL.pcx", "HPS033AL.pcx", "HPS034AL.pcx", "HPS035AL.pcx",
      "HPS036AL.pcx", "HPS037AL.pcx", "HPS038AL.pcx", "HPS039AL.pcx",

      // Wizard (WZ)
      "HPS040WZ.pcx", "HPS041WZ.pcx", "HPS042WZ.pcx", "HPS043WZ.pcx",
      "HPS044WZ.pcx", "HPS045WZ.pcx", "HPS046WZ.pcx", "HPS047WZ.pcx",

      // Knight (HR)
      "HPS048HR.pcx", "HPS049HR.pcx", "HPS050HR.pcx", "HPS051HR.pcx",
      "HPS052HR.pcx", "HPS053HR.pcx", "HPS054HR.pcx", "HPS055HR.pcx",

      // Demon Lord (DM)
      "HPS056DM.pcx", "HPS057DM.pcx", "HPS058DM.pcx", "HPS059DM.pcx",
      "HPS060DM.pcx", "HPS061DM.pcx", "HPS062DM.pcx", "HPS063DM.pcx",

      // Death Knight (DK)
      "HPS064DK.pcx", "HPS065DK.pcx", "HPS066DK.pcx", "HPS067DK.pcx",
      "HPS068DK.pcx", "HPS069DK.pcx", "HPS070DK.pcx", "HPS071DK.pcx",

      // Necromancer (NC)
      "HPS072NC.pcx", "HPS073NC.pcx", "HPS074NC.pcx", "HPS075NC.pcx",
      "HPS076NC.pcx", "HPS077NC.pcx", "HPS078NC.pcx", "HPS079NC.pcx",

      // Overlord (OV)
      "HPS080OV.pcx", "HPS081OV.pcx", "HPS082OV.pcx", "HPS083OV.pcx",
      "HPS084OV.pcx", "HPS085OV.pcx", "HPS086OV.pcx", "HPS087OV.pcx",

      // Warlock (WL)
      "HPS088WL.pcx", "HPS089WL.pcx", "HPS090WL.pcx", "HPS091WL.pcx",
      "HPS092WL.pcx", "HPS093WL.pcx", "HPS094WL.pcx", "HPS095WL.pcx",

      // Barbarian (BR)
      "HPS096BR.pcx", "HPS097BR.pcx", "HPS098BR.pcx", "HPS099BR.pcx",
      "HPS100BR.pcx", "HPS101BR.pcx", "HPS102BR.pcx", "HPS103BR.pcx",

      // Battle Mage (BM)
      "HPS104BM.pcx", "HPS105BM.pcx", "HPS106BM.pcx", "HPS107BM.pcx",
      "HPS108BM.pcx", "HPS109BM.pcx", "HPS110BM.pcx", "HPS111BM.pcx",

      // Beastmaster (BS)
      "HPS112BS.pcx", "HPS113BS.pcx", "HPS114BS.pcx", "HPS115BS.pcx",
      "HPS116BS.pcx", "HPS117BS.pcx", "HPS118BS.pcx", "HPS119BS.pcx",

      // Witch (WH)
      "HPS120WH.pcx", "HPS121WH.pcx", "HPS122WH.pcx", "HPS123WH.pcx",
      "HPS124WH.pcx", "HPS125WH.pcx", "HPS126WH.pcx", "HPS127WH.pcx",

      // Planeswalker (PL)
      "HPS000PL.pcx", "HPS001PL.pcx", "HPS002PL.pcx", "HPS003PL.pcx",
      "HPS004PL.pcx", "HPS005PL.pcx", "HPS006PL.pcx", "HPS007PL.pcx",

      // Elementalist (EL)
      "HPS000EL.pcx", "HPS001EL.pcx", "HPS002EL.pcx", "HPS003EL.pcx",
      "HPS004EL.pcx", "HPS005EL.pcx", "HPS006EL.pcx", "HPS007EL.pcx",

      // 特殊英雄
      "HPS130KN.pcx", "HPS000SH.pcx", "HPS128QC.pcx", "HPS003SH.pcx",
      "HPS004SH.pcx", "HPS005SH.pcx", "HPS006SH.pcx", "HPS007SH.pcx",
      "HPS009SH.pcx", "HPS008SH.pcx", "HPS001SH.pcx", "HPS131DM.pcx",

      // 随机英雄
      "HPSRAND1.pcx", "HPSRAND6.pcx", "HPSXXX.pcx", "HPSYYY.pcx"};

  const static inline std::string heroLargePor[] = {
      // Knight (KN)
      "HPL000KN.pcx", "HPL001KN.pcx", "HPL002KN.pcx", "HPL003KN.pcx",
      "HPL004KN.pcx", "HPL005KN.pcx", "HPL006KN.pcx", "HPL007KN.pcx",

      // Cleric (CL)
      "HPL008CL.pcx", "HPL009CL.pcx", "HPL010CL.pcx", "HPL011CL.pcx",
      "HPL012CL.pcx", "HPL013CL.pcx", "HPL014CL.pcx", "HPL015CL.pcx",

      // Ranger (RN)
      "HPL016RN.pcx", "HPL017RN.pcx", "HPL018RN.pcx", "HPL019RN.pcx",
      "HPL020RN.pcx", "HPL021RN.pcx", "HPL022RN.pcx", "HPL023RN.pcx",

      // Druid (DR)
      "HPL024DR.pcx", "HPL025DR.pcx", "HPL026DR.pcx", "HPL027DR.pcx",
      "HPL028DR.pcx", "HPL029DR.pcx", "HPL030DR.pcx", "HPL031DR.pcx",

      // Alchemist (AL)
      "HPL032AL.pcx", "HPL033AL.pcx", "HPL034AL.pcx", "HPL035AL.pcx",
      "HPL036AL.pcx", "HPL037AL.pcx", "HPL038AL.pcx", "HPL039AL.pcx",

      // Wizard (WZ)
      "HPL040WZ.pcx", "HPL041WZ.pcx", "HPL042WZ.pcx", "HPL043WZ.pcx",
      "HPL044WZ.pcx", "HPL045WZ.pcx", "HPL046WZ.pcx", "HPL047WZ.pcx",

      // Knight (HR)
      "HPL048HR.pcx", "HPL049HR.pcx", "HPL050HR.pcx", "HPL051HR.pcx",
      "HPL052HR.pcx", "HPL053HR.pcx", "HPL054HR.pcx", "HPL055HR.pcx",

      // Demon Lord (DM)
      "HPL056DM.pcx", "HPL057DM.pcx", "HPL058DM.pcx", "HPL059DM.pcx",
      "HPL060DM.pcx", "HPL061DM.pcx", "HPL062DM.pcx", "HPL063DM.pcx",

      // Death Knight (DK)
      "HPL064DK.pcx", "HPL065DK.pcx", "HPL066DK.pcx", "HPL067DK.pcx",
      "HPL068DK.pcx", "HPL069DK.pcx", "HPL070DK.pcx", "HPL071DK.pcx",

      // Necromancer (NC)
      "HPL072NC.pcx", "HPL073NC.pcx", "HPL074NC.pcx", "HPL075NC.pcx",
      "HPL076NC.pcx", "HPL077NC.pcx", "HPL078NC.pcx", "HPL079NC.pcx",

      // Overlord (OV)
      "HPL080OV.pcx", "HPL081OV.pcx", "HPL082OV.pcx", "HPL083OV.pcx",
      "HPL084OV.pcx", "HPL085OV.pcx", "HPL086OV.pcx", "HPL087OV.pcx",

      // Warlock (WL)
      "HPL088WL.pcx", "HPL089WL.pcx", "HPL090WL.pcx", "HPL091WL.pcx",
      "HPL092WL.pcx", "HPL093WL.pcx", "HPL094WL.pcx", "HPL095WL.pcx",

      // Barbarian (BR)
      "HPL096BR.pcx", "HPL097BR.pcx", "HPL098BR.pcx", "HPL099BR.pcx",
      "HPL100BR.pcx", "HPL101BR.pcx", "HPL102BR.pcx", "HPL103BR.pcx",

      // Battle Mage (BM)
      "HPL104BM.pcx", "HPL105BM.pcx", "HPL106BM.pcx", "HPL107BM.pcx",
      "HPL108BM.pcx", "HPL109BM.pcx", "HPL110BM.pcx", "HPL111BM.pcx",

      // Beastmaster (BS)
      "HPL112BS.pcx", "HPL113BS.pcx", "HPL114BS.pcx", "HPL115BS.pcx",
      "HPL116BS.pcx", "HPL117BS.pcx", "HPL118BS.pcx", "HPL119BS.pcx",

      // Witch (WH)
      "HPL120WH.pcx", "HPL121WH.pcx", "HPL122WH.pcx", "HPL123WH.pcx",
      "HPL124WH.pcx", "HPL125WH.pcx", "HPL126WH.pcx", "HPL127WH.pcx",

      // Planeswalker (PL)
      "HPL000PL.pcx", "HPL001PL.pcx", "HPL002PL.pcx", "HPL003PL.pcx",
      "HPL004PL.pcx", "HPL005PL.pcx", "HPL006PL.pcx", "HPL007PL.pcx",

      // Elementalist (EL)
      "HPL000EL.pcx", "HPL001EL.pcx", "HPL002EL.pcx", "HPL003EL.pcx",
      "HPL004EL.pcx", "HPL005EL.pcx", "HPL006EL.pcx", "HPL007EL.pcx",

      // 特殊英雄
      "HPL130KN.pcx", "HPL000SH.pcx", "HPL128QC.pcx", "HPL003SH.pcx",
      "HPL004SH.pcx", "HPL005SH.pcx", "HPL006SH.pcx", "HPL007SH.pcx",
      "HPL009SH.pcx", "HPL008SH.pcx", "HPL001SH.pcx", "HPL131DM.pcx"};
};