#pragma once
#include "Set/StructSet.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <vector>

struct HeroComp {
  entt::entity flagEnt;
  std::optional<entt::entity> goalEnt;
  std::optional<entt::entity> curEnt;
  std::vector<entt::entity> pathEnts;
  std::vector<entt::entity> pathEntsBack;
  int32_t movement;
  int32_t mana;
  uint8_t portrait;
  bool move;

  std::vector<uint16_t> artifactsInBackpack;
  std::vector<uint16_t> artifacts;

  uint8_t moveType;
  enum MOVE_TYPE : uint8_t {
    HORSE,
    BOAT,
    FLY,
    WATER_WALK,
  };

  uint8_t subId;
  std::array<uint8_t, 4> primSkills;
  std::vector<std::pair<uint8_t, uint8_t>> secSkills;
  std::vector<std::pair<uint16_t, uint32_t>> creatures;
  std::set<uint8_t> spells;
  bool sleep;

  uint64_t exp;
  uint8_t level;

  std::multiset<uint8_t> visited;
  std::set<entt::entity> visitedEnt;
  std::multimap<uint8_t, ArtifactBonus> artifactBonus;
  std::multimap<uint8_t, AdventureBonus> adventureBonus;
};