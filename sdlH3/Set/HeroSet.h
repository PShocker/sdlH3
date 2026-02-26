#pragma once
#include "Enum/Enum.h"
#include "Set/hero/CastleHeroSet.h"
#include "Set/hero/ConfluxHeroSet.h"
#include "Set/hero/DungeonHeroSet.h"
#include "Set/hero/FortressHeroSet.h"
#include "Set/hero/InfernoHeroSet.h"
#include "Set/hero/NecropolisHeroSet.h"
#include "Set/hero/RampartHeroSet.h"
#include "Set/hero/SpecialHeroSet.h"
#include "Set/hero/StrongholdHeroSet.h"
#include "Set/hero/TowerHeroSet.h"
#include <array>
#include <cstdint>
#include <vector>

struct HeroSet {
  const static inline std::array heroLevelExperience = {
      0,      1000,   2000,   3200,   4600,   6200,   8000,   10000,
      12200,  14700,  17500,  20600,  24320,  28784,  34140,  40468,
      48022,  57226,  68471,  82165,  98798,  118757, 142508, 171009,
      205210, 246252, 295502, 354602, 425522, 510626};

  const static inline std::array townHeros = {
      &CastleHeroSet::heros,     &RampartHeroSet::heros,
      &TowerHeroSet::heros,      &InfernoHeroSet::heros,
      &NecropolisHeroSet::heros, &DungeonHeroSet::heros,
      &StrongholdHeroSet::heros, &FortressHeroSet::heros,
      &ConfluxHeroSet::heros,    &SpecialHeroSet::heros,
  };

  static inline std::array<std::vector<const HeroSetI *>, 18> fullHerosClasz;

  static inline std::vector<const HeroSetI *> fullHeros;

  static void init();
};