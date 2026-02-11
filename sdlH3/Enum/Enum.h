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

  enum RESTYPE : uint8_t {
    CRYSTAL = 0,
    GEM = 1,
    MERCURY = 2,
    ORE = 3,
    SULFUR = 4,
    WOOD = 5,
    GOLD = 6,

    // 随机资源
    RAMDOM_RESOURCE
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
    SHOOTING_ARMY,    // 远程部队
    FLYING_ARMY,      // 飞行部队
    DOUBLE_WIDE,      // 2格兵种
    IS_UNDEAD,        // 丧尸
    MAGIC_RESISTANCE, // 魔法抵抗

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
    const_hate,                 // 死敌属性
    const_enemy_spell_cost,     //  增加(减少)敌方魔法消耗

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

  enum SECOND_SKILL : uint8_t {
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

  enum SECOND_SKILL_LEVEL : uint8_t { BASIC = 0, ADVANCED = 1, EXPERT = 2 };

  enum HERO_SPECIAL : uint8_t {
    // 技能类特长
    SPECIAL_SECONDARY_SKILL, // 对应二级技能 (如：archery, armorer, logistics等)
    SPECIAL_SPECIFIC_SPELL,
    // 生物类特长
    SPECIAL_CREATURE, // 特定生物增强

    // 属性类特长
    SPECIAL_PRIMARY_SKILL,            // 主要属性 (攻击、防御)
    SPECIAL_GENERAL_DAMAGE_PREMY,     // 通用伤害加成
    SPECIAL_GENERAL_DAMAGE_REDUCTION, // 通用伤害减免
    SPECIAL_STACKS_SPEED,             // 部队速度

    // 资源类特长
    SPECIAL_GENERATE_RESOURCE, // 资源生成 (gold, mercury, sulfur等)
    // 特殊类特长
    SPECIAL_SPECIAL_UPGRADE, // 特殊升级 (如：archer升级为sharpshooter)
  };

  enum SPELL : uint8_t {
    SummonBoat = 0,    // 0: 召船术
    ScuttleBoat = 1,   // 1: 摧毁船只
    Visions = 2,       // 2: 透视之眼
    ViewEarth = 3,     // 3: 透视大地
    Disguise = 4,      // 4: 伪装大法
    ViewAir = 5,       // 5: 透视大气
    Fly = 6,           // 6: 飞行奇术
    WaterWalk = 7,     // 7: 凌波微步
    DimensionDoor = 8, // 8: 异次元之门
    TownPortal = 9,    // 9: 时空之门

    Quicksand = 10,      // 10: 流沙陷阱
    LandMine = 11,       // 11: 埋设地雷
    ForceField = 12,     // 12: 大力神盾
    FireWall = 13,       // 13: 烈火魔墙
    Earthquake = 14,     // 14: 地动山摇
    MagicArrow = 15,     // 15: 魔法神箭
    IceBolt = 16,        // 16: 霹雳寒冰
    LightningBolt = 17,  // 17: 霹雳闪电
    Implosion = 18,      // 18: 雷鸣爆弹
    ChainLightning = 19, // 19: 连锁闪电

    FrostRing = 20,     // 20: 寒冰魔环
    Fireball = 21,      // 21: 连珠火球
    Inferno = 22,       // 22: 地狱烈焰
    MeteorShower = 23,  // 23: 流星火雨
    DeathRipple = 24,   // 24: 死亡波纹
    DestroyUndead = 25, // 25: 亡灵杀手
    Armageddon = 26,    // 26: 末日审判
    Shield = 27,        // 27: 护体神盾
    AirShield = 28,     // 28: 大气神盾
    FireShield = 29,    // 29: 烈火神盾

    ProtectionfromAir = 30,   // 30: 御气奇术
    ProtectionfromFire = 31,  // 31: 御火奇术
    ProtectionfromWater = 32, // 32: 御水奇术
    ProtectionfromEarth = 33, // 33: 御土奇术
    AntiMagic = 34,           // 34: 抗魔大法
    Dispel = 35,              // 35: 驱魔大法
    MagicMirror = 36,         // 36: 魔法神镜
    Cure = 37,                // 37: 疗伤
    Resurrection = 38,        // 38: 转世重生
    AnimateDead = 39,         // 39: 聚灵奇术

    Sacrifice = 40,     // 40: 牺牲
    Bless = 41,         // 41: 圣灵佑佐
    Curse = 42,         // 42: 恶咒附身
    Bloodlust = 43,     // 43: 嗜血奇术
    Precision = 44,     // 44: 百发百中
    Weakness = 45,      // 45: 虚弱无力
    StoneSkin = 46,     // 46: 护体石肤
    DisruptingRay = 47, // 47: 毁灭之光
    Prayer = 48,        // 48: 祈祷
    Mirth = 49,         // 49: 欢欣鼓舞

    Sorrow = 50,              // 50: 悲痛欲绝
    Fortune = 51,             // 51: 幸运之神
    Misfortune = 52,          // 52: 大难临头
    Haste = 53,               // 53: 攻击加速
    Slow = 54,                // 54: 迟缓大法
    Slayer = 55,              // 55: 屠戮成性
    Frenzy = 56,              // 56: 孤注一掷
    TitansLightningBolt = 57, // 57: 泰坦之箭
    Counterstrike = 58,       // 58: 反戈一击
    Berserk = 59,             // 59: 丧心病狂

    Hypnotize = 60,            // 60: 蛊惑人心
    Forgetfulness = 61,        // 61: 失忆大法
    Blind = 62,                // 62: 双目失明
    Teleport = 63,             // 63: 瞬间移动
    RemoveObstacle = 64,       // 64: 驱除障碍
    MirrorImage = 65,          // 65: 镜像大法
    SummonFireElemental = 66,  // 66: 召唤火元素
    SummonEarthElemental = 67, // 67: 召唤土元素
    SummonWaterElemental = 68, // 68: 召唤水元素
    SummonAirElemental = 69    // 69: 召唤气元素
  };

  enum BUILD : int32_t {
    // 通用建筑
    BUILD_VILLAGE_HALL = -1,
    BUILD_TOWN_HALL = 0,
    BUILD_CITY_HALL = 1,
    BUILD_CAPITOL = 2,
    BUILD_FORT = 3,
    BUILD_CITADEL = 4,
    BUILD_CASTLE = 5,
    BUILD_TAVERN = 6,
    BUILD_BLACKSMITH = 7,
    BUILD_MARKETPLACE = 8,
    BUILD_RESOURCE_SILO = 9,

    BUILD_SPECIAL_10 = 10,
    // 魔法行会
    BUILD_MAGE_GUILD_1 = 11,
    BUILD_MAGE_GUILD_2 = 12,
    BUILD_MAGE_GUILD_3 = 13,
    BUILD_MAGE_GUILD_4 = 14,
    BUILD_MAGE_GUILD_5 = 15,

    BUILD_SHIPYARD = 16,
    BUILD_GRAIL = 17,

    // 特殊建筑编号（根据城镇不同而意义不同）
    BUILD_SPECIAL_18 = 18,
    BUILD_SPECIAL_19 = 19,
    BUILD_SPECIAL_20 = 20,
    BUILD_SPECIAL_21 = 21,

    // 生物巢穴
    BUILD_DWELLING_LEVEL_1 = 22,
    BUILD_DWELLING_UPGRADE_LEVEL_1 = 23,
    BUILD_HORDE_1 = 24,
    BUILD_DWELLING_LEVEL_2 = 25,
    BUILD_DWELLING_UPGRADE_LEVEL_2 = 26,
    BUILD_HORDE_2 = 27,
    BUILD_DWELLING_LEVEL_3 = 28,
    BUILD_DWELLING_UPGRADE_LEVEL_3 = 29,
    BUILD_HORDE_3 = 30,
    BUILD_DWELLING_LEVEL_4 = 31,
    BUILD_DWELLING_UPGRADE_LEVEL_4 = 32,
    BUILD_HORDE_4 = 33,
    BUILD_DWELLING_LEVEL_5 = 34,
    BUILD_DWELLING_UPGRADE_LEVEL_5 = 35,
    BUILD_HORDE_5 = 36,
    BUILD_DWELLING_LEVEL_6 = 37,
    BUILD_DWELLING_UPGRADE_LEVEL_6 = 38,
    BUILD_DWELLING_LEVEL_7 = 39,
    BUILD_DWELLING_UPGRADE_LEVEL_7 = 40,
    // 额外的建筑,补充
    BUILD_SHIP,
    BUILD_HORDE_UPGRADE_1,
    BUILD_HORDE_UPGRADE_2,
    BUILD_HORDE_UPGRADE_3,
    BUILD_HORDE_UPGRADE_4,
    BUILD_HORDE_UPGRADE_5,

    // 一些额外的动画
    BUILD_EXTRA_ANIMATE_1,
    BUILD_EXTRA_ANIMATE_2,
    BUILD_EXTRA_ANIMATE_3,
  };

  enum TERRAIN : int8_t {
    TERRAIN_GRASS,
  };

  enum BUILD_BONUS : uint8_t {
    CREATURE_GROWTH,
    CREATURE_GROWTH_RATE,
    TOWN_BATTLE_MORALE_RAISE,
    TOWN_BATTLE_LUCK_RAISE,
    TOWN_BATTLE_ESCAPE,
    TOWN_BATTLE_SIEGE,
    RESTORE_MANA,
    HERO_PRIMAYRY_SKILL,
    HERO_SECOND_SKILL,
    HERO_MOVENT_LAND,
    HERO_MOVENT_SEA,
    HERO_MANA,
  };
};
