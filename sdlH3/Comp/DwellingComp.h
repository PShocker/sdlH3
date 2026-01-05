#pragma once
#include <cstdint>
#include <vector>
struct DwellingComp {
  uint32_t id;
  std::vector<std::pair<uint16_t, uint32_t>> garCreatures;
  std::vector<std::pair<uint16_t, uint32_t>> creatures;
};