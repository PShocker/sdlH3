#pragma once

#include <any>
#include <array>
#include <cstdint>
#include <vector>

void SummonBoat(std::any data);
void ScuttleBoat(std::any data);
void Visions(std::any data);
void ViewEarth(std::any data);
void Disguise(std::any data);
void ViewAir(std::any data);
void Fly(std::any data);
void WaterWalk(std::any data);
void DimensionDoor(std::any data);
void TownPortal(std::any data);
void Quicksand(std::any data);
void LandMine(std::any data);
void ForceField(std::any data);
void FireWall(std::any data);
void Earthquake(std::any data);
void MagicArrow(std::any data);
void IceBolt(std::any data);
void LightningBolt(std::any data);
void Implosion(std::any data);
void ChainLightning(std::any data);
void FrostRing(std::any data);
void Fireball(std::any data);
void Inferno(std::any data);
void MeteorShower(std::any data);
void DeathRipple(std::any data);
void DestroyUndead(std::any data);
void Armageddon(std::any data);
void Shield(std::any data);
void AirShield(std::any data);
void FireShield(std::any data);
void ProtectionfromAir(std::any data);
void ProtectionfromFire(std::any data);
void ProtectionfromWater(std::any data);
void ProtectionfromEarth(std::any data);
void AntiMagic(std::any data);
void Dispel(std::any data);
void MagicMirror(std::any data);
void Cure(std::any data);
void Resurrection(std::any data);
void AnimateDead(std::any data);
void Sacrifice(std::any data);
void Bless(std::any data);
void Curse(std::any data);
void Bloodlust(std::any data);
void Precision(std::any data);
void Weakness(std::any data);
void StoneSkin(std::any data);
void DisruptingRay(std::any data);
void Prayer(std::any data);
void Mirth(std::any data);
void Sorrow(std::any data);
void Fortune(std::any data);
void Misfortune(std::any data);
void Haste(std::any data);
void Slow(std::any data);
void Slayer(std::any data);
void Frenzy(std::any data);
void TitansLightningBolt(std::any data);
void Counterstrike(std::any data);
void Berserk(std::any data);
void Hypnotize(std::any data);
void Forgetfulness(std::any data);
void Blind(std::any data);
void Teleport(std::any data);
void RemoveObstacle(std::any data);
void MirrorImage(std::any data);
void SummonFireElemental(std::any data);
void SummonEarthElemental(std::any data);
void SummonWaterElemental(std::any data);
void SummonAirElemental(std::any data);

struct SpellCfg {

 enum class Spell : uint8_t {
    SummonBoat = 0,            // 0: 召船术
    ScuttleBoat = 1,           // 1: 摧毁船只
    Visions = 2,               // 2: 透视之眼
    ViewEarth = 3,             // 3: 透视大地
    Disguise = 4,              // 4: 伪装大法
    ViewAir = 5,              // 5: 透视大气 (复用ViewAir函数)
    Fly = 6,                   // 6: 飞行奇术
    WaterWalk = 7,             // 7: 凌波微步
    DimensionDoor = 8,         // 8: 异次元之门
    TownPortal = 9,            // 9: 时空之门
    
    Quicksand = 10,            // 10: 流沙陷阱
    LandMine = 11,             // 11: 埋设地雷
    ForceField = 12,           // 12: 大力神盾
    FireWall = 13,             // 13: 烈火魔墙
    Earthquake = 14,           // 14: 地动山摇
    MagicArrow = 15,           // 15: 魔法神箭
    IceBolt = 16,              // 16: 霹雳寒冰
    LightningBolt = 17,        // 17: 霹雳闪电
    Implosion = 18,            // 18: 雷鸣爆弹
    ChainLightning = 19,       // 19: 连锁闪电
    
    FrostRing = 20,            // 20: 寒冰魔环
    Fireball = 21,             // 21: 连珠火球
    Inferno = 22,              // 22: 地狱烈焰
    MeteorShower = 23,         // 23: 流星火雨
    DeathRipple = 24,          // 24: 死亡波纹
    DestroyUndead = 25,        // 25: 亡灵杀手
    Armageddon = 26,           // 26: 末日审判
    Shield = 27,               // 27: 护体神盾
    AirShield = 28,            // 28: 大气神盾
    FireShield = 29,           // 29: 烈火神盾
    
    ProtectionfromAir = 30,    // 30: 御气奇术
    ProtectionfromFire = 31,   // 31: 御火奇术
    ProtectionfromWater = 32,  // 32: 御水奇术
    ProtectionfromEarth = 33,  // 33: 御土奇术
    AntiMagic = 34,            // 34: 抗魔大法
    Dispel = 35,               // 35: 驱魔大法
    MagicMirror = 36,          // 36: 魔法神镜
    Cure = 37,                 // 37: 疗伤
    Resurrection = 38,         // 38: 转世重生
    AnimateDead = 39,          // 39: 聚灵奇术
    
    Sacrifice = 40,            // 40: 牺牲
    Bless = 41,                // 41: 圣灵佑佐
    Curse = 42,                // 42: 恶咒附身
    Bloodlust = 43,            // 43: 嗜血奇术
    Precision = 44,            // 44: 百发百中
    Weakness = 45,             // 45: 虚弱无力
    StoneSkin = 46,            // 46: 护体石肤
    DisruptingRay = 47,        // 47: 毁灭之光
    Prayer = 48,               // 48: 祈祷
    Mirth = 49,                // 49: 欢欣鼓舞
    
    Sorrow = 50,               // 50: 悲痛欲绝
    Fortune = 51,              // 51: 幸运之神
    Misfortune = 52,           // 52: 大难临头
    Haste = 53,                // 53: 攻击加速
    Slow = 54,                 // 54: 迟缓大法
    Slayer = 55,               // 55: 屠戮成性
    Frenzy = 56,               // 56: 孤注一掷
    TitansLightningBolt = 57,  // 57: 泰坦之箭
    Counterstrike = 58,        // 58: 反戈一击
    Berserk = 59,              // 59: 丧心病狂
    
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

  const static inline std::vector<std::vector<bool>> SpellSchool = {
      // 0: 召船术 (Summon Boat)
      {false, true, false, false},
      // 1: 摧毁船只 (Scuttle Boat)
      {false, true, false, false},
      // 2: 透视之眼 (View Air)
      {true, true, true, true},
      // 3: 透视大地 (View Earth)
      {true, false, false, false},
      // 4: 伪装大法 (Disguise)
      {false, false, false, true},
      // 5: 透视大气 (View Air)
      {false, false, false, true},
      // 6: 飞行奇术 (Fly)
      {false, false, false, true},
      // 7: 凌波微步 (Water Walk)
      {false, true, false, false},
      // 8: 异次元之门 (Dimension Door)
      {false, false, false, true},
      // 9: 时空之门 (Town Portal)
      {true, false, false, false},
      // 10: 流沙陷阱 (Quicksand)
      {true, false, false, false},
      // 11: 埋设地雷 (Land Mine)
      {false, false, true, false},
      // 12: 大力神盾 (Force Field)
      {true, false, false, false},
      // 13: 烈火魔墙 (Fire Wall)
      {false, false, true, false},
      // 14: 地动山摇 (Earthquake)
      {true, false, false, false},
      // 15: 魔法神箭 (Magic Arrow)
      {true, true, true, true},
      // 16: 霹雳寒冰 (Ice Bolt)
      {false, true, false, false},
      // 17: 霹雳闪电 (Lightning Bolt)
      {false, false, false, true},
      // 18: 雷鸣爆弹 (Implosion)
      {true, false, false, false},
      // 19: 连锁闪电 (Chain Lightning)
      {false, false, false, true},
      // 20: 寒冰魔环 (Frost Ring)
      {false, true, false, false},
      // 21: 连珠火球 (Fireball)
      {false, false, true, false},
      // 22: 地狱烈焰 (Inferno)
      {false, false, true, false},
      // 23: 流星火雨 (Meteor Shower)
      {true, false, false, false},
      // 24: 死亡波纹 (Death Ripple)
      {true, false, false, false},
      // 25: 亡灵杀手 (Destroy Undead)
      {false, false, false, true},
      // 26: 末日审判 (Armageddon)
      {false, false, true, false},
      // 27: 护体神盾 (Shield)
      {true, false, false, false},
      // 28: 大气神盾 (Air Shield)
      {false, false, false, true},
      // 29: 烈火神盾 (Fire Shield)
      {false, false, true, false},
      // 30: 御气奇术 (Protection from Air)
      {false, false, false, true},
      // 31: 御火奇术 (Protection from Fire)
      {false, false, true, false},
      // 32: 御水奇术 (Protection from Water)
      {false, true, false, false},
      // 33: 御土奇术 (Protection from Earth)
      {true, false, false, false},
      // 34: 抗魔大法 (Anti-Magic)
      {true, false, false, false},
      // 35: 驱魔大法 (Dispel)
      {false, true, false, false},
      // 36: 魔法神镜 (Magic Mirror)
      {false, false, false, true},
      // 37: 疗伤 (Cure)
      {false, true, false, false},
      // 38: 转世重生 (Resurrection)
      {true, false, false, false},
      // 39: 聚灵奇术 (Animate Dead)
      {true, false, false, false},
      // 40: 牺牲 (Sacrifice)
      {false, false, true, false},
      // 41: 圣灵佑佐 (Bless)
      {false, true, false, false},
      // 42: 恶咒附身 (Curse)
      {false, false, true, false},
      // 43: 嗜血奇术 (Bloodlust)
      {false, false, true, false},
      // 44: 百发百中 (Precision)
      {false, false, false, true},
      // 45: 虚弱无力 (Weakness)
      {false, true, false, false},
      // 46: 护体石肤 (Stone Skin)
      {true, false, false, false},
      // 47: 毁灭之光 (Disrupting Ray)
      {false, false, false, true},
      // 48: 祈祷 (Prayer)
      {false, true, false, false},
      // 49: 欢欣鼓舞 (Mirth)
      {false, true, false, false},
      // 50: 悲痛欲绝 (Sorrow)
      {true, false, false, false},
      // 51: 幸运之神 (Fortune)
      {false, false, false, true},
      // 52: 大难临头 (Misfortune)
      {false, false, true, false},
      // 53: 攻击加速 (Haste)
      {false, false, false, true},
      // 54: 迟缓大法 (Slow)
      {true, false, false, false},
      // 55: 屠戮成性 (Slayer)
      {false, false, true, false},
      // 56: 孤注一掷 (Frenzy)
      {false, false, true, false},
      // 57: 泰坦之箭 (Titan's Lightning Bolt)
      {false, false, false, true},
      // 58: 反戈一击 (Counterstrike)
      {false, false, false, true},
      // 59: 丧心病狂 (Berserk)
      {false, false, true, false},
      // 60: 蛊惑人心 (Hypnotize)
      {false, false, false, true},
      // 61: 失忆大法 (Forgetfulness)
      {false, true, false, false},
      // 62: 双目失明 (Blind)
      {false, false, true, false},
      // 63: 瞬间移动 (Teleport)
      {false, true, false, false},
      // 64: 驱除障碍 (Remove Obstacle)
      {false, true, false, false},
      // 65: 镜像大法 (Mirror Image)
      {false, true, false, false},
      // 66: 召唤火元素 (Summon Fire Elemental)
      {false, false, true, false},
      // 67: 召唤土元素 (Summon Earth Elemental)
      {true, false, false, false},
      // 68: 召唤水元素 (Summon Water Elemental)
      {false, true, false, false},
      // 69: 召唤气元素 (Summon Air Elemental)
      {false, false, false, true}};

  const static inline std::vector<std::array<uint16_t, 4>> SpellCost = {
      std::array<uint16_t, 4>{8, 7, 7, 7},     // 0: 召船术
      std::array<uint16_t, 4>{8, 6, 6, 6},     // 1: 摧毁船只
      std::array<uint16_t, 4>{4, 2, 2, 2},     // 2: 透视之眼
      std::array<uint16_t, 4>{2, 1, 1, 1},     // 3: 透视大地
      std::array<uint16_t, 4>{4, 2, 2, 2},     // 4: 伪装大法
      std::array<uint16_t, 4>{2, 1, 1, 1},     // 5: 透视大气
      std::array<uint16_t, 4>{20, 15, 15, 15}, // 6: 飞行奇术
      std::array<uint16_t, 4>{12, 8, 8, 8},    // 7: 凌波微步
      std::array<uint16_t, 4>{25, 20, 20, 20}, // 8: 异次元之门
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 9: 时空之门

      // 战斗魔法 (10-69)
      std::array<uint16_t, 4>{8, 6, 6, 6},     // 10: 流沙陷阱
      std::array<uint16_t, 4>{18, 15, 15, 15}, // 11: 埋设地雷
      std::array<uint16_t, 4>{12, 9, 9, 9},    // 12: 大力神盾
      std::array<uint16_t, 4>{8, 6, 6, 6},     // 13: 烈火魔墙
      std::array<uint16_t, 4>{20, 17, 17, 17}, // 14: 地动山摇
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 15: 魔法神箭
      std::array<uint16_t, 4>{8, 6, 6, 6},     // 16: 霹雳寒冰
      std::array<uint16_t, 4>{10, 8, 8, 8},    // 17: 霹雳闪电
      std::array<uint16_t, 4>{30, 25, 25, 25}, // 18: 雷鸣爆弹
      std::array<uint16_t, 4>{24, 20, 20, 20}, // 19: 连锁闪电
      std::array<uint16_t, 4>{12, 9, 9, 9},    // 20: 寒冰魔环
      std::array<uint16_t, 4>{15, 12, 12, 12}, // 21: 连珠火球
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 22: 地狱烈焰
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 23: 流星火雨
      std::array<uint16_t, 4>{10, 8, 8, 8},    // 24: 死亡波纹
      std::array<uint16_t, 4>{15, 12, 12, 12}, // 25: 亡灵杀手
      std::array<uint16_t, 4>{24, 20, 20, 20}, // 26: 末日审判
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 27: 护体神盾
      std::array<uint16_t, 4>{12, 9, 9, 9},    // 28: 大气神盾
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 29: 烈火神盾
      std::array<uint16_t, 4>{7, 5, 5, 5},     // 30: 御气奇术
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 31: 御火奇术
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 32: 御水奇术
      std::array<uint16_t, 4>{12, 9, 9, 9},    // 33: 御土奇术
      std::array<uint16_t, 4>{15, 12, 12, 12}, // 34: 抗魔大法
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 35: 驱魔大法
      std::array<uint16_t, 4>{25, 20, 20, 20}, // 36: 魔法神镜
      std::array<uint16_t, 4>{6, 5, 5, 5},     // 37: 疗伤
      std::array<uint16_t, 4>{20, 16, 16, 16}, // 38: 转世重生
      std::array<uint16_t, 4>{15, 12, 12, 12}, // 39: 聚灵奇术
      std::array<uint16_t, 4>{25, 20, 20, 20}, // 40: 牺牲
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 41: 圣灵佑佐
      std::array<uint16_t, 4>{6, 5, 5, 5},     // 42: 恶咒附身
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 43: 嗜血奇术
      std::array<uint16_t, 4>{8, 6, 6, 6},     // 44: 百发百中
      std::array<uint16_t, 4>{8, 6, 6, 6},     // 45: 虚弱无力
      std::array<uint16_t, 4>{5, 4, 4, 4},     // 46: 护体石肤
      std::array<uint16_t, 4>{10, 8, 8, 8},    // 47: 毁灭之光
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 48: 祈祷
      std::array<uint16_t, 4>{12, 9, 9, 9},    // 49: 欢欣鼓舞
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 50: 悲痛欲绝
      std::array<uint16_t, 4>{7, 5, 5, 5},     // 51: 幸运之神
      std::array<uint16_t, 4>{12, 9, 9, 9},    // 52: 大难临头
      std::array<uint16_t, 4>{6, 5, 5, 5},     // 53: 攻击加速
      std::array<uint16_t, 4>{6, 5, 5, 5},     // 54: 迟缓大法
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 55: 屠戮成性
      std::array<uint16_t, 4>{16, 12, 12, 12}, // 56: 孤注一掷
      std::array<uint16_t, 4>{0, 0, 0, 0},     // 57: 泰坦之箭 (免费)
      std::array<uint16_t, 4>{24, 20, 20, 20}, // 58: 反戈一击
      std::array<uint16_t, 4>{20, 16, 16, 16}, // 59: 丧心病狂
      std::array<uint16_t, 4>{18, 15, 15, 15}, // 60: 蛊惑人心
      std::array<uint16_t, 4>{12, 9, 9, 9},    // 61: 失忆大法
      std::array<uint16_t, 4>{10, 8, 8, 8},    // 62: 双目失明
      std::array<uint16_t, 4>{15, 12, 6, 3},   // 63: 瞬间移动 (专家级消耗减少)
      std::array<uint16_t, 4>{7, 5, 5, 5},     // 64: 驱除障碍
      std::array<uint16_t, 4>{24, 20, 20, 20}, // 65: 镜像大法
      std::array<uint16_t, 4>{25, 20, 20, 20}, // 66: 召唤火元素
      std::array<uint16_t, 4>{25, 20, 20, 20}, // 67: 召唤土元素
      std::array<uint16_t, 4>{25, 20, 20, 20}, // 68: 召唤水元素
      std::array<uint16_t, 4>{25, 20, 20, 20}  // 69: 召唤气元素
  };

  const static inline std::vector<uint8_t> SpellLevel = {
      // === 冒险魔法 (Adventure Spells) 0-9 ===
      1, // 0: 召船术 (Summon Boat) - 水系1级
      2, // 1: 摧毁船只 (Scuttle Boat) - 水系2级
      2, // 2: 透视之眼 (View Air) - 气系2级（全学派）
      1, // 3: 透视大地 (View Earth) - 土系1级
      2, // 4: 伪装大法 (Disguise) - 气系2级
      1, // 5: 透视大气 (View Air) - 气系1级
      5, // 6: 飞行奇术 (Fly) - 气系5级（高级空间魔法）
      4, // 7: 凌波微步 (Water Walk) - 水系4级
      5, // 8: 异次元之门 (Dimension Door) - 气系5级（顶级空间魔法）
      4, // 9: 时空之门 (Town Portal) - 土系4级（城镇传送）

      // === 战斗魔法 (Combat Spells) 10-19 ===
      2, // 10: 流沙陷阱 (Quicksand) - 土系2级
      3, // 11: 埋设地雷 (Land Mine) - 火系3级
      3, // 12: 大力神盾 (Force Field) - 土系3级
      2, // 13: 烈火魔墙 (Fire Wall) - 火系2级
      3, // 14: 地动山摇 (Earthquake) - 土系3级（地形破坏）
      1, // 15: 魔法神箭 (Magic Arrow) - 全学派1级（基础伤害）
      2, // 16: 霹雳寒冰 (Ice Bolt) - 水系2级
      2, // 17: 霹雳闪电 (Lightning Bolt) - 气系2级
      5, // 18: 雷鸣爆弹 (Implosion) - 土系5级（单体最高伤害）
      4, // 19: 连锁闪电 (Chain Lightning) - 气系4级

      // === 战斗魔法续 20-29 ===
      3, // 20: 寒冰魔环 (Frost Ring) - 水系3级（范围冰伤）
      3, // 21: 连珠火球 (Fireball) - 火系3级
      4, // 22: 地狱烈焰 (Inferno) - 火系4级（直线火焰）
      4, // 23: 流星火雨 (Meteor Shower) - 土系4级（范围伤害）
      2, // 24: 死亡波纹 (Death Ripple) - 土系2级（对非亡灵）
      3, // 25: 亡灵杀手 (Destroy Undead) - 气系3级（对亡灵特攻）
      4, // 26: 末日审判 (Armageddon) - 火系4级（全屏伤害）
      1, // 27: 护体神盾 (Shield) - 土系1级（防御+）
      3, // 28: 大气神盾 (Air Shield) - 气系3级（远程防御）
      4, // 29: 烈火神盾 (Fire Shield) - 火系4级（近战反弹）

      // === 防御魔法 (Protection Spells) 30-39 ===
      2, // 30: 御气奇术 (Protection from Air) - 气系2级
      1, // 31: 御火奇术 (Protection from Fire) - 火系1级
      1, // 32: 御水奇术 (Protection from Water) - 水系1级
      3, // 33: 御土奇术 (Protection from Earth) - 土系3级
      3, // 34: 抗魔大法 (Anti-Magic) - 土系3级（魔法抗性）
      1, // 35: 驱魔大法 (Dispel) - 水系1级（驱散魔法）
      5, // 36: 魔法神镜 (Magic Mirror) - 气系5级（反射魔法）
      1, // 37: 疗伤 (Cure) - 水系1级（治疗）
      4, // 38: 转世重生 (Resurrection) - 土系4级（复活）
      3, // 39: 聚灵奇术 (Animate Dead) - 土系3级（召唤亡灵）

      // === 战斗魔法续 40-49 ===
      5, // 40: 牺牲 (Sacrifice) - 火系5级（以兵换兵）
      1, // 41: 圣灵佑佐 (Bless) - 水系1级（攻击最大化）
      1, // 42: 恶咒附身 (Curse) - 火系1级（攻击最小化）
      1, // 43: 嗜血奇术 (Bloodlust) - 火系1级（攻击+）
      2, // 44: 百发百中 (Precision) - 气系2级（远程攻击+）
      2, // 45: 虚弱无力 (Weakness) - 水系2级（攻击-）
      1, // 46: 护体石肤 (Stone Skin) - 土系1级（防御+）
      2, // 47: 毁灭之光 (Disrupting Ray) - 气系2级（降低防御）
      4, // 48: 祈祷 (Prayer) - 水系4级（全属性+）
      3, // 49: 欢欣鼓舞 (Mirth) - 水系3级（士气+）

      // === 状态魔法 (Status Spells) 50-59 ===
      4, // 50: 悲痛欲绝 (Sorrow) - 土系4级（士气-）
      2, // 51: 幸运之神 (Fortune) - 气系2级（幸运+）
      3, // 52: 大难临头 (Misfortune) - 火系3级（幸运-）
      1, // 53: 攻击加速 (Haste) - 气系1级（速度+）
      1, // 54: 迟缓大法 (Slow) - 土系1级（速度-）
      4, // 55: 屠戮成性 (Slayer) - 火系4级（对特定种族伤害+）
      4, // 56: 孤注一掷 (Frenzy) - 火系4级（攻击+防御-）
      5, // 57: 泰坦之箭 (Titan's Lightning Bolt) - 气系5级（神器，无消耗）
      4, // 58: 反戈一击 (Counterstrike) - 气系4级（反击次数+）
      4, // 59: 丧心病狂 (Berserk) - 火系4级（混乱攻击）

      // === 控制魔法和召唤魔法 60-69 ===
      3, // 60: 蛊惑人心 (Hypnotize) - 气系3级（控制敌方单位）
      3, // 61: 失忆大法 (Forgetfulness) - 水系3级（禁止远程攻击）
      2, // 62: 双目失明 (Blind) - 火系2级（致盲）
      3, // 63: 瞬间移动 (Teleport) - 水系3级（单位传送）
      2, // 64: 驱除障碍 (Remove Obstacle) - 水系2级
      4, // 65: 镜像大法 (Mirror Image) - 水系4级（创造镜像）
      5, // 66: 召唤火元素 (Summon Fire Elemental) - 火系5级
      5, // 67: 召唤土元素 (Summon Earth Elemental) - 土系5级
      5, // 68: 召唤水元素 (Summon Water Elemental) - 水系5级
      5, // 69: 召唤气元素 (Summon Air Elemental) - 气系5级

      // === 特殊/扩展魔法 70-80 ===
      3, // 70: 石化之眼 (Stone Gaze) - 特殊3级（概率石化）
      0, // 71: 剧毒 (Poison) - 特殊0级（毒性攻击，非标准魔法）
      0, // 72: 束缚 (Bind) - 特殊0级（限制移动，非标准魔法）
      2, // 73: 疾病 (Disease) - 特殊2级（降低生命值）
      4, // 74: 麻痹 (Paralyze) - 特殊4级（无法行动）
      5, // 75: 衰老 (Aging) - 特殊5级（按百分比减少生命）
      0, // 76: 死亡之雾 (Death Cloud) - 特殊0级（持续伤害）
      0, // 77: 霹雳 (Thunderbolt) - 特殊0级（雷击）
      0, // 78: 去除辅助魔法 (Remove Beneficial) - 特殊0级
      0, // 79: 死亡之眼 (Death Stare) - 特殊0级（死神之眼能力）
      0  // 80: 毒液 (Venom) - 特殊0级（毒性攻击）
  };

  static const inline std::vector<uint8_t> SpellLevels[6] = {
      {71, 72, 76, 77, 78, 79, 80},                                     // 等级0
      {0, 3, 5, 15, 27, 31, 32, 35, 37, 41, 42, 43, 46, 53, 54},        // 等级1
      {1, 2, 4, 10, 13, 16, 17, 24, 30, 44, 45, 47, 51, 62, 64, 73},    // 等级2
      {11, 12, 14, 20, 21, 25, 28, 33, 34, 39, 49, 52, 60, 61, 63, 70}, // 等级3
      {7, 9, 19, 22, 23, 26, 29, 38, 48, 50, 55, 56, 58, 59, 65, 74},   // 等级4
      {6, 8, 18, 36, 40, 57, 66, 67, 68, 69, 75}                        // 等级5
  };

  const static inline std::vector<void (*)(std::any)> SpellFunc = {
      &SummonBoat,    // 0: 召船术
      &ScuttleBoat,   // 1: 摧毁船只
      &Visions,       // 2: 透视之眼
      &ViewEarth,     // 3: 透视大地
      &Disguise,      // 4: 伪装大法
      &ViewAir,       // 5: 透视大气 
      &Fly,           // 6: 飞行奇术
      &WaterWalk,     // 7: 凌波微步
      &DimensionDoor, // 8: 异次元之门
      &TownPortal,    // 9: 时空之门

      &Quicksand,      // 10: 流沙陷阱
      &LandMine,       // 11: 埋设地雷
      &ForceField,     // 12: 大力神盾
      &FireWall,       // 13: 烈火魔墙
      &Earthquake,     // 14: 地动山摇
      &MagicArrow,     // 15: 魔法神箭
      &IceBolt,        // 16: 霹雳寒冰
      &LightningBolt,  // 17: 霹雳闪电
      &Implosion,      // 18: 雷鸣爆弹
      &ChainLightning, // 19: 连锁闪电

      &FrostRing,     // 20: 寒冰魔环
      &Fireball,      // 21: 连珠火球
      &Inferno,       // 22: 地狱烈焰
      &MeteorShower,  // 23: 流星火雨
      &DeathRipple,   // 24: 死亡波纹
      &DestroyUndead, // 25: 亡灵杀手
      &Armageddon,    // 26: 末日审判
      &Shield,        // 27: 护体神盾
      &AirShield,     // 28: 大气神盾
      &FireShield,    // 29: 烈火神盾

      &ProtectionfromAir,   // 30: 御气奇术
      &ProtectionfromFire,  // 31: 御火奇术
      &ProtectionfromWater, // 32: 御水奇术
      &ProtectionfromEarth, // 33: 御土奇术
      &AntiMagic,           // 34: 抗魔大法
      &Dispel,              // 35: 驱魔大法
      &MagicMirror,         // 36: 魔法神镜
      &Cure,                // 37: 疗伤
      &Resurrection,        // 38: 转世重生
      &AnimateDead,         // 39: 聚灵奇术

      &Sacrifice,     // 40: 牺牲
      &Bless,         // 41: 圣灵佑佐
      &Curse,         // 42: 恶咒附身
      &Bloodlust,     // 43: 嗜血奇术
      &Precision,     // 44: 百发百中
      &Weakness,      // 45: 虚弱无力
      &StoneSkin,     // 46: 护体石肤
      &DisruptingRay, // 47: 毁灭之光
      &Prayer,        // 48: 祈祷
      &Mirth,         // 49: 欢欣鼓舞

      &Sorrow,              // 50: 悲痛欲绝
      &Fortune,             // 51: 幸运之神
      &Misfortune,          // 52: 大难临头
      &Haste,               // 53: 攻击加速
      &Slow,                // 54: 迟缓大法
      &Slayer,              // 55: 屠戮成性
      &Frenzy,              // 56: 孤注一掷
      &TitansLightningBolt, // 57: 泰坦之箭
      &Counterstrike,       // 58: 反戈一击
      &Berserk,             // 59: 丧心病狂

      &Hypnotize,            // 60: 蛊惑人心
      &Forgetfulness,        // 61: 失忆大法
      &Blind,                // 62: 双目失明
      &Teleport,             // 63: 瞬间移动
      &RemoveObstacle,       // 64: 驱除障碍
      &MirrorImage,          // 65: 镜像大法
      &SummonFireElemental,  // 66: 召唤火元素
      &SummonEarthElemental, // 67: 召唤土元素
      &SummonWaterElemental, // 68: 召唤水元素
      &SummonAirElemental    // 69: 召唤气元素
  };
};
