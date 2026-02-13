#pragma once
#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

struct StrongholdCreatureSet {
  const static inline std::vector<CreatureSetI> creatures =
      {
          {
              // goblin
              .index = 84,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {Enum::HOBGOBLIN},
              .graphics =
                  {
                      .animation = "CGOBLI.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "GBLNATTK.wav",
                      .defend = "GBLNDFND.wav",
                      .killed = "GBLNKILL.wav",
                      .move = "GBLNMOVE.wav",
                      .shoot = "",
                      .wince = "GBLNWNCE.wav",
                  },
              .attribute = {10, 4, 4, 5, 1, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 60},
              .hasDoubleWeek = false,
          },
          {
              // hobgoblin
              .index = 85,
              .level = 1,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CHGOBL.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "HGOBATTK.wav",
                      .defend = "HGOBDFND.wav",
                      .killed = "HGOBKILL.wav",
                      .move = "HGOBMOVE.wav",
                      .shoot = "",
                      .wince = "HGOBWNCE.wav",
                  },
              .attribute = {10, 5, 6, 5, 2, 3, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 75},
              .hasDoubleWeek = true,
          },
          {
              // goblinWolfRider
              .index = 86,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {Enum::WOLF_RAIDER},
              .graphics =
                  {
                      .animation = "CBWLFR.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "GWRDATTK.wav",
                      .defend = "GWRDDFND.wav",
                      .killed = "GWRDKILL.wav",
                      .move = "GWRDMOVE.wav",
                      .shoot = "",
                      .wince = "GWRDWNCE.wav",
                  },
              .attribute = {10, 4, 6, 3, 2, 3, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 100},
              .hasDoubleWeek = true,
          },
          {
              // hobgoblinWolfRider
              .index = 87,
              .level = 2,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CUWLFR.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "HGWRATTK.wav",
                      .defend = "HGWRDFND.wav",
                      .killed = "HGWRKILL.wav",
                      .move = "HGWRMOVE.wav",
                      .shoot = "",
                      .wince = "HGWRWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 150},
              .hasDoubleWeek = false,
          },
          {
              // orc
              .index = 88,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {Enum::ORC_CHIEFTAIN},
              .graphics =
                  {
                      .animation = "CORC.DEF",
                      .missile = "PORCHX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "OORCATTK.wav",
                      .defend = "OORCDFND.wav",
                      .killed = "OORCKILL.wav",
                      .move = "OORCMOVE.wav",
                      .shoot = "OORCSHOT.wav",
                      .wince = "OORCWNCE.wav",
                  },
              .attribute = {10, 4, 6, 3, 2, 3, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 200},
              .hasDoubleWeek = false,
          },
          {
              // orcChieftain
              .index = 89,
              .level = 3,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CORCCH.DEF",
                      .missile = "PORCHX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "ORCCATTK.wav",
                      .defend = "ORCCDFND.wav",
                      .killed = "ORCCKILL.wav",
                      .move = "ORCCMOVE.wav",
                      .shoot = "ORCCSHOT.wav",
                      .wince = "ORCCWNCE.wav",
                  },
              .attribute = {10, 6, 6, 3, 2, 3, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 250},
              .hasDoubleWeek = false,
          },
          {
              // ogre
              .index = 90,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {Enum::OGRE_MAGE},
              .graphics =
                  {
                      .animation = "COGRE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "OGREATTK.wav",
                      .defend = "OGREDFND.wav",
                      .killed = "OGREKILL.wav",
                      .move = "OGREMOVE.wav",
                      .shoot = "",
                      .wince = "OGREWNCE.wav",
                  },
              .attribute = {35, 5, 10, 12, 6, 9, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // ogreMage
              .index = 91,
              .level = 4,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "COGMAG.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "OGRMATTK.wav",
                      .defend = "OGRMDFND.wav",
                      .killed = "OGRMKILL.wav",
                      .move = "OGRMMOVE.wav",
                      .shoot = "OGRMSHOT.wav",
                      .wince = "OGRMWNCE.wav",
                  },
              .attribute = {35, 6, 12, 12, 7, 10, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 400},
              .hasDoubleWeek = false,
          },
          {
              // roc
              .index = 92,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {Enum::THUNDERBIRD},
              .graphics =
                  {
                      .animation = "CROC.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "ROCCATTK.wav",
                      .defend = "ROCCDFND.wav",
                      .killed = "ROCCKILL.wav",
                      .move = "ROCCMOVE.wav",
                      .shoot = "",
                      .wince = "ROCCWNCE.wav",
                  },
              .attribute = {30, 5, 12, 7, 10, 12, 12},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 300},
              .hasDoubleWeek = false,
          },
          {
              // thunderbird
              .index = 93,
              .level = 5,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CTBIRD.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "TBRDATTK.wav",
                      .defend = "TBRDDFND.wav",
                      .killed = "TBRDKILL.wav",
                      .move = "TBRDMOVE.wav",
                      .shoot = "",
                      .wince = "TBRDWNCE.wav",
                  },
              .attribute = {30, 7, 12, 10, 10, 12, 24},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 450},
              .hasDoubleWeek = false,
          },
          {
              // cyclop
              .index = 94,
              .level = 6,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {Enum::CYCLOPS_KING},
              .graphics =
                  {
                      .animation = "CCYCLR.DEF",
                      .missile = "PCYCLBX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "CCYCATTK.wav",
                      .defend = "CCYCDFND.wav",
                      .killed = "CCYCKILL.wav",
                      .move = "CCYCMOVE.wav",
                      .shoot = "CCYCSHOT.wav",
                      .wince = "CCYCWNCE.wav",
                  },
              .attribute = {100, 7, 15, 15, 15, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // cyclopKing
              .index = 95,
              .level = 6,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CCYCLLOR.DEF",
                      .missile = "PCYCLBX.DEF",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "CYCLATTK.wav",
                      .defend = "CYCLDFND.wav",
                      .killed = "CYCLKILL.wav",
                      .move = "CYCLMOVE.wav",
                      .shoot = "CYCLSHOT.wav",
                      .wince = "CYCLWNCE.wav",
                  },
              .attribute = {100, 9, 16, 16, 20, 25, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1200},
              .hasDoubleWeek = false,
          },
          {
              // behemoth
              .index = 96,
              .level = 7,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {Enum::ANCIENT_BEHEMOTH},
              .graphics =
                  {
                      .animation = "CYBEHE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "YBMHATTK.wav",
                      .defend = "YBMHDFND.wav",
                      .killed = "YBMHKILL.wav",
                      .move = "YBMHMOVE.wav",
                      .shoot = "",
                      .wince = "YBMHWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          },
          {
              // ancientBehemoth
              .index = 97,
              .level = 7,
              .female = false,
              .faction = Enum::FACTION_STRONGHOLD,
              .upgrades = {},
              .graphics =
                  {
                      .animation = "CABEHE.DEF",
                      .missile = "",
                      .adventure = "",
                  },
              .sounds =
                  {
                      .attack = "BMTHATTK.wav",
                      .defend = "BMTHDFND.wav",
                      .killed = "BMTHKILL.wav",
                      .move = "BMTHMOVE.wav",
                      .shoot = "",
                      .wince = "BMTHWNCE.wav",
                  },
              .attribute = {200, 12, 20, 20, 50, 50, 0},
              .abilities = {},
              .growth = 14,
              .experience = 10,
              .cost = {0, 0, 0, 0, 0, 0, 1000},
              .hasDoubleWeek = false,
          }};
};