#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

struct BoatComp {
  static inline const std::unordered_map<std::string, std::string> boatMap = {
      {"AVXboat0.def", "AB01_.def"},
      {"AVXboat1.def", "AB02_.def"},
      {"AVXboat2.def", "AB03_.def"},
  };
  static inline const std::unordered_map<std::string, std::string> boatFlagMap =
      {{"AB01_.def", "ABF01"}, {"AB02_.def", "ABF02"}, {"AB03_.def", "ABF03"}};
  static inline const std::unordered_map<uint8_t, std::string>
      boatPlayerFlagMap = {{0, "L"}};
  std::string path;
};