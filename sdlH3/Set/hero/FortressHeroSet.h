#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct FortressHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// bron
       .index = 112,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 10},
               {Enum::BASILISK, 4},
               {Enum::SERPENT_FLY, 2},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BASILISK,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GREATER_BASILISK,
                   .val = 5,
               },
           }},
      {// drakon
       .index = 113,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::BASIC},
               {Enum::LEADERSHIP, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GNOLL,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GNOLL_MARAUDER,
                   .val = 5,
               },
           }},
      {// wystan
       .index = 114,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::BASIC},
               {Enum::ARCHERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::LIZARDMAN,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::LIZARD_WARRIOR,
                   .val = 5,
               },
           }},
      {// tazar
       .index = 115,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::ARMORER,
                   .val = 5,
               },
           }},
      {// alkin
       .index = 116,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GORGON,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MIGHTY_GORGON,
                   .val = 5,
               },
           }},
      {// korbac
       .index = 117,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::BASIC},
               {Enum::PATHFINDING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::SERPENT_FLY,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DRAGON_FLY,
                   .val = 5,
               },
           }},
      {// gerwulf
       .index = 118,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::BASIC},
               {Enum::ARTILLERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
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
      {// broghild
       .index = 119,
       .clasz = Enum::HERO_CLASS_BEASTMASTER, // 驯兽师 = 14
       .female = false,
       .secSkill =
           {
               {Enum::ARMORER, Enum::BASIC},
               {Enum::SCOUTING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WYVERN,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WYVERN_MONARCH,
                   .val = 5,
               },
           }},
      {// mirlanda
       .index = 120,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::WEAKNESS,
                   .val = 5,
               },
           },
       .spells = {Enum::WEAKNESS}},
      {// rosic
       .index = 121,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::MYSTICISM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::MYSTICISM,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// voy
       .index = 122,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::NAVIGATION, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::NAVIGATION,
                   .val = 5,
               },
           },
       .spells = {Enum::SLOW}},
      {// verdish
       .index = 123,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::FIRST_AID, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::FIRST_AID,
                   .val = 5,
               },
           },
       .spells = {Enum::PROTECTION_FROM_FIRE}},
      {// merist
       .index = 124,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LEARNING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::STONE_SKIN,
                   .val = 0,
               },
           },
       .spells = {Enum::STONE_SKIN}},
      {// styg
       .index = 125,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
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
       .spells = {Enum::SHIELD}},
      {// andra
       .index = 126,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::INTELLIGENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::INTELLIGENCE,
                   .val = 5,
               },
           },
       .spells = {Enum::DISPEL}},
      {// tiva
       .index = 127,
       .clasz = Enum::HERO_CLASS_WITCH, // 女巫 = 15
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GNOLL, 15},
               {Enum::LIZARDMAN, 8},
               {Enum::SERPENT_FLY, 5},
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
       .spells = {Enum::STONE_SKIN}},
  };
};