#pragma once

#include <cstdint>
#include <flat_set>
#include <string>
#include <vector>

class game_hero {
public:
  int index;
  struct second_skill {
    std::string name;
    uint8_t level;
  };
  std::vector<second_skill> second_skills;
  bool spell_book = false;
  std::flat_set<std::string> spells;
};