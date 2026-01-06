#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
struct HeroCfg {

  enum class SecondarySkill : uint8_t {
    PATHFINDING = 0,
    ARCHERY = 1,
    LOGISTICS = 2,
    SCOUTING = 3,
    DIPLOMACY = 4,
    NAVIGATION = 5,
    LEADERSHIP = 6,
    WISDOM = 7,
    MYSTICISM = 8,
    LUCK = 9,
    BALLISTICS = 10,
    EAGLE_EYE = 11,
    NECROMANCY = 12,
    ESTATES = 13,
    FIRE_MAGIC = 14,
    AIR_MAGIC = 15,
    WATER_MAGIC = 16,
    EARTH_MAGIC = 17,
    SCHOLAR = 18,
    TACTICS = 19,
    ARTILLERY = 20,
    LEARNING = 21,
    OFFENCE = 22,
    ARMORER = 23,
    INTELLIGENCE = 24,
    SORCERY = 25,
    RESISTANCE = 26,
    FIRST_AID = 27
  };

  enum class SecondaryLevel : uint8_t { BASIC = 0, ADVANCED = 1, EXPERT = 2 };

  const static inline std::vector<std::vector<std::pair<uint8_t, uint8_t>>>
      heroSecSkills = {
          // 0-23: 基础英雄
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 0
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 1
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 2
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::NAVIGATION,
            (uint8_t)SecondaryLevel::BASIC}}, // 3
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ESTATES,
            (uint8_t)SecondaryLevel::BASIC}}, // 4
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 5
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 6
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 7
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRST_AID,
            (uint8_t)SecondaryLevel::BASIC}}, // 8
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::DIPLOMACY,
            (uint8_t)SecondaryLevel::BASIC}}, // 9
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ESTATES,
            (uint8_t)SecondaryLevel::BASIC}}, // 10
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 11
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 12
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 13
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 14
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 15
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 16
          {{(uint8_t)SecondarySkill::LUCK, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 17
          {{(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 18
          {{(uint8_t)SecondarySkill::DIPLOMACY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 19
          {{(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 20
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 21
          {{(uint8_t)SecondarySkill::PATHFINDING,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 22
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LOGISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 23

          // 24-31: Druid英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 24
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::ADVANCED},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 25
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 26
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRST_AID,
            (uint8_t)SecondaryLevel::BASIC}}, // 27
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 28
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LUCK,
            (uint8_t)SecondaryLevel::BASIC}}, // 29
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 30
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 31

          // 32-39: 更多Druid相关英雄
          {{(uint8_t)SecondarySkill::SCOUTING, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 32
          {{(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 33
          {{(uint8_t)SecondarySkill::MYSTICISM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 34
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 35
          {{(uint8_t)SecondarySkill::MYSTICISM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 36
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 37
          {{(uint8_t)SecondarySkill::MYSTICISM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 38
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 39

          // 40-47: Wizard英雄
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 40
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 41
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 42
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 43
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 44
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 45
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::DIPLOMACY,
            (uint8_t)SecondaryLevel::BASIC}}, // 46
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 47

          // 48-55: 更多Wizard相关英雄
          {{(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 48
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 49
          {{(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 50
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 51
          {{(uint8_t)SecondarySkill::SCHOLAR, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 52
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 53
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LOGISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 54
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 55

          // 56-63: Heretic英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 56
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 57
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 58
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 59
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 60
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 61
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 62
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 63

          // 64-71: Death Knight英雄
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 64
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 65
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 66
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 67
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 68
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 69
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 70
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 71

          // 72-79: Necromancer英雄
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 72
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::BASIC}}, // 73
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 74
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 75
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 76
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 77
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 78
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 79

          // 80-87: Overlord英雄
          {{(uint8_t)SecondarySkill::SCOUTING, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 80
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 81
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 82
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 83
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 84
          {{(uint8_t)SecondarySkill::LOGISTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 85
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 86
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 87

          // 88-95: Warlock英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCHOLAR,
            (uint8_t)SecondaryLevel::BASIC}}, // 88
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 89
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 90
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 91
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 92
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 93
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 94
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 95

          // 96-103: 更多Warlock相关英雄
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::BALLISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 96
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 97
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 98
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 99
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::PATHFINDING,
            (uint8_t)SecondaryLevel::BASIC}}, // 100
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 101
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 102
          {{(uint8_t)SecondarySkill::OFFENCE, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 103

          // 104-111: Battlemage英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 104
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 105
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LOGISTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 106
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 107
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 108
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 109
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 110
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 111

          // 112-119: Beastmaster英雄
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::RESISTANCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 112
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 113
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARCHERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 114
          {{(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 115
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 116
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::PATHFINDING,
            (uint8_t)SecondaryLevel::BASIC}}, // 117
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARTILLERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 118
          {{(uint8_t)SecondarySkill::ARMORER, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SCOUTING,
            (uint8_t)SecondaryLevel::BASIC}}, // 119

          // 120-127: Witch英雄
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 120
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::MYSTICISM,
            (uint8_t)SecondaryLevel::BASIC}}, // 121
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::NAVIGATION,
            (uint8_t)SecondaryLevel::BASIC}}, // 122
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRST_AID,
            (uint8_t)SecondaryLevel::BASIC}}, // 123
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 124
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::SORCERY,
            (uint8_t)SecondaryLevel::BASIC}}, // 125
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::INTELLIGENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 126
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EAGLE_EYE,
            (uint8_t)SecondaryLevel::BASIC}}, // 127

          // 128-135: Planeswalker英雄
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 128
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 129
          {{(uint8_t)SecondarySkill::ARTILLERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 130
          {{(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 131
          {{(uint8_t)SecondarySkill::LOGISTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 132
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 133
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 134
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEARNING,
            (uint8_t)SecondaryLevel::BASIC}}, // 135

          // 136-143: Elementalist英雄
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRE_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 136
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::AIR_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 137
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::WATER_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 138
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EARTH_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 139
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRE_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 140
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::AIR_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 141
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::WATER_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 142
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::EARTH_MAGIC,
            (uint8_t)SecondaryLevel::BASIC}}, // 143

          // 144-155: 特殊战役英雄
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 144
          {{(uint8_t)SecondarySkill::WISDOM, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::FIRE_MAGIC,
            (uint8_t)SecondaryLevel::EXPERT}}, // 145
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 146
          {{(uint8_t)SecondarySkill::WISDOM,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 147
          {{(uint8_t)SecondarySkill::ARCHERY, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC}}, // 148
          {{(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 149
          {{(uint8_t)SecondarySkill::NECROMANCY,
            (uint8_t)SecondaryLevel::ADVANCED}}, // 150
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 151
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::ARMORER,
            (uint8_t)SecondaryLevel::BASIC}}, // 152
          {{(uint8_t)SecondarySkill::ESTATES, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}}, // 153
          {{(uint8_t)SecondarySkill::TACTICS, (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::OFFENCE,
            (uint8_t)SecondaryLevel::BASIC}}, // 154
          {{(uint8_t)SecondarySkill::LEADERSHIP,
            (uint8_t)SecondaryLevel::BASIC},
           {(uint8_t)SecondarySkill::TACTICS,
            (uint8_t)SecondaryLevel::BASIC}} // 155
  };

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