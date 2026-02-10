
#include "Enum/Enum.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct HeroSetSpec {
  uint8_t id;
  uint8_t subId;
  int32_t val;
};

struct HeroSetI {
  uint8_t index;
  uint8_t clasz; // class
  bool female;
  std::vector<std::pair<uint8_t, uint8_t>> secSkill;
  std::vector<std::pair<uint8_t, uint8_t>> defaultCre;
  std::string smallPor;
  std::string largePor;
  std::vector<HeroSetSpec> spec;
  uint64_t experience;
  std::set<uint8_t> spells;
};

struct CastleHeroSet {
  std::vector<HeroSetI> heros = {
      {// orrin
       .index = 0,
       .clasz = 0,
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
       .spells = {Enum::StoneSkin}},
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
                   .subId = Enum::Bless,
                   .val = 5,
               },
           },
       .spells = {Enum::Bless}},
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
                   .subId = Enum::Weakness,
                   .val = 5,
               },

           },
       .spells = {Enum::Weakness}},

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
                   .subId = Enum::FrostRing,
                   .val = 5,
               },

           },
       .spells = {Enum::FrostRing}},

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
       .spells = {Enum::Curse}},
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
       .spells = {Enum::Dispel}},

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
                   .subId = Enum::Prayer,
                   .val = 5,
               },

           },
       .spells = {Enum::Prayer}},
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