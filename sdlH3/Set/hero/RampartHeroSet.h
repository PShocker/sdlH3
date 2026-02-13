#pragma once

#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct RampartHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// mephala
       .index = 16,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = true,
       .secSkill = {{Enum::LEADERSHIP, Enum::BASIC},
                    {Enum::ARMORER, Enum::BASIC}},
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},
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
      {// ufretin
       .index = 17,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = false,
       .secSkill =
           {
               {Enum::LUCK, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DWARF,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BATTLE_DWARF,
                   .val = 5,
               },
           }},
      {// jenova
       .index = 18,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = true,
       .secSkill =
           {
               {Enum::ARCHERY, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_GENERATE_RESOURCE,
                   .subId = Enum::GOLD,
                   .val = 350,
               },
           }},
      {// ryland
       .index = 19,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = false,
       .secSkill =
           {
               {Enum::DIPLOMACY, Enum::BASIC},
               {Enum::LEADERSHIP, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DENDROID_GUARD,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DENDROID_SOLDIER,
                   .val = 5,
               },
           }},
      {// thorgrim
       .index = 20,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = false,
       .secSkill =
           {
               {Enum::RESISTANCE, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::RESISTANCE,
                   .val = 5,
               },
           }},
      {// ivor
       .index = 21,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = false,
       .secSkill =
           {
               {Enum::ARCHERY, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WOOD_ELF,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GRAND_ELF,
                   .val = 5,
               },
           }},
      {// clancy
       .index = 22,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = false,
       .secSkill =
           {
               {Enum::PATHFINDING, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::UNICORN,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WAR_UNICORN,
                   .val = 5,
               },
           }},
      {// kyrre
       .index = 23,
       .clasz = Enum::HERO_CLASS_RANGER, // 游侠 = 2
       .female = true,
       .secSkill =
           {
               {Enum::ARCHERY, Enum::BASIC},
               {Enum::LOGISTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

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
           }},
      {// coronius
       .index = 24,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SCHOLAR, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::SLAYER,
                   .val = 1,
               },
           },
       .spells = {Enum::SLAYER}},
      {// uland
       .index = 25,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::ADVANCED},
               {Enum::BALLISTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::CURE,
                   .val = 3,
               },
           },
       .spells = {Enum::CURE}},
      {// elleshar
       .index = 26,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::INTELLIGENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

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
       .spells = {Enum::CURSE}},
      {// gem
       .index = 27,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::FIRST_AID, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

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
       .spells = {Enum::SUMMON_BOAT}},
      {// malcom
       .index = 28,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

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
       .spells = {Enum::MAGIC_ARROW}},
      {// melodia
       .index = 29,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LUCK, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::FORTUNE,
                   .val = 3,
               },
           },
       .spells = {Enum::FORTUNE}},
      {// alagar
       .index = 30,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::ICE_BOLT,
                   .val = 3,
               },
           },
       .spells = {Enum::ICE_BOLT}},
      {// aeris
       .index = 31,
       .clasz = Enum::HERO_CLASS_DRUID, // 德鲁伊 = 3
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SCOUTING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::CENTAUR, 12},
               {Enum::DWARF, 6},

           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::PEGASUS,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::SILVER_PEGASUS,
                   .val = 5,
               },
           },
       .spells = {Enum::PROTECTION_FROM_AIR}},
  };
};