#include "NetEvent.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TextureComp.h"
#include "Ent/Ent.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "H3mSaver/H3mDeSaver.h"
#include "NetWork.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/CameraSys.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <utility>

static std::pair<uint8_t, entt::entity> findHeroEnt(uint8_t por) {
  for (uint8_t i : {0, 1}) {
    auto &registry = World::registrys[i];
    for (auto ent : registry.view<HeroComp>()) {
      auto hComp = &registry.get<HeroComp>(ent);
      if (hComp->portrait == por) {
        return {i, ent};
      }
    }
  }
  return {0, entt::null};
}

// networkEvent
void NetEvent::inScene(uint32_t scene, uint32_t seed, uint64_t hId,
                       uint64_t cId) {
  std::srand(seed);
  Global::gen.seed(seed);

  if (Global::mapPath.ends_with(".h3s")) {
    Global::mapData = H3mData(Global::mapPath, false);
  } else {
    Global::mapData = H3mData(Global::mapPath);
  }
  Global::mapData.init();
  Global::mapW = Global::mapData.header.width * 32;
  Global::mapH = Global::mapData.header.height * 32;
  Global::mapSize = Global::mapData.header.width;

  Ent::load(Global::mapData);
  if (Global::mapPath.ends_with(".h3s")) {
    H3mDeSaver::afterEntLoad(Global::mapData.reader);
  }
  Global::startGame();
  if (cId == hId) {
    World::enterAdvScrn();
  } else {
    World::enterSpectate();
  }

  NetWork::cId = cId;
  NetWork::sceneHost[scene] = hId;

  return;
}

void NetEvent::heroMove(uint8_t por, uint8_t level, uint8_t x, uint8_t y) {
  auto [i, heroEnt] = findHeroEnt(por);
  auto &registry = World::registrys[i];
  auto hComp = &registry.get<HeroComp>(heroEnt);
  std::vector<SDL_Point> path;
  auto paths = hComp->pathEnts;
  path = {{0, 0}, {x, y}};
  Ent::loadPath(path, heroEnt, 5, level);
  paths.append_range(hComp->pathEnts);
  hComp->pathEnts = paths;
  World::level = i;
  hComp->move = true;
  Global::heroMove = true;
  AdvMapSys::heroFocus(heroEnt, i);
  return;
}

void NetEvent::heroGoal(uint8_t por, uint8_t type, uint8_t level, uint8_t x,
                        uint8_t y) {
  auto [i, heroEnt] = findHeroEnt(por);
  auto registry = &World::registrys[i];
  auto hComp = &registry->get<HeroComp>(heroEnt);
  if (type == ObjectType::NOTHING) {
    heroMove(por, level, x, y);
    auto goalEnt = Global::terrains[World::level][x][y].back();
    hComp->goalEnt.push_back(goalEnt);
    return;
  }
  auto r = &World::registrys[level];
  for (auto oEnt : r->view<ObjectComp>()) {
    auto oComp = &r->get<ObjectComp>(oEnt);
    if (oComp->type == type && oComp->x == x && oComp->y == y) {
      auto ox = oComp->x;
      auto oy = oComp->y;
      if (oComp->type != ObjectType::MONSTER) {
        ox = ox + oComp->accessTiles[0].first;
        oy = oy + oComp->accessTiles[0].second;
        heroMove(por, level, ox, oy);
      }
      hComp->goalEnt.push_back(oEnt);
      hComp->visitedIndex.insert(oComp->index);
      return;
    }
  }
  return;
}

void NetEvent::heroRecruit(uint8_t por, uint8_t level, uint8_t x, uint8_t y) {
  auto [i, heroEnt] = findHeroEnt(por);
  auto &registry = World::registrys[i];
}

void NetEvent::heroDismiss(uint8_t por) {
  auto [i, heroEnt] = findHeroEnt(por);
  World::level = i;
  AdvMapSys::heroFocus(heroEnt, i);
  auto &registry = World::registrys[i];

  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.push_back([]() {
    auto [level, heroEnt] = Global::heroScnPair;
    for (uint8_t i = 0; i < Global::heros[Global::playerId].size(); i++) {
      if (Global::heros[Global::playerId][i].second == heroEnt &&
          Global::heros[Global::playerId][i].first == level) {
        Global::heros[Global::playerId].erase(
            Global::heros[Global::playerId].begin() + i);
        if (Global::herosIndex[Global::playerId] == i) {
          Global::herosIndex[Global::playerId] = 0xff;
        }
        break;
      }
    }
    auto heroComp = &World::registrys[level].get<HeroComp>(heroEnt);
    if (heroComp->curEnt.has_value()) {
      auto curEnt = heroComp->curEnt.value();
      if (auto townComp =
              World::registrys[World::level].try_get<TownComp>(curEnt)) {
        for (auto &ent : townComp->heroEnt) {
          if (ent == heroEnt) { // std::optional 支持直接比较
            ent = std::nullopt;
            break;
          }
        }
      }
    }
    for (auto pathEnt : heroComp->pathEnts) {
      World::registrys[World::level].destroy(pathEnt);
    }
    World::registrys[World::level].destroy(heroComp->flagEnt);
    World::registrys[World::level].destroy(heroEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
}

void NetEvent::heroTeleport(uint8_t por, uint8_t level, uint8_t x, uint8_t y) {
  auto [i, heroEnt] = findHeroEnt(por);
  auto registry = &World::registrys[i];
  AdvMapSys::heroFocus(heroEnt, i);
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystems.pop_back();
  World::iterateSystems.push_back([=]() {
    auto &textureComp = registry->get<TextureComp>(heroEnt);
    auto &heroComp = registry->get<HeroComp>(heroEnt);
    for (auto pathEnt : heroComp.pathEnts) {
      World::registrys[i].destroy(pathEnt);
    }
    auto &positionComp = registry->get<PositionComp>(heroEnt);
    auto &heros = Global::heros[Global::playerId];
    auto &playerIdComp = registry->get<PlayerIdComp>(heroEnt);
    auto newHeroEnt =
        Ent::loadHero(heroComp, playerIdComp.id, x, y, level,
                      textureComp.path.back() - '0', positionComp.flip);
    heros[Global::herosIndex[Global::playerId]] = {level, newHeroEnt};

    registry->destroy(heroComp.flagEnt);
    registry->destroy(heroEnt);
    auto registryNew = &World::registrys[level];

    CameraSys::focus(registryNew->get<PositionComp>(newHeroEnt).point.x + 48,
                     registryNew->get<PositionComp>(newHeroEnt).point.y + 48);

    World::needSort = true;
    World::level = level;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
  return;
}

void NetEvent::endTurn(uint64_t cId) {}