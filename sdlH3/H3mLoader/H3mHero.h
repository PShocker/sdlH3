#pragma once

#include "H3mCreatureSet.h"
#include <array>
#include <cstdint>
#include <set>
#include <string>

struct H3mHero {
  uint8_t id;
  uint8_t subId;
  uint8_t portrait = 255;
  std::string name;
  std::set<uint8_t> players; /// Who can hire this hero (bitfield).

  uint32_t exp;
  std::vector<std::pair<uint8_t, uint8_t>>
      secSkills; // first - ID of skill, second - level of skill (1 - basic, 2 -
                 // adv., 3 - expert); if hero has ability (-1, -1) it meansthat
                 // it should have default secondary
  std::set<uint8_t> spells;
  bool gender;
  std::array<uint8_t, 4> primSkills;
  std::vector<uint16_t> artifactsInBackpack;
  std::vector<uint16_t> artifacts;

  uint8_t customPortraitSource;

  std::string biography;

  uint8_t playerId;
  H3mCreatureSet creatureSet;
};