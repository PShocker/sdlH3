#pragma once

#include "entt/entity/fwd.hpp"
#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct TownDwe {
  uint8_t bId;
  entt::entity ent;
};

struct TownDweInc {
  uint8_t id;
  uint8_t subId;
  uint8_t num;
};

struct TownSys {
  static void
  drawCreature(uint8_t i, std::vector<std::pair<uint16_t, uint32_t>> *creature);
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool rightMouseDown(float x, float y);
  static bool keyUp(uint16_t key);

  static void heroVisit();
  static uint8_t visitBuild(uint8_t bId);
  static std::array<uint16_t, 7> townInCome(uint8_t lvl, entt::entity townEnt);
  static std::u16string townName(uint8_t lvl, entt::entity townEnt);
  static std::vector<TownDwe> townDweBuilds(uint8_t lvl, entt::entity townEnt);
  static std::vector<TownDweInc> townDweInc(uint8_t lvl, entt::entity townEnt,
                                            uint8_t bId);
  static uint32_t townDweNum(uint8_t lvl, entt::entity townEnt, uint8_t bId);
  static uint8_t fortLevel(uint8_t lvl, entt::entity townEnt);
};