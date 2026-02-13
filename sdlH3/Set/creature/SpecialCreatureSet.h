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
          .abilities = {},
          .growth = 1,
          .experience = 10,
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
          .abilities = {},
          .growth = 1,
          .experience = 10,
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
          .abilities = {},
          .growth = 1,
          .experience = 10,
          .cost = {0, 0, 0, 0, 0, 0, 60},
          .hasDoubleWeek = false,
      },
  };
};