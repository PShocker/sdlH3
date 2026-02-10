#pragma once

#include <cstdint>
struct Enum {
  enum class DWEINCTYPE : uint8_t {
    BASE,
    BUILD,
    ARTIFACT,
  };

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

  enum FACTION : uint8_t {
    CASTLE,
    RAMPART,
    TOWER,
    INFERNO,
    NECROPOLIS,
    DUNGEON,
    STRONGHOLD,
    FORTRESS,
    CONFLUX,
    NEUTRAL,
  };

  enum CREATURE : uint16_t {
    // 城堡
    PIKEMAN = 0,
    HALBERDIER = 1,
    ARCHER = 2,
    MARKSMAN = 3,
    GRIFFIN = 4,
    ROYAL_GRIFFIN = 5,
    SWORDSMAN = 6,
    CRUSADER = 7,
    MONK = 8,
    ZEALOT = 9,
    CAVALIER = 10,
    CHAMPION = 11,
    ANGEL = 12,
    ARCHANGEL = 13,

    // 壁垒
    CENTAUR = 14,
    CENTAUR_CAPTAIN = 15,
    DWARF = 16,
    BATTLE_DWARF = 17,
    WOOD_ELF = 18,
    GRAND_ELF = 19,
    PEGASUS = 20,
    SILVER_PEGASUS = 21,
    DENDROID_GUARD = 22,
    DENDROID_SOLDIER = 23,
    UNICORN = 24,
    WAR_UNICORN = 25,
    GREEN_DRAGON = 26,
    GOLD_DRAGON = 27,

    // 塔楼
    GREMLIN = 28,
    MASTER_GREMLIN = 29,
    STONE_GARGOYLE = 30,
    OBSIDIAN_GARGOYLE = 31,
    STONE_GOLEM = 32,
    IRON_GOLEM = 33,
    MAGE = 34,
    ARCH_MAGE = 35,
    GENIE = 36,
    MASTER_GENIE = 37,
    NAGA = 38,
    NAGA_QUEEN = 39,
    GIANT = 40,
    TITAN = 41,

    // 地狱
    IMP = 42,
    FAMILIAR = 43,
    GOG = 44,
    MAGOG = 45,
    HELL_HOUND = 46,
    CERBERUS = 47,
    DEMON = 48,
    HORNED_DEMON = 49,
    PIT_FIEND = 50,
    PIT_LORD = 51,
    EFREETI = 52,
    EFREET_SULTAN = 53,
    DEVIL = 54,
    ARCH_DEVIL = 55,

    // 墓园
    SKELETON = 56,
    SKELETON_WARRIOR = 57,
    WALKING_DEAD = 58,
    ZOMBIE = 59,
    WIGHT = 60,
    WRAITH = 61,
    VAMPIRE = 62,
    VAMPIRE_LORD = 63,
    LICH = 64,
    POWER_LICH = 65,
    BLACK_KNIGHT = 66,
    DREAD_KNIGHT = 67,
    BONE_DRAGON = 68,
    GHOST_DRAGON = 69,

    // 地牢
    TROGLODYTE = 70,
    INFERNAL_TROGLODYTE = 71,
    HARPY = 72,
    HARPY_HAG = 73,
    BEHOLDER = 74,
    EVIL_EYE = 75,
    MEDUSA = 76,
    MEDUSA_QUEEN = 77,
    MINOTAUR = 78,
    MINOTAUR_KING = 79,
    MANTICORE = 80,
    SCORPICORE = 81,
    RED_DRAGON = 82,
    BLACK_DRAGON = 83,

    // 据点
    GOBLIN = 84,
    HOBGOBLIN = 85,
    WOLF_RIDER = 86,
    WOLF_RAIDER = 87,
    ORC = 88,
    ORC_CHIEFTAIN = 89,
    OGRE = 90,
    OGRE_MAGE = 91,
    ROC = 92,
    THUNDERBIRD = 93,
    CYCLOPS = 94,
    CYCLOPS_KING = 95,
    BEHEMOTH = 96,
    ANCIENT_BEHEMOTH = 97,

    // 要塞
    GNOLL = 98,
    GNOLL_MARAUDER = 99,
    LIZARDMAN = 100,
    LIZARD_WARRIOR = 101,
    GORGON = 102,
    MIGHTY_GORGON = 103,
    SERPENT_FLY = 104,
    DRAGON_FLY = 105,
    BASILISK = 106,
    GREATER_BASILISK = 107,
    WYVERN = 108,
    WYVERN_MONARCH = 109,
    HYDRA = 110,
    CHAOS_HYDRA = 111,

    // 元素生物1
    AIR_ELEMENTAL = 112,
    EARTH_ELEMENTAL = 113,
    FIRE_ELEMENTAL = 114,
    WATER_ELEMENTAL = 115,
    GOLD_GOLEM = 116,
    DIAMOND_GOLEM = 117,

    // 元素生物2
    PIXIE = 118,
    SPRITE = 119,
    PSYCHIC_ELEMENTAL = 120,
    MAGIC_ELEMENTAL = 121,
    NOT_USED_1 = 122,
    ICE_ELEMENTAL = 123,
    NOT_USED_2 = 124,
    MAGMA_ELEMENTAL = 125,
    NOT_USED_3 = 126,
    STORM_ELEMENTAL = 127,
    NOT_USED_4 = 128,
    ENERGY_ELEMENTAL = 129,
    FIREBIRD = 130,
    PHOENIX = 131,

    // 特殊生物1
    AZURE_DRAGON = 132,
    CRYSTAL_DRAGON = 133,
    FAERIE_DRAGON = 134,
    RUST_DRAGON = 135,
    ENCHANTER = 136,
    SHARPSHOOTER = 137,
    HALFLING = 138,
    PEASANT = 139,
    BOAR = 140,
    MUMMY = 141,
    NOMAD = 142,
    ROGUE = 143,
    TROLL = 144,

    // 战争机器
    CATAPULT = 145,
    BALLISTA = 146,
    FIRST_AID_TENT = 147,
    AMMO_CART = 148,
    ARROW_TOWER = 149,
  };

  enum CREATURE_EX_ATTRIBUTE {
    // 基本类型属性
    SHOOTING_ARMY, // 远程部队
    FLYING_ARMY,   // 飞行部队
    DOUBLE_WIDE,   // 2格兵种
    IS_UNDEAD,     // 丧尸

    // 特殊能力属性
    const_no_melee_penalty,     // 无近战惩罚
    const_two_attacks,          // 攻击两次
    const_two_distance_attacks, // 攻击两次(远程)
    const_free_attack,          // 不被反击
    const_jousting,             // 冲锋加成（杀伤力可增大）
    const_raises_morale,        // 提升士气
    const_lowers_morale,        // 降低士气
    const_no_wall_penalty,      // 无城墙惩罚
    const_two_retaliation,      // 两次反击
    const_three_retaliation,    // 三次反击(反戈一击+两次反击)
    const_unlimit_retaliation,  // 无限反击次数
    const_spell,                // 生物可以释放魔法
    const_spell_attack,         // 攻击后释放魔法
    const_spell_hit,            // 被攻击后产生的魔法

    // 兵种等级属性
    KING_1, // 7级生物（龙、比蒙、九头怪等）
    KING_2, // 天使/恶魔级别
    KING_3, // 巨人/泰坦级别

    // 魔法免疫属性
    IMMUNE_TO_MIND_SPELLS, // 免疫心智魔法
    IMMUNE_TO_FIRE_SPELLS, // 免疫火系魔法
    IMMUNE_TO_CAVALRY,     // 免疫骑兵冲锋

    // 攻城属性
    CATAPULT_ATTACK, // 攻击城墙
    SIEGE_WEAPON,    // 攻城武器

    // 攻击方式属性
    MULTI_HEADED,        // 多头攻击（攻击多个敌人）
    HAS_EXTENDED_ATTACK, // 扩展攻击范围
  };

  enum HERO_CLASS : uint8_t {
    HERO_CLASS_KNIGHT = 0,
    HERO_CLASS_CLERIC = 1,
    HERO_CLASS_RANGER = 2,
    HERO_CLASS_DRUID = 3,
    HERO_CLASS_ALCHEMIST = 4,
    HERO_CLASS_WIZARD = 5,
    HERO_CLASS_DEMON = 6,
    HERO_CLASS_HERETIC = 7,
    HERO_CLASS_DEATH_KNIGHT = 8,
    HERO_CLASS_NECROMANCER = 9,
    HERO_CLASS_OVERLORD = 10,
    HERO_CLASS_WARLOCK = 11,
    HERO_CLASS_BARBARIAN = 12,
    HERO_CLASS_BATTLE_MAGE = 13,
    HERO_CLASS_BEASTMASTER = 14,
    HERO_CLASS_WITCH = 15,
    HERO_CLASS_ELEMENTALIST = 16,
    HERO_CLASS_PLANESWALKER = 17,
  };
};
