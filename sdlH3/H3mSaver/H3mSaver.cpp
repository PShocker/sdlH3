#include "H3mSaver.h"
#include "Comp/BoatComp.h"
#include "Comp/DwellingComp.h"
#include "Comp/HeroComp.h"
#include "Comp/MonsterComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/RefugeeComp.h"
#include "Comp/TextureComp.h"
#include "Comp/TownComp.h"
#include "Comp/WaterWheelComp.h"
#include "Comp/WindMillComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mHero.h"
#include "SDL3/SDL_iostream.h"
#include "SDL3/SDL_stdinc.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include <bit>
#include <bitset>
#include <cstdint>
#include <set>
#include <vector>

template <typename... Components> static uint32_t compCount() {
  uint32_t count = 0;
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    auto view = registry.view<Components...>();
    // view 返回的是同时拥有所有 Components 的实体
    for (auto entity : view) {
      count++;
    }
  }
  return count;
}

static void saveHero(Writer &writer) {
  auto hCount = compCount<HeroComp, PlayerIdComp>();
  writer.writeU32(hCount);

  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<HeroComp, PlayerIdComp>()) {
      auto &hComp = registry.get<HeroComp>(ent);
      auto &pId = registry.get<PlayerIdComp>(ent);
      writer.writeU8(pId.id);
      writer.writeU8(hComp.portrait);
      auto hasName = hComp.name.empty();
      writer.writeU8(hasName);
      if (hasName) {
        writer.writeString("name");
      }
      // exp
      writer.writeU32(hComp.exp);

      //   secNum
      auto secNum = hComp.secSkills.size();
      writer.writeU8(secNum);
      for (auto [secId, secLevel] : hComp.secSkills) {
        writer.writeU8(secId);
        writer.writeU8(secLevel);
      }
      // creNum
      auto creNum = hComp.creatures.size();
      writer.writeU8(creNum);
      for (auto [creId, creCount] : hComp.creatures) {
        writer.writeU8(creId);
        writer.writeU8(creCount);
      }
      // artifact
      auto artNum = hComp.artifacts.size();
      writer.writeU8(artNum);
      for (auto artId : hComp.artifacts) {
        writer.writeU16(artId);
      }
      // artifactPack
      auto artPackNum = hComp.artifactsInBackpack.size();
      writer.writeU8(artPackNum);
      for (auto artId : hComp.artifactsInBackpack) {
        writer.writeU16(artId);
      }
      // spell
      auto spellNum = hComp.spells.size();
      writer.writeU8(spellNum);
      for (auto sId : hComp.spells) {
        writer.writeU8(sId);
      }
      // primSki
      writer.writeU8(hComp.primSkills[0]);
      writer.writeU8(hComp.primSkills[1]);
      writer.writeU8(hComp.primSkills[2]);
      writer.writeU8(hComp.primSkills[3]);

      // visitEnts
      auto vNum = hComp.visitedIndex.size();
      writer.writeU32(vNum);
      for (auto index : hComp.visitedIndex) {
        writer.writeU32(index);
      }
      // visit
      auto viNum = hComp.visited.size();
      writer.writeU32(viNum);
      for (auto vi : hComp.visited) {
        writer.writeU8(vi);
      }
      // movement
      writer.writeU32(hComp.movement);
      // mana
      writer.writeU32(hComp.mana);
      // moveType
      writer.writeU8(hComp.moveType);
      // subId
      writer.writeU8(hComp.subId);
      // sleep
      writer.writeU8(hComp.sleep);
      // x,y,z
      auto &oComp = registry.get<ObjectComp>(ent);
      writer.writeU8(oComp.x);
      writer.writeU8(oComp.y);
      writer.writeU8(i);

      // advBonuse
      auto advNum = hComp.adventureBonus.size();
      writer.writeU32(advNum);
      for (auto [i, val] : hComp.adventureBonus) {
        writer.writeU8(i);
        writer.writeU8(val.src);
        writer.writeU8(val.type);
        writer.writeU8(val.subType);
        writer.writeU32(val.val);
      }
      // texturePath
      auto &tComp = registry.get<TextureComp>(ent);
      writer.writeString(tComp.path);
      // flip
      auto &pComp = registry.get<PositionComp>(ent);
      writer.writeU8(pComp.flip);
      // z
      writer.writeU64(pComp.z);
    }
  }
  return;
}

static void saveMonster(Writer &writer) {
  auto mCount = compCount<MonsterComp, ObjectComp>();
  writer.writeU32(mCount);

  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<MonsterComp, ObjectComp>()) {
      auto &mComp = registry.get<MonsterComp>(ent);
      auto &oComp = registry.get<ObjectComp>(ent);
      writer.writeU32(mComp.id);
      writer.writeU16(mComp.count);
      writer.writeU8(mComp.initialCharacter);
      bool hasMessage = mComp.hasMessage;
      writer.writeU8(hasMessage);
      if (hasMessage) {
        writer.writeString(mComp.message);
        for (auto r : mComp.resources) {
          writer.writeU32(r);
        }
        writer.writeU16(mComp.gainedArtifact);
      }
      writer.writeU8(mComp.neverFlees);
      writer.writeU8(mComp.notGrowingTeam);

      writer.writeU8(oComp.x);
      writer.writeU8(oComp.y);
      writer.writeU8(i);

      auto &posComp = registry.get<PositionComp>(ent);
      writer.writeU64(posComp.z);
    }
  }
}

static void saveTown(Writer &writer) {
  auto tCount = compCount<TownComp, ObjectComp>();
  writer.writeU32(tCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<TownComp, ObjectComp>()) {
      auto &tComp = registry.get<TownComp>(ent);
      auto &oComp = registry.get<ObjectComp>(ent);
      // index
      writer.writeU32(oComp.index);
      // build
      auto buildsSize = tComp.buildings.size();
      writer.writeU8(buildsSize);
      for (auto [key, val] : tComp.buildings) {
        writer.writeU8(key);
      }
      // gar
      auto garNum = tComp.garCreatures.size();
      writer.writeU8(garNum);
      for (auto [garId, garCount] : tComp.garCreatures) {
        writer.writeU16(garId);
        writer.writeU32(garCount);
      }
      // hasbuild
      writer.writeU8(tComp.hasBuild);
      // visitHeros
      auto vNum = tComp.visitHeros.size();
      writer.writeU8(vNum);
      for (auto [key, val] : tComp.visitHeros) {
        writer.writeU8(val.size() + 1);
        writer.writeU8(key);
        for (auto v : val) {
          writer.writeU8(v);
        }
      }
    }
  }
}

static void saveFog(Writer &writer) {
  for (auto fogs : Global::fogs) {
    for (auto f : fogs) {
      for (auto ff : f) {
        writer.writeU8(ff);
      }
    }
  }
}

static void saveSeed(Writer &writer) { writer.writeU32(Global::seed); }

static void saveDwe(Writer &writer) {
  auto dCount = compCount<DwellingComp, ObjectComp>();
  writer.writeU32(dCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<DwellingComp, ObjectComp>()) {
      auto &dComp = registry.get<DwellingComp>(ent);
      auto &oComp = registry.get<ObjectComp>(ent);
      // index
      writer.writeU32(oComp.index);
      // gar
      auto garNum = dComp.garCreatures.size();
      writer.writeU8(garNum);
      for (auto [garId, garCount] : dComp.garCreatures) {
        writer.writeU8(garId);
        writer.writeU8(garCount);
      }
      // creNum
      auto creNum = dComp.creatures.size();
      writer.writeU8(creNum);
      for (auto [creId, creCount] : dComp.creatures) {
        writer.writeU8(creCount);
      }
    }
  }
}

static void saveRefugee(Writer &writer) {
  auto rCount = compCount<RefugeeComp, ObjectComp>();
  writer.writeU32(rCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<RefugeeComp, ObjectComp>()) {
      auto &rComp = registry.get<RefugeeComp>(ent);
      auto &oComp = registry.get<ObjectComp>(ent);
      // index
      writer.writeU32(oComp.index);

      // creNum
      auto creNum = rComp.creatures.size();
      writer.writeU8(creNum);
      for (auto [creId, creCount] : rComp.creatures) {
        writer.writeU8(creId);
        writer.writeU8(creCount);
      }
    }
  }
}

static void saveObject(Writer &writer) {
  auto oCount = compCount<ObjectComp>();
  writer.writeU32(oCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<ObjectComp>()) {
      auto &oComp = registry.get<ObjectComp>(ent);
      writer.writeU32(oComp.index);
    }
  }
}

static void savePuzzle(Writer &writer) {
  for (auto puzzle : Global::puzzle) {
    writer.writeU8(puzzle.size());
    for (auto p : puzzle) {
      writer.writeU8(p);
    }
  }
}

static void saveWaterWheel(Writer &writer) {
  auto wCount = compCount<WaterWheelComp>();
  writer.writeU32(wCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<ObjectComp, WaterWheelComp>()) {
      auto &oComp = registry.get<ObjectComp>(ent);
      auto &wComp = registry.get<WaterWheelComp>(ent);
      writer.writeU32(oComp.index);
      writer.writeU8(wComp.resources.size());
      for (auto [rId, rCount] : wComp.resources) {
        writer.writeU8(rId);
        writer.writeU64(rCount);
      }
    }
  }
}

static void saveWindMill(Writer &writer) {
  auto wCount = compCount<WindMillComp>();
  writer.writeU32(wCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<ObjectComp, WindMillComp>()) {
      auto &oComp = registry.get<ObjectComp>(ent);
      auto &wComp = registry.get<WindMillComp>(ent);
      writer.writeU32(oComp.index);
      writer.writeU8(wComp.resources.size());
      for (auto [rId, rCount] : wComp.resources) {
        writer.writeU8(rId);
        writer.writeU64(rCount);
      }
    }
  }
}

static void saveBoat(Writer &writer) {
  auto bCount = compCount<BoatComp>();
  writer.writeU32(bCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<ObjectComp, BoatComp>()) {
      auto &oComp = registry.get<ObjectComp>(ent);
      auto &bComp = registry.get<BoatComp>(ent);
      auto &tComp = registry.get<TextureComp>(ent);
      auto &posComp = registry.get<PositionComp>(ent);
      writer.writeString(bComp.path);
      writer.writeString(tComp.path);
      writer.writeU8(oComp.x);
      writer.writeU8(oComp.y);
      writer.writeU8(i);
      writer.writeU8(posComp.flip);
      writer.writeU64(posComp.z);
    }
  }
}

static void savePlayerId(Writer &writer) {
  auto pCount = compCount<PlayerIdComp, ObjectComp>();
  writer.writeU32(pCount);
  for (auto i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<ObjectComp, PlayerIdComp>()) {
      auto &oComp = registry.get<ObjectComp>(ent);
      auto &pComp = registry.get<PlayerIdComp>(ent);
      writer.writeU32(oComp.index);
      writer.writeU8(pComp.id);
    }
  }
}

static void saveTavernHero(Writer &writer) {
  auto tHeros = Global::tavernHeros[Global::playerId];
  uint8_t count = 0;
  for (auto ent : tHeros) {
    if (ent != entt::null) {
      count++;
    }
  }
  writer.writeU8(count);
  for (auto ent : tHeros) {
    if (ent != entt::null) {
    }
  }
}

void H3mSaver::saveMap(const std::string &filePath) {
  Writer writer(filePath.c_str());
  auto reader = Global::mapData.reader;
  reader.seek(0);
  char *originData = (char *)SDL_malloc(reader.size());
  SDL_ReadIO(reader.stream, originData, reader.size());
  SDL_WriteIO(writer.stream, originData, reader.size());
  SDL_free(originData);
  auto cursor = reader.cursor();
  // seed,Hero,Town,Monster,Object
  saveSeed(writer);
  saveObject(writer);
  savePlayerId(writer);
  saveHero(writer);
  saveTown(writer);
  saveBoat(writer);
  saveMonster(writer);
  saveDwe(writer);
  saveRefugee(writer);
  saveWaterWheel(writer);
  saveWindMill(writer);
  savePuzzle(writer);
  saveFog(writer);
  // save cursor
  writer.writeU32(cursor);
  writer.flush();
  writer.close();
}