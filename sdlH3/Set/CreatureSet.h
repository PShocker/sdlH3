#pragma once
#include "Set/creature/CastleCreatureSet.h"
#include "Set/creature/ConfluxCreatureSet.h"
#include "Set/creature/DungeonCreatureSet.h"
#include "Set/creature/FortressCreatureSet.h"
#include "Set/creature/InfernoCreatureSet.h"
#include "Set/creature/NecropolisCreatureSet.h"
#include "Set/creature/NeutralCreatureSet.h"
#include "Set/creature/RampartCreatureSet.h"
#include "Set/creature/StrongholdCreatureSet.h"
#include "Set/creature/TowerCreatureSet.h"
#include <algorithm>
#include <vector>

struct CreatureSet {
  const static inline std::vector<const std::vector<CreatureSetI> *>
      townCreatures = {
          &CastleCreatureSet::creatures,     &RampartCreatureSet::creatures,
          &TowerCreatureSet::creatures,      &InfernoCreatureSet::creatures,
          &NecropolisCreatureSet::creatures, &DungeonCreatureSet::creatures,
          &StrongholdCreatureSet::creatures, &FortressCreatureSet::creatures,
          &ConfluxCreatureSet::creatures,    &NeutralCreatureSet::creatures,
  };

  static constexpr auto fullCreatures = []() {
    std::vector<CreatureSetI> r;
    for (auto creatures : townCreatures) {
      r.append_range(*creatures);
    }
    std::ranges::sort(r, {}, &CreatureSetI::index);
    return r;
  };
};