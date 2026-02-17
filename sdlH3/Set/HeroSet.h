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
#include <array>
#include <vector>

struct HeroSet {
  const static inline std::array heroLevelExperience = {
      0,      // 等级1
      1000,   // 等级2
      2000,   // 等级3
      3200,   // 等级4
      4600,   // 等级5
      6200,   // 等级6
      8000,   // 等级7
      10000,  // 等级8
      12200,  // 等级9
      14700,  // 等级10
      17500,  // 等级11
      20600,  // 等级12
      24320,  // 等级13
      28784,  // 等级14
      34140,  // 等级15
      40468,  // 等级16
      48022,  // 等级17
      57226,  // 等级18
      68471,  // 等级19
      82165,  // 等级20
      98798,  // 等级21
      118757, // 等级22
      142508, // 等级23
      171009, // 等级24
      205210, // 等级25
      246252, // 等级26
      295502, // 等级27
      354602, // 等级28
      425522, // 等级29
      510626  // 等级30
  };

  const static inline std::vector<std::vector<uint8_t>> heroLowPrimChance = {
      {35, 45, 10, 10}, // 索引 0: Knight
      {20, 15, 30, 35}, // 索引 1: Cleric
      {35, 45, 10, 10}, // 索引 2: Ranger
      {10, 20, 35, 35}, // 索引 3: Druid
      {30, 30, 20, 20}, // 索引 4: Alchemist
      {10, 10, 40, 40}, // 索引 5: Wizard
      {35, 35, 15, 15}, // 索引 6: Demon
      {15, 15, 35, 35}, // 索引 7: Heretic
      {30, 25, 20, 25}, // 索引 8: Death Knight
      {15, 15, 35, 35}, // 索引 9: Necromancer
      {35, 35, 15, 15}, // 索引 10: Overlord
      {10, 10, 50, 30}, // 索引 11: Warlock
      {55, 35, 5, 5},   // 索引 12: Barbarian
      {30, 20, 25, 25}, // 索引 13: Battle Mage
      {30, 50, 10, 10}, // 索引 14: Beastmaster
      {5, 15, 40, 40},  // 索引 15: Witch
      {45, 25, 15, 15}, // 索引 16: Elementalist
      {15, 15, 35, 35}  // 索引 17: Planeswalker
  };

  const static inline std::vector<std::vector<uint8_t>> heroSecondarySkills = {
      // 0: Knight
      {4, 5, 5, 4, 4, 8, 10, 3, 2, 3, 8, 2, 0, 6,
       1, 3, 4, 2, 1, 7, 5,  4, 7, 5, 1, 1, 5, 2},
      // 1: Cleric
      {2, 3, 4, 3, 7, 5, 2, 7, 4, 5, 4, 6, 0, 3,
       2, 4, 4, 3, 6, 2, 2, 4, 4, 3, 6, 5, 2, 10},
      // 2: Ranger
      {7, 8, 5, 7, 4, 3, 6, 3, 3, 6, 4, 2, 0, 2,
       0, 1, 3, 3, 1, 5, 6, 4, 5, 8, 2, 2, 9, 3},
      // 3: Druid
      {5, 5, 5, 2, 4, 2, 2, 8, 6, 9, 4, 7, 0, 3,
       1, 2, 4, 4, 8, 1, 1, 4, 1, 3, 7, 6, 1, 7},
      // 4: Alchemist
      {4, 5, 6, 4, 3, 3, 3, 6,  4, 2, 6, 3, 0, 4,
       1, 4, 2, 3, 3, 4, 4, 10, 6, 8, 4, 3, 5, 2},
      // 5: Wizard
      {2, 2, 2, 2, 4, 1, 4, 10, 8, 4, 4,  8, 0, 5,
       2, 6, 3, 3, 9, 1, 1, 4,  1, 1, 10, 8, 0, 7},
      // 6: Demon
      {4, 6, 10, 5, 4, 4, 3, 4, 2, 2, 7, 3, 0, 3,
       4, 2, 1,  3, 2, 6, 5, 4, 8, 7, 2, 3, 6, 2},
      // 7: Heretic
      {4, 4, 3, 3, 3, 2, 2, 8, 10, 2, 6, 4, 0, 2,
       5, 3, 2, 4, 5, 4, 4, 4, 4,  4, 6, 6, 3, 5},
      // 8: Death Knight
      {4, 5, 5, 4, 2, 8, 0, 6, 4, 1, 7, 4, 10, 0,
       1, 2, 3, 4, 2, 5, 5, 4, 7, 5, 5, 4, 5,  0},
      // 9: Necromancer
      {6, 2, 4, 2, 4, 5, 0, 8, 6, 1, 5, 7, 10, 3,
       2, 3, 3, 8, 6, 2, 3, 4, 3, 2, 6, 6, 1,  0},
      // 10: Overlord
      {5, 6, 8, 5, 3, 4,  8, 3, 3, 1, 7, 2, 0, 4,
       2, 1, 0, 3, 1, 10, 8, 4, 8, 6, 1, 2, 6, 1},
      // 11: Warlock
      {2, 2, 2, 2, 4, 4, 3, 10, 8, 2, 6, 8,  0, 5,
       5, 2, 2, 5, 8, 1, 1, 4,  1, 1, 8, 10, 0, 6},
      // 12: Barbarian
      {8, 7, 7, 8, 1, 2, 5, 2, 3,  3, 8, 2, 0, 2,
       2, 3, 0, 3, 1, 8, 8, 4, 10, 6, 1, 1, 6, 1},
      // 13: Battle Mage
      {4, 4, 9, 4, 3, 0, 4, 6, 4, 2, 6, 5, 0, 1,
       3, 3, 3, 3, 4, 5, 4, 4, 8, 4, 5, 6, 4, 4},
      // 14: Beastmaster
      {8, 7, 8, 7, 1, 8, 5, 2, 2, 2,  7, 1, 0, 1,
       0, 1, 2, 3, 1, 6, 8, 4, 5, 10, 1, 1, 5, 6},
      // 15: Witch
      {2, 3, 3, 2, 2, 6, 1, 8, 8, 4, 8, 10, 0, 1,
       3, 3, 3, 3, 7, 1, 1, 4, 2, 4, 7, 8,  0, 8},
      // 16: Elementalist
      {6, 8, 8, 6, 2, 5, 3, 2, 3, 2, 8, 2, 0, 3,
       3, 2, 2, 3, 1, 8, 8, 8, 9, 5, 1, 1, 2, 1},
      // 17: Planeswalker
      {2, 2, 2, 2, 4, 4, 3, 8, 8, 2, 4, 8, 0, 3,
       6, 6, 6, 6, 8, 1, 1, 4, 1, 1, 8, 8, 0, 4}};

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