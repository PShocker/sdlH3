#pragma once
#include "SDL3/SDL_pixels.h"
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
#include "creature/SpecialCreatureSet.h"
#include <algorithm>
#include <vector>

struct CreatureSet {
  const static inline std::array townCreatures = {
      &CastleCreatureSet::creatures,     &RampartCreatureSet::creatures,
      &TowerCreatureSet::creatures,      &InfernoCreatureSet::creatures,
      &NecropolisCreatureSet::creatures, &DungeonCreatureSet::creatures,
      &StrongholdCreatureSet::creatures, &FortressCreatureSet::creatures,
      &ConfluxCreatureSet::creatures,    &NeutralCreatureSet::creatures,
      &SpecialCreatureSet::creatures,
  };

  enum CREATURE_OV_COLOR {
    OV_COLOR_CYAN,
    OV_COLOR_TRANSPARENCY,
  };

  const static inline std::array<SDL_Color, 2> ovColor = {
      SDL_Color{0, 255, 255, 255}, // CYAN
      SDL_Color{0, 0, 0, 0}        // TRANSPARENCY
  };

  static inline std::vector<CreatureSetI *> fullCreatures;

  static void init();
};