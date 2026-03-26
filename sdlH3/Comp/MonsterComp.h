#pragma once
#include <array>
#include <cstdint>
#include <string>
struct MonsterComp {
  uint32_t id;
  uint16_t count;
  uint8_t initialCharacter;
  bool hasMessage;
  std::string message;
  std::array<uint32_t, 7> resources;
  uint16_t gainedArtifact;
  uint8_t neverFlees;
  uint8_t notGrowingTeam;
};