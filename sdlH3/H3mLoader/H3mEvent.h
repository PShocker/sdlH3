#pragma once

#include <cstdint>
#include <set>
#include <string>

struct H3mEvent {
  std::string name;
  std::string message;
  uint32_t resources[7];
  uint16_t creatures[7];
  std::set<uint8_t> players;
  bool humanAffected;

  bool computerAffected;
  uint16_t firstOccurrence;
  uint16_t nextOccurrence;

  std::set<uint8_t> builtBuildings;
};