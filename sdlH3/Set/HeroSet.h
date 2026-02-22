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

  const static inline std::vector<HeroClazz> heroClazz = {
      // Knight (索引 0)
      {
          .id = Enum::HERO_CLASS_KNIGHT,
          .lowPrimRate = {35, 45, 10, 10},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {2, 2, 1, 1},
          .secSkillRate = {4, 5, 5, 4, 4, 8, 10, 3, 2, 3, 8, 2, 0, 6,
                           1, 3, 4, 2, 1, 7, 5,  4, 7, 5, 1, 1, 5, 2},
      },
      // Cleric (索引 1)
      {
          .id = Enum::HERO_CLASS_CLERIC,
          .lowPrimRate = {20, 15, 30, 35},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {1, 0, 2, 2},
          .secSkillRate = {2, 3, 4, 3, 7, 5, 2, 7, 4, 5, 4, 6, 0, 3,
                           2, 4, 4, 3, 6, 2, 2, 4, 4, 3, 6, 5, 2, 10},
      },
      // Ranger (索引 2)
      {
          .id = Enum::HERO_CLASS_RANGER,
          .lowPrimRate = {35, 45, 10, 10},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {1, 3, 1, 1},
          .secSkillRate = {7, 8, 5, 7, 4, 3, 6, 3, 3, 6, 4, 2, 0, 2,
                           0, 1, 3, 3, 1, 5, 6, 4, 5, 8, 2, 2, 9, 3},
      },
      // Druid (索引 3)
      {
          .id = Enum::HERO_CLASS_DRUID,
          .lowPrimRate = {10, 20, 35, 35},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {0, 2, 1, 2},
          .secSkillRate = {5, 5, 5, 2, 4, 2, 2, 8, 6, 9, 4, 7, 0, 3,
                           1, 2, 4, 4, 8, 1, 1, 4, 1, 3, 7, 6, 1, 7},
      },
      // Alchemist (索引 4)
      {
          .id = Enum::HERO_CLASS_ALCHEMIST,
          .lowPrimRate = {30, 30, 20, 20},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {1, 1, 2, 2},
          .secSkillRate = {4, 5, 6, 4, 3, 3, 3, 6,  4, 2, 6, 3, 0, 4,
                           1, 4, 2, 3, 3, 4, 4, 10, 6, 8, 4, 3, 5, 2},
      },
      // Wizard (索引 5)
      {
          .id = Enum::HERO_CLASS_WIZARD,
          .lowPrimRate = {10, 10, 40, 40},
          .highPrimRate = {30, 20, 20, 30},
          .defaultPrim = {0, 0, 2, 3},
          .secSkillRate = {2, 2, 2, 2, 4, 1, 4, 10, 8, 4, 4,  8, 0, 5,
                           2, 6, 3, 3, 9, 1, 1, 4,  1, 1, 10, 8, 0, 7},
      },
      // Demon (索引 6)
      {
          .id = Enum::HERO_CLASS_DEMON,
          .lowPrimRate = {35, 35, 15, 15},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {2, 2, 1, 1},
          .secSkillRate = {4, 6, 10, 5, 4, 4, 3, 4, 2, 2, 7, 3, 0, 3,
                           4, 2, 1,  3, 2, 6, 5, 4, 8, 7, 2, 3, 6, 2},
      },
      // Heretic (索引 7)
      {
          .id = Enum::HERO_CLASS_HERETIC,
          .lowPrimRate = {15, 15, 35, 35},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {1, 1, 2, 1},
          .secSkillRate = {4, 4, 3, 3, 3, 2, 2, 8, 10, 2, 6, 4, 0, 2,
                           5, 3, 2, 4, 5, 4, 4, 4, 4,  4, 6, 6, 3, 5},
      },
      // Death Knight (索引 8)
      {
          .id = Enum::HERO_CLASS_DEATH_KNIGHT,
          .lowPrimRate = {30, 25, 20, 25},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {1, 2, 2, 1},
          .secSkillRate = {4, 5, 5, 4, 2, 8, 0, 6, 4, 1, 7, 4, 10, 0,
                           1, 2, 3, 4, 2, 5, 5, 4, 7, 5, 5, 4, 5,  0},
      },
      // Necromancer (索引 9)
      {
          .id = Enum::HERO_CLASS_NECROMANCER,
          .lowPrimRate = {15, 15, 35, 35},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {1, 0, 2, 2},
          .secSkillRate = {6, 2, 4, 2, 4, 5, 0, 8, 6, 1, 5, 7, 10, 3,
                           2, 3, 3, 8, 6, 2, 3, 4, 3, 2, 6, 6, 1,  0},
      },
      // Overlord (索引 10)
      {
          .id = Enum::HERO_CLASS_OVERLORD,
          .lowPrimRate = {35, 35, 15, 15},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {2, 2, 1, 1},
          .secSkillRate = {5, 6, 8, 5, 3, 4,  8, 3, 3, 1, 7, 2, 0, 4,
                           2, 1, 0, 3, 1, 10, 8, 4, 8, 6, 1, 2, 6, 1},
      },
      // Warlock (索引 11)
      {
          .id = Enum::HERO_CLASS_WARLOCK,
          .lowPrimRate = {10, 10, 50, 30},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {0, 0, 3, 2},
          .secSkillRate = {2, 2, 2, 2, 4, 4, 3, 10, 8, 2, 6, 8,  0, 5,
                           5, 2, 2, 5, 8, 1, 1, 4,  1, 1, 8, 10, 0, 6},
      },
      // Barbarian (索引 12)
      {
          .id = Enum::HERO_CLASS_BARBARIAN,
          .lowPrimRate = {55, 35, 5, 5},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {4, 0, 1, 1},
          .secSkillRate = {8, 7, 7, 8, 1, 2, 5, 2, 3,  3, 8, 2, 0, 2,
                           2, 3, 0, 3, 1, 8, 8, 4, 10, 6, 1, 1, 6, 1},
      },
      // Battle Mage (索引 13)
      {
          .id = Enum::HERO_CLASS_BATTLE_MAGE,
          .lowPrimRate = {30, 20, 25, 25},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {2, 1, 1, 1},
          .secSkillRate = {4, 4, 9, 4, 3, 0, 4, 6, 4, 2, 6, 5, 0, 1,
                           3, 3, 3, 3, 4, 5, 4, 4, 8, 4, 5, 6, 4, 4},
      },
      // Beastmaster (索引 14)
      {
          .id = Enum::HERO_CLASS_BEASTMASTER,
          .lowPrimRate = {30, 50, 10, 10},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {0, 4, 1, 1},
          .secSkillRate = {8, 7, 8, 7, 1, 8, 5, 2, 2, 2,  7, 1, 0, 1,
                           0, 1, 2, 3, 1, 6, 8, 4, 5, 10, 1, 1, 5, 6},
      },
      // Witch (索引 15)
      {
          .id = Enum::HERO_CLASS_WITCH,
          .lowPrimRate = {5, 15, 40, 40},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {0, 1, 2, 2},
          .secSkillRate = {2, 3, 3, 2, 2, 6, 1, 8, 8, 4, 8, 10, 0, 1,
                           3, 3, 3, 3, 7, 1, 1, 4, 2, 4, 7, 8,  0, 8},
      },
      // Elementalist (索引 16)
      {
          .id = Enum::HERO_CLASS_ELEMENTALIST,
          .lowPrimRate = {45, 25, 15, 15},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {3, 1, 1, 1},
          .secSkillRate = {6, 8, 8, 6, 2, 5, 3, 2, 3, 2, 8, 2, 0, 3,
                           3, 2, 2, 3, 1, 8, 8, 8, 9, 5, 1, 1, 2, 1},
      },
      // Planeswalker (索引 17)
      {
          .id = Enum::HERO_CLASS_PLANESWALKER,
          .lowPrimRate = {15, 15, 35, 35},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {0, 0, 3, 3},
          .secSkillRate = {2, 2, 2, 2, 4, 4, 3, 8, 8, 2, 4, 8, 0, 3,
                           6, 6, 6, 6, 8, 1, 1, 4, 1, 1, 8, 8, 0, 4},
      },
  };
  
  const static inline std::array townHeros = {
      &CastleHeroSet::heros,     &RampartHeroSet::heros,
      &TowerHeroSet::heros,      &InfernoHeroSet::heros,
      &NecropolisHeroSet::heros, &DungeonHeroSet::heros,
      &StrongholdHeroSet::heros, &FortressHeroSet::heros,
      &ConfluxHeroSet::heros,    &SpecialHeroSet::heros,
  };

  static inline std::vector<const HeroSetI *> fullHeros;

  static void init();
};