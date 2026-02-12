#pragma once
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
#include <algorithm>
#include <vector>

struct HeroSet {
  const static inline std::vector<const std::vector<HeroSetI> *> townHeros = {
      &CastleHeroSet::heros,     &RampartHeroSet::heros,
      &TowerHeroSet::heros,      &InfernoHeroSet::heros,
      &NecropolisHeroSet::heros, &DungeonHeroSet::heros,
      &StrongholdHeroSet::heros, &FortressHeroSet::heros,
      &ConfluxHeroSet::heros,    &SpecialHeroSet::heros,
  };

  static constexpr auto fullHeros = []() {
    std::vector<HeroSetI> r;
    for (auto heros : townHeros) {
      r.append_range(*heros);
    }
    std::ranges::sort(r, {}, &HeroSetI::index);
    return r;
  };
};