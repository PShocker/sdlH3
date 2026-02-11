#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>


struct NecropolisCreatureSet {
  const static inline std::vector<CreatureSetI>
      creatures =
          {
              {
                  // skeleton
                  .index = 56,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = { Enum::SKELETON_WARRIOR },
                  .graphics =
                      {
                          .animation = "CSKELE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "SKELATTK.wav",
                          .defend = "SKELDFND.wav",
                          .killed = "SKELKILL.wav",
                          .move = "SKELMOVE.wav",
                          .shoot = "",
                          .wince = "SKELWNCE.wav",
                      },
                  .attribute = {10, 4, 4, 5, 1, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 60},
                  .hasDoubleWeek = false,
              },
              {
                  // skeletonWarrior
                  .index = 57,
                  .level = 1,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CWSKEL.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "SKLWATTK.wav",
                          .defend = "SKLWDFND.wav",
                          .killed = "SKLWKILL.wav",
                          .move = "SKLWMOVE.wav",
                          .shoot = "",
                          .wince = "SKLWWNCE.wav",
                      },
                  .attribute = {10, 5, 6, 5, 2, 3, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 75},
                  .hasDoubleWeek = false,
              },
              {
                  // walkingDead - FIXME: zombie is a name of upgrade but not in HOTRAITS
                  .index = 58,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = { Enum::ZOMBIE },
                  .graphics =
                      {
                          .animation = "CZOMBI.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "ZOMBATTK.wav",
                          .defend = "ZOMBDFND.wav",
                          .killed = "ZOMBKILL.wav",
                          .move = "ZOMBMOVE.wav",
                          .shoot = "",
                          .wince = "ZOMBWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 100},
                  .hasDoubleWeek = false,
              },
              {
                  // zombieLord - FIXME: zombie is a correct in-name but not in HOTRAITS.TXT
                  .index = 59,
                  .level = 2,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CZOMLO.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "ZMBLATTK.wav",
                          .defend = "ZMBLDFND.wav",
                          .killed = "ZMBLKILL.wav",
                          .move = "ZMBLMOVE.wav",
                          .shoot = "",
                          .wince = "ZMBLWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 150},
                  .hasDoubleWeek = false,
              },
              {
                  // wight
                  .index = 60,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = { Enum::WRAITH },
                  .graphics =
                      {
                          .animation = "CWIGHT.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "WGHTATTK.wav",
                          .defend = "WGHTDFND.wav",
                          .killed = "WGHTKILL.wav",
                          .move = "WGHTMOVE.wav",
                          .shoot = "",
                          .wince = "WGHTWNCE.wav",
                      },
                  .attribute = {10, 4, 6, 3, 2, 3, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 200},
                  .hasDoubleWeek = true,
              },
              {
                  // wraith
                  .index = 61,
                  .level = 3,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CWRAIT.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "WRTHATTK.wav",
                          .defend = "WRTHDFND.wav",
                          .killed = "WRTHKILL.wav",
                          .move = "WRTHMOVE.wav",
                          .shoot = "",
                          .wince = "WRTHWNCE.wav",
                      },
                  .attribute = {10, 6, 6, 3, 2, 3, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 250},
                  .hasDoubleWeek = false,
              },
              {
                  // vampire
                  .index = 62,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = { Enum::VAMPIRE_LORD },
                  .graphics =
                      {
                          .animation = "CVAMP.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "VAMPATTK.wav",
                          .defend = "VAMPDFND.wav",
                          .killed = "VAMPKILL.wav",
                          .move = "VAMPMOVE.wav",
                          .shoot = "",
                          .wince = "VAMPWNCE.wav",
                      },
                  .attribute = {35, 5, 10, 12, 6, 9, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // vampireLord
                  .index = 63,
                  .level = 4,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CNOSFE.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "NOSFATTK.wav",
                          .defend = "NOSFDFND.wav",
                          .killed = "NOSFKILL.wav",
                          .move = "NOSFMOVE.wav",
                          .shoot = "NOSFSHOT.wav",
                          .wince = "NOSFWNCE.wav",
                      },
                  .attribute = {35, 6, 12, 12, 7, 10, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 400},
                  .hasDoubleWeek = false,
              },
              {
                  // lich
                  .index = 64,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = { Enum::POWER_LICH },
                  .graphics =
                      {
                          .animation = "CLICH.DEF",
                          .missile = "PLICH.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "LICHATTK.wav",
                          .defend = "LICHDFND.wav",
                          .killed = "LICHKILL.wav",
                          .move = "LICHMOVE.wav",
                          .shoot = "LICHSHOT.wav",
                          .wince = "LICHWNCE.wav",
                      },
                  .attribute = {30, 5, 12, 7, 10, 12, 12},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 300},
                  .hasDoubleWeek = false,
              },
              {
                  // powerLich
                  .index = 65,
                  .level = 5,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CPLICH.DEF",
                          .missile = "PLICH.DEF",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "PLCHATTK.wav",
                          .defend = "PLCHDFND.wav",
                          .killed = "PLCHKILL.wav",
                          .move = "PLCHMOVE.wav",
                          .shoot = "PLCHSHOT.wav",
                          .wince = "PLCHWNCE.wav",
                      },
                  .attribute = {30, 7, 12, 10, 10, 12, 24},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 450},
                  .hasDoubleWeek = false,
              },
              {
                  // blackKnight
                  .index = 66,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = { Enum::DREAD_KNIGHT },
                  .graphics =
                      {
                          .animation = "CBKNIG.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "BKNTATTK.wav",
                          .defend = "BKNTDFND.wav",
                          .killed = "BKNTKILL.wav",
                          .move = "BKNTMOVE.wav",
                          .shoot = "",
                          .wince = "BKNTWNCE.wav",
                      },
                  .attribute = {100, 7, 15, 15, 15, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // dreadKnight
                  .index = 67,
                  .level = 6,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CBLORD.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "BLRDATTK.wav",
                          .defend = "BLRDDFND.wav",
                          .killed = "BLRDKILL.wav",
                          .move = "BLRDMOVE.wav",
                          .shoot = "",
                          .wince = "BLRDWNCE.wav",
                      },
                  .attribute = {100, 9, 16, 16, 20, 25, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1200},
                  .hasDoubleWeek = false,
              },
              {
                  // boneDragon
                  .index = 68,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = { Enum::GHOST_DRAGON },
                  .graphics =
                      {
                          .animation = "CNDRGN.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "BODRATTK.wav",
                          .defend = "BODRDFND.wav",
                          .killed = "BODRKILL.wav",
                          .move = "BODRMOVE.wav",
                          .shoot = "",
                          .wince = "BODRWNCE.wav",
                      },
                  .attribute = {200, 12, 20, 20, 50, 50, 0},
                  .abilities = {},
                  .growth = 14,
                  .experience = 10,
                  .cost = {0, 0, 0, 0, 0, 0, 1000},
                  .hasDoubleWeek = false,
              },
              {
                  // ghostDragon
                  .index = 69,
                  .level = 7,
                  .female = false,
                  .faction = Enum::FACTION_NECROPOLIS,
                  .upgrades = {},
                  .graphics =
                      {
                          .animation = "CHDRGN.DEF",
                          .missile = "",
                          .adventure = "",
                      },
                  .sounds =
                      {
                          .attack = "GHDRATTK.wav",
                          .defend = "GHDRDFND.wav",
                          .killed = "GHDRKILL.wav",
                          .move = "GHDRMOVE.wav",
                          .shoot = "",
                          .wince = "GHDRWNCE.wav",
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