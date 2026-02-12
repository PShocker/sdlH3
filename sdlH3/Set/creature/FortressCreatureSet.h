#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

struct FortressCreatureSet {
  const static inline std::vector<CreatureSetI> creatures =
      {
          {
              // gnoll
              .index = 98,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {Enum::GNOLL_MARAUDER},
              .graphics =
                  {
                      .animation = "CGNOLL.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "GNOLATTK.wav",
                      .defend = "GNOLDFND.wav",
                      .killed = "GNOLKILL.wav",
                      .move = "GNOLMOVE.wav",
                      .shoot = "",
                      .wince = "GNOLWNCE.wav",
                  },
              .attribute = {10, 4, 4, 5, 1, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 60},
              .hasDoubleWeek = false,
          },
          {
              // gnollMarauder
              .index = 99,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CGNOLM.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "GNLMATTK.wav",
                      .defend = "GNLMDFND.wav",
                      .killed = "GNLMKILL.wav",
                      .move = "GNLMMOVE.wav",
                      .shoot = "",
                      .wince = "GNLMWNCE.wav",
                  },
              .attribute = {10, 5, 6, 5, 2, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 75},
              .hasDoubleWeek = false,
          },
          {
              // lizardman
              .index = 100,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {Enum::LIZARD_WARRIOR},
              .graphics =
                  {
                      .animation = "CPLIZA.DEF",
                      .missile = "PPLIZAX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "PLIZATTK.wav",
                      .defend = "PLIZDFND.wav",
                      .killed = "PLIZKILL.wav",
                      .move = "PLIZMOVE.wav",
                      .shoot = "PLIZSHOT.wav",
                      .wince = "PLIZWNCE.wav",
                  },
              .attribute = {10, 4, 6, 3, 2, 3, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 100},
              .hasDoubleWeek = true,
          },
          {
              // lizardWarrior
              .index = 101,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CALIZA.DEF",
                      .missile = "PPLIZAX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "ALIZATTK.wav",
                      .defend = "ALIZDFND.wav",
                      .killed = "ALIZKILL.wav",
                      .move = "ALIZMOVE.wav",
                      .shoot = "ALIZSHOT.wav",
                      .wince = "ALIZWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 150},
              .hasDoubleWeek = false,
          },
          {
              // serpentFly
              .index = 104,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {Enum::DRAGON_FLY},
              .graphics =
                  {
                      .animation = "CDRFLY.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "DFLYATTK.wav",
                      .defend = "DFLYDFND.wav",
                      .killed = "DFLYKILL.wav",
                      .move = "DFLYMOVE.wav",
                      .shoot = "",
                      .wince = "DFLYWNCE.wav",
                  },
              .attribute = {10, 4, 6, 3, 2, 3, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 200},
              .hasDoubleWeek = true,
          },
          {
              // fireDragonFly - FIXME: dragonFly is correct in-game, incorrect
              // in HOTRAITS
              .index = 105,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CDRFIR.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "FDFLATTK.wav",
                      .defend = "FDFLDFND.wav",
                      .killed = "FDFLKILL.wav",
                      .move = "FDFLMOVE.wav",
                      .shoot = "FDFLSHOT.wav",
                      .wince = "FDFLWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 250},
              .hasDoubleWeek = false,
          },
          {
              // gorgon
              .index = 102,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {Enum::MIGHTY_GORGON},
              .graphics =
                  {
                      .animation = "CCGORG.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "CGORATTK.wav",
                      .defend = "CGORDFND.wav",
                      .killed = "CGORKILL.wav",
                      .move = "CGORMOVE.wav",
                      .shoot = "",
                      .wince = "CGORWNCE.wav",
                  },
              .attribute = {30, 5, 12, 7, 10, 12, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // mightyGorgon
              .index = 103,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CBGOG.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "BGORATTK.wav",
                      .defend = "BGORDFND.wav",
                      .killed = "BGORKILL.wav",
                      .move = "BGORMOVE.wav",
                      .shoot = "",
                      .wince = "BGORWNCE.wav",
                  },
              .attribute = {30, 7, 12, 10, 10, 12, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 450},
              .hasDoubleWeek = false,
          },
          {
              // basilisk
              .index = 106,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {Enum::GREATER_BASILISK},
              .graphics =
                  {
                      .animation = "CBASIL.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "BASLATTK.wav",
                      .defend = "BASLDFND.wav",
                      .killed = "BASLKILL.wav",
                      .move = "BASLMOVE.wav",
                      .shoot = "",
                      .wince = "BASLWNCE.wav",
                  },
              .attribute = {35, 5, 10, 12, 6, 9, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // greaterBasilisk
              .index = 107,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CGBASI.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "GBASATTK.wav",
                      .defend = "GBASDFND.wav",
                      .killed = "GBASKILL.wav",
                      .move = "GBASMOVE.wav",
                      .shoot = "",
                      .wince = "GBASWNCE.wav",
                  },
              .attribute = {35, 6, 12, 12, 7, 10, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 400},
              .hasDoubleWeek = false,
          },
          {
              // wyvern
              .index = 108,
              .level = 6,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {Enum::WYVERN_MONARCH},
              .graphics =
                  {
                      .animation = "CWYVER.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "WYVNATTK.wav",
                      .defend = "WYVNDFND.wav",
                      .killed = "WYVNKILL.wav",
                      .move = "WYVNMOVE.wav",
                      .shoot = "",
                      .wince = "WYVNWNCE.wav",
                  },
              .attribute = {100, 7, 15, 15, 15, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // wyvernMonarch
              .index = 109,
              .level = 6,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CWYVMN.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "WYVMATTK.wav",
                      .defend = "WYVMDFND.wav",
                      .killed = "WYVMKILL.wav",
                      .move = "WYVMMOVE.wav",
                      .shoot = "",
                      .wince = "WYVMWNCE.wav",
                  },
              .attribute = {100, 9, 16, 16, 20, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1200},
              .hasDoubleWeek = false,
          },
          {
              // hydra
              .index = 110,
              .level = 7,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {Enum::CHAOS_HYDRA},
              .graphics =
                  {
                      .animation = "CHYDRA.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "HYDRATTK.wav",
                      .defend = "HYDRDFND.wav",
                      .killed = "HYDRKILL.wav",
                      .move = "HYDRMOVE.wav",
                      .shoot = "",
                      .wince = "HYDRWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // chaosHydra
              .index = 111,
              .level = 7,
              .female = false,
              .faction = Enum::FACTION_FORTRESS,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CCHYDR.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "CHYDATTK.wav",
                      .defend = "CHYDDFND.wav",
                      .killed = "CHYDKILL.wav",
                      .move = "CHYDMOVE.wav",
                      .shoot = "",
                      .wince = "CHYDWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          }};
};