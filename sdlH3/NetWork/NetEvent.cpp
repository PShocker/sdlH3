#include "NetEvent.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TextureComp.h"
#include "Ent/Ent.h"
#include "Global/Global.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/CameraSys.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <utility>

static std::pair<uint8_t, entt::entity> FindHeroEnt(uint8_t por) {
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
void NetEvent::InScene(uint32_t scene) {
  World::enterAdvScrn();
  return;
}

void NetEvent::HeroMove(uint8_t por, uint8_t level, uint8_t x, uint8_t y) {
  auto [i, heroEnt] = FindHeroEnt(por);
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

void NetEvent::HeroGoal(uint8_t por, uint8_t type, uint8_t level, uint8_t x,
                        uint8_t y) {
  auto [i, heroEnt] = FindHeroEnt(por);
  auto registry = &World::registrys[i];
  auto hComp = &registry->get<HeroComp>(heroEnt);
  auto r = &World::registrys[level];
  for (auto oEnt : r->view<ObjectComp>()) {
    auto oComp = &r->get<ObjectComp>(heroEnt);
    if (oComp->type == type && oComp->x == x && oComp->y == y) {
      hComp->goalEnt.push_back(oEnt);
      return;
    }
  }
  return;
}

void NetEvent::HeroTeleport(uint8_t por, uint8_t level, uint8_t x, uint8_t y) {
  auto [i, heroEnt] = FindHeroEnt(por);
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