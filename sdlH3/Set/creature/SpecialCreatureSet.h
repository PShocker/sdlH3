#pragma once
#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstddef>
#include <vector>

struct SpecialCreatureSet {
  const static inline std::vector<CreatureSetI> creatures = {
      {
          .index = 122,
          .level = 0,
          .growth = 0,
      },
      {
          .index = 124,
          .level = 0,
          .growth = 0,
      },
      {
          .index = 126,
          .level = 0,
          .growth = 0,
      },
      {
          .index = 128,
          .level = 0,
          .growth = 0,
      },
      {
          // catapult
          .index = 145,
          .level = 0,
          .female = false,
          .faction = Enum::FACTION_NEUTRAL,
          .upgrades = {},
          .graphics =
              {
                  .animation = "SMCATA.DEFF",
                  .missile = "SMCATX.DEF",
                  .adventure = "",
              },
          .sounds =
              {
                  .attack = "",
                  .defend = "",
                  .killed = "CATAKILL.wav",
                  .move = "",
                  .shoot = "CATASHOT.wav",
                  .wince = "CATAWNCE.wav",
              },
          .attribute = {10, 4, 4, 5, 1, 3, 0},
          .abilities =
              {
                  {Enum::DOUBLE_WIDE, NULL},
                  {Enum::WAR_MACHINE, Enum::MACH4},

              },
          .growth = 1,
          .experience = 3, // artifactId
          .cost = {0, 0, 0, 0, 0, 0, 60},
          .hasDoubleWeek = false,
      },
      {
          // ballista
          .index = 146,
          .level = 0,
          .female = false,
          .faction = Enum::FACTION_NEUTRAL,
          .upgrades = {},
          .graphics =
              {
                  .animation = "SMBAL.DEF",
                  .missile = "SMBALX.DEF",
                  .adventure = "",
              },
          .sounds =
              {
                  .attack = "",
                  .defend = "",
                  .killed = "BALLKILL.wav",
                  .move = "",
                  .shoot = "BALLSHOT.wav",
                  .wince = "BALLWNCE.wav",
              },
          .attribute = {10, 4, 4, 5, 1, 3, 0},
          .abilities =
              {
                  {Enum::DOUBLE_WIDE, NULL},
                  {Enum::SHOOTING_ARMY, NULL},
                  {Enum::WAR_MACHINE, Enum::MACH3},

              },
          .growth = 1,
          .experience = 4,
          .cost = {0, 0, 0, 0, 0, 0, 60},
          .hasDoubleWeek = false,
      },
      {
          // firstAidTent
          .index = 147,
          .level = 0,
          .female = false,
          .faction = Enum::FACTION_NEUTRAL,
          .upgrades = {},
          .graphics =
              {
                  .animation = "SMTENT.DEF",
                  .missile = "",
                  .adventure = "",
              },
          .sounds =
              {
                  .attack = "",
                  .defend = "",
                  .killed = "FAIDKILL.wav",
                  .move = "",
                  .shoot = "",
                  .wince = "FAIDWNCE.wav",
              },
          .attribute = {10, 4, 4, 5, 1, 3, 0},
          .abilities =
              {
                  {Enum::DOUBLE_WIDE, NULL},
                  {Enum::WAR_MACHINE, Enum::MACH1},
              },
          .growth = 1,
          .experience = 6,
          .cost = {0, 0, 0, 0, 0, 0, 60},
          .hasDoubleWeek = false,
      },
      {
          // ammoCart
          .index = 148,
          .level = 0,
          .female = false,
          .faction = Enum::FACTION_NEUTRAL,
          .upgrades = {},
          .graphics =
              {
                  .animation = "SMCART.DEF",
                  .missile = "",
                  .adventure = "",
              },
          .sounds =
              {
                  .attack = "",
                  .defend = "",
                  .killed = "CARTKILL.wav",
                  .move = "",
                  .shoot = "",
                  .wince = "CARTWNCE.wav",
              },
          .attribute = {10, 4, 4, 5, 1, 3, 0},
          .abilities =
              {
                  {Enum::WAR_MACHINE, Enum::MACH2},
              },
          .growth = 1,
          .experience = 5,
          .cost = {0, 0, 0, 0, 0, 0, 60},
          .hasDoubleWeek = false,
      },
  };
};