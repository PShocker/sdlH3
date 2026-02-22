#pragma once
#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <algorithm>
#include <array>
#include <vector>

struct SpellSet {
  static void init();

  static void SummonBoat(std::any data);
  static void ScuttleBoat(std::any data);
  static void Visions(std::any data);
  static void ViewEarth(std::any data);
  static void Disguise(std::any data);
  static void ViewAir(std::any data);
  static void Fly(std::any data);
  static void WaterWalk(std::any data);
  static void DimensionDoor(std::any data);
  static void TownPortal(std::any data);
  static void Quicksand(std::any data);
  static void LandMine(std::any data);
  static void ForceField(std::any data);
  static void FireWall(std::any data);
  static void Earthquake(std::any data);
  static void MagicArrow(std::any data);
  static void IceBolt(std::any data);
  static void LightningBolt(std::any data);
  static void Implosion(std::any data);
  static void ChainLightning(std::any data);
  static void FrostRing(std::any data);
  static void Fireball(std::any data);
  static void Inferno(std::any data);
  static void MeteorShower(std::any data);
  static void DeathRipple(std::any data);
  static void DestroyUndead(std::any data);
  static void Armageddon(std::any data);
  static void Shield(std::any data);
  static void AirShield(std::any data);
  static void FireShield(std::any data);
  static void ProtectionfromAir(std::any data);
  static void ProtectionfromFire(std::any data);
  static void ProtectionfromWater(std::any data);
  static void ProtectionfromEarth(std::any data);
  static void AntiMagic(std::any data);
  static void Dispel(std::any data);
  static void MagicMirror(std::any data);
  static void Cure(std::any data);
  static void Resurrection(std::any data);
  static void AnimateDead(std::any data);
  static void Sacrifice(std::any data);
  static void Bless(std::any data);
  static void Curse(std::any data);
  static void Bloodlust(std::any data);
  static void Precision(std::any data);
  static void Weakness(std::any data);
  static void StoneSkin(std::any data);
  static void DisruptingRay(std::any data);
  static void Prayer(std::any data);
  static void Mirth(std::any data);
  static void Sorrow(std::any data);
  static void Fortune(std::any data);
  static void Misfortune(std::any data);
  static void Haste(std::any data);
  static void Slow(std::any data);
  static void Slayer(std::any data);
  static void Frenzy(std::any data);
  static void TitansLightningBolt(std::any data);
  static void Counterstrike(std::any data);
  static void Berserk(std::any data);
  static void Hypnotize(std::any data);
  static void Forgetfulness(std::any data);
  static void Blind(std::any data);
  static void Teleport(std::any data);
  static void RemoveObstacle(std::any data);
  static void MirrorImage(std::any data);
  static void SummonFireElemental(std::any data);
  static void SummonEarthElemental(std::any data);
  static void SummonWaterElemental(std::any data);
  static void SummonAirElemental(std::any data);

  static inline std::vector<const SpellI *> spellsAdv = {};

  static inline std::vector<const SpellI *> spellsBat = {};

  static inline std::vector<const SpellI *> spellsCre = {};

  static inline std::array<std::vector<const SpellI *>, 4> spellsSchool = {};

  static inline std::array<std::vector<const SpellI *>, 6> spellsLvl = {};

  static inline std::vector<SpellI> spells = {
      // === 冒险魔法 (Adventure Spells) 0-9 ===
      {
          .index = 0,                            // 召船术
          .school = {false, true, false, false}, // 水系
          .manaCost = {8, 7, 7, 7},
          .level = 1,
          .type = Enum::SPELL_TYPE_ADV, // 冒险魔法
          .func = SummonBoat,
      },
      {
          .index = 1,                            // 摧毁船只
          .school = {false, true, false, false}, // 水系
          .manaCost = {8, 6, 6, 6},
          .level = 2,
          .type = Enum::SPELL_TYPE_ADV,
          .func = ScuttleBoat,
      },
    //   {
    //       .index = 2,                         // 透视之眼
    //       .school = {true, true, true, true}, // 全学派
    //       .manaCost = {4, 2, 2, 2},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = Visions,
    //   },
    //   {
    //       .index = 3,                            // 透视大地
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {2, 1, 1, 1},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = ViewEarth,
    //   },
    //   {
    //       .index = 4,                            // 伪装大法
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {4, 2, 2, 2},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = Disguise,
    //   },
    //   {
    //       .index = 5,                            // 透视大气
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {2, 1, 1, 1},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = ViewAir,
    //   },
    //   {
    //       .index = 6,                            // 飞行奇术
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {20, 15, 15, 15},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = Fly,
    //   },
    //   {
    //       .index = 7,                            // 凌波微步
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {12, 8, 8, 8},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = WaterWalk,
    //   },
    //   {
    //       .index = 8,                            // 异次元之门
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {25, 20, 20, 20},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = DimensionDoor,
    //   },
    //   {
    //       .index = 9,                            // 时空之门
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_ADV,
    //       .func = TownPortal,
    //   },

    //   // === 战斗魔法 (Combat Spells) 10-69 ===
    //   {
    //       .index = 10,                           // 流沙陷阱
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {8, 6, 6, 6},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Quicksand,
    //   },
    //   {
    //       .index = 11,                           // 埋设地雷
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {18, 15, 15, 15},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = LandMine,
    //   },
    //   {
    //       .index = 12,                           // 大力神盾
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {12, 9, 9, 9},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = ForceField,
    //   },
    //   {
    //       .index = 13,                           // 烈火魔墙
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {8, 6, 6, 6},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = FireWall,
    //   },
    //   {
    //       .index = 14,                           // 地动山摇
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {20, 17, 17, 17},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Earthquake,
    //   },
    //   {
    //       .index = 15,                        // 魔法神箭
    //       .school = {true, true, true, true}, // 全学派
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = MagicArrow,
    //   },
    //   {
    //       .index = 16,                           // 霹雳寒冰
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {8, 6, 6, 6},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = IceBolt,
    //   },
    //   {
    //       .index = 17,                           // 霹雳闪电
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {10, 8, 8, 8},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = LightningBolt,
    //   },
    //   {
    //       .index = 18,                           // 雷鸣爆弹
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {30, 25, 25, 25},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Implosion,
    //   },
    //   {
    //       .index = 19,                           // 连锁闪电
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {24, 20, 20, 20},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = ChainLightning,
    //   },
    //   {
    //       .index = 20,                           // 寒冰魔环
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {12, 9, 9, 9},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = FrostRing,
    //   },
    //   {
    //       .index = 21,                           // 连珠火球
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {15, 12, 12, 12},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Fireball,
    //   },
    //   {
    //       .index = 22,                           // 地狱烈焰
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Inferno,
    //   },
    //   {
    //       .index = 23,                           // 流星火雨
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = MeteorShower,
    //   },
    //   {
    //       .index = 24,                           // 死亡波纹
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {10, 8, 8, 8},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = DeathRipple,
    //   },
    //   {
    //       .index = 25,                           // 亡灵杀手
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {15, 12, 12, 12},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = DestroyUndead,
    //   },
    //   {
    //       .index = 26,                           // 末日审判
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {24, 20, 20, 20},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Armageddon,
    //   },
    //   {
    //       .index = 27,                           // 护体神盾
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Shield,
    //   },
    //   {
    //       .index = 28,                           // 大气神盾
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {12, 9, 9, 9},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = AirShield,
    //   },
    //   {
    //       .index = 29,                           // 烈火神盾
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = FireShield,
    //   },
    //   {
    //       .index = 30,                           // 御气奇术
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {7, 5, 5, 5},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = ProtectionfromAir,
    //   },
    //   {
    //       .index = 31,                           // 御火奇术
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = ProtectionfromFire,
    //   },
    //   {
    //       .index = 32,                           // 御水奇术
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = ProtectionfromWater,
    //   },
    //   {
    //       .index = 33,                           // 御土奇术
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {12, 9, 9, 9},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = ProtectionfromEarth,
    //   },
    //   {
    //       .index = 34,                           // 抗魔大法
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {15, 12, 12, 12},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = AntiMagic,
    //   },
    //   {
    //       .index = 35,                           // 驱魔大法
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Dispel,
    //   },
    //   {
    //       .index = 36,                           // 魔法神镜
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {25, 20, 20, 20},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = MagicMirror,
    //   },
    //   {
    //       .index = 37,                           // 疗伤
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {6, 5, 5, 5},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Cure,
    //   },
    //   {
    //       .index = 38,                           // 转世重生
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {20, 16, 16, 16},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Resurrection,
    //   },
    //   {
    //       .index = 39,                           // 聚灵奇术
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {15, 12, 12, 12},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = AnimateDead,
    //   },
    //   {
    //       .index = 40,                           // 牺牲
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {25, 20, 20, 20},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Sacrifice,
    //   },
    //   {
    //       .index = 41,                           // 圣灵佑佐
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Bless,
    //   },
    //   {
    //       .index = 42,                           // 恶咒附身
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {6, 5, 5, 5},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Curse,
    //   },
    //   {
    //       .index = 43,                           // 嗜血奇术
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Bloodlust,
    //   },
    //   {
    //       .index = 44,                           // 百发百中
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {8, 6, 6, 6},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Precision,
    //   },
    //   {
    //       .index = 45,                           // 虚弱无力
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {8, 6, 6, 6},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Weakness,
    //   },
    //   {
    //       .index = 46,                           // 护体石肤
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {5, 4, 4, 4},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = StoneSkin,
    //   },
    //   {
    //       .index = 47,                           // 毁灭之光
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {10, 8, 8, 8},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = DisruptingRay,
    //   },
    //   {
    //       .index = 48,                           // 祈祷
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Prayer,
    //   },
    //   {
    //       .index = 49,                           // 欢欣鼓舞
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {12, 9, 9, 9},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Mirth,
    //   },
    //   {
    //       .index = 50,                           // 悲痛欲绝
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Sorrow,
    //   },
    //   {
    //       .index = 51,                           // 幸运之神
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {7, 5, 5, 5},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Fortune,
    //   },
    //   {
    //       .index = 52,                           // 大难临头
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {12, 9, 9, 9},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Misfortune,
    //   },
    //   {
    //       .index = 53,                           // 攻击加速
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {6, 5, 5, 5},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Haste,
    //   },
    //   {
    //       .index = 54,                           // 迟缓大法
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {6, 5, 5, 5},
    //       .level = 1,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Slow,
    //   },
    //   {
    //       .index = 55,                           // 屠戮成性
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Slayer,
    //   },
    //   {
    //       .index = 56,                           // 孤注一掷
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {16, 12, 12, 12},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Frenzy,
    //   },
    //   {
    //       .index = 57,                           // 泰坦之箭
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {0, 0, 0, 0},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = TitansLightningBolt,
    //   },
    //   {
    //       .index = 58,                           // 反戈一击
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {24, 20, 20, 20},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Counterstrike,
    //   },
    //   {
    //       .index = 59,                           // 丧心病狂
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {20, 16, 16, 16},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Berserk,
    //   },
    //   {
    //       .index = 60,                           // 蛊惑人心
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {18, 15, 15, 15},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Hypnotize,
    //   },
    //   {
    //       .index = 61,                           // 失忆大法
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {12, 9, 9, 9},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Forgetfulness,
    //   },
    //   {
    //       .index = 62,                           // 双目失明
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {10, 8, 8, 8},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Blind,
    //   },
    //   {
    //       .index = 63,                           // 瞬间移动
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {15, 12, 6, 3},
    //       .level = 3,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = Teleport,
    //   },
    //   {
    //       .index = 64,                           // 驱除障碍
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {7, 5, 5, 5},
    //       .level = 2,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = RemoveObstacle,
    //   },
    //   {
    //       .index = 65,                           // 镜像大法
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {24, 20, 20, 20},
    //       .level = 4,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = MirrorImage,
    //   },
    //   {
    //       .index = 66,                           // 召唤火元素
    //       .school = {false, false, true, false}, // 火系
    //       .manaCost = {25, 20, 20, 20},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = SummonFireElemental,
    //   },
    //   {
    //       .index = 67,                           // 召唤土元素
    //       .school = {true, false, false, false}, // 土系
    //       .manaCost = {25, 20, 20, 20},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = SummonEarthElemental,
    //   },
    //   {
    //       .index = 68,                           // 召唤水元素
    //       .school = {false, true, false, false}, // 水系
    //       .manaCost = {25, 20, 20, 20},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = SummonWaterElemental,
    //   },
    //   {
    //       .index = 69,                           // 召唤气元素
    //       .school = {false, false, false, true}, // 气系
    //       .manaCost = {25, 20, 20, 20},
    //       .level = 5,
    //       .type = Enum::SPELL_TYPE_BAT,
    //       .func = SummonAirElemental,
    //   },
  };
};