#pragma once

#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

struct ArtifactSet {
  const static inline std::vector<ArtifactI> artifacts = {
      // ==================== 基础神器 (0-6) ====================
      {
          // 0: SPELL_BOOK (魔法书)
          .index = 0,
          .bonus = {},  // 魔法书本身不提供属性加成
          .experience = 0,
          .cost = 500,  // 魔法书的价格
          .slot = {false, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, true, false, false},  // MACH3
          .components = {},
      },
      {
          // 1: SPELL_SCROLL (魔法卷轴)
          .index = 1,
          .bonus = {},  // 卷轴不提供永久加成
          .experience = 1000,
          .cost = 2500,
          .slot = {false, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, true},  // MISC5
          .components = {},
      },
      {
          // 2: GRAIL (神器/圣杯)
          .index = 2,
          .bonus = {},  // 特殊神器
          .experience = 1000,
          .cost = 0,    // 无法购买
          .slot = {false, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},
          .components = {},
      },
      {
          // 3: CATAPULT (投石车)
          .index = 3,
          .bonus = {},  // 战争机器
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, true, false, false, false},  // MACH1
          .components = {},
      },
      {
          // 4: BALLISTA (弩车)
          .index = 4,
          .bonus = {},  // 战争机器
          .experience = 1000,
          .cost = 2500,
          .slot = {false, false, false, false, false, false, false, false, false, false,
                   false, false, false, true, false, false, false, false, false},  // MACH2
          .components = {},
      },
      {
          // 5: AMMO_CART (补给车)
          .index = 5,
          .bonus = {},  // 战争机器
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, true, false, false, false, false},  // MACH3
          .components = {},
      },
      {
          // 6: FIRST_AID_TENT (急救帐篷)
          .index = 6,
          .bonus = {},  // 战争机器
          .experience = 1000,
          .cost = 750,
          .slot = {false, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, true, false, false, false},  // MACH1
          .components = {},
      },

      // ==================== 武器 - 攻击加成 (7-12) ====================
      {
          // 7: CENTAUR_AXE (人马战斧)
          .index = 7,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 2}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 8: BLACKSHARD_OF_THE_DEAD_KNIGHT (黑魔剑)
          .index = 8,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 3}
          },
          .experience = 1000,
          .cost = 3000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 9: GREATER_GNOLDS_FLAIL (狼人连枷)
          .index = 9,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 4}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 10: OGRES_CLUB_OF_HAVOC (恶魔之棒)
          .index = 10,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 5}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 11: SWORD_OF_HELLFIRE (火神剑)
          .index = 11,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 6}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 12: TITANS_GLADIUS (泰坦之剑)
          .index = 12,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 12},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = -3}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },

      // ==================== 盾牌 - 防御加成 (13-18) ====================
      {
          // 13: SHIELD_OF_THE_DWARVEN_LORDS (矮人王盾)
          .index = 13,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 2}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },
      {
          // 14: SHIELD_OF_THE_YAWNING_DEAD (亡灵盾)
          .index = 14,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 3}
          },
          .experience = 1000,
          .cost = 3000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },
      {
          // 15: BUCKLER_OF_THE_GNOLF_KING (狼人王盾)
          .index = 15,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 4}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },
      {
          // 16: TARG_OF_THE_RAMPAGING_OGRE (狂魔盾)
          .index = 16,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 5}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },
      {
          // 17: SHIELD_OF_THE_DAMNED (邪盾)
          .index = 17,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 6}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },
      {
          // 18: SENTINELS_SHIELD (守护神之盾)
          .index = 18,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 12},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = -3}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },

      // ==================== 头盔 - 知识加成 (19-24) ====================
      {
          // 19: HELM_OF_THE_ALABASTER_UNICORN (神兽之冠)
          .index = 19,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },
      {
          // 20: SKULL_HELMET (骷髅冠)
          .index = 20,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 2}
          },
          .experience = 1000,
          .cost = 3000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },
      {
          // 21: HELM_OF_CHAOS (混沌之冠)
          .index = 21,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 3}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },
      {
          // 22: CROWN_OF_THE_SUPREME_MAGI (智慧之冠)
          .index = 22,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 4}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },
      {
          // 23: HELLSTORM_HELMET (地狱王冠)
          .index = 23,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 5}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },
      {
          // 24: THUNDER_HELMET (雷神之盔)
          .index = 24,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 10},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = -2}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },

      // ==================== 盔甲 - 法术力量加成 (25-31) ====================
      {
          // 25: BREASTPLATE_OF_PETRIFIED_WOOD (藤木甲)
          .index = 25,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 26: RIB_CAGE (骨质胸甲)
          .index = 26,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 2}
          },
          .experience = 1000,
          .cost = 3000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 27: SCALES_OF_THE_GREATER_BASILISK (大蛇神胸甲)
          .index = 27,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 3}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 28: TUNIC_OF_THE_CYCLOPS_KING (巨人战甲)
          .index = 28,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 4}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 29: BREASTPLATE_OF_BRIMSTONE (黄金甲)
          .index = 29,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 5}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 30: TITANS_CUIRASS (泰坦战甲)
          .index = 30,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 10},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = -2}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 31: ARMOR_OF_WONDER (神奇战甲)
          .index = 31,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 1}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },

      // ==================== 鞋子/项链/戒指等 (32-36) ====================
      {
          // 32: SANDALS_OF_THE_SAINT (圣靴)
          .index = 32,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 2},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 2},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 2},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 2}
          },
          .experience = 1000,
          .cost = 8000,
          .slot = {false, false, false, false, false, false, false, false, true, false,
                   false, false, false, false, false, false, false, false, false},  // FEET
          .components = {},
      },
      {
          // 33: CELESTIAL_NECKLACE_OF_BLISS (天使项链)
          .index = 33,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 3}
          },
          .experience = 1000,
          .cost = 12000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 34: LIONS_SHIELD_OF_COURAGE (狮王盾)
          .index = 34,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 4}
          },
          .experience = 1000,
          .cost = 16000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },
      {
          // 35: SWORD_OF_JUDGEMENT (先知剑)
          .index = 35,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 5},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 5},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 5},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 5}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 36: HELM_OF_HEAVENLY_ENLIGHTENMENT (神谕之冠)
          .index = 36,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 6},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 6},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 6},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 6}
          },
          .experience = 1000,
          .cost = 24000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },

      // ==================== 龙系列 (37-45) ====================
      {
          // 37: QUIET_EYE_OF_THE_DRAGON (龙眼戒)
          .index = 37,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 1}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 38: RED_DRAGON_FLAME_TONGUE (赤龙剑)
          .index = 38,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 2},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 2}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 39: DRAGON_SCALE_SHIELD (龙盾)
          .index = 39,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 3}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, true, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // LEFT_HAND
          .components = {},
      },
      {
          // 40: DRAGON_SCALE_ARMOR (龙甲)
          .index = 40,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 4}
          },
          .experience = 1000,
          .cost = 8000,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 41: DRAGONBONE_GREAVES (龙骨胫甲)
          .index = 41,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 1}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, false, false, false, false, true, false,
                   false, false, false, false, false, false, false, false, false},  // FEET
          .components = {},
      },
      {
          // 42: DRAGON_WING_TABARD (龙翼袍)
          .index = 42,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 2},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 2}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },
      {
          // 43: NECKLACE_OF_DRAGONTEETH (龙牙项链)
          .index = 43,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 3}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 44: CROWN_OF_DRAGONTOOTH (龙牙冠)
          .index = 44,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 4}
          },
          .experience = 1000,
          .cost = 8000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },
      {
          // 45: STILL_EYE_OF_THE_DRAGON (龙眼指环)
          .index = 45,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MORALE, .subType = 0, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_LUCK, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },

      // ==================== 幸运神器 (46-48) ====================
      {
          // 46: CLOVER_OF_FORTUNE (幸运三叶草)
          .index = 46,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LUCK, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 47: CARDS_OF_PROPHECY (预言卡)
          .index = 47,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LUCK, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 48: LADYBIRD_OF_LUCK (幸运鸟)
          .index = 48,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LUCK, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 士气神器 (49-51) ====================
      {
          // 49: BADGE_OF_COURAGE (勇气勋章)
          .index = 49,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MORALE, .subType = 0, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_MIND_IMMUNITY, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 50: CREST_OF_VALOR (勇士勋章)
          .index = 50,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MORALE, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 51: GLYPH_OF_GALLANTRY (勇士令)
          .index = 51,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MORALE, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 视野神器 (52-53) ====================
      {
          // 52: SPECULUM (窥镜)
          .index = 52,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SIGHT_RADIUS, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 53: SPYGLASS (望远镜)
          .index = 53,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SIGHT_RADIUS, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 招魂术神器 (54-56) ====================
      {
          // 54: AMULET_OF_THE_UNDERTAKER (亡灵护身符)
          .index = 54,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_UNDEAD_RAISE_PERCENTAGE, .subType = 0, .val = 5}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 55: VAMPIRES_COWL (吸血鬼披风)
          .index = 55,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_UNDEAD_RAISE_PERCENTAGE, .subType = 0, .val = 10}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },
      {
          // 56: DEAD_MANS_BOOTS (死神靴)
          .index = 56,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_UNDEAD_RAISE_PERCENTAGE, .subType = 0, .val = 15}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, true, false,
                   false, false, false, false, false, false, false, false, false},  // FEET
          .components = {},
      },

      // ==================== 魔法抗性神器 (57-59) ====================
      {
          // 57: GARNITURE_OF_INTERFERENCE (抗魔链)
          .index = 57,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MAGIC_RESISTANCE, .subType = 0, .val = 5}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 58: SURCOAT_OF_COUNTERPOISE (抗魔披风)
          .index = 58,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MAGIC_RESISTANCE, .subType = 0, .val = 10}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },
      {
          // 59: BOOTS_OF_POLARITY (抗魔靴)
          .index = 59,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MAGIC_RESISTANCE, .subType = 0, .val = 15}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, true, false,
                   false, false, false, false, false, false, false, false, false},  // FEET
          .components = {},
      },

      // ==================== 箭术神器 (60-62) ====================
      {
          // 60: BOW_OF_ELVEN_CHERRYWOOD (树精灵之弓)
          .index = 60,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PERCENTAGE_DAMAGE_BOOST_RANGED, .subType = 0, .val = 5}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 61: BOWSTRING_OF_THE_UNICORNS_MANE (神兽之鬃)
          .index = 61,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PERCENTAGE_DAMAGE_BOOST_RANGED, .subType = 0, .val = 10}
          },
          .experience = 1000,
          .cost = 4000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 62: ANGEL_FEATHER_ARROWS (天羽箭)
          .index = 62,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PERCENTAGE_DAMAGE_BOOST, .subType = 0, .val = 15}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 战斗法术学习神器 (63-65) ====================
      {
          // 63: BIRD_OF_PERCEPTION (神目鸟)
          .index = 63,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LEARN_BATTLE_SPELL_CHANCE, .subType = 0, .val = 5}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 64: STOIC_WATCHMAN (火眼人)
          .index = 64,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LEARN_BATTLE_SPELL_CHANCE, .subType = 0, .val = 10}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 65: EMBLEM_OF_COGNIZANCE (真理徽章)
          .index = 65,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LEARN_BATTLE_SPELL_CHANCE, .subType = 0, .val = 15}
          },
          .experience = 1000,
          .cost = 3000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 投降折扣神器 (66-68) ====================
      {
          // 66: STATESMANS_MEDAL (政治家勋章)
          .index = 66,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SURRENDER_DISCOUNT, .subType = 0, .val = 10}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 67: DIPLOMATS_RING (礼仪之戒)
          .index = 67,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SURRENDER_DISCOUNT, .subType = 0, .val = 10}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 68: AMBASSADORS_SASH (大使勋带)
          .index = 68,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SURRENDER_DISCOUNT, .subType = 0, .val = 10}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },

      // ==================== 移动力神器 (69-72) ====================
      {
          // 69: RING_OF_THE_WAYFARER (旅行者之戒)
          .index = 69,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_STACKS_SPEED, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 70: EQUESTRIANS_GLOVES (骑士手套)
          .index = 70,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MOVEMENT_LAND, .subType = 0, .val = 300}
          },
          .experience = 1000,
          .cost = 3000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 71: NECKLACE_OF_OCEAN_GUIDANCE (海神项链)
          .index = 71,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MOVEMENT_SEA, .subType = 0, .val = 1000}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 72: ANGEL_WINGS (炽天之翼)
          .index = 72,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_FLYING_MOVEMENT, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },

      // ==================== 魔法回复神器 (73-75) ====================
      {
          // 73: CHARM_OF_MANA (魔力护符)
          .index = 73,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MANA_REGENERATION, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 500,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 74: TALISMAN_OF_MANA (魔法护符)
          .index = 74,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MANA_REGENERATION, .subType = 0, .val = 2}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 75: MYSTIC_ORB_OF_MANA (魔力球)
          .index = 75,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MANA_REGENERATION, .subType = 0, .val = 3}
          },
          .experience = 1000,
          .cost = 1500,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 法术持续时间神器 (76-78) ====================
      {
          // 76: COLLAR_OF_CONJURING (魔力项圈)
          .index = 76,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DURATION, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 500,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 77: RING_OF_CONJURING (魔戒)
          .index = 77,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DURATION, .subType = 0, .val = 2}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 78: CAPE_OF_CONJURING (魔法披风)
          .index = 78,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DURATION, .subType = 0, .val = 3}
          },
          .experience = 1000,
          .cost = 1500,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },

      // ==================== 法术伤害神器 (79-82) ====================
      {
          // 79: ORB_OF_THE_FIRMAMENT (气灵球)
          .index = 79,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DAMAGE, .subType = Enum::SPELL_SCHOOL_AIR, .val = 50}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 80: ORB_OF_SILT (土灵球)
          .index = 80,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DAMAGE, .subType = Enum::SPELL_SCHOOL_EARTH, .val = 50}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 81: ORB_OF_TEMPESTUOUS_FIRE (火灵球)
          .index = 81,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DAMAGE, .subType = Enum::SPELL_SCHOOL_FIRE, .val = 50}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 82: ORB_OF_DRIVING_RAIN (水灵球)
          .index = 82,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DAMAGE, .subType = Enum::SPELL_SCHOOL_WATER, .val = 50}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 特殊魔法神器 (83-93) ====================
      {
          // 83: RECANTERS_CLOAK (禁魔披风)
          .index = 83,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_BLOCK_MAGIC_ABOVE, .subType = 0, .val = 2}
          },
          .experience = 1000,
          .cost = 8000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },
      {
          // 84: SPIRIT_OF_OPPRESSION (禁锢之灵)
          .index = 84,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MORALE, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 85: HOURGLASS_OF_THE_EVIL_HOUR (恶运沙漏)
          .index = 85,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LUCK, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 2000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 86: TOME_OF_FIRE_MAGIC (火系魔法书)
          .index = 86,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELLS_OF_SCHOOL, .subType = Enum::SPELL_SCHOOL_FIRE, .val = 0}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 87: TOME_OF_AIR_MAGIC (气系魔法书)
          .index = 87,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELLS_OF_SCHOOL, .subType = Enum::SPELL_SCHOOL_AIR, .val = 0}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 88: TOME_OF_WATER_MAGIC (水系魔法书)
          .index = 88,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELLS_OF_SCHOOL, .subType = Enum::SPELL_SCHOOL_WATER, .val = 0}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 89: TOME_OF_EARTH_MAGIC (土系魔法书)
          .index = 89,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELLS_OF_SCHOOL, .subType = Enum::SPELL_SCHOOL_EARTH, .val = 0}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 90: BOOTS_OF_LEVITATION (水神靴)
          .index = 90,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_WATER_WALKING, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, false, false, false, false, false, false, false, true, false,
                   false, false, false, false, false, false, false, false, false},  // FEET
          .components = {},
      },
      {
          // 91: GOLDEN_BOW (黄金弓)
          .index = 91,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_NO_DISTANCE_PENALTY, .subType = 0, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_NO_WALL_PENALTY, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 8000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 92: SPHERE_OF_PERMANENCE (永恒之球)
          .index = 92,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::DISPEL}
          },
          .experience = 1000,
          .cost = 7500,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 93: ORB_OF_VULNERABILITY (毁灭之球)
          .index = 93,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_NEGATE_ALL_NATURAL_IMMUNITIES, .subType = 0, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_MAGIC_RESISTANCE, .subType = 0, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_SPELL_RESISTANCE_AURA, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 25000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 生命值神器 (94-96) ====================
      {
          // 94: RING_OF_VITALITY (活力之戒)
          .index = 94,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_STACK_HEALTH, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 95: RING_OF_LIFE (生命之戒)
          .index = 95,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_STACK_HEALTH, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 96: VIAL_OF_LIFEBLOOD (活力圣瓶)
          .index = 96,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_STACK_HEALTH, .subType = 0, .val = 2}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 速度神器 (97-99) ====================
      {
          // 97: NECKLACE_OF_SWIFTNESS (极速项链)
          .index = 97,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_STACKS_SPEED, .subType = 0, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 98: BOOTS_OF_SPEED (神行靴)
          .index = 98,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MOVEMENT_LAND, .subType = 0, .val = 600}
          },
          .experience = 1000,
          .cost = 6000,
          .slot = {false, false, false, false, false, false, false, false, true, false,
                   false, false, false, false, false, false, false, false, false},  // FEET
          .components = {},
      },
      {
          // 99: CAPE_OF_VELOCITY (极速披风)
          .index = 99,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_STACKS_SPEED, .subType = 0, .val = 2}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },

      // ==================== 护身符 - 法术免疫 (100-108) ====================
      {
          // 100: PENDANT_OF_DISPASSION (冷静挂件)
          .index = 100,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::BERSERK}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 101: PENDANT_OF_SECOND_SIGHT (光明挂件)
          .index = 101,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::BLIND}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 102: PENDANT_OF_HOLINESS (神圣挂件)
          .index = 102,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::CURSE}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 103: PENDANT_OF_LIFE (生命挂件)
          .index = 103,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::DEATH_RIPPLE}
          },
          .experience = 1000,
          .cost = 2500,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 104: PENDANT_OF_DEATH (死神挂件)
          .index = 104,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::DESTROY_UNDEAD}
          },
          .experience = 1000,
          .cost = 2500,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 105: PENDANT_OF_FREE_WILL (自由挂件)
          .index = 105,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::HYPNOTIZE}
          },
          .experience = 1000,
          .cost = 1000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 106: PENDANT_OF_NEGATIVITY (电神挂件)
          .index = 106,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::LIGHTNING_BOLT},
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::CHAIN_LIGHTNING}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 107: PENDANT_OF_TOTAL_RECALL (清醒挂件)
          .index = 107,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::FORGETFULNESS}
          },
          .experience = 1000,
          .cost = 3000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },
      {
          // 108: PENDANT_OF_COURAGE (勇气挂件)
          .index = 108,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_MORALE, .subType = 0, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_LUCK, .subType = 0, .val = 3}
          },
          .experience = 1000,
          .cost = 7000,
          .slot = {false, false, true, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // NECK
          .components = {},
      },

      // ==================== 资源生成神器 (109-117) ====================
      {
          // 109: EVERFLOWING_CRYSTAL_CLOAK (水晶披风)
          .index = 109,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::CRYSTAL, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },
      {
          // 110: RING_OF_INFINITE_GEMS (宝石戒指)
          .index = 110,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::GEM, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 111: EVERPOURING_VIAL_OF_MERCURY (水银瓶)
          .index = 111,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::MERCURY, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 112: INEXHAUSTIBLE_CART_OF_ORE (矿石车)
          .index = 112,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::ORE, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 113: EVERSMOKING_RING_OF_SULFUR (硫磺指环)
          .index = 113,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::SULFUR, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {},
      },
      {
          // 114: INEXHAUSTIBLE_CART_OF_LUMBER (木材车)
          .index = 114,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::WOOD, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 115: ENDLESS_SACK_OF_GOLD (黄金囊)
          .index = 115,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::GOLD, .val = 1000}
          },
          .experience = 1000,
          .cost = 10000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 116: ENDLESS_BAG_OF_GOLD (黄金袋)
          .index = 116,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::GOLD, .val = 750}
          },
          .experience = 1000,
          .cost = 7500,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 117: ENDLESS_PURSE_OF_GOLD (黄金包)
          .index = 117,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::GOLD, .val = 500}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 军团系列 (118-122) ====================
      {
          // 118: LEGS_OF_LEGION (天赐神足)
          .index = 118,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_CREATURE_GROWTH, .subType = 2, .val = 5}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 119: LOINS_OF_LEGION (天赐神胯)
          .index = 119,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_CREATURE_GROWTH, .subType = 3, .val = 4}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 120: TORSO_OF_LEGION (天赐神躯)
          .index = 120,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_CREATURE_GROWTH, .subType = 4, .val = 3}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 121: ARMS_OF_LEGION (天赐神臂)
          .index = 121,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_CREATURE_GROWTH, .subType = 5, .val = 2}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 122: HEAD_OF_LEGION (天赐神首)
          .index = 122,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_CREATURE_GROWTH, .subType = 6, .val = 1}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },

      // ==================== 帽子 (123-124) ====================
      {
          // 123: SEA_CAPTAINS_HAT (航海家之帽)
          .index = 123,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_WHIRLPOOL_PROTECTION, .subType = 0, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_MOVEMENT_SEA, .subType = 0, .val = 500},
              {.src = 0, .type = Enum::ARTIFACT_SPELL, .subType = 0, .val = Enum::SUMMON_BOAT},
              {.src = 0, .type = Enum::ARTIFACT_SPELL, .subType = 0, .val = Enum::SCUTTLE_BOAT}
          },
          .experience = 1000,
          .cost = 15000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {Enum::ARTIFACT_NECKLACE_OF_OCEAN_GUIDANCE, Enum::ARTIFACT_SEA_CAPTAINS_HAT},
      },
      {
          // 124: SPELLBINDERS_HAT (魔法师之帽)
          .index = 124,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELLS_OF_LEVEL, .subType = 0, .val = 5}
          },
          .experience = 1000,
          .cost = 30000,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {},
      },

      // ==================== 特殊神器 (125-140) ====================
      {
          // 125: SHACKLES_OF_WAR (战争枷锁)
          .index = 125,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_BATTLE_NO_FLEEING, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 5000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 126: ORB_OF_INHIBITION (禁魔球)
          .index = 126,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_BLOCK_ALL_MAGIC, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 127: VIAL_OF_DRAGON_BLOOD (龙之血瓶)
          .index = 127,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 5},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 5}
          },
          .experience = 1000,
          .cost = 20000,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {},
      },
      {
          // 128: ARMAGEDDONS_BLADE (末日之刃)
          .index = 128,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL, .subType = 0, .val = Enum::ARMAGEDDON},
              {.src = 0, .type = Enum::ARTIFACT_SPELL_IMMUNITY, .subType = 0, .val = Enum::ARMAGEDDON},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 3},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 6}
          },
          .experience = 1000,
          .cost = 50000,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
      {
          // 129: ANGELIC_ALLIANCE (天使联盟)
          .index = 129,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_NONEVIL_ALIGNMENT_MIX, .subType = 0, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL, .subType = 0, .val = Enum::PRAYER}
          },
          .experience = 1000,
          .cost = 0,  // 组合神器，无法购买
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {
              Enum::ARTIFACT_ARMOR_OF_WONDER,
              Enum::ARTIFACT_SANDALS_OF_THE_SAINT,
              Enum::ARTIFACT_CELESTIAL_NECKLACE_OF_BLISS,
              Enum::ARTIFACT_LIONS_SHIELD_OF_COURAGE,
              Enum::ARTIFACT_SWORD_OF_JUDGEMENT,
              Enum::ARTIFACT_HELM_OF_HEAVENLY_ENLIGHTENMENT
          },
      },
      {
          // 130: CLOAK_OF_THE_UNDEAD_KING (鬼王斗蓬)
          .index = 130,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_IMPROVED_NECROMANCY, .subType = Enum::SKELETON, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_IMPROVED_NECROMANCY, .subType = Enum::WALKING_DEAD, .val = 1},
              {.src = 0, .type = Enum::ARTIFACT_IMPROVED_NECROMANCY, .subType = Enum::WIGHT, .val = 2},
              {.src = 0, .type = Enum::ARTIFACT_IMPROVED_NECROMANCY, .subType = Enum::LICH, .val = 3}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {
              Enum::ARTIFACT_AMULET_OF_THE_UNDERTAKER,
              Enum::ARTIFACT_VAMPIRES_COWL,
              Enum::ARTIFACT_DEAD_MANS_BOOTS
          },
      },
      {
          // 131: ELIXIR_OF_LIFE (神圣血瓶)
          .index = 131,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_STACK_HEALTH, .subType = 0, .val = 25},
              {.src = 0, .type = Enum::ARTIFACT_HP_REGENERATION, .subType = 0, .val = 50}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {
              Enum::ARTIFACT_RING_OF_VITALITY,
              Enum::ARTIFACT_RING_OF_LIFE,
              Enum::ARTIFACT_VIAL_OF_LIFEBLOOD
          },
      },
      {
          // 132: ARMOR_OF_THE_DAMNED (诅咒铠甲)
          .index = 132,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL, .subType = 0, .val = Enum::SLOW},
              {.src = 0, .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL, .subType = 0, .val = Enum::CURSE},
              {.src = 0, .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL, .subType = 0, .val = Enum::WEAKNESS},
              {.src = 0, .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL, .subType = 0, .val = Enum::MISFORTUNE}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {
              Enum::ARTIFACT_BLACKSHARD_OF_THE_DEAD_KNIGHT,
              Enum::ARTIFACT_SHIELD_OF_THE_YAWNING_DEAD,
              Enum::ARTIFACT_SKULL_HELMET,
              Enum::ARTIFACT_RIB_CAGE
          },
      },
      {
          // 133: STATUE_OF_LEGION (天赐神兵)
          .index = 133,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_CREATURE_GROWTH_PERCENT, .subType = 0, .val = 50}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {
              Enum::ARTIFACT_LEGS_OF_LEGION,
              Enum::ARTIFACT_LOINS_OF_LEGION,
              Enum::ARTIFACT_TORSO_OF_LEGION,
              Enum::ARTIFACT_ARMS_OF_LEGION,
              Enum::ARTIFACT_HEAD_OF_LEGION
          },
      },
      {
          // 134: POWER_OF_THE_DRAGON_FATHER (龙王神力)
          .index = 134,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_LEVEL_SPELL_IMMUNITY, .subType = 0, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_ATTACK, .val = 6},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_DEFENCE, .val = 6},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_SPELLPOWER, .val = 6},
              {.src = 0, .type = Enum::ARTIFACT_PRIMARY_SKILL, .subType = Enum::PRIMARY_SKILL_KNOWLEDGE, .val = 6}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {
              Enum::ARTIFACT_QUIET_EYE_OF_THE_DRAGON,
              Enum::ARTIFACT_RED_DRAGON_FLAME_TONGUE,
              Enum::ARTIFACT_DRAGON_SCALE_SHIELD,
              Enum::ARTIFACT_DRAGON_SCALE_ARMOR,
              Enum::ARTIFACT_DRAGONBONE_GREAVES,
              Enum::ARTIFACT_DRAGON_WING_TABARD,
              Enum::ARTIFACT_NECKLACE_OF_DRAGONTEETH,
              Enum::ARTIFACT_CROWN_OF_DRAGONTOOTH,
              Enum::ARTIFACT_STILL_EYE_OF_THE_DRAGON
          },
      },
      {
          // 135: TITANS_THUNDER (泰坦之箭)
          .index = 135,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL, .subType = 0, .val = Enum::TITANS_LIGHTNING_BOLT}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {
              Enum::ARTIFACT_TITANS_GLADIUS,
              Enum::ARTIFACT_SENTINELS_SHIELD,
              Enum::ARTIFACT_THUNDER_HELMET,
              Enum::ARTIFACT_TITANS_CUIRASS
          },
      },
      {
          // 136: ADMIRALS_HAT (海洋之帽)
          .index = 136,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_FREE_SHIP_BOARDING, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {true, false, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // HEAD
          .components = {
              Enum::ARTIFACT_NECKLACE_OF_OCEAN_GUIDANCE,
              Enum::ARTIFACT_SEA_CAPTAINS_HAT
          },
      },
      {
          // 137: BOW_OF_THE_SHARPSHOOTER (幻影神弓)
          .index = 137,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_NO_DISTANCE_PENALTY, .subType = 0, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_NO_WALL_PENALTY, .subType = 0, .val = 0},
              {.src = 0, .type = Enum::ARTIFACT_FREE_SHOOTING, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {
              Enum::ARTIFACT_BOW_OF_ELVEN_CHERRYWOOD,
              Enum::ARTIFACT_BOWSTRING_OF_THE_UNICORNS_MANE,
              Enum::ARTIFACT_ANGEL_FEATHER_ARROWS
          },
      },
      {
          // 138: WIZARDS_WELL (魔力源泉)
          .index = 138,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_FULL_MANA_REGENERATION, .subType = 0, .val = 0}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {
              Enum::ARTIFACT_CHARM_OF_MANA,
              Enum::ARTIFACT_TALISMAN_OF_MANA,
              Enum::ARTIFACT_MYSTIC_ORB_OF_MANA
          },
      },
      {
          // 139: RING_OF_THE_MAGI (法师之戒)
          .index = 139,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_SPELL_DURATION, .subType = 0, .val = 50}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, false, true, true, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_RING, LEFT_RING
          .components = {
              Enum::ARTIFACT_COLLAR_OF_CONJURING,
              Enum::ARTIFACT_RING_OF_CONJURING,
              Enum::ARTIFACT_CAPE_OF_CONJURING
          },
      },
      {
          // 140: CORNUCOPIA (丰收之角)
          .index = 140,
          .bonus = {
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::CRYSTAL, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::GEM, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::MERCURY, .val = 4},
              {.src = 0, .type = Enum::ARTIFACT_GENERATE_RESOURCE, .subType = Enum::SULFUR, .val = 4}
          },
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, false, false, false, false, true,
                   true, true, true, false, false, false, false, false, true},  // MISC1-4, MISC5
          .components = {
              Enum::ARTIFACT_RECANTERS_CLOAK,
              Enum::ARTIFACT_RING_OF_INFINITE_GEMS,
              Enum::ARTIFACT_EVERPOURING_VIAL_OF_MERCURY,
              Enum::ARTIFACT_EVERSMOKING_RING_OF_SULFUR
          },
      },

      // ==================== 未使用神器 (141-143) ====================
      {
          // 141: DIPLOMATS_SUIT
          .index = 141,
          .bonus = {},
          .experience = 1000,
          .cost = 0,
          .slot = {false, true, false, false, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // SHOULDERS
          .components = {},
      },
      {
          // 142: MIRED_IN_NEUTRALITY
          .index = 142,
          .bonus = {},
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, false, false, true, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // TORSO
          .components = {},
      },
      {
          // 143: IRONFIST_OF_THE_OGRE
          .index = 143,
          .bonus = {},
          .experience = 1000,
          .cost = 0,
          .slot = {false, false, false, true, false, false, false, false, false, false,
                   false, false, false, false, false, false, false, false, false},  // RIGHT_HAND
          .components = {},
      },
  };
};