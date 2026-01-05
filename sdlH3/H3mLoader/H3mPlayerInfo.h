#pragma once
#include <cstdint>
#include <set>
#include <string>
#include <vector>

enum class EAiTactic : int8_t {
  NONE = -1,
  RANDOM = 0,
  WARRIOR = 1,
  BUILDER = 2,
  EXPLORER = 3
};

struct H3mPlayerInfo {
  bool canHumanPlay;
  bool canComputerPlay;
  EAiTactic aiTactic; /// The default value is EAiTactic::RANDOM.

  std::set<uint8_t> allowedFactions;
  bool isFactionRandom;

  /// main hero instance (VCMI maps only)
  std::string mainHeroInstance;
  /// Player has a random main hero
  bool hasRandomHero;
  /// The default value is -1.
  int8_t mainCustomHeroPortrait;
  std::string mainCustomHeroNameTextId;
  /// ID of custom hero (only if portrait and hero name are set, otherwise
  /// unpredicted value), -1 if none (not always -1)
  int8_t mainCustomHeroId;

  std::vector<int8_t> heroesNames; /// list of placed heroes on the map
  bool hasMainTown;                /// The default value is false.
  bool generateHeroAtMainTown;     /// The default value is false.
  uint8_t posOfMainTown[3];
  int8_t team; /// The default value NO_TEAM
};