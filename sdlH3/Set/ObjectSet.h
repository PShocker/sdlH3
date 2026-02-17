#pragma once
#include "SDL3/SDL_pixels.h"
#include "objects/DwellingSet.h"
#include "objects/GenericSet.h"

#include <algorithm>
#include <flat_map>
#include <vector>

struct ObjectSet {
  const static inline std::array objects = {
      &DwellingSet::dwellings1, &DwellingSet::dwellings2,
      &DwellingSet::dwellings3, &DwellingSet::dwellings4,
      &GenericSet::generics,
  };

  const static inline std::flat_map<uint8_t, ObjectSetI *> fullObjects = {};

  static void init();
};