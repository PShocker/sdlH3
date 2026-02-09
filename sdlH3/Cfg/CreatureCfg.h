#pragma once

#include "SDL3/SDL_pixels.h"
#include <array>
#include <cstdint>
#include <string>
#include <vector>
struct CreatureCfg {

  enum OV_COLOR {
    CYAN,
    TRANSPARENCY,
  };

  const static inline std::array<SDL_Color, 2> ovColor = {
      SDL_Color{0, 255, 255, 255}, // CYAN
      SDL_Color{0, 0, 0, 0}        // TRANSPARENCY
  };

  enum class Creature : uint16_t {
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

  const static inline std::vector<int8_t> creatureLevel = {
      // 城堡 (0-13)
      1, // PIKEMAN
      1, // HALBERDIER
      2, // ARCHER
      2, // MARKSMAN
      3, // GRIFFIN
      3, // ROYAL_GRIFFIN
      4, // SWORDSMAN
      4, // CRUSADER
      5, // MONK
      5, // ZEALOT
      6, // CAVALIER
      6, // CHAMPION
      7, // ANGEL
      7, // ARCHANGEL

      // 壁垒 (14-27)
      1, // CENTAUR
      1, // CENTAUR_CAPTAIN
      2, // DWARF
      2, // BATTLE_DWARF
      3, // WOOD_ELF
      3, // GRAND_ELF
      4, // PEGASUS
      4, // SILVER_PEGASUS
      5, // DENDROID_GUARD
      5, // DENDROID_SOLDIER
      6, // UNICORN
      6, // WAR_UNICORN
      7, // GREEN_DRAGON
      7, // GOLD_DRAGON

      // 塔楼 (28-41)
      1, // GREMLIN
      1, // MASTER_GREMLIN
      2, // STONE_GARGOYLE
      2, // OBSIDIAN_GARGOYLE
      3, // STONE_GOLEM
      3, // IRON_GOLEM
      4, // MAGE
      4, // ARCH_MAGE
      5, // GENIE
      5, // MASTER_GENIE
      6, // NAGA
      6, // NAGA_QUEEN
      7, // GIANT
      7, // TITAN

      // 地狱 (42-55)
      1, // IMP
      1, // FAMILIAR
      2, // GOG
      2, // MAGOG
      3, // HELL_HOUND
      3, // CERBERUS
      4, // DEMON
      4, // HORNED_DEMON
      5, // PIT_FIEND
      5, // PIT_LORD
      6, // EFREETI
      6, // EFREET_SULTAN
      7, // DEVIL
      7, // ARCH_DEVIL

      // 墓园 (56-69)
      1, // SKELETON
      1, // SKELETON_WARRIOR
      2, // WALKING_DEAD
      2, // ZOMBIE
      3, // WIGHT
      3, // WRAITH
      4, // VAMPIRE
      4, // VAMPIRE_LORD
      5, // LICH
      5, // POWER_LICH
      6, // BLACK_KNIGHT
      6, // DREAD_KNIGHT
      7, // BONE_DRAGON
      7, // GHOST_DRAGON

      // 地牢 (70-83)
      1, // TROGLODYTE
      1, // INFERNAL_TROGLODYTE
      2, // HARPY
      2, // HARPY_HAG
      3, // BEHOLDER
      3, // EVIL_EYE
      4, // MEDUSA
      4, // MEDUSA_QUEEN
      5, // MINOTAUR
      5, // MINOTAUR_KING
      6, // MANTICORE
      6, // SCORPICORE
      7, // RED_DRAGON
      7, // BLACK_DRAGON

      // 据点 (84-97)
      1, // GOBLIN
      1, // HOBGOBLIN
      2, // WOLF_RIDER
      2, // WOLF_RAIDER
      3, // ORC
      3, // ORC_CHIEFTAIN
      4, // OGRE
      4, // OGRE_MAGE
      5, // ROC
      5, // THUNDERBIRD
      6, // CYCLOPS
      6, // CYCLOPS_KING
      7, // BEHEMOTH
      7, // ANCIENT_BEHEMOTH

      // 要塞 (98-111)
      1, // GNOLL
      1, // GNOLL_MARAUDER
      2, // LIZARDMAN
      2, // LIZARD_WARRIOR
      3, // GORGON
      3, // MIGHTY_GORGON
      4, // SERPENT_FLY
      4, // DRAGON_FLY
      5, // BASILISK
      5, // GREATER_BASILISK
      6, // WYVERN
      6, // WYVERN_MONARCH
      7, // HYDRA
      7, // CHAOS_HYDRA

      // 元素生物1 (112-117) - 中立生物
      2, // AIR_ELEMENTAL
      2, // EARTH_ELEMENTAL
      2, // FIRE_ELEMENTAL
      2, // WATER_ELEMENTAL
      5, // GOLD_GOLEM
      5, // DIAMOND_GOLEM

      // 元素生物2 (118-131) - 中立生物
      1, // PIXIE
      1, // SPRITE
      5, // PSYCHIC_ELEMENTAL
      6, // MAGIC_ELEMENTAL
      0, // NOT_USED_1 (占位符)
      4, // ICE_ELEMENTAL
      0, // NOT_USED_2 (占位符)
      4, // MAGMA_ELEMENTAL
      0, // NOT_USED_3 (占位符)
      5, // STORM_ELEMENTAL
      0, // NOT_USED_4 (占位符)
      5, // ENERGY_ELEMENTAL
      7, // FIREBIRD
      7, // PHOENIX

      // 特殊生物1 (132-144) - 中立生物
      10, // AZURE_DRAGON (特殊10级生物)
      10, // CRYSTAL_DRAGON (特殊10级生物)
      10, // FAERIE_DRAGON
      10, // RUST_DRAGON (8级生物)
      2,  // ENCHANTER
      2,  // SHARPSHOOTER
      1,  // HALFLING
      1,  // PEASANT
      2,  // BOAR
      5,  // MUMMY
      5,  // NOMAD
      4,  // ROGUE
      5,  // TROLL

      // 战争机器 (145-149) - 特殊单位
      0, // CATAPULT (战争机器)
      0, // BALLISTA (战争机器)
      0, // FIRST_AID_TENT (战争机器)
      0, // AMMO_CART (战争机器)
      0, // ARROW_TOWER (战争机器)
  };

  // 141个兵种的可升级目标，-1表示无升级目标，正数表示可升级到该ID
  const static inline std::vector<int16_t> creatureUpgradeTo = {
      // 城堡 (Castle) - 14个兵种
      1,  // 0: 枪兵 -> 戟兵
      -1, // 1: 戟兵 (无进一步升级)
      3,  // 2: 弓箭手 -> 神射手
      -1, // 3: 神射手 (无进一步升级)
      5,  // 4: 狮鹫 -> 皇家狮鹫
      -1, // 5: 皇家狮鹫 (无进一步升级)
      7,  // 6: 剑士 -> 十字军
      -1, // 7: 十字军 (无进一步升级)
      9,  // 8: 僧侣 -> 祭司
      -1, // 9: 祭司 (无进一步升级)
      11, // 10: 骑兵 -> 骑士
      -1, // 11: 骑士 (无进一步升级)
      13, // 12: 天使 -> 大天使
      -1, // 13: 大天使 (无进一步升级)

      // 壁垒 (Rampart) - 14个兵种
      15, // 14: 半人马 -> 半人马首领
      -1, // 15: 半人马首领 (无进一步升级)
      17, // 16: 矮人 -> 战斗矮人
      -1, // 17: 战斗矮人 (无进一步升级)
      19, // 18: 木精灵 -> 大精灵
      -1, // 19: 大精灵 (无进一步升级)
      21, // 20: 飞马 -> 银飞马
      -1, // 21: 银飞马 (无进一步升级)
      23, // 22: 枯木卫士 -> 枯木战士
      -1, // 23: 枯木战士 (无进一步升级)
      25, // 24: 独角兽 -> 独角神兽
      -1, // 25: 独角神兽 (无进一步升级)
      27, // 26: 绿龙 -> 金龙
      -1, // 27: 金龙 (无进一步升级)

      // 塔楼 (Tower) - 14个兵种
      29, // 28: 小妖精 -> 大妖精
      -1, // 29: 大妖精 (无进一步升级)
      31, // 30: 石像鬼 -> 石像怪
      -1, // 31: 石像怪 (无进一步升级)
      33, // 32: 石人 -> 铁人
      -1, // 33: 铁人 (无进一步升级)
      35, // 34: 法师 -> 大法师
      -1, // 35: 大法师 (无进一步升级)
      37, // 36: 神怪 -> 神怪主
      -1, // 37: 神怪主 (无进一步升级)
      39, // 38: 蛇女 -> 蛇妖
      -1, // 39: 蛇妖 (无进一步升级)
      41, // 40: 巨人 -> 泰坦巨人
      -1, // 41: 泰坦巨人 (无进一步升级)

      // 地狱 (Inferno) - 14个兵种
      43, // 42: 小怪物 -> 怪物
      -1, // 43: 怪物 (无进一步升级)
      45, // 44: 歌革 -> 玛各
      -1, // 45: 玛各 (无进一步升级)
      47, // 46: 地狱猎犬 -> 三首猎犬
      -1, // 47: 三首猎犬 (无进一步升级)
      49, // 48: 恶鬼 -> 长角恶鬼
      -1, // 49: 长角恶鬼 (无进一步升级)
      51, // 50: 邪神 -> 邪神王
      -1, // 51: 邪神王 (无进一步升级)
      53, // 52: 火精灵 -> 烈火精灵
      -1, // 53: 烈火精灵 (无进一步升级)
      55, // 54: 恶魔 -> 大恶魔
      -1, // 55: 大恶魔 (无进一步升级)

      // 墓园 (Necropolis) - 14个兵种
      57, // 56: 骷髅兵 -> 骷髅勇士
      -1, // 57: 骷髅勇士 (无进一步升级)
      59, // 58: 行尸 -> 僵尸
      -1, // 59: 僵尸 (无进一步升级)
      61, // 60: 幽灵 -> 阴魂
      -1, // 61: 阴魂 (无进一步升级)
      63, // 62: 吸血鬼 -> 吸血鬼王
      -1, // 63: 吸血鬼王 (无进一步升级)
      65, // 64: 尸巫 -> 尸巫王
      -1, // 65: 尸巫王 (无进一步升级)
      67, // 66: 暗黑骑士 -> 恐怖骑士
      -1, // 67: 恐怖骑士 (无进一步升级)
      69, // 68: 骨龙 -> 鬼龙
      -1, // 69: 鬼龙 (无进一步升级)

      // 地下城 (Dungeon) - 14个兵种
      71, // 70: 洞穴人 -> 地狱洞穴人
      -1, // 71: 地狱洞穴人 (无进一步升级)
      73, // 72: 鹰身女妖 -> 鹰身女巫
      -1, // 73: 鹰身女巫 (无进一步升级)
      75, // 74: 邪眼 -> 毒眼
      -1, // 75: 毒眼 (无进一步升级)
      77, // 76: 美杜莎 -> 美杜莎女王
      -1, // 77: 美杜莎女王 (无进一步升级)
      79, // 78: 牛头怪 -> 牛头王
      -1, // 79: 牛头王 (无进一步升级)
      81, // 80: 蝎狮 -> 毒蝎狮
      -1, // 81: 毒蝎狮 (无进一步升级)
      83, // 82: 赤龙 -> 黑龙
      -1, // 83: 黑龙 (无进一步升级)

      // 据点 (Stronghold) - 14个兵种
      85, // 84: 大耳怪 -> 大耳怪王
      -1, // 85: 大耳怪王 (无进一步升级)
      87, // 86: 恶狼骑士 -> 恶狼斗士
      -1, // 87: 恶狼斗士 (无进一步升级)
      89, // 88: 半兽人 -> 半兽人首领
      -1, // 89: 半兽人首领 (无进一步升级)
      91, // 90: 食人魔 -> 食人魔王
      -1, // 91: 食人魔王 (无进一步升级)
      93, // 92: 大雕 -> 雷鸟
      -1, // 93: 雷鸟 (无进一步升级)
      95, // 94: 独眼巨人 -> 独眼王
      -1, // 95: 独眼王 (无进一步升级)
      97, // 96: 比蒙 -> 比蒙巨兽
      -1, // 97: 比蒙巨兽 (无进一步升级)

      // 要塞 (Fortress) - 14个兵种
      99,  // 98: 狼人 -> 大狼人
      -1,  // 99: 大狼人 (无进一步升级)
      101, // 100: 蜥蜴人 -> 蜥蜴勇士
      -1,  // 101: 蜥蜴勇士 (无进一步升级)
      103, // 102: 野牛 -> 蛮牛
      -1,  // 103: 蛮牛 (无进一步升级)
      105, // 104: 毒蝇 -> 龙蝇
      -1,  // 105: 龙蝇 (无进一步升级)
      107, // 106: 蜥蜴 -> 巨蜥
      -1,  // 107: 巨蜥 (无进一步升级)
      109, // 108: 飞龙 -> 飞龙王
      -1,  // 109: 飞龙王 (无进一步升级)
      111, // 110: 九头怪 -> 终极九头怪
      -1,  // 111: 终极九头怪 (无进一步升级)

      // 元素城 (Conflux) - 14个兵种 (实际16个位置)
      127, // 112: 气元素
      125, // 113: 土元素
      129, // 114: 火元素
      123, // 115: 水元素
      -1,  // 116: 金人
      -1,  // 117: 钻石人 (无进一步升级)
      119, // 118: 小精灵 -> 精灵
      -1,  // 119: 精灵 (无进一步升级)
      121, // 120: 精神元素 -> 魔法元素
      -1,  // 121: 魔法元素 (无进一步升级)
      -1,  // 122: NOT USED (1) (无升级)
      -1,  // 123: 冰元素 (无升级)
      -1,  // 124: NOT USED (2) (无升级)
      -1,  // 125: 石元素 (无升级)
      -1,  // 126: NOT USED (3) (无升级)
      -1,  // 127: 雷元素 (无升级)
      -1,  // 128: NOT USED (4) (无升级)
      -1,  // 129: 烈火元素 (无升级)
      131, // 130: 火鸟 -> 凤凰
      -1,  // 131: 凤凰 (无进一步升级)

      // 中立兵种 (Neutral) - 13个兵种
      -1, // 132: 圣龙 (无升级)
      -1, // 133: 水晶龙 (无升级)
      -1, // 134: 紫龙 (无升级)
      -1, // 135: 毒龙 (无升级)
      -1, // 136: 魔幻法师 (无升级)
      -1, // 137: 幻影射手 (无升级)
      -1, // 138: 投石矮人 (无升级)
      -1, // 139: 农民 (无升级)
      -1, // 140: 野猪 (无升级)
      -1, // 141: 木乃伊 (无升级)
      -1, // 142: 游牧民 (无升级)
      -1, // 143: 盗贼 (无升级)
      -1, // 144: 恶鬼 (无升级)

      // 战争机器 (War Machines) - 5个
      -1, // 145: 投石车 (无升级)
      -1, // 146: 弩车 (无升级)
      -1, // 147: 急救帐篷 (无升级)
      -1, // 148: 补给车 (无升级)
      -1, // 149: 箭塔 (无升级)
  };

  const static inline std::vector<std::string> creatureGraphics = {
      "CPKMAN.DEF", // 枪兵 (pikeman)
      "CHALBD.DEF", // 戟兵 (halberdier)
      "CLCBOW.DEF", // 弓箭手 (archer)
      "CHCBOW.DEF", // 神射手 (marksman)
      "CGRIFF.DEF", // 狮鹫 (griffin)
      "CRGRIF.DEF", // 皇家狮鹫 (royalGriffin)
      "CSWORD.DEF", // 剑士 (swordsman)
      "CCRUSD.DEF", // 十字军 (crusader)
      "CMONKK.DEF", // 僧侣 (monk)
      "CZEALT.DEF", // 祭司 (zealot)
      "CCAVLR.DEF", // 骑兵 (cavalier)
      "CCHAMP.DEF", // 骑士 (champion)
      "CANGEL.DEF", // 天使 (angel)
      "CRANGL.DEF", // 大天使 (archangel)
      "CCENTR.DEF", // 半人马 (centaur)
      "CECENT.DEF", // 半人马首领 (centaurCaptain)
      "CDWARF.DEF", // 矮人 (dwarf)
      "CBDWAR.DEF", // 战斗矮人 (battleDwarf)
      "CELF.DEF",   // 木精灵 (woodElf)
      "CGRELF.DEF", // 大精灵 (grandElf)
      "CPEGAS.DEF", // 飞马 (pegasus)
      "CAPEGS.DEF", // 银飞马 (silverPegasus)
      "CTREE.DEF",  // 枯木卫士 (dendroidGuard)
      "CBTREE.DEF", // 枯木战士 (dendroidSoldier)
      "CUNICO.DEF", // 独角兽 (unicorn)
      "CWUNIC.DEF", // 独角神兽 (warUnicorn)
      "CGDRAG.DEF", // 绿龙 (greenDragon)
      "CDDRAG.DEF", // 金龙 (goldDragon)
  };

  const static inline std::vector<std::string> creatureGraphicsMini = {
      "AvWPike.def",  "AVWpikx0.def", "AvWLCrs.def",  "AvWHCrs.def",
      "AvWGrif.def",  "AVWgrix0.def", "AVWswrd0.def", "AVWswrx0.def",
      "AvWMonk.def",  "AVWmonx0.def", "AVWcvlr0.def", "AVWcvlx0.def",
      "AvWAngl.def",  "AvWArch.def",  "AVWcent0.def", "AVWcenx0.def",
      "AVWdwrf0.def", "AVWdwrx0.def", "AVWelfw0.def", "AVWelfx0.def",
      "AVWpega0.def", "AVWpegx0.def", "AVWtree0.def", "AVWtrex0.def",
      "AVWunic0.def", "AVWunix0.def", "AVWdrag0.def", "AVWdrax0.def",
      "AVWgrem0.def", "AVWgrex0.def", "AVWgarg0.def", "AVWgarx0.def",
      "AVWgolm0.def", "AVWgolx0.def", "AVWmage0.def", "AVWmagx0.def",
      "AVWgeni0.def", "AVWgenx0.def", "AVWnaga0.def", "AVWnagx0.def",
      "AVWtitn0.def", "AVWtitx0.def", "AVWimp0.def",  "AVWimpx0.def",
      "AVWgog0.def",  "AVWgogx0.def", "AVWhoun0.def", "AVWhoux0.def",
      "AVWdemn0.def", "AVWdemx0.def", "AVWpitf0.def", "AVWpitx0.def",
      "AVWefre0.def", "AVWefrx0.def", "AVWdevl0.def", "AVWdevx0.def",
      "AVWskel0.def", "AVWskex0.def", "AVWzomb0.def", "AVWzomx0.def",
      "AvWWigh.def",  "AVWwigx0.def", "AVWvamp0.def", "AVWvamx0.def",
      "AVWlich0.def", "AVWlicx0.def", "AVWbkni0.def", "AVWbknx0.def",
      "AVWbone0.def", "AVWbonx0.def", "AVWtrog0.def", "AvWInfr.def",
      "AVWharp0.def", "AVWharx0.def", "AVWbehl0.def", "AVWbehx0.def",
      "AvWMeds.def",  "AVWmedx0.def", "AvWMino.def",  "AVWminx0.def",
      "AVWmant0.def", "AVWmanx0.def", "AvWRDrg.def",  "AVWddrx0.def",
      "AVWgobl0.def", "AVWgobx0.def", "AVWwolf0.def", "AVWwolx0.def",
      "AVWorc0.def",  "AVWorcx0.def", "AVWogre0.def", "AVWogrx0.def",
      "AVWroc0.def",  "AVWrocx0.def", "AVWcycl0.def", "AVWcycx0.def",
      "AVWbhmt0.def", "AVWbhmx0.def", "AVWgnll0.def", "AVWgnlx0.def",
      "AvWLizr.def",  "AVWlizx0.def", "AvWDFly.def",  "AvWDFir.def",
      "AvWBasl.def",  "AvWGBas.def",  "AvWGorg.def",  "AVWgorx0.def",
      "AvWWyvr.def",  "AVWwyvx0.def", "AvWHydr.def",  "AVWhydx0.def",
      "AVWpixie.def", "AVWsprit.def", "AVWelmw0.def", "AVWicee.def",
      "AVWelme0.def", "AVWstone.def", "AVWelma0.def", "AVWstorm.def",
      "AVWelmf0.def", "AVWnrg.def",   "AVWpsye.def",  "AVWmagel.def",
      "AVWfbird.def", "AVWphx.def",   "AVWglmg0.def", "AVWglmd0.def",
      "AVWazure.def", "AVWcdrg.def",  "AVWfdrg.def",  "AVWrust.def",
      "AVWench.def",  "AVWsharp.def", "AVWhalf.def",  "AVWpeas.def",
      "AVWboar.def",  "AVWmumy.def",  "AVWnomd.def",  "AVWrog.def",
      "AVWtrll.def"};
  const static inline std::vector<int8_t> creatureTowns = {
      // 城堡 (Castle) - 16个兵种
      0, // 枪兵
      0, // 戟兵
      0, // 弓箭手
      0, // 神射手
      0, // 狮鹫
      0, // 皇家狮鹫
      0, // 剑士
      0, // 十字军
      0, // 僧侣
      0, // 祭司
      0, // 骑兵
      0, // 骑士
      0, // 天使
      0, // 大天使

      // 壁垒 (Rampart) - 16个兵种
      1, // 半人马
      1, // 半人马首领
      1, // 矮人
      1, // 战斗矮人
      1, // 木精灵
      1, // 大精灵
      1, // 飞马
      1, // 银飞马
      1, // 枯木卫士
      1, // 枯木战士
      1, // 独角兽
      1, // 独角神兽
      1, // 绿龙
      1, // 金龙

      // 塔楼 (Tower) - 16个兵种
      2, // 小妖精
      2, // 大妖精
      2, // 石像鬼
      2, // 石像怪
      2, // 石人
      2, // 铁人
      2, // 法师
      2, // 大法师
      2, // 神怪
      2, // 神怪主
      2, // 蛇女
      2, // 蛇妖
      2, // 巨人
      2, // 泰坦巨人

      // 地狱 (Inferno) - 16个兵种
      3, // 小怪物
      3, // 怪物
      3, // 歌革
      3, // 玛各
      3, // 地狱猎犬
      3, // 三首猎犬
      3, // 恶鬼
      3, // 长角恶鬼
      3, // 邪神
      3, // 邪神王
      3, // 火精灵
      3, // 烈火精灵
      3, // 恶魔
      3, // 大恶魔

      // 墓园 (Necropolis) - 16个兵种
      4, // 骷髅兵
      4, // 骷髅勇士
      4, // 行尸
      4, // 僵尸
      4, // 幽灵
      4, // 阴魂
      4, // 吸血鬼
      4, // 吸血鬼王
      4, // 尸巫
      4, // 尸巫王
      4, // 暗黑骑士
      4, // 恐怖骑士
      4, // 骨龙
      4, // 鬼龙

      // 地下城 (Dungeon) - 16个兵种
      5, // 洞穴人
      5, // 地狱洞穴人
      5, // 鹰身女妖
      5, // 鹰身女巫
      5, // 邪眼
      5, // 毒眼
      5, // 美杜莎
      5, // 美杜莎女王
      5, // 牛头怪
      5, // 牛头王
      5, // 蝎狮
      5, // 毒蝎狮
      5, // 赤龙
      5, // 黑龙

      // 据点 (Stronghold) - 16个兵种
      6, // 大耳怪
      6, // 大耳怪王
      6, // 恶狼骑士
      6, // 恶狼斗士
      6, // 半兽人
      6, // 半兽人首领
      6, // 食人魔
      6, // 食人魔王
      6, // 大雕
      6, // 雷鸟
      6, // 独眼巨人
      6, // 独眼王
      6, // 比蒙
      6, // 比蒙巨兽

      // 要塞 (Fortress) - 16个兵种
      7, // 狼人
      7, // 大狼人
      7, // 蜥蜴人
      7, // 蜥蜴勇士
      7, // 野牛
      7, // 蛮牛
      7, // 毒蝇
      7, // 龙蝇
      7, // 蜥蜴
      7, // 巨蜥
      7, // 飞龙
      7, // 飞龙王
      7, // 九头怪
      7, // 终极九头怪

      // 元素城 (Conflux) - 16个兵种
      8,  // 气元素
      8,  // 土元素
      8,  // 火元素
      8,  // 水元素
      -1, // 金人
      -1, // 钻石人
      8,  // 小精灵
      8,  // 精灵
      8,  // 精神元素
      8,  // 魔法元素
      8,  // NOT USED (1)
      8,  // 冰元素
      8,  // NOT USED (2)
      8,  // 石元素
      8,  // NOT USED (3)
      8,  // 雷元素
      8,  // NOT USED (4)
      8,  // 烈火元素
      8,  // 火鸟
      8,  // 凤凰

      // 中立兵种 (Neutral) - 10个
      -1, // 圣龙
      -1, // 水晶龙
      -1, // 紫龙
      -1, // 毒龙
      -1, // 魔幻法师
      -1, // 幻影射手
      -1, // 投石矮人
      -1, // 农民
      -1, // 野猪
      -1, // 木乃伊
      -1, // 游牧民
      -1, // 盗贼
      -1, // 恶鬼

      // 战争机器 (War Machines) - 5个
      -1, // 投石车
      -1, // 弩车
      -1, // 急救帐篷
      -1, // 补给车
      -1, // 箭塔
  };
  // CRTRAITS.TXT
  const static inline std::vector<std::vector<uint32_t>> creatureCost = {
      // 城堡 (0-13)
      {0, 0, 0, 0, 0, 0, 60},   // 0: 枪兵
      {0, 0, 0, 0, 0, 0, 75},   // 1: 戟兵
      {0, 0, 0, 0, 0, 0, 100},  // 2: 弓箭手
      {0, 0, 0, 0, 0, 0, 150},  // 3: 神射手
      {0, 0, 0, 0, 0, 0, 200},  // 4: 狮鹫
      {0, 0, 0, 0, 0, 0, 240},  // 5: 皇家狮鹫
      {0, 0, 0, 0, 0, 0, 300},  // 6: 剑士
      {0, 0, 0, 0, 0, 0, 400},  // 7: 十字军
      {0, 0, 0, 0, 0, 0, 400},  // 8: 僧侣
      {0, 0, 0, 0, 0, 0, 450},  // 9: 祭司
      {0, 0, 0, 0, 0, 0, 1000}, // 10: 骑兵
      {0, 0, 0, 0, 0, 0, 1200}, // 11: 骑士
      {0, 0, 0, 0, 0, 1, 3000}, // 12: 天使
      {0, 0, 0, 0, 0, 3, 5000}, // 13: 大天使

      // 壁垒 (14-27)
      {0, 0, 0, 0, 0, 0, 70},   // 14: 半人马
      {0, 0, 0, 0, 0, 0, 90},   // 15: 半人马首领
      {0, 0, 0, 0, 0, 0, 120},  // 16: 矮人
      {0, 0, 0, 0, 0, 0, 150},  // 17: 战斗矮人
      {0, 0, 0, 0, 0, 0, 200},  // 18: 木精灵
      {0, 0, 0, 0, 0, 0, 225},  // 19: 大精灵
      {0, 0, 0, 0, 0, 0, 250},  // 20: 飞马
      {0, 0, 0, 0, 0, 0, 275},  // 21: 银飞马
      {0, 0, 0, 0, 0, 0, 350},  // 22: 枯木卫士
      {0, 0, 0, 0, 0, 0, 425},  // 23: 枯木战士
      {0, 0, 0, 0, 0, 0, 850},  // 24: 独角兽
      {0, 0, 0, 0, 0, 0, 950},  // 25: 独角神兽
      {0, 0, 0, 0, 1, 0, 2400}, // 26: 绿龙
      {0, 0, 0, 0, 2, 0, 4000}, // 27: 金龙

      // 塔楼 (28-41)
      {0, 0, 0, 0, 0, 0, 30},   // 28: 小妖精
      {0, 0, 0, 0, 0, 0, 40},   // 29: 大妖精
      {0, 0, 0, 0, 0, 0, 130},  // 30: 石像鬼
      {0, 0, 0, 0, 0, 0, 160},  // 31: 石像怪
      {0, 0, 0, 0, 0, 0, 150},  // 32: 石人
      {0, 0, 0, 0, 0, 0, 200},  // 33: 铁人
      {0, 0, 0, 0, 0, 0, 350},  // 34: 法师
      {0, 0, 0, 0, 0, 0, 450},  // 35: 大法师
      {0, 0, 0, 0, 0, 0, 550},  // 36: 神怪
      {0, 0, 0, 0, 0, 0, 600},  // 37: 神怪主
      {0, 0, 0, 0, 0, 0, 1100}, // 38: 蛇女
      {0, 0, 0, 0, 0, 0, 1600}, // 39: 蛇妖
      {0, 0, 0, 0, 0, 1, 2000}, // 40: 巨人
      {0, 0, 0, 0, 0, 2, 5000}, // 41: 泰坦巨人

      // 地狱 (42-55)
      {0, 0, 0, 0, 0, 0, 50},   // 42: 小怪物
      {0, 0, 0, 0, 0, 0, 60},   // 43: 怪物
      {0, 0, 0, 0, 0, 0, 125},  // 44: 歌革
      {0, 0, 0, 0, 0, 0, 175},  // 45: 玛各
      {0, 0, 0, 0, 0, 0, 200},  // 46: 地狱猎犬
      {0, 0, 0, 0, 0, 0, 250},  // 47: 三首猎犬
      {0, 0, 0, 0, 0, 0, 250},  // 48: 恶鬼
      {0, 0, 0, 0, 0, 0, 270},  // 49: 长角恶鬼
      {0, 0, 0, 0, 0, 0, 500},  // 50: 邪神
      {0, 0, 0, 0, 0, 0, 700},  // 51: 邪神王
      {0, 0, 0, 0, 0, 0, 900},  // 52: 火精灵
      {0, 0, 0, 0, 0, 0, 1100}, // 53: 烈火精灵
      {0, 1, 0, 0, 0, 0, 2700}, // 54: 恶魔
      {0, 2, 0, 0, 0, 0, 4500}, // 55: 大恶魔

      // 墓园 (56-69)
      {0, 0, 0, 0, 0, 0, 60},   // 56: 骷髅兵
      {0, 0, 0, 0, 0, 0, 70},   // 57: 骷髅勇士
      {0, 0, 0, 0, 0, 0, 100},  // 58: 行尸
      {0, 0, 0, 0, 0, 0, 125},  // 59: 僵尸
      {0, 0, 0, 0, 0, 0, 200},  // 60: 幽灵
      {0, 0, 0, 0, 0, 0, 230},  // 61: 阴魂
      {0, 0, 0, 0, 0, 0, 360},  // 62: 吸血鬼
      {0, 0, 0, 0, 0, 0, 500},  // 63: 吸血鬼王
      {0, 0, 0, 0, 0, 0, 550},  // 64: 尸巫
      {0, 0, 0, 0, 0, 0, 600},  // 65: 尸巫王
      {0, 0, 0, 0, 0, 0, 1200}, // 66: 暗黑骑士
      {0, 0, 0, 0, 0, 0, 1500}, // 67: 恐怖骑士
      {0, 0, 0, 0, 0, 0, 1800}, // 68: 骨龙
      {0, 1, 0, 0, 0, 0, 3000}, // 69: 鬼龙

      // 地下城 (70-83)
      {0, 0, 0, 0, 0, 0, 50},   // 70: 洞穴人
      {0, 0, 0, 0, 0, 0, 65},   // 71: 地狱洞穴人
      {0, 0, 0, 0, 0, 0, 130},  // 72: 鹰身女妖
      {0, 0, 0, 0, 0, 0, 170},  // 73: 鹰身女巫
      {0, 0, 0, 0, 0, 0, 250},  // 74: 邪眼
      {0, 0, 0, 0, 0, 0, 280},  // 75: 毒眼
      {0, 0, 0, 0, 0, 0, 300},  // 76: 美杜莎
      {0, 0, 0, 0, 0, 0, 330},  // 77: 美杜莎女王
      {0, 0, 0, 0, 0, 0, 500},  // 78: 牛头怪
      {0, 0, 0, 0, 0, 0, 575},  // 79: 牛头王
      {0, 0, 0, 0, 0, 0, 850},  // 80: 蝎狮
      {0, 0, 0, 0, 0, 0, 1050}, // 81: 毒蝎狮
      {0, 0, 0, 1, 0, 0, 2500}, // 82: 赤龙
      {0, 0, 0, 2, 0, 0, 4000}, // 83: 黑龙

      // 据点 (84-97)
      {0, 0, 0, 0, 0, 0, 40},   // 84: 大耳怪
      {0, 0, 0, 0, 0, 0, 50},   // 85: 大耳怪王
      {0, 0, 0, 0, 0, 0, 100},  // 86: 恶狼骑士
      {0, 0, 0, 0, 0, 0, 140},  // 87: 恶狼斗士
      {0, 0, 0, 0, 0, 0, 150},  // 88: 半兽人
      {0, 0, 0, 0, 0, 0, 165},  // 89: 半兽人首领
      {0, 0, 0, 0, 0, 0, 300},  // 90: 食人魔
      {0, 0, 0, 0, 0, 0, 400},  // 91: 食人魔王
      {0, 0, 0, 0, 0, 0, 600},  // 92: 大雕
      {0, 0, 0, 0, 0, 0, 700},  // 93: 雷鸟
      {0, 0, 0, 0, 0, 0, 750},  // 94: 独眼巨人
      {0, 0, 0, 0, 0, 0, 1100}, // 95: 独眼王
      {0, 0, 0, 0, 0, 0, 1500}, // 96: 比蒙
      {0, 0, 0, 0, 1, 0, 3000}, // 97: 比蒙巨兽

      // 要塞 (98-111)
      {0, 0, 0, 0, 0, 0, 50},   // 98: 狼人
      {0, 0, 0, 0, 0, 0, 70},   // 99: 大狼人
      {0, 0, 0, 0, 0, 0, 110},  // 100: 蜥蜴人
      {0, 0, 0, 0, 0, 0, 140},  // 101: 蜥蜴勇士
      {0, 0, 0, 0, 0, 0, 525},  // 102: 野牛
      {0, 0, 0, 0, 0, 0, 600},  // 103: 蛮牛
      {0, 0, 0, 0, 0, 0, 220},  // 104: 毒蝇
      {0, 0, 0, 0, 0, 0, 240},  // 105: 龙蝇
      {0, 0, 0, 0, 0, 0, 325},  // 106: 蜥蜴
      {0, 0, 0, 0, 0, 0, 400},  // 107: 巨蜥
      {0, 0, 0, 0, 0, 0, 800},  // 108: 飞龙
      {0, 0, 0, 0, 0, 0, 1100}, // 109: 飞龙王
      {0, 0, 0, 0, 0, 0, 2200}, // 110: 九头怪
      {0, 0, 0, 1, 0, 0, 3500}, // 111: 终极九头怪

      // 元素 (112-117)
      {0, 0, 0, 0, 0, 0, 250}, // 112: 气元素
      {0, 0, 0, 0, 0, 0, 400}, // 113: 土元素
      {0, 0, 0, 0, 0, 0, 350}, // 114: 火元素
      {0, 0, 0, 0, 0, 0, 300}, // 115: 水元素
      {0, 0, 0, 0, 0, 0, 500}, // 116: 金人
      {0, 0, 0, 0, 0, 0, 750}, // 117: 钻石人

      // 元素和特殊 (118-149)
      {0, 0, 0, 0, 0, 0, 25},   // 118: 小精灵
      {0, 0, 0, 0, 0, 0, 30},   // 119: 精灵
      {0, 0, 0, 0, 0, 0, 750},  // 120: 精神元素
      {0, 0, 0, 0, 0, 0, 800},  // 121: 魔法元素
      {0, 0, 0, 0, 0, 0, 0},    // 122: NOT USED (1)
      {0, 0, 0, 0, 0, 0, 375},  // 123: 冰元素
      {0, 0, 0, 0, 0, 0, 0},    // 124: NOT USED (2)
      {0, 0, 0, 0, 0, 0, 500},  // 125: 石元素
      {0, 0, 0, 0, 0, 0, 0},    // 126: NOT USED (3)
      {0, 0, 0, 0, 0, 0, 275},  // 127: 雷元素
      {0, 0, 0, 0, 0, 0, 0},    // 128: NOT USED (4)
      {0, 0, 0, 0, 0, 0, 400},  // 129: 烈火元素
      {0, 0, 0, 0, 0, 0, 1500}, // 130: 火鸟
      {0, 1, 0, 0, 0, 0, 2000}, // 131: 凤凰

      // 特殊生物 (132-149)
      {0, 20, 0, 0, 0, 0, 30000}, // 132: 圣龙
      {0, 0, 0, 0, 10, 0, 20000}, // 133: 水晶龙
      {0, 0, 0, 0, 0, 8, 10000},  // 134: 紫龙
      {0, 0, 0, 14, 0, 0, 15000}, // 135: 毒龙
      {0, 0, 0, 0, 0, 0, 750},    // 136: 魔幻法师
      {0, 0, 0, 0, 0, 0, 400},    // 137: 幻影射手
      {0, 0, 0, 0, 0, 0, 40},     // 138: 投石矮人
      {0, 0, 0, 0, 0, 0, 10},     // 139: 农民
      {0, 0, 0, 0, 0, 0, 150},    // 140: 野猪
      {0, 0, 0, 0, 0, 0, 300},    // 141: 木乃伊
      {0, 0, 0, 0, 0, 0, 200},    // 142: 游牧民
      {0, 0, 0, 0, 0, 0, 100},    // 143: 盗贼
      {0, 0, 0, 0, 0, 0, 500},    // 144: 恶鬼
      {0, 0, 0, 0, 0, 0, 1},      // 145: 投石车
      {0, 0, 0, 0, 0, 0, 2500},   // 146: 弩车
      {0, 0, 0, 0, 0, 0, 750},    // 147: 急救帐篷
      {0, 0, 0, 0, 0, 0, 1000},   // 148: 补给车
      {0, 0, 0, 0, 0, 0, 1000}    // 149: 箭塔
  };

  // Hit Points,Speed,Attack,Defense,Low,High,Shots,Spells,Low,High
  enum ATTRIBUTE {
    LIFE,
    SPEED,
    ATTACK,
    DEFENSE,
    LOW_DMG,
    HIGH_DMG,
    SHOTS,
    SPELL,
    LOW,
    HIGH,
  };

  const static inline std::vector<std::vector<uint16_t>> creatureAttr = {
      // 城堡
      {10, 4, 4, 5, 1, 3, 0, 0, 20, 50},      // 枪兵
      {10, 5, 6, 5, 2, 3, 0, 0, 20, 30},      // 戟兵
      {10, 4, 6, 3, 2, 3, 12, 0, 16, 30},     // 弓箭手
      {10, 6, 6, 3, 2, 3, 24, 0, 16, 25},     // 神射手
      {25, 6, 8, 8, 3, 6, 0, 0, 12, 25},      // 狮鹫
      {25, 9, 9, 9, 3, 6, 0, 0, 12, 20},      // 皇家狮鹫
      {35, 5, 10, 12, 6, 9, 0, 0, 10, 20},    // 剑士
      {35, 6, 12, 12, 7, 10, 0, 0, 10, 16},   // 十字军
      {30, 5, 12, 7, 10, 12, 12, 0, 8, 16},   // 僧侣
      {30, 7, 12, 10, 10, 12, 24, 0, 8, 12},  // 祭司
      {100, 7, 15, 15, 15, 25, 0, 0, 5, 12},  // 骑兵
      {100, 9, 16, 16, 20, 25, 0, 0, 5, 10},  // 骑士
      {200, 12, 20, 20, 50, 50, 0, 0, 4, 10}, // 天使
      {250, 18, 30, 30, 50, 50, 0, 1, 3, 8},  // 大天使

      // 壁垒
      {8, 6, 5, 3, 2, 3, 0, 0, 20, 50},       // 半人马
      {10, 8, 6, 3, 2, 3, 0, 0, 20, 30},      // 半人马首领
      {20, 3, 6, 7, 2, 4, 0, 0, 16, 30},      // 矮人
      {20, 5, 7, 7, 2, 4, 0, 0, 16, 25},      // 战斗矮人
      {15, 6, 9, 5, 3, 5, 24, 0, 12, 25},     // 木精灵
      {15, 7, 9, 5, 3, 5, 24, 0, 12, 20},     // 大精灵
      {30, 8, 9, 8, 5, 9, 0, 0, 10, 20},      // 飞马
      {30, 12, 9, 10, 5, 9, 0, 0, 10, 16},    // 银飞马
      {55, 3, 9, 12, 10, 14, 0, 0, 8, 16},    // 枯木卫士
      {65, 4, 9, 12, 10, 14, 0, 0, 8, 12},    // 枯木战士
      {90, 7, 15, 14, 18, 22, 0, 0, 5, 12},   // 独角兽
      {110, 9, 15, 14, 18, 22, 0, 0, 5, 10},  // 独角神兽
      {180, 10, 18, 18, 40, 50, 0, 0, 4, 10}, // 绿龙
      {250, 16, 27, 27, 40, 50, 0, 0, 3, 8},  // 金龙

      // 塔楼
      {4, 4, 3, 3, 1, 2, 0, 0, 20, 50},       // 小妖精
      {4, 5, 4, 4, 1, 2, 8, 0, 20, 30},       // 大妖精
      {16, 6, 6, 6, 2, 3, 0, 0, 16, 30},      // 石像鬼
      {16, 9, 7, 7, 2, 3, 0, 0, 16, 25},      // 石像怪
      {30, 3, 7, 10, 4, 5, 0, 0, 12, 25},     // 石人
      {35, 5, 9, 10, 4, 5, 0, 0, 12, 20},     // 铁人
      {25, 5, 11, 8, 7, 9, 24, 0, 10, 20},    // 法师
      {30, 7, 12, 9, 7, 9, 24, 0, 10, 16},    // 大法师
      {40, 7, 12, 12, 13, 16, 0, 0, 8, 16},   // 神怪
      {40, 11, 12, 12, 13, 16, 0, 3, 8, 12},  // 神怪主
      {110, 5, 16, 13, 20, 20, 0, 0, 5, 12},  // 蛇女
      {110, 7, 16, 13, 30, 30, 0, 0, 5, 10},  // 蛇妖
      {150, 7, 19, 16, 40, 60, 0, 0, 4, 10},  // 巨人
      {300, 11, 24, 24, 40, 60, 24, 0, 3, 8}, // 泰坦巨人

      // 地狱
      {4, 5, 2, 3, 1, 2, 0, 0, 20, 50},       // 小怪物
      {4, 7, 4, 4, 1, 2, 0, 0, 20, 30},       // 怪物
      {13, 4, 6, 4, 2, 4, 12, 0, 16, 30},     // 歌革
      {13, 6, 7, 4, 2, 4, 24, 0, 16, 25},     // 玛各
      {25, 7, 10, 6, 2, 7, 0, 0, 12, 25},     // 地狱猎犬
      {25, 8, 10, 8, 2, 7, 0, 0, 12, 20},     // 三首猎犬
      {35, 5, 10, 10, 7, 9, 0, 0, 10, 20},    // 恶鬼
      {40, 6, 10, 10, 7, 9, 0, 0, 10, 16},    // 长角恶鬼
      {45, 6, 13, 13, 13, 17, 0, 0, 8, 16},   // 邪神
      {45, 7, 13, 13, 13, 17, 0, 1, 8, 12},   // 邪神王
      {90, 9, 16, 12, 16, 24, 0, 0, 5, 12},   // 火精灵
      {90, 13, 16, 14, 16, 24, 0, 0, 5, 10},  // 烈火精灵
      {160, 11, 19, 21, 30, 40, 0, 0, 4, 10}, // 恶魔
      {200, 17, 26, 28, 30, 40, 0, 0, 3, 8},  // 大恶魔

      // 墓园
      {6, 4, 5, 4, 1, 3, 0, 0, 20, 50},      // 骷髅兵
      {6, 5, 6, 6, 1, 3, 0, 0, 20, 30},      // 骷髅勇士
      {15, 3, 5, 5, 2, 3, 0, 0, 16, 30},     // 行尸
      {20, 4, 5, 5, 2, 3, 0, 0, 16, 25},     // 僵尸
      {18, 5, 7, 7, 3, 5, 0, 0, 12, 25},     // 幽灵
      {18, 7, 7, 7, 3, 5, 0, 0, 12, 20},     // 阴魂
      {30, 6, 10, 9, 5, 8, 0, 0, 10, 20},    // 吸血鬼
      {40, 9, 10, 10, 5, 8, 0, 0, 10, 16},   // 吸血鬼王
      {30, 6, 13, 10, 11, 13, 12, 0, 8, 16}, // 尸巫
      {40, 7, 13, 10, 11, 15, 24, 0, 8, 12}, // 尸巫王
      {120, 7, 16, 16, 15, 30, 0, 0, 5, 12}, // 暗黑骑士
      {120, 9, 18, 18, 15, 30, 0, 0, 5, 10}, // 恐怖骑士
      {150, 9, 17, 15, 25, 50, 0, 0, 4, 10}, // 骨龙
      {200, 14, 19, 17, 25, 50, 0, 0, 3, 8}, // 鬼龙

      // 地下城
      {5, 4, 4, 3, 1, 3, 0, 0, 20, 50},       // 洞穴人
      {6, 5, 5, 4, 1, 3, 0, 0, 20, 30},       // 地狱洞穴人
      {14, 6, 6, 5, 1, 4, 0, 0, 16, 30},      // 鹰身女妖
      {14, 9, 6, 6, 1, 4, 0, 0, 16, 25},      // 鹰身女巫
      {22, 5, 9, 7, 3, 5, 12, 0, 12, 25},     // 邪眼
      {22, 7, 10, 8, 3, 5, 24, 0, 12, 20},    // 毒眼
      {25, 5, 9, 9, 6, 8, 4, 0, 10, 20},      // 美杜莎
      {30, 6, 10, 10, 6, 8, 8, 0, 10, 16},    // 美杜莎女王
      {50, 6, 14, 12, 12, 20, 0, 0, 8, 16},   // 牛头怪
      {50, 8, 15, 15, 12, 20, 0, 0, 8, 12},   // 牛头王
      {80, 7, 15, 13, 14, 20, 0, 0, 5, 12},   // 蝎狮
      {80, 11, 16, 14, 14, 20, 0, 0, 5, 10},  // 毒蝎狮
      {180, 11, 19, 19, 40, 50, 0, 0, 4, 10}, // 赤龙
      {300, 15, 25, 25, 40, 50, 0, 0, 3, 8},  // 黑龙

      // 据点
      {5, 5, 4, 2, 1, 2, 0, 0, 20, 50},      // 大耳怪
      {5, 7, 5, 3, 1, 2, 0, 0, 20, 30},      // 大耳怪王
      {10, 6, 7, 5, 2, 4, 0, 0, 16, 30},     // 恶狼骑士
      {10, 8, 8, 5, 3, 4, 0, 0, 16, 25},     // 恶狼斗士
      {15, 4, 8, 4, 2, 5, 12, 0, 12, 25},    // 半兽人
      {20, 5, 8, 4, 2, 5, 24, 0, 12, 20},    // 半兽人首领
      {40, 4, 13, 7, 6, 12, 0, 0, 10, 20},   // 食人魔
      {60, 5, 13, 7, 6, 12, 0, 3, 10, 16},   // 食人魔王
      {60, 7, 13, 11, 11, 15, 0, 0, 8, 16},  // 大雕
      {60, 11, 13, 11, 11, 15, 0, 0, 8, 12}, // 雷鸟
      {70, 6, 15, 12, 16, 20, 16, 0, 5, 12}, // 独眼巨人
      {70, 8, 17, 13, 16, 20, 24, 0, 5, 10}, // 独眼王
      {160, 6, 17, 17, 30, 50, 0, 0, 4, 10}, // 比蒙
      {300, 9, 19, 19, 30, 50, 0, 0, 3, 8},  // 比蒙巨兽

      // 要塞
      {6, 4, 3, 5, 2, 3, 0, 0, 20, 50},      // 狼人
      {6, 5, 4, 6, 2, 3, 0, 0, 20, 30},      // 大狼人
      {14, 4, 5, 6, 2, 3, 12, 0, 16, 30},    // 蜥蜴人
      {15, 5, 6, 8, 2, 5, 24, 0, 16, 25},    // 蜥蜴勇士
      {70, 5, 10, 14, 12, 16, 0, 0, 12, 25}, // 野牛
      {70, 6, 11, 16, 12, 16, 0, 0, 12, 20}, // 蛮牛
      {20, 9, 7, 9, 2, 5, 0, 0, 10, 20},     // 毒蝇
      {20, 13, 8, 10, 2, 5, 0, 0, 10, 16},   // 龙蝇
      {35, 5, 11, 11, 6, 10, 0, 0, 8, 16},   // 蜥蜴
      {40, 7, 12, 12, 6, 10, 0, 0, 8, 12},   // 巨蜥
      {70, 7, 14, 14, 14, 18, 0, 0, 5, 12},  // 飞龙
      {70, 11, 14, 14, 18, 22, 0, 0, 5, 10}, // 飞龙王
      {175, 5, 16, 18, 25, 45, 0, 0, 4, 10}, // 九头怪
      {250, 7, 18, 20, 25, 45, 0, 0, 3, 8},  // 终极九头怪

      // 元素
      {25, 7, 9, 9, 2, 8, 0, 0, 8, 12},     // 气元素
      {40, 4, 10, 10, 4, 8, 0, 0, 16, 30},  // 土元素
      {35, 6, 10, 8, 4, 6, 0, 0, 16, 25},   // 火元素
      {30, 5, 8, 10, 3, 7, 0, 0, 12, 25},   // 水元素
      {50, 5, 11, 12, 8, 10, 0, 0, 10, 16}, // 金人
      {60, 5, 13, 12, 10, 14, 0, 0, 8, 12}, // 钻石人

      // 特殊生物
      {3, 7, 2, 2, 1, 2, 0, 0, 20, 50},       // 小精灵
      {3, 9, 2, 2, 1, 3, 0, 0, 20, 30},       // 精灵
      {75, 7, 15, 13, 10, 20, 0, 0, 8, 16},   // 精神元素
      {80, 9, 15, 13, 15, 25, 0, 0, 8, 12},   // 魔法元素
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},         // NOT USED (1)
      {30, 6, 8, 10, 3, 7, 24, 3, 12, 20},    // 冰元素
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},         // NOT USED (2)
      {40, 6, 11, 11, 6, 10, 0, 3, 16, 25},   // 石元素
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},         // NOT USED (3)
      {25, 8, 9, 9, 2, 8, 24, 3, 6, 12},      // 雷元素
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},         // NOT USED (4)
      {35, 8, 12, 8, 4, 6, 0, 3, 12, 25},     // 烈火元素
      {150, 15, 18, 18, 30, 40, 0, 0, 4, 10}, // 火鸟
      {200, 21, 21, 18, 30, 40, 0, 1, 4, 10}, // 凤凰

      // 中立生物
      {1000, 19, 50, 50, 70, 80, 0, 0, 1, 3}, // 圣龙
      {800, 16, 40, 40, 60, 75, 0, 0, 1, 3},  // 水晶龙
      {500, 15, 20, 20, 20, 30, 0, 5, 1, 3},  // 紫龙
      {750, 17, 30, 30, 50, 50, 0, 0, 1, 3},  // 毒龙
      {30, 9, 17, 12, 14, 14, 32, 0, 5, 12},  // 魔幻法师
      {15, 9, 12, 10, 8, 10, 32, 0, 5, 12},   // 幻影射手
      {4, 5, 4, 2, 1, 3, 24, 0, 20, 50},      // 投石矮人
      {1, 3, 1, 1, 1, 1, 0, 0, 20, 50},       // 农民
      {15, 6, 6, 5, 2, 3, 0, 0, 16, 30},      // 野猪
      {30, 5, 7, 7, 3, 5, 0, 0, 12, 25},      // 木乃伊
      {30, 7, 9, 8, 2, 6, 0, 0, 12, 25},      // 游牧民
      {10, 6, 8, 3, 2, 4, 0, 0, 16, 30},      // 盗贼
      {40, 7, 14, 7, 10, 15, 0, 0, 8, 12},    // 恶鬼

      // 战争机器
      {1000, 0, 10, 10, 0, 0, 24, 0, 0, 0}, // 投石车
      {250, 0, 10, 10, 2, 3, 24, 0, 0, 0},  // 弩车
      {75, 0, 0, 0, 0, 0, 0, 0, 0, 0},      // 急救帐篷
      {100, 0, 0, 5, 0, 0, 0, 0, 0, 0},     // 补给车
      {100, 0, 10, 5, 2, 4, 99, 0, 0, 0}    // 箭塔
  };

  enum EX_ATTRIBUTE {
    // 基本类型属性
    SHOOTING_ARMY, // 远程部队
    FLYING_ARMY,   // 飞行部队
    DOUBLE_WIDE,   // 2格兵种
    IS_UNDEAD,     // 丧尸

    // 特殊能力属性
    const_no_melee_penalty, // 无近战惩罚
    const_two_attacks,      // 攻击两次
    const_free_attack,      // 不被反击
    const_jousting,         // 冲锋加成（杀伤力可增大）
    const_raises_morale,    // 提升士气
    const_lowers_morale,    // 降低士气
    const_no_wall_penalty,  // 无城墙惩罚

    // 兵种等级属性
    KING_1, // 7级生物（龙、比蒙、九头怪等）
    KING_2, // 天使/恶魔级别
    KING_3, // 巨人/泰坦级别

    // 魔法免疫属性
    IMMUNE_TO_MIND_SPELLS, // 免疫心智魔法
    IMMUNE_TO_FIRE_SPELLS, // 免疫火系魔法

    // 攻城属性
    CATAPULT,     // 攻击城墙
    SIEGE_WEAPON, // 攻城武器

    // 攻击方式属性
    MULTI_HEADED,        // 多头攻击（攻击多个敌人）
    HAS_EXTENDED_ATTACK, // 扩展攻击范围

    // 总属性数量
    LENGTH
  };

  const static inline std::vector<std::array<bool, EX_ATTRIBUTE::LENGTH>>
      creatureExAttr = {
          // 城堡（Castle）生物 - 9个
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 0: 枪兵
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 1: 戟兵
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 2: 弓箭手
          {true, false, false, false, false, true, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 3: 神射手
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 4: 狮鹫
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 5: 皇家狮鹫
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 6: 剑士
          {false, false, false, false, false, true, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 7: 十字军
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 8: 僧侣
          {true, false, false, false, true, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 9: 祭司
          {false, false, true, false, false, false, false, true, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 10: 骑兵
          {false, false, true, false, false, false, false, true, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 11: 骑士
          {false, true, false, false, false, false, false, false, true, false,
           false, false, true, false, false, false, false, false,
           false}, // 12: 天使（1格）
          {false, true, true, false, false, false, false, false, true, false,
           false, false, true, false, false, false, false, false,
           false}, // 13: 大天使（2格）

          // 壁垒（Rampart）生物 - 9个
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 14: 半人马
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 15: 半人马首领
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 16: 矮人
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 17: 战斗矮人
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 18: 木精灵
          {true, false, false, false, false, true, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 19: 大精灵
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 20: 飞马
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 21: 银飞马
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 22: 枯木卫士
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 23: 枯木战士
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 24: 独角兽
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 25: 独角神兽
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 26: 绿龙
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 27: 金龙

          // 塔楼（Tower）生物 - 9个
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 28: 小妖精
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 29: 大妖精
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 30: 石像鬼
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 31: 石像怪
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 32: 石人
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 33: 铁人
          {true, false, false, false, true, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 34: 法师
          {true, false, false, false, true, false, false, false, false, false,
           true, false, false, false, false, false, false, false,
           false}, // 35: 大法师（有const_no_wall_penalty）
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 36: 神怪
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 37: 神怪主
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 38: 蛇女
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 39: 蛇妖
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, true, false, false, false, false,
           false}, // 40: 巨人（KING_3）
          {true, false, false, false, true, false, false, false, false, false,
           false, false, false, true, false, false, false, false,
           false}, // 41: 泰坦巨人（SHOOTING_ARMY, const_no_melee_penalty,
                   // KING_3）

          // 地狱（Inferno）生物 - 9个
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 42: 小怪物
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 43: 怪物
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 44: 歌革
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 45: 玛各
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 46: 地狱猎犬
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, true,
           false}, // 47: 三首猎犬（MULTI_HEADED）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 48: 恶鬼
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 49: 长角恶鬼
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 50: 邪神
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 51: 邪神王
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 52: 火精灵
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 53: 烈火精灵
          {false, true, false, false, false, false, false, false, false, false,
           false, false, true, false, false, false, false, false,
           false}, // 54: 恶魔（KING_2）
          {false, true, false, false, false, false, false, false, false, false,
           false, false, true, false, false, false, false, false,
           false}, // 55: 大恶魔（KING_2）

          // 墓园（Necropolis）生物 - 9个
          {false, false, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 56: 骷髅兵（IS_UNDEAD）
          {false, false, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 57: 骷髅勇士（IS_UNDEAD）
          {false, false, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 58: 行尸（IS_UNDEAD）
          {false, false, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 59: 僵尸（IS_UNDEAD）
          {false, true, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 60: 幽灵（IS_UNDEAD, FLYING_ARMY）
          {false, true, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 61: 阴魂（IS_UNDEAD, FLYING_ARMY）
          {false, true, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 62: 吸血鬼（IS_UNDEAD, FLYING_ARMY）
          {false, true, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 63: 吸血鬼王（IS_UNDEAD, FLYING_ARMY）
          {true, false, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 64: 尸巫（IS_UNDEAD, SHOOTING_ARMY）
          {true, false, false, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 65: 尸巫王（IS_UNDEAD, SHOOTING_ARMY）
          {false, false, true, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 66: 暗黑骑士（IS_UNDEAD, DOUBLE_WIDE）
          {false, false, true, true, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 67: 恐怖骑士（IS_UNDEAD, DOUBLE_WIDE）
          {false, true, true, true, false, false, false, false, false, true,
           false, true, false, false, false, false, false, false,
           false}, // 68: 骨龙（IS_UNDEAD, FLYING_ARMY, DOUBLE_WIDE,
                   // const_lowers_morale, KING_1）
          {false, true, true, true, false, false, false, false, false, true,
           false, true, false, false, false, false, false, false,
           false}, // 69: 鬼龙（IS_UNDEAD, FLYING_ARMY, DOUBLE_WIDE,
                   // const_lowers_morale, KING_1）

          // 地下城（Dungeon）生物 - 9个
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 70: 洞穴人
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 71: 地狱洞穴人
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 72: 鹰身女妖
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 73: 鹰身女巫
          {true, false, false, false, true, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 74: 邪眼（SHOOTING_ARMY, const_no_melee_penalty）
          {true, false, false, false, true, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 75: 毒眼（SHOOTING_ARMY, const_no_melee_penalty）
          {true, false, true, false, true, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 76: 美杜莎（SHOOTING_ARMY, DOUBLE_WIDE,
                   // const_no_melee_penalty）
          {true, false, true, false, true, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 77: 美杜莎女王（SHOOTING_ARMY, DOUBLE_WIDE,
                   // const_no_melee_penalty）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 78: 牛头怪
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 79: 牛头王
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 80: 蝎狮
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 81: 毒蝎狮
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 82: 赤龙（FLYING_ARMY, DOUBLE_WIDE, KING_1）
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 83: 黑龙（FLYING_ARMY, DOUBLE_WIDE, KING_1）

          // 据点（Stronghold）生物 - 9个
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 84: 大耳怪
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 85: 大耳怪王
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 86: 恶狼骑士
          {false, false, true, false, false, true, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 87: 恶狼斗士（DOUBLE_WIDE, const_two_attacks）
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 88: 半兽人
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 89: 半兽人首领
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 90: 食人魔
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 91: 食人魔王
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 92: 大雕
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 93: 雷鸟
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, true, false, false,
           false}, // 94: 独眼巨人（SHOOTING_ARMY, CATAPULT）
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, true, false, false,
           false}, // 95: 独眼王（SHOOTING_ARMY, CATAPULT）
          {false, false, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 96: 比蒙（DOUBLE_WIDE, KING_1）
          {false, false, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 97: 比蒙巨兽（DOUBLE_WIDE, KING_1）

          // 要塞（Fortress）生物 - 9个
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 98: 狼人
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 99: 大狼人
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 100: 蜥蜴人
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 101: 蜥蜴勇士
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 102: 野牛
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 103: 蛮牛
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 104: 毒蝇
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 105: 龙蝇
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 106: 蜥蜴
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 107: 巨蜥
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 108: 飞龙
          {false, true, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 109: 飞龙王
          {false, false, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 110: 九头怪（DOUBLE_WIDE, KING_1）
          {false, false, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 111: 终极九头怪（DOUBLE_WIDE, KING_1）

          // 元素城（Conflux）生物 - 10个（包含特殊元素）
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 112: 小精灵
          {false, true, false, false, false, false, true, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 113: 精灵（FLYING_ARMY, const_free_attack）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, true, false, false, false, true,
           false}, // 114: 精神元素（IMMUNE_TO_MIND_SPELLS, MULTI_HEADED）
          {false, false, false, false, false, false, true, false, false, false,
           false, false, false, true, false, false, false, true,
           false}, // 115: 魔法元素（const_free_attack, IMMUNE_TO_MIND_SPELLS,
                   // MULTI_HEADED）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 116: NOT USED (1)
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, true, false, false, false, false,
           false}, // 117: 冰元素（SHOOTING_ARMY, IMMUNE_TO_MIND_SPELLS）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 118: NOT USED (2)
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, true, false, false, false, false,
           false}, // 119: 石元素（IMMUNE_TO_MIND_SPELLS）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 120: NOT USED (3)
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, true, false, false, false, false,
           false}, // 121: 雷元素（SHOOTING_ARMY, IMMUNE_TO_MIND_SPELLS）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 122: NOT USED (4)
          {false, true, false, false, false, false, false, false, false, false,
           false, false, false, true, true, false, false, false,
           false}, // 123: 烈火元素（FLYING_ARMY, IMMUNE_TO_MIND_SPELLS,
                   // IMMUNE_TO_FIRE_SPELLS）
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, true, false, false, false,
           true}, // 124: 火鸟（FLYING_ARMY, DOUBLE_WIDE, KING_1,
                  // IMMUNE_TO_FIRE_SPELLS, HAS_EXTENDED_ATTACK）
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, true, false, false, false,
           true}, // 125: 凤凰（FLYING_ARMY, DOUBLE_WIDE, KING_1,
                  // IMMUNE_TO_FIRE_SPELLS, HAS_EXTENDED_ATTACK）

          // 特殊生物
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 126: 圣龙
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 127: 水晶龙
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 128: 紫龙
          {false, true, true, false, false, false, false, false, false, false,
           false, true, false, false, false, false, false, false,
           false}, // 129: 毒龙
          {true, false, false, false, true, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 130: 魔幻法师（SHOOTING_ARMY, const_no_melee_penalty）
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 131: 幻影射手（SHOOTING_ARMY）
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 132: 投石矮人（SHOOTING_ARMY）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 133: 农民
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 134: 野猪
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 135: 木乃伊
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 136: 游牧民
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 137: 盗贼
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false}, // 138: 恶鬼（再生）

          // 攻城武器
          {true, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, true, true, false,
           false}, // 139: 投石车（SHOOTING_ARMY, DOUBLE_WIDE, CATAPULT,
                   // SIEGE_WEAPON）
          {true, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, true, false,
           false}, // 140: 弩车（SHOOTING_ARMY, DOUBLE_WIDE, SIEGE_WEAPON）
          {false, false, true, false, false, false, false, false, false, false,
           false, false, false, false, false, false, true, false,
           false}, // 141: 急救帐篷（DOUBLE_WIDE, SIEGE_WEAPON）
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, true, false,
           false}, // 142: 补给车（SIEGE_WEAPON）
          {true, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, true, false,
           false}, // 143: 箭塔（SHOOTING_ARMY, SIEGE_WEAPON）
  };

  const static inline std::vector<uint32_t> creatureExp = {
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 0-7
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 8-15
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 16-23
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 24-31
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 32-39
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 40-47
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 48-55
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 56-63
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 64-71
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 72-79
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 80-87
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 88-95
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 96-103
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 104-111
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 112-119
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 120-127
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, // 128-135
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000  // 136-143
  };

  const static inline std::vector<uint32_t> creatureGrowth = {
      // 城堡 (0-13)
      14, 14, 9, 9, 7, 7, 4, 4, 3, 3, 2, 2, 1, 1,
      // 壁垒 (14-27)
      14, 14, 8, 8, 7, 7, 5, 5, 3, 3, 2, 2, 1, 1,
      // 塔楼 (28-41)
      16, 16, 9, 9, 6, 6, 4, 4, 3, 3, 2, 2, 1, 1,
      // 地狱 (42-55)
      15, 15, 8, 8, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1,
      // 墓园 (56-69)
      12, 12, 8, 8, 7, 7, 4, 4, 3, 3, 2, 2, 1, 1,
      // 地下城 (70-83)
      14, 14, 8, 8, 7, 7, 4, 4, 3, 3, 2, 2, 1, 1,
      // 据点 (84-97)
      15, 15, 9, 9, 7, 7, 4, 4, 3, 3, 2, 2, 1, 1,
      // 要塞 (98-111)
      12, 12, 9, 9, 3, 3, 8, 8, 4, 4, 2, 2, 1, 1,
      // 元素 (112-117)
      6, 4, 5, 6, 3, 2,
      // 元素和特殊 (118-131)
      20, 20, 2, 2, 0, 6, 0, 4, 0, 6, 0, 5, 2, 2,
      // 特殊生物 (132-149)
      1, 1, 1, 1, 2, 4, 15, 25, 8, 7, 7, 8, 3, 0, 0, 0, 0, 0};

  enum CREATURE_ACTION {
    ACTION_MOVE = 0,
    ACTION_STAND = 2,
    ACTION_GET_HIT = 3,
    ACTION_DEFEND = 4,
    ACTION_ATTCK = 11,
    ACTION_SHOOT_UP = 11,
    ACTION_START_MOVE = 20,
    ACTION_STOP_MOVE = 21,
  };
};