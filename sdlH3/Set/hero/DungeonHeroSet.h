#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct DungeonHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// lorelei
       .index = 80,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = true,
       .secSkill =
           {
               {Enum::SCOUTING, Enum::BASIC},
               {Enum::LEADERSHIP, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::HARPY,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::HARPY_HAG,
                   .val = 5,
               },
           }},
      {// arlach
       .index = 81,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = false,
       .secSkill =
           {
               {Enum::ARTILLERY, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
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
      {// dace
       .index = 82,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = false,
       .secSkill =
           {
               {Enum::TACTICS, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MINOTAUR,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MINOTAUR_KING,
                   .val = 5,
               },
           }},
      {// ajit
       .index = 83,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BEHOLDER,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::EVIL_EYE,
                   .val = 5,
               },
           }},
      {// damacon
       .index = 84,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
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
      {// gunnar
       .index = 85,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = false,
       .secSkill =
           {
               {Enum::LOGISTICS, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
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
      {// synca
       .index = 86,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = true,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::SCHOLAR, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MANTICORE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::SCORPICORE,
                   .val = 5,
               },
           }},
      {// shakti
       .index = 87,
       .clasz = Enum::HERO_CLASS_OVERLORD,  // 领主 = 10
       .female = false,
       .secSkill =
           {
               {Enum::TACTICS, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::TROGLODYTE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::INFERNAL_TROGLODYTE,
                   .val = 5,
               },
           }},
      {// alamar
       .index = 88,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SCHOLAR, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::RESURRECTION,
                   .val = 3,
               },
           },
       .spells = {Enum::RESURRECTION}},
      {// jaegar
       .index = 89,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::MYSTICISM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
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
       .spells = {Enum::SHIELD}},
      {// malekith
       .index = 90,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
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
      {// jeddite
       .index = 91,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::RESURRECTION,
                   .val = 3,
               },
           },
       .spells = {Enum::RESURRECTION}},
      {// geon
       .index = 92,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
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
       .spells = {Enum::SLOW}},
      {// deemer
       .index = 93,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SCOUTING, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::METEOR_SHOWER,
                   .val = 3,
               },
           },
       .spells = {Enum::METEOR_SHOWER}},
      {// sephinroth
       .index = 94,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::INTELLIGENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_GENERATE_RESOURCE,
                   .subId = Enum::CRYSTAL,
                   .val = 1,
               },
           },
       .spells = {Enum::PROTECTION_FROM_AIR}},
      {// darkstorn
       .index = 95,
       .clasz = Enum::HERO_CLASS_WARLOCK,  // 妖术师 = 11
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LEARNING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::TROGLODYTE, 20},
               {Enum::HARPY, 9},
               {Enum::BEHOLDER, 6},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::STONE_SKIN,
                   .val = 5,
               },
           },
       .spells = {Enum::STONE_SKIN}},
  };
};