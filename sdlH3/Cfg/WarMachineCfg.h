#pragma once

#include <cstdint>
#include <string>
#include <vector>
struct WarMachineCfg {
  const static inline std::vector<std::string> warMachineVector = {
      "ballista", "firstAidTent", "ammoCart"};

  const static inline std::vector<std::string> warMachineGraphics = {
      {"SMBAL.DEF", "SMTENT.DEF", "SMCART.DEF"},
  };
  const static inline std::vector<bool> machinedoubleWide = {true, true, false};

  const static inline std::vector<std::vector<uint32_t>> machineCost = {
      {{0, 0, 0, 0, 0, 0, 60}},
      {{0, 0, 0, 0, 0, 0, 75}},
      {{0, 0, 0, 0, 0, 0, 1000}}};
};