#pragma once

#include "Enum/Enum.h"
#include "H3mLoader/H3mObject.h"
#include "SDL3/SDL_rect.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

struct FactionBuildIncome {
  uint32_t id;
  uint32_t minVal;
  uint32_t maxVal;
  uint8_t frequency;
};

struct FactionBuildBonus {
  uint32_t id;
  uint32_t subId;
  float val;
  bool forceVisit;
  std::optional<uint8_t> frequency;
  std::optional<uint32_t> strIndex;
};

struct FactionBuild {
  int32_t id;
  std::string animation;
  int32_t x;
  int32_t y;
  int32_t z;
  std::string border;
  std::string area;
  std::string icon;
  std::vector<int32_t> require;
  std::array<uint32_t, 7> cost;
  std::vector<FactionBuildIncome> income;
  std::optional<int32_t> upgrades;
  bool autoMode;
  std::vector<FactionBuildBonus> bonus;
};

struct FactionSetI {
  uint8_t index;
  uint8_t nativeTerrain;
  std::array<std::string, 2> creatureBackground;
  std::vector<std::pair<std::string, SDL_FPoint>> puzzleMap;
  std::array<std::string, 5> mapObject;
  std::string musicTheme;
  std::string guildBackground;
  std::string townBackground;
  std::string guildWindow;
  std::vector<std::vector<std::vector<int32_t>>> hallSlots;
  std::vector<uint16_t> blacksmith;
  std::vector<FactionBuild> builds;
};

struct CastleFactionSet {
  const static inline FactionSetI faction =
      {
          .index = 0,
          .nativeTerrain = Enum::TERRAIN_GRASS,
          .creatureBackground = {"TPCASCAS.pcx", "CRBKGCAS.pcx"},
          .puzzleMap =
              {
                  {"PUZCAS00.pcx", {7, 8}},     {"PUZCAS01.pcx", {7, 30}},
                  {"PUZCAS02.pcx", {7, 102}},   {"PUZCAS03.pcx", {7, 156}},
                  {"PUZCAS04.pcx", {7, 202}},   {"PUZCAS05.pcx", {7, 320}},
                  {"PUZCAS06.pcx", {16, 8}},    {"PUZCAS07.pcx", {22, 406}},
                  {"PUZCAS08.pcx", {70, 301}},  {"PUZCAS09.pcx", {72, 194}},
                  {"PUZCAS10.pcx", {101, 332}}, {"PUZCAS11.pcx", {106, 8}},
                  {"PUZCAS12.pcx", {106, 31}},  {"PUZCAS13.pcx", {114, 60}},
                  {"PUZCAS14.pcx", {126, 329}}, {"PUZCAS15.pcx", {128, 191}},
                  {"PUZCAS16.pcx", {152, 347}}, {"PUZCAS17.pcx", {154, 239}},
                  {"PUZCAS18.pcx", {157, 429}}, {"PUZCAS19.pcx", {166, 470}},
                  {"PUZCAS20.pcx", {185, 127}}, {"PUZCAS21.pcx", {212, 335}},
                  {"PUZCAS22.pcx", {214, 191}}, {"PUZCAS23.pcx", {217, 226}},
                  {"PUZCAS24.pcx", {235, 147}}, {"PUZCAS25.pcx", {245, 77}},
                  {"PUZCAS26.pcx", {266, 384}}, {"PUZCAS27.pcx", {288, 288}},
                  {"PUZCAS28.pcx", {298, 8}},   {"PUZCAS29.pcx", {321, 177}},
                  {"PUZCAS30.pcx", {346, 67}},  {"PUZCAS31.pcx", {354, 459}},
                  {"PUZCAS32.pcx", {355, 397}}, {"PUZCAS33.pcx", {375, 162}},
                  {"PUZCAS34.pcx", {382, 255}}, {"PUZCAS35.pcx", {408, 32}},
                  {"PUZCAS36.pcx", {408, 111}}, {"PUZCAS37.pcx", {421, 147}},
                  {"PUZCAS38.pcx", {422, 466}}, {"PUZCAS39.pcx", {426, 8}},
                  {"PUZCAS40.pcx", {436, 238}}, {"PUZCAS41.pcx", {458, 336}},
                  {"PUZCAS42.pcx", {486, 8}},   {"PUZCAS43.pcx", {487, 144}},
                  {"PUZCAS44.pcx", {517, 145}}, {"PUZCAS45.pcx", {520, 68}},
                  {"PUZCAS46.pcx", {524, 234}}, {"PUZCAS47.pcx", {525, 327}},
              },
          .mapObject =
              {
                  "AVCcasx0.def",
                  "AVCcasx0.def",
                  "AVCcasx0.def",
                  "AVCCAST0.DEF",
                  "AVCCASZ0.DEF",
              },
          .musicTheme = "CstleTown.wav",
          .guildBackground = "TPMAGE.pcx",
          .townBackground = "TBCSBACK.pcx",
          .guildWindow = "TPMAGECS.pcx",
          .hallSlots =
              {
                  {
                      {
                          Enum::BUILD_VILLAGE_HALL,
                          Enum::BUILD_TOWN_HALL,
                          Enum::BUILD_CITY_HALL,
                          Enum::BUILD_CAPITOL,
                      },
                      {
                          Enum::BUILD_FORT,
                          Enum::BUILD_CITADEL,
                          Enum::BUILD_CASTLE,
                      },
                      {
                          Enum::BUILD_TAVERN,
                          Enum::BUILD_SPECIAL_19,
                      },
                      {Enum::BUILD_BLACKSMITH},
                  },
                  {
                      {
                          Enum::BUILD_MARKETPLACE,
                          Enum::BUILD_RESOURCE_SILO,
                      },
                      {
                          Enum::BUILD_MAGE_GUILD_1,
                          Enum::BUILD_MAGE_GUILD_2,
                          Enum::BUILD_MAGE_GUILD_3,
                          Enum::BUILD_MAGE_GUILD_4,
                      },
                      {
                          Enum::BUILD_SHIPYARD,
                          Enum::BUILD_SPECIAL_18,
                      },
                  },
                  {
                      {Enum::BUILD_SPECIAL_20}, // special2 for castle
                      {Enum::BUILD_HORDE_3},
                  },
                  {
                      {
                          Enum::BUILD_DWELLING_LEVEL_1,
                          Enum::BUILD_DWELLING_UPGRADE_LEVEL_1,
                      },
                      {
                          Enum::BUILD_DWELLING_LEVEL_2,
                          Enum::BUILD_DWELLING_UPGRADE_LEVEL_2,
                      },
                      {
                          Enum::BUILD_DWELLING_LEVEL_3,
                          Enum::BUILD_DWELLING_UPGRADE_LEVEL_3,
                      },
                      {
                          Enum::BUILD_DWELLING_LEVEL_4,
                          Enum::BUILD_DWELLING_UPGRADE_LEVEL_4,
                      },
                  },
                  {
                      {
                          Enum::BUILD_DWELLING_LEVEL_5,
                          Enum::BUILD_DWELLING_UPGRADE_LEVEL_5,
                      },
                      {
                          Enum::BUILD_DWELLING_LEVEL_6,
                          Enum::BUILD_DWELLING_UPGRADE_LEVEL_6,
                      },
                      {
                          Enum::BUILD_DWELLING_LEVEL_7,
                          Enum::BUILD_DWELLING_UPGRADE_LEVEL_7,
                      },
                  },
              },
          .blacksmith = {Enum::BALLISTA},
          .builds =
              {
                  {
                      .id = Enum::BUILD_VILLAGE_HALL,
                      .animation = "TBCSHALL.def",
                      .x = 0,
                      .y = 209,
                      .z = 1,
                      .border = "TOCSH101.pcx",
                      .area = "TZCSH101.pcx",
                      .icon = "ThCsHal1.pcx",
                      .require = {},
                      .cost = {},
                      .income =
                          {
                              {
                                  .id = Enum::GOLD,
                                  .minVal = 500,
                                  .maxVal = 500,
                                  .frequency = 1,
                              },
                          },
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_TOWN_HALL,
                      .animation = "TBCSHAL2.def",
                      .x = 0,
                      .y = 176,
                      .z = 1,
                      .border = "TOCSH201.pcx",
                      .area = "TZCSH201.pcx",
                      .icon = "ThCsHal2.pcx",
                      .require = {Enum::BUILD_TAVERN},
                      .cost = {},
                      .income =
                          {
                              {
                                  .id = Enum::GOLD,
                                  .minVal = 1000,
                                  .maxVal = 1000,
                                  .frequency = 1,
                              },
                          },
                      .upgrades = Enum::BUILD_VILLAGE_HALL,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_CITY_HALL,
                      .animation = "TBCSHAL3.def",
                      .x = 0,
                      .y = 164,
                      .z = 1,
                      .border = "TOCSH301.pcx",
                      .area = "TZCSH301.pcx",
                      .icon = "ThCsHal3.pcx",
                      .require =
                          {
                              Enum::BUILD_MAGE_GUILD_1,
                              Enum::BUILD_MARKETPLACE,
                              Enum::BUILD_BLACKSMITH,
                          },
                      .cost = {},
                      .income =
                          {
                              {
                                  .id = Enum::GOLD,
                                  .minVal = 2000,
                                  .maxVal = 2000,
                                  .frequency = 1,
                              },
                          },
                      .upgrades = Enum::BUILD_TOWN_HALL,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_CAPITOL,
                      .animation = "TBCSHAL3.def",
                      .x = 0,
                      .y = 164,
                      .z = 1,
                      .border = "TOCSH301.pcx",
                      .area = "TZCSH301.pcx",
                      .icon = "ThCsHal3.pcx",
                      .require =
                          {
                              Enum::BUILD_CASTLE,
                          },
                      .cost = {},
                      .income =
                          {
                              {
                                  .id = Enum::GOLD,
                                  .minVal = 4000,
                                  .maxVal = 4000,
                                  .frequency = 1,
                              },
                          },
                      .upgrades = Enum::BUILD_CITY_HALL,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_FORT,
                      .animation = "TBELCSTL.def",
                      .x = 349,
                      .y = 101,
                      .z = 1,
                      .border = "TOELCSTL.pcx",
                      .area = "TZELCSTL.pcx",
                      .icon = "ThCsCAS1.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                      .bonus =
                          {
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 1,
                                  .val = 0.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 2,
                                  .val = 0.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 3,
                                  .val = 0.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 4,
                                  .val = 0.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 5,
                                  .val = 0.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 6,
                                  .val = 0.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 7,
                                  .val = 0.5,
                              },
                              {
                                  .id = Enum::TOWN_BATTLE_SIEGE,
                                  .subId = NULL,
                                  .val = 0,
                              },
                          },
                  },
                  {
                      .id = Enum::BUILD_CITADEL,
                      .animation = "TBELCAS2.def",
                      .x = 349,
                      .y = 101,
                      .z = 1,
                      .border = "TOELCAS2.pcx",
                      .area = "TZELCAS2.pcx",
                      .icon = "ThCsCAS2.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = Enum::BUILD_FORT,
                      .autoMode = false,
                      .bonus =
                          {
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 1,
                                  .val = 1,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 2,
                                  .val = 1,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 3,
                                  .val = 1,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 4,
                                  .val = 1,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 5,
                                  .val = 1,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 6,
                                  .val = 1,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 7,
                                  .val = 1,
                              },
                              {
                                  .id = Enum::TOWN_BATTLE_SIEGE,
                                  .subId = Enum::MARKSMAN,
                                  .val = 1,
                              },
                          },
                  },
                  {
                      .id = Enum::BUILD_CASTLE,
                      .animation = "TBELCAS3.def",
                      .x = 349,
                      .y = 101,
                      .z = 1,
                      .border = "TOELCAS3.bmp",
                      .area = "TZELCAS3.pcx",
                      .icon = "ThCsCAS3.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = Enum::BUILD_CITADEL,
                      .autoMode = false,
                      .bonus =
                          {
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 1,
                                  .val = 1.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 2,
                                  .val = 1.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 3,
                                  .val = 1.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 4,
                                  .val = 1.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 5,
                                  .val = 1.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 6,
                                  .val = 1.5,
                              },
                              {
                                  .id = Enum::CREATURE_GROWTH_RATE,
                                  .subId = 7,
                                  .val = 1.5,
                              },
                              {
                                  .id = Enum::TOWN_BATTLE_SIEGE,
                                  .subId = Enum::MARKSMAN,
                                  .val = 3,
                              },
                          },
                  },
                  {
                      .id = Enum::BUILD_TAVERN,
                      .animation = "TBELTVRN.def",
                      .x = 553,
                      .y = 203,
                      .z = 7,
                      .border = "TOELTVRN.pcx",
                      .area = "TOELTVRN.pcx",
                      .icon = "ThCsTAV1.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_BLACKSMITH,
                      .animation = "TBELBLAK.def",
                      .x = 449,
                      .y = 151,
                      .z = 5,
                      .border = "TOELBLAK.pcx",
                      .area = "TZELBLAK.pcx",
                      .icon = "ThCsBLAK.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_MARKETPLACE,
                      .animation = "TBELMARK.def",
                      .x = 347,
                      .y = 216,
                      .z = 8,
                      .border = "TOELBLAK.pcx",
                      .area = "TOELMARK.bmp",
                      .icon = "ThCsMRK1.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_RESOURCE_SILO,
                      .animation = "TBELSILO.def",
                      .x = 372,
                      .y = 171,
                      .z = 7,
                      .border = "TOELSILO.pcx",
                      .area = "TZELSILO.bmp",
                      .icon = "ThCsMRK2.pcx",
                      .require = {},
                      .cost = {},
                      .income =
                          {
                              {
                                  .id = Enum::WOOD,
                                  .minVal = 1,
                                  .maxVal = 1,
                                  .frequency = 1,
                              },
                              {
                                  .id = Enum::ORE,
                                  .minVal = 1,
                                  .maxVal = 1,
                                  .frequency = 1,
                              },
                          },
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_SPECIAL_10,
                      .animation = "",
                  },
                  {
                      .id = Enum::BUILD_MAGE_GUILD_1,
                      .animation = "TBCSMAGE.def",
                      .x = 707,
                      .y = 166,
                      .z = 1,
                      .border = "TOCSMAG1.bmp",
                      .area = "TZCSMAG1.bmp",
                      .icon = "ThCsMAG1.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_MAGE_GUILD_2,
                      .animation = "TBCSMAG2.def",
                      .x = 706,
                      .y = 135,
                      .z = 1,
                      .border = "TOCSMAG2.bmp",
                      .area = "TZCSMAG2.bmp",
                      .icon = "ThCsMAG2.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_MAGE_GUILD_3,
                      .animation = "TBCSMAG3.def",
                      .x = 704,
                      .y = 107,
                      .z = 1,
                      .border = "TOCSMAG3.bmp",
                      .area = "TZCSMAG3.bmp",
                      .icon = "ThCsMAG3.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_MAGE_GUILD_4,
                      .animation = "TBCSMAG4.def",
                      .x = 704,
                      .y = 76,
                      .z = 1,
                      .border = "TOCSMAG4.bmp",
                      .area = "TZCSMAG4.bmp",
                      .icon = "ThCsMAG4.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_MAGE_GUILD_5,
                      .animation = "",
                  },
                  {
                      .id = Enum::BUILD_SHIPYARD,
                      .animation = "TBCSDOCK.def",
                      .x = 478,
                      .y = 134,
                      .z = -3,
                      .border = "TOCSDKMS.bmp",
                      .area = "TZCSDKMS.bmp",
                      .icon = "ThCsDock.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_GRAIL,
                      .animation = "TBCSHOLY.def",
                      .x = 456,
                      .y = 109,
                      .z = -6,
                      .border = "TOCSHOLY.bmp",
                      .area = "TZCSHOLY.bmp",
                      .icon = "ThCsHOLY.pcx",
                      .require = {},
                      .cost = {},
                      .income =
                          {
                              {
                                  .id = Enum::GOLD,
                                  .minVal = 5000,
                                  .maxVal = 5000,
                                  .frequency = 1,
                              },
                          },
                      .upgrades = std::nullopt,
                      .autoMode = false,
                      .bonus =
                          {
                              {
                                  .id = Enum::TOWN_BATTLE_MORALE_RAISE,
                                  .subId = NULL,
                                  .val = 2,
                              },
                          },
                  },
                  {
                      .id = Enum::BUILD_SPECIAL_18,
                      .animation = "TBCSSPEC.def",
                      .x = 553,
                      .y = 71,
                      .z = -4,
                      .border = "TOCSLT01.bmp",
                      .area = "TZCSLT01.bmp",
                      .icon = "ThCsLite.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                      .bonus =
                          {
                              {
                                  .id = Enum::HERO_MOVENT_SEA,
                                  .subId = NULL,
                                  .val = 500,
                              },
                          },
                  },
                  {
                      .id = Enum::BUILD_SPECIAL_19,
                      .animation = "TBCSEXT1.def",
                      .x = 0,
                      .y = 198,
                      .z = 2,
                      .border = "TOCSTAV2.bmp",
                      .area = "TZCSTAV2.bmp",
                      .icon = "ThCsTAV2.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = Enum::BUILD_TAVERN,
                      .autoMode = false,
                      .bonus =
                          {
                              {
                                  .id = Enum::TOWN_BATTLE_MORALE_RAISE,
                                  .subId = NULL,
                                  .val = 1,
                              },
                          },
                  },
                  {
                      .id = Enum::BUILD_SPECIAL_20,
                      .animation = "TBCSSPEC.def",
                      .x = 553,
                      .y = 71,
                      .z = -4,
                      .border = "TOCSLT01.bmp",
                      .area = "TZCSLT01.bmp",
                      .icon = "ThCsLite.pcx",
                      .require = {},
                      .cost = {},
                      .income = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                      .bonus =
                          {
                              {
                                  .id = Enum::HERO_MOVENT_LAND,
                                  .subId = ObjectType::STABLES,
                                  .val = 500,
                                  .forceVisit = true,
                                  .frequency = 7,
                              },
                          },
                  },
                  {
                      .id = Enum::BUILD_SPECIAL_21,
                      .animation = "",
                  },
                  {
                      .id = Enum::BUILD_DWELLING_LEVEL_1,
                      .animation = "TBCSDW_0.def",
                      .x = 304,
                      .y = 92,
                      .z = -1,
                      .border = "TOCSPIK1.bmp",
                      .area = "TZCSPIK1.bmp",
                      .icon = "ThCsPIK1.pcx",
                      .require = {},
                      .cost = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_DWELLING_UPGRADE_LEVEL_1,
                      .animation = "TBCSUP_0.def",
                      .x = 304,
                      .y = 65,
                      .z = -1,
                      .border = "TOCSPIK2.bmp",
                      .area = "TZCSPIK2.bmp",
                      .icon = "ThCsPIK2.pcx",
                      .require = {},
                      .cost = {},
                      .upgrades = Enum::BUILD_DWELLING_LEVEL_1,
                      .autoMode = false,
                  },
                  {
                      .id = Enum::BUILD_DWELLING_LEVEL_2,
                      .animation = "TBCSDW_1.def",
                      .x = 360,
                      .y = 130,
                      .z = 0,
                      .border = "TOCSCRS1.bmp",
                      .area = "TZCSCRS1.bmp",
                      .icon = "ThCsCRS1.pcx",
                      .require = {},
                      .cost = {},
                      .upgrades = std::nullopt,
                      .autoMode = false,
                  },
              },
  };
};