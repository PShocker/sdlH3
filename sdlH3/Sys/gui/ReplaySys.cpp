#include "ReplaySys.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TextureComp.h"
#include "Global/Global.h"
#include "NetWork/NetServer.h"
#include "NetWork/protocol/Protocol.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/SpectateSys.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"

// 单个组件的复制辅助函数
template <typename ComponentType>
static void saveComp(entt::registry &src, entt::registry &dst,
                     entt::entity src_ent, entt::entity dst_ent) {
  if (src.all_of<ComponentType>(src_ent)) {
    const auto &comp = src.get<ComponentType>(src_ent);
    dst.emplace<ComponentType>(dst_ent, comp);
  }
}

void ReplaySys::saveRegistry() {
  for (auto i : {0, 1}) {
    auto &src_reg = World::registrys[i];
    auto &dst_reg = World::registrys[i + 2];
    dst_reg.clear();
    const auto &entity_pool = src_reg.storage<entt::entity>();
    for (entt::entity src_entity : entity_pool) {
      if (src_reg.valid(src_entity)) {
        auto dst_ent = dst_reg.create(src_entity);
        saveComp<PositionComp>(src_reg, dst_reg, src_entity, dst_ent);
        saveComp<TextureComp>(src_reg, dst_reg, src_entity, dst_ent);
        saveComp<ObjectComp>(src_reg, dst_reg, src_entity, dst_ent);
        saveComp<HeroComp>(src_reg, dst_reg, src_entity, dst_ent);
        saveComp<PlayerIdComp>(src_reg, dst_reg, src_entity, dst_ent);
      }
    }
  }
}

static void cosumeEvent() {
  if (Global::heroMove == false) {
    auto &v = Global::replayNetPack;
    if (!v.empty()) {
      auto buf = v.front().data();
      auto packet = GetNetPacket(buf);
      NetServer::dispatchPacket(0, packet);
      v.erase(v.begin());
    } else {
      return;
    }
  }
}

bool ReplaySys::run() {
  auto playerId = Global::playerId;
  Global::playerId = Global::playerIdSelf;
  AdvMapSys::drawHeroList();
  AdvMapSys::drawTownList();
  SpectateSys::drawRightTop();
  SpectateSys::drawRightButton();
  AdvMapSys::drawAgem();
  AdvMapSys::drawResBar(3, Global::viewPort.h - 25);
  Global::playerId = playerId;
  cosumeEvent();
  return true;
}