#pragma once
#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

struct NeutralCreatureSet {
  const static inline std::vector<CreatureSetI> creatures =
      {
          {
              // goldGolem
              .index = 116,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CGGOLE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "GGLMATTK.wav",
                      .defend = "GGLMDFND.wav",
                      .killed = "GGLMKILL.wav",
                      .move = "GGLMMOVE.wav",
                      .shoot = "",
                      .wince = "GGLMWNCE.wav",
                  },
              .attribute = {35, 5, 10, 12, 6, 9, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // diamondGolem
              .index = 117,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CDGOLE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "DGLMATTK.wav",
                      .defend = "DGLMDFND.wav",
                      .killed = "DGLMKILL.wav",
                      .move = "DGLMMOVE.wav",
                      .shoot = "",
                      .wince = "DGLMWNCE.wav",
                  },
              .attribute = {30, 5, 12, 7, 10, 12, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // azureDragon
              .index = 132,
              .level = 10,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CADRGN.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "AZURATTK.wav",
                      .defend = "AZURDFND.wav",
                      .killed = "AZURKILL.wav",
                      .move = "AZURMOVE.wav",
                      .shoot = "",
                      .wince = "AZURWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // crystalDragon
              .index = 133,
              .level = 10,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CCDRGN.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "CRYSATTK.wav",
                      .defend = "CRYSDFND.wav",
                      .killed = "CRYSKILL.wav",
                      .move = "CRYSMOVE.wav",
                      .shoot = "",
                      .wince = "CRYSWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // fairieDragon
              .index = 134,
              .level = 8,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CFDRGN.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "FAERATTK.wav",
                      .defend = "FAERDFND.wav",
                      .killed = "FAERKILL.wav",
                      .move = "FAERMOVE.wav",
                      .shoot = "FAERSHOT.wav",
                      .wince = "FAERWNCE.wav",
                  },
              .attribute = {100, 9, 16, 16, 20, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1200},
              .hasDoubleWeek = false,
          },
          {
              // rustDragon
              .index = 135,
              .level = 10,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CRSDGN.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "RUSTATTK.wav",
                      .defend = "RUSTDFND.wav",
                      .killed = "RUSTKILL.wav",
                      .move = "RUSTMOVE.wav",
                      .shoot = "",
                      .wince = "RUSTWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // enchanter
              .index = 136,
              .level = 6,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "Cench.DEF",
                      .missile = "CPRZEAX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "ENCHATTK.wav",
                      .defend = "ENCHDFND.wav",
                      .killed = "ENCHKILL.wav",
                      .move = "ENCHMOVE.wav",
                      .shoot = "ENCHSHOT.wav",
                      .wince = "ENCHWNCE.wav",
                  },
              .attribute = {100, 7, 15, 15, 15, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // sharpshooter
              .index = 137,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CSHARP.DEF",
                      .missile = "PELFX.DEF",
                      .adventure = "",
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
              .attribute = {35, 6, 12, 12, 7, 10, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 400},
              .hasDoubleWeek = false,
          },
          {
              // halfling
              .index = 138,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CHALF.DEF",
                      .missile = "PHALF.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "HALFATTK.wav",
                      .defend = "HALFDFND.wav",
                      .killed = "HALFKILL.wav",
                      .move = "HALFMOVE.wav",
                      .shoot = "HALFSHOT.wav",
                      .wince = "HALFWNCE.wav",
                  },
              .attribute = {10, 5, 6, 5, 2, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 75},
              .hasDoubleWeek = false,
          },
          {
              // peasant
              .index = 139,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CPEAS.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "PSNTATTK.wav",
                      .defend = "PSNTDFND.wav",
                      .killed = "PSNTKILL.wav",
                      .move = "PSNTMOVE.wav",
                      .shoot = "",
                      .wince = "PSNTWNCE.wav",
                  },
              .attribute = {10, 4, 4, 5, 1, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 60},
              .hasDoubleWeek = false,
          },
          {
              // boar
              .index = 140,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CBOAR.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "BOARATTK.wav",
                      .defend = "BOARDFND.wav",
                      .killed = "BOARKILL.wav",
                      .move = "BOARMOVE.wav",
                      .shoot = "",
                      .wince = "BOARWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 150},
              .hasDoubleWeek = false,
          },
          {
              // mummy
              .index = 141,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CMUMMY.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "MUMYATTK.wav",
                      .defend = "MUMYDFND.wav",
                      .killed = "MUMYKILL.wav",
                      .move = "MUMYMOVE.wav",
                      .shoot = "",
                      .wince = "MUMYWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 250},
              .hasDoubleWeek = false,
          },
          {
              // nomad
              .index = 142,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CNOMAD.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "NMADATTK.wav",
                      .defend = "NMADDFND.wav",
                      .killed = "NMADKILL.wav",
                      .move = "NMADMOVE.wav",
                      .shoot = "",
                      .wince = "NMADWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 250},
              .hasDoubleWeek = false,
          },
          {
              // rogue
              .index = 143,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CROGUE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "ROGUATTK.wav",
                      .defend = "ROGUDFND.wav",
                      .killed = "ROGUKILL.wav",
                      .move = "ROGUMOVE.wav",
                      .shoot = "",
                      .wince = "ROGUWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 150},
              .hasDoubleWeek = false,
          },
          {
              // troll
              .index = 144,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_NEUTRAL,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CTROLL.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "TRLLATTK.wav",
                      .defend = "TRLLDFND.wav",
                      .killed = "TRLLKILL.wav",
                      .move = "TRLLMOVE.wav",
                      .shoot = "",
                      .wince = "TRLLWNCE.wav",
                  },
              .attribute = {30, 7, 12, 10, 10, 12, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 450},
              .hasDoubleWeek = false,
          }};
};