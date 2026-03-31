#include "H3mDeSaver.h"
#include "Comp/HeroComp.h"
#include "Comp/MonsterComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/ResourceComp.h"
#include "Comp/TextureComp.h"
#include "Comp/TownComp.h"
#include "Ent/Ent.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Set/CreatureSet.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <utility>
#include <vector>

static void clearDefaultEnt() {
  for (auto i : {0, 1}) {
    std::vector<entt::entity> clear;
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<HeroComp>()) {
      auto hComp = registry.get<HeroComp>(ent);
      clear.push_back(hComp.flagEnt);
      clear.push_back(ent);
    }
    clear.append_range(registry.view<MonsterComp>());
    for (auto ent : clear) {
      registry.destroy(ent);
    }
    World::needSort = true;
  }
}

static void clearPickEnt(std::set<uint32_t> &s) {
  for (auto i : {0, 1}) {
    std::vector<entt::entity> clear;
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<ObjectComp>()) {
      auto oComp = registry.get<ObjectComp>(ent);
      if (s.contains(oComp.index)) {
        clear.push_back(ent);
      }
    }
    for (auto ent : clear) {
      registry.destroy(ent);
    }
    World::needSort = true;
  }
}

static void loadSeed(Reader &reader) {
  auto seed = reader.readU32();
  std::srand(seed);
  Global::gen.seed(seed);
}

static void loadHero(Reader &reader) {
  auto count = reader.readU32();
  for (uint8_t i = 0; i < count; i++) {
    HeroComp hComp;
    PlayerIdComp pComp;
    // pid
    pComp.id = reader.readU8();
    // por
    hComp.portrait = reader.readU8();
    // name
    auto hasName = reader.readU8();
    if (hasName) {
      auto name = reader.readString();
      hComp.name = u"name";
    }
    // exp
    hComp.exp = reader.readU32();
    // secSki
    auto secCount = reader.readU8();
    for (uint8_t j = 0; j < secCount; j++) {
      auto secId = reader.readU8();
      auto secLevel = reader.readU8();
      hComp.secSkills.push_back({secId, secLevel});
    }
    // cre
    auto creNum = reader.readU8();
    hComp.creatures.resize(creNum);
    for (uint8_t j = 0; j < creNum; j++) {
      auto creId = reader.readU8();
      auto creCount = reader.readU8();
      hComp.creatures.push_back({creId, creCount});
    }
    // artifact
    auto artNum = reader.readU8();
    hComp.artifacts.resize(artNum);
    for (uint8_t j = 0; j < artNum; j++) {
      auto artId = reader.readU16();
      hComp.artifacts[j] = artId;
    }
    // artifactPack
    auto artPackNum = reader.readU8();
    hComp.artifactsInBackpack.resize(artPackNum);
    for (uint8_t j = 0; j < artPackNum; j++) {
      auto artId = reader.readU16();
      hComp.artifactsInBackpack[j] = artId;
    }
    // spell
    auto sNum = reader.readU8();
    for (uint8_t j = 0; j < sNum; j++) {
      auto sId = reader.readU8();
      hComp.spells.insert(sId);
    }
    // primSki
    hComp.primSkills[0] = reader.readU8();
    hComp.primSkills[1] = reader.readU8();
    hComp.primSkills[2] = reader.readU8();
    hComp.primSkills[3] = reader.readU8();

    // visitIndex
    auto vIndNum = reader.readU32();
    for (uint8_t j = 0; j < vIndNum; j++) {
      auto oId = reader.readU32();
      hComp.visitedIndex.insert(oId);
    }
    // visit
    auto viNum = reader.readU32();
    for (uint8_t j = 0; j < viNum; j++) {
      auto oId = reader.readU32();
      hComp.visited.insert(oId);
    }
    // movement
    hComp.movement = reader.readU32();
    // mana
    hComp.mana = reader.readU32();
    // moveType
    hComp.moveType = reader.readU8();
    // subId
    hComp.subId = reader.readU8();
    // sleep
    hComp.sleep = reader.readU8();
    ObjectComp oComp;
    oComp.type = ObjectType::HERO;
    // x,y,z
    oComp.x = reader.readU8();
    oComp.y = reader.readU8();
    auto level = reader.readU8();
    // advBouns
    auto advBounsNum = reader.readU32();
    for (uint8_t j = 0; j < advBounsNum; j++) {
      AdventureBonus bouns;
      auto type = reader.readU8();
      bouns.src = reader.readU8();
      bouns.type = reader.readU8();
      bouns.subType = reader.readU8();
      bouns.val = reader.readU32();
      hComp.adventureBonus.insert({type, bouns});
    }
    // texturePath
    TextureComp tComp;
    tComp.index = 0;
    tComp.time = 0;
    tComp.path = reader.readString();
    // flip
    PositionComp posComp;
    posComp.flip = reader.readU8();
    posComp.point = {static_cast<float>((oComp.x - 2) * 32),
                     static_cast<float>((oComp.y - 1) * 32)};
    posComp.z = reader.readU64();
    // level
    auto &r = World::registrys[level];
    auto ent = r.create();
    r.emplace<HeroComp>(ent, hComp);
    r.emplace<PlayerIdComp>(ent, pComp);
    r.emplace<ObjectComp>(ent, oComp);
    r.emplace<TextureComp>(ent, tComp);
    r.emplace<PositionComp>(ent, posComp);
  }
}

static void loadMonster(Reader &reader) {
  auto count = reader.readU32();
  for (uint8_t i = 0; i < count; i++) {
    MonsterComp mComp;
    ObjectComp oComp;
    mComp.id = reader.readU32();
    mComp.count = reader.readU16();
    mComp.initialCharacter = reader.readU8();
    mComp.hasMessage = reader.readU8();
    if (mComp.hasMessage) {
      mComp.message = reader.readString();
      for (uint8_t j = 0; j < 7; j++) {
        mComp.resources[j] = reader.readU32();
      }
      mComp.gainedArtifact = reader.readU16();
    }
    mComp.neverFlees = reader.readU8();
    mComp.notGrowingTeam = reader.readU8();

    oComp.x = reader.readU8();
    oComp.y = reader.readU8();
    auto level = reader.readU8();
    PositionComp posComp;
    posComp.flip = 0;
    posComp.point = {static_cast<float>((oComp.x - 1) * 32),
                     static_cast<float>((oComp.y - 1) * 32)};
    posComp.z = (int64_t)reader.readU64();

    // texturePath
    TextureComp tComp;
    tComp.index = 0;
    tComp.time = 0;
    tComp.path = CreatureSet::fullCreatures[mComp.id]->graphics.adventure;

    // level
    auto &r = World::registrys[level];
    auto ent = r.create();
    r.emplace<MonsterComp>(ent, mComp);
    r.emplace<ObjectComp>(ent, oComp);
    r.emplace<TextureComp>(ent, tComp);
    r.emplace<PositionComp>(ent, posComp);
  }
}

static std::pair<uint8_t, entt::entity> findEnt(uint32_t index) {
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<ObjectComp>()) {
      auto oComp = registry.get<ObjectComp>(ent);
      if (oComp.index == index) {
        return {i, ent};
      }
    }
  }
  return {0, entt::null};
}

static void loadTown(Reader &reader) {
  auto count = reader.readU32();
  for (uint8_t i = 0; i < count; i++) {
    auto index = reader.readU32();
    auto [in, ent] = findEnt(index);
    auto &r = World::registrys[in];
    auto &tComp = r.get<TownComp>(ent);
    auto buildSize = reader.readU8();
    for (uint8_t j = 0; j < buildSize; j++) {
      auto bId = reader.readU8();
      tComp.buildings[bId] = Ent::loadBuild(in, ent, bId);
    }
    auto garNum = reader.readU8();
    for (uint8_t j = 0; j < garNum; j++) {
      auto garId = reader.readU16();
      auto garCount = reader.readU32();
      tComp.garCreatures.push_back({garId, garCount});
    }
    tComp.hasBuild = reader.readU8();
    auto vNum = reader.readU8();
    for (uint8_t j = 0; j < vNum; j++) {
      auto vSize = reader.readU8();
      auto bId = reader.readU8();
      for (uint8_t k = 0; k < vSize - 1; k++) {
        auto heroPor = reader.readU8();
        tComp.visitHeros[bId].insert(heroPor);
      }
    }
    r.emplace_or_replace<TownComp>(ent, tComp);
  }
}

void H3mDeSaver::afterEntLoad(Reader &reader) {
  clearDefaultEnt();
  auto size = reader.size();
  reader.seek(size - 4);
  auto cursor = reader.readU32();
  reader.seek(cursor);
  // seed
  loadSeed(reader);
  loadHero(reader);
  loadTown(reader);
  loadMonster(reader);
}

void H3mDeSaver::loadMap(Reader &reader) {}