#include "/Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

struct RampartCreatureSet {
  const static inline std::vector<CreatureSetI> creatures =
      {
          {
              // centaur
              .index = 14,
              .level = 1,
              .female = false,
              .faction = Enum::RAMPART,
              .upgrades = {Enum::CENTAUR_CAPTAIN},
              .graphics =
                  {
                      .animation = "CCENTR.DEF",
                      .missile = "",
                      .adventure = "AvWPike.def",
                  },
              .sounds =
                  {
                      .attack = "CNTRATTK.wav",
                      .defend = "CNTRDFND.wav",
                      .killed = "CNTRKILL.wav",
                      .move = "CNTRMOVE.wav",
                      .wince = "CNTRWNCE.wav",
                  },
              .attribute = {10, 4, 4, 5, 1, 3, 0},
              .abilities = {{Enum::DOUBLE_WIDE, NULL}},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 60},
              .hasDoubleWeek = true,
          },
          {// centaurCaptain
           .index = 15,
           .level = 1,
           .female = false,
           .faction = Enum::RAMPART,
           .upgrades = {},
           .graphics =
               {
                   .animation = "CECENT.DEF",
                   .missile = "",
                   .adventure = "AVWpikx0.def",
               },
           .sounds =
               {
                   .attack = "ECNTATTK.wav",
                   .defend = "ECNTDFND.wav",
                   .killed = "ECNTKILL.wav",
                   .move = "ECNTMOVE.wav",
                   .wince = "ECNTWNCE.wav",
               },
           .attribute = {10, 5, 6, 5, 2, 3, 0},
           .abilities = {{Enum::IMMUNE_TO_CAVALRY, NULL}},
           .growth = 14,
           .experience = 10,
           .cost = {0, 0, 0, 0, 0, 0, 75}},
          {// dwarf
           .index = 16,
           .level = 2,
           .female = false,
           .faction = Enum::RAMPART,
           .upgrades = {Enum::BATTLE_DWARF},
           .graphics =
               {
                   .animation = "CDWARF.DEF",
                   .missile = "",
                   .adventure = "",
               },
           .sounds =
               {
                   .attack = "DWRFATTK.wav",
                   .defend = "DWRFDFND.wav",
                   .killed = "DWRFKILL.wav",
                   .move = "DWRFMOVE.wav",
                   .shoot = "",
                   .wince = "DWRFWNCE.wav",
               },
           .attribute = {10, 4, 6, 3, 2, 3, 12},
           .abilities = {{Enum::MAGIC_RESISTANCE, 20}},
           .growth = 14,
           .experience = 10,
           .cost = {0, 0, 0, 0, 0, 0, 100}},
          {// battleDwarf
           .index = 17,
           .level = 2,
           .female = false,
           .faction = Enum::RAMPART,
           .upgrades = {},
           .graphics =
               {
                   .animation = "CBDWAR.DEF",
                   .missile = "",
                   .adventure = "AvWHCrs.def",
               },
           .sounds =
               {
                   .attack = "BDRFATTK.wav",
                   .defend = "BDRFDFND.wav",
                   .killed = "BDRFKILL.wav",
                   .move = "BDRFMOVE.wav",
                   .shoot = "",
                   .wince = "BDRFWNCE.wav",
               },
           .attribute = {10, 6, 6, 3, 2, 3, 24},
           .abilities = {{Enum::MAGIC_RESISTANCE, 40}},
           .growth = 14,
           .experience = 10,
           .cost = {0, 0, 0, 0, 0, 0, 150}},
          {
              // woodElf
              .index = 18,
              .level = 3,
              .female = false,
              .faction = Enum::RAMPART,
              .upgrades = {Enum::GRAND_ELF},
              .graphics =
                  {
                      .animation = "CELF.DEF",
                      .missile = "CELF.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "WELFATTK.wav",
                      .defend = "WELFDFND.wav",
                      .killed = "WELFKILL.wav",
                      .move = "WELFMOVE.wav",
                      .shoot = "WELFSHOT.wav",
                      .wince = "WELFWNCE.wav",
                  },
              .attribute = {25, 6, 8, 8, 3, 6, 0},
              .abilities =
                  {
                      {Enum::SHOOTING_ARMY, NULL},
                      {Enum::const_two_distance_attacks, NULL},
                  },
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 200},
              .hasDoubleWeek = true,
          },
          {
              // grandElf
              .index = 19,
              .level = 3,
              .female = false,
              .faction = Enum::RAMPART,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CGRELF.DEF",
                      .missile = "PELFX.DEF",
                      .adventure = "AVWgrix0.def",
                  },
              .sounds =
                  {
                      .attack = "GELFATTK.wav",
                      .defend = "GELFDFND.wav",
                      .killed = "GELFKILL.wav",
                      .move = "GELFMOVE.wav",
                      .shoot = "GELFSHOT.wav",
                      .wince = "GELFWNCE.wav",
                  },
              .attribute = {25, 9, 9, 9, 3, 6, 0},
              .abilities =
                  {
                      {Enum::SHOOTING_ARMY, NULL},
                      {Enum::const_two_distance_attacks, NULL},
                  },
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 240},
          },
          {
              // pegasus
              .index = 20,
              .level = 4,
              .female = false,
              .faction = Enum::RAMPART,
              .upgrades = {Enum::SILVER_PEGASUS},
              .graphics =
                  {
                      .animation = "CSWORD.DEF",
                      .missile = "",
                      .adventure = "AVWswrd0.def",
                  },
              .sounds =
                  {
                      .attack = "PEGAATTK.wav",
                      .defend = "PEGADFND.wav",
                      .killed = "PEGAKILL.wav",
                      .move = "PEGAMOVE.wav",
                      .wince = "PEGAWNCE.wav",
                  },
              .attribute = {35, 5, 10, 12, 6, 9, 0},
              .abilities =
                  {
                      {Enum::DOUBLE_WIDE, NULL},
                      {Enum::const_enemy_spell_cost, 2},
                  },
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
          },
          {
              // silverPegasus
              .index = 21,
              .level = 4,
              .female = false,
              .faction = Enum::RAMPART,
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
              .abilities =
                  {
                      {Enum::DOUBLE_WIDE, NULL},
                      {Enum::const_enemy_spell_cost, 2},
                  },
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 400},
          },
          {
              // dendroidGuard
              .index = 22,
              .level = 5,
              .female = false,
              .faction = Enum::RAMPART,
              .upgrades = {Enum::DENDROID_SOLDIER},
              .graphics =
                  {
                      .animation = "CTREE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "TREEATTK.wav",
                      .defend = "TREEDFND.wav",
                      .killed = "TREEKILL.wav",
                      .move = "TREEMOVE.wav",
                      .shoot = "",
                      .wince = "TREEWNCE.wav",
                  },
              .attribute = {30, 5, 12, 7, 10, 12, 12},
              .abilities =
                  {
                      {Enum::const_spell_attack,
                       std::vector<CreatureSetSpellEx>{
                           {.type=Enum::bind},
                       }},
                  },
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
          },
          {
              // zealot
              .index = 9,
              .level = 5,
              .female = false,
              .faction = Enum::RAMPART,
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
              .abilities =
                  {
                      {Enum::SHOOTING_ARMY, NULL},
                      {Enum::const_no_melee_penalty, NULL},
                  },
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 450},
          },
          {
              // cavalier
              .index = 10,
              .level = 6,
              .female = false,
              .faction = Enum::RAMPART,
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
              .abilities = {{Enum::DOUBLE_WIDE, NULL},
                            {Enum::const_jousting, 5}},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
          },
          {
              // champion
              .index = 11,
              .level = 6,
              .female = false,
              .faction = Enum::RAMPART,
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
              .abilities = {{Enum::DOUBLE_WIDE, NULL},
                            {Enum::const_jousting, 5}},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1200},
          },
          {
              // angel
              .index = 12,
              .level = 7,
              .female = false,
              .faction = Enum::RAMPART,
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
              .faction = Enum::RAMPART,
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
          }};
};