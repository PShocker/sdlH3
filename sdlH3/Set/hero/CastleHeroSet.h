#pragma once

#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>


struct CastleHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// orrin (index 0) - Knight
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
       .smallPor = "HPS000KN.pcx", // Knight 第1个
       .largePor = "HPL000KN.pcx", // Knight 第1个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::ARCHERY,
                   .val = 5,
               },
           }},
      {// valeska (index 1) - Knight
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
       .smallPor = "HPS001KN.pcx", // Knight 第2个
       .largePor = "HPL001KN.pcx", // Knight 第2个
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
      {// edric (index 2) - Knight
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
       .smallPor = "HPS002KN.pcx", // Knight 第3个
       .largePor = "HPL002KN.pcx", // Knight 第3个
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
      {// sylvia (index 3) - Knight
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
       .smallPor = "HPS003KN.pcx", // Knight 第4个
       .largePor = "HPL003KN.pcx", // Knight 第4个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::NAVIGATION,
                   .val = 5,
               },
           }},
      {// lordHaart (index 4) - Knight
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
       .smallPor = "HPS004KN.pcx", // Knight 第5个
       .largePor = "HPL004KN.pcx", // Knight 第5个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::ESTATES,
                   .val = 5,
               },

           }},
      {// sorsha (index 5) - Knight
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
       .smallPor = "HPS005KN.pcx", // Knight 第6个
       .largePor = "HPL005KN.pcx", // Knight 第6个
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

      {// christian (index 6) - Knight
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
       .smallPor = "HPS006KN.pcx", // Knight 第7个
       .largePor = "HPL006KN.pcx", // Knight 第7个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BALLISTA,
                   .val = 5,
               },
           }},
      {// tyris (index 7) - Knight
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
       .smallPor = "HPS007KN.pcx", // Knight 第8个
       .largePor = "HPL007KN.pcx", // Knight 第8个
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
      {// rion (index 8) - Cleric
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
       .smallPor = "HPS008CL.pcx", // Cleric 第1个
       .largePor = "HPL008CL.pcx", // Cleric 第1个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::FIRST_AID,
                   .val = 5,
               },

           },
       .spells = {Enum::STONE_SKIN}},
      {// adela (index 9) - Cleric
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
       .smallPor = "HPS009CL.pcx", // Cleric 第2个
       .largePor = "HPL009CL.pcx", // Cleric 第2个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::BLESS,
                   .val = 5,
               },
           },
       .spells = {Enum::BLESS}},
      {// cuthbert (index 10) - Cleric
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
       .smallPor = "HPS010CL.pcx", // Cleric 第3个
       .largePor = "HPL010CL.pcx", // Cleric 第3个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::WEAKNESS,
                   .val = 5,
               },

           },
       .spells = {Enum::WEAKNESS}},

      {// adelaide (index 11) - Cleric
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
       .smallPor = "HPS011CL.pcx", // Cleric 第4个
       .largePor = "HPL011CL.pcx", // Cleric 第4个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::FROST_RING,
                   .val = 5,
               },

           },
       .spells = {Enum::FROST_RING}},

      {// ingham (index 12) - Cleric
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
       .smallPor = "HPS012CL.pcx", // Cleric 第5个
       .largePor = "HPL012CL.pcx", // Cleric 第5个
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
      {// sanya (index 13) - Cleric
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
       .smallPor = "HPS013CL.pcx", // Cleric 第6个
       .largePor = "HPL013CL.pcx", // Cleric 第6个
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::EAGLE_EYE,
                   .val = 5,
               },

           },
       .spells = {Enum::DISPEL}},

      {// loynis (index 14) - Cleric
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
       .smallPor = "HPS014CL.pcx", // Cleric 第7个
       .largePor = "HPL014CL.pcx", // Cleric 第7个
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
          // caitlin (index 15) - Cleric
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
          .smallPor = "HPS015CL.pcx", // Cleric 第8个
          .largePor = "HPL015CL.pcx", // Cleric 第8个
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