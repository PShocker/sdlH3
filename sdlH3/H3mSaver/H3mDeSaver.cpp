#include "H3mDeSaver.h"
#include "Comp/HeroComp.h"
#include "Comp/MonsterComp.h"
#include "Comp/ResourceComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
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

static void clearPickEnt() {
}

void H3mDeSaver::afterEntLoad(Reader &reader) {
  clearDefaultEnt();
  auto size = reader.size();
  reader.seek(size - 4);
  auto cursor = reader.readU32();
  reader.seek(cursor);
}

void H3mDeSaver::loadMap(Reader &reader) {}