#pragma once

#include <cstdint>
#include <utility>
#include <vector>
struct ArtifactCfg {
  enum class artSlot : uint8_t {
    HEAD,
    SHOULDERS,
    NECK,
    RIGHT_HAND,
    LEFT_HAND,
    TORSO,
    RIGHT_RING,
    LEFT_RING,
    FEET,
    MISC1,
    MISC2,
    MISC3,
    MISC4,
    MACH1,
    MACH2,
    MACH3,
    MACH4,
    SPELLBOOK,
    MISC5,
  };

  const static inline std::vector<uint32_t> artCost = {
      // 0-10
      0,    // 0: 魔法书
      2500, // 1: 魔法卷轴
      0,    // 2: 神器
      1000, // 3: 投石车
      2500, // 4: 弩车
      1000, // 5: 补给车
      750,  // 6: 急救帐篷
      2000, // 7: 人马战斧
      3000, // 8: 黑魔剑
      4000, // 9: 狼人连枷
      5000, // 10: 恶魔之棒

      // 11-20
      6000,  // 11: 火神剑
      10000, // 12: 泰坦之剑
      2000,  // 13: 矮人王盾
      3000,  // 14: 亡灵盾
      4000,  // 15: 狼人王盾
      5000,  // 16: 狂魔盾
      6000,  // 17: 邪盾
      10000, // 18: 守护神之盾
      1000,  // 19: 神兽之冠
      3000,  // 20: 骷髅冠

      // 21-30
      4000,  // 21: 混沌之冠
      5000,  // 22: 智慧之冠
      6000,  // 23: 地狱王冠
      10000, // 24: 雷神之盔
      1000,  // 25: 藤木甲
      3000,  // 26: 骨质胸甲
      4000,  // 27: 大蛇神胸甲
      5000,  // 28: 巨人战甲
      6000,  // 29: 黄金甲
      10000, // 30: 泰坦战甲

      // 31-40
      4000,  // 31: 神奇战甲
      8000,  // 32: 圣靴
      12000, // 33: 天使项链
      16000, // 34: 狮王盾
      20000, // 35: 先知剑
      24000, // 36: 神谕之冠
      2000,  // 37: 龙眼戒
      4000,  // 38: 赤龙剑
      6000,  // 39: 龙盾
      8000,  // 40: 龙甲

      // 41-50
      2000, // 41: 龙骨胫甲
      4000, // 42: 龙翼袍
      6000, // 43: 龙牙项链
      8000, // 44: 龙牙冠
      2000, // 45: 龙眼指环
      1000, // 46: 幸运三叶草
      1000, // 47: 预言卡
      1000, // 48: 幸运鸟
      1000, // 49: 勇气勋章
      1000, // 50: 勇士勋章

      // 51-60
      1000, // 51: 勇士令
      1000, // 52: 窥镜
      1000, // 53: 望远镜
      2000, // 54: 亡灵护身符
      4000, // 55: 吸血鬼披风
      6000, // 56: 死神靴
      2000, // 57: 抗魔链
      4000, // 58: 抗魔披风
      6000, // 59: 抗魔靴
      2000, // 60: 树精灵之弓

      // 61-70
      4000, // 61: 神兽之鬃
      6000, // 62: 天羽箭
      1000, // 63: 神目鸟
      2000, // 64: 火眼人
      3000, // 65: 真理徽章
      5000, // 66: 政治家勋章
      5000, // 67: 礼仪之戒
      5000, // 68: 大使勋带
      5000, // 69: 旅行者之戒
      3000, // 70: 骑士手套

      // 71-80
      10000, // 71: 海神项链
      20000, // 72: 炽天之翼
      500,   // 73: 魔力护符
      1000,  // 74: 魔法护符
      1500,  // 75: 魔力球
      500,   // 76: 魔力项圈
      1000,  // 77: 魔戒
      1500,  // 78: 魔法披风
      6000,  // 79: 气灵球
      6000,  // 80: 土灵球

      // 81-90
      6000,  // 81: 火灵球
      6000,  // 82: 水灵球
      8000,  // 83: 禁魔披风
      2000,  // 84: 禁锢之灵
      2000,  // 85: 恶运沙漏
      20000, // 86: 火系魔法书
      20000, // 87: 气系魔法书
      20000, // 88: 水系魔法书
      20000, // 89: 土系魔法书
      10000, // 90: 水神靴

      // 91-100
      8000,  // 91: 黄金弓
      7500,  // 92: 永恒之球
      25000, // 93: 毁灭之球
      5000,  // 94: 活力之戒
      5000,  // 95: 生命之戒
      10000, // 96: 活力圣瓶
      5000,  // 97: 极速项链
      6000,  // 98: 神行靴
      10000, // 99: 极速披风
      1000,  // 100: 冷静挂件

      // 101-110
      5000, // 101: 光明挂件
      1000, // 102: 神圣挂件
      2500, // 103: 生命挂件
      2500, // 104: 死神挂件
      1000, // 105: 自由挂件
      5000, // 106: 电神挂件
      3000, // 107: 清醒挂件
      7000, // 108: 勇气挂件
      5000, // 109: 水晶披风
      5000, // 110: 宝石戒指

      // 111-120
      5000,  // 111: 水银瓶
      5000,  // 112: 矿石车
      5000,  // 113: 硫磺指环
      5000,  // 114: 木材车
      10000, // 115: 黄金囊
      7500,  // 116: 黄金袋
      5000,  // 117: 黄金包
      5000,  // 118: 天赐神足
      5000,  // 119: 天赐神胯
      5000,  // 120: 天赐神躯

      // 121-130
      5000,  // 121: 天赐神臂
      5000,  // 122: 天赐神首
      15000, // 123: 航海家之帽
      30000, // 124: 魔法师之帽
      5000,  // 125: 战争枷锁
      20000, // 126: 禁魔球
      20000, // 127: 龙之血瓶
      50000, // 128: 末日之刃
      0,     // 129: 天使联盟
      0,     // 130: 鬼王斗蓬

      // 131-140
      0, // 131: 神圣血瓶
      0, // 132: 诅咒铠甲
      0, // 133: 天赐神兵
      0, // 134: 龙王神力
      0, // 135: 泰坦之箭
      0, // 136: 海洋之帽
      0, // 137: 幻影神弓
      0, // 138: 魔力源泉
      0, // 139: 法师之戒
      0, // 140: 丰收之角
      // 141-143
      0, // 141: Diplomat's Suit
      0, // 142: Mired in Neutrality
      0  // 143: Ironfist of the Ogre
  };

  const static inline std::vector<std::vector<bool>> artSlot = {
      // 0: 魔法书
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, true, false, false},
      // 1: 魔法卷轴
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, true},
      // 2: 神器
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 3: 投石车
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, true, false, false, false},
      // 4: 弩车
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, true, false, false, false, false, false},
      // 5: 补给车
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, true, false, false, false, false},
      // 6: 急救帐篷
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, true, false, false, false},
      // 7: 人马战斧
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 8: 黑魔剑
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 9: 狼人连枷
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 10: 恶魔之棒
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 11: 火神剑
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 12: 泰坦之剑
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 13: 矮人王盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 14: 亡灵盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 15: 狼人王盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 16: 狂魔盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 17: 邪盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 18: 守护神之盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 19: 神兽之冠
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 20: 骷髅冠
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 21: 混沌之冠
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 22: 智慧之冠
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 23: 地狱王冠
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 24: 雷神之盔
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 25: 藤木甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 26: 骨质胸甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 27: 大蛇神胸甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 28: 巨人战甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 29: 黄金甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 30: 泰坦战甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 31: 神奇战甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 32: 圣靴
      {false, false, false, false, false, false, false, false, true, false,
       false, false, false, false, false, false, false, false, false},
      // 33: 天使项链
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 34: 狮王盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 35: 先知剑
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 36: 神谕之冠
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 37: 龙眼戒
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 38: 赤龙剑
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 39: 龙盾
      {false, false, false, false, true, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 40: 龙甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 41: 龙骨胫甲
      {false, false, false, false, false, false, false, false, true, false,
       false, false, false, false, false, false, false, false, false},
      // 42: 龙翼袍
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 43: 龙牙项链
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 44: 龙牙冠
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 45: 龙眼指环
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 46: 幸运三叶草
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 47: 预言卡
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 48: 幸运鸟
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 49: 勇气勋章
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 50: 勇士勋章
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 51: 勇士令
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 52: 窥镜
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 53: 望远镜
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 54: 亡灵护身符
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 55: 吸血鬼披风
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 56: 死神靴
      {false, false, false, false, false, false, false, false, true, false,
       false, false, false, false, false, false, false, false, false},
      // 57: 抗魔链
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 58: 抗魔披风
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 59: 抗魔靴
      {false, false, false, false, false, false, false, false, true, false,
       false, false, false, false, false, false, false, false, false},
      // 60: 树精灵之弓
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 61: 神兽之鬃
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 62: 天羽箭
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 63: 神目鸟
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 64: 火眼人
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 65: 真理徽章
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 66: 政治家勋章
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 67: 礼仪之戒
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 68: 大使勋带
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 69: 旅行者之戒
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 70: 骑士手套
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 71: 海神项链
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 72: 炽天之翼
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 73: 魔力护符
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 74: 魔法护符
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 75: 魔力球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 76: 魔力项圈
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 77: 魔戒
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 78: 魔法披风
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 79: 气灵球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 80: 土灵球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 81: 火灵球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 82: 水灵球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 83: 禁魔披风
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 84: 禁锢之灵
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 85: 恶运沙漏
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 86: 火系魔法书
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 87: 气系魔法书
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 88: 水系魔法书
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 89: 土系魔法书
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 90: 水神靴
      {false, false, false, false, false, false, false, false, true, false,
       false, false, false, false, false, false, false, false, false},
      // 91: 黄金弓
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 92: 永恒之球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 93: 毁灭之球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 94: 活力之戒
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 95: 生命之戒
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 96: 活力圣瓶
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 97: 极速项链
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 98: 神行靴
      {false, false, false, false, false, false, false, false, true, false,
       false, false, false, false, false, false, false, false, false},
      // 99: 极速披风
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 100: 冷静挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 101: 光明挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 102: 神圣挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 103: 生命挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 104: 死神挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 105: 自由挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 106: 电神挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 107: 清醒挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 108: 勇气挂件
      {false, false, true, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 109: 水晶披风
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 110: 宝石戒指
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 111: 水银瓶
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 112: 矿石车
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 113: 硫磺指环
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 114: 木材车
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 115: 黄金囊
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 116: 黄金袋
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 117: 黄金包
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 118: 天赐神足
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 119: 天赐神胯
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 120: 天赐神躯
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 121: 天赐神臂
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 122: 天赐神首
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 123: 航海家之帽
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 124: 魔法师之帽
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 125: 战争枷锁
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 126: 禁魔球
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 127: 龙之血瓶
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 128: 末日之刃
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 129: 天使联盟
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 130: 鬼王斗蓬
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 131: 神圣血瓶
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 132: 诅咒铠甲
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 133: 天赐神兵
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 134: 龙王神力
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 135: 泰坦之箭
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 136: 海洋之帽
      {true, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 137: 幻影神弓
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 138: 魔力源泉
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 139: 法师之戒
      {false, false, false, false, false, false, true, true, false, false,
       false, false, false, false, false, false, false, false, false},
      // 140: 丰收之角
      {false, false, false, false, false, false, false, false, false, true,
       true, true, true, false, false, false, false, false, true},
      // 141: Diplomat's Suit
      {false, true, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 142: Mired in Neutrality
      {false, false, false, false, false, true, false, false, false, false,
       false, false, false, false, false, false, false, false, false},
      // 143: Ironfist of the Ogre
      {false, false, false, true, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false}};

  const static inline std::vector<uint32_t> artExp = {
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
      1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};

  enum class BONUSE : uint8_t {
    ATK,
    DEF,
    POW,
    KNO,
    MOR,
    LUK,
    SIGHT,
    UNDEAD_RAISE,
    MAGIC_RESISTANCE,
    MAGIC_RESISTANCE_LVL,
    BOOST,
    LEARN_BATTLE,
    SURRENDER_DISCOUNT,
    STACKS_SPEED,
    MOVEMENT_LAND,
    MOVEMENT_SEA,
    FLYING_MOVEMENT,
    MANA_REGENERATION,
    SPELL_DURATION,
    SPELL_DAMAGE_AIR,
    SPELL_DAMAGE_EARTH,
    SPELL_DAMAGE_FIRE,
    SPELL_DAMAGE_WATER,
    BLOCK_MAGIC_ABOVE,
    MAX_MOR,
    MAX_LUK,
    SPELLS_OF_SCHOOL,
    WATER_WALKING,
    NO_DISTANCE_PENALTY,
    NO_WALL_PENALTY,
    SPELL_IMMUNITY,
    STACK_HEALTH,
    GENERATE_RESOURCE_CRYSTAL,
    GENERATE_RESOURCE_GEM,
    GENERATE_RESOURCE_MERCURY,
    GENERATE_RESOURCE_ORE,
    GENERATE_RESOURCE_SULFUR,
    GENERATE_RESOURCE_WOOD,
    GENERATE_RESOURCE_GOLD,
    CREATURE_GROWTH_2,
    CREATURE_GROWTH_3,
    CREATURE_GROWTH_4,
    CREATURE_GROWTH_5,
    CREATURE_GROWTH_6,
    WHIRLPOOL_PROTECTION,
    SPELL,
    SPELLS_OF_LEVEL,
    BATTLE_NO_FLEEING,
    BLOCK_ALL_MAGIC,
    DRAGON_ATK,
    DRAGON_DEF,
  };

  const static inline std::vector<std::vector<std::pair<uint8_t, int32_t>>>
      artBonuse = {
          /* 0-6: 无加成 */
          {},
          {},
          {},
          {},
          {},
          {},
          {},

          /* 7-12: 攻击加成系列 */
          {{static_cast<uint8_t>(BONUSE::ATK), 2}}, // 7
          {{static_cast<uint8_t>(BONUSE::ATK), 3}}, // 8
          {{static_cast<uint8_t>(BONUSE::ATK), 4}}, // 9
          {{static_cast<uint8_t>(BONUSE::ATK), 5}}, // 10
          {{static_cast<uint8_t>(BONUSE::ATK), 6}}, // 11
          {{static_cast<uint8_t>(BONUSE::ATK), 12}, // 12
           {static_cast<uint8_t>(BONUSE::DEF), -3}},

          /* 13-18: 防御加成系列 */
          {{static_cast<uint8_t>(BONUSE::DEF), 2}}, // 13
          {{static_cast<uint8_t>(BONUSE::DEF), 3}}, // 14
          {{static_cast<uint8_t>(BONUSE::DEF), 4}}, // 15
          {{static_cast<uint8_t>(BONUSE::DEF), 5}}, // 16
          {{static_cast<uint8_t>(BONUSE::DEF), 6}}, // 17
          {{static_cast<uint8_t>(BONUSE::ATK), -3}, // 18
           {static_cast<uint8_t>(BONUSE::DEF), 12}},

          /* 19-24: 知识加成系列 */
          {{static_cast<uint8_t>(BONUSE::KNO), 1}}, // 19
          {{static_cast<uint8_t>(BONUSE::KNO), 2}}, // 20
          {{static_cast<uint8_t>(BONUSE::KNO), 3}}, // 21
          {{static_cast<uint8_t>(BONUSE::KNO), 4}}, // 22
          {{static_cast<uint8_t>(BONUSE::KNO), 5}}, // 23
          {{static_cast<uint8_t>(BONUSE::KNO), 10}, // 24
           {static_cast<uint8_t>(BONUSE::POW), -2}},

          /* 25-30: 力量加成系列 */
          {{static_cast<uint8_t>(BONUSE::KNO), 2}}, // 25
          {{static_cast<uint8_t>(BONUSE::POW), 2}}, // 26
          {{static_cast<uint8_t>(BONUSE::POW), 3}}, // 27
          {{static_cast<uint8_t>(BONUSE::POW), 4}}, // 28
          {{static_cast<uint8_t>(BONUSE::POW), 5}}, // 29
          {{static_cast<uint8_t>(BONUSE::KNO), -2}, // 30
           {static_cast<uint8_t>(BONUSE::POW), 10}},

          /* 31-36: 全属性加成系列 */
          {{static_cast<uint8_t>(BONUSE::ATK), 1}, // 31
           {static_cast<uint8_t>(BONUSE::DEF), 1},
           {static_cast<uint8_t>(BONUSE::KNO), 1},
           {static_cast<uint8_t>(BONUSE::POW), 1}},
          {{static_cast<uint8_t>(BONUSE::ATK), 2}, // 32
           {static_cast<uint8_t>(BONUSE::DEF), 2},
           {static_cast<uint8_t>(BONUSE::KNO), 2},
           {static_cast<uint8_t>(BONUSE::POW), 2}},
          {{static_cast<uint8_t>(BONUSE::ATK), 3}, // 33
           {static_cast<uint8_t>(BONUSE::DEF), 3},
           {static_cast<uint8_t>(BONUSE::KNO), 3},
           {static_cast<uint8_t>(BONUSE::POW), 3}},
          {{static_cast<uint8_t>(BONUSE::ATK), 4}, // 34
           {static_cast<uint8_t>(BONUSE::DEF), 4},
           {static_cast<uint8_t>(BONUSE::KNO), 4},
           {static_cast<uint8_t>(BONUSE::POW), 4}},
          {{static_cast<uint8_t>(BONUSE::ATK), 5}, // 35
           {static_cast<uint8_t>(BONUSE::DEF), 5},
           {static_cast<uint8_t>(BONUSE::KNO), 5},
           {static_cast<uint8_t>(BONUSE::POW), 5}},
          {{static_cast<uint8_t>(BONUSE::ATK), 6}, // 36
           {static_cast<uint8_t>(BONUSE::DEF), 6},
           {static_cast<uint8_t>(BONUSE::KNO), 6},
           {static_cast<uint8_t>(BONUSE::POW), 6}},

          /* 37-40: 攻防双加成系列 */
          {{static_cast<uint8_t>(BONUSE::ATK), 1}, // 37
           {static_cast<uint8_t>(BONUSE::DEF), 1}},
          {{static_cast<uint8_t>(BONUSE::ATK), 2}, // 38
           {static_cast<uint8_t>(BONUSE::DEF), 2}},
          {{static_cast<uint8_t>(BONUSE::ATK), 3}, // 39
           {static_cast<uint8_t>(BONUSE::DEF), 3}},
          {{static_cast<uint8_t>(BONUSE::ATK), 4}, // 40
           {static_cast<uint8_t>(BONUSE::DEF), 4}},

          /* 41-44: 知力双加成系列 */
          {{static_cast<uint8_t>(BONUSE::KNO), 1}, // 41
           {static_cast<uint8_t>(BONUSE::POW), 1}},
          {{static_cast<uint8_t>(BONUSE::KNO), 2}, // 42
           {static_cast<uint8_t>(BONUSE::POW), 2}},
          {{static_cast<uint8_t>(BONUSE::KNO), 3}, // 43
           {static_cast<uint8_t>(BONUSE::POW), 3}},
          {{static_cast<uint8_t>(BONUSE::KNO), 4}, // 44
           {static_cast<uint8_t>(BONUSE::POW), 4}},

          /* 45: 士气幸运双加成 */
          {{static_cast<uint8_t>(BONUSE::MOR), 1}, // 45
           {static_cast<uint8_t>(BONUSE::LUK), 1}},

          /* 46-53: 单一加成系列 */
          {{static_cast<uint8_t>(BONUSE::LUK), 1}},           // 46
          {{static_cast<uint8_t>(BONUSE::LUK), 1}},           // 47
          {{static_cast<uint8_t>(BONUSE::LUK), 1}},           // 48
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}, // 49
           {static_cast<uint8_t>(BONUSE::MOR), 1}},
          {{static_cast<uint8_t>(BONUSE::MOR), 1}},   // 50
          {{static_cast<uint8_t>(BONUSE::MOR), 1}},   // 51
          {{static_cast<uint8_t>(BONUSE::SIGHT), 1}}, // 52
          {{static_cast<uint8_t>(BONUSE::SIGHT), 1}}, // 53

          /* 54-59: 亡灵/抗魔系列 */
          {{static_cast<uint8_t>(BONUSE::UNDEAD_RAISE), 5}},      // 54
          {{static_cast<uint8_t>(BONUSE::UNDEAD_RAISE), 10}},     // 55
          {{static_cast<uint8_t>(BONUSE::UNDEAD_RAISE), 15}},     // 56
          {{static_cast<uint8_t>(BONUSE::MAGIC_RESISTANCE), 5}},  // 57
          {{static_cast<uint8_t>(BONUSE::MAGIC_RESISTANCE), 10}}, // 58
          {{static_cast<uint8_t>(BONUSE::MAGIC_RESISTANCE), 15}}, // 59

          /* 60-65: 战斗加成系列 */
          {{static_cast<uint8_t>(BONUSE::BOOST), 5}},         // 60
          {{static_cast<uint8_t>(BONUSE::BOOST), 10}},        // 61
          {{static_cast<uint8_t>(BONUSE::BOOST), 15}},        // 62
          {{static_cast<uint8_t>(BONUSE::LEARN_BATTLE), 5}},  // 63
          {{static_cast<uint8_t>(BONUSE::LEARN_BATTLE), 10}}, // 64
          {{static_cast<uint8_t>(BONUSE::LEARN_BATTLE), 15}}, // 65

          /* 66-69: 特殊效果系列 */
          {{static_cast<uint8_t>(BONUSE::SURRENDER_DISCOUNT), 10}}, // 66
          {{static_cast<uint8_t>(BONUSE::SURRENDER_DISCOUNT), 10}}, // 67
          {{static_cast<uint8_t>(BONUSE::SURRENDER_DISCOUNT), 10}}, // 68
          {{static_cast<uint8_t>(BONUSE::STACKS_SPEED), 1}},        // 69

          /* 70-72: 移动加成系列 */
          {{static_cast<uint8_t>(BONUSE::MOVEMENT_LAND), 300}}, // 70
          {{static_cast<uint8_t>(BONUSE::MOVEMENT_SEA), 300}},  // 71
          {{static_cast<uint8_t>(BONUSE::FLYING_MOVEMENT), 0}}, // 72

          /* 73-78: 魔法加成系列 */
          {{static_cast<uint8_t>(BONUSE::MANA_REGENERATION), 1}}, // 73
          {{static_cast<uint8_t>(BONUSE::MANA_REGENERATION), 2}}, // 74
          {{static_cast<uint8_t>(BONUSE::MANA_REGENERATION), 3}}, // 75
          {{static_cast<uint8_t>(BONUSE::SPELL_DURATION), 1}},    // 76
          {{static_cast<uint8_t>(BONUSE::SPELL_DURATION), 2}},    // 77
          {{static_cast<uint8_t>(BONUSE::SPELL_DURATION), 3}},    // 78

          /* 79-82: 元素伤害加成系列 */
          {{static_cast<uint8_t>(BONUSE::SPELL_DAMAGE_AIR), 50}},   // 79
          {{static_cast<uint8_t>(BONUSE::SPELL_DAMAGE_EARTH), 50}}, // 80
          {{static_cast<uint8_t>(BONUSE::SPELL_DAMAGE_FIRE), 50}},  // 81
          {{static_cast<uint8_t>(BONUSE::SPELL_DAMAGE_WATER), 50}}, // 82

          /* 83-85: 魔法抵抗系列 */
          {{static_cast<uint8_t>(BONUSE::BLOCK_MAGIC_ABOVE), 2}}, // 83
          {{static_cast<uint8_t>(BONUSE::MAX_MOR), 0}},           // 84
          {{static_cast<uint8_t>(BONUSE::MAX_LUK), 0}},           // 85

          /* 86-89: 学派魔法系列 */
          {{static_cast<uint8_t>(BONUSE::SPELLS_OF_SCHOOL), 0}}, // 86
          {{static_cast<uint8_t>(BONUSE::SPELLS_OF_SCHOOL), 1}}, // 87
          {{static_cast<uint8_t>(BONUSE::SPELLS_OF_SCHOOL), 2}}, // 88
          {{static_cast<uint8_t>(BONUSE::SPELLS_OF_SCHOOL), 3}}, // 89

          /* 90-93: 特殊能力系列 */
          {{static_cast<uint8_t>(BONUSE::WATER_WALKING), 0}},      // 90
          {{static_cast<uint8_t>(BONUSE::NO_DISTANCE_PENALTY), 0}, // 91
           {static_cast<uint8_t>(BONUSE::NO_WALL_PENALTY), 0}},
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}},      // 92
          {{static_cast<uint8_t>(BONUSE::MAGIC_RESISTANCE_LVL), 0}, // 93
           {static_cast<uint8_t>(BONUSE::MAGIC_RESISTANCE), 0}},

          /* 94-99: 部队加成系列 */
          {{static_cast<uint8_t>(BONUSE::STACK_HEALTH), 1}},    // 94
          {{static_cast<uint8_t>(BONUSE::STACK_HEALTH), 1}},    // 95
          {{static_cast<uint8_t>(BONUSE::STACK_HEALTH), 2}},    // 96
          {{static_cast<uint8_t>(BONUSE::STACKS_SPEED), 1}},    // 97
          {{static_cast<uint8_t>(BONUSE::MOVEMENT_LAND), 600}}, // 98
          {{static_cast<uint8_t>(BONUSE::STACKS_SPEED), 2}},    // 99

          /* 100-107: 魔法免疫系列（都是0值加成） */
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 100
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 101
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 102
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 103
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 104
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 105
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 106
          {{static_cast<uint8_t>(BONUSE::SPELL_IMMUNITY), 0}}, // 107

          /* 108: 士气幸运三加成 */
          {{static_cast<uint8_t>(BONUSE::MOR), 3}, // 108
           {static_cast<uint8_t>(BONUSE::LUK), 3}},

          /* 109-117: 资源生成系列 */
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_CRYSTAL), 1}}, // 109
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_GEM), 1}},     // 110
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_MERCURY), 1}}, // 111
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_ORE), 1}},     // 112
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_SULFUR), 1}},  // 113
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_WOOD), 1}},    // 114
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_GOLD), 1000}}, // 115
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_GOLD), 750}},  // 116
          {{static_cast<uint8_t>(BONUSE::GENERATE_RESOURCE_GOLD), 500}},  // 117

          /* 118-122: 生物成长系列 */
          {{static_cast<uint8_t>(BONUSE::CREATURE_GROWTH_2), 5}}, // 118
          {{static_cast<uint8_t>(BONUSE::CREATURE_GROWTH_3), 4}}, // 119
          {{static_cast<uint8_t>(BONUSE::CREATURE_GROWTH_4), 3}}, // 120
          {{static_cast<uint8_t>(BONUSE::CREATURE_GROWTH_5), 2}}, // 121
          {{static_cast<uint8_t>(BONUSE::CREATURE_GROWTH_6), 1}}, // 122

          /* 123: 航海家之帽复合加成 */
          {{static_cast<uint8_t>(BONUSE::WHIRLPOOL_PROTECTION), 0}, // 123
           {static_cast<uint8_t>(BONUSE::MOVEMENT_SEA), 500},
           {static_cast<uint8_t>(BONUSE::SPELL), 0},
           {static_cast<uint8_t>(BONUSE::SPELL), 0}},

          /* 124-128: 顶级宝物系列 */
          {{static_cast<uint8_t>(BONUSE::SPELLS_OF_LEVEL), 5}},   // 124
          {{static_cast<uint8_t>(BONUSE::BATTLE_NO_FLEEING), 0}}, // 125
          {{static_cast<uint8_t>(BONUSE::BLOCK_ALL_MAGIC), 0}},   // 126
          {{static_cast<uint8_t>(BONUSE::DRAGON_ATK), 5},         // 127
           {static_cast<uint8_t>(BONUSE::DRAGON_DEF), 5}},
          {{static_cast<uint8_t>(BONUSE::SPELL), 0}}, // 128
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
          {},
  };
};