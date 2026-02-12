#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstddef>
#include <vector>

struct InfernoCreatureSet {
  const static inline std::vector<CreatureSetI> creatures =
      {
          {
              // imp
              .index = 42,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {Enum::FAMILIAR},
              .graphics =
                  {
                      .animation = "CIMP.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "IMPPATTK.wav",
                      .defend = "IMPPDFND.wav",
                      .killed = "IMPPKILL.wav",
                      .move = "IMPPMOVE.wav",
                      .shoot = "",
                      .wince = "IMPPWNCE.wav",
                  },
              .attribute = {10, 4, 4, 5, 1, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 60},
              .hasDoubleWeek = false,
          },
          {
              // familiar
              .index = 43,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CFAMIL.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "FMLRATTK.wav",
                      .defend = "FMLRDFND.wav",
                      .killed = "FMLRKILL.wav",
                      .move = "FMLRMOVE.wav",
                      .shoot = "",
                      .wince = "FMLRWNCE.wav",
                  },
              .attribute = {10, 5, 6, 5, 2, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 75},
              .hasDoubleWeek = false,
          },
          {
              // gog
              .index = 44,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {Enum::MAGOG},
              .graphics =
                  {
                      .animation = "CGOG.DEF",
                      .missile = "CPRGOGX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "GOGGATTK.wav",
                      .defend = "GOGGDFND.wav",
                      .killed = "GOGGKILL.wav",
                      .move = "GOGGMOVE.wav",
                      .shoot = "GOGGSHOT.wav",
                      .wince = "GOGGWNCE.wav",
                  },
              .attribute = {10, 4, 6, 3, 2, 3, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 100},
              .hasDoubleWeek = true,
          },
          {
              // magog
              .index = 45,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CMAGOG.DEF",
                      .missile = "CPRGOGX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "MGOGATTK.wav",
                      .defend = "MGOGDFND.wav",
                      .killed = "MGOGKILL.wav",
                      .move = "MGOGMOVE.wav",
                      .shoot = "SPONTCOMB.wav",
                      .wince = "MGOGWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 150},
              .hasDoubleWeek = false,
          },
          {
              // hellHound
              .index = 46,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {Enum::CERBERUS},
              .graphics =
                  {
                      .animation = "CHHOUN.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "HHNDATTK.wav",
                      .defend = "HHNDDFND.wav",
                      .killed = "HHNDKILL.wav",
                      .move = "HHNDMOVE.wav",
                      .shoot = "",
                      .wince = "HHNDWNCE.wav",
                  },
              .attribute = {10, 4, 6, 3, 2, 3, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 200},
              .hasDoubleWeek = false,
          },
          {
              // cerberus
              .index = 47,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CCERBU.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "CERBATTK.wav",
                      .defend = "CERBDFND.wav",
                      .killed = "CERBKILL.wav",
                      .move = "CERBMOVE.wav",
                      .shoot = "",
                      .wince = "CERBWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 250},
              .hasDoubleWeek = false,
          },
          {
              // demon
              .index = 48,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {Enum::HORNED_DEMON},
              .graphics =
                  {
                      .animation = "COHDEM.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "SHDMATTK.wav",
                      .defend = "SHDMDFND.wav",
                      .killed = "SHDMKILL.wav",
                      .move = "SHDMMOVE.wav",
                      .shoot = "",
                      .wince = "SHDMWNCE.wav",
                  },
              .attribute = {35, 5, 10, 12, 6, 9, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // hornedDemon
              .index = 49,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CTHDEM.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "DHDMATTK.wav",
                      .defend = "DHDMDFND.wav",
                      .killed = "DHDMKILL.wav",
                      .move = "DHDMMOVE.wav",
                      .shoot = "",
                      .wince = "DHDMWNCE.wav",
                  },
              .attribute = {35, 6, 12, 12, 7, 10, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 400},
              .hasDoubleWeek = false,
          },
          {
              // pitFiend
              .index = 50,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {Enum::PIT_LORD},
              .graphics =
                  {
                      .animation = "CPFIEN.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "PFNDATTK.wav",
                      .defend = "PFNDDFND.wav",
                      .killed = "PFNDKILL.wav",
                      .move = "PFNDMOVE.wav",
                      .shoot = "",
                      .wince = "PFNDWNCE.wav",
                  },
              .attribute = {30, 5, 12, 7, 10, 12, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // pitLord
              .index = 51,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CPFOE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "PFOEATTK.wav",
                      .defend = "PFOEDFND.wav",
                      .killed = "PFOEKILL.wav",
                      .move = "PFOEMOVE.wav",
                      .shoot = "",
                      .wince = "PFOEWNCE.wav",
                  },
              .attribute = {30, 7, 12, 10, 10, 12, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 450},
              .hasDoubleWeek = false,
          },
          {
              // efreet
              .index = 52,
              .level = 6,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {Enum::EFREET_SULTAN},
              .graphics =
                  {
                      .animation = "CEFREE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "EFRTATTK.wav",
                      .defend = "EFRTDFND.wav",
                      .killed = "EFRTKILL.wav",
                      .move = "EFRTMOVE.wav",
                      .shoot = "",
                      .wince = "EFRTWNCE.wav",
                  },
              .attribute = {100, 7, 15, 15, 15, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // efreetSultan
              .index = 53,
              .level = 6,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CEFRES.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "ESULATTK.wav",
                      .defend = "ESULDFND.wav",
                      .killed = "ESULKILL.wav",
                      .move = "ESULMOVE.wav",
                      .shoot = "ESULSHOT.wav",
                      .wince = "ESULWNCE.wav",
                  },
              .attribute = {100, 9, 16, 16, 20, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1200},
              .hasDoubleWeek = false,
          },
          {
              // devil
              .index = 54,
              .level = 7,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {Enum::ARCH_DEVIL},
              .graphics =
                  {
                      .animation = "CDEVIL.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "DEVLATTK.wav",
                      .defend = "DEVLDFND.wav",
                      .killed = "DEVLKILL.wav",
                      .move = "DEVLMOVE.wav",
                      .shoot = "",
                      .wince = "DEVLWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // archDevil
              .index = 55,
              .level = 7,
              .female = false,
              .faction = Enum::FACTION_INFERNO,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CADEVL.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "ADVLATTK.wav",
                      .defend = "ADVLDFND.wav",
                      .killed = "ADVLKILL.wav",
                      .move = "ADVLMOVE.wav",
                      .shoot = "",
                      .wince = "ADVLWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          }};
};