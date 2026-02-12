#pragma once
#include "Set/StructSet.h"

#include <algorithm>
#include <cstdint>
#include <vector>

struct ArtifactBonus {
  uint8_t type;
  uint8_t subType;
  int32_t val;
  uint8_t valType;
};

struct ArtifactData {
  uint8_t index;
  std::vector<ArtifactBonus> bouns;
};

struct ArtifactSet {
    

};