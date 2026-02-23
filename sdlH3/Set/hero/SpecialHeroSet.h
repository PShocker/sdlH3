#pragma once

#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct SpecialHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// sirMullich (索引144)
       .index = 144,
       .clasz = Enum::HERO_CLASS_KNIGHT, // 骑士 = 0
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "HPS130KN.pcx",
       .largePor = "HPL130KN.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_STACKS_SPEED,
                   .val = 2,
               },
           }},
      {// adrienne (索引145)
       .index = 145,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::FIRE_MAGIC, Enum::EXPERT},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "HPS000SH.pcx",
       .largePor = "HPL000SH.pcx",
       .spec = {},
       .spells = {Enum::INFERNO}},
      {// catherine (索引146)
       .index = 146,
       .clasz = Enum::HERO_CLASS_KNIGHT, // 骑士 = 0
       .female = true,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "HPS128QC.pcx",
       .largePor = "HPL128QC.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::SWORDSMAN,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::CRUSADER,
                   .val = 5,
               },
           }},
      {// dracon (索引147)
       .index = 147,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "HPS003SH.pcx",
       .largePor = "HPL003SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::MONK,
                   .val = Enum::ENCHANTER,
               },
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::ZEALOT,
                   .val = Enum::ENCHANTER,
               },
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::MAGE,
                   .val = Enum::ENCHANTER,
               },
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::ARCH_MAGE,
                   .val = Enum::ENCHANTER,
               },
           },
       .spells = {Enum::HASTE}},
      {// gelu (索引148)
       .index = 148,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = false,
       .secSkill =
           {
               {Enum::ARCHERY, Enum::BASIC},
               {Enum::LEADERSHIP, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},
           },
       .smallPor = "HPS004SH.pcx",
       .largePor = "HPL004SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::ARCHER,
                   .val = Enum::SHARPSHOOTER,
               },
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::MARKSMAN,
                   .val = Enum::SHARPSHOOTER,
               },
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::WOOD_ELF,
                   .val = Enum::SHARPSHOOTER,
               },
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .subId = Enum::GRAND_ELF,
                   .val = Enum::SHARPSHOOTER,
               },
           }},
      {// kilgor (索引149)
       .index = 149,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},
               {Enum::WOLF_RIDER, 6},
           },
       .smallPor = "HPS005SH.pcx",
       .largePor = "HPL005SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BEHEMOTH,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ANCIENT_BEHEMOTH,
                   .val = 5,
               },
           }},
      {// undeadHaart (索引150)
       .index = 150,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT, // 死亡骑士 = 8
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "HPS006SH.pcx",
       .largePor = "HPL006SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BLACK_KNIGHT,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DREAD_KNIGHT,
                   .val = 5,
               },
           },
       .spells = {Enum::SLOW}},
      {// mutare (索引151)
       .index = 151,
       .clasz = Enum::HERO_CLASS_OVERLORD, // 领主 = 10
       .female = true,
       .secSkill =
           {
               {Enum::ESTATES, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "HPS007SH.pcx",
       .largePor = "HPL007SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GREEN_DRAGON,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// roland (索引152)
       .index = 152,
       .clasz = Enum::HERO_CLASS_KNIGHT, // 骑士 = 0
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::ARMORER, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "HPS009SH.pcx",
       .largePor = "HPL009SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::SWORDSMAN,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::CRUSADER,
                   .val = 5,
               },
           }},
      {// mutareDrake (索引153)
       .index = 153,
       .clasz = Enum::HERO_CLASS_OVERLORD, // 领主 = 10
       .female = true,
       .secSkill =
           {
               {Enum::ESTATES, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 10},
               {Enum::HARPY, 4},
               {Enum::EVIL_EYE, 2},
           },
       .smallPor = "HPS008SH.pcx",
       .largePor = "HPL008SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// boragus (索引154)
       .index = 154,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = false,
       .secSkill =
           {
               {Enum::TACTICS, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 10},
               {Enum::WOLF_RIDER, 4},
               {Enum::ORC, 2},
           },
       .smallPor = "HPS001SH.pcx",
       .largePor = "HPL001SH.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::OGRE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::OGRE_MAGE,
                   .val = 5,
               },
           }},
      {// xeron (索引155)
       .index = 155,
       .clasz = Enum::HERO_CLASS_DEMON, // 魔鬼 = 6
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 10},
               {Enum::HELL_HOUND, 4},
               {Enum::HELL_HOUND, 2},
           },
       .smallPor = "HPS131DM.pcx",
       .largePor = "HPL131DM.pcx",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DEVIL,
                   .val = 4,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ARCH_DEVIL,
                   .val = 4,
               },
               {
                   .id = Enum::SPECIAL_SPECIAL_UPGRADE,
                   .val = 1,
               },
           }},
  };
};