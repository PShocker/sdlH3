#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
struct DwellingCfg {
  const static inline std::vector<std::vector<std::string>> dweCreature[] = {
      {
          // cr1
          {"basilisk"},         // 0: basiliskPit
          {"behemoth"},         // 1: behemothCrag
          {"beholder"},         // 2: pillarOfEyes
          {"blackKnight"},      // 3: hallOfDarkness
          {"boneDragon"},       // 4: dragonVault
          {"cavalier"},         // 5: trainingGrounds
          {"centaur"},          // 6: centaurStables
          {"airElemental"},     // 7: airConflux
          {"angel"},            // 8: portalOfGlory
          {"cyclop"},           // 9: cyclopsCave
          {"devil"},            // 10: forsakenPalace
          {"serpentFly"},       // 11: serpentFlyHive
          {"dwarf"},            // 12: dwarfCottage
          {"earthElemental"},   // 13: earthConflux
          {"efreet"},           // 14: fireLake
          {"woodElf"},          // 15: homestead
          {"fireElemental"},    // 16: fireConflux
          {"stoneGargoyle"},    // 17: parapet
          {"genie"},            // 18: altarOfWishes
          {"goblinWolfRider"},  // 19: wolfPen
          {"gnoll"},            // 20: gnollHut
          {"goblin"},           // 21: goblinBarracks
          {"gog"},              // 22: hallOfSins
          {"gorgon"},           // 23: gorgonLair
          {"greenDragon"},      // 24: dragonCliffs
          {"griffin"},          // 25: griffinTower
          {"harpy"},            // 26: harpyLoft
          {"hellHound"},        // 27: kennels
          {"hydra"},            // 28: hydraPond
          {"imp"},              // 29: impCrucible
          {"lizardman"},        // 30: lizardDen
          {"mage"},             // 31: mageTower
          {"manticore"},        // 32: manticoreLair
          {"medusa"},           // 33: medusaChapel
          {"minotaur"},         // 34: labyrinth
          {"monk"},             // 35: monastery
          {"naga"},             // 36: goldenPavilion
          {"demon"},            // 37: demonGate
          {"ogre"},             // 38: ogreFort
          {"orc"},              // 39: orcTower
          {"pitFiend"},         // 40: hellHole
          {"redDragon"},        // 41: dragonCave
          {"roc"},              // 42: cliffNest
          {"gremlin"},          // 43: workshop
          {"giant"},            // 44: cloudTemple
          {"dendroidGuard"},    // 45: dendroidArches
          {"troglodyte"},       // 46: warren
          {"waterElemental"},   // 47: waterConflux
          {"wight"},            // 48: tombOfSouls
          {"wyvern"},           // 49: wyvernNest
          {"pegasus"},          // 50: enchantedSpring
          {"unicorn"},          // 51: unicornGladeBig
          {"lich"},             // 52: mausoleum
          {"vampire"},          // 53: estate
          {"skeleton"},         // 54: cursedTemple
          {"walkingDead"},      // 55: graveyard
          {"pikeman"},          // 56: guardhouse
          {"archer"},           // 57: archersTower
          {"swordsman"},        // 58: barracks
          {"pixie"},            // 59: magicLantern
          {"psychicElemental"}, // 60: altarOfThought
          {"firebird"},         // 61: pyre
          {"azureDragon"},      // 62: frozenCliffs
          {"crystalDragon"},    // 63: crystalCavern
          {"fairieDragon"},     // 64: magicForest
          {"rustDragon"},       // 65: sulfurousLair
          {"enchanter"},        // 66: enchantersHollow
          {"sharpshooter"},     // 67: treetopTower
          {"unicorn"},          // 68: unicornGlade
          {"airElemental"},     // 69: altarOfAir
          {"earthElemental"},   // 70: altarOfEarth
          {"fireElemental"},    // 71: altarOfFire
          {"waterElemental"},   // 72: altarOfWater
          {"halfling"},         // 73: thatchedHut
          {"peasant"},          // 74: hovel
          {"boar"},             // 75: boarGlen
          {"mummy"},            // 76: tombOfCurses
          {"nomad"},            // 77: nomadTent
          {"rogue"},            // 78: rogueCavern
          {"troll"}             // 79: trollBridge
      },
      // cr2
      {},
      //  cr3
      {},
      //  cr4
      {{
           "airElemental",   // 层级 0: 气元素
           "waterElemental", // 层级 1: 水元素
           "fireElemental",  // 层级 2: 火元素
           "earthElemental"  // 层级 3: 土元素
       },
       {
           "ironGolem",   // 层级 0: 铁魔像
           "stoneGolem",  // 层级 1: 石魔像
           "goldGolem",   // 层级 2: 金魔像
           "diamondGolem" // 层级 3: 钻石魔像
       }

      }};

  const static inline std::unordered_map<uint16_t, std::vector<uint16_t>>
      dweCreatureInc = {{57, {100}}};

  const static inline std::vector<std::vector<std::pair<uint8_t, std::string>>>
      dweCreGuard[] = {
          // cr1
          {},
          // cr2
          {},
          // cr3
          {},
          // cr4
          {{{12, "earthElemental"}}}};
};