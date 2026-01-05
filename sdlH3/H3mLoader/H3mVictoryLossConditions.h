#pragma once
#include <any>
#include <cstdint>

enum class EVictoryConditionType : int8_t {
  WINSTANDARD = -1,   // 标准胜利条件（通常是击败所有敌人或占领所有城镇）
  ARTIFACT = 0,       // 需要获得指定的神器（Artifact）
  GATHERTROOP = 1,    // 需要收集指定类型和数量的部队（Troop）
  GATHERRESOURCE = 2, // 需要收集指定类型和数量的资源（Resource）
  BUILDCITY = 3,      // 需要在指定位置建造特定城镇（City）
  BUILDGRAIL = 4,     // 需要在城镇中建造神迹（Grail Building）。
  BEATHERO = 5,       // 需要击败特定的英雄（Hero）。
  CAPTURECITY = 6,    // 需要占领特定的城镇（City）。
  BEATMONSTER = 7,    // 需要击败特定的怪物（Monster）。
  TAKEDWELLINGS = 8,  // 需要占领特定的生物巢穴（Dwelling）。
  TAKEMINES = 9,      // 需要占领特定的矿场（Mine）。
  TRANSPORTITEM = 10, // 需要将特定物品（如神器）运送到指定城镇。
  HOTA_ELIMINATE_ALL_MONSTERS =
      11, // （Horn of the Abyss 扩展）需要消灭地图上所有怪物。
  HOTA_SURVIVE_FOR_DAYS =
      12 // （Horn of the Abyss 扩展）需要在指定天数内存活（类似生存模式）。
};
enum class ELossConditionType : int8_t {
  LOSSSTANDARD = -1, // 标准失败方式
  LOSSCASTLE = 0,    // 失去城镇
  LOSSHERO = 1,      // 失去英雄
  TIMEEXPIRES = 2    // 超时
};

struct H3mVictoryLossConditions {
  EVictoryConditionType vicCondition;
  bool allowNormalVictory;
  bool appliesToAI;
  std::any vicConditionData;

  ELossConditionType lossCond;
  std::any lossCondData;
};