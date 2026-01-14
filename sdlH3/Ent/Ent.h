#pragma once
#include "Comp/HeroComp.h"
#include "H3mLoader/H3mData.h"
#include "H3mLoader/H3mObject.h"
#include "SDL3/SDL_rect.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <string>

struct Ent {
  static entt::entity loadHero(HeroComp &heroComp, uint8_t playerId, uint8_t x,
                               uint8_t y, uint8_t level, uint8_t direct,
                               uint8_t flip);
  static entt::entity loadBoat(const std::string &path, uint8_t x, uint8_t y,
                               uint8_t level, uint8_t direct, uint8_t flip);
  static void loadPath(std::vector<SDL_Point> &path, entt::entity heroEnt,
                       uint16_t indexCost);
  static void load(H3mData &data);
  static entt::entity loadBuild(uint8_t level, entt::entity townEnt,
                                uint8_t buildId);
  static int64_t loadZorder(int32_t i, H3mObject &object);
};