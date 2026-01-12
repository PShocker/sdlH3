#include "Ent.h"
#include "Cfg/CreatureCfg.h"
#include "Cfg/DwellingCfg.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/SpellCfg.h"
#include "Cfg/TownCfg.h"
#include "Comp/AltarSacComp.h"
#include "Comp/ArenaComp.h"
#include "Comp/ArtifactComp.h"
#include "Comp/BoatComp.h"
#include "Comp/CampFireComp.h"
#include "Comp/CorpseComp.h"
#include "Comp/CreatureBankComp.h"
#include "Comp/DerelictShipComp.h"
#include "Comp/DragonUtComp.h"
#include "Comp/DwellingComp.h"
#include "Comp/FaerieRingComp.h"
#include "Comp/FlotsamComp.h"
#include "Comp/FouFortuneComp.h"
#include "Comp/FouYouthComp.h"
#include "Comp/FreeGuildComp.h"
#include "Comp/GarRevComp.h"
#include "Comp/GateComp.h"
#include "Comp/GrailComp.h"
#include "Comp/HeroComp.h"
#include "Comp/HillFortComp.h"
#include "Comp/HutMagComp.h"
#include "Comp/IdolFortuneComp.h"
#include "Comp/KnoTreeComp.h"
#include "Comp/LeanToComp.h"
#include "Comp/LearnStoneComp.h"
#include "Comp/LibraryComp.h"
#include "Comp/LightComp.h"
#include "Comp/MagEyeComp.h"
#include "Comp/MageGuildComp.h"
#include "Comp/MarketComp.h"
#include "Comp/MarlettoComp.h"
#include "Comp/MerCampComp.h"
#include "Comp/MermaidComp.h"
#include "Comp/MineComp.h"
#include "Comp/MonolithComp.h"
#include "Comp/MonsterComp.h"
#include "Comp/MysGarComp.h"
#include "Comp/OasisComp.h"
#include "Comp/ObeliskComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PandorBoxComp.h"
#include "Comp/PathComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/PrisonComp.h"
#include "Comp/PyramidComp.h"
#include "Comp/RalFlagComp.h"
#include "Comp/RefugeeComp.h"
#include "Comp/ResourceComp.h"
#include "Comp/SanctuaryComp.h"
#include "Comp/ScholarComp.h"
#include "Comp/SchoolMagComp.h"
#include "Comp/SchoolWarComp.h"
#include "Comp/SeaChestComp.h"
#include "Comp/ShipSurvivorComp.h"
#include "Comp/ShipWreckComp.h"
#include "Comp/ShrineMagicComp.h"
#include "Comp/SignComp.h"
#include "Comp/SirensComp.h"
#include "Comp/StablesComp.h"
#include "Comp/StarAxisComp.h"
#include "Comp/SwanPondComp.h"
#include "Comp/TavernComp.h"
#include "Comp/TempleComp.h"
#include "Comp/TerrainComp.h"
#include "Comp/TextureComp.h"
#include "Comp/TownComp.h"
#include "Comp/UniversComp.h"
#include "Comp/WagonComp.h"
#include "Comp/WarMachineFacComp.h"
#include "Comp/WarTombComp.h"
#include "Comp/WaterHoleComp.h"
#include "Comp/WaterWheelComp.h"
#include "Comp/WhirlpoolComp.h"
#include "Comp/WindMillComp.h"
#include "Comp/WitchHutComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mCreatureSet.h"
#include "H3mLoader/H3mHero.h"
#include "H3mLoader/H3mObject.h"
#include "Point/Point.h"
#include "SDL3/SDL_rect.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <cmath>
#include <cstdint>
#include <format>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

entt::entity Ent::loadBuild(uint8_t level, TownComp &townComp,
                            uint8_t buildId) {
  auto townId = townComp.id;
  entt::entity ent = entt::null;
  auto &registry = World::registrys[level];
  switch (buildId) {
  case (uint8_t)TownCfg::Building::BLACKSMITH: {
    ent = registry.create();
    auto wComp = &registry.emplace<WarMachineFacComp>(ent);
    wComp->warMachines = {{0, 1}, {1, 1}, {2, 1}};
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_LEVEL_1: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][0][0];
    dComp->creatures.push_back({std::vector<uint16_t>{creatures}, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_1: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][0];
    dComp->creatures.push_back({creatures, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_LEVEL_2: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][1][0];
    dComp->creatures.push_back({std::vector<uint16_t>{creatures}, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_2: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][1];
    dComp->creatures.push_back({creatures, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_LEVEL_3: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][2][0];
    dComp->creatures.push_back({std::vector<uint16_t>{creatures}, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_3: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][2];
    dComp->creatures.push_back({creatures, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_LEVEL_4: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][3][0];
    dComp->creatures.push_back({std::vector<uint16_t>{creatures}, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_4: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][3];
    dComp->creatures.push_back({creatures, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_LEVEL_5: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][4][0];
    dComp->creatures.push_back({std::vector<uint16_t>{creatures}, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_5: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][4];
    dComp->creatures.push_back({creatures, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_LEVEL_6: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][5][0];
    dComp->creatures.push_back({std::vector<uint16_t>{creatures}, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_6: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][5];
    dComp->creatures.push_back({creatures, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_LEVEL_7: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][6][0];
    dComp->creatures.push_back({std::vector<uint16_t>{creatures}, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_7: {
    ent = registry.create();
    auto dComp = &registry.emplace<DwellingComp>(ent);
    auto creatures = TownCfg::townCreature[townId][6];
    dComp->creatures.push_back({creatures, 0});
    break;
  }
  case (uint8_t)TownCfg::Building::MAGE_GUILD_1:
  case (uint8_t)TownCfg::Building::MAGE_GUILD_2:
  case (uint8_t)TownCfg::Building::MAGE_GUILD_3:
  case (uint8_t)TownCfg::Building::MAGE_GUILD_4:
  case (uint8_t)TownCfg::Building::MAGE_GUILD_5: {
    const uint8_t spellNums[] = {5, 4, 4, 3, 2};
    auto level = buildId - (uint8_t)TownCfg::Building::MAGE_GUILD_1 + 1;
    auto num = spellNums[level - 1];
    ent = registry.create();
    auto mComp = &registry.emplace<MageGuildComp>(ent);
    mComp->level = level;
    auto s = SpellCfg::SpellLevels[level];
    std::vector<uint8_t> r;
    std::sample(s.begin(), s.end(), std::back_inserter(r), num, Global::gen);
    mComp->spells = r;
    break;
  }

  default: {
    break;
  }
  }
  return ent;
}

static std::vector<std::pair<int16_t, int16_t>>
loadBlockTiles(H3mObject &object) {
  std::vector<std::pair<int16_t, int16_t>> blockTiles;
  int i = 0;
  for (auto usedTile : object.usedTiles) {
    for (auto used : usedTile) {
      if (used == 0x05) {
        blockTiles.push_back({-i % 8, -i / 8});
      }
      i++;
    }
  }
  return blockTiles;
}

static std::vector<std::pair<int16_t, int16_t>>
loadAccessTiles(H3mObject &object) {
  std::vector<std::pair<int16_t, int16_t>> accessTiles;
  int i = 0;
  for (auto usedTile : object.usedTiles) {
    for (auto used : usedTile) {
      if (used == 0x07) {
        accessTiles.push_back({-i % 8, -i / 8});
      }
      i++;
    }
  }
  return accessTiles;
}

static std::vector<std::pair<int16_t, int16_t>> loadMonsterAccessTiles() {
  std::vector<std::pair<int16_t, int16_t>> accessTiles = {
      {0, 0}, {-1, -1}, {0, -1}, {1, -1}, {-1, 0},
      {1, 0}, {-1, 1},  {0, 1},  {1, 1},
  };
  return accessTiles;
}

int64_t Ent::loadZorder(int32_t i, H3mObject &object) {
  int64_t z = 0;
  z += i;
  z += (ObjectType)object.id == ObjectType::HERO ? std::pow(10, 3) : 0;
  // z += (object.position[1] * 10000);
  z += (99 - loadBlockTiles(object).size()) * std::pow(10, 4);
  z += (object.position[1]) * std::pow(10, 6);
  z += (int64_t)(9 - object.printPriority / 100) * std::pow(10, 9);
  return z;
}

static entt::entity loadObj(H3mObject &object, uint32_t i) {
  uint8_t level = object.position[2];
  auto &registry = World::registrys[level];
  auto ent = registry.create();
  auto textureComp = &registry.emplace<TextureComp>(ent);
  std::string texturePath = object.name + "/0";
  uint8_t flip = SDL_FLIP_NONE;
  switch ((ObjectType)object.id) {
  case ObjectType::RANDOM_HERO: {
    auto hero = std::any_cast<H3mHero>(object.data["hero"]);
    hero.subId = 0;
    hero.portrait = 0;
    object.data["hero"] = hero;
    object.id = (uint32_t)ObjectType::HERO;
  }
  case ObjectType::HERO: {
    auto direct = std::any_cast<uint8_t>(object.data["direct"]);
    texturePath = std::format("AH{:02d}_.def/{}", object.subId, direct);
    flip = std::any_cast<uint8_t>(object.data["flip"]);
    auto heroComp = &registry.emplace<HeroComp>(ent);
    if (object.data.contains("moveType")) {
      heroComp->moveType = std::any_cast<uint8_t>(object.data["moveType"]);
    }
    auto hero = std::any_cast<H3mHero>(object.data["hero"]);
    auto playerIdComp = &registry.emplace<PlayerIdComp>(ent);
    playerIdComp->id = hero.playerId;
    heroComp->subId = object.subId;
    heroComp->portrait = hero.portrait == 0xff ? hero.subId : hero.portrait;
    heroComp->movement = 65535;
    heroComp->mana = 500;
    heroComp->exp = hero.exp;
    heroComp->level = 1;
    if (hero.secSkills.empty()) {
      auto secSkills = HeroCfg::heroSecSkills.at(heroComp->portrait);
      heroComp->secSkills = secSkills;
    } else {
      heroComp->secSkills = hero.secSkills;
      for (auto &p : heroComp->secSkills) {
        p.second -= 1;
      }
    }
    heroComp->creatures = hero.creatureSet.creatures;
    if (heroComp->creatures.empty()) {
      //
      for (auto pair : HeroCfg::heroCreatures[heroComp->portrait]) {
        switch (pair.first) {
        case (uint16_t)CreatureCfg::Creature::CATAPULT:
        case (uint16_t)CreatureCfg::Creature::BALLISTA:
        case (uint16_t)CreatureCfg::Creature::FIRST_AID_TENT:
        case (uint16_t)CreatureCfg::Creature::AMMO_CART: {
          break;
        }
        default: {
          heroComp->creatures.push_back(pair);
          break;
        }
        }
      }
    }
    heroComp->creatures.resize(7, {0xffff, 0});

    heroComp->spells = hero.spells;
    heroComp->artifactsInBackpack = hero.artifactsInBackpack;
    heroComp->artifacts = hero.artifacts;
    if (heroComp->artifacts.empty()) {
      heroComp->artifacts.assign(19, 0xffff);
    }
    if (object.data.contains("heroDefaultPrimSkills")) {
      heroComp->primSkills = HeroCfg::heroPrimarySkills.at(object.subId);
    } else {
      heroComp->primSkills = hero.primSkills;
    }

    heroComp->flagEnt = registry.create();
    auto flagEnt = heroComp->flagEnt;
    auto flagPositionComp = &registry.emplace<PositionComp>(flagEnt);
    auto flagTextureComp = &registry.emplace<TextureComp>(flagEnt);
    flagPositionComp->point =
        SDL_FPoint{static_cast<float>((object.position[0] - 2) * 32),
                   static_cast<float>((object.position[1] - 1) * 32)};
    flagPositionComp->flip = flip;
    flagPositionComp->z = Ent::loadZorder(i, object);
    flagTextureComp->path =
        std::format("AF0{}.def/{}", playerIdComp->id, direct);
    break;
  }
  case ObjectType::RANDOM_TOWN: {
    auto buildings =
        std::any_cast<std::set<uint8_t>>(object.data["builtBuildings"]);
    object.subId = 0;
    object.data["builtBuildings"] = buildings;
  }
  case ObjectType::TOWN: {
    auto townComp = &registry.emplace<TownComp>(ent);
    townComp->id = object.subId;
    townComp->garCreatures =
        std::any_cast<H3mCreatureSet>(object.data["creatureSet"]).creatures;
    if (townComp->garCreatures.empty()) {
      townComp->garCreatures.assign(7, {0xffff, 0});
    }

    townComp->forbidBuildings =
        std::any_cast<std::set<uint8_t>>(object.data["forbidBuildings"]);
    townComp->obligatorySpells =
        std::any_cast<std::set<uint8_t>>(object.data["obligatorySpells"]);
    townComp->possibleSpells =
        std::any_cast<std::set<uint8_t>>(object.data["possibleSpells"]);

    auto playerIdComp = &registry.emplace<PlayerIdComp>(ent);
    playerIdComp->id = std::any_cast<uint8_t>(object.data["playerId"]);
    playerIdComp->id = playerIdComp->id == 0xff ? 8 : playerIdComp->id;
    // townName
    townComp->nameIndex = 0;
    for (auto i : {0, 1}) {
      auto &r = World::registrys[i];
      for (auto [e, tComp] : r.view<TownComp>().each()) {
        if (e == ent) {
          continue;
        }
        if (tComp.id == townComp->id) {
          townComp->nameIndex++;
        }
      }
    }
    townComp->nameIndex = townComp->nameIndex % 16;
    townComp->heroEnt = {std::nullopt, std::nullopt};

    auto buildings =
        std::any_cast<std::set<uint8_t>>(object.data["builtBuildings"]);
    std::unordered_map<uint8_t, entt::entity> builds;
    for (auto i : buildings) {
      builds[i] = Ent::loadBuild(level, *townComp, i);
    }
    townComp->buildings = builds;

    texturePath = texturePath + "/" + std::to_string(playerIdComp->id);
    break;
  }
  case ObjectType::WAR_MACHINE_FACTORY: {
    auto wComp = &registry.emplace<WarMachineFacComp>(ent);
    wComp->warMachines = {{0, 1}, {1, 1}, {2, 1}, {2, 1}};
    break;
  }
  case ObjectType::CREATURE_GENERATOR1:
  case ObjectType::CREATURE_GENERATOR2:
  case ObjectType::CREATURE_GENERATOR3:
  case ObjectType::CREATURE_GENERATOR4: {
    auto dwellingComp = &registry.emplace<DwellingComp>(ent);
    dwellingComp->id = object.subId;

    auto creatures =
        DwellingCfg::dweCreature[object.id -
                                 (uint8_t)ObjectType::CREATURE_GENERATOR1]
            .at(object.subId);
    for (auto creature : creatures) {
      dwellingComp->creatures.push_back(
          {std::vector<uint16_t>{creature},
           CreatureCfg::creatureGrowth.at(creature)});
    }
    auto playerIdComp = &registry.emplace<PlayerIdComp>(ent);
    playerIdComp->id = std::any_cast<uint8_t>(object.data["playerId"]);
    playerIdComp->id = playerIdComp->id == 0xff ? 8 : playerIdComp->id;
    texturePath = texturePath + "/" + std::to_string(playerIdComp->id);
    break;
  }
  case ObjectType::GARRISON:
  case ObjectType::GARRISON2: {
    auto playerIdComp = &registry.emplace<PlayerIdComp>(ent);
    playerIdComp->id = std::any_cast<uint8_t>(object.data["playerId"]);
    playerIdComp->id = playerIdComp->id == 0xff ? 8 : playerIdComp->id;
    texturePath = texturePath + "/" + std::to_string(playerIdComp->id);
    break;
  }
  case ObjectType::ABANDONED_MINE:
  case ObjectType::MINE: {
    auto mineComp = &registry.emplace<MineComp>(ent);
    mineComp->id = object.subId;
    auto playerIdComp = &registry.emplace<PlayerIdComp>(ent);
    playerIdComp->id = std::any_cast<uint8_t>(object.data["playerId"]);
    playerIdComp->id = playerIdComp->id == 0xff ? 8 : playerIdComp->id;
    texturePath = texturePath + "/" + std::to_string(playerIdComp->id);
    break;
  }

  case ObjectType::SHIPYARD: {
    auto playerIdComp = &registry.emplace<PlayerIdComp>(ent);
    playerIdComp->id = std::any_cast<uint8_t>(object.data["playerId"]);
    playerIdComp->id = playerIdComp->id == 0xff ? 8 : playerIdComp->id;
    texturePath = texturePath + "/" + std::to_string(playerIdComp->id);
    break;
  }
  case ObjectType::SUBTERRANEAN_GATE: {
    auto gateComp = &registry.emplace<GateComp>(ent);
    gateComp->x = object.position[0];
    gateComp->y = object.position[1];
    gateComp->order = i;
    gateComp->level = 255;
    break;
  }
  case ObjectType::RANDOM_MONSTER: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] <= 7 &&
            CreatureCfg::creatureLevel[i] >= 1) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    auto monsterComp = &registry.emplace<MonsterComp>(ent);

    break;
  }
  case ObjectType::RANDOM_MONSTER_L1: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] == 1) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    texturePath = CreatureCfg::creatureGraphicsMini[0] + "/" + "0";
    auto monsterComp = &registry.emplace<MonsterComp>(ent);
    break;
  }
  case ObjectType::RANDOM_MONSTER_L2: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] == 2) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    auto monsterComp = &registry.emplace<MonsterComp>(ent);

    break;
  }
  case ObjectType::RANDOM_MONSTER_L3: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] == 3) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    auto monsterComp = &registry.emplace<MonsterComp>(ent);

    break;
  }
  case ObjectType::RANDOM_MONSTER_L4: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] == 4) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    auto monsterComp = &registry.emplace<MonsterComp>(ent);

    break;
  }
  case ObjectType::RANDOM_MONSTER_L5: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] == 5) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    auto monsterComp = &registry.emplace<MonsterComp>(ent);

    break;
  }
  case ObjectType::RANDOM_MONSTER_L6: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] == 6) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    auto monsterComp = &registry.emplace<MonsterComp>(ent);

    break;
  }
  case ObjectType::RANDOM_MONSTER_L7: {
    static std::vector<uint8_t> creatures;
    if (creatures.empty()) {
      for (int i = 0; i < CreatureCfg::creatureLevel.size(); ++i) {
        if (CreatureCfg::creatureLevel[i] == 7) {
          creatures.push_back(i);
        }
      }
    }
    int randomIndex = std::rand() % creatures.size();
    auto monsterComp = &registry.emplace<MonsterComp>(ent);
    break;
  }

  case ObjectType::MONSTER: {
    auto monsterComp = &registry.emplace<MonsterComp>(ent);
    monsterComp->id = object.subId;
    break;
  }
  case ObjectType::BOAT: {
    auto boatComp = &registry.emplace<BoatComp>(ent);
    boatComp->path = object.name;
    if (BoatComp::boatMap.contains(object.name)) {
      boatComp->path = BoatComp::boatMap.at(object.name);
    }
    auto direct = std::any_cast<uint8_t>(object.data["direct"]);
    flip = std::any_cast<uint8_t>(object.data["flip"]);
    texturePath = boatComp->path + "/" + std::to_string(direct);
    break;
  }
  case ObjectType::ARTIFACT: {
    auto artifactComp = &registry.emplace<ArtifactComp>(ent);
    artifactComp->id = object.subId;
    if (object.data.contains("message")) {
      artifactComp->message =
          std::any_cast<std::string>(object.data["message"]);
    }
    if (object.data.contains("guards")) {
      artifactComp->guards =
          std::any_cast<H3mCreatureSet>(object.data["guards"]).creatures;
    }
    break;
  }
  case ObjectType::RANDOM_RESOURCE: {
    int a = 0;
    break;
  }
  case ObjectType::RESOURCE: {
    auto resourceComp = &registry.emplace<ResourceComp>(ent);
    resourceComp->id = object.subId;
    resourceComp->count = std::any_cast<uint32_t>(object.data["amount"]);
    if (object.data.contains("message")) {
      resourceComp->message =
          std::any_cast<std::string>(object.data["message"]);
    }
    if (object.data.contains("guards")) {
      resourceComp->guards =
          std::any_cast<H3mCreatureSet>(object.data["guards"]).creatures;
    }
    break;
  }
  case ObjectType::UNIVERSITY: {
    auto universComp = &registry.emplace<UniversComp>(ent);
    universComp->secSkills = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},
    };
    break;
  }
  case ObjectType::TAVERN: {
    registry.emplace<TavernComp>(ent);
    break;
  }
  case ObjectType::WINDMILL: {
    auto wComp = &registry.emplace<WindMillComp>(ent);
    std::uniform_int_distribution<int> dis(0, 6);
    wComp->resources = {{dis(Global::gen), dis(Global::gen)}};
    break;
  }
  case ObjectType::WATER_WHEEL: {
    auto wComp = &registry.emplace<WaterWheelComp>(ent);
    std::uniform_int_distribution<int> dis(0, 6);
    wComp->resources = {{dis(Global::gen), dis(Global::gen)}};
    break;
  }
  case ObjectType::WARRIORS_TOMB: {
    auto warTombComp = &registry.emplace<WarTombComp>(ent);
    warTombComp->artId = (std::rand() % 7) + 1;
    break;
  }
  case ObjectType::SIGN: {
    auto signComp = &registry.emplace<SignComp>(ent);
    signComp->message = std::any_cast<std::string>(object.data["message"]);
    break;
  }
  case ObjectType::PANDORAS_BOX: {
    auto pandorBoxComp = &registry.emplace<PandorBoxComp>(ent);
    if (object.data.contains("message")) {
      pandorBoxComp->message = std::any_cast<decltype(pandorBoxComp->message)>(
          object.data["message"]);
    } else {
      pandorBoxComp->message = "";
    }
    if (object.data.contains("guards")) {
      pandorBoxComp->guards = std::any_cast<decltype(pandorBoxComp->guards)>(
          object.data["message"]);
    } else {
      pandorBoxComp->guards.assign(7, {0xffff, 0});
    }
    pandorBoxComp->manaDiff = std::any_cast<decltype(pandorBoxComp->manaDiff)>(
        object.data["manaDiff"]);
    pandorBoxComp->morale =
        std::any_cast<decltype(pandorBoxComp->morale)>(object.data["morale"]);
    pandorBoxComp->resources =
        std::any_cast<decltype(pandorBoxComp->resources)>(
            object.data["resources"]);
    pandorBoxComp->luck =
        std::any_cast<decltype(pandorBoxComp->luck)>(object.data["luck"]);
    pandorBoxComp->heroExperience =
        std::any_cast<decltype(pandorBoxComp->heroExperience)>(
            object.data["heroExperience"]);
    pandorBoxComp->primary =
        std::any_cast<decltype(pandorBoxComp->primary)>(object.data["primary"]);
    pandorBoxComp->secSkills =
        std::any_cast<decltype(pandorBoxComp->secSkills)>(
            object.data["secondary"]);
    pandorBoxComp->creatures =
        std::any_cast<decltype(pandorBoxComp->creatures)>(
            object.data["creatures"]);
    pandorBoxComp->artifacts =
        std::any_cast<decltype(pandorBoxComp->artifacts)>(
            object.data["artifacts"]);
    pandorBoxComp->spells =
        std::any_cast<decltype(pandorBoxComp->spells)>(object.data["spells"]);
    break;
  }
  case ObjectType::BLACK_MARKET: {
    auto marketComp = &registry.emplace<MarketComp>(ent);
    marketComp->type = 2;
    marketComp->artifacts = {1, 2, 3, 4, 5, 6, 7};
    break;
  }
  case ObjectType::REFUGEE_CAMP: {
    registry.emplace<RefugeeComp>(ent);
    registry.emplace<DwellingComp>(ent);
    break;
  }
  case ObjectType::LEARNING_STONE: {
    registry.emplace<LearnStoneComp>(ent);
    break;
  }
  case ObjectType::TEMPLE: {
    registry.emplace<TempleComp>(ent);
    break;
  }
  case ObjectType::RALLY_FLAG: {
    registry.emplace<RalFlagComp>(ent);
    break;
  }
  case ObjectType::SCHOLAR: {
    auto sComp = &registry.emplace<ScholarComp>(ent);
    auto bonusTypeRaw = std::any_cast<uint8_t>(object.data["bonusTypeRaw"]);
    auto bonusID = std::any_cast<uint8_t>(object.data["bonusID"]);
    if (bonusTypeRaw == 0xff) {
      bonusTypeRaw = 0;
      bonusID = 0;
    }
    switch (bonusTypeRaw) {
    case 0: {
      sComp->primId = bonusID;
      break;
    }
    case 1: {
      sComp->secId = bonusID;
      break;
    }
    case 2: {
      sComp->splId = bonusID;
      break;
    }
    default: {
      break;
    }
    }
    break;
  }
  case ObjectType::SHRINE_OF_MAGIC_GESTURE: {
    auto shrMagComp = &registry.emplace<ShrineMagicComp>(ent);
    shrMagComp->level = 1;
    if (object.data.contains("spell")) {
      shrMagComp->spellId = std::any_cast<uint8_t>(object.data["spell"]);
    } else {
      auto &spells = SpellCfg::SpellLevels[shrMagComp->level];
      shrMagComp->spellId = spells[std::rand() % spells.size()];
    }
    break;
  }
  case ObjectType::SHRINE_OF_MAGIC_INCANTATION: {
    auto shrMagComp = &registry.emplace<ShrineMagicComp>(ent);
    shrMagComp->level = 0;
    if (object.data.contains("spell")) {
      shrMagComp->spellId = std::any_cast<uint8_t>(object.data["spell"]);
    } else {
      auto spells = SpellCfg::SpellLevels[shrMagComp->level];
      shrMagComp->spellId = spells[std::rand() % spells.size()];
    }
    break;
  }
  case ObjectType::SHRINE_OF_MAGIC_THOUGHT: {
    auto shrMagComp = &registry.emplace<ShrineMagicComp>(ent);
    shrMagComp->level = 2;
    if (object.data.contains("spell")) {
      shrMagComp->spellId = std::any_cast<uint8_t>(object.data["spell"]);
    } else {
      auto spells = SpellCfg::SpellLevels[shrMagComp->level];
      shrMagComp->spellId = spells[std::rand() % spells.size()];
    }
    break;
  }
  case ObjectType::STAR_AXIS: {
    registry.emplace<StarAxisComp>(ent);
    break;
  }
  case ObjectType::PYRAMID: {
    registry.emplace<PyramidComp>(ent);
    break;
  }
  case ObjectType::SANCTUARY: {
    registry.emplace<SanctuaryComp>(ent);
    break;
  }
  case ObjectType::SHIPWRECK: {
    auto sComp = &registry.emplace<ShipWreckComp>(ent);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double rValue = dis(Global::gen);
    if (rValue < 0.3) {        // 30% 概率
                               // 10幽灵 + 2000金币
    } else if (rValue < 0.6) { // 30% 概率
                               // 15幽灵 + 3000金币
    } else if (rValue < 0.9) { // 30% 概率
                               // 25幽灵 + 4000金币 + 1级宝物
    } else {                   // 10% 概率
                               // 50幽灵 + 5000金币 + 2级宝物
    }
    break;
  }
  case ObjectType::DERELICT_SHIP: {
    auto sComp = &registry.emplace<DerelictShipComp>(ent);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double rValue = dis(Global::gen);
    if (rValue < 0.3) {

    } else if (rValue < 0.6) {

    } else if (rValue < 0.9) {

    } else {
    }
    break;
  }
  case ObjectType::SHIPWRECK_SURVIVOR: {
    auto sComp = &registry.emplace<ShipSurvivorComp>(ent);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double rValue = dis(Global::gen);
    if (rValue < 0.55) {

    } else if (rValue < 0.75) {

    } else if (rValue < 0.95) {

    } else {
    }
    break;
  }
  case ObjectType::CREATURE_BANK: {
    auto cComp = &registry.emplace<CreatureBankComp>(ent);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double rValue = dis(Global::gen);
    if (rValue < 0.55) {

    } else if (rValue < 0.75) {

    } else if (rValue < 0.95) {

    } else {
    }
    break;
  }
  case ObjectType::SEA_CHEST: {
    auto sComp = &registry.emplace<SeaChestComp>(ent);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double rValue = dis(Global::gen);
    if (rValue < 0.2) {
      sComp->artifacts.clear();
      sComp->resources.push_back({0, 1});
    } else if (rValue < 0.9) {
      sComp->artifacts.clear();
      sComp->resources.push_back({6, 1500});
    } else {
      sComp->artifacts.push_back(0);
      sComp->resources.clear();
    }
    break;
  }
  case ObjectType::WITCH_HUT: {
    registry.emplace<WitchHutComp>(ent);
    break;
  }
  case ObjectType::PRISON: {
    registry.emplace<PrisonComp>(ent);
    auto hero = std::any_cast<H3mHero>(object.data["hero"]);
    auto heroComp = &registry.emplace<HeroComp>(ent);
    heroComp->subId = 0;
    heroComp->portrait = hero.portrait == 0xff ? hero.subId : hero.portrait;
    heroComp->exp = hero.exp;
    heroComp->primSkills = hero.primSkills;
    heroComp->artifacts = hero.artifacts;
    heroComp->artifactsInBackpack = hero.artifactsInBackpack;
    heroComp->creatures = hero.creatureSet.creatures;
    heroComp->spells = hero.spells;
    heroComp->secSkills = hero.secSkills;
    heroComp->moveType = HeroComp::HORSE;
    break;
  }
  case ObjectType::MONOLITH_TWO_WAY: {
    auto monoComp = &registry.emplace<MonolithComp>(ent);
    monoComp->x = object.position[0];
    monoComp->y = object.position[1];
    monoComp->order = i;
    monoComp->twoWay = true;
    monoComp->id = object.subId;
    break;
  }
  case ObjectType::MONOLITH_ONE_WAY_ENTRANCE: {
    auto monoComp = &registry.emplace<MonolithComp>(ent);
    monoComp->x = object.position[0];
    monoComp->y = object.position[1];
    monoComp->order = i;
    monoComp->twoWay = false;
    monoComp->entrance = true;
    monoComp->id = object.subId;
    break;
  }
  case ObjectType::MONOLITH_ONE_WAY_EXIT: {
    auto monoComp = &registry.emplace<MonolithComp>(ent);
    monoComp->x = object.position[0];
    monoComp->y = object.position[1];
    monoComp->order = i;
    monoComp->twoWay = false;
    monoComp->entrance = false;
    monoComp->id = object.subId;
    break;
  }
  case ObjectType::SCHOOL_OF_WAR: {
    registry.emplace<SchoolWarComp>(ent);
    break;
  }
  case ObjectType::SCHOOL_OF_MAGIC: {
    registry.emplace<SchoolMagComp>(ent);
    break;
  }
  case ObjectType::IDOL_OF_FORTUNE: {
    registry.emplace<IdolFortuneComp>(ent);
    break;
  }
  case ObjectType::FOUNTAIN_OF_FORTUNE: {
    registry.emplace<FouFortuneComp>(ent);
    break;
  }
  case ObjectType::CAMPFIRE: {
    auto cfComp = &registry.emplace<CampFireComp>(ent);
    cfComp->resources = {{0, 5}, {6, 500}};
    break;
  }
  case ObjectType::CORPSE: {
    auto cpComp = &registry.emplace<CorpseComp>(ent);

    break;
  }
  case ObjectType::MARLETTO_TOWER: {
    auto cpComp = &registry.emplace<MarlettoComp>(ent);

    break;
  }
  case ObjectType::DRAGON_UTOPIA: {
    auto duComp = &registry.emplace<DragonUtComp>(ent);
    break;
  }
  case ObjectType::CRYPT: {
    break;
  }
  case ObjectType::WHIRLPOOL: {
    auto wComp = &registry.emplace<WhirlpoolComp>(ent);
    wComp->x = object.position[0];
    wComp->y = object.position[1];
    wComp->order = i;
    break;
  }
  case ObjectType::ARENA: {
    auto aComp = &registry.emplace<ArenaComp>(ent);
    break;
  }
  case ObjectType::LIGHTHOUSE: {
    registry.emplace<LightComp>(ent);
    break;
  }
  case ObjectType::MERMAID: {
    registry.emplace<MermaidComp>(ent);
    break;
  }
  case ObjectType::MERCENARY_CAMP: {
    registry.emplace<MerCampComp>(ent);
    break;
  }
  case ObjectType::LIBRARY_OF_ENLIGHTENMENT: {
    registry.emplace<LibraryComp>(ent);
    break;
  }
  case ObjectType::STABLES: {
    registry.emplace<StablesComp>(ent);
    break;
  }
  case ObjectType::EYE_OF_MAGI: {
    registry.emplace<MagEyeComp>(ent);
    break;
  }
  case ObjectType::HUT_OF_MAGI: {
    registry.emplace<HutMagComp>(ent);
    break;
  }
  case ObjectType::FLOTSAM: {
    auto fComp = &registry.emplace<FlotsamComp>(ent);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double rValue = dis(Global::gen);
    if (rValue < 0.25) {
      fComp->resources = {{0, 1}};
    } else if (rValue < 0.5) {
      fComp->resources = {{0, 5}};
    } else if (rValue < 0.75) {
      fComp->resources = {{0, 5}, {6, 200}};
    } else {
      fComp->resources = {{0, 10}, {6, 500}};
    }
    break;
  }
  case ObjectType::SIRENS: {
    registry.emplace<SirensComp>(ent);
    break;
  }
  case ObjectType::HILL_FORT: {
    // APHLFTBK.pcx
    registry.emplace<HillFortComp>(ent);
    break;
  }
  case ObjectType::FOUNTAIN_OF_YOUTH: {
    registry.emplace<FouYouthComp>(ent);
    break;
  }
  case ObjectType::OASIS: {
    registry.emplace<OasisComp>(ent);
    break;
  }
  case ObjectType::WATERING_HOLE: {
    registry.emplace<WaterHoleComp>(ent);
    break;
  }
  case ObjectType::GARDEN_OF_REVELATION: {
    registry.emplace<GarRevComp>(ent);
    break;
  }
  case ObjectType::FAERIE_RING: {
    registry.emplace<FaerieRingComp>(ent);
    break;
  }
  case ObjectType::LEAN_TO: {
    auto lComp = &registry.emplace<LeanToComp>(ent);
    lComp->resources = {{0, 5}, {6, 200}};
    break;
  }
  case ObjectType::FREELANCERS_GUILD: {
    auto marketComp = &registry.emplace<MarketComp>(ent);
    marketComp->type = (uint8_t)Enum::MARKET::CRE_SELL;
    registry.emplace<FreeGuildComp>(ent);
    break;
  }
  case ObjectType::ALTAR_OF_SACRIFICE: {
    registry.emplace<AltarSacComp>(ent);
    break;
  }
  case ObjectType::SWAN_POND: {
    registry.emplace<SwanPondComp>(ent);
    break;
  }
  case ObjectType::MYSTICAL_GARDEN: {
    registry.emplace<MysGarComp>(ent);
    break;
  }
  case ObjectType::OBELISK: {
    registry.emplace<ObeliskComp>(ent);
    break;
  }
  case ObjectType::GRAIL: {
    registry.emplace<GrailComp>(ent);
    break;
  }
  case ObjectType::WAGON: {
    registry.emplace<WagonComp>(ent);
    break;
  }
  case ObjectType::COVER_OF_DARKNESS: {
    registry.emplace<WagonComp>(ent);
    break;
  }
  case ObjectType::TREE_OF_KNOWLEDGE: {
    registry.emplace<KnoTreeComp>(ent);
    break;
  }
  case ObjectType::TRADING_POST: {
    auto &mComp = registry.emplace<MarketComp>(ent);
    mComp.type = 0;
    break;
  }
  default: {
    break;
  }
  }
  textureComp->path = texturePath;

  auto objectComp = &registry.emplace<ObjectComp>(ent);
  objectComp->type = object.id;
  objectComp->x = object.position[0];
  objectComp->y = object.position[1];
  objectComp->blockTiles = loadBlockTiles(object);
  if ((ObjectType)object.id == ObjectType::MONSTER) {
    objectComp->accessTiles = loadMonsterAccessTiles();
  } else {
    objectComp->accessTiles = loadAccessTiles(object);
  }
  auto texture = Global::defCache.at(texturePath)[0];

  auto positionComp = &registry.emplace<PositionComp>(ent);
  positionComp->point = {
      static_cast<float>((object.position[0] + 1) * 32 - texture[0].w),
      static_cast<float>((object.position[1] + 1) * 32 - texture[0].h)};
  positionComp->flip = flip;
  positionComp->z = Ent::loadZorder(i, object);
  return ent;
}

entt::entity Ent::loadHero(HeroComp &heroComp, uint8_t playerId, uint8_t x,
                           uint8_t y, uint8_t level, uint8_t direct,
                           uint8_t flip) {
  H3mObject object;
  H3mHero hero;
  hero.playerId = playerId;
  hero.portrait = heroComp.portrait;
  hero.creatureSet = H3mCreatureSet(heroComp.creatures);
  hero.primSkills = heroComp.primSkills;
  hero.artifacts = heroComp.artifacts;
  hero.artifactsInBackpack = heroComp.artifactsInBackpack;
  hero.exp = heroComp.exp;
  hero.spells = heroComp.spells;
  for (auto &p : heroComp.secSkills) {
    p.second += 1;
  }
  hero.secSkills = heroComp.secSkills;
  object.printPriority = 0;
  object.id = (uint8_t)ObjectType::HERO;
  object.subId = heroComp.subId;
  object.position[0] = x;
  object.position[1] = y;
  object.position[2] = level;
  object.data["hero"] = hero;
  object.data["direct"] = (uint8_t)direct;
  object.data["flip"] = (uint8_t)flip;
  object.data["moveType"] = (uint8_t)heroComp.moveType;
  object.usedTiles = {{0x01, 0x07}};
  World::needSort = true;

  return loadObj(object, 0);
}

entt::entity Ent::loadBoat(const std::string &path, uint8_t x, uint8_t y,
                           uint8_t level, uint8_t direct, uint8_t flip) {
  H3mObject object;
  object.printPriority = 0;
  object.id = (uint8_t)ObjectType::BOAT;
  object.position[0] = x;
  object.position[1] = y;
  object.position[2] = level;
  object.data["direct"] = (uint8_t)direct;
  object.data["flip"] = (uint8_t)flip;
  object.usedTiles = {{0x01, 0x07}};
  object.name = path;
  World::needSort = true;

  return loadObj(object, 0);
}
void Ent::loadPath(std::vector<SDL_Point> &path, entt::entity heroEnt,
                   uint16_t indexCost) {

  auto &registry = World::registrys[World::level];
  std::vector<entt::entity> pathEnts;
  SDL_FPoint lastPoint{static_cast<float>(path[0].x),
                       static_cast<float>(path[0].y)};
  for (uint32_t i = 1; i < path.size(); i++) {
    auto ent = registry.create();
    auto positionComp = &registry.emplace<PositionComp>(ent);
    positionComp->point = {static_cast<float>(path[i].x * 32),
                           static_cast<float>(path[i].y * 32)};
    positionComp->z = INT64_MAX;

    auto textureComp = &registry.emplace<TextureComp>(ent);
    SDL_FPoint point{static_cast<float>(path[i].x),
                     static_cast<float>(path[i].y)};
    auto direct = direction(point, lastPoint);

    textureComp->path = "adag.def/";
    if (i == path.size() - 1) {
      direct = 0;
    } else {
      direct += 9;
    }
    if (indexCost < i) {
      direct += 25;
    }
    textureComp->path = textureComp->path + std::to_string(direct);
    lastPoint = SDL_FPoint{static_cast<float>(path[i].x),
                           static_cast<float>(path[i].y)};

    registry.emplace<PathComp>(ent);
    pathEnts.push_back(ent);
  }
  registry.get<HeroComp>(heroEnt).pathEnts = pathEnts;
  World::needSort = true;
}

static void loadTerrain(H3mData &data) {
  for (auto &terrain : Global::terrains) {
    terrain.resize(data.header.height);
    for (auto &i : terrain) {
      i.resize(data.header.width);
    }
  }
  auto loadTerrainInternal =
      [width = data.header.width](int i, const std::string &filePath,
                                  uint8_t view, uint8_t rotationFlags,
                                  int zOrder, uint8_t index) {
        uint8_t level = (i >= width * width) ? 1 : 0;

        auto &registry = World::registrys[level];
        auto ent = registry.create();

        auto textureComp = &registry.emplace<TextureComp>(ent);
        textureComp->path = filePath + "/" + std::to_string(view);

        auto positionComp = &registry.emplace<PositionComp>(ent);
        positionComp->point = {static_cast<float>(i % width * 32),
                               static_cast<float>((i / width % width) * 32)};
        positionComp->flip = SDL_FLIP_NONE;

        if (rotationFlags & 0b01) {
          positionComp->flip = positionComp->flip | SDL_FLIP_HORIZONTAL;
        }
        if (rotationFlags & 0b10) {
          positionComp->flip = positionComp->flip | SDL_FLIP_VERTICAL;
        }
        positionComp->z = zOrder;

        auto terrainComp = &registry.emplace<TerrainComp>(ent);
        terrainComp->index = index;

        Global::terrains[level][i % width][(i / width) % width].push_back(ent);
        return;
      };
  for (int i = 0; i < data.terrains.size(); i++) {
    auto &terrain = data.terrains[i];
    std::string path;
    switch (terrain.terrainType) {
    case 0: {
      path = "DIRTTL.def";
      break;
    }
    case 1: {
      path = "SANDTL.def";
      break;
    }
    case 2: {
      path = "GRASTL.def";
      break;
    }
    case 3: {
      path = "SNOWTL.def";
      break;
    }
    case 4: {
      path = "SWMPTL.def";
      break;
    }
    case 5: {
      path = "ROUGTL.def";
      break;
    }
    case 6: {
      path = "SUBBTL.def";
      break;
    }
    case 7: {
      path = "LAVATL.def";
      break;
    }
    case 8: {
      path = "WATRTL.def";
      break;
    }
    case 9: {
      path = "ROCKTL.def";
      break;
    }
    default: {
      // 处理未知地形类型的逻辑
      path = "UNKNOWN.def"; // 或者抛出异常等其他处理方式
      break;
    }
    }
    loadTerrainInternal(i, path, terrain.terView,
                        terrain.extTileFlags & 0b00000011, INT32_MIN + 1,
                        terrain.terrainType);
    uint8_t level = (i >= data.header.width * data.header.width) ? 1 : 0;
    if (path == "WATRTL.def") {
      Global::waterBlock[level].insert(i % (Global::mapSize * Global::mapSize));
    } else if (path == "ROCKTL.def") {
      Global::rockBlock[level].insert(i % (Global::mapSize * Global::mapSize));
    } else {
      Global::landBlock[level].insert(i % (Global::mapSize * Global::mapSize));
    }
    if (terrain.extTileFlags & 0b01000000) {
      Global::coastalBlock[level].insert(i %
                                         (Global::mapSize * Global::mapSize));
    }
    if (terrain.riverType != 0) {
      switch (terrain.riverType) {
      case 1: {
        path = "clrrvr.def";
        break;
      }
      case 2: {
        path = "icyrvr.def";
        break;
      }
      case 3: {
        path = "mudrvr.def";
        break;
      }
      case 4: {
        path = "lavrvr.def";
        break;
      }
      default: {
        // 处理未知河流类型的逻辑
        path = "UNKNOWN.def"; // 或者抛出异常等其他处理方式
        break;
      }
      }
      loadTerrainInternal(i, path, terrain.riverDir,
                          (terrain.extTileFlags & 0b00001100) >> 2,
                          INT32_MIN + 2, terrain.riverType + 13);
    }
    if (terrain.roadType != 0) {
      switch (terrain.roadType) {
      case 1: {
        path = "dirtrd.def";
        break;
      }
      case 2: {
        path = "gravrd.def";
        break;
      }
      case 3: {
        path = "cobbrd.def";
        break;
      }
      default: {
        // 处理未知道路类型的逻辑
        path = "UNKNOWN.def"; // 或者抛出异常等其他处理方式
        break;
      }
      }
      loadTerrainInternal(i, path, terrain.roadDir,
                          (terrain.extTileFlags & 0b00110000) >> 4,
                          INT32_MIN + 3, terrain.roadType + 10);
    }
  }
};

void Ent::load(H3mData &data) {
  for (uint32_t i = 0; i < data.objects.size(); i++) {
    loadObj(data.objects[i], i);
  }
  loadTerrain(data);
}