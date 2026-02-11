#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

struct ConfluxCreatureSet {
  const static inline std::vector<CreatureSetI>
      creatures =
          {
              {
                  // pixie
                  .index = 118,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = { Enum::SPRITE },
                  .graphics =
                      {
                          .animation = "CPIXIE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "PIXIATTK.wav",
                          .defend = "PIXIDFND.wav",
                          .killed = "PIXIKILL.wav",
                          .move = "PIXIMOVE.wav",
                          .shoot = "",
                          .wince = "PIXIWNCE.wav",
                      },
                  .attribute = {10, 4, 4, 5, 1, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 60},
                  .hasDoubleWeek = false,
              },
              {
                  // sprite
                  .index = 119,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CSPRITE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "SPRTATTK.wav",
                          .defend = "SPRTDFND.wav",
                          .killed = "SPRTKILL.wav",
                          .move = "SPRTMOVE.wav",
                          .shoot = "",
                          .wince = "SPRTWNCE.wav",
                      },
                  .attribute = {10, 5, 6, 5, 2, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 75},
                  .hasDoubleWeek = false,
              },
              {
                  // airElemental
                  .index = 112,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = { Enum::STORM_ELEMENTAL },
                  .graphics =
                      {
                          .animation = "CAELEM.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "AELMATTK.wav",
                          .defend = "AELMDFND.wav",
                          .killed = "AELMKILL.wav",
                          .move = "AELMMOVE.wav",
                          .shoot = "",
                          .wince = "AELMWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 100},
                  .hasDoubleWeek = false,
              },
              {
                  // stormElemental
                  .index = 127,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CSTORM.DEF",
                          .missile = "CPRGTIX.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "STORATTK.wav",
                          .defend = "STORDFND.wav",
                          .killed = "STORKILL.wav",
                          .move = "STORMOVE.wav",
                          .shoot = "STORSHOT.wav",
                          .wince = "STORWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 150},
                  .hasDoubleWeek = false,
              },
              {
                  // waterElemental
                  .index = 115,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = { Enum::ICE_ELEMENTAL },
                  .graphics =
                      {
                          .animation = "CWELEM.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "WELMATTK.wav",
                          .defend = "WELMDFND.wav",
                          .killed = "WELMKILL.wav",
                          .move = "WELMMOVE.wav",
                          .shoot = "",
                          .wince = "WELMWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 200},
                  .hasDoubleWeek = false,
              },
              {
                  // iceElemental
                  .index = 123,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CICEE.DEF",
                          .missile = "PICEE.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "ICELATTK.wav",
                          .defend = "ICELDFND.wav",
                          .killed = "ICELKILL.wav",
                          .move = "ICELMOVE.wav",
                          .shoot = "ICELSHOT.wav",
                          .wince = "ICELWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 250},
                  .hasDoubleWeek = false,
              },
              {
                  // fireElemental
                  .index = 114,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = { Enum::ENERGY_ELEMENTAL },
                  .graphics =
                      {
                          .animation = "CFELEM.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "FELMATTK.wav",
                          .defend = "FELMDFND.wav",
                          .killed = "FELMKILL.wav",
                          .move = "FELMMOVE.wav",
                          .shoot = "",
                          .wince = "FELMWNCE.wav",
                      },
                  .attribute = {35, 5, 10, 12, 6, 9, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // energyElemental
                  .index = 129,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CNRG.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "ENERATTK.wav",
                          .defend = "ENERDFND.wav",
                          .killed = "ENERKILL.wav",
                          .move = "ENERMOVE.wav",
                          .shoot = "",
                          .wince = "ENERWNCE.wav",
                      },
                  .attribute = {35, 6, 12, 12, 7, 10, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 400},
                  .hasDoubleWeek = false,
              },
              {
                  // earthElemental
                  .index = 113,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = { Enum::MAGMA_ELEMENTAL },
                  .graphics =
                      {
                          .animation = "CEELEM.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "EELMATTK.wav",
                          .defend = "EELMDFND.wav",
                          .killed = "EELMKILL.wav",
                          .move = "EELMMOVE.wav",
                          .shoot = "",
                          .wince = "EELMWNCE.wav",
                      },
                  .attribute = {30, 5, 12, 7, 10, 12, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // magmaElemental
                  .index = 125,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CSTONE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MAGMATTK.wav",
                          .defend = "MAGMDFND.wav",
                          .killed = "MAGMKILL.wav",
                          .move = "MAGMMOVE.wav",
                          .shoot = "",
                          .wince = "MAGMWNCE.wav",
                      },
                  .attribute = {30, 7, 12, 10, 10, 12, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 450},
                  .hasDoubleWeek = false,
              },
              {
                  // psychicElemental
                  .index = 120,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = { Enum::MAGIC_ELEMENTAL },
                  .graphics =
                      {
                          .animation = "CPSYEL.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "PSYCATTK.wav",
                          .defend = "PSYCDFND.wav",
                          .killed = "PSYCKILL.wav",
                          .move = "PSYCMOVE.wav",
                          .shoot = "",
                          .wince = "PSYCWNCE.wav",
                      },
                  .attribute = {100, 7, 15, 15, 15, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // magicElemental
                  .index = 121,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CMAGEL.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MGELATTK.wav",
                          .defend = "MGELDFND.wav",
                          .killed = "MGELKILL.wav",
                          .move = "MGELMOVE.wav",
                          .shoot = "",
                          .wince = "MGELWNCE.wav",
                      },
                  .attribute = {100, 9, 16, 16, 20, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1200},
                  .hasDoubleWeek = false,
              },
              {
                  // firebird
                  .index = 130,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = { Enum::PHOENIX },
                  .graphics =
                      {
                          .animation = "CFBIRD.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "FIRBATTK.wav",
                          .defend = "FIRBDFND.wav",
                          .killed = "FIRBKILL.wav",
                          .move = "FIRBMOVE.wav",
                          .shoot = "",
                          .wince = "FIRBWNCE.wav",
                      },
                  .attribute = {200, 12, 20, 20, 50, 50, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // phoenix
                  .index = 131,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_CONFLUX,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CPHX.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "PHOEATTK.wav",
                          .defend = "PHOEDFND.wav",
                          .killed = "PHOEKILL.wav",
                          .move = "PHOEMOVE.wav",
                          .shoot = "",
                          .wince = "PHOEWNCE.wav",
                      },
                  .attribute = {200, 12, 20, 20, 50, 50, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
  };
};