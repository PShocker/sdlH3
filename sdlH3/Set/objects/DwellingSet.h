#pragma once
#include "Enum/Enum.h"
#include "Set/StructSet.h"
#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct DwellingSet {
  const static inline std::vector<ObjectSetI> dwellings1 = {
      // === 普通生物巢穴 (creatureGeneratorCommon) ===
      {
          // basiliskPit - 蛇妖窝
          .index = 0,
          .sound =
              {
                  .ambient = "LOOPMONS.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::BASILISK,
              },
      },
      {
          // behemothCrag - 比蒙崖
          .index = 1,
          .sound =
              {
                  .ambient = "LOOPBEHE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::BEHEMOTH,
              },
      },
      {
          // pillarOfEyes - 邪眼之柱
          .index = 2,
          .sound =
              {
                  .ambient = "LOOPCAVE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::BEHOLDER,
              },
      },
      {
          // hallOfDarkness - 黑暗殿
          .index = 3,
          .sound =
              {
                  .ambient = "LOOPDEAD.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::BLACK_KNIGHT,
              },
      },
      {
          // dragonVault - 龙窟
          .index = 4,
          .sound =
              {
                  .ambient = "LOOPDRAG.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::BONE_DRAGON,
              },
      },
      {
          // trainingGrounds - 训练场
          .index = 5,
          .sound =
              {
                  .ambient = "LOOPHORS.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::CAVALIER,
              },
      },
      {
          // centaurStables - 半人马马厩
          .index = 6,
          .sound =
              {
                  .ambient = "LOOPHORS.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::CENTAUR,
              },
      },
      {
          // airConflux - 气元素汇聚点
          .index = 7,
          .sound =
              {
                  .ambient = "LOOPAIR.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::AIR_ELEMENTAL,
              },
      },
      {
          // portalOfGlory - 荣耀之门
          .index = 8,
          .sound =
              {
                  .ambient = "LOOPSANC.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::ANGEL,
              },
      },
      {
          // cyclopsCave - 独眼巨人洞穴
          .index = 9,
          .sound =
              {
                  .ambient = "LOOPCAVE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::CYCLOPS,
              },
      },
      {
          // forsakenPalace - 被遗忘的宫殿
          .index = 10,
          .sound =
              {
                  .ambient = "LOOPDEVL.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::DEVIL,
              },
      },
      {
          // serpentFlyHive - 飞龙巢
          .index = 11,
          .sound =
              {
                  .ambient = "LOOPLEAR.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::SERPENT_FLY,
              },
      },
      {
          // dwarfCottage - 矮人小屋
          .index = 12,
          .sound =
              {
                  .ambient = "LOOPDWAR.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::DWARF,
              },
      },
      {
          // earthConflux - 土元素汇聚点
          .index = 13,
          .sound =
              {
                  .ambient = "LOOPEART.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::EARTH_ELEMENTAL,
              },
      },
      {
          // fireLake - 火湖
          .index = 14,
          .sound =
              {
                  .ambient = "LOOPVENT.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::EFREETI,
              },
      },
      {
          // homestead - 林居
          .index = 15,
          .sound =
              {
                  .ambient = "LOOPELF.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::WOOD_ELF,
              },
      },
      {
          // fireConflux - 火元素汇聚点
          .index = 16,
          .sound =
              {
                  .ambient = "LOOPFIRE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::FIRE_ELEMENTAL,
              },
      },
      {
          // parapet - 护栏
          .index = 17,
          .sound =
              {
                  .ambient = "LOOPGRIF.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::STONE_GARGOYLE,
              },
      },
      {
          // altarOfWishes - 祈愿神坛
          .index = 18,
          .sound =
              {
                  .ambient = "LOOPMAGI.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GENIE,
              },
      },
      {
          // wolfPen - 狼圈
          .index = 19,
          .sound =
              {
                  .ambient = "LOOPWOLF.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::WOLF_RIDER,
              },
      },
      {
          // gnollHut - 豺狼人小屋
          .index = 20,
          .sound =
              {
                  .ambient = "LOOPORC.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GNOLL,
              },
      },
      {
          // goblinBarracks - 哥布林兵营
          .index = 21,
          .sound =
              {
                  .ambient = "LOOPGOBL.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GOBLIN,
              },
      },
      {
          // hallOfSins - 罪恶殿
          .index = 22,
          .sound =
              {
                  .ambient = "LOOPVENT.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GOG,
              },
      },
      {
          // gorgonLair - 蛇妖巢穴
          .index = 23,
          .sound =
              {
                  .ambient = "LOOPBEHE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GORGON,
              },
      },
      {
          // dragonCliffs - 龙崖
          .index = 24,
          .sound =
              {
                  .ambient = "LOOPDRAG.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GREEN_DRAGON,
              },
      },
      {
          // griffinTower - 狮鹫塔
          .index = 25,
          .sound =
              {
                  .ambient = "LOOPGRIF.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GRIFFIN,
              },
      },
      {
          // harpyLoft - 鹰身女巫阁楼
          .index = 26,
          .sound =
              {
                  .ambient = "LOOPHARP.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::HARPY,
              },
      },
      {
          // kennels - 狗舍
          .index = 27,
          .sound =
              {
                  .ambient = "LOOPDOG.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::HELL_HOUND,
              },
      },
      {
          // hydraPond - 九头蛇池塘
          .index = 28,
          .sound =
              {
                  .ambient = "LOOPHYDR.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::HYDRA,
              },
      },
      {
          // impCrucible - 小恶魔坩埚
          .index = 29,
          .sound =
              {
                  .ambient = "LOOPFIRE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::IMP,
              },
      },
      {
          // lizardDen - 蜥蜴人巢穴
          .index = 30,
          .sound =
              {
                  .ambient = "LOOPARCH.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::LIZARDMAN,
              },
      },
      {
          // mageTower - 法师塔
          .index = 31,
          .sound =
              {
                  .ambient = "LOOPMAGI.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::MAGE,
              },
      },
      {
          // manticoreLair - 蝎狮巢穴
          .index = 32,
          .sound =
              {
                  .ambient = "LOOPMANT.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::MANTICORE,
              },
      },
      {
          // medusaChapel - 美杜莎礼拜堂
          .index = 33,
          .sound =
              {
                  .ambient = "LOOPMEDU.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::MEDUSA,
              },
      },
      {
          // labyrinth - 迷宫
          .index = 34,
          .sound =
              {
                  .ambient = "LOOPANIM.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::MINOTAUR,
              },
      },
      {
          // monastery - 修道院
          .index = 35,
          .sound =
              {
                  .ambient = "LOOPMONK.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::MONK,
              },
      },
      {
          // goldenPavilion - 金色凉亭
          .index = 36,
          .sound =
              {
                  .ambient = "LOOPNAGA.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::NAGA,
              },
      },
      {
          // demonGate - 恶魔之门
          .index = 37,
          .sound =
              {
                  .ambient = "LOOPCAVE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::DEMON,
              },
      },
      {
          // ogreFort - 食人魔堡垒
          .index = 38,
          .sound =
              {
                  .ambient = "LOOPOGRE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::OGRE,
              },
      },
      {
          // orcTower - 兽人塔
          .index = 39,
          .sound =
              {
                  .ambient = "LOOPORC.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::ORC,
              },
      },
      {
          // hellHole - 地狱洞穴
          .index = 40,
          .sound =
              {
                  .ambient = "LOOPFIRE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::PIT_FIEND,
              },
      },
      {
          // dragonCave - 龙穴
          .index = 41,
          .sound =
              {
                  .ambient = "LOOPDRAG.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::RED_DRAGON,
              },
      },
      {
          // cliffNest - 崖壁巢穴
          .index = 42,
          .sound =
              {
                  .ambient = "LOOPBIRD.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::ROC,
              },
      },
      {
          // workshop - 工坊
          .index = 43,
          .sound =
              {
                  .ambient = "LOOPGREM.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GREMLIN,
              },
      },
      {
          // cloudTemple - 云殿
          .index = 44,
          .sound =
              {
                  .ambient = "LOOPTITA.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::GIANT,
              },
      },
      {
          // dendroidArches - 树精拱门
          .index = 45,
          .sound =
              {
                  .ambient = "LOOPGARD.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::DENDROID_GUARD,
              },
      },
      {
          // warren - 洞穴
          .index = 46,
          .sound =
              {
                  .ambient = "LOOPCAVE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::TROGLODYTE,
              },
      },
      {
          // waterConflux - 水元素汇聚点
          .index = 47,
          .sound =
              {
                  .ambient = "LOOPFOUN.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::WATER_ELEMENTAL,
              },
      },
      {
          // tombOfSouls - 灵魂之墓
          .index = 48,
          .sound =
              {
                  .ambient = "LOOPDEAD.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::WIGHT,
              },
      },
      {
          // wyvernNest - 双足飞龙巢
          .index = 49,
          .sound =
              {
                  .ambient = "LOOPMONS.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::WYVERN,
              },
      },
      {
          // enchantedSpring - 魔法泉
          .index = 50,
          .sound =
              {
                  .ambient = "LOOPPEGA.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::PEGASUS,
              },
      },
      {
          // unicornGladeBig - 独角兽林（大）
          .index = 51,
          .sound =
              {
                  .ambient = "LOOPUNIC.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::UNICORN,
              },
      },
      {
          // mausoleum - 陵墓
          .index = 52,
          .sound =
              {
                  .ambient = "LOOPDEAD.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::LICH,
              },
      },
      {
          // estate - 庄园
          .index = 53,
          .sound =
              {
                  .ambient = "LOOPDEAD.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::VAMPIRE,
              },
      },
      {
          // cursedTemple - 诅咒神殿
          .index = 54,
          .sound =
              {
                  .ambient = "LOOPSKEL.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::SKELETON,
              },
      },
      {
          // graveyard - 墓地
          .index = 55,
          .sound =
              {
                  .ambient = "LOOPDEAD.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::WALKING_DEAD,
              },
      },
      {
          // guardhouse - 岗哨
          .index = 56,
          .sound =
              {
                  .ambient = "LOOPPIKE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::PIKEMAN,
              },
      },
      {
          // archersTower - 弓箭手塔楼
          .index = 57,
          .sound =
              {
                  .ambient = "LOOPARCH.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::ARCHER,
              },
      },
      {
          // barracks - 兵营
          .index = 58,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::SWORDSMAN,
              },
      },
      {
          // magicLantern - 魔法灯笼
          .index = 59,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::PIXIE,
              },
      },
      {
          // altarOfThought - 思维祭坛
          .index = 60,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::PSYCHIC_ELEMENTAL,
              },
      },
      {
          // pyre - 火葬柴堆
          .index = 61,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::FIREBIRD,
              },
      },
      {
          // frozenCliffs - 冰封悬崖
          .index = 62,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::AZURE_DRAGON,
              },
      },
      {
          // crystalCavern - 水晶洞穴
          .index = 63,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::CRYSTAL_DRAGON,
              },
      },
      {
          // magicForest - 魔法森林
          .index = 64,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::FAERIE_DRAGON,
              },
      },
      {
          // sulfurousLair - 硫磺巢穴
          .index = 65,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::RUST_DRAGON,
              },
      },
      {
          // enchantersHollow - 附魔师之洞
          .index = 66,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::ENCHANTER,
              },
      },
      {
          // treetopTower - 树顶塔
          .index = 67,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::SHARPSHOOTER,
              },
      },
      {
          // unicornGlade - 独角兽林
          .index = 68,
          .sound =
              {
                  .ambient = "LOOPUNIC.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::UNICORN,
              },
      },
      {
          // altarOfAir - 气元素祭坛
          .index = 69,
          .sound =
              {
                  .ambient = "LOOPAIR.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::AIR_ELEMENTAL,
              },
      },
      {
          // altarOfEarth - 土元素祭坛
          .index = 70,
          .sound =
              {
                  .ambient = "LOOPEART.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::EARTH_ELEMENTAL,
              },
      },
      {
          // altarOfFire - 火元素祭坛
          .index = 71,
          .sound =
              {
                  .ambient = "LOOPFIRE.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::FIRE_ELEMENTAL,
              },
      },
      {
          // altarOfWater - 水元素祭坛
          .index = 72,
          .sound =
              {
                  .ambient = "LOOPFOUN.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::WATER_ELEMENTAL,
              },
      },
      {
          // thatchedHut - 茅草屋
          .index = 73,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::HALFLING,
              },
      },
      {
          // hovel - 农舍
          .index = 74,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::PEASANT,
              },
      },
      {
          // boarGlen - 野猪谷
          .index = 75,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::BOAR,
              },
      },
      {
          // tombOfCurses - 诅咒之墓
          .index = 76,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::MUMMY,
              },
      },
      {
          // nomadTent - 游牧帐篷
          .index = 77,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::NOMAD,
              },
      },
      {
          // rogueCavern - 盗贼洞穴
          .index = 78,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::ROGUE,
              },
      },
      {
          // trollBridge - 巨魔桥
          .index = 79,
          .sound =
              {
                  .ambient = "LOOPSWOR.wav", // 没有指定，使用默认
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::TROLL,
              },
      },

      // === 特殊生物巢穴 (creatureGeneratorSpecial) ===
      {
          // elementalConflux - 元素汇聚点（四系）
          .index = 80, // 从80开始，避免与普通巢穴冲突
          .sound =
              {
                  .ambient = "LOOPTITA.wav",
                  .visit = "", // 没有访问声音
              },
          .guards =
              {
                  {Enum::EARTH_ELEMENTAL, 12},
              },
          .creatures =
              {
                  Enum::AIR_ELEMENTAL,
                  Enum::WATER_ELEMENTAL,
                  Enum::FIRE_ELEMENTAL,
                  Enum::EARTH_ELEMENTAL,
              },
      },
      {
          // golemFactory - 傀儡工厂
          .index = 81,
          .sound =
              {
                  .ambient = "LOOPFACT.wav",
                  .visit = "",
              },
          .guards =
              {
                  {Enum::GOLD_GOLEM, 9},
                  {Enum::DIAMOND_GOLEM, 6},
              },
          .creatures =
              {
                  Enum::IRON_GOLEM,
                  Enum::STONE_GOLEM,
                  Enum::GOLD_GOLEM,
                  Enum::DIAMOND_GOLEM,
              },
      },
  };
  const static inline std::vector<ObjectSetI> dwellings2 = {};
  const static inline std::vector<ObjectSetI> dwellings3 = {};
  const static inline std::vector<ObjectSetI> dwellings4 = {
        // === 普通生物巢穴 (creatureGeneratorCommon) ===
      {
          // basiliskPit - 蛇妖窝
          .index = 0,
          .sound =
              {
                  .ambient = "LOOPMONS.wav",
                  .visit = "MILITARY.wav",
              },
          .guards = {},
          .creatures =
              {
                  Enum::BASILISK,
              },
      },
  };

  const static inline std::array fullDwellings = {
      &dwellings1,
      &dwellings2,
      &dwellings3,
      &dwellings4,
  };
};