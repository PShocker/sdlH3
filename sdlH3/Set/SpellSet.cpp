#include "Set/SpellSet.h"
#include <cstdint>

void SpellSet::init() {

  for (auto &spell : spells) {
    switch (spell.type) {
    case Enum::SPELL_TYPE_ADV: {
      spellsAdv.push_back(&spell);
      break;
    }
    case Enum::SPELL_TYPE_BAT: {
      spellsBat.push_back(&spell);
      break;
    }
    case Enum::SPELL_TYPE_CRE: {
      spellsCre.push_back(&spell);
      break;
    }
    }
    for (uint8_t i = 0; i < 4; i++) {
      if (spell.school[i]) {
        spellsSchool[i].push_back(&spell);
      }
    }
    spellsLvl[spell.level].push_back(&spell);
  }
}
