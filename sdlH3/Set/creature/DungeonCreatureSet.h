#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

struct DungeonCreatureSet {
  const static inline std::vector<CreatureSetI>
      creatures =
          {
              {
                  // troglodyte
                  .index = 70,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = { Enum::INFERNAL_TROGLODYTE },
                  .graphics =
                      {
                          .animation = "CTROGL.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "TROGATTK.wav",
                          .defend = "TROGDFND.wav",
                          .killed = "TROGKILL.wav",
                          .move = "TROGMOVE.wav",
                          .shoot = "",
                          .wince = "TROGWNCE.wav",
                      },
                  .attribute = {10, 4, 4, 5, 1, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 60},
                  .hasDoubleWeek = true,
              },
              {
                  // infernalTroglodyte
                  .index = 71,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CITROG.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "ITRGATTK.wav",
                          .defend = "ITRGDFND.wav",
                          .killed = "ITRGKILL.wav",
                          .move = "ITRGMOVE.wav",
                          .shoot = "",
                          .wince = "ITRGWNCE.wav",
                      },
                  .attribute = {10, 5, 6, 5, 2, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 75},
                  .hasDoubleWeek = false,
              },
              {
                  // harpy
                  .index = 72,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = { Enum::HARPY_HAG },
                  .graphics =
                      {
                          .animation = "CHARPY.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "HARPATTK.wav",
                          .defend = "HARPDFND.wav",
                          .killed = "HARPKILL.wav",
                          .move = "HARPMOVE.wav",
                          .shoot = "",
                          .wince = "HARPWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 100},
                  .hasDoubleWeek = true,
              },
              {
                  // harpyHag
                  .index = 73,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CHARPH.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "HHAGATTK.wav",
                          .defend = "HHAGDFND.wav",
                          .killed = "HHAGKILL.wav",
                          .move = "HHAGMOVE.wav",
                          .shoot = "HHAGSHOT.wav",
                          .wince = "HHAGWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 150},
                  .hasDoubleWeek = false,
              },
              {
                  // beholder
                  .index = 74,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = { Enum::EVIL_EYE },
                  .graphics =
                      {
                          .animation = "CBEHOL.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "BHDRATTK.wav",
                          .defend = "BHDRDFND.wav",
                          .killed = "BHDRKILL.wav",
                          .move = "BHDRMOVE.wav",
                          .shoot = "BHDRSHOT.wav",
                          .wince = "BHDRWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 200},
                  .hasDoubleWeek = false,
              },
              {
                  // evilEye
                  .index = 75,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CEVEYE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "EVLIATTK.wav",
                          .defend = "EVLIDFND.wav",
                          .killed = "EVLIKILL.wav",
                          .move = "EVLIMOVE.wav",
                          .shoot = "EVLISHOT.wav",
                          .wince = "EVLIWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 250},
                  .hasDoubleWeek = false,
              },
              {
                  // medusa
                  .index = 76,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = { Enum::MEDUSA_QUEEN },
                  .graphics =
                      {
                          .animation = "CMEDUS.DEF",
                          .missile = "PMEDUSX.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MEDUATTK.wav",
                          .defend = "MEDUDFND.wav",
                          .killed = "MEDUKILL.wav",
                          .move = "MEDUMOVE.wav",
                          .shoot = "MEDUSHOT.wav",
                          .wince = "MEDUWNCE.wav",
                      },
                  .attribute = {35, 5, 10, 12, 6, 9, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // medusaQueen
                  .index = 77,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CMEDUQ.DEF",
                          .missile = "PMEDUSX.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MEDQATTK.wav",
                          .defend = "MEDQDFND.wav",
                          .killed = "MEDQKILL.wav",
                          .move = "MEDQMOVE.wav",
                          .shoot = "MEDQSHOT.wav",
                          .wince = "MEDQWNCE.wav",
                      },
                  .attribute = {35, 6, 12, 12, 7, 10, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 400},
                  .hasDoubleWeek = false,
              },
              {
                  // minotaur
                  .index = 78,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = { Enum::MINOTAUR_KING },
                  .graphics =
                      {
                          .animation = "CMINOT.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MINOATTK.wav",
                          .defend = "MINODFND.wav",
                          .killed = "MINOKILL.wav",
                          .move = "MINOMOVE.wav",
                          .shoot = "",
                          .wince = "MINOWNCE.wav",
                      },
                  .attribute = {30, 5, 12, 7, 10, 12, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // minotaurKing
                  .index = 79,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CMINOK.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MINKATTK.wav",
                          .defend = "MINKDFND.wav",
                          .killed = "MINKKILL.wav",
                          .move = "MINKMOVE.wav",
                          .shoot = "MINKSHOT.wav",
                          .wince = "MINKWNCE.wav",
                      },
                  .attribute = {30, 7, 12, 10, 10, 12, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 450},
                  .hasDoubleWeek = false,
              },
              {
                  // manticore
                  .index = 80,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = { Enum::SCORPICORE },
                  .graphics =
                      {
                          .animation = "CMCORE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MANTATTK.wav",
                          .defend = "MANTDFND.wav",
                          .killed = "MANTKILL.wav",
                          .move = "MANTMOVE.wav",
                          .shoot = "MANTSHOT.wav",
                          .wince = "MANTWNCE.wav",
                      },
                  .attribute = {100, 7, 15, 15, 15, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // scorpicore
                  .index = 81,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CCMCOR.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "SCRPATTK.wav",
                          .defend = "SCRPDFND.wav",
                          .killed = "SCRPKILL.wav",
                          .move = "SCRPMOVE.wav",
                          .shoot = "SCRPSHOT.wav",
                          .wince = "SCRPWNCE.wav",
                      },
                  .attribute = {100, 9, 16, 16, 20, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1200},
                  .hasDoubleWeek = false,
              },
              {
                  // redDragon
                  .index = 82,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = { Enum::BLACK_DRAGON },
                  .graphics =
                      {
                          .animation = "CRDRGN.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "RDDRATTK.wav",
                          .defend = "RDDRDFND.wav",
                          .killed = "RDDRKILL.wav",
                          .move = "RDDRMOVE.wav",
                          .shoot = "",
                          .wince = "RDDRWNCE.wav",
                      },
                  .attribute = {200, 12, 20, 20, 50, 50, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // blackDragon
                  .index = 83,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_DUNGEON,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CBDRGN.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "BKDRATTK.wav",
                          .defend = "BKDRDFND.wav",
                          .killed = "BKDRKILL.wav",
                          .move = "BKDRMOVE.wav",
                          .shoot = "",
                          .wince = "BKDRWNCE.wav",
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