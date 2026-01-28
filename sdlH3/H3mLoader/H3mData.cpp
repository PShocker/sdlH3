#include "H3mData.h"
#include "H3mArtifact.h"
#include "H3mBitMask.h"
#include "H3mCreatureSet.h"
#include "H3mEvent.h"
#include "H3mHearder.h"
#include "H3mHero.h"
#include "H3mObject.h"
#include "H3mQuest.h"
#include "Reader/Reader.h"
#include "SDL3/SDL_stdinc.h"
#include "zlib.h"
#include <cstdint>
#include <cstdlib>
#include <set>
#include <string>
#include <utility>
#include <vector>

void H3mData::readTeamInfo() {
  howManyTeams = reader.readU8();
  if (howManyTeams > 0) {
    // Teams
    for (int i = 0; i < 8; ++i)
      playerInfos[i].team = reader.readU8();
  } else {
    // No alliances
    for (int i = 0; i < 8; i++)
      if (playerInfos[i].canComputerPlay || playerInfos[i].canHumanPlay)
        playerInfos[i].team = howManyTeams++;
  }
}

void H3mData::readAllowedHeroes() {
  H3mBitMask::readBitmask(reader, allowedHeroes, features.heroesBytes,
                          features.heroesCount, false);
  if (features.levelAB) {
    auto placeholdersQty = reader.readU32();

    for (size_t i = 0; i < placeholdersQty; ++i) {
      auto heroID = reader.readU8();
      reservedCampaignHeroes.insert(heroID);
    }
  }
}

void H3mData::readDisposedHeroes() {
  // Reading disposed heroes (20 bytes)
  if (features.levelSOD) {
    size_t disp = reader.readU8();
    disposedHeroes.resize(disp);
    for (size_t g = 0; g < disp; ++g) {
      disposedHeroes[g].id = reader.readU8();
      disposedHeroes[g].portrait = reader.readU8();
      disposedHeroes[g].name = reader.readString();
      H3mBitMask::readBitmask(reader, disposedHeroes[g].players, 1, 8, false);
    }
  }
}

void H3mData::readMapOptions() { reader.skip(31); }

void H3mData::readAllowedArtifacts() {
  if (features.levelAB) {
    H3mBitMask::readBitmask(reader, allowedArtifact, features.artifactsBytes,
                            features.artifactsCount, true);
  }
}

void H3mData::readAllowedSpellsAbilities() {
  if (features.levelSOD) {
    H3mBitMask::readBitmask(reader, allowedSpells, features.spellsBytes,
                            features.spellsCount, true);
    H3mBitMask::readBitmask(reader, allowedAbilities, features.skillsBytes,
                            features.skillsCount, true);
  }
}

void H3mData::readRumors() {
  auto rumorsCount = reader.readU32();
  rumors.resize(rumorsCount);
  for (size_t it = 0; it < rumorsCount; it++) {
    rumors[it].name = reader.readString();
    rumors[it].description = reader.readString();
  }
}

void H3mData::readPredefinedHeroes() {
  if (!features.levelSOD)
    return;
  for (int heroID = 0; heroID < features.heroesCount; heroID++) {
    bool custom = reader.readU8();
    if (!custom)
      continue;
    H3mHero hero;
    hero.id = (uint8_t)ObjectType::HERO;
    hero.subId = heroID;
    bool hasExp = reader.readU8();
    if (hasExp) {
      hero.exp = reader.readU32();
    } else {
      hero.exp = 0;
    }

    bool hasSecSkills = reader.readU8();
    if (hasSecSkills) {
      uint32_t howMany = reader.readU32();
      hero.secSkills.resize(howMany);
      for (int yy = 0; yy < howMany; ++yy) {
        hero.secSkills[yy].first = reader.readU8();
        hero.secSkills[yy].second = reader.readU8();
      }
    }
    loadArtifactsOfHero(hero);
    bool hasCustomBio = reader.readU8();
    if (hasCustomBio) {
      hero.name = reader.readString();
    }

    hero.gender = reader.readU8();
    bool hasCustomSpells = reader.readU8();
    if (hasCustomSpells) {
      H3mBitMask::readBitmask(reader, hero.spells, features.spellsBytes,
                              features.spellsCount, false);
    }

    bool hasCustomPrimSkills = reader.readU8();
    if (hasCustomPrimSkills) {
      for (int skillID = 0; skillID < 4; skillID++) {
        auto sId = reader.readU8();
        hero.primSkills[skillID] = sId;
      }
    }
    predefinedHeroes.emplace_back(hero);
  }
}

void H3mData::readTerrain() {
  uint8_t pos[3];
  uint8_t map_level = 1;
  if (header.twoLevel) {
    map_level = 2;
  }
  for (pos[2] = 0; pos[2] < map_level; ++pos[2]) {
    // OH3 format is [z][y][x]
    for (pos[1] = 0; pos[1] < header.height; pos[1]++) {
      for (pos[0] = 0; pos[0] < header.width; pos[0]++) {
        H3mTerrain terrain;
        terrain.terrainType = reader.readU8();
        terrain.terView = reader.readU8();
        terrain.riverType = reader.readU8();
        terrain.riverDir = reader.readU8();
        terrain.roadType = reader.readU8();
        terrain.roadDir = reader.readU8();
        terrain.extTileFlags = reader.readU8();
        terrains.push_back(terrain);
      }
    }
  }
}

void H3mData::readPlayerInfo() {
  for (int i = 0; i < 8; ++i) {
    playerInfos[i].canHumanPlay = reader.readU8();
    playerInfos[i].canComputerPlay = reader.readU8();
    // If nobody can play with this player - skip loading of these properties
    if ((!(playerInfos[i].canHumanPlay || playerInfos[i].canComputerPlay))) {
      if (features.levelROE)
        reader.skip(6);
      if (features.levelAB)
        reader.skip(6);
      if (features.levelSOD)
        reader.skip(1);
      continue;
    }
    playerInfos[i].aiTactic = (EAiTactic)reader.readU8();

    if (features.levelSOD)
      reader.skip(1); // faction is selectable

    std::set<uint8_t> allowedFactions;
    H3mBitMask::readBitmask(reader, allowedFactions, features.factionsBytes,
                            features.factionsCount, false);

    playerInfos[i].isFactionRandom = reader.readU8();
    const bool allFactionsAllowed =
        playerInfos[i].isFactionRandom &&
        allowedFactions.size() == features.factionsCount;
    if (!allFactionsAllowed)
      playerInfos[i].allowedFactions = allowedFactions;

    playerInfos[i].hasMainTown = reader.readU8();

    if (playerInfos[i].hasMainTown) {
      if (features.levelAB) {
        playerInfos[i].generateHeroAtMainTown = reader.readU8();
        reader.skip(1); // starting town type, unused
      } else {
        playerInfos[i].generateHeroAtMainTown = true;
      }
      playerInfos[i].generateHeroAtMainTown = true;
      playerInfos[i].posOfMainTown[0] = reader.readU8();
      playerInfos[i].posOfMainTown[1] = reader.readU8();
      playerInfos[i].posOfMainTown[2] = reader.readU8();
    }

    playerInfos[i].hasRandomHero = reader.readU8();
    playerInfos[i].mainCustomHeroId = reader.readU8();

    if (playerInfos[i].mainCustomHeroId !=
        (int8_t)features.heroIdentifierInvalid) {
      playerInfos[i].mainCustomHeroPortrait = reader.readU8();
      playerInfos[i].mainCustomHeroNameTextId = reader.readString();
    }

    if (features.levelAB) {
      reader.skip(1); // TODO: check meaning?
      size_t heroCount = reader.readU32();
      for (size_t pp = 0; pp < heroCount; ++pp) {
        auto heroId = reader.readU8();
        auto heroName = reader.readString();
      }
    }
  }
}

void H3mData::readVictoryLossConditions() {
  victorylossCond.vicCondition = (EVictoryConditionType)reader.readU8();
  if (victorylossCond.vicCondition != EVictoryConditionType::WINSTANDARD) {
    bool allowNormalVictory = reader.readU8();
    bool appliesToAI = reader.readU8();
    switch (victorylossCond.vicCondition) {
    case EVictoryConditionType::ARTIFACT: {
      uint16_t result;
      if (features.levelAB)
        result = reader.readU16();
      else
        result = reader.readU8();
      victorylossCond.vicConditionData = result;
      break;
    }
    case EVictoryConditionType::GATHERTROOP: {
      uint16_t result;
      if (features.levelAB)
        result = reader.readU16();
      else
        result = reader.readU8();
      auto value = reader.readU32();
      victorylossCond.vicConditionData = std::make_tuple(result, value);
      break;
    }
    case EVictoryConditionType::GATHERRESOURCE: {
      uint16_t result;
      result = reader.readU8();
      auto value = reader.readU32();
      victorylossCond.vicConditionData = std::make_tuple(result, value);
      break;
    }
    case EVictoryConditionType::BUILDCITY: {
      uint8_t position[3];
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      auto HALL_LEVEL = reader.readU8();
      auto FORT_LEVEL = reader.readU8();
      victorylossCond.vicConditionData =
          std::make_tuple(position, HALL_LEVEL, FORT_LEVEL);
      break;
    }
    case EVictoryConditionType::BUILDGRAIL: {
      uint8_t position[3];
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      victorylossCond.vicConditionData = position;
      break;
    }
    case EVictoryConditionType::BEATHERO: {
      uint8_t position[3];
      //  英雄坐标?
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      victorylossCond.vicConditionData = position;
      break;
    }
    case EVictoryConditionType::CAPTURECITY: {
      uint8_t position[3];
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      victorylossCond.vicConditionData = position;
      break;
    }
    case EVictoryConditionType::BEATMONSTER: {
      uint8_t position[3];
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      victorylossCond.vicConditionData = position;
      break;
    }
    case EVictoryConditionType::TAKEDWELLINGS: {
      break;
    }
    case EVictoryConditionType::TAKEMINES: {
      break;
    }
    case EVictoryConditionType::TRANSPORTITEM: {
      uint16_t artifact;
      artifact = reader.readU8();
      uint8_t position[3];
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      victorylossCond.vicConditionData = std::make_tuple(artifact, position);
      break;
    }
    default:
      break;
    }
  }
  auto lossCond = (ELossConditionType)reader.readU8();
  if (lossCond == ELossConditionType::LOSSSTANDARD) {
  } else {
    switch (lossCond) {
    case ELossConditionType::LOSSCASTLE: {
      uint8_t position[3];
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      victorylossCond.lossCondData = position;
      break;
    }
    case ELossConditionType::LOSSHERO: {
      uint8_t position[3];
      position[0] = reader.readU8();
      position[1] = reader.readU8();
      position[2] = reader.readU8();
      victorylossCond.lossCondData = position;
      break;
    }
    case ELossConditionType::TIMEEXPIRES: {
      uint16_t result;
      result = reader.readU16();
      victorylossCond.lossCondData = result;
      break;
    }
    default:
      break;
    }
  }
}

void H3mData::readHeader() {
  header.version = (EMapFormat)reader.readU32();
  switch (header.version) {
  case EMapFormat::ROE:
    features.FeaturesROE();
    break;
  case EMapFormat::AB:
    features.FeaturesAB();
    break;
  case EMapFormat::SOD:
    features.FeaturesSOD();
    break;
  default:
    std::abort();
  }
  reader.skip(1); // areAnyPlayers is not used
  header.width = header.height = reader.readU32();
  header.twoLevel = reader.readU8();
  header.name = reader.readString();
  header.description = reader.readString();
  header.difficulty = (EMapDifficulty)reader.readU8();
  if (features.levelAB)
    reader.skip(1); // levelLimit is not used
}

void H3mData::readObjectTemplates() {
  uint32_t defAmount = reader.readU32();
  // Read custom defs
  for (int defID = 0; defID < defAmount; ++defID) {
    H3mObject object;
    object.name = reader.readString();
    uint8_t blockMask[6];
    uint8_t visitMask[6];
    for (auto &byte : blockMask)
      byte = reader.readU8();
    for (auto &byte : visitMask)
      byte = reader.readU8();

    /// tiles that are covered by this object, uses EBlockMapBits enum as flags
    std::vector<std::vector<uint8_t>> usedTiles;
    usedTiles.resize(6);
    for (auto &line : usedTiles)
      line.resize(8, 0);

    for (size_t i = 0; i < 6; i++) // 6 rows
    {
      for (size_t j = 0; j < 8; j++) // 8 columns
      {
        auto &tile = usedTiles[5 - i][7 - j];
        tile |= (unsigned char)
            EBlockMapBits::VISIBLE; // assume that all tiles are visible
        if (((blockMask[i] >> j) & 1) == 0)
          tile |= (unsigned char)EBlockMapBits::BLOCKED;

        if (((visitMask[i] >> j) & 1) != 0)
          tile |= (unsigned char)EBlockMapBits::VISITABLE;
      }
    }
    object.usedTiles = usedTiles;
    reader.skip(2);
    auto terrMask = reader.readU16();

    for (int32_t i = (int32_t)ObjectTemplateType::FIRST_REGULAR_TERRAIN;
         i < (int32_t)ObjectTemplateType::ORIGINAL_REGULAR_TERRAIN_COUNT; ++i) {
      if (((terrMask >> i) & 1) != 0)
        object.allowedTerrains.insert(i);
    }
    object.id = reader.readU32();
    object.subId = reader.readU32();
    object.type = reader.readU8();
    object.printPriority =
        reader.readU8() * 100; // to have some space in future
    reader.skip(16);
    originalTemplates.push_back(object);
  }
}
void H3mData::readEventCommon(H3mEvent &event) {
  event.name = reader.readString();
  event.message = reader.readString();

  for (int x = 0; x < features.resourcesCount; ++x)
    event.resources[x] = reader.readU32();

  H3mBitMask::readBitmask(reader, event.players, 1, 8, false);

  if (features.levelSOD)
    event.humanAffected = reader.readU8();
  else
    event.humanAffected = true;

  event.computerAffected = reader.readU8();
  event.firstOccurrence = reader.readU16();
  event.nextOccurrence = reader.readU16();
  reader.skip(16);
}

void H3mData::readMessageAndGuards(H3mObject &object) {
  auto hasMessage = reader.readU8();
  if (hasMessage) {
    object.data["message"] = reader.readString();
    bool hasGuards = reader.readU8();
    if (hasGuards) {
      H3mCreatureSet guards;
      readCreatureSet(guards);
      object.data["guards"] = guards;
    }
    reader.skip(4);
  }
}

void H3mData::readObjects() {
  uint32_t objectsCount = reader.readU32();
  for (uint32_t i = 0; i < objectsCount; ++i) {
    uint8_t mapPosition[3];
    mapPosition[0] = reader.readU8();
    mapPosition[1] = reader.readU8();
    mapPosition[2] = reader.readU8();

    auto defIndex = reader.readU32();
    reader.skip(5);

    auto object = originalTemplates.at(defIndex);
    object.position[0] = mapPosition[0];
    object.position[1] = mapPosition[1];
    object.position[2] = mapPosition[2];
    switch ((ObjectType)object.id) {
      {
      case ObjectType::EVENT: {
        readBoxContent(object);
        std::set<uint8_t> availableFor;
        H3mBitMask::readBitmask(reader, availableFor, 1, 8, false);
        object.data["availableFor"] = availableFor;
        object.data["computerActivate"] = reader.readU8();
        object.data["removeAfterVisit"] = reader.readU8();
        reader.skip(4);
        break;
      }

      case ObjectType::HERO:
      case ObjectType::RANDOM_HERO:
      case ObjectType::PRISON: {
        if (features.levelAB) {
          object.identifier = reader.readU32();
        }
        H3mHero hero;
        hero.playerId = reader.readU8();
        hero.subId = reader.readU8();

        for (auto &elem : predefinedHeroes) {
          if (elem.subId == object.subId) {
            hero = elem;
            break;
          }
        }
        for (auto &elem : disposedHeroes) {
          if (elem.subId == object.subId) {
            hero = elem;
            break;
          }
        }

        bool hasName = reader.readU8();
        if (hasName)
          hero.name = reader.readString();

        if (features.levelSOD) {
          bool hasCustomExperience = reader.readU8();
          if (hasCustomExperience) {
            hero.exp = reader.readU32();
          } else {
            hero.exp = 0;
          }
        } else {
          hero.exp = reader.readU32();
        }

        bool hasPortrait = reader.readU8();
        if (hasPortrait)
          hero.customPortraitSource = reader.readU8();

        bool hasSecSkills = reader.readU8();
        if (hasSecSkills) {
          if (!hero.secSkills.empty()) {
            hero.secSkills.clear();
          }

          uint32_t skillsCount = reader.readU32();
          hero.secSkills.resize(skillsCount);
          for (int i = 0; i < skillsCount; ++i) {
            hero.secSkills[i].first = reader.readU8();
            hero.secSkills[i].second = reader.readU8();
          }
        }

        bool hasGarrison = reader.readU8();
        H3mCreatureSet creatureSet;
        if (hasGarrison) {
          readCreatureSet(creatureSet);
        }
        hero.creatureSet = creatureSet;
        auto armyFormation = reader.readU8();
        loadArtifactsOfHero(hero);
        auto patrolRadius = reader.readU8();

        if (features.levelAB) {
          bool hasCustomBiography = reader.readU8();
          if (hasCustomBiography) {
            hero.biography = reader.readString();
          }
          hero.gender = reader.readU8();
        }
        // Spells
        if (features.levelSOD) {
          bool hasCustomSpells = reader.readU8();
          if (hasCustomSpells) {
            if (!hero.spells.empty()) {
              hero.spells.clear();
            }
            H3mBitMask::readBitmask(reader, hero.spells, features.spellsBytes,
                                    features.spellsCount, false);
          }
        } else if (features.levelAB) {
          // we can read one spell
          auto spell = reader.readU8();
          hero.spells.insert(spell);
        }

        if (features.levelSOD) {
          bool hasCustomPrimSkills = reader.readU8();
          if (hasCustomPrimSkills) {
            for (int xx = 0; xx < 4; ++xx) {
              hero.primSkills[xx] = reader.readU8();
            }
          } else {
            object.data["heroDefaultPrimSkills"] = true;
          }
        }
        object.data["hero"] = hero;
        object.data["direct"] = (uint8_t)2;
        object.data["flip"] = (uint8_t)0;
        reader.skip(16);
        break;
      }

      case ObjectType::MONSTER:
      case ObjectType::RANDOM_MONSTER:
      case ObjectType::RANDOM_MONSTER_L1:
      case ObjectType::RANDOM_MONSTER_L2:
      case ObjectType::RANDOM_MONSTER_L3:
      case ObjectType::RANDOM_MONSTER_L4:
      case ObjectType::RANDOM_MONSTER_L5:
      case ObjectType::RANDOM_MONSTER_L6:
      case ObjectType::RANDOM_MONSTER_L7: {
        if (features.levelAB) {
          object.identifier = reader.readU32();
        }
        auto count = reader.readU16();
        auto character = reader.readU8();
        bool hasMessage = reader.readU8();
        if (hasMessage) {
          object.data["message"] = reader.readString();
          uint32_t resources[7];
          for (int x = 0; x < features.resourcesCount; ++x)
            resources[x] = reader.readU32();
          object.data["resources"] = resources;
          uint8_t gainedArtifact = 0;
          if (features.levelAB)
            gainedArtifact = reader.readU16();
          else
            gainedArtifact = reader.readU8();
          object.data["gainedArtifact"] = gainedArtifact;
        }
        object.data["neverFlees"] = reader.readU8();
        object.data["notGrowingTeam"] = reader.readU8();
        reader.skip(2);
        break;
      }

      case ObjectType::OCEAN_BOTTLE:
      case ObjectType::SIGN: {
        object.data["message"] = reader.readString();
        reader.skip(4);
        break;
      }
      case ObjectType::SEER_HUT: {
        H3mQuest quest;
        if (features.levelAB) {
          readQuest(quest);
        } else {
          auto artID = reader.readU8();
          if (artID != (uint8_t)ArtifactType::NONE) {
            // not none quest
            quest.artifacts.push_back(artID);
            quest.missionId = (uint8_t)EQuestMission::ARTIFACT;
          }
          quest.lastDay = -1; // no timeout
        }
        if (quest.missionId != (uint8_t)EQuestMission::NONE) {
          auto rewardType = reader.readU8();
          object.data["rewardType"] = rewardType;
          switch ((ESeerHutRewardType)rewardType) {
          case ESeerHutRewardType::NOTHING: {
            break;
          }
          case ESeerHutRewardType::EXPERIENCE: {
            object.data["heroExperience"] = reader.readU32();
            break;
          }
          case ESeerHutRewardType::MANA_POINTS: {
            object.data["manaDiff"] = reader.readU32();
            break;
          }
          case ESeerHutRewardType::MORALE: {
            object.data["morale"] = reader.readU8();
            break;
          }
          case ESeerHutRewardType::LUCK: {
            object.data["luck"] = reader.readU8();
            break;
          }
          case ESeerHutRewardType::RESOURCES: {
            auto rId = reader.readU8();
            auto rVal = reader.readU32();
            object.data["resources"] = std::make_pair(rId, rVal);
            break;
          }
          case ESeerHutRewardType::PRIMARY_SKILL: {
            auto rId = reader.readU8();
            auto rVal = reader.readU8();
            object.data["primary"] = std::make_pair(rId, rVal);
            break;
          }
          case ESeerHutRewardType::SECONDARY_SKILL: {
            auto rId = reader.readU8();
            auto rVal = reader.readU8();
            object.data["secondary"] = std::make_pair(rId, rVal);
            break;
          }
          case ESeerHutRewardType::ARTIFACT: {
            if (features.levelAB)
              object.data["artifacts"] = reader.readU16();
            else
              object.data["artifacts"] = reader.readU8();
            break;
          }
          case ESeerHutRewardType::SPELL: {
            object.data["spells"] = reader.readU8();
            break;
          }
          case ESeerHutRewardType::CREATURE: {
            uint16_t rId;
            if (features.levelAB)
              rId = reader.readU16();
            else
              rId = reader.readU8();
            auto rVal = reader.readU16();
            object.data["creatures"] = std::make_pair(rId, rVal);
            break;
          }
          default:
            break;
          }
        } else {
          reader.skip(1);
        }
        object.data["quest"] = quest;
        reader.skip(2);
        break;
      }

      case ObjectType::WITCH_HUT: {
        if (features.levelAB) {
          std::set<uint8_t> allowedAbilities;
          H3mBitMask::readBitmask(reader, allowedAbilities,
                                  features.skillsBytes, features.skillsCount,
                                  false);
          object.data["allowedAbilities"] = allowedAbilities;
        }
        break;
      }
      case ObjectType::SCHOLAR: {
        auto bonusTypeRaw = reader.readU8();
        auto bonusID = reader.readU8();
        object.data["bonusTypeRaw"] = bonusTypeRaw;
        object.data["bonusID"] = bonusID;
        reader.skip(6);
        break;
      }
      case ObjectType::GARRISON:
      case ObjectType::GARRISON2: {
        object.data["playerId"] = (uint8_t)reader.readU32();
        H3mCreatureSet creatureSet;
        readCreatureSet(creatureSet);
        object.data["creatureSet"] = creatureSet;
        if (features.levelAB)
          object.data["removableUnits"] = reader.readU8();
        else
          object.data["removableUnits"] = true;
        reader.skip(8);
        break;
      }
      case ObjectType::ARTIFACT:
      case ObjectType::RANDOM_ART:
      case ObjectType::RANDOM_TREASURE_ART:
      case ObjectType::RANDOM_MINOR_ART:
      case ObjectType::RANDOM_MAJOR_ART:
      case ObjectType::RANDOM_RELIC_ART: {
        readMessageAndGuards(object);
        break;
      }
      case ObjectType::SPELL_SCROLL: {
        readMessageAndGuards(object);
        object.data["spellID"] = reader.readU32();
        break;
      }
      case ObjectType::RANDOM_RESOURCE:
      case ObjectType::RESOURCE: {
        readMessageAndGuards(object);
        uint32_t amount = 0;
        amount = reader.readU32();
        if (amount == 0) {
          amount = (std::rand() % 10) + 1;
        }
        if (object.id != (int32_t)ObjectType::RANDOM_RESOURCE) {
          if (object.subId == 6) {
            amount *= 100;
          }
        }
        object.data["amount"] = amount;
        reader.skip(4);
        break;
      }
      case ObjectType::RANDOM_TOWN:
      case ObjectType::TOWN: {
        if (features.levelAB) {
          object.identifier = reader.readU32();
        }
        auto playerId = reader.readU8();
        object.data["playerId"] = playerId;
        bool hasName = reader.readU8();
        std::string name = "";
        if (hasName) {
          name = reader.readString();
        }
        object.data["name"] = name;

        bool hasGarrison = reader.readU8();
        H3mCreatureSet creatureSet;
        if (hasGarrison) {
          readCreatureSet(creatureSet);
        }
        object.data["creatureSet"] = creatureSet;

        auto armyFormation = reader.readU8();
        bool hasCustomBuildings = reader.readU8();
        std::set<uint8_t> builtBuildings;
        std::set<uint8_t> forbidBuildings;
        if (hasCustomBuildings) {
          H3mBitMask::readBitmask(reader, builtBuildings,
                                  features.buildingsBytes,
                                  features.buildingsCount, false);
          H3mBitMask::readBitmask(reader, forbidBuildings,
                                  features.buildingsBytes,
                                  features.buildingsCount, false);
        }
        // Standard buildings
        else {
          bool hasFort = reader.readU8();
          if (hasFort) {
            builtBuildings.insert((uint8_t)BuildingIDBase::FORT);
          }
          // means that set of standard building should be included
          // builtBuildings.insert((uint8_t)BuildingIDBase::DEFAULT);
        }
        builtBuildings.insert(0xff);
        object.data["builtBuildings"] = builtBuildings;
        object.data["forbidBuildings"] = forbidBuildings;

        std::set<uint8_t> obligatorySpells;
        std::set<uint8_t> possibleSpells;

        if (features.levelAB) {
          H3mBitMask::readBitmask(reader, obligatorySpells,
                                  features.spellsBytes, features.spellsCount,
                                  false);
        }

        H3mBitMask::readBitmask(reader, possibleSpells, features.spellsBytes,
                                features.spellsCount, true);
        object.data["obligatorySpells"] = obligatorySpells;
        object.data["possibleSpells"] = possibleSpells;

        uint32_t eventsCount = reader.readU32();
        std::vector<H3mEvent> events;
        for (int eventID = 0; eventID < eventsCount; ++eventID) {
          H3mEvent event;

          readEventCommon(event);

          // New buildings
          H3mBitMask::readBitmask(reader, builtBuildings,
                                  features.buildingsBytes,
                                  features.buildingsCount, false);

          for (int i = 0; i < 7; ++i) {
            event.creatures[i] = reader.readU16();
          }
          reader.skip(4);
          events.push_back(event);
        }

        if (features.levelSOD) {
          reader.skip(1);
        }
        reader.skip(3);
        break;
      }
      case ObjectType::MINE:
      case ObjectType::ABANDONED_MINE: {
        if (object.subId < 7) {
          uint8_t playerId = reader.readU32();
          object.data["playerId"] = playerId;
        } else {
          std::set<uint8_t> abandonedMineResources;
          H3mBitMask::readBitmask(reader, abandonedMineResources,
                                  features.resourcesBytes,
                                  features.resourcesCount, false);
          object.data["abandonedMineResources"] = abandonedMineResources;
        }
        break;
      }

      case ObjectType::CREATURE_GENERATOR1:
      case ObjectType::CREATURE_GENERATOR2:
      case ObjectType::CREATURE_GENERATOR3:
      case ObjectType::CREATURE_GENERATOR4: {
        object.data["playerId"] = (uint8_t)reader.readU32();
        break;
      }
      case ObjectType::SHRINE_OF_MAGIC_INCANTATION:
      case ObjectType::SHRINE_OF_MAGIC_GESTURE:
      case ObjectType::SHRINE_OF_MAGIC_THOUGHT: {
        object.data["spell"] = (uint8_t)reader.readU32();
        break;
      }
      case ObjectType::PANDORAS_BOX: {
        readBoxContent(object);
        break;
      }
      case ObjectType::GRAIL: {
        object.data["grailRadius"] = reader.readU32();
        break;
      }

      case ObjectType::RANDOM_DWELLING:
      case ObjectType::RANDOM_DWELLING_LVL:
      case ObjectType::RANDOM_DWELLING_FACTION: {
        object.data["playerId"] = (uint8_t)reader.readU32();
        bool hasFactionInfo =
            (ObjectType)object.id == ObjectType::RANDOM_DWELLING ||
            (ObjectType)object.id == ObjectType::RANDOM_DWELLING_LVL;
        bool hasLevelInfo =
            (ObjectType)object.id == ObjectType::RANDOM_DWELLING ||
            (ObjectType)object.id == ObjectType::RANDOM_DWELLING_FACTION;
        std::set<uint8_t> allowedFactions;
        if (hasFactionInfo) {
          object.identifier = reader.readU32();
          if (object.identifier == 0) {
            H3mBitMask::readBitmask(reader, allowedFactions,
                                    features.factionsBytes,
                                    features.factionsCount, false);
          }
        } else {
          allowedFactions.insert(object.subId);
        }
        object.data["allowedFactions"] = allowedFactions;
        uint8_t minLevel;
        uint8_t maxLevel;
        if (hasLevelInfo) {
          minLevel = std::max(reader.readU8(), (uint8_t)0) + 1;
          maxLevel = std::min(reader.readU8(), (uint8_t)6) + 1;
        } else {
          minLevel = object.subId;
          maxLevel = object.subId;
        }
        object.data["minLevel"] = minLevel;
        object.data["maxLevel"] = maxLevel;
        break;
      }

      case ObjectType::QUEST_GUARD: {
        H3mQuest quest;
        readQuest(quest);
        object.data["quest"] = quest;
        break;
      }

      case ObjectType::SHIPYARD: {
        object.data["playerId"] = (uint8_t)reader.readU32();
        break;
      }

      case ObjectType::HERO_PLACEHOLDER: {
        object.data["playerId"] = reader.readU8();
        auto heroId = reader.readU8();
        if (heroId == (uint8_t)-1) {
          object.data["powerRank"] = reader.readU8();
        } else {
          object.data["heroId"] = heroId;
        }
        break;
      }

      case ObjectType::LIGHTHOUSE: {
        object.data["playerId"] = (uint8_t)reader.readU32();
        break;
      }

      case ObjectType::CREATURE_BANK:
      case ObjectType::DERELICT_SHIP:
      case ObjectType::DRAGON_UTOPIA:
      case ObjectType::CRYPT:
      case ObjectType::SHIPWRECK: {
        break;
      }

      case ObjectType::TREASURE_CHEST:
      case ObjectType::CORPSE:
      case ObjectType::SHIPWRECK_SURVIVOR:
      case ObjectType::SEA_CHEST:
      case ObjectType::FLOTSAM:
      case ObjectType::TREE_OF_KNOWLEDGE:
      case ObjectType::PYRAMID:
      case ObjectType::WARRIORS_TOMB: {
        break;
      }

      case ObjectType::CAMPFIRE:
      case ObjectType::WAGON:
      case ObjectType::LEAN_TO: {
        break;
      }
      case ObjectType::BORDER_GATE: {
        break;
      }
      case ObjectType::BLACK_MARKET: {
        break;
      }
      case ObjectType::UNIVERSITY: {
        break;
      }
      case ObjectType::BOAT: {
        object.data["direct"] = (uint8_t)2;
        object.data["flip"] = (uint8_t)0;
        break;
      }
      default: // any other object
        break;
      }
    }
    objects.push_back(object);
  }
}

void H3mData::loadArtifactsOfHero(H3mHero &hero) {
  bool hasArtSet = reader.readU8();
  if (!hasArtSet)
    return;

  for (int i = 0; i < features.artifactSlotsCount; i++) {
    loadArtifactToSlot(hero, i);
  }
  auto amount = reader.readU16();
  for (size_t i = 0; i < amount; ++i) {
    loadArtifactToSlot(hero, 19 + hero.artifactsInBackpack.size());
  }
}

void H3mData::loadArtifactToSlot(H3mHero &hero, uint16_t slot) {
  uint16_t artifactId;
  if (features.levelAB)
    artifactId = reader.readU16();
  else
    artifactId = reader.readU8();
  if (slot < 19)
    hero.artifacts.push_back(artifactId);
  else
    hero.artifactsInBackpack.push_back(artifactId);
}

void H3mData::readEvents() {
  uint32_t eventsCount = reader.readU32();
  for (int eventID = 0; eventID < eventsCount; ++eventID) {
    H3mEvent event;
    readEventCommon(event);
    events.push_back(event);
  }
}

void H3mData::readCreatureSet(H3mCreatureSet &creatureSet) {
  creatureSet.creatures.resize(7);
  for (int index = 0; index < 7; ++index) {
    uint16_t creatureId;
    if (features.levelAB)
      creatureId = reader.readU16();
    else
      creatureId = reader.readU8();
    uint16_t count = reader.readU16();
    creatureSet.creatures[index] = std::make_pair(creatureId, count);
  }
}

void H3mData::readBoxContent(H3mObject &object) {
  readMessageAndGuards(object);
  object.data["heroExperience"] = reader.readU32();
  object.data["manaDiff"] = (int32_t)reader.readU32();
  object.data["morale"] = (int8_t)reader.readU8();
  object.data["luck"] = (int8_t)reader.readU8();
  std::array<uint32_t, 7> resources;
  for (int x = 0; x < features.resourcesCount; ++x)
    resources[x] = reader.readU32();
  object.data["resources"] = resources;
  std::array<uint8_t, 4> primary;
  for (int x = 0; x < 4; ++x)
    primary[x] = reader.readU8();
  object.data["primary"] = primary;

  std::vector<std::pair<uint8_t, uint8_t>> secondary;
  size_t gabn = reader.readU8(); // number of gained abilities
  for (size_t oo = 0; oo < gabn; ++oo) {
    auto rId = reader.readU8();
    auto rVal = reader.readU8();
    secondary.push_back(std::make_pair(rId, rVal));
  }
  object.data["secondary"] = secondary;

  std::vector<uint16_t> artifacts;
  size_t gart = reader.readU8(); // number of gained artifacts
  for (size_t oo = 0; oo < gart; ++oo) {
    if (features.levelAB)
      artifacts.push_back(reader.readU16());
    else
      artifacts.push_back(reader.readU8());
  }
  object.data["artifacts"] = artifacts;

  std::vector<uint8_t> spells;
  size_t gspel = reader.readU8(); // number of gained spells
  for (size_t oo = 0; oo < gspel; ++oo) {
    spells.push_back(reader.readU8());
  }
  object.data["spells"] = spells;

  std::vector<std::pair<uint16_t, uint32_t>> creatures;
  size_t gcre = reader.readU8(); // number of gained creatures
  for (size_t oo = 0; oo < gcre; ++oo) {
    uint16_t rId;
    if (features.levelAB)
      rId = reader.readU16();
    else
      rId = reader.readU8();

    auto rVal = reader.readU16();
    creatures.emplace_back(rId, rVal);
  }
  object.data["creatures"] = creatures;
  reader.skip(8);
}

void H3mData::readQuest(H3mQuest &quest) {
  quest.missionId = reader.readU8();
  switch ((EQuestMission)quest.missionId) {
  case EQuestMission::NONE: {
    return;
  }
  case EQuestMission::PRIMARY_SKILL: {
    for (int x = 0; x < 4; ++x) {
      quest.primary[x] = reader.readU8();
    }
    break;
  }
  case EQuestMission::LEVEL: {
    quest.heroLevel = reader.readU32();
    break;
  }
  case EQuestMission::KILL_HERO:
  case EQuestMission::KILL_CREATURE: {
    quest.killTarget = reader.readU32();
    break;
  }
  case EQuestMission::ARTIFACT: {
    size_t artNumber = reader.readU8();
    for (size_t yy = 0; yy < artNumber; ++yy) {
      uint16_t artid = 0;
      if (features.levelAB)
        artid = reader.readU16();
      else
        artid = reader.readU8();
      quest.artifacts.push_back(artid);
    }
    break;
  }
  case EQuestMission::ARMY: {
    size_t typeNumber = reader.readU8();
    for (size_t hh = 0; hh < typeNumber; ++hh) {
      uint16_t creatureId = 0;
      if (features.levelAB)
        creatureId = reader.readU16();
      else
        creatureId = reader.readU8();
      auto count = reader.readU16();
      quest.creatures.push_back(std::make_pair(creatureId, count));
    }
    break;
  }
  case EQuestMission::RESOURCES: {
    for (int x = 0; x < 7; ++x)
      quest.resources[x] = reader.readU32();

    break;
  }
  case EQuestMission::HERO: {
    quest.hero = reader.readU8();
    break;
  }
  case EQuestMission::PLAYER: {
    quest.player = reader.readU8();
    break;
  }
  default:
    break;
  }
  quest.lastDay = reader.readU32();
  quest.firstVisitText = reader.readString();
  quest.nextVisitText = reader.readString();
  quest.completedText = reader.readString();
}

H3mData::H3mData(std::string filePath) : reader(filePath) {
  char *compressData = (char *)SDL_malloc(reader.size());
  SDL_ReadIO(reader.stream, compressData, reader.size());
  z_stream zs{};
  int ret = inflateInit2(&zs, MAX_WBITS + 32);
  if (ret != Z_OK)
    std::abort();

  zs.next_in = reinterpret_cast<Bytef *>(compressData);
  zs.avail_in = static_cast<uInt>(reader.size());

  reader.seek(reader.size() - 4);
  auto unCompressDataSize = reader.readU32();
  auto unCompressData = (char *)SDL_malloc(unCompressDataSize);

  zs.next_out = reinterpret_cast<Bytef *>(unCompressData);
  zs.avail_out = unCompressDataSize;

  inflate(&zs, Z_NO_FLUSH);
  inflateEnd(&zs);

  SDL_free(compressData);
  reader.close();
  reader = Reader(unCompressData, unCompressDataSize);
  SDL_free(unCompressData);
}

void H3mData::init() {
  readHeader();
  readPlayerInfo();
  readVictoryLossConditions();
  readTeamInfo();
  readAllowedHeroes();
  readDisposedHeroes();
  readMapOptions();
  readAllowedArtifacts();
  readAllowedSpellsAbilities();
  readRumors();
  readPredefinedHeroes();
  readTerrain();
  readObjectTemplates();
  readObjects();
  readEvents();

  reader.close();
}