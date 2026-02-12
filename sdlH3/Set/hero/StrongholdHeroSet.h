#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct StrongholdHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// yog
       .index = 96,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::BASIC},
               {Enum::BALLISTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},
               {Enum::WOLF_RIDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::CYCLOPS,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::CYCLOPS_KING,
                   .val = 5,
               },
           }},
      {// gurnisson
       .index = 97,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::BASIC},
               {Enum::ARTILLERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},
               {Enum::BALLISTA, 1},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BALLISTA,
                   .val = 5,
               },
           }},
      {// jabarkas
       .index = 98,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::BASIC},
               {Enum::ARCHERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ORC,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ORC_CHIEFTAIN,
                   .val = 5,
               },
           }},
      {// shiva
       .index = 99,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = true,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::BASIC},
               {Enum::SCOUTING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ROC,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::THUNDERBIRD,
                   .val = 5,
               },
           }},
      {// gretchin
       .index = 100,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = true,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::BASIC},
               {Enum::PATHFINDING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GOBLIN,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::HOBGOBLIN,
                   .val = 5,
               },
           }},
      {// krellion
       .index = 101,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
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
      {// cragHack
       .index = 102,
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

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::OFFENCE,
                   .val = 5,
               },
           }},
      {// tyraxor
       .index = 103,
       .clasz = Enum::HERO_CLASS_BARBARIAN, // 野蛮人 = 12
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WOLF_RIDER,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WOLF_RAIDER,
                   .val = 5,
               },
           }},
      {// gird
       .index = 104,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::SORCERY,
                   .val = 5,
               },
           },
       .spells = {Enum::BLOODLUST}},
      {// vey
       .index = 105,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LEADERSHIP, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
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
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// dessa
       .index = 106,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LOGISTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::LOGISTICS,
                   .val = 5,
               },
           },
       .spells = {Enum::STONE_SKIN}},
      {// terek
       .index = 107,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::HASTE,
                   .val = 0,
               },
           },
       .spells = {Enum::HASTE}},
      {// zubin
       .index = 108,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::ARTILLERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},
               {Enum::BALLISTA, 1},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::PRECISION,
                   .val = 0,
               },
           },
       .spells = {Enum::PRECISION}},
      {// gundula
       .index = 109,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::OFFENCE,
                   .val = 5,
               },
           },
       .spells = {Enum::SLOW}},
      {// oris
       .index = 110,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::EAGLE_EYE,
                   .val = 5,
               },
           },
       .spells = {Enum::PROTECTION_FROM_AIR}},
      {// saurug
       .index = 111,
       .clasz = Enum::HERO_CLASS_BATTLE_MAGE, // 战斗法师 = 13
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GOBLIN, 20},
               {Enum::ORC, 10},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_GENERATE_RESOURCE,
                   .subId = Enum::GEM,
                   .val = 1,
               },
           },
       .spells = {Enum::BLOODLUST}},
  };
};