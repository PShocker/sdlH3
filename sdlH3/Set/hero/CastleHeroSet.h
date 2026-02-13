#pragma once

#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct CastleHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// orrin
       .index = 0,
       .clasz = Enum::HERO_CLASS_KNIGHT,
       .female = false,
       .secSkill = {{Enum::LEADERSHIP, Enum::BASIC},
                    {Enum::ARCHERY, Enum::BASIC}},
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::ARCHERY,
                   .val = 5,
               },
           }},
      {// valeska
       .index = 1,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::ARCHERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::ARCHER, 7},
               {Enum::ARCHER, 7},
               {Enum::ARCHER, 7},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ARCHER,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MARKSMAN,
                   .val = 5,
               },
           }},
      {// edric
       .index = 2,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::ARMORER, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::GRIFFIN, 3},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::GRIFFIN,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ROYAL_GRIFFIN,
                   .val = 5,
               },
           }},
      {// sylvia
       .index = 3,
       .clasz = 0,
       .female = true,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::NAVIGATION, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
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
           }},
      {// lordHaart
       .index = 4,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::ESTATES, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::ESTATES,
                   .val = 5,
               },

           }},
      {// sorsha
       .index = 5,
       .clasz = 0,
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
       .smallPor = "",
       .largePor = "",
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

      {// christian
       .index = 6,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::ARTILLERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::BALLISTA, 1},
               {Enum::GRIFFIN, 3},
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
      {// tyris
       .index = 7,
       .clasz = 0,
       .female = true,
       .secSkill =
           {
               {Enum::LEADERSHIP, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::CAVALIER,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::CHAMPION,
                   .val = 5,
               },
           }},
      {// rion
       .index = 8,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::FIRST_AID, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::FIRST_AID_TENT, 1},
               {Enum::GRIFFIN, 3},
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
       .spells = {Enum::STONE_SKIN}},
      {// adela
       .index = 9,
       .clasz = 0,
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::DIPLOMACY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::BLESS,
                   .val = 5,
               },
           },
       .spells = {Enum::BLESS}},
      {// cuthbert
       .index = 10,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::ESTATES, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
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

      {// adelaide
       .index = 11,
       .clasz = 0,
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::FROST_RING,
                   .val = 5,
               },

           },
       .spells = {Enum::FROST_RING}},

      {// ingham
       .index = 12,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::MYSTICISM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::MONK,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ZEALOT,
                   .val = 5,
               },
           },
       .spells = {Enum::CURSE}},
      {// sanya
       .index = 13,
       .clasz = 0,
       .female = true,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
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

      {// loynis
       .index = 14,
       .clasz = 0,
       .female = false,
       .secSkill =
           {
               {Enum::WISDOM, Enum::BASIC},
               {Enum::LEARNING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::PIKEMAN, 20},
               {Enum::ARCHER, 7},
               {Enum::GRIFFIN, 3},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::PRAYER,
                   .val = 5,
               },

           },
       .spells = {Enum::PRAYER}},
      {
          // caitlin
          .index = 15,
          .clasz = 0,
          .female = true,
          .secSkill =
              {
                  {Enum::WISDOM, Enum::BASIC},
                  {Enum::INTELLIGENCE, Enum::BASIC},
              },
          .defaultCre =
              {
                  {Enum::PIKEMAN, 20},
                  {Enum::ARCHER, 7},
                  {Enum::GRIFFIN, 3},
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
      },
  };
};