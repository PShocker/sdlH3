#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct PandorBoxComp {
  std::string message;
  std::vector<std::pair<uint16_t, uint32_t>> guards;
  std::vector<std::pair<uint16_t, uint32_t>> creatures;
  uint32_t heroExperience;
  int32_t manaDiff;
  int8_t morale;
  int8_t luck;
  std::array<uint32_t, 7> resources;
  std::array<uint8_t, 4> primary;
  std::vector<std::pair<uint8_t, uint8_t>> secSkills;
  std::vector<uint16_t> artifacts;
  std::vector<uint8_t> spells;
};