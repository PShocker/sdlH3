#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

struct CastleCreatureSet {
  const static inline std::vector<CreatureSetI> creatures = {
      {// pikeman
       .index = 0,
       .level = 1,
       .female = false,
       .faction = Enum::FACTION_CASTLE,
       .upgrades = {Enum::HALBERDIER},
       .graphics =
           {
               .animation = "CPKMAN.DEF",
               .missile = "",
               .adventure = "AvWPike.def",
           },
       .sounds =
           {
               .attack = "PIKEATTK.wav",
               .defend = "PIKEDFND.wav",
               .killed = "PIKEKILL.wav",
               .move = "PIKEMOVE.wav",
               .wince = "PIKEWNCE.wav",
           },
       .attribute = {10, 4, 4, 5, 1, 3, 0},
       .abilities = {{Enum::IMMUNE_TO_CAVALRY, NULL}},
       .growth = 14,
       .experience = 10,
       .cost = {0, 0, 0, 0, 0, 0, 60}},
      {// halberdier
       .index = 1,
       .level = 1,
       .female = false,
       .faction = Enum::FACTION_CASTLE,
       .upgrades = {},
       .graphics =
           {
               .animation = "CHALBD.DEF",
               .missile = "",
               .adventure = "AVWpikx0.def",
           },
       .sounds =
           {
               .attack = "HALBATTK.wav",
               .defend = "HALBDFND.wav",
               .killed = "HALBKILL.wav",
               .move = "HALBMOVE.wav",
               .wince = "HALBWNCE.wav",
           },
       .attribute = {10, 5, 6, 5, 2, 3, 0},
       .abilities = {{Enum::IMMUNE_TO_CAVALRY, NULL}},
       .growth = 14,
       .experience = 10,
       .cost = {0, 0, 0, 0, 0, 0, 75}},
      {// archer
       .index = 2,
       .level = 2,
       .female = false,
       .faction = Enum::FACTION_CASTLE,
       .upgrades = {Enum::MARKSMAN},
       .graphics =
           {
               .animation = "CLCBOW.DEF",
               .missile = "PLCBOWX.DEF",
               .adventure = "AvWLCrs.def",
           },
       .sounds =
           {
               .attack = "LCRSATTK.wav",
               .defend = "LCRSDFND.wav",
               .killed = "LCRSKILL.wav",
               .move = "LCRSMOVE.wav",
               .shoot = "LCRSSHOT.wav",
               .wince = "LCRSWNCE.wav",
           },
       .attribute = {10, 4, 6, 3, 2, 3, 12},
       .abilities = {{Enum::SHOOTING_ARMY, NULL}},
       .growth = 14,
       .experience = 10,
       .cost = {0, 0, 0, 0, 0, 0, 100}},
      {// marksman
       .index = 3,
       .level = 2,
       .female = false,
       .faction = Enum::FACTION_CASTLE,
       .upgrades = {},
       .graphics =
           {
               .animation = "CHCBOW.DEF",
               .missile = "PLCBOWX.DEF",
               .adventure = "AvWHCrs.def",
           },
       .sounds =
           {
               .attack = "HCRSATTK.wav",
               .defend = "HCRSDFND.wav",
               .killed = "HCRSKILL.wav",
               .move = "HCRSMOVE.wav",
               .shoot = "HCRSSHOT.wav",
               .wince = "HCRSWNCE.wav",
           },
       .attribute = {10, 6, 6, 3, 2, 3, 24},
       .abilities = {{Enum::SHOOTING_ARMY, NULL},
                     {Enum::const_two_distance_attacks, NULL}},
       .growth = 14,
       .experience = 10,
       .cost = {0, 0, 0, 0, 0, 0, 150}},
      {
          // griffin
          .index = 4,
          .level = 3,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {Enum::ROYAL_GRIFFIN},
          .graphics =
              {
                  .animation = "CGRIFF.DEF",
                  .missile = "",
                  .adventure = "AvWGrif.def",
              },
          .sounds =
              {
                  .attack = "GRIFATTK.wav",
                  .defend = "GRIFDFND.wav",
                  .killed = "GRIFKILL.wav",
                  .move = "GRIFMOVE.wav",
                  .wince = "GRIFWNCE.wav",
              },
          .attribute = {25, 6, 8, 8, 3, 6, 0},
          .abilities = {{Enum::DOUBLE_WIDE, NULL},
                        {Enum::FLYING_ARMY, NULL},
                        {Enum::const_two_retaliation, NULL}},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 200},
          .hasDoubleWeek = true,
      },
      {
          // royalGriffin
          .index = 5,
          .level = 3,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {},
          .graphics =
              {
                  .animation = "CRGRIF.DEF",
                  .missile = "",
                  .adventure = "AVWgrix0.def",
              },
          .sounds =
              {
                  .attack = "RGRFATTK.wav",
                  .defend = "RGRFDFND.wav",
                  .killed = "RGRFKILL.wav",
                  .move = "RGRFMOVE.wav",
                  .wince = "RGRFWNCE.wav",
              },
          .attribute = {25, 9, 9, 9, 3, 6, 0},
          .abilities = {{Enum::DOUBLE_WIDE, NULL},
                        {Enum::FLYING_ARMY, NULL},
                        {Enum::const_unlimit_retaliation, NULL}},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 240},
      },
      {
          // swordsman
          .index = 6,
          .level = 4,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {Enum::CRUSADER},
          .graphics =
              {
                  .animation = "CSWORD.DEF",
                  .missile = "",
                  .adventure = "AVWswrd0.def",
              },
          .sounds =
              {
                  .attack = "SWRDATTK.wav",
                  .defend = "SWRDDFND.wav",
                  .killed = "SWRDKILL.wav",
                  .move = "SWRDMOVE.wav",
                  .wince = "SWRDWNCE.wav",
              },
          .attribute = {35, 5, 10, 12, 6, 9, 0},
          .abilities = {},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 300},
      },
      {
          // crusader
          .index = 7,
          .level = 4,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {},
          .graphics =
              {
                  .animation = "CCRUSD.DEF",
                  .missile = "",
                  .adventure = "AVWswrx0.def",
              },
          .sounds =
              {
                  .attack = "CRUSATTK.wav",
                  .defend = "CRUSDFND.wav",
                  .killed = "CRUSKILL.wav",
                  .move = "CRUSMOVE.wav",
                  .wince = "CRUSWNCE.wav",
              },
          .attribute = {35, 6, 12, 12, 7, 10, 0},
          .abilities = {{Enum::const_two_attacks, NULL}},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 400},
      },
      {
          // monk
          .index = 8,
          .level = 5,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {Enum::ZEALOT},
          .graphics =
              {
                  .animation = "CMONKK.DEF",
                  .missile = "CPRZEAX.DEF",
                  .adventure = "AvWMonk.def",
              },
          .sounds =
              {
                  .attack = "MONKATTK.wav",
                  .defend = "MONKDFND.wav",
                  .killed = "MONKKILL.wav",
                  .move = "MONKMOVE.wav",
                  .shoot = "MONKSHOT.wav",
                  .wince = "MONKWNCE.wav",
              },
          .attribute = {30, 5, 12, 7, 10, 12, 12},
          .abilities = {{Enum::SHOOTING_ARMY, NULL},
                        {Enum::const_no_melee_penalty, NULL}},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 300},
      },
      {
          // zealot
          .index = 9,
          .level = 5,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {},
          .graphics =
              {
                  .animation = "CZEALT.DEF",
                  .missile = "CPRZEAX.DEF",
                  .adventure = "AVWmonx0.def",
              },
          .sounds =
              {
                  .attack = "ZELTATTK.wav",
                  .defend = "ZELTDFND.wav",
                  .killed = "ZELTKILL.wav",
                  .move = "ZELTMOVE.wav",
                  .shoot = "ZELTSHOT.wav",
                  .wince = "ZELTWNCE.wav",
              },
          .attribute = {30, 7, 12, 10, 10, 12, 24},
          .abilities = {{Enum::SHOOTING_ARMY, NULL},
                        {Enum::const_no_melee_penalty, NULL}},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 450},
      },
      {
          // cavalier
          .index = 10,
          .level = 6,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {Enum::CHAMPION},
          .graphics =
              {
                  .animation = "CCAVLR.DEF",
                  .missile = "",
                  .adventure = "AVWcvlr0.def",
              },
          .sounds =
              {
                  .attack = "CAVAATTK.wav",
                  .defend = "CAVADFND.wav",
                  .killed = "CAVAKILL.wav",
                  .move = "CAVAMOVE.wav",
                  .shoot = "",
                  .wince = "CAVAWNCE.wav",
              },
          .attribute = {100, 7, 15, 15, 15, 25, 0},
          .abilities = {{Enum::DOUBLE_WIDE, NULL}, {Enum::const_jousting, 5}},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 1000},
      },
      {
          // champion
          .index = 11,
          .level = 6,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {},
          .graphics =
              {
                  .animation = "CCHAMP.DEF",
                  .missile = "",
                  .adventure = "AVWcvlx0.def",
              },
          .sounds =
              {
                  .attack = "CHMPATTK.wav",
                  .defend = "CHMPDFND.wav",
                  .killed = "CHMPKILL.wav",
                  .move = "CHMPMOVE.wav",
                  .shoot = "",
                  .wince = "CHMPWNCE.wav",
              },
          .attribute = {100, 9, 16, 16, 20, 25, 0},
          .abilities = {{Enum::DOUBLE_WIDE, NULL}, {Enum::const_jousting, 5}},
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 1200},
      },
      {
          // angel
          .index = 12,
          .level = 7,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {Enum::ARCHANGEL},
          .graphics =
              {
                  .animation = "CANGEL.DEF",
                  .missile = "",
                  .adventure = "AvWAngl.def",
              },
          .sounds =
              {
                  .attack = "ANGLATTK.wav",
                  .defend = "ANGLDFND.wav",
                  .killed = "ANGLKILL.wav",
                  .move = "ANGLMOVE.wav",
                  .shoot = "",
                  .wince = "ANGLWNCE.wav",
              },
          .attribute = {200, 12, 20, 20, 50, 50, 0},
          .abilities =
              {
                  {Enum::const_raises_morale, 1},
                  {Enum::const_hate,
                   std::map<uint16_t, float>{
                       {Enum::DEVIL, 0.5},
                       {Enum::ARCH_DEVIL, 0.5},
                   }},
                  {Enum::FLYING_ARMY, NULL},

              },
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 1000},
      },
      {
          // archangel
          .index = 13,
          .level = 7,
          .female = false,
          .faction = Enum::FACTION_CASTLE,
          .upgrades = {},
          .graphics =
              {
                  .animation = "CRANGL.DEF",
                  .missile = "",
                  .adventure = "AvWAngl.def",
              },
          .sounds =
              {
                  .attack = "AAGLATTK.wav",
                  .defend = "AAGLDFND.wav",
                  .killed = "AAGLKILL.wav",
                  .move = "AAGLMOVE.wav",
                  .shoot = "",
                  .wince = "AAGLWNCE.wav",
              },
          .attribute = {200, 12, 20, 20, 50, 50, 0},
          .abilities =
              {
                  {Enum::const_raises_morale, 1},
                  {Enum::const_hate,
                   std::map<uint16_t, float>{
                       {Enum::DEVIL, 0.5},
                       {Enum::ARCH_DEVIL, 0.5},
                   }},
                  {Enum::FLYING_ARMY, NULL},
                  {Enum::DOUBLE_WIDE, NULL},
                  {Enum::const_spell,
                   std::vector<CreatureSetSpell>{
                       {
                           .type = Enum::Resurrection,
                           .power = 100,
                           .level = 3,
                           .spellPoint = 1,
                       },
                   }},
              },
          .growth = 14,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 1000},
      },
  };
};