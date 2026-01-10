#include "HeroSys.h"
#include "Cfg/AudioCfg.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/TerrainCfg.h"
#include "Comp/BoatComp.h"
#include "Comp/CampFireComp.h"
#include "Comp/FlotsamComp.h"
#include "Comp/GateComp.h"
#include "Comp/HeroComp.h"
#include "Comp/LeanToComp.h"
#include "Comp/MarketComp.h"
#include "Comp/MonolithComp.h"
#include "Comp/MysGarComp.h"
#include "Comp/ObeliskComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/ResourceComp.h"
#include "Comp/SeaChestComp.h"
#include "Comp/TerrainComp.h"
#include "Comp/TextureComp.h"
#include "Comp/TownComp.h"
#include "Comp/WhirlpoolComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "FreeTypeSys.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Point/Point.h"
#include "SDL3/SDL_rect.h"
#include "Sys/gui/CameraSys.h"
#include "Sys/gui/CursorSys.h"
#include "Sys/gui/DwellingSys.h"
#include "Sys/gui/WarMachineFacSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

static void ambientAudio(uint8_t id) {}

static void visitAudio(uint8_t id) {
  auto &rAudio = AudioCfg::objectAudio.at(id)[AudioCfg::VISIT];
  int randomIndex = std::rand() % rAudio.size();
  auto audioStr = rAudio[randomIndex];
  if (!Global::audioData.contains(audioStr)) {
    Global::audioData[audioStr] = 0;
  }
}

static void removeAudio(uint8_t id) {
  auto &rAudio = AudioCfg::objectAudio.at(id)[AudioCfg::REMOVAL];
  int randomIndex = std::rand() % rAudio.size();
  auto audioStr = rAudio[randomIndex];
  if (!Global::audioData.contains(audioStr)) {
    Global::audioData[audioStr] = 0;
  }
}

static bool checkAccessibility(ObjectType type, int heroX, int heroY,
                               int accessX, int accessY) {
  const bool isAccessibleType =
      type == ObjectType::NOTHING || type == ObjectType::BOAT ||
      type == ObjectType::HERO || type == ObjectType::MONSTER ||
      type == ObjectType::ARTIFACT || type == ObjectType::RESOURCE ||
      type == ObjectType::TREASURE_CHEST || type == ObjectType::TAVERN ||
      type == ObjectType::PRISON || type == ObjectType::SCHOLAR ||
      type == ObjectType::PANDORAS_BOX || type == ObjectType::CAMPFIRE ||
      type == ObjectType::CORPSE || type == ObjectType::SEA_CHEST ||
      type == ObjectType::SIRENS || type == ObjectType::MERMAID ||
      type == ObjectType::FLOTSAM;

  const bool inProximity =
      std::abs(accessX - heroX) <= 32 && std::abs(accessY - heroY) <= 32;
  const bool exactPosition = (heroX == accessX) && (heroY == accessY);

  return isAccessibleType ? inProximity : exactPosition;
}

static void clearPathEntities(entt::registry &registry, HeroComp &heroComp) {
  for (auto pathEnt : heroComp.pathEnts) {
    registry.destroy(pathEnt);
  }
  heroComp.pathEnts.clear();

  for (auto pathEntBack : heroComp.pathEntsBack) {
    registry.destroy(pathEntBack);
  }
  heroComp.pathEntsBack.clear();
  heroComp.goalEnt = std::nullopt;
  World::needSort = true;
}

static std::function<bool()> createCameraCallback(const SDL_FPoint &oldPoint,
                                                  const SDL_FPoint &newPoint) {
  const float oldX = oldPoint.x + 48;
  const float oldY = oldPoint.y + 48;
  const float newX = newPoint.x + 48;
  const float newY = newPoint.y + 48;

  static uint8_t callCount = 0;
  callCount = 0;

  return [oldX, oldY, newX, newY]() -> bool {
    if (callCount == 1) {
      CameraSys::focus(newX, newY);
      return true;
    }
    CameraSys::focus((oldX + newX) / 2, (oldY + newY) / 2);
    callCount++;
    return false;
  };
}

static void handleLand(entt::entity heroEnt, entt::entity goalEnt,
                       ObjectComp &objectComp) {
  auto &registry = World::registrys[World::level];
  const int goalX = objectComp.x + objectComp.accessTiles[0].first;
  const int goalY = objectComp.y + objectComp.accessTiles[0].second;

  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();
  World::iterateSystems.push_back([heroEnt, goalX, goalY]() {
    auto &registry = World::registrys[World::level];
    auto &heroPos = registry.get<PositionComp>(heroEnt);
    auto &heroObj = registry.get<ObjectComp>(heroEnt);
    auto &heroComp = registry.get<HeroComp>(heroEnt);
    auto &texture = registry.get<TextureComp>(heroEnt);

    const auto oldPoint = heroPos.point;
    const char direct = texture.path.back();

    // 更新英雄为马类型
    heroComp.moveType = HeroComp::HORSE;
    texture.path.resize(texture.path.size() - 2);

    // 加载船只并更新纹理
    Ent::loadBoat(texture.path, heroObj.x, heroObj.y, World::level,
                  direct - '0', heroPos.flip);
    texture.path = std::format("AH{:02d}_.def/", heroComp.subId) + direct;

    // 更新旗帜
    auto &flagTexture = registry.get<TextureComp>(heroComp.flagEnt);
    auto &playerId = registry.get<PlayerIdComp>(heroEnt);
    flagTexture.path =
        std::format("AF0{}.def/", playerId.id) + texture.path.back();

    // 更新位置
    heroPos.point = {static_cast<float>((goalX - 1) * 32),
                     static_cast<float>((goalY - 1) * 32)};
    heroObj.x = goalX + 1;
    heroObj.y = goalY;
    heroPos.z = heroPos.z - ((heroPos.z / 1000000) % 1000) * 1000000 +
                heroObj.y * 1000000;

    // 更新旗帜位置
    auto &flagPos = registry.get<PositionComp>(heroComp.flagEnt);
    flagPos.point = heroPos.point;
    flagPos.z = heroPos.z;

    // 设置摄像机过渡
    Global::fadeCallBack = createCameraCallback(oldPoint, heroPos.point);
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
  registry.erase<ObjectComp>(goalEnt);
  removeAudio(0);
}

static void handleGate(entt::entity heroEnt, entt::entity goalEnt) {
  auto &registry = World::registrys[World::level];
  auto &gateComp = registry.get<GateComp>(goalEnt);

  if (gateComp.level != 0xff) {
    // 检查地道另一边是否有英雄堵门
    for (auto ent :
         World::registrys[gateComp.level].view<HeroComp, ObjectComp>()) {
      auto &objectComp = World::registrys[gateComp.level].get<ObjectComp>(ent);
      if (objectComp.x == gateComp.x && objectComp.y == gateComp.y) {
        return;
      }
    }

    World::iterateSystemsBak.push_back(World::iterateSystems);
    World::iterateSystems.pop_back();
    const auto gateX = gateComp.x;
    const auto gateY = gateComp.y;
    const auto gateLevel = gateComp.level;
    const auto gateEnt = gateComp.goalEnt;

    World::iterateSystems.push_back([heroEnt, gateX, gateY, gateLevel,
                                     gateEnt]() {
      auto registry = &World::registrys[World::level];
      auto &textureComp = registry->get<TextureComp>(heroEnt);
      auto &heroComp = registry->get<HeroComp>(heroEnt);
      auto &positionComp = registry->get<PositionComp>(heroEnt);

      auto &heros = Global::heros[Global::playerId];
      auto &playerIdComp = registry->get<PlayerIdComp>(heroEnt);
      auto newHeroEnt =
          Ent::loadHero(heroComp, playerIdComp.id, gateX, gateY, gateLevel,
                        textureComp.path.back() - '0', positionComp.flip);
      heros[Global::herosIndex[Global::playerId]] = {gateLevel, newHeroEnt};

      registry = &World::registrys[gateLevel];
      CameraSys::focus(registry->get<PositionComp>(newHeroEnt).point.x + 48,
                       registry->get<PositionComp>(newHeroEnt).point.y + 48);

      World::registrys[World::level].destroy(heroComp.flagEnt);
      World::registrys[World::level].destroy(heroEnt);
      World::needSort = true;

      World::level = gateLevel;

      registry = &World::registrys[World::level];
      registry->get<HeroComp>(newHeroEnt).curEnt = gateEnt;

      return true;
    });
    Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                        Global::viewPort.h - 47};
    World::iterateSystems.push_back(World::enterFadeScrn);
    visitAudio((uint8_t)ObjectType::SUBTERRANEAN_GATE);
  }
}

static void handleMono(entt::entity heroEnt, entt::entity goalEnt) {
  auto &registry = World::registrys[World::level];
  auto &monoComp = registry.get<MonolithComp>(goalEnt);
  if (monoComp.goalEnt.empty()) {
    return;
  }
  auto goalMono = monoComp.goalEnt[std::rand() % monoComp.goalEnt.size()];

  registry.get<HeroComp>(heroEnt).curEnt = goalMono;

  auto goalX = registry.get<MonolithComp>(goalMono).x;
  auto goalY = registry.get<MonolithComp>(goalMono).y;

  for (auto ent : registry.view<HeroComp, ObjectComp>()) {
    auto &oComp = registry.get<ObjectComp>(ent);
    if (oComp.x - 1 == goalX && oComp.y == goalY) {
      registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
      return;
    }
  }

  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();

  World::iterateSystems.push_back([heroEnt, goalX, goalY]() {
    HeroSys::heroTelePort(heroEnt, goalX, goalY);
    CameraSys::focus(goalX * 32 + 16, goalY * 32 + 16);
    Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
    CursorSys::clearHeroPath();

    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
}

static void handleResource(entt::entity goalEnt) {
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();
  World::iterateSystems.push_back([goalEnt]() {
    World::registrys[World::level].destroy(goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);

  Global::fadeCallBack =
      [rComp = World::registrys[World::level].get<ResourceComp>(goalEnt)]() {
        Global::resources[Global::playerId][rComp.id] += rComp.count;
        auto textures = Global::defCache["RESOUR82.def/0"];
        auto texture0 = textures[rComp.id];
        auto str0 = FreeTypeSys::str(rComp.count);
        Global::advStats = {{texture0, str0}};
        Global::advStatTime = Window::dtNow + 5000;
        auto strPool = *Lang::strPool[Global::langIndex];
        Global::advStrs = {{{92, 0}, {240, 224, 104, 255}, strPool[1003]}};

        return true;
      };
  removeAudio((uint8_t)ObjectType::RESOURCE);
}

static void handleSeaChest(entt::entity heroEnt, entt::entity goalEnt) {
  auto sComp = World::registrys[World::level].get<SeaChestComp>(goalEnt);
  if (!sComp.artifacts.empty()) {
    World::enterSeaChest(heroEnt, goalEnt);
    return;
  }
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();
  World::iterateSystems.push_back([goalEnt]() {
    World::registrys[World::level].destroy(goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);

  Global::fadeCallBack = [sComp]() {
    for (auto r : sComp.resources) {
      Global::resources[Global::playerId][r.first] += r.second;
    }
    auto textures = Global::defCache["RESOUR82.def/0"];
    auto size = sComp.resources.size();
    if (size == 2) {
      auto texture0 = textures[sComp.resources[0].first];
      auto texture1 = textures[sComp.resources[1].first];

      auto str0 = FreeTypeSys::str(sComp.resources[0].second);
      auto str1 = FreeTypeSys::str(sComp.resources[1].second);

      Global::advStats = {{texture0, str0}, {texture1, str1}};
    } else {
      auto texture0 = textures[sComp.resources[0].first];
      auto str0 = FreeTypeSys::str(sComp.resources[0].second);
      Global::advStats = {{texture0, str0}};
    }
    Global::advStatTime = Window::dtNow + 5000;
    auto strPool = *Lang::strPool[Global::langIndex];
    Global::advStrs = {{{92, 0}, {240, 224, 104, 255}, strPool[1005]}};
    return true;
  };
}

static void handleCampFire(entt::entity goalEnt) {
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();
  World::iterateSystems.push_back([goalEnt]() {
    World::registrys[World::level].destroy(goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);

  Global::fadeCallBack =
      [cComp = World::registrys[World::level].get<CampFireComp>(goalEnt)]() {
        for (auto r : cComp.resources) {
          Global::resources[Global::playerId][r.first] += r.second;
        }
        auto textures = Global::defCache["RESOUR82.def/0"];
        auto texture0 = textures[cComp.resources[0].first];
        auto texture1 = textures[cComp.resources[1].first];

        auto str0 = FreeTypeSys::str(cComp.resources[0].second);
        auto str1 = FreeTypeSys::str(cComp.resources[1].second);

        auto strPool = *Lang::strPool[Global::langIndex];
        Global::advStrs = {{{92, 0}, {240, 224, 104, 255}, strPool[936]}};
        Global::advStats = {{texture0, str0}, {texture1, str1}};
        Global::advStatTime = Window::dtNow + 5000;
        return true;
      };
}

static void handleFlotsam(entt::entity goalEnt) {
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();
  World::iterateSystems.push_back([goalEnt]() {
    World::registrys[World::level].destroy(goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);

  Global::fadeCallBack =
      [fComp = World::registrys[World::level].get<FlotsamComp>(goalEnt)]() {
        for (auto r : fComp.resources) {
          Global::resources[Global::playerId][r.first] += r.second;
        }
        auto textures = Global::defCache["RESOUR82.def/0"];
        auto size = fComp.resources.size();
        if (size == 2) {
          auto texture0 = textures[fComp.resources[0].first];
          auto texture1 = textures[fComp.resources[1].first];

          auto str0 = FreeTypeSys::str(fComp.resources[0].second);
          auto str1 = FreeTypeSys::str(fComp.resources[1].second);

          Global::advStats = {{texture0, str0}, {texture1, str1}};
        } else {
          auto texture0 = textures[fComp.resources[0].first];
          auto str0 = FreeTypeSys::str(fComp.resources[0].second);
          Global::advStats = {{texture0, str0}};
        }

        Global::advStatTime = Window::dtNow + 5000;
        auto strPool = *Lang::strPool[Global::langIndex];
        Global::advStrs = {{{92, 0}, {240, 224, 104, 255}, strPool[953]}};

        return true;
      };
}

static void handleLeanTo(entt::entity goalEnt) {
  auto &lComp = World::registrys[World::level].get<LeanToComp>(goalEnt);
  if (lComp.resources.empty()) {

  } else {
    for (auto r : lComp.resources) {
      Global::resources[Global::playerId][r.first] += r.second;
    }
    auto textures = Global::defCache["RESOUR82.def/0"];
    auto size = lComp.resources.size();
    if (size == 2) {
      auto texture0 = textures[lComp.resources[0].first];
      auto texture1 = textures[lComp.resources[1].first];

      auto str0 = FreeTypeSys::str(lComp.resources[0].second);
      auto str1 = FreeTypeSys::str(lComp.resources[1].second);

      Global::advStats = {{texture0, str0}, {texture1, str1}};
    } else {
      auto texture0 = textures[lComp.resources[0].first];
      auto str0 = FreeTypeSys::str(lComp.resources[0].second);
      Global::advStats = {{texture0, str0}};
    }
    Global::advStrs.clear();
    lComp.resources.clear();
  }

  Global::advStatTime = Window::dtNow + 5000;

  return;
}

static void handleMysGar(entt::entity goalEnt) {
  auto &mComp = World::registrys[World::level].get<MysGarComp>(goalEnt);
  for (auto r : mComp.resources) {
    Global::resources[Global::playerId][r.first] += r.second;
  }
  if (mComp.resources.empty()) {

  } else {
    auto textures = Global::defCache["RESOUR82.def/0"];
    auto size = mComp.resources.size();
    if (size == 2) {
      auto texture0 = textures[mComp.resources[0].first];
      auto texture1 = textures[mComp.resources[1].first];

      auto str0 = FreeTypeSys::str(mComp.resources[0].second);
      auto str1 = FreeTypeSys::str(mComp.resources[1].second);

      Global::advStats = {{texture0, str0}, {texture1, str1}};
    } else {
      auto texture0 = textures[mComp.resources[0].first];
      auto str0 = FreeTypeSys::str(mComp.resources[0].second);
      Global::advStats = {{texture0, str0}};
    }
    Global::advStrs.clear();
    mComp.resources.clear();
  }
  Global::advStatTime = Window::dtNow + 5000;
  return;
}

static void handleObelisk(entt::entity goalEnt) {
  auto &oComp = World::registrys[World::level].get<ObeliskComp>(goalEnt);
  Global::puzzle[Global::playerId].insert(oComp.puzzles.begin(),
                                          oComp.puzzles.end());
  World::enterPuzzle(goalEnt);
  return;
}

static void handleBoat(entt::entity heroEnt, entt::entity goalEnt) {
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();
  World::iterateSystems.push_back([heroEnt, goalEnt]() {
    auto &registry = World::registrys[World::level];
    auto &textureComp = registry.get<TextureComp>(heroEnt);
    auto &boatComp = registry.get<BoatComp>(goalEnt);
    auto &heroComp = registry.get<HeroComp>(heroEnt);
    auto &playerIdComp = registry.get<PlayerIdComp>(heroEnt);
    auto &heroPos = registry.get<PositionComp>(heroEnt);

    textureComp.path = boatComp.path + "/" + textureComp.path.back();
    heroComp.moveType = HeroComp::BOAT;

    auto &flagTexture = registry.get<TextureComp>(heroComp.flagEnt);
    flagTexture.path = BoatComp::boatFlagMap.at(boatComp.path) +
                       BoatComp::boatPlayerFlagMap.at(playerIdComp.id) +
                       ".def/" + textureComp.path.back();

    const auto oldPoint = heroPos.point;
    auto &heroObj = registry.get<ObjectComp>(heroEnt);
    auto &flagPos = registry.get<PositionComp>(heroComp.flagEnt);
    auto &boatPos = registry.get<PositionComp>(goalEnt);

    heroPos.point = boatPos.point;
    heroObj.x = heroPos.point.x / 32 + 2;
    heroObj.y = heroPos.point.y / 32 + 1;
    flagPos.point = boatPos.point;

    registry.destroy(goalEnt);
    World::needSort = true;

    Global::fadeCallBack = createCameraCallback(oldPoint, heroPos.point);
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
  removeAudio(0);
}

static void handleMonster(entt::entity goalEnt) {
  // TODO: 实现怪物处理逻辑
}

static void handleHeroMeet(entt::entity heroEnt, uint8_t level0,
                           entt::entity goalEnt, uint8_t level1) {
  // 判断是否是盟友或自己的英雄
  auto playerId0 = World::registrys[level0].get<PlayerIdComp>(heroEnt).id;
  auto playerId1 = World::registrys[level1].get<PlayerIdComp>(goalEnt).id;

  auto hComp0 = &World::registrys[level0].get<HeroComp>(heroEnt);
  auto hComp1 = &World::registrys[level1].get<HeroComp>(goalEnt);
  if (playerId0 == playerId1) {
    int8_t learnLevel = -1;
    // 判断有没有学术
    for (auto v2 : {hComp0->secSkills, hComp1->secSkills}) {
      for (auto v1 : v2) {
        if (v1.first == (uint8_t)HeroCfg::SecondarySkill::LEARNING) {
          learnLevel = std::max(learnLevel, (int8_t)v1.second);
        }
      }
    }
    if (learnLevel >= 0) {
      auto spellLevel = learnLevel + 2;
      World::enterLearn(heroEnt, goalEnt, level1);
    } else {
      World::enterHeroTrade(heroEnt, goalEnt, level1);
    }
  }
}

static void handleTown(entt::entity heroEnt, entt::entity goalEnt) {
  auto heroComp = &World::registrys[World::level].get<HeroComp>(heroEnt);
  heroComp->curEnt = goalEnt;
  auto &townComp = World::registrys[World::level].get<TownComp>(goalEnt);
  townComp.heroEnt[1] = heroEnt;
  World::enterTownScrn(World::level, goalEnt, (uint8_t)Enum::SCNTYPE::MOD);
}

static void handleMine(entt::entity heroEnt, entt::entity goalEnt) {
  auto playerId = World::registrys[World::level].get<PlayerIdComp>(goalEnt).id;
  auto &textureComp = World::registrys[World::level].get<TextureComp>(goalEnt);
  textureComp.path.back() = '0' + Global::playerId;
  if (Global::playerId != playerId) {
    World::enterMine(goalEnt);
  }
  World::registrys[World::level].get<PlayerIdComp>(goalEnt).id =
      Global::playerId;
}

static void handleWarMachine(entt::entity heroEnt, entt::entity goalEnt) {
  auto playerId = World::registrys[World::level].get<PlayerIdComp>(heroEnt).id;
  Global::goalEnt = goalEnt;
  Global::goalIndex = 0;
  auto count = WarMachineFacSys::maxCount();
  if (count >= 1) {
    Global::dweSliderNum = 1;
  } else {
    Global::dweSliderNum = 0;
  }
  World::enterWarMachineFac(heroEnt, goalEnt);
}

static void handleCreatureGentrator(entt::entity heroEnt,
                                    entt::entity goalEnt) {
  auto playerId = World::registrys[World::level].get<PlayerIdComp>(heroEnt).id;
  auto &textureComp = World::registrys[World::level].get<TextureComp>(goalEnt);
  textureComp.path.back() = '0' + playerId;
  World::registrys[World::level].get<PlayerIdComp>(goalEnt).id = playerId;
  Global::goalEnt = goalEnt;
  Global::goalIndex = 0;
  auto count = DwellingSys::maxCount();
  if (count >= 1) {
    Global::dweSliderNum = 1;
  } else {
    Global::dweSliderNum = 0;
  }
  World::enterDwe(heroEnt, goalEnt);
}

static void handleGarrison(entt::entity heroEnt, entt::entity goalEnt) {
  auto playerId = World::registrys[World::level].get<PlayerIdComp>(heroEnt).id;
  auto &textureComp = World::registrys[World::level].get<TextureComp>(goalEnt);
  textureComp.path.back() = '0' + playerId;
  World::registrys[World::level].get<PlayerIdComp>(goalEnt).id = playerId;
  World::enterGarrison(heroEnt, goalEnt);
}

static void handleShipy(entt::entity heroEnt, entt::entity goalEnt) {
  auto playerId = World::registrys[World::level].get<PlayerIdComp>(heroEnt).id;
  auto &textureComp = World::registrys[World::level].get<TextureComp>(goalEnt);
  textureComp.path.back() = '0' + playerId;
  World::registrys[World::level].get<PlayerIdComp>(goalEnt).id = playerId;
  World::enterShipyard(heroEnt, goalEnt);
}

static void handleRedOb(entt::entity heroEnt, entt::entity goalEnt) {
  auto objectComp = World::registrys[World::level].get<ObjectComp>(goalEnt);
  auto playerId = World::registrys[World::level].get<PlayerIdComp>(heroEnt).id;
  auto radius = 15;
  auto radius_sq = radius * radius;

  for (int x = -radius; x <= radius; ++x) {
    for (int y = -radius; y <= radius; ++y) {
      // 检查点是否在圆内（包括边界）
      if (x * x + y * y < radius_sq) {
        int16_t rX =
            std::clamp((int)objectComp.x + x, 0, (int)Global::mapSize - 1);
        int16_t rY =
            std::clamp((int)objectComp.y + y, 0, (int)Global::mapSize - 1);
        Global::fogs[playerId][World::level][rX + rY * Global::mapSize] = true;
      }
    }
  }

  auto strPool = *Lang::strPool[Global::langIndex];

  std::tuple<SDL_Point, SDL_Color, std::u16string> title(
      {92, 0}, {240, 224, 104, 255}, strPool[981]);

  std::tuple<SDL_Point, SDL_Color, std::u16string> des(
      {92, 50}, {255, 255, 255, 255}, strPool[680]);

  Global::advStrs = {title, des};
  Global::advStatTime = Window::dtNow + 5000;
  Global::advStats.clear();
}

static void handleGoalByType(entt::entity heroEnt, entt::entity goalEnt,
                             ObjectComp &objectComp) {
  auto &registry = World::registrys[World::level];
  switch (static_cast<ObjectType>(objectComp.type)) {
  case ObjectType::NOTHING:
    handleLand(heroEnt, goalEnt, objectComp);
    break;
  case ObjectType::TOWN:
    handleTown(heroEnt, goalEnt);
    break;
  case ObjectType::SUBTERRANEAN_GATE:
    handleGate(heroEnt, goalEnt);
    break;
  case ObjectType::MONOLITH_TWO_WAY:
  case ObjectType::MONOLITH_ONE_WAY_ENTRANCE:
    handleMono(heroEnt, goalEnt);
    break;
  case ObjectType::MONSTER:
    handleMonster(goalEnt);
    break;
  case ObjectType::ARTIFACT:
    World::enterArtifact(heroEnt, goalEnt);
    break;
  case ObjectType::RESOURCE:
    handleResource(goalEnt);
    break;
  case ObjectType::BOAT:
    handleBoat(heroEnt, goalEnt);
    break;
  case ObjectType::HERO:
    handleHeroMeet(heroEnt, World::level, goalEnt, World::level);
    break;
  case ObjectType::TREASURE_CHEST:
    // RESOUR82.def PSKILL.def
    World::enterTreasure(heroEnt, goalEnt);
    break;
  case ObjectType::MINE:
    handleMine(heroEnt, goalEnt);
    break;
  case ObjectType::WAR_MACHINE_FACTORY:
    handleWarMachine(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::CREATURE_GENERATOR1:
  case ObjectType::CREATURE_GENERATOR2:
  case ObjectType::CREATURE_GENERATOR3:
  case ObjectType::CREATURE_GENERATOR4:
    handleCreatureGentrator(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::GARRISON:
  case ObjectType::GARRISON2:
    handleGarrison(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::UNIVERSITY:
    World::enterUnivers(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::SHIPYARD:
    handleShipy(heroEnt, goalEnt);
    break;
  case ObjectType::TAVERN:
    World::enterTavern(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::WINDMILL:
    World::enterWindMill(goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::WATER_WHEEL:
    World::enterWaterWheel(goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::WARRIORS_TOMB:
    World::enterWarTomb(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::BLACK_MARKET:
    Global::makType =
        World::registrys[World::level].get<MarketComp>(goalEnt).type;
    World::enterMarket(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::REFUGEE_CAMP:
    World::enterLearnStone(heroEnt, goalEnt);
    break;
  case ObjectType::SHRINE_OF_MAGIC_GESTURE:
  case ObjectType::SHRINE_OF_MAGIC_INCANTATION:
  case ObjectType::SHRINE_OF_MAGIC_THOUGHT:
    World::enterShrMag(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::RALLY_FLAG:
    World::enterRalFlag(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::TREE_OF_KNOWLEDGE:
    World::enterKnoTree(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::SCHOOL_OF_WAR:
    World::enterSchoolWar(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::PRISON:
    World::enterPrison(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    visitAudio((uint8_t)ObjectType::PRISON);
    break;
  case ObjectType::WITCH_HUT:
    World::enterWitchHut(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::SCHOLAR:
    World::enterScholar(heroEnt, goalEnt);
    break;
  case ObjectType::PANDORAS_BOX:
    World::enterPandora(heroEnt, goalEnt);
    break;
  case ObjectType::SCHOOL_OF_MAGIC:
    World::enterSchoolMag(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::LEARNING_STONE:
    World::enterLearnStone(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::IDOL_OF_FORTUNE:
    World::enterIFortune(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::FOUNTAIN_OF_FORTUNE:
    World::enterFFortune(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::REDWOOD_OBSERVATORY:
    handleRedOb(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::CAMPFIRE:
    handleCampFire(goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::CORPSE:
    World::enterCorpse(heroEnt, goalEnt);
    break;
  case ObjectType::MARLETTO_TOWER:
    World::enterMarletto(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::TEMPLE:
    World::enterTemple(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::CRYPT:
    break;
  case ObjectType::WHIRLPOOL:
    World::enterWhirlPool(heroEnt, goalEnt);
    visitAudio((uint8_t)ObjectType::WHIRLPOOL);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::ARENA:
    World::enterArena(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::SEA_CHEST:
    handleSeaChest(heroEnt, goalEnt);
    break;
  case ObjectType::MERCENARY_CAMP:
    World::enterMerCamp(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::LIBRARY_OF_ENLIGHTENMENT:
    World::enterLibrary(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::HUT_OF_MAGI:
    World::enterHutMag(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::FLOTSAM:
    handleFlotsam(goalEnt);
    break;
  case ObjectType::LEAN_TO:
    handleLeanTo(goalEnt);
    break;
  case ObjectType::MYSTICAL_GARDEN:
    handleMysGar(goalEnt);
    break;
  case ObjectType::SIRENS:
    World::enterSirens(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::HILL_FORT:
    World::enterHillFt(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::FOUNTAIN_OF_YOUTH:
    World::enterFouYouth(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::OBELISK:
    handleObelisk(goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::FAERIE_RING:
    World::enterFaerieRing(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::ALTAR_OF_SACRIFICE:
    World::enterAltarSac(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::CARTOGRAPHER:
    World::enterCartographer(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::FREELANCERS_GUILD:
    Global::makType = (uint8_t)Enum::MARKET::CRE_SELL;
    World::enterMarket(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  case ObjectType::STAR_AXIS:
    World::enterStarAxis(heroEnt, goalEnt);
    registry.get<HeroComp>(heroEnt).curEnt = goalEnt;
    break;
  default:
    break;
  }
}

static bool heroGoal(entt::entity heroEnt) {
  auto &registry = World::registrys[World::level];
  auto &heroComp = registry.get<HeroComp>(heroEnt);
  // 1. 提前检查条件
  if (!heroComp.goalEnt.has_value() || heroComp.pathEnts.size() > 1) {
    return true;
  }
  auto goalEnt = heroComp.goalEnt.value();
  // 2. 验证目标实体
  if (!registry.valid(goalEnt)) {
    return true;
  }
  // 3. 确保目标有ObjectComp组件
  if (!registry.all_of<ObjectComp>(goalEnt)) {
    auto &objectComp = registry.emplace<ObjectComp>(goalEnt);
    auto &posComp = registry.get<PositionComp>(goalEnt);
    objectComp.type = static_cast<int16_t>(ObjectType::NOTHING);
    objectComp.x = posComp.point.x / 32;
    objectComp.y = posComp.point.y / 32;
    objectComp.accessTiles = {{0, 0}};
  }
  auto &objectComp = registry.get<ObjectComp>(goalEnt);
  auto &heroPos = registry.get<PositionComp>(heroEnt);
  // 4. 计算位置
  const int heroCenterX = heroPos.point.x + 32;
  const int heroCenterY = heroPos.point.y + 32;
  bool access = false;
  for (auto &pair : objectComp.accessTiles) {
    const int accessX = objectComp.x * 32 + pair.first * 32;
    const int accessY = objectComp.y * 32 + pair.second * 32;
    // 5. 检查可访问性
    if (checkAccessibility(static_cast<ObjectType>(objectComp.type),
                           heroCenterX, heroCenterY, accessX, accessY)) {
      access = true;
      break;
    }
  }
  if (!access) {
    return true;
  }

  // 6. 清理路径实体
  clearPathEntities(registry, heroComp);
  // 7. 根据不同类型处理目标
  handleGoalByType(heroEnt, goalEnt, objectComp);
  CursorSys::run();
  return false;
}

static void heroFlag(entt::entity heroEnt) {
  auto &registry = World::registrys[World::level];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  auto heroTextureComp = &registry.get<TextureComp>(heroEnt);

  auto flagPositionComp = &registry.get<PositionComp>(heroComp->flagEnt);
  flagPositionComp->point = registry.get<PositionComp>(heroEnt).point;
  flagPositionComp->flip = registry.get<PositionComp>(heroEnt).flip;
  flagPositionComp->z = registry.get<PositionComp>(heroEnt).z;
  auto flagTextureComp = &registry.get<TextureComp>(heroComp->flagEnt);
  flagTextureComp->path.back() = heroTextureComp->path.back();
}

static void heroDirect(entt::entity heroEnt, bool stopMove) {
  auto &registry = World::registrys[World::level];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  auto herotextureComp = &registry.get<TextureComp>(heroEnt);
  if (stopMove) {
    if (herotextureComp->path.back() - '0' >= 5) {
      herotextureComp->path.back() = herotextureComp->path.back() - 5;
      herotextureComp->index = 0;
      herotextureComp->time = 0;
    }
  } else if (!heroComp->pathEnts.empty()) {
    auto pathEnt = heroComp->pathEnts.front();
    auto pathPositionComp = &registry.get<PositionComp>(pathEnt);
    auto pathPoint = pathPositionComp->point;
    uint8_t flip = SDL_FLIP_NONE;
    auto heroPositionComp = &registry.get<PositionComp>(heroEnt);
    auto heroPoint = heroPositionComp->point + SDL_FPoint{32, 32};
    auto direct = direction(pathPoint, heroPoint);
    switch ((DIRECTION)direct) {
    case DIRECTION::UP: {
      direct = 5;
      break;
    }
    case DIRECTION::UPRIGHT: {
      direct = 6;
      break;
    }
    case DIRECTION::RIGHT: {
      direct = 7;
      break;
    }
    case DIRECTION::DOWNRIGHT: {
      direct = 8;
      break;
    }
    case DIRECTION::DOWN: {
      direct = 9;
      break;
    }
    case DIRECTION::DOWNLEFT: {
      direct = 8;
      flip = SDL_FLIP_HORIZONTAL;
      break;
    }
    case DIRECTION::LEFT: {
      direct = 7;
      flip = SDL_FLIP_HORIZONTAL;
      break;
    }
    case DIRECTION::UPLEFT: {
      direct = 6;
      flip = SDL_FLIP_HORIZONTAL;
      break;
    }
    }
    heroPositionComp->flip = flip;
    herotextureComp->path.back() = direct + '0';
  }
}

static void heroMove(entt::entity heroEnt) {
  auto &registry = World::registrys[World::level];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  auto heroPositionComp = &registry.get<PositionComp>(heroEnt);

  auto pathEnt = heroComp->pathEnts.front();
  auto pathPositionComp = &registry.get<PositionComp>(pathEnt);
  auto pathPoint = pathPositionComp->point;
  auto heroPoint = heroPositionComp->point + SDL_FPoint{32, 32};
  float speedRate = 8;
  float dx = pathPoint.x - heroPoint.x;
  float dy = pathPoint.y - heroPoint.y;
  float speedX = dx > 0 ? 32 / speedRate : dx < 0 ? -32 / speedRate : 0;
  float speedY = dy > 0 ? 32 / speedRate : dy < 0 ? -32 / speedRate : 0;

  heroPoint.x += speedX;
  heroPoint.y += speedY;

  auto objectComp = &registry.get<ObjectComp>(heroEnt);
  objectComp->x = heroPoint.x / 32 + 1;
  objectComp->y = heroPoint.y / 32;

  if ((int)heroPoint.x == (int)pathPoint.x &&
      (int)heroPoint.y == (int)pathPoint.y) {
    registry.destroy(pathEnt);
    World::needSort = true;

    heroComp->pathEnts.erase(heroComp->pathEnts.begin());

    auto terrainEnt =
        Global::terrains[World::level][objectComp->x - 1][objectComp->y].back();
    auto moveCost = TerrainCfg::moveCost.at(
        World::registrys[World::level].get<TerrainComp>(terrainEnt).index);
    heroComp->movement -= moveCost;
    // 判断是否触发事件
  }
  heroPositionComp->point = heroPoint - SDL_FPoint{32, 32};
  heroPositionComp->z = heroPositionComp->z -
                        ((heroPositionComp->z / 1000000) % 1000) * 1000000 +
                        objectComp->y * 1000000;
}

static bool heroStartMove(entt::entity heroEnt) {
  auto &registry = World::registrys[World::level];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  if (!heroComp->pathEnts.empty()) {
    auto pathEnt = heroComp->pathEnts.front();
    auto textureComp = &registry.get<TextureComp>(pathEnt);
    auto i = textureComp->path.rfind('/');
    auto indexStr = textureComp->path.substr(i + 1);
    auto index = std::stoi(indexStr);
    if (index >= 25) {
      return false;
    }
  }
  return true;
}

static void heroLeave(entt::entity heroEnt) {
  auto &registry = World::registrys[World::level];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  if (!heroComp->curEnt.has_value()) {
    return;
  }
  auto curEnt = heroComp->curEnt.value();
  if (auto townComp = registry.try_get<TownComp>(curEnt)) {
    townComp->heroEnt[1] = std::nullopt;
  }
  heroComp->curEnt = std::nullopt;
}

void HeroSys::heroTelePort(entt::entity heroEnt, uint8_t x, uint8_t y) {
  auto &registry = World::registrys[World::level];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  auto objectComp = &registry.get<ObjectComp>(heroEnt);
  objectComp->x = x + 1;
  objectComp->y = y;

  auto heropositionComp = &registry.get<PositionComp>(heroEnt);
  heropositionComp->point.x = x * 32 - 32;
  heropositionComp->point.y = y * 32 - 32;
  heropositionComp->z = heropositionComp->z -
                        ((heropositionComp->z / 1000000) % 1000) * 1000000 +
                        objectComp->y * 1000000;

  auto flagPositionComp = &registry.get<PositionComp>(heroComp->flagEnt);
  flagPositionComp->point = registry.get<PositionComp>(heroEnt).point;
  flagPositionComp->flip = registry.get<PositionComp>(heroEnt).flip;
  flagPositionComp->z = registry.get<PositionComp>(heroEnt).z;
  World::needSort = true;
}

static void heroAudio() {
  if (Global::heroMove) {
    if (!Global::audioData.contains("horse00.wav")) {
      Global::audioData["horse00.wav"] = 0;
    }
  } else {
    Global::audioData.erase("horse00.wav");
  }
}

bool HeroSys::run() {
  bool r = true;
  Global::heroMove = false;
  auto playerId = Global::playerId;
  if (Global::herosIndex[playerId] < 8) {
    auto [level, heroEnt] =
        Global::heros[playerId][Global::herosIndex[playerId]];
    auto &registry = World::registrys[level];
    if (!registry.valid(heroEnt)) {
      return r;
    }
    auto heroComp = &registry.get<HeroComp>(heroEnt);
    if (heroComp->move) {
      World::level = level;
      if (!heroStartMove(heroEnt)) {
        heroDirect(heroEnt, true);
        heroComp->move = false;
        return r;
      }
      Global::heroMove = true;
      heroDirect(heroEnt, false);
      if (!heroGoal(heroEnt)) {
        Global::heroMove = false;
        r = false;
      }
      if (heroComp->pathEnts.empty()) {
        heroDirect(heroEnt, true);
        heroComp->move = false;
        std::swap(heroComp->pathEntsBack, heroComp->pathEnts);
      } else {
        heroDirect(heroEnt, false);
        heroMove(heroEnt);
        heroLeave(heroEnt);
      }
      heroFlag(heroEnt);
      auto heroPositionComp = &registry.get<PositionComp>(heroEnt);
      CameraSys::focus(heroPositionComp->point.x + 48,
                       heroPositionComp->point.y + 48);
      World::needSort = true;
    }
    heroAudio();
  }
  return r;
}