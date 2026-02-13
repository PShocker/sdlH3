#include "Set/HeroSet.h"

void HeroSet::init() {
  for (auto heros : townHeros) {
    for (auto hero : *heros) {
      fullHeros.push_back(&hero);
    }
  }
  std::ranges::sort(fullHeros, {}, &HeroSetI::index);
}
