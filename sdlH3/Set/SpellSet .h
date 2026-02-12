#pragma once
#include "Set/StructSet.h"
#include "Set/spell/SummonBoat.h"

#include <algorithm>
#include <vector>

struct SpellSet {
  const static inline std::vector<const SpellData *> spellsAdv = {

  };

  const static inline std::vector<const SpellData *> spellsBat = {
      &SummonBoat::spell,
  };

  const static inline std::vector<const SpellData *> spellsCre = {
      &SummonBoat::spell,
  };

  static constexpr auto fullSpells = []() {
    std::vector<const SpellData *> r;
    for (auto spel : {spellsAdv, spellsBat, spellsCre}) {
      r.append_range(spel);
    }
    std::ranges::sort(r, {}, &SpellData::index);
    return r;
  };
};