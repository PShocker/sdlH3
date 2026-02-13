#pragma once

#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct TowerHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// piquedram
       .index = 32,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = false,
       .secSkill =
           {
               {Enum::SCOUTING, Enum::BASIC},
               {Enum::MYSTICISM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::STONE_GARGOYLE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::OBSIDIAN_GARGOYLE,
                   .val = 5,
               },
           },
       .spells = {Enum::SHIELD}},
      {// thane
       .index = 33,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = false,
       .secSkill =
           {
               {Enum::SCHOLAR, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GENIE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MASTER_GENIE,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// josephine
       .index = 34,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = true,
       .secSkill =
           {
               {Enum::MYSTICISM, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::IRON_GOLEM,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::STONE_GOLEM,
                   .val = 5,
               },
           },
       .spells = {Enum::HASTE}},
      {// neela
       .index = 35,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = true,
       .secSkill =
           {
               {Enum::SCHOLAR, Enum::BASIC},
               {Enum::ARMORER, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
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
           },
       .spells = {Enum::SHIELD}},
      {// torosar
       .index = 36,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = false,
       .secSkill =
           {
               {Enum::MYSTICISM, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
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
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// fafner
       .index = 37,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = false,
       .secSkill =
           {
               {Enum::SCHOLAR, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::NAGA,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::NAGA_QUEEN,
                   .val = 5,
               },
           },
       .spells = {Enum::HASTE}},
      {// rissa
       .index = 38,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = true,
       .secSkill =
           {
               {Enum::MYSTICISM, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_GENERATE_RESOURCE,
                   .subId = Enum::MERCURY,
                   .val = 1,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// iona
       .index = 39,
       .clasz = Enum::HERO_CLASS_ALCHEMIST, // 炼金术士 = 4
       .female = true,
       .secSkill =
           {
               {Enum::SCHOLAR, Enum::BASIC},
               {Enum::INTELLIGENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GENIE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MASTER_GENIE,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// astral
       .index = 40,
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
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::HYPNOTIZE,
                   .val = 3,
               },
           },
       .spells = {Enum::HYPNOTIZE}},
      {// halon
       .index = 41,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::MYSTICISM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
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
       .spells = {Enum::STONE_SKIN}},
      {// serena
       .index = 42,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
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
       .spells = {Enum::DISPEL}},
      {// daremyth
       .index = 43,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::INTELLIGENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
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
      {// theodorus
       .index = 44,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::BALLISTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MAGE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ARCH_MAGE,
                   .val = 5,
               },
           },
       .spells = {Enum::SHIELD}},
      {// solmyr
       .index = 45,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::CHAIN_LIGHTNING,
                   .val = 3,
               },
           },
       .spells = {Enum::CHAIN_LIGHTNING}},
      {// cyra
       .index = 46,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::DIPLOMACY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
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
      {// aine
       .index = 47,
       .clasz = Enum::HERO_CLASS_WIZARD, // 术士 = 5
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::SCHOLAR, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::GREMLIN, 15},
               {Enum::STONE_GARGOYLE, 8},
               {Enum::IRON_GOLEM, 4},
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
       .spells = {Enum::CURSE}},
  };
};