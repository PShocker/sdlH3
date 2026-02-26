#pragma once
#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <array>
#include <cstdint>
#include <vector>

struct HeroClassSet {
  const static inline std::vector<HeroClasz> heroClasz = {
      // Knight (索引 0)
      {
          .id = Enum::HERO_CLASS_KNIGHT,
          .faction = Enum::FACTION_CASTLE,
          .lowPrimRate = {35, 45, 10, 10},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {2, 2, 1, 1},
          .secSkillRate = {4, 5, 5, 4, 4, 8, 10, 3, 2, 3, 8, 2, 0, 6,
                           1, 3, 4, 2, 1, 7, 5,  4, 7, 5, 1, 1, 5, 2},
          .animation = {"AH00_.def", "AH00_E.def"},
          .battle = {"CH00.DEF", "CH01.DEF"},
      },
      // Cleric (索引 1)
      {
          .id = Enum::HERO_CLASS_CLERIC,
          .faction = Enum::FACTION_CASTLE,
          .lowPrimRate = {20, 15, 30, 35},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {1, 0, 2, 2},
          .secSkillRate = {2, 3, 4, 3, 7, 5, 2, 7, 4, 5, 4, 6, 0, 3,
                           2, 4, 4, 3, 6, 2, 2, 4, 4, 3, 6, 5, 2, 10},
          .animation = {"AH01_.def", "AH01_E.def"},
          .battle = {"CH00.DEF", "CH01.DEF"},
      },
      // Ranger (索引 2)
      {
          .id = Enum::HERO_CLASS_RANGER,
          .faction = Enum::FACTION_RAMPART,
          .lowPrimRate = {35, 45, 10, 10},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {1, 3, 1, 1},
          .secSkillRate = {7, 8, 5, 7, 4, 3, 6, 3, 3, 6, 4, 2, 0, 2,
                           0, 1, 3, 3, 1, 5, 6, 4, 5, 8, 2, 2, 9, 3},
          .animation = {"AH02_.def", "AH02_E.def"},
          .battle = {"CH02.DEF", "CH03.DEF"},
      },
      // Druid (索引 3)
      {
          .id = Enum::HERO_CLASS_DRUID,
          .faction = Enum::FACTION_RAMPART,
          .lowPrimRate = {10, 20, 35, 35},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {0, 2, 1, 2},
          .secSkillRate = {5, 5, 5, 2, 4, 2, 2, 8, 6, 9, 4, 7, 0, 3,
                           1, 2, 4, 4, 8, 1, 1, 4, 1, 3, 7, 6, 1, 7},
          .animation = {"AH03_.def", "AH03_E.def"},
          .battle = {"CH02.DEF", "CH03.DEF"},
      },
      // Alchemist (索引 4)
      {
          .id = Enum::HERO_CLASS_ALCHEMIST,
          .faction = Enum::FACTION_TOWER,
          .lowPrimRate = {30, 30, 20, 20},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {1, 1, 2, 2},
          .secSkillRate = {4, 5, 6, 4, 3, 3, 3, 6,  4, 2, 6, 3, 0, 4,
                           1, 4, 2, 3, 3, 4, 4, 10, 6, 8, 4, 3, 5, 2},
          .animation = {"AH04_.def", "AH04_E.def"},
          .battle = {"CH05.DEF", "CH04.DEF"},

      },
      // Wizard (索引 5)
      {
          .id = Enum::HERO_CLASS_WIZARD,
          .faction = Enum::FACTION_TOWER,
          .lowPrimRate = {10, 10, 40, 40},
          .highPrimRate = {30, 20, 20, 30},
          .defaultPrim = {0, 0, 2, 3},
          .secSkillRate = {2, 2, 2, 2, 4, 1, 4, 10, 8, 4, 4,  8, 0, 5,
                           2, 6, 3, 3, 9, 1, 1, 4,  1, 1, 10, 8, 0, 7},
          .animation = {"AH05_.def", "AH05_E.def"},
          .battle = {"CH05.DEF", "CH04.DEF"},
      },
      // Demon (索引 6)
      {
          .id = Enum::HERO_CLASS_DEMON,
          .faction = Enum::FACTION_INFERNO,
          .lowPrimRate = {35, 35, 15, 15},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {2, 2, 1, 1},
          .secSkillRate = {4, 6, 10, 5, 4, 4, 3, 4, 2, 2, 7, 3, 0, 3,
                           4, 2, 1,  3, 2, 6, 5, 4, 8, 7, 2, 3, 6, 2},
          .animation = {"AH06_.def", "AH06_E.def"},
          .battle = {"CH06.DEF", "CH07.DEF"},

      },
      // Heretic (索引 7)
      {
          .id = Enum::HERO_CLASS_HERETIC,
          .faction = Enum::FACTION_INFERNO,
          .lowPrimRate = {15, 15, 35, 35},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {1, 1, 2, 1},
          .secSkillRate = {4, 4, 3, 3, 3, 2, 2, 8, 10, 2, 6, 4, 0, 2,
                           5, 3, 2, 4, 5, 4, 4, 4, 4,  4, 6, 6, 3, 5},
          .animation = {"AH07_.def", "AH07_E.def"},
          .battle = {"CH06.DEF", "CH07.DEF"},

      },
      // Death Knight (索引 8)
      {
          .id = Enum::HERO_CLASS_DEATH_KNIGHT,
          .faction = Enum::FACTION_NECROPOLIS,
          .lowPrimRate = {30, 25, 20, 25},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {1, 2, 2, 1},
          .secSkillRate = {4, 5, 5, 4, 2, 8, 0, 6, 4, 1, 7, 4, 10, 0,
                           1, 2, 3, 4, 2, 5, 5, 4, 7, 5, 5, 4, 5,  0},
          .animation = {"AH08_.def", "AH08_E.def"},
          .battle = {"CH08.DEF", "CH09.DEF"},

      },
      // Necromancer (索引 9)
      {
          .id = Enum::HERO_CLASS_NECROMANCER,
          .faction = Enum::FACTION_NECROPOLIS,
          .lowPrimRate = {15, 15, 35, 35},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {1, 0, 2, 2},
          .secSkillRate = {6, 2, 4, 2, 4, 5, 0, 8, 6, 1, 5, 7, 10, 3,
                           2, 3, 3, 8, 6, 2, 3, 4, 3, 2, 6, 6, 1,  0},
          .animation = {"AH09_.def", "AH09_E.def"},
          .battle = {"CH08.DEF", "CH09.DEF"},
      },
      // Overlord (索引 10)
      {
          .id = Enum::HERO_CLASS_OVERLORD,
          .faction = Enum::FACTION_DUNGEON,
          .lowPrimRate = {35, 35, 15, 15},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {2, 2, 1, 1},
          .secSkillRate = {5, 6, 8, 5, 3, 4,  8, 3, 3, 1, 7, 2, 0, 4,
                           2, 1, 0, 3, 1, 10, 8, 4, 8, 6, 1, 2, 6, 1},
          .animation = {"AH10_.def", "AH10_E.def"},
          .battle = {"CH10.DEF", "CH11.DEF"},
      },
      // Warlock (索引 11)
      {
          .id = Enum::HERO_CLASS_WARLOCK,
          .faction = Enum::FACTION_DUNGEON,
          .lowPrimRate = {10, 10, 50, 30},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {0, 0, 3, 2},
          .secSkillRate = {2, 2, 2, 2, 4, 4, 3, 10, 8, 2, 6, 8,  0, 5,
                           5, 2, 2, 5, 8, 1, 1, 4,  1, 1, 8, 10, 0, 6},
          .animation = {"AH11_.def", "AH11_E.def"},
          .battle = {"CH10.DEF", "CH11.DEF"},

      },
      // Barbarian (索引 12)
      {
          .id = Enum::HERO_CLASS_BARBARIAN,
          .faction = Enum::FACTION_STRONGHOLD,
          .lowPrimRate = {55, 35, 5, 5},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {4, 0, 1, 1},
          .secSkillRate = {8, 7, 7, 8, 1, 2, 5, 2, 3,  3, 8, 2, 0, 2,
                           2, 3, 0, 3, 1, 8, 8, 4, 10, 6, 1, 1, 6, 1},
          .animation = {"AH12_.def", "AH12_E.def"},
          .battle = {"CH13.DEF", "CH12.DEF"},

      },
      // Battle Mage (索引 13)
      {
          .id = Enum::HERO_CLASS_BATTLE_MAGE,
          .faction = Enum::FACTION_STRONGHOLD,
          .lowPrimRate = {30, 20, 25, 25},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {2, 1, 1, 1},
          .secSkillRate = {4, 4, 9, 4, 3, 0, 4, 6, 4, 2, 6, 5, 0, 1,
                           3, 3, 3, 3, 4, 5, 4, 4, 8, 4, 5, 6, 4, 4},
          .animation = {"AH13_.def", "AH13_E.def"},
          .battle = {"CH13.DEF", "CH12.DEF"},

      },
      // Beastmaster (索引 14)
      {
          .id = Enum::HERO_CLASS_BEASTMASTER,
          .faction = Enum::FACTION_FORTRESS,

          .lowPrimRate = {30, 50, 10, 10},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {0, 4, 1, 1},
          .secSkillRate = {8, 7, 8, 7, 1, 8, 5, 2, 2, 2,  7, 1, 0, 1,
                           0, 1, 2, 3, 1, 6, 8, 4, 5, 10, 1, 1, 5, 6},
          .animation = {"AH14_.def", "AH14_E.def"},
          .battle = {"CH14.DEF", "CH15.DEF"},

      },
      // Witch (索引 15)
      {
          .id = Enum::HERO_CLASS_WITCH,
          .faction = Enum::FACTION_FORTRESS,

          .lowPrimRate = {5, 15, 40, 40},
          .highPrimRate = {20, 20, 30, 30},
          .defaultPrim = {0, 1, 2, 2},
          .secSkillRate = {2, 3, 3, 2, 2, 6, 1, 8, 8, 4, 8, 10, 0, 1,
                           3, 3, 3, 3, 7, 1, 1, 4, 2, 4, 7, 8,  0, 8},
          .animation = {"AH15_.def", "AH15_E.def"},
          .battle = {"CH14.DEF", "CH15.DEF"},

      },
      // Elementalist (索引 16)
      {
          .id = Enum::HERO_CLASS_ELEMENTALIST,
          .faction = Enum::FACTION_CONFLUX,

          .lowPrimRate = {45, 25, 15, 15},
          .highPrimRate = {30, 30, 20, 20},
          .defaultPrim = {3, 1, 1, 1},
          .secSkillRate = {6, 8, 8, 6, 2, 5, 3, 2, 3, 2, 8, 2, 0, 3,
                           3, 2, 2, 3, 1, 8, 8, 8, 9, 5, 1, 1, 2, 1},
          .animation = {"AH16_.def", "AH16_E.def"},
          .battle = {"CH16.DEF", "CH16.DEF"},

      },
      // Planeswalker (索引 17)
      {
          .id = Enum::HERO_CLASS_PLANESWALKER,
          .faction = Enum::FACTION_CONFLUX,
          .lowPrimRate = {15, 15, 35, 35},
          .highPrimRate = {25, 25, 25, 25},
          .defaultPrim = {0, 0, 3, 3},
          .secSkillRate = {2, 2, 2, 2, 4, 4, 3, 8, 8, 2, 4, 8, 0, 3,
                           6, 6, 6, 6, 8, 1, 1, 4, 1, 1, 8, 8, 0, 4},
          .animation = {"AH17_.def", "AH17_E.def"},
          .battle = {"CH17.DEF", "CH17.DEF"},

      },
  };
};