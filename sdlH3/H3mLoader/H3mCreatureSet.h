#pragma once

#include <cstdint>
#include <utility>
#include <vector>

enum class EArmyFormation : int8_t { LOOSE, TIGHT };

struct H3mCreatureSet {
  std::vector<std::pair<uint16_t, uint32_t>> creatures;
};