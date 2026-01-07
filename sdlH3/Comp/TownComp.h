#pragma once

#include "entt/entity/fwd.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <set>
#include <unordered_map>
#include <vector>
struct TownComp {
  uint8_t id;
  uint8_t nameIndex;
  std::unordered_map<uint8_t, entt::entity> buildings;
  std::vector<std::pair<uint16_t, uint32_t>> garCreatures;
  std::vector<std::pair<uint16_t, uint32_t>> remainCreatures;
  std::vector<std::pair<uint16_t, uint32_t>> incCreatures;
  bool hasBuild = false;
  std::array<std::optional<entt::entity>, 2> heroEnt;

  std::set<uint8_t> forbidBuildings;
  std::set<uint8_t> obligatorySpells;
  std::set<uint8_t> possibleSpells;
};