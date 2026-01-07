#pragma once

#include "Cfg/CreatureCfg.h"
#include <cstdint>
#include <vector>
struct DwellingCfg {

  const static inline std::vector<std::vector<uint16_t>> dweCreature[] = {
      {
          // cr1
          {(uint16_t)CreatureCfg::Creature::BASILISK},     // 0: basiliskPit
          {(uint16_t)CreatureCfg::Creature::BEHEMOTH},     // 1: behemothCrag
          {(uint16_t)CreatureCfg::Creature::BEHOLDER},     // 2: pillarOfEyes
          {(uint16_t)CreatureCfg::Creature::BLACK_KNIGHT}, // 3: hallOfDarkness
          {(uint16_t)CreatureCfg::Creature::BONE_DRAGON},  // 4: dragonVault
          {(uint16_t)CreatureCfg::Creature::CAVALIER},     // 5: trainingGrounds
          {(uint16_t)CreatureCfg::Creature::CENTAUR},      // 6: centaurStables
          {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL}, // 7: airConflux
          {(uint16_t)CreatureCfg::Creature::ANGEL},         // 8: portalOfGlory
          {(uint16_t)CreatureCfg::Creature::CYCLOPS},       // 9: cyclopsCave
          {(uint16_t)CreatureCfg::Creature::DEVIL},       // 10: forsakenPalace
          {(uint16_t)CreatureCfg::Creature::SERPENT_FLY}, // 11: serpentFlyHive
          {(uint16_t)CreatureCfg::Creature::DWARF},       // 12: dwarfCottage
          {(uint16_t)
               CreatureCfg::Creature::EARTH_ELEMENTAL},      // 13: earthConflux
          {(uint16_t)CreatureCfg::Creature::EFREETI},        // 14: fireLake
          {(uint16_t)CreatureCfg::Creature::WOOD_ELF},       // 15: homestead
          {(uint16_t)CreatureCfg::Creature::FIRE_ELEMENTAL}, // 16: fireConflux
          {(uint16_t)CreatureCfg::Creature::STONE_GARGOYLE}, // 17: parapet
          {(uint16_t)CreatureCfg::Creature::GENIE},        // 18: altarOfWishes
          {(uint16_t)CreatureCfg::Creature::WOLF_RIDER},   // 19: wolfPen
          {(uint16_t)CreatureCfg::Creature::GNOLL},        // 20: gnollHut
          {(uint16_t)CreatureCfg::Creature::GOBLIN},       // 21: goblinBarracks
          {(uint16_t)CreatureCfg::Creature::GOG},          // 22: hallOfSins
          {(uint16_t)CreatureCfg::Creature::GORGON},       // 23: gorgonLair
          {(uint16_t)CreatureCfg::Creature::GREEN_DRAGON}, // 24: dragonCliffs
          {(uint16_t)CreatureCfg::Creature::GRIFFIN},      // 25: griffinTower
          {(uint16_t)CreatureCfg::Creature::HARPY},        // 26: harpyLoft
          {(uint16_t)CreatureCfg::Creature::HELL_HOUND},   // 27: kennels
          {(uint16_t)CreatureCfg::Creature::HYDRA},        // 28: hydraPond
          {(uint16_t)CreatureCfg::Creature::IMP},          // 29: impCrucible
          {(uint16_t)CreatureCfg::Creature::LIZARDMAN},    // 30: lizardDen
          {(uint16_t)CreatureCfg::Creature::MAGE},         // 31: mageTower
          {(uint16_t)CreatureCfg::Creature::MANTICORE},    // 32: manticoreLair
          {(uint16_t)CreatureCfg::Creature::MEDUSA},       // 33: medusaChapel
          {(uint16_t)CreatureCfg::Creature::MINOTAUR},     // 34: labyrinth
          {(uint16_t)CreatureCfg::Creature::MONK},         // 35: monastery
          {(uint16_t)CreatureCfg::Creature::NAGA},         // 36: goldenPavilion
          {(uint16_t)CreatureCfg::Creature::DEMON},        // 37: demonGate
          {(uint16_t)CreatureCfg::Creature::OGRE},         // 38: ogreFort
          {(uint16_t)CreatureCfg::Creature::ORC},          // 39: orcTower
          {(uint16_t)CreatureCfg::Creature::PIT_FIEND},    // 40: hellHole
          {(uint16_t)CreatureCfg::Creature::RED_DRAGON},   // 41: dragonCave
          {(uint16_t)CreatureCfg::Creature::ROC},          // 42: cliffNest
          {(uint16_t)CreatureCfg::Creature::GREMLIN},      // 43: workshop
          {(uint16_t)CreatureCfg::Creature::GIANT},        // 44: cloudTemple
          {(uint16_t)
               CreatureCfg::Creature::DENDROID_GUARD},   // 45: dendroidArches
          {(uint16_t)CreatureCfg::Creature::TROGLODYTE}, // 46: warren
          {(uint16_t)
               CreatureCfg::Creature::WATER_ELEMENTAL}, // 47: waterConflux
          {(uint16_t)CreatureCfg::Creature::WIGHT},     // 48: tombOfSouls
          {(uint16_t)CreatureCfg::Creature::WYVERN},    // 49: wyvernNest
          {(uint16_t)CreatureCfg::Creature::PEGASUS},   // 50: enchantedSpring
          {(uint16_t)CreatureCfg::Creature::UNICORN},   // 51: unicornGladeBig
          {(uint16_t)CreatureCfg::Creature::LICH},      // 52: mausoleum
          {(uint16_t)CreatureCfg::Creature::VAMPIRE},   // 53: estate
          {(uint16_t)CreatureCfg::Creature::SKELETON},  // 54: cursedTemple
          {(uint16_t)CreatureCfg::Creature::WALKING_DEAD}, // 55: graveyard
          {(uint16_t)CreatureCfg::Creature::PIKEMAN},      // 56: guardhouse
          {(uint16_t)CreatureCfg::Creature::ARCHER},       // 57: archersTower
          {(uint16_t)CreatureCfg::Creature::SWORDSMAN},    // 58: barracks
          {(uint16_t)CreatureCfg::Creature::PIXIE},        // 59: magicLantern
          {(uint16_t)
               CreatureCfg::Creature::PSYCHIC_ELEMENTAL},  // 60: altarOfThought
          {(uint16_t)CreatureCfg::Creature::FIREBIRD},     // 61: pyre
          {(uint16_t)CreatureCfg::Creature::AZURE_DRAGON}, // 62: frozenCliffs
          {(uint16_t)
               CreatureCfg::Creature::CRYSTAL_DRAGON},      // 63: crystalCavern
          {(uint16_t)CreatureCfg::Creature::FAERIE_DRAGON}, // 64: magicForest
          {(uint16_t)CreatureCfg::Creature::RUST_DRAGON},   // 65: sulfurousLair
          {(uint16_t)CreatureCfg::Creature::ENCHANTER}, // 66: enchantersHollow
          {(uint16_t)CreatureCfg::Creature::SHARPSHOOTER},  // 67: treetopTower
          {(uint16_t)CreatureCfg::Creature::UNICORN},       // 68: unicornGlade
          {(uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL}, // 69: altarOfAir
          {(uint16_t)
               CreatureCfg::Creature::EARTH_ELEMENTAL},      // 70: altarOfEarth
          {(uint16_t)CreatureCfg::Creature::FIRE_ELEMENTAL}, // 71: altarOfFire
          {(uint16_t)
               CreatureCfg::Creature::WATER_ELEMENTAL}, // 72: altarOfWater
          {(uint16_t)CreatureCfg::Creature::HALFLING},  // 73: thatchedHut
          {(uint16_t)CreatureCfg::Creature::PEASANT},   // 74: hovel
          {(uint16_t)CreatureCfg::Creature::BOAR},      // 75: boarGlen
          {(uint16_t)CreatureCfg::Creature::MUMMY},     // 76: tombOfCurses
          {(uint16_t)CreatureCfg::Creature::NOMAD},     // 77: nomadTent
          {(uint16_t)CreatureCfg::Creature::ROGUE},     // 78: rogueCavern
          {(uint16_t)CreatureCfg::Creature::TROLL}      // 79: trollBridge
      },
      // cr2
      {},
      // cr3
      {},
      // cr4
      {{
           (uint16_t)CreatureCfg::Creature::AIR_ELEMENTAL,   // 层级 0: 气元素
           (uint16_t)CreatureCfg::Creature::WATER_ELEMENTAL, // 层级 1: 水元素
           (uint16_t)CreatureCfg::Creature::FIRE_ELEMENTAL,  // 层级 2: 火元素
           (uint16_t)CreatureCfg::Creature::EARTH_ELEMENTAL  // 层级 3: 土元素
       },
       {
           (uint16_t)CreatureCfg::Creature::IRON_GOLEM,   // 层级 0: 铁魔像
           (uint16_t)CreatureCfg::Creature::STONE_GOLEM,  // 层级 1: 石魔像
           (uint16_t)CreatureCfg::Creature::GOLD_GOLEM,   // 层级 2: 金魔像
           (uint16_t)CreatureCfg::Creature::DIAMOND_GOLEM // 层级 3: 钻石魔像
       }}};

  const static inline std::vector<std::vector<std::pair<uint8_t, uint16_t>>>
      dweCreGuard[] = {
          // cr1
          {},
          // cr2
          {},
          // cr3
          {},
          // cr4
          {{{12, (uint16_t)CreatureCfg::Creature::EARTH_ELEMENTAL}}}};
};