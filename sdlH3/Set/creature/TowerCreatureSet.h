#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstddef>
#include <vector>

struct TowerCreatureSet {
  const static inline std::vector<CreatureSetI>
      creatures =
          {
              {
                  // gremlin
                  .index = 28,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = { Enum::MASTER_GREMLIN },
                  .graphics =
                      {
                          .animation = "CGREMA.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "AGRMATTK.wav",
                          .defend = "AGRMDFND.wav",
                          .killed = "AGRMKILL.wav",
                          .move = "AGRMMOVE.wav",
                          .shoot = "AGRMSHOT.wav",
                          .wince = "AGRMWNCE.wav",
                      },
                  .attribute = {10, 4, 4, 5, 1, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 60},
                  .hasDoubleWeek = true,
              },
              {
                  // masterGremlin
                  .index = 29,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CGREMM.DEF",
                          .missile = "CPRGRE.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MGRMATTK.wav",
                          .defend = "MGRMDFND.wav",
                          .killed = "MGRMKILL.wav",
                          .move = "MGRMMOVE.wav",
                          .shoot = "MGRMSHOT.wav",
                          .wince = "MGRMWNCE.wav",
                      },
                  .attribute = {10, 5, 6, 5, 2, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 75},
                  .hasDoubleWeek = false,
              },
              {
                  // stoneGargoyle
                  .index = 30,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = { Enum::OBSIDIAN_GARGOYLE },
                  .graphics =
                      {
                          .animation = "CGARGO.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "SGRGATTK.wav",
                          .defend = "SGRGDFND.wav",
                          .killed = "SGRGKILL.wav",
                          .move = "SGRGMOVE.wav",
                          .shoot = "",
                          .wince = "SGRGWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 100},
                  .hasDoubleWeek = false,
              },
              {
                  // obsidianGargoyle
                  .index = 31,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "COGARG.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "OGRGATTK.wav",
                          .defend = "OGRGDFND.wav",
                          .killed = "OGRGKILL.wav",
                          .move = "OGRGMOVE.wav",
                          .shoot = "",
                          .wince = "OGRGWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 150},
                  .hasDoubleWeek = false,
              },
              {
                  // ironGolem - FIXME correct ID is stoneGolem, unchangeable due to HOTRAITS.TXT
                  .index = 32,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = { Enum::STONE_GOLEM },
                  .graphics =
                      {
                          .animation = "CSGOLE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "SGLMATTK.wav",
                          .defend = "SGLMDFND.wav",
                          .killed = "SGLMKILL.wav",
                          .move = "SGLMMOVE.wav",
                          .shoot = "",
                          .wince = "SGLMWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 200},
                  .hasDoubleWeek = false,
              },
              {
                  // stoneGolem - FIXME correct ID is ironGolem, unchangeable due to HOTRAITS.TXT
                  .index = 33,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CIGOLE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "IGLMATTK.wav",
                          .defend = "IGLMDFND.wav",
                          .killed = "IGLMKILL.wav",
                          .move = "IGLMMOVE.wav",
                          .shoot = "",
                          .wince = "IGLMWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 250},
                  .hasDoubleWeek = false,
              },
              {
                  // mage
                  .index = 34,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = { Enum::ARCH_MAGE },
                  .graphics =
                      {
                          .animation = "CMAGE.DEF",
                          .missile = "PMAGEX.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "MAGEATTK.wav",
                          .defend = "MAGEDFND.wav",
                          .killed = "MAGEKILL.wav",
                          .move = "MAGEMOVE.wav",
                          .shoot = "MAGESHOT.wav",
                          .wince = "MAGEWNCE.wav",
                      },
                  .attribute = {35, 5, 10, 12, 6, 9, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // archMage
                  .index = 35,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CAMAGE.DEF",
                          .missile = "PMAGEX.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "AMAGATTK.wav",
                          .defend = "AMAGDFND.wav",
                          .killed = "AMAGKILL.wav",
                          .move = "AMAGMOVE.wav",
                          .shoot = "AMAGSHOT.wav",
                          .wince = "AMAGWNCE.wav",
                      },
                  .attribute = {35, 6, 12, 12, 7, 10, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 400},
                  .hasDoubleWeek = false,
              },
              {
                  // genie
                  .index = 36,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = { Enum::MASTER_GENIE },
                  .graphics =
                      {
                          .animation = "CGENIE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "GENIATTK.wav",
                          .defend = "GENIDFND.wav",
                          .killed = "GENIKILL.wav",
                          .move = "GENIMOVE.wav",
                          .shoot = "",
                          .wince = "GENIWNCE.wav",
                      },
                  .attribute = {30, 5, 12, 7, 10, 12, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // masterGenie
                  .index = 37,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CSULTA.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "CALFATTK.wav",
                          .defend = "CALFDFND.wav",
                          .killed = "CALFKILL.wav",
                          .move = "CALFMOVE.wav",
                          .shoot = "CALFSHOT.wav",
                          .wince = "CALFWNCE.wav",
                      },
                  .attribute = {30, 7, 12, 10, 10, 12, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 450},
                  .hasDoubleWeek = false,
              },
              {
                  // naga
                  .index = 38,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = { Enum::NAGA_QUEEN },
                  .graphics =
                      {
                          .animation = "CNAGA.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "NSENATTK.wav",
                          .defend = "NSENDFND.wav",
                          .killed = "NSENKILL.wav",
                          .move = "NSENMOVE.wav",
                          .shoot = "",
                          .wince = "NSENWNCE.wav",
                      },
                  .attribute = {100, 7, 15, 15, 15, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // nagaQueen
                  .index = 39,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CNAGAG.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "NGRDATTK.wav",
                          .defend = "NGRDDFND.wav",
                          .killed = "NGRDKILL.wav",
                          .move = "NGRDMOVE.wav",
                          .shoot = "",
                          .wince = "NGRDWNCE.wav",
                      },
                  .attribute = {100, 9, 16, 16, 20, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1200},
                  .hasDoubleWeek = false,
              },
              {
                  // giant
                  .index = 40,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = { Enum::TITAN },
                  .graphics =
                      {
                          .animation = "CLTITA.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "LTITATTK.wav",
                          .defend = "LTITDFND.wav",
                          .killed = "LTITKILL.wav",
                          .move = "LTITMOVE.wav",
                          .shoot = "",
                          .wince = "LTITWNCE.wav",
                      },
                  .attribute = {200, 12, 20, 20, 50, 50, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // titan
                  .index = 41,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_TOWER,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CGTITA.DEF",
                          .missile = "CPRGTIX.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "GTITATTK.wav",
                          .defend = "GTITDFND.wav",
                          .killed = "GTITKILL.wav",
                          .move = "GTITMOVE.wav",
                          .shoot = "GTITSHOT.wav",
                          .wince = "GTITWNCE.wav",
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