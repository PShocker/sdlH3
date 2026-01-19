#pragma once

#include <cstdint>
struct Enum {
  enum class GAMESET : uint8_t {
    MY_HERO_SPEED,
    OTHER_HERO_SPEED,
    MAP_SPEED,
    ANIMATE_EFFECT,
    MUSIC1,
    MUSIC2,
    HERO_TIP,
    QUICK_BATTLE,
    ANIMATE_TEXT,
    BUILD_FADE,
    MAP_MSG,
    BACK_MUSIC,
  };

  enum class MARKET : uint8_t {
    RES_BUY,
    RES_SEND,
    ART_BUY,
    ART_SELL,
    CRE_SELL,
  };

  enum class ALTAR : uint8_t {
    ART,
    CRE,
    SKE, // 骷髅转换场
  };

  enum class CURSOR : uint8_t {
    ADVENTURE, // set of various cursors for adventure map
    COMBAT,    // set of various cursors for combat
    DEFAULT,   // default arrow and hourglass cursors
    SPELL,     // animated cursor for spellcasting
    FADE,      // animated cursor for spellcasting
    HIDE       // hide
  };
  enum class CRADVNTR : uint8_t {
    POINTER = 0,
    HOURGLASS = 1,
    HERO = 2,
    TOWN = 3,
    T1_MOVE = 4,
    T1_ATTACK = 5,
    T1_SAIL = 6,
    T1_DISEMBARK = 7,
    T1_EXCHANGE = 8,
    T1_VISIT = 9,
    T2_MOVE = 10,
    T2_ATTACK = 11,
    T2_SAIL = 12,
    T2_DISEMBARK = 13,
    T2_EXCHANGE = 14,
    T2_VISIT = 15,
    T3_MOVE = 16,
    T3_ATTACK = 17,
    T3_SAIL = 18,
    T3_DISEMBARK = 19,
    T3_EXCHANGE = 20,
    T3_VISIT = 21,
    T4_MOVE = 22,
    T4_ATTACK = 23,
    T4_SAIL = 24,
    T4_DISEMBARK = 25,
    T4_EXCHANGE = 26,
    T4_VISIT = 27,
    T1_SAIL_VISIT = 28,
    T2_SAIL_VISIT = 29,
    T3_SAIL_VISIT = 30,
    T4_SAIL_VISIT = 31,
    SCROLL_NORTH = 32,
    SCROLL_NORTHEAST = 33,
    SCROLL_EAST = 34,
    SCROLL_SOUTHEAST = 35,
    SCROLL_SOUTH = 36,
    SCROLL_SOUTHWEST = 37,
    SCROLL_WEST = 38,
    SCROLL_NORTHWEST = 39,
    // POINTER_COPY       = 40, // probably unused
    TELEPORT = 41,
    SCUTTLE_BOAT = 42,
  };
  enum class ADAG : uint8_t {
    UP = 9,
    UPRIGHT = 10,
    RIGHT = 11,
    DOWNRIGHT = 12,
    DOWN = 13,
    DOWNLEFT = 14,
    LEFT = 15,
    UPLEFT = 16,
  };

  enum class RESTYPE : uint8_t {
    CRYSTAL = 0,
    GEM = 1,
    MERCURY = 2,
    ORE = 3,
    SULFUR = 4,
    WOOD = 5,
    GOLD = 6,
  };

  enum class SCNTYPE : uint8_t {
    MOD,
    POP,
  };

  enum class CRETYPE : uint8_t {
    POP_HERO,
    POP_DWE,
    POP_BAT,
    MOD_HERO,
    MOD_DWE,
    MOD_BAT,
  };

  enum class CLICKTYPE : uint8_t {
    L_UP,
    L_DOWN,
    R_UP,
    R_DOWN,
  };

  enum class LANG : uint8_t {
    ENGLISH,
    CHINESE,
  };
};
