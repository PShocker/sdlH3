#pragma once
#include <cstdint>
#include <vector>
struct WarMachineFacComp {
  uint32_t id;
  std::vector<std::pair<uint16_t, uint32_t>> warMachines;
};