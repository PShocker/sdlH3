#include "H3mSaver.h"
#include "H3mLoader/H3mHero.h"
#include <bitset>
#include <cstdint>
#include <set>

static void writeBitmask(Writer &writer, const std::set<uint8_t> &src,
                         int bytesToWrite, int objectsToWrite, bool invert) {
  // 初始化掩码数组
  std::vector<uint8_t> masks(bytesToWrite, 0);

  // 根据set中的值设置对应的位
  for (uint8_t index : src) {
    if (index < objectsToWrite) {
      int byteIndex = index / 8;
      int bitIndex = index % 8;
      masks[byteIndex] |= (1 << bitIndex);
    }
  }

  // 如果需要反转
  if (invert) {
    for (int i = 0; i < bytesToWrite; ++i) {
      masks[i] = ~masks[i];
    }
  }

  // 写入掩码数据
  for (int i = 0; i < bytesToWrite; ++i) {
    writer.writeU8(masks[i]);
  }
}

void H3mSaver::saveMapHeader(Writer &writer, H3mData &data) {
  //   version
  writer.writeU32((uint32_t)data.header.version);
  // areAnyPlayers
  writer.writeU8(0);
  // width
  writer.writeU32((uint32_t)data.header.width);
  // twoLevel
  writer.writeU8((uint32_t)data.header.twoLevel);
  // name
  writer.writeString(data.header.name);
  // description
  writer.writeString(data.header.description);
  // difficult
  writer.writeU8((uint8_t)data.header.difficulty);
  if (data.features.levelAB)
    writer.writeU8(0);
}

void H3mSaver::savePlayerInfo(Writer &writer, H3mData &data) {
  for (int i = 0; i < 8; ++i) {
    auto &playerInfos = data.playerInfos;
    writer.writeU8((uint8_t)playerInfos[i].canHumanPlay);
    writer.writeU8((uint8_t)playerInfos[i].canComputerPlay);
    if ((!(playerInfos[i].canHumanPlay || playerInfos[i].canComputerPlay))) {
      if (data.features.levelROE)
        writer.fill(6, 0);
      if (data.features.levelAB)
        writer.fill(6, 0);
      if (data.features.levelSOD)
        writer.fill(1, 0);
      continue;
    }
    // aiTactic
    writer.writeU8((uint8_t)playerInfos[i].aiTactic);
    if (data.features.levelSOD)
      writer.writeU8(0);
    writeBitmask(writer, playerInfos[i].allowedFactions,
                 data.features.factionsBytes, data.features.factionsCount,
                 false);
    // isFactionRandom
    writer.writeU8(playerInfos[i].isFactionRandom);
    writer.writeU8(playerInfos[i].hasMainTown);
    if (playerInfos[i].hasMainTown) {
      if (data.features.levelAB) {
        writer.writeU8(playerInfos[i].generateHeroAtMainTown);
        writer.writeU8(0);
      }
      writer.writeU8(playerInfos[i].posOfMainTown[0]);
      writer.writeU8(playerInfos[i].posOfMainTown[1]);
      writer.writeU8(playerInfos[i].posOfMainTown[2]);
    }

    writer.writeU8(playerInfos[i].hasRandomHero);
    writer.writeU8(playerInfos[i].mainCustomHeroId);

    if (playerInfos[i].mainCustomHeroId !=
        (int8_t)data.features.heroIdentifierInvalid) {
      writer.writeU8(playerInfos[i].mainCustomHeroPortrait);
      writer.writeString(playerInfos[i].mainCustomHeroNameTextId);
    }

    if (data.features.levelAB) {
      writer.writeU8(0);
      writer.writeU32(playerInfos[i].heroCount);
      for (size_t pp = 0; pp < playerInfos[i].heroCount; ++pp) {
        writer.writeU8(playerInfos[i].heroId[pp]);
        writer.writeString(playerInfos[i].heroName[pp]);
      }
    }
  }
}

static void saveVictoryLossConditions(Writer &writer, H3mData &data) {
  auto &victorylossCond = data.victorylossCond;
  auto &features = data.features;

  // 保存胜利条件类型
  writer.writeU8(static_cast<uint8_t>(victorylossCond.vicCondition));

  // 如果不是标准胜利，保存额外标志位和数据
  if (victorylossCond.vicCondition != EVictoryConditionType::WINSTANDARD) {
    // 保存两个标志位
    writer.writeU8(victorylossCond.allowNormalVictory ? 1 : 0);
    writer.writeU8(victorylossCond.appliesToAI ? 1 : 0);

    // 根据不同的胜利条件类型保存数据
    switch (victorylossCond.vicCondition) {
    case EVictoryConditionType::ARTIFACT: {
      uint16_t artifactId =
          std::any_cast<uint16_t>(victorylossCond.vicConditionData);
      if (features.levelAB)
        writer.writeU16(artifactId);
      else
        writer.writeU8(static_cast<uint8_t>(artifactId));
      break;
    }

    case EVictoryConditionType::GATHERTROOP: {
      auto [troopType, troopCount] =
          std::any_cast<std::tuple<uint16_t, uint32_t>>(
              victorylossCond.vicConditionData);
      if (features.levelAB)
        writer.writeU16(troopType);
      else
        writer.writeU8(static_cast<uint8_t>(troopType));
      writer.writeU32(troopCount);
      break;
    }

    case EVictoryConditionType::GATHERRESOURCE: {
      auto [resourceType, resourceCount] =
          std::any_cast<std::tuple<uint16_t, uint32_t>>(
              victorylossCond.vicConditionData);
      writer.writeU8(static_cast<uint8_t>(resourceType));
      writer.writeU32(resourceCount);
      break;
    }

    case EVictoryConditionType::BUILDCITY: {
      auto [position, hallLevel, fortLevel] =
          std::any_cast<std::tuple<std::array<uint8_t, 3>, uint8_t, uint8_t>>(
              victorylossCond.vicConditionData);
      writer.writeU8(position[0]);
      writer.writeU8(position[1]);
      writer.writeU8(position[2]);
      writer.writeU8(hallLevel);
      writer.writeU8(fortLevel);
      break;
    }

    case EVictoryConditionType::BUILDGRAIL:
    case EVictoryConditionType::BEATHERO:
    case EVictoryConditionType::CAPTURECITY:
    case EVictoryConditionType::BEATMONSTER: {
      auto position = std::any_cast<std::array<uint8_t, 3>>(
          victorylossCond.vicConditionData);
      writer.writeU8(position[0]);
      writer.writeU8(position[1]);
      writer.writeU8(position[2]);
      break;
    }

    case EVictoryConditionType::TAKEDWELLINGS:
    case EVictoryConditionType::TAKEMINES: {
      // 这些类型没有额外数据
      // 注意：原读取函数中这些case是空的，所以不需要写入数据
      break;
    }

    case EVictoryConditionType::TRANSPORTITEM: {
      auto [artifact, position] =
          std::any_cast<std::tuple<uint16_t, std::array<uint8_t, 3>>>(
              victorylossCond.vicConditionData);
      writer.writeU8(static_cast<uint8_t>(artifact));
      writer.writeU8(position[0]);
      writer.writeU8(position[1]);
      writer.writeU8(position[2]);
      break;
    }

    case EVictoryConditionType::HOTA_ELIMINATE_ALL_MONSTERS:
    case EVictoryConditionType::HOTA_SURVIVE_FOR_DAYS: {
      // HOTA扩展类型，可能需要额外的数据处理
      // 根据实际需要补充
      break;
    }

    default:
      // 未知类型，可能需要记录日志
      break;
    }
  }

  // 保存失败条件
  writer.writeU8(static_cast<uint8_t>(victorylossCond.lossCond));
  if (victorylossCond.lossCond != ELossConditionType::LOSSSTANDARD) {
    switch (victorylossCond.lossCond) {
    case ELossConditionType::LOSSCASTLE:
    case ELossConditionType::LOSSHERO: {
      auto position =
          std::any_cast<std::array<uint8_t, 3>>(victorylossCond.lossCondData);
      writer.writeU8(position[0]);
      writer.writeU8(position[1]);
      writer.writeU8(position[2]);
      break;
    }

    case ELossConditionType::TIMEEXPIRES: {
      uint16_t timeLimit =
          std::any_cast<uint16_t>(victorylossCond.lossCondData);
      writer.writeU16(timeLimit);
      break;
    }

    default:
      break;
    }
  }
}

static void saveTeamInfo(Writer &writer, H3mData &data) {
  // 保存团队数量
  writer.writeU8(data.howManyTeams);
  // 只有当有预设团队时才保存玩家团队分配
  if (data.howManyTeams > 0) {
    for (int i = 0; i < 8; ++i) {
      writer.writeU8(data.playerInfos[i].team);
    }
  }
}

static void saveAllowedHeroes(Writer &writer, H3mData &data) {
  auto &features = data.features;

  // 保存英雄位掩码
  writeBitmask(writer, data.allowedHeroes, features.heroesBytes,
               features.heroesCount, false);

  // 如果是AB版本，保存预留的英雄数量和数据
  if (features.levelAB) {
    writer.writeU32(static_cast<uint32_t>(data.reservedCampaignHeroes.size()));

    for (uint8_t heroID : data.reservedCampaignHeroes) {
      writer.writeU8(heroID);
    }
  }
}

static void saveDisposedHeroes(Writer &writer, H3mData &data) {
  auto &features = data.features;

  // 只有SOD版本才保存已移除的英雄数据
  if (features.levelSOD) {
    // 保存英雄数量
    writer.writeU8(static_cast<uint8_t>(data.disposedHeroes.size()));

    // 保存每个已移除的英雄信息
    for (const auto &disposedHero : data.disposedHeroes) {
      writer.writeU8(disposedHero.id);       // 英雄ID
      writer.writeU8(disposedHero.portrait); // 英雄头像
      writer.writeString(disposedHero.name); // 英雄名称

      writeBitmask(writer, disposedHero.players, 1, 8, false);
    }
  }
}

static void saveMapOptions(Writer &writer) { writer.fill(31, 0); }

static void saveAllowedArtifacts(Writer &writer, H3mData &data) {
  auto &features = data.features;

  // 只有AB版本才保存神器限制数据
  if (features.levelAB) {
    writeBitmask(writer, data.allowedArtifact, features.artifactsBytes,
                 features.artifactsCount,
                 true); // 注意：这里是true，表示反转
  }
}

static void saveAllowedSpellsAbilities(Writer &writer, H3mData &data) {
  auto &features = data.features;

  // 只有SOD版本才保存法术和技能限制数据
  if (features.levelSOD) {
    // 保存法术限制位掩码
    writeBitmask(writer, data.allowedSpells, features.spellsBytes,
                 features.spellsCount,
                 true); // 注意：invert=true

    // 保存技能限制位掩码
    writeBitmask(writer, data.allowedAbilities, features.skillsBytes,
                 features.skillsCount,
                 true); // 注意：invert=true
  }
}

static void saveRumors(Writer &writer, H3mData &data) {
  // 保存谣言/消息数量
  writer.writeU32(static_cast<uint32_t>(data.rumors.size()));

  // 保存每个谣言/消息
  for (const auto &rumor : data.rumors) {
    writer.writeString(rumor.name);        // 谣言名称
    writer.writeString(rumor.description); // 谣言描述
  }
}

static void saveArtifactToSlot(Writer &writer, const H3mFeatures &features,
                               const H3mHero &hero, uint16_t slot) {
  uint16_t artifactId = 0;

  // 获取对应槽位的神器ID
  if (slot < 19) {
    if (slot < hero.artifacts.size()) {
      artifactId = hero.artifacts[slot];
    }
  } else {
    uint16_t backpackIndex = slot - 19;
    if (backpackIndex < hero.artifactsInBackpack.size()) {
      artifactId = hero.artifactsInBackpack[backpackIndex];
    }
  }

  // 根据版本保存神器ID
  if (features.levelAB) {
    writer.writeU16(artifactId);
  } else {
    writer.writeU8(static_cast<uint8_t>(artifactId));
  }
}

static void saveArtifactsOfHero(Writer &writer, H3mData &data,
                                const H3mHero &hero) {
  auto &features = data.features;

  // 检查是否有神器套装
  bool hasArtSet = !hero.artifacts.empty() || !hero.artifactsInBackpack.empty();
  writer.writeU8(hasArtSet ? 1 : 0);

  if (!hasArtSet) {
    return;
  }

  // 保存装备槽位中的神器（前19个槽位）
  for (int i = 0; i < features.artifactSlotsCount; i++) {
    saveArtifactToSlot(writer, features, hero, i);
  }

  // 保存背包中的神器数量
  writer.writeU16(static_cast<uint16_t>(hero.artifactsInBackpack.size()));

  // 保存背包中的神器
  for (size_t i = 0; i < hero.artifactsInBackpack.size(); ++i) {
    saveArtifactToSlot(writer, features, hero, 19 + i);
  }
}

static void savePredefinedHeroes(Writer &writer, H3mData &data) {
  auto &features = data.features;

  // 只有SOD版本才保存预定义英雄数据
  if (!features.levelSOD) {
    return;
  }

  // 创建英雄映射，按英雄ID快速查找
  std::unordered_map<uint8_t, const H3mHero *> heroMap;
  for (const auto &hero : data.predefinedHeroes) {
    heroMap[hero.subId] = &hero;
  }

  // 按顺序遍历所有英雄ID
  for (int heroID = 0; heroID < features.heroesCount; heroID++) {
    auto it = heroMap.find(static_cast<uint8_t>(heroID));
    bool hasCustomHero = (it != heroMap.end());

    // 保存是否有自定义英雄的标志
    writer.writeU8(hasCustomHero ? 1 : 0);

    if (!hasCustomHero) {
      continue;
    }

    const H3mHero &hero = *it->second;

    // 保存经验值
    bool hasExp = (hero.exp > 0);
    writer.writeU8(hasExp ? 1 : 0);
    if (hasExp) {
      writer.writeU32(hero.exp);
    }

    // 保存次要技能
    bool hasSecSkills = !hero.secSkills.empty();
    writer.writeU8(hasSecSkills ? 1 : 0);
    if (hasSecSkills) {
      writer.writeU32(static_cast<uint32_t>(hero.secSkills.size()));
      for (const auto &skill : hero.secSkills) {
        writer.writeU8(skill.first);  // 技能ID
        writer.writeU8(skill.second); // 技能等级
      }
    }

    // 保存神器（调用loadArtifactsOfHero对应的保存函数）
    saveArtifactsOfHero(writer, data, hero);

    // 保存自定义名称/传记
    bool hasCustomBio = !hero.name.empty();
    writer.writeU8(hasCustomBio ? 1 : 0);
    if (hasCustomBio) {
      writer.writeString(hero.name);
    }

    // 保存性别
    writer.writeU8(hero.gender);

    // 保存自定义法术
    bool hasCustomSpells = !hero.spells.empty();
    writer.writeU8(hasCustomSpells ? 1 : 0);
    if (hasCustomSpells) {
      writeBitmask(writer, hero.spells, features.spellsBytes,
                   features.spellsCount,
                   false); // 注意：invert=false
    }

    // 保存自定义基本技能
    bool hasCustomPrimSkills = false;
    for (int i = 0; i < 4; i++) {
      if (hero.primSkills[i] != 0) {
        hasCustomPrimSkills = true;
        break;
      }
    }
    writer.writeU8(hasCustomPrimSkills ? 1 : 0);
    if (hasCustomPrimSkills) {
      for (int skillID = 0; skillID < 4; skillID++) {
        writer.writeU8(hero.primSkills[skillID]);
      }
    }
  }
}

static void saveTerrain(Writer &writer, H3mData &data) {
  auto &header = data.header;
  uint8_t mapLevel = header.twoLevel ? 2 : 1;
  size_t idx = 0;
  for (uint8_t z = 0; z < mapLevel; ++z) {
    for (uint16_t y = 0; y < header.height; ++y) {
      for (uint16_t x = 0; x < header.width; ++x) {
        const H3mTerrain &terrain = data.terrains[idx++];
        writer.writeU8(terrain.terrainType);
        writer.writeU8(terrain.terView);
        writer.writeU8(terrain.riverType);
        writer.writeU8(terrain.riverDir);
        writer.writeU8(terrain.roadType);
        writer.writeU8(terrain.roadDir);
        writer.writeU8(terrain.extTileFlags);
      }
    }
  }
}

static void saveObjectTemplates(Writer &writer, H3mData &data) {
  // 保存自定义对象模板数量
  writer.writeU32(static_cast<uint32_t>(data.originalTemplates.size()));

  // 保存每个对象模板
  for (const auto &object : data.originalTemplates) {
    // 保存对象名称
    writer.writeString(object.name);

    // 计算blockMask和visitMask
    uint8_t blockMask[6] = {0};
    uint8_t visitMask[6] = {0};

    // 根据usedTiles重新计算掩码
    for (size_t i = 0; i < 6; i++) {
      for (size_t j = 0; j < 8; j++) {
        // 注意：读取时的转换逻辑是：
        // usedTiles[5-i][7-j] 对应 blockMask[i] 的 bit j
        if (i < object.usedTiles.size() && (5 - i) < object.usedTiles.size() &&
            j < object.usedTiles[5 - i].size() &&
            (7 - j) < object.usedTiles[5 - i].size()) {

          uint8_t tile = object.usedTiles[5 - i][7 - j];

          // 检查BLOCKED标志
          if (!(tile & static_cast<uint8_t>(EBlockMapBits::BLOCKED))) {
            blockMask[i] |= (1 << j);
          }

          // 检查VISITABLE标志
          if (tile & static_cast<uint8_t>(EBlockMapBits::VISITABLE)) {
            visitMask[i] |= (1 << j);
          }
        }
      }
    }

    // 写入blockMask (6字节)
    for (uint8_t byte : blockMask) {
      writer.writeU8(byte);
    }

    // 写入visitMask (6字节)
    for (uint8_t byte : visitMask) {
      writer.writeU8(byte);
    }

    // 跳过2字节（读取时跳过了2字节）
    writer.writeU16(0);

    // 计算并写入terrMask (地形掩码)
    uint16_t terrMask = 0;
    for (int32_t terrain : object.allowedTerrains) {
      if (terrain >=
              static_cast<int32_t>(ObjectTemplateType::FIRST_REGULAR_TERRAIN) &&
          terrain < static_cast<int32_t>(
                        ObjectTemplateType::ORIGINAL_REGULAR_TERRAIN_COUNT)) {
        terrMask |= (1 << terrain);
      }
    }
    writer.writeU16(terrMask);

    // 写入对象ID和子ID
    writer.writeU32(object.id);
    writer.writeU32(object.subId);

    // 写入对象类型
    writer.writeU8(object.type);

    // 写入打印优先级（注意：读取时乘以100，保存时需要除以100）
    writer.writeU8(static_cast<uint8_t>(object.printPriority / 100));

    // 跳过16字节（读取时跳过了16字节）
    for (int i = 0; i < 16; ++i) {
      writer.writeU8(0);
    }
  }
}

static void saveCreatureSet(Writer &writer, H3mData &data,
                            const H3mCreatureSet &creatureSet) {
  auto &features = data.features;

  // 确保有7个槽位（如果不足则补充默认值）
  const int SLOT_COUNT = 7;

  for (int index = 0; index < SLOT_COUNT; ++index) {
    uint16_t creatureId = 0;
    uint16_t count = 0;

    // 获取对应槽位的生物数据
    if (index < creatureSet.creatures.size()) {
      creatureId = creatureSet.creatures[index].first;
      count = creatureSet.creatures[index].second;
    }

    // 保存生物ID
    if (features.levelAB) {
      writer.writeU16(creatureId);
    } else {
      writer.writeU8(static_cast<uint8_t>(creatureId));
    }

    // 保存生物数量
    writer.writeU16(count);
  }
}

static void saveMessageAndGuards(Writer &writer, H3mData &data,
                                 const H3mObject &object) {
  // 检查是否有消息
  auto it = object.data.find("message");
  bool hasMessage = (it != object.data.end());

  writer.writeU8(hasMessage ? 1 : 0);

  if (hasMessage) {
    // 保存消息字符串
    writer.writeString(std::any_cast<std::string>(it->second));

    // 检查是否有守卫
    auto guardIt = object.data.find("guards");
    bool hasGuards = (guardIt != object.data.end());
    writer.writeU8(hasGuards ? 1 : 0);

    if (hasGuards) {
      // 保存守卫生物组
      const auto &guards = std::any_cast<H3mCreatureSet>(guardIt->second);
      saveCreatureSet(writer, data, guards);
    }

    // 跳过4字节（与读取时的reader.skip(4)对应）
    writer.writeU32(0); // 写入4个0字节
  }
}

static void saveBoxContent(Writer &writer, H3mData &data,
                           const H3mObject &object) {
  auto &features = data.features;

  // 1. 保存消息和守卫
  saveMessageAndGuards(writer, data, object);

  // 2. 保存英雄经验
  uint32_t heroExperience =
      object.data.contains("heroExperience")
          ? std::any_cast<uint32_t>(object.data.at("heroExperience"))
          : 0;
  writer.writeU32(heroExperience);

  // 3. 保存魔法值变化
  int32_t manaDiff = object.data.contains("manaDiff")
                         ? std::any_cast<int32_t>(object.data.at("manaDiff"))
                         : 0;
  writer.writeU32(static_cast<uint32_t>(manaDiff));

  // 4. 保存士气
  int8_t morale = object.data.contains("morale")
                      ? std::any_cast<int8_t>(object.data.at("morale"))
                      : 0;
  writer.writeU8(static_cast<uint8_t>(morale));

  // 5. 保存幸运
  int8_t luck = object.data.contains("luck")
                    ? std::any_cast<int8_t>(object.data.at("luck"))
                    : 0;
  writer.writeU8(static_cast<uint8_t>(luck));

  // 6. 保存资源
  std::array<uint32_t, 7> resources = {0};
  if (object.data.contains("resources")) {
    resources =
        std::any_cast<std::array<uint32_t, 7>>(object.data.at("resources"));
  }
  for (int x = 0; x < features.resourcesCount; ++x) {
    writer.writeU32(resources[x]);
  }

  // 7. 保存基本技能
  std::array<uint8_t, 4> primary = {0};
  if (object.data.contains("primary")) {
    primary = std::any_cast<std::array<uint8_t, 4>>(object.data.at("primary"));
  }
  for (int x = 0; x < 4; ++x) {
    writer.writeU8(primary[x]);
  }

  // 8. 保存次要技能
  std::vector<std::pair<uint8_t, uint8_t>> secondary;
  if (object.data.contains("secondary")) {
    secondary = std::any_cast<std::vector<std::pair<uint8_t, uint8_t>>>(
        object.data.at("secondary"));
  }
  writer.writeU8(static_cast<uint8_t>(secondary.size()));
  for (const auto &skill : secondary) {
    writer.writeU8(skill.first);
    writer.writeU8(skill.second);
  }

  // 9. 保存神器
  std::vector<uint16_t> artifacts;
  if (object.data.contains("artifacts")) {
    artifacts =
        std::any_cast<std::vector<uint16_t>>(object.data.at("artifacts"));
  }
  writer.writeU8(static_cast<uint8_t>(artifacts.size()));
  for (uint16_t artifactId : artifacts) {
    if (features.levelAB) {
      writer.writeU16(artifactId);
    } else {
      writer.writeU8(static_cast<uint8_t>(artifactId));
    }
  }

  // 10. 保存法术
  std::vector<uint8_t> spells;
  if (object.data.contains("spells")) {
    spells = std::any_cast<std::vector<uint8_t>>(object.data.at("spells"));
  }
  writer.writeU8(static_cast<uint8_t>(spells.size()));
  for (uint8_t spellId : spells) {
    writer.writeU8(spellId);
  }

  // 11. 保存生物
  std::vector<std::pair<uint16_t, uint32_t>> creatures;
  if (object.data.contains("creatures")) {
    creatures = std::any_cast<std::vector<std::pair<uint16_t, uint32_t>>>(
        object.data.at("creatures"));
  }
  writer.writeU8(static_cast<uint8_t>(creatures.size()));
  for (const auto &creature : creatures) {
    if (features.levelAB) {
      writer.writeU16(creature.first);
    } else {
      writer.writeU8(static_cast<uint8_t>(creature.first));
    }
    writer.writeU16(static_cast<uint16_t>(creature.second));
  }

  // 12. 跳过8字节
  for (int i = 0; i < 8; ++i) {
    writer.writeU8(0);
  }
}

static void saveSingleObject(Writer &writer, H3mData &data,
                             const H3mObject &object) {
  // 保存位置坐标
  writer.writeU8(object.position[0]); // x
  writer.writeU8(object.position[1]); // y
  writer.writeU8(object.position[2]); // z

  const auto findDefIndex = [](const std::vector<H3mObject> &templates,
                               const H3mObject &object) {
    for (size_t i = 0; i < templates.size(); ++i) {
      if (templates[i].id == object.id && templates[i].subId == object.subId &&
          templates[i].type == object.type) {
        return (uint32_t)i;
      }
    }
    return (uint32_t)0;
  };

  // 查找并保存defIndex
  uint32_t defIndex = findDefIndex(data.originalTemplates, object);
  writer.writeU32(defIndex);

  // 跳过5字节（读取时跳过了5字节）
  for (int i = 0; i < 5; ++i) {
    writer.writeU8(0);
  }

  // 根据对象类型保存特定数据
  switch (static_cast<ObjectType>(object.id)) {
  case ObjectType::EVENT: {
    saveBoxContent(writer, data, object);
    auto availableFor =
        std::any_cast<std::set<uint8_t>>(object.data.at("availableFor"));
    writeBitmask(writer, availableFor, 1, 8, false);
    auto computerActivate =
        std::any_cast<uint8_t>(object.data.at("computerActivate"));
    auto removeAfterVisit =
        std::any_cast<uint8_t>(object.data.at("removeAfterVisit"));
    writer.writeU8(computerActivate);
    writer.writeU8(removeAfterVisit);
    writer.fill(4, 0);
    break;
  }
  case ObjectType::HERO:
  case ObjectType::RANDOM_HERO:
  case ObjectType::PRISON: {
    auto &features = data.features;
    const auto &hero = std::any_cast<H3mHero>(object.data.at("hero"));

    // 1. 保存identifier (AB版本)
    if (features.levelAB) {
      writer.writeU32(object.identifier);
    }

    // 2. 保存玩家ID和英雄子ID
    writer.writeU8(hero.playerId);
    writer.writeU8(hero.subId);

    // 3. 保存名称
    bool hasName = !hero.name.empty();
    writer.writeU8(hasName ? 1 : 0);
    if (hasName) {
      writer.writeString(hero.name);
    }

    // 4. 保存经验值
    if (features.levelSOD) {
      bool hasCustomExperience = (hero.exp > 0);
      writer.writeU8(hasCustomExperience ? 1 : 0);
      if (hasCustomExperience) {
        writer.writeU32(hero.exp);
      }
    } else {
      writer.writeU32(hero.exp);
    }

    // 5. 保存自定义肖像
    bool hasPortrait = (hero.customPortraitSource != 0);
    writer.writeU8(hasPortrait ? 1 : 0);
    if (hasPortrait) {
      writer.writeU8(hero.customPortraitSource);
    }

    // 6. 保存次要技能
    bool hasSecSkills = !hero.secSkills.empty();
    writer.writeU8(hasSecSkills ? 1 : 0);
    if (hasSecSkills) {
      writer.writeU32(static_cast<uint32_t>(hero.secSkills.size()));
      for (const auto &skill : hero.secSkills) {
        writer.writeU8(skill.first);  // 技能ID
        writer.writeU8(skill.second); // 技能等级
      }
    }

    // 7. 保存驻军
    bool hasGarrison = !hero.creatureSet.creatures.empty();
    writer.writeU8(hasGarrison ? 1 : 0);
    if (hasGarrison) {
      saveCreatureSet(writer, data, hero.creatureSet);
    }

    // 8. 保存军队阵型
    uint8_t armyFormation =
        object.data.count("armyFormation")
            ? std::any_cast<uint8_t>(object.data.at("armyFormation"))
            : 0;
    writer.writeU8(armyFormation);

    // 9. 保存神器
    saveArtifactsOfHero(writer, data, hero);

    // 10. 保存巡逻半径
    uint8_t patrolRadius =
        object.data.count("patrolRadius")
            ? std::any_cast<uint8_t>(object.data.at("patrolRadius"))
            : 0;
    writer.writeU8(patrolRadius);

    // 11. AB版本额外数据
    if (features.levelAB) {
      bool hasCustomBiography = !hero.biography.empty();
      writer.writeU8(hasCustomBiography ? 1 : 0);
      if (hasCustomBiography) {
        writer.writeString(hero.biography);
      }
      writer.writeU8(hero.gender);
    }

    // 12. 保存法术
    if (features.levelSOD) {
      bool hasCustomSpells = !hero.spells.empty();
      writer.writeU8(hasCustomSpells ? 1 : 0);
      if (hasCustomSpells) {
        writeBitmask(writer, hero.spells, features.spellsBytes,
                     features.spellsCount, false);
      }
    } else if (features.levelAB) {
      uint8_t spell = hero.spells.empty() ? 0 : *hero.spells.begin();
      writer.writeU8(spell);
    }

    // 13. 保存基本技能 (SOD版本)
    if (features.levelSOD) {
      bool hasCustomPrimSkills =
          (object.data.find("heroDefaultPrimSkills") == object.data.end());
      writer.writeU8(hasCustomPrimSkills ? 1 : 0);
      if (hasCustomPrimSkills) {
        for (int i = 0; i < 4; ++i) {
          writer.writeU8(hero.primSkills[i]);
        }
      }
    }

    // 14. 跳过16字节（读取时跳过了16字节）
    for (int i = 0; i < 16; ++i) {
      writer.writeU8(0);
    }
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
    auto &features = data.features;

    // 1. 保存identifier (AB版本)
    if (features.levelAB) {
      writer.writeU32(object.identifier);
    }

    // 2. 保存怪物数量和角色
    uint16_t count = object.data.count("count")
                         ? std::any_cast<uint16_t>(object.data.at("count"))
                         : 0;
    uint8_t character =
        object.data.count("character")
            ? std::any_cast<uint8_t>(object.data.at("character"))
            : 0;
    writer.writeU16(count);
    writer.writeU8(character);

    // 3. 检查是否有消息
    bool hasMessage = object.data.count("message") > 0;
    writer.writeU8(hasMessage ? 1 : 0);

    if (hasMessage) {
      // 保存消息
      writer.writeString(std::any_cast<std::string>(object.data.at("message")));
      // 保存资源
      std::array<uint32_t, 7> resources = {0};
      if (object.data.count("resources")) {
        resources =
            std::any_cast<std::array<uint32_t, 7>>(object.data.at("resources"));
      }
      for (int x = 0; x < features.resourcesCount; ++x) {
        writer.writeU32(resources[x]);
      }

      // 保存获得的神器
      uint16_t gainedArtifact =
          object.data.count("gainedArtifact")
              ? std::any_cast<uint16_t>(object.data.at("gainedArtifact"))
              : 0;
      if (features.levelAB) {
        writer.writeU16(gainedArtifact);
      } else {
        writer.writeU8(static_cast<uint8_t>(gainedArtifact));
      }
    }

    // 4. 保存标志位
    uint8_t neverFlees =
        object.data.count("neverFlees")
            ? std::any_cast<uint8_t>(object.data.at("neverFlees"))
            : 0;
    uint8_t notGrowingTeam =
        object.data.count("notGrowingTeam")
            ? std::any_cast<uint8_t>(object.data.at("notGrowingTeam"))
            : 0;
    writer.writeU8(neverFlees);
    writer.writeU8(notGrowingTeam);

    // 5. 跳过2字节
    writer.writeU16(0);
    break;
  }
  case ObjectType::OCEAN_BOTTLE:
  case ObjectType::SIGN: {
    auto message = std::any_cast<std::string>(object.data.at("message"));
    writer.writeString(message);
    writer.writeU32(0);
    break;
  }
  case ObjectType::SEER_HUT:
    break;
  case ObjectType::WITCH_HUT:
    break;
  case ObjectType::SCHOLAR:
    break;
  case ObjectType::GARRISON:
  case ObjectType::GARRISON2:
    break;
  case ObjectType::ARTIFACT:
  case ObjectType::RANDOM_ART:
  case ObjectType::RANDOM_TREASURE_ART:
  case ObjectType::RANDOM_MINOR_ART:
  case ObjectType::RANDOM_MAJOR_ART:
  case ObjectType::RANDOM_RELIC_ART:
  case ObjectType::SPELL_SCROLL:
    break;
  case ObjectType::RANDOM_RESOURCE:
  case ObjectType::RESOURCE:
    break;
  case ObjectType::RANDOM_TOWN:
  case ObjectType::TOWN:
    break;
  case ObjectType::MINE:
  case ObjectType::ABANDONED_MINE:
    break;
  case ObjectType::CREATURE_GENERATOR1:
  case ObjectType::CREATURE_GENERATOR2:
  case ObjectType::CREATURE_GENERATOR3:
  case ObjectType::CREATURE_GENERATOR4:
    break;
  case ObjectType::SHRINE_OF_MAGIC_INCANTATION:
  case ObjectType::SHRINE_OF_MAGIC_GESTURE:
  case ObjectType::SHRINE_OF_MAGIC_THOUGHT:
    break;
  case ObjectType::PANDORAS_BOX:
    break;
  case ObjectType::GRAIL:
    break;
  case ObjectType::RANDOM_DWELLING:
  case ObjectType::RANDOM_DWELLING_LVL:
  case ObjectType::RANDOM_DWELLING_FACTION:
    break;
  case ObjectType::QUEST_GUARD:
    break;
  case ObjectType::SHIPYARD:
  case ObjectType::LIGHTHOUSE:
    break;
  case ObjectType::HERO_PLACEHOLDER:
    break;
  default:
    // 其他对象类型没有额外数据
    break;
  }
}

static void saveObjects(Writer &writer, H3mData &data) {
  // 保存对象数量
  writer.writeU32(static_cast<uint32_t>(data.objects.size()));

  // 保存每个对象
  for (const auto &object : data.objects) {
    saveSingleObject(writer, data, object);
  }
}

void H3mSaver::saveMap(Writer &writer, H3mData &data) {
  saveMapHeader(writer, data);
  savePlayerInfo(writer, data);
  saveVictoryLossConditions(writer, data);
  saveTeamInfo(writer, data);
  saveAllowedHeroes(writer, data);
  saveDisposedHeroes(writer, data);
  saveMapOptions(writer);
  saveAllowedArtifacts(writer, data);
  saveAllowedSpellsAbilities(writer, data);
  saveRumors(writer, data);
  savePredefinedHeroes(writer, data);
  saveTerrain(writer, data);
}