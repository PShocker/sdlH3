#include "ReplaySys.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TextureComp.h"
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

bool ReplaySys::run() { return true; }