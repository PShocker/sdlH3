#pragma once

#include "Enum/Enum.h"
#include <cstdint>
#include <flat_set>
#include <string>
#include <vector>

struct BattleFieldSetBonuse {
  uint8_t id;
  uint8_t subId;
  int32_t val;
  std::flat_set<uint8_t> limitFaction;
};

struct BattleFieldSetI {
  uint8_t index;
  std::string graphics;
  std::vector<BattleFieldSetBonuse> bonuse;
  std::vector<uint8_t> impassableHexes;
};

struct BattleFieldSet {
  const static inline std::vector<BattleFieldSetI> battleFileds = {
      {
          .index = Enum::BATTLE_FIELD_SAND_SHORE,
          .graphics = "CMBKBCH.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_SAND_MESAS,
          .graphics = "CMBKDES.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_DIRT_BIRCHES,
          .graphics = "CMBKDRTR.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_DIRT_HILLS,
          .graphics = "CMBKDRMT.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_DIRT_PINES,
          .graphics = "CMBKDRDD.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_GRASS_HILLS,
          .graphics = "CMBKGRMT.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_GRASS_PINES,
          .graphics = "CMBKGRTR.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_LAVA,
          .graphics = "CMBKLAVA.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_MAGIC_PLAINS,
          .graphics = "CMBKMAG.pcx",
          .bonuse =
              {
                  {
                      .id = Enum::
                          BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, // MAGIC_SCHOOL_SKILL
                      .subId = Enum::FIRE_MAGIC,              // spellSchool.any
                      .val = 3,
                      .limitFaction = {},
                  },
                  {
                      .id = Enum::
                          BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, // MAGIC_SCHOOL_SKILL
                      .subId = Enum::AIR_MAGIC,               // spellSchool.any
                      .val = 3,
                      .limitFaction = {},
                  },
                  {
                      .id = Enum::
                          BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, // MAGIC_SCHOOL_SKILL
                      .subId = Enum::WATER_MAGIC,             // spellSchool.any
                      .val = 3,
                      .limitFaction = {},
                  },
                  {
                      .id = Enum::
                          BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, // MAGIC_SCHOOL_SKILL
                      .subId = Enum::EARTH_MAGIC,             // spellSchool.any
                      .val = 3,
                      .limitFaction = {},
                  },
              },
      },
      {
          .index = Enum::BATTLE_FIELD_SNOW_MOUNTAINS,
          .graphics = "CMBKSNMT.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_SNOW_TREES,
          .graphics = "CMBKSNTR.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_SUBTERRANEAN,
          .graphics = "CMBKSUB.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_SWAMP_TREES,
          .graphics = "CMBKSWMP.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_FIERY_FIELDS,
          .graphics = "CMBKFF.pcx",
          .bonuse =
              {
                  {
                      .id = Enum::BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, //
                      .subId = Enum::FIRE_MAGIC,                      //
                      .val = 3,
                      .limitFaction = {},
                  },
              },
      },
      {
          .index = Enum::BATTLE_FIELD_ROCKLANDS,
          .graphics = "CMBKRK.pcx",
          .bonuse =
              {
                  {
                      .id = Enum::BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, //
                      .subId = Enum::EARTH_MAGIC,                     //
                      .val = 3,
                      .limitFaction = {},
                  },
              },
      },
      {
          .index = Enum::BATTLE_FIELD_MAGIC_CLOUDS,
          .graphics = "CMBKMC.pcx",
          .bonuse =
              {
                  {
                      .id = Enum::BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, //
                      .subId = Enum::AIR_MAGIC,                       //
                      .val = 3,
                      .limitFaction = {},
                  },
              },
      },
      {
          .index = Enum::BATTLE_FIELD_LUCID_POOLS,
          .graphics = "CMBKLP.pcx",
          .bonuse =
              {
                  {
                      .id = Enum::BATTLE_FIELD_BONUSE_SECSKILL_LEVEL, //
                      .subId = Enum::WATER_MAGIC,                     //
                      .val = 3,
                      .limitFaction = {},
                  },
              },
      },
      {
          .index = Enum::BATTLE_FIELD_HOLY_GROUND,
          .graphics = "CMBKHG.pcx",
          .bonuse =
              {
                  {
                      .id = Enum::BATTLE_FIELD_BONUSE_MORALE, // MORALE
                      .subId = 0,
                      .val = 1,
                      .limitFaction = {Enum::FACTION_CASTLE}, // good
                  },
                  {
                      .id = Enum::BATTLE_FIELD_BONUSE_MORALE, // MORALE
                      .subId = 0,
                      .val = -1,
                      .limitFaction = {Enum::FACTION_NECROPOLIS}, // evil
                  },
              },
      },
      {
          .index = Enum::BATTLE_FIELD_CLOVER_FIELD,
          .graphics = "CMBKCF.pcx",
          .bonuse =
              {
                  {
                      .id = Enum::BATTLE_FIELD_BONUSE_LUCK, // LUCK
                      .subId = 0,
                      .val = 2,
                      .limitFaction = {Enum::FACTION_NEUTRAL}, // neutral
                  },
              },
      },
      {
          .index = Enum::BATTLE_FIELD_EVIL_FOG,
          .graphics = "CMBKEF.pcx",
          .bonuse = {{
                         .id = Enum::BATTLE_FIELD_BONUSE_MORALE, // MORALE
                         .subId = 0,
                         .val = -1,
                         .limitFaction = {Enum::FACTION_CASTLE}, // good
                     },
                     {
                         .id = Enum::BATTLE_FIELD_BONUSE_MORALE, // MORALE
                         .subId = 0,
                         .val = 1,
                         .limitFaction = {Enum::FACTION_NECROPOLIS}, // evil
                     }},
      },
      {
          .index = Enum::BATTLE_FIELD_CURSED_GROUND,
          .graphics = "CMBKCUR.pcx",
          .bonuse =
              {{
                   .id = Enum::BATTLE_FIELD_BONUSE_MAX_MORALE, // NO_MORALE
                   .subId = 0,
                   .val = 0,
                   .limitFaction = {},
               },
               {
                   .id = Enum::BATTLE_FIELD_BONUSE_MAX_LUCK, // NO_LUCK
                   .subId = 0,
                   .val = 0,
                   .limitFaction = {},
               },
               {
                   .id = Enum::
                       BATTLE_FIELD_BONUSE_SPELL_MAX_LEVEL, // BLOCK_MAGIC_ABOVE
                   .subId = 0,
                   .val = 1,
                   .limitFaction = {},
               }},
      },
      {
          .index = Enum::BATTLE_FIELD_ROUGH,
          .graphics = "CMBKRGH.pcx",
          .bonuse = {},
      },
      {
          .index = Enum::BATTLE_FIELD_SHIP_TO_SHIP,
          .graphics = "CMBKBOAT.pcx",
          .bonuse = {},
          .impassableHexes = {6,   7,   8,   9,   24,  25,  26,  58,
                              59,  60,  75,  76,  77,  92,  93,  94,
                              109, 110, 111, 126, 127, 128, 159, 160,
                              161, 162, 163, 176, 177, 178, 179, 180},
      },
      {
          .index = Enum::BATTLE_FIELD_SHIP,
          .graphics = "CMBKDECK.pcx",
          .bonuse = {},
      },
  };
};