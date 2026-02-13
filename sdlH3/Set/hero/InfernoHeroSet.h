#pragma once

#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct InfernoHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// fiona
       .index = 48,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = true,
       .secSkill =
           {
               {Enum::SCOUTING, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::HELL_HOUND,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::CERBERUS,
                   .val = 5,
               },
           }},
      {// rashka
       .index = 49,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SCHOLAR, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::EFREETI,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::EFREET_SULTAN,
                   .val = 5,
               },
           }},
      {// marius
       .index = 50,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = true,
       .secSkill =
           {
               {Enum::ARMORER, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::DEMON, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DEMON,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::HORNED_DEMON,
                   .val = 5,
               },
           }},
      {// ignatius
       .index = 51,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = false,
       .secSkill =
           {
               {Enum::TACTICS, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::IMP,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::FAMILIAR,
                   .val = 5,
               },
           }},
      {// octavia
       .index = 52,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = true,
       .secSkill =
           {
               {Enum::SCHOLAR, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
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
      {// calh
       .index = 53,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = false,
       .secSkill =
           {
               {Enum::ARCHERY, Enum::BASIC},
               {Enum::SCOUTING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GOG,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MAGOG,
                   .val = 5,
               },
           }},
      {// pyre
       .index = 54,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = true,
       .secSkill =
           {
               {Enum::ARTILLERY, Enum::BASIC},
               {Enum::LOGISTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
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
      {// nymus
       .index = 55,
       .clasz = Enum::HERO_CLASS_DEMON,  // 魔鬼 = 6
       .female = true,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::PIT_FIEND, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::PIT_FIEND,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::PIT_LORD,
                   .val = 5,
               },
           }},
      {// ayden
       .index = 56,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::INTELLIGENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
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
       .spells = {Enum::VIEW_EARTH}},
      {// xyron
       .index = 57,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SCHOLAR, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::INFERNO,
                   .val = 3,
               },
           },
       .spells = {Enum::INFERNO}},
      {// axsis
       .index = 58,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::MYSTICISM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
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
       .spells = {Enum::PROTECTION_FROM_AIR}},
      {// olema
       .index = 59,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::BALLISTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::WEAKNESS,
                   .val = 0,
               },
           },
       .spells = {Enum::WEAKNESS}},
      {// calid
       .index = 60,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LEARNING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_GENERATE_RESOURCE,
                   .subId = Enum::SULFUR,
                   .val = 1,
               },
           },
       .spells = {Enum::HASTE}},
      {// ash
       .index = 61,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::BLOODLUST,
                   .val = 5,
               },
           },
       .spells = {Enum::BLOODLUST}},
      {// zydar
       .index = 62,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
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
       .spells = {Enum::STONE_SKIN}},
      {// xarfax
       .index = 63,
       .clasz = Enum::HERO_CLASS_HERETIC,  // 异教徒 = 7
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LEADERSHIP, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::IMP, 15},
               {Enum::GOG, 9},
               {Enum::HELL_HOUND, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::FIREBALL,
                   .val = 3,
               },
           },
       .spells = {Enum::FIREBALL}},
  };
};