

#include "SDL3/SDL_rect.h"
#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct FactionBuildIncome {
  uint32_t id;
  uint32_t subId;
  uint32_t val;
  uint8_t frequency;
};

struct FactionBuild {
  std::string animation;
  int32_t x;
  int32_t y;
  int32_t z;
  std::string border;
  std::string area;
  std::string icon;
  std::vector<uint8_t> require;
  std::array<uint32_t, 7> cost;
  std::vector<FactionBuildIncome> income;
  uint8_t upgrades;
  bool mode;
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
  std::vector<std::vector<std::vector<uint8_t>>> hallSlots;
  std::vector<uint16_t> blacksmith;
  std::vector<FactionBuild> builds;
  std::vector<uint8_t> bonusBuilds;
};