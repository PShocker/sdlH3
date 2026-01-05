#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
struct HeroCfg {
  const static inline std::vector<
      std::vector<std::pair<std::string, std::string>>>
      heroSecSkills = {
          // 0-23: 基础英雄
          {{"leadership", "basic"}, {"archery", "basic"}},     // 0
          {{"leadership", "basic"}, {"archery", "basic"}},     // 1
          {{"leadership", "basic"}, {"armorer", "basic"}},     // 2
          {{"leadership", "basic"}, {"navigation", "basic"}},  // 3
          {{"leadership", "basic"}, {"estates", "basic"}},     // 4
          {{"leadership", "basic"}, {"offence", "basic"}},     // 5
          {{"leadership", "basic"}, {"artillery", "basic"}},   // 6
          {{"leadership", "basic"}, {"tactics", "basic"}},     // 7
          {{"wisdom", "basic"}, {"firstAid", "basic"}},        // 8
          {{"wisdom", "basic"}, {"diplomacy", "basic"}},       // 9
          {{"wisdom", "basic"}, {"estates", "basic"}},         // 10
          {{"wisdom", "advanced"}},                            // 11
          {{"wisdom", "basic"}, {"mysticism", "basic"}},       // 12
          {{"wisdom", "basic"}, {"eagleEye", "basic"}},        // 13
          {{"wisdom", "basic"}, {"learning", "basic"}},        // 14
          {{"wisdom", "basic"}, {"intelligence", "basic"}},    // 15
          {{"leadership", "basic"}, {"armorer", "basic"}},     // 16
          {{"luck", "basic"}, {"resistance", "basic"}},        // 17
          {{"archery", "advanced"}},                           // 18
          {{"diplomacy", "basic"}, {"leadership", "basic"}},   // 19
          {{"resistance", "advanced"}},                        // 20
          {{"archery", "basic"}, {"offence", "basic"}},        // 21
          {{"pathfinding", "basic"}, {"resistance", "basic"}}, // 22
          {{"archery", "basic"}, {"logistics", "basic"}},      // 23

          // 24-31: Druid英雄
          {{"wisdom", "basic"}, {"scholar", "basic"}},       // 24
          {{"wisdom", "advanced"}, {"ballistics", "basic"}}, // 25
          {{"wisdom", "basic"}, {"intelligence", "basic"}},  // 26
          {{"wisdom", "basic"}, {"firstAid", "basic"}},      // 27
          {{"wisdom", "basic"}, {"eagleEye", "basic"}},      // 28
          {{"wisdom", "basic"}, {"luck", "basic"}},          // 29
          {{"wisdom", "basic"}, {"sorcery", "basic"}},       // 30
          {{"wisdom", "basic"}, {"scouting", "basic"}},      // 31

          // 32-39: 更多Druid相关英雄
          {{"scouting", "basic"}, {"mysticism", "basic"}},   // 32
          {{"scholar", "advanced"}},                         // 33
          {{"mysticism", "basic"}, {"sorcery", "basic"}},    // 34
          {{"scholar", "basic"}, {"armorer", "basic"}},      // 35
          {{"mysticism", "basic"}, {"tactics", "basic"}},    // 36
          {{"scholar", "basic"}, {"resistance", "basic"}},   // 37
          {{"mysticism", "basic"}, {"offence", "basic"}},    // 38
          {{"scholar", "basic"}, {"intelligence", "basic"}}, // 39

          // 40-47: Wizard英雄
          {{"wisdom", "advanced"}},                         // 40
          {{"wisdom", "basic"}, {"mysticism", "basic"}},    // 41
          {{"wisdom", "basic"}, {"eagleEye", "basic"}},     // 42
          {{"wisdom", "basic"}, {"intelligence", "basic"}}, // 43
          {{"wisdom", "basic"}, {"ballistics", "basic"}},   // 44
          {{"wisdom", "basic"}, {"sorcery", "basic"}},      // 45
          {{"wisdom", "basic"}, {"diplomacy", "basic"}},    // 46
          {{"wisdom", "basic"}, {"scholar", "basic"}},      // 47

          // 48-55: 更多Wizard相关英雄
          {{"scouting", "advanced"}},                       // 48
          {{"wisdom", "basic"}, {"scholar", "basic"}},      // 49
          {{"armorer", "advanced"}},                        // 50
          {{"tactics", "basic"}, {"resistance", "basic"}},  // 51
          {{"scholar", "basic"}, {"offence", "basic"}},     // 52
          {{"archery", "basic"}, {"scouting", "basic"}},    // 53
          {{"artillery", "basic"}, {"logistics", "basic"}}, // 54
          {{"offence", "advanced"}},                        // 55

          // 56-63: Heretic英雄
          {{"wisdom", "basic"}, {"intelligence", "basic"}}, // 56
          {{"wisdom", "basic"}, {"scholar", "basic"}},      // 57
          {{"wisdom", "basic"}, {"mysticism", "basic"}},    // 58
          {{"wisdom", "basic"}, {"ballistics", "basic"}},   // 59
          {{"wisdom", "basic"}, {"learning", "basic"}},     // 60
          {{"wisdom", "basic"}, {"eagleEye", "basic"}},     // 61
          {{"wisdom", "basic"}, {"sorcery", "basic"}},      // 62
          {{"wisdom", "basic"}, {"leadership", "basic"}},   // 63

          // 64-71: Death Knight英雄
          {{"necromancy", "basic"}, {"resistance", "basic"}}, // 64
          {{"necromancy", "basic"}, {"artillery", "basic"}},  // 65
          {{"necromancy", "basic"}, {"learning", "basic"}},   // 66
          {{"necromancy", "basic"}, {"tactics", "basic"}},    // 67
          {{"necromancy", "basic"}, {"offence", "basic"}},    // 68
          {{"necromancy", "advanced"}},                       // 69
          {{"necromancy", "basic"}, {"offence", "basic"}},    // 70
          {{"necromancy", "basic"}, {"armorer", "basic"}},    // 71

          // 72-79: Necromancer英雄
          {{"necromancy", "basic"}, {"scholar", "basic"}},      // 72
          {{"necromancy", "basic"}, {"wisdom", "basic"}},       // 73
          {{"necromancy", "basic"}, {"sorcery", "basic"}},      // 74
          {{"necromancy", "basic"}, {"eagleEye", "basic"}},     // 75
          {{"necromancy", "basic"}, {"mysticism", "basic"}},    // 76
          {{"necromancy", "basic"}, {"learning", "basic"}},     // 77
          {{"necromancy", "advanced"}},                         // 78
          {{"necromancy", "basic"}, {"intelligence", "basic"}}, // 79

          // 80-87: Overlord英雄
          {{"scouting", "basic"}, {"leadership", "basic"}},   // 80
          {{"artillery", "basic"}, {"offence", "basic"}},     // 81
          {{"tactics", "basic"}, {"offence", "basic"}},       // 82
          {{"leadership", "basic"}, {"resistance", "basic"}}, // 83
          {{"offence", "advanced"}},                          // 84
          {{"logistics", "basic"}, {"tactics", "basic"}},     // 85
          {{"leadership", "basic"}, {"scholar", "basic"}},    // 86
          {{"tactics", "basic"}, {"offence", "basic"}},       // 87

          // 88-95: Warlock英雄
          {{"wisdom", "basic"}, {"scholar", "basic"}},      // 88
          {{"wisdom", "basic"}, {"mysticism", "basic"}},    // 89
          {{"wisdom", "basic"}, {"sorcery", "basic"}},      // 90
          {{"wisdom", "advanced"}},                         // 91
          {{"wisdom", "basic"}, {"eagleEye", "basic"}},     // 92
          {{"wisdom", "basic"}, {"scouting", "advanced"}},  // 93
          {{"wisdom", "basic"}, {"intelligence", "basic"}}, // 94
          {{"wisdom", "basic"}, {"learning", "basic"}},     // 95

          // 96-103: 更多Warlock相关英雄
          {{"offence", "basic"}, {"ballistics", "basic"}},  // 96
          {{"offence", "basic"}, {"artillery", "basic"}},   // 97
          {{"offence", "basic"}, {"archery", "basic"}},     // 98
          {{"offence", "basic"}, {"scouting", "basic"}},    // 99
          {{"offence", "basic"}, {"pathfinding", "basic"}}, // 100
          {{"offence", "basic"}, {"resistance", "basic"}},  // 101
          {{"offence", "advanced"}},                        // 102
          {{"offence", "basic"}, {"tactics", "basic"}},     // 103

          // 104-111: Battlemage英雄
          {{"wisdom", "basic"}, {"sorcery", "basic"}},    // 104
          {{"wisdom", "basic"}, {"leadership", "basic"}}, // 105
          {{"wisdom", "basic"}, {"logistics", "basic"}},  // 106
          {{"wisdom", "basic"}, {"tactics", "basic"}},    // 107
          {{"wisdom", "basic"}, {"artillery", "basic"}},  // 108
          {{"wisdom", "basic"}, {"offence", "basic"}},    // 109
          {{"wisdom", "basic"}, {"eagleEye", "basic"}},   // 110
          {{"wisdom", "basic"}, {"resistance", "basic"}}, // 111

          // 112-119: Beastmaster英雄
          {{"armorer", "basic"}, {"resistance", "basic"}},  // 112
          {{"armorer", "basic"}, {"leadership", "basic"}},  // 113
          {{"armorer", "basic"}, {"archery", "basic"}},     // 114
          {{"armorer", "advanced"}},                        // 115
          {{"armorer", "basic"}, {"offence", "basic"}},     // 116
          {{"armorer", "basic"}, {"pathfinding", "basic"}}, // 117
          {{"armorer", "basic"}, {"artillery", "basic"}},   // 118
          {{"armorer", "basic"}, {"scouting", "basic"}},    // 119

          // 120-127: Witch英雄
          {{"wisdom", "advanced"}},                         // 120
          {{"wisdom", "basic"}, {"mysticism", "basic"}},    // 121
          {{"wisdom", "basic"}, {"navigation", "basic"}},   // 122
          {{"wisdom", "basic"}, {"firstAid", "basic"}},     // 123
          {{"wisdom", "basic"}, {"learning", "basic"}},     // 124
          {{"wisdom", "basic"}, {"sorcery", "basic"}},      // 125
          {{"wisdom", "basic"}, {"intelligence", "basic"}}, // 126
          {{"wisdom", "basic"}, {"eagleEye", "basic"}},     // 127

          // 128-135: Planeswalker英雄
          {{"artillery", "basic"}, {"offence", "basic"}}, // 128
          {{"estates", "basic"}, {"tactics", "basic"}},   // 129
          {{"artillery", "basic"}, {"offence", "basic"}}, // 130
          {{"tactics", "advanced"}},                      // 131
          {{"logistics", "basic"}, {"offence", "basic"}}, // 132
          {{"estates", "basic"}, {"tactics", "basic"}},   // 133
          {{"offence", "advanced"}},                      // 134
          {{"tactics", "basic"}, {"learning", "basic"}},  // 135

          // 136-143: Elementalist英雄
          {{"wisdom", "basic"}, {"fireMagic", "basic"}},  // 136
          {{"wisdom", "basic"}, {"airMagic", "basic"}},   // 137
          {{"wisdom", "basic"}, {"waterMagic", "basic"}}, // 138
          {{"wisdom", "basic"}, {"earthMagic", "basic"}}, // 139
          {{"wisdom", "basic"}, {"fireMagic", "basic"}},  // 140
          {{"wisdom", "basic"}, {"airMagic", "basic"}},   // 141
          {{"wisdom", "basic"}, {"waterMagic", "basic"}}, // 142
          {{"wisdom", "basic"}, {"earthMagic", "basic"}}, // 143

          // 144-155: 特殊战役英雄
          {{"leadership", "advanced"}},                    // 144
          {{"wisdom", "basic"}, {"fireMagic", "expert"}},  // 145
          {{"leadership", "basic"}, {"offence", "basic"}}, // 146
          {{"wisdom", "advanced"}},                        // 147
          {{"archery", "basic"}, {"leadership", "basic"}}, // 148
          {{"offence", "advanced"}},                       // 149
          {{"necromancy", "advanced"}},                    // 150
          {{"estates", "basic"}, {"tactics", "basic"}},    // 151
          {{"leadership", "basic"}, {"armorer", "basic"}}, // 152
          {{"estates", "basic"}, {"tactics", "basic"}},    // 153
          {{"tactics", "basic"}, {"offence", "basic"}},    // 154
          {{"leadership", "basic"}, {"tactics", "basic"}}  // 155
  };

  const static inline std::unordered_map<std::string, uint8_t>
      heroSecSkillsNameIndex = {
          {"pathfinding", 0},   {"archery", 1},     {"logistics", 2},
          {"scouting", 3},      {"diplomacy", 4},   {"navigation", 5},
          {"leadership", 6},    {"wisdom", 7},      {"mysticism", 8},
          {"luck", 9},          {"ballistics", 10}, {"eagleEye", 11},
          {"necromancy", 12},   {"estates", 13},    {"fireMagic", 14},
          {"airMagic", 15},     {"waterMagic", 16}, {"earthMagic", 17},
          {"scholar", 18},      {"tactics", 19},    {"artillery", 20},
          {"learning", 21},     {"offence", 22},    {"armorer", 23},
          {"intelligence", 24}, {"sorcery", 25},    {"resistance", 26},
          {"firstAid", 27}};

  const static inline std::unordered_map<std::string, uint8_t>
      heroSecSkillsLevelIndex = {
          {"basic", 0},
          {"advanced", 1},
          {"expert", 2},
  };

  const static inline std::string SecSkillNames[] = {
      "pathfinding", "archery",      "logistics",
      "scouting",    "diplomacy", //  5
      "navigation",  "leadership",   "wisdom",
      "mysticism",   "luck", // 10
      "ballistics",  "eagleEye",     "necromancy",
      "estates",     "fireMagic", // 15
      "airMagic",    "waterMagic",   "earthMagic",
      "scholar",     "tactics", // 20
      "artillery",   "learning",     "offence",
      "armorer",     "intelligence", // 25
      "sorcery",     "resistance",   "firstAid"};

  const static inline std::string SecSkilLvl[] = {"basic", "advanced",
                                                  "expert"};

  // HCTRAITS.TXT
  const static inline std::vector<std::array<uint8_t, 4>> heroPrimarySkills = {
      {2, 2, 1, 1}, // 索引 0: Knight
      {1, 0, 2, 2}, // 索引 1: Cleric
      {1, 3, 1, 1}, // 索引 2: Ranger
      {0, 2, 1, 2}, // 索引 3: Druid
      {1, 1, 2, 2}, // 索引 4: Alchemist
      {0, 0, 2, 3}, // 索引 5: Wizard
      {2, 2, 1, 1}, // 索引 6: Demon
      {1, 1, 2, 1}, // 索引 7: Heretic
      {1, 2, 2, 1}, // 索引 8: Death Knight
      {1, 0, 2, 2}, // 索引 9: Necromancer
      {2, 2, 1, 1}, // 索引 10: Overlord
      {0, 0, 3, 2}, // 索引 11: Warlock
      {4, 0, 1, 1}, // 索引 12: Barbarian
      {2, 1, 1, 1}, // 索引 13: Battle Mage
      {0, 4, 1, 1}, // 索引 14: Beastmaster
      {0, 1, 2, 2}, // 索引 15: Witch
      {3, 1, 1, 1}, // 索引 16: Elementalist
      {0, 0, 3, 3}  // 索引 17: Planeswalker
  };

  const static inline std::vector<std::vector<uint8_t>> heroLowLevelChance = {
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

  const static inline std::vector<std::vector<uint8_t>> heroHighLevelChance = {
      {30, 30, 20, 20}, // 索引 0: Knight
      {20, 20, 30, 30}, // 索引 1: Cleric
      {30, 30, 20, 20}, // 索引 2: Ranger
      {20, 20, 30, 30}, // 索引 3: Druid
      {30, 30, 20, 20}, // 索引 4: Alchemist
      {30, 20, 20, 30}, // 索引 5: Wizard
      {30, 30, 20, 20}, // 索引 6: Demon
      {20, 20, 30, 30}, // 索引 7: Heretic
      {25, 25, 25, 25}, // 索引 8: Death Knight
      {25, 25, 25, 25}, // 索引 9: Necromancer
      {30, 30, 20, 20}, // 索引 10: Overlord
      {20, 20, 30, 30}, // 索引 11: Warlock
      {30, 30, 20, 20}, // 索引 12: Barbarian
      {25, 25, 25, 25}, // 索引 13: Battle Mage
      {30, 30, 20, 20}, // 索引 14: Beastmaster
      {20, 20, 30, 30}, // 索引 15: Witch
      {30, 30, 20, 20}, // 索引 16: Elementalist
      {25, 25, 25, 25}  // 索引 17: Planeswalker
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

  const static inline uint64_t heroLevelExp[] = {
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
  const static inline std::string heroSmallPor[] = {
      // Knight (KN)
      "HPS000KN.pcx", "HPS001KN.pcx", "HPS002KN.pcx", "HPS003KN.pcx",
      "HPS004KN.pcx", "HPS005KN.pcx", "HPS006KN.pcx", "HPS007KN.pcx",

      // Cleric (CL)
      "HPS008CL.pcx", "HPS009CL.pcx", "HPS010CL.pcx", "HPS011CL.pcx",
      "HPS012CL.pcx", "HPS013CL.pcx", "HPS014CL.pcx", "HPS015CL.pcx",

      // Ranger (RN)
      "HPS016RN.pcx", "HPS017RN.pcx", "HPS018RN.pcx", "HPS019RN.pcx",
      "HPS020RN.pcx", "HPS021RN.pcx", "HPS022RN.pcx", "HPS023RN.pcx",

      // Druid (DR)
      "HPS024DR.pcx", "HPS025DR.pcx", "HPS026DR.pcx", "HPS027DR.pcx",
      "HPS028DR.pcx", "HPS029DR.pcx", "HPS030DR.pcx", "HPS031DR.pcx",

      // Alchemist (AL)
      "HPS032AL.pcx", "HPS033AL.pcx", "HPS034AL.pcx", "HPS035AL.pcx",
      "HPS036AL.pcx", "HPS037AL.pcx", "HPS038AL.pcx", "HPS039AL.pcx",

      // Wizard (WZ)
      "HPS040WZ.pcx", "HPS041WZ.pcx", "HPS042WZ.pcx", "HPS043WZ.pcx",
      "HPS044WZ.pcx", "HPS045WZ.pcx", "HPS046WZ.pcx", "HPS047WZ.pcx",

      // Knight (HR)
      "HPS048HR.pcx", "HPS049HR.pcx", "HPS050HR.pcx", "HPS051HR.pcx",
      "HPS052HR.pcx", "HPS053HR.pcx", "HPS054HR.pcx", "HPS055HR.pcx",

      // Demon Lord (DM)
      "HPS056DM.pcx", "HPS057DM.pcx", "HPS058DM.pcx", "HPS059DM.pcx",
      "HPS060DM.pcx", "HPS061DM.pcx", "HPS062DM.pcx", "HPS063DM.pcx",

      // Death Knight (DK)
      "HPS064DK.pcx", "HPS065DK.pcx", "HPS066DK.pcx", "HPS067DK.pcx",
      "HPS068DK.pcx", "HPS069DK.pcx", "HPS070DK.pcx", "HPS071DK.pcx",

      // Necromancer (NC)
      "HPS072NC.pcx", "HPS073NC.pcx", "HPS074NC.pcx", "HPS075NC.pcx",
      "HPS076NC.pcx", "HPS077NC.pcx", "HPS078NC.pcx", "HPS079NC.pcx",

      // Overlord (OV)
      "HPS080OV.pcx", "HPS081OV.pcx", "HPS082OV.pcx", "HPS083OV.pcx",
      "HPS084OV.pcx", "HPS085OV.pcx", "HPS086OV.pcx", "HPS087OV.pcx",

      // Warlock (WL)
      "HPS088WL.pcx", "HPS089WL.pcx", "HPS090WL.pcx", "HPS091WL.pcx",
      "HPS092WL.pcx", "HPS093WL.pcx", "HPS094WL.pcx", "HPS095WL.pcx",

      // Barbarian (BR)
      "HPS096BR.pcx", "HPS097BR.pcx", "HPS098BR.pcx", "HPS099BR.pcx",
      "HPS100BR.pcx", "HPS101BR.pcx", "HPS102BR.pcx", "HPS103BR.pcx",

      // Battle Mage (BM)
      "HPS104BM.pcx", "HPS105BM.pcx", "HPS106BM.pcx", "HPS107BM.pcx",
      "HPS108BM.pcx", "HPS109BM.pcx", "HPS110BM.pcx", "HPS111BM.pcx",

      // Beastmaster (BS)
      "HPS112BS.pcx", "HPS113BS.pcx", "HPS114BS.pcx", "HPS115BS.pcx",
      "HPS116BS.pcx", "HPS117BS.pcx", "HPS118BS.pcx", "HPS119BS.pcx",

      // Witch (WH)
      "HPS120WH.pcx", "HPS121WH.pcx", "HPS122WH.pcx", "HPS123WH.pcx",
      "HPS124WH.pcx", "HPS125WH.pcx", "HPS126WH.pcx", "HPS127WH.pcx",

      // Planeswalker (PL)
      "HPS000PL.pcx", "HPS001PL.pcx", "HPS002PL.pcx", "HPS003PL.pcx",
      "HPS004PL.pcx", "HPS005PL.pcx", "HPS006PL.pcx", "HPS007PL.pcx",

      // Elementalist (EL)
      "HPS000EL.pcx", "HPS001EL.pcx", "HPS002EL.pcx", "HPS003EL.pcx",
      "HPS004EL.pcx", "HPS005EL.pcx", "HPS006EL.pcx", "HPS007EL.pcx",

      // 特殊英雄
      "HPS130KN.pcx", "HPS000SH.pcx", "HPS128QC.pcx", "HPS003SH.pcx",
      "HPS004SH.pcx", "HPS005SH.pcx", "HPS006SH.pcx", "HPS007SH.pcx",
      "HPS009SH.pcx", "HPS008SH.pcx", "HPS001SH.pcx", "HPS131DM.pcx",

      // 随机英雄
      "HPSRAND1.pcx", "HPSRAND6.pcx", "HPSXXX.pcx", "HPSYYY.pcx"};

  const static inline std::string heroLargePor[] = {
      // Knight (KN)
      "HPL000KN.pcx", "HPL001KN.pcx", "HPL002KN.pcx", "HPL003KN.pcx",
      "HPL004KN.pcx", "HPL005KN.pcx", "HPL006KN.pcx", "HPL007KN.pcx",

      // Cleric (CL)
      "HPL008CL.pcx", "HPL009CL.pcx", "HPL010CL.pcx", "HPL011CL.pcx",
      "HPL012CL.pcx", "HPL013CL.pcx", "HPL014CL.pcx", "HPL015CL.pcx",

      // Ranger (RN)
      "HPL016RN.pcx", "HPL017RN.pcx", "HPL018RN.pcx", "HPL019RN.pcx",
      "HPL020RN.pcx", "HPL021RN.pcx", "HPL022RN.pcx", "HPL023RN.pcx",

      // Druid (DR)
      "HPL024DR.pcx", "HPL025DR.pcx", "HPL026DR.pcx", "HPL027DR.pcx",
      "HPL028DR.pcx", "HPL029DR.pcx", "HPL030DR.pcx", "HPL031DR.pcx",

      // Alchemist (AL)
      "HPL032AL.pcx", "HPL033AL.pcx", "HPL034AL.pcx", "HPL035AL.pcx",
      "HPL036AL.pcx", "HPL037AL.pcx", "HPL038AL.pcx", "HPL039AL.pcx",

      // Wizard (WZ)
      "HPL040WZ.pcx", "HPL041WZ.pcx", "HPL042WZ.pcx", "HPL043WZ.pcx",
      "HPL044WZ.pcx", "HPL045WZ.pcx", "HPL046WZ.pcx", "HPL047WZ.pcx",

      // Knight (HR)
      "HPL048HR.pcx", "HPL049HR.pcx", "HPL050HR.pcx", "HPL051HR.pcx",
      "HPL052HR.pcx", "HPL053HR.pcx", "HPL054HR.pcx", "HPL055HR.pcx",

      // Demon Lord (DM)
      "HPL056DM.pcx", "HPL057DM.pcx", "HPL058DM.pcx", "HPL059DM.pcx",
      "HPL060DM.pcx", "HPL061DM.pcx", "HPL062DM.pcx", "HPL063DM.pcx",

      // Death Knight (DK)
      "HPL064DK.pcx", "HPL065DK.pcx", "HPL066DK.pcx", "HPL067DK.pcx",
      "HPL068DK.pcx", "HPL069DK.pcx", "HPL070DK.pcx", "HPL071DK.pcx",

      // Necromancer (NC)
      "HPL072NC.pcx", "HPL073NC.pcx", "HPL074NC.pcx", "HPL075NC.pcx",
      "HPL076NC.pcx", "HPL077NC.pcx", "HPL078NC.pcx", "HPL079NC.pcx",

      // Overlord (OV)
      "HPL080OV.pcx", "HPL081OV.pcx", "HPL082OV.pcx", "HPL083OV.pcx",
      "HPL084OV.pcx", "HPL085OV.pcx", "HPL086OV.pcx", "HPL087OV.pcx",

      // Warlock (WL)
      "HPL088WL.pcx", "HPL089WL.pcx", "HPL090WL.pcx", "HPL091WL.pcx",
      "HPL092WL.pcx", "HPL093WL.pcx", "HPL094WL.pcx", "HPL095WL.pcx",

      // Barbarian (BR)
      "HPL096BR.pcx", "HPL097BR.pcx", "HPL098BR.pcx", "HPL099BR.pcx",
      "HPL100BR.pcx", "HPL101BR.pcx", "HPL102BR.pcx", "HPL103BR.pcx",

      // Battle Mage (BM)
      "HPL104BM.pcx", "HPL105BM.pcx", "HPL106BM.pcx", "HPL107BM.pcx",
      "HPL108BM.pcx", "HPL109BM.pcx", "HPL110BM.pcx", "HPL111BM.pcx",

      // Beastmaster (BS)
      "HPL112BS.pcx", "HPL113BS.pcx", "HPL114BS.pcx", "HPL115BS.pcx",
      "HPL116BS.pcx", "HPL117BS.pcx", "HPL118BS.pcx", "HPL119BS.pcx",

      // Witch (WH)
      "HPL120WH.pcx", "HPL121WH.pcx", "HPL122WH.pcx", "HPL123WH.pcx",
      "HPL124WH.pcx", "HPL125WH.pcx", "HPL126WH.pcx", "HPL127WH.pcx",

      // Planeswalker (PL)
      "HPL000PL.pcx", "HPL001PL.pcx", "HPL002PL.pcx", "HPL003PL.pcx",
      "HPL004PL.pcx", "HPL005PL.pcx", "HPL006PL.pcx", "HPL007PL.pcx",

      // Elementalist (EL)
      "HPL000EL.pcx", "HPL001EL.pcx", "HPL002EL.pcx", "HPL003EL.pcx",
      "HPL004EL.pcx", "HPL005EL.pcx", "HPL006EL.pcx", "HPL007EL.pcx",

      // 特殊英雄
      "HPL130KN.pcx", "HPL000SH.pcx", "HPL128QC.pcx", "HPL003SH.pcx",
      "HPL004SH.pcx", "HPL005SH.pcx", "HPL006SH.pcx", "HPL007SH.pcx",
      "HPL009SH.pcx", "HPL008SH.pcx", "HPL001SH.pcx", "HPL131DM.pcx"};
};