#pragma once
#include <cstdint>
#include <string>


enum class EMapFormat : uint8_t {
  INVALID = 0,
  //       HEX    DEC
  ROE = 0x0e,  // 14
  AB = 0x15,   // 21
  SOD = 0x1c,  // 28
  CHR = 0x1d,  // 29
  HOTA = 0x20, // 32
  WOG = 0x33,  // 51
  VCMI = 0x64
};

enum class EMapDifficulty : uint8_t {
  EASY = 0,
  NORMAL = 1,
  HARD = 2,
  EXPERT = 3,
  IMPOSSIBLE = 4
};

struct H3mHeader {
  EMapFormat version; /// The default value is EMapFormat::SOD.
  uint8_t height;     /// The default value is 72.
  uint8_t width;      /// The default value is 72.
  bool twoLevel;      /// The default value is true.
  std::string name;
  std::string description;
  EMapDifficulty difficulty;
};