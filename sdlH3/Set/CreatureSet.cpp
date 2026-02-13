#include "Set/CreatureSet.h"

void CreatureSet::init() {
  for (auto creatures : townCreatures) {
    for (auto creature : *creatures) {
      fullCreatures.push_back(&creature);
    }
  }
  std::ranges::sort(fullCreatures, {}, &CreatureSetI::index);
}
