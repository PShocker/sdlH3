#pragma once
#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct ConfluxHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// pasis
       .index = 128,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = true,
       .secSkill =
           {
               {Enum::ARTILLERY, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::PSYCHIC_ELEMENTAL,
                   .val = 3,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MAGIC_ELEMENTAL,
                   .val = 3,
               },
           }},
      {// thunar
       .index = 129,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = true,
       .secSkill =
           {
               {Enum::ESTATES, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::EARTH_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::EARTH_ELEMENTAL,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MAGMA_ELEMENTAL,
                   .val = 5,
               },
           }},
      {// ignissa
       .index = 130,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = true,
       .secSkill =
           {
               {Enum::ARTILLERY, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::FIRE_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::FIRE_ELEMENTAL,
                   .val = 2,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ENERGY_ELEMENTAL,
                   .val = 2,
               },
           }},
      {// lacus
       .index = 131,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = true,
       .secSkill =
           {
               {Enum::TACTICS, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WATER_ELEMENTAL,
                   .val = 2,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ICE_ELEMENTAL,
                   .val = 2,
               },
           }},
      {// monere
       .index = 132,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = false,
       .secSkill =
           {
               {Enum::LOGISTICS, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::PSYCHIC_ELEMENTAL,
                   .val = 3,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MAGIC_ELEMENTAL,
                   .val = 3,
               },
           }},
      {// erdamon
       .index = 133,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = false,
       .secSkill =
           {
               {Enum::ESTATES, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::EARTH_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::EARTH_ELEMENTAL,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MAGMA_ELEMENTAL,
                   .val = 5,
               },
           }},
      {// fiur
       .index = 134,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = false,
       .secSkill =
           {
               {Enum::OFFENCE, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::FIRE_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::FIRE_ELEMENTAL,
                   .val = 2,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ENERGY_ELEMENTAL,
                   .val = 2,
               },
           }},
      {// kalt
       .index = 135,
       .clasz = Enum::HERO_CLASS_PLANESWALKER,  // 位面行者 = 17
       .female = false,
       .secSkill =
           {
               {Enum::TACTICS, Enum::BASIC},
               {Enum::LEARNING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WATER_ELEMENTAL,
                   .val = 2,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ICE_ELEMENTAL,
                   .val = 2,
               },
           }},
      {// luna
       .index = 136,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::FIRE_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::FIRE_WALL,
                   .val = 100,
               },
           },
       .spells = {Enum::FIRE_WALL}},
      {// brissa
       .index = 137,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::AIR_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
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
      {// ciele
       .index = 138,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::WATER_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::MAGIC_ARROW,
                   .val = 50,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// labetha
       .index = 139,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EARTH_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::EARTH_ELEMENTAL, 4},
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
      {// inteus
       .index = 140,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::FIRE_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::FIRE_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::BLOODLUST,
                   .val = 0,
               },
           },
       .spells = {Enum::BLOODLUST}},
      {// aenain
       .index = 141,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::AIR_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::DISRUPTING_RAY,
                   .val = 5,
               },
           },
       .spells = {Enum::DISRUPTING_RAY}},
      {// gelare
       .index = 142,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::WATER_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::WATER_ELEMENTAL, 4},
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
           },
       .spells = {Enum::DISPEL}},
      {// grindan
       .index = 143,
       .clasz = Enum::HERO_CLASS_ELEMENTALIST,  // 元素使 = 16
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EARTH_MAGIC, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIXIE, 15},
               {Enum::AIR_ELEMENTAL, 6},
               {Enum::EARTH_ELEMENTAL, 4},
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
           },
       .spells = {Enum::SLOW}},
  };
};