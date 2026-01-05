#pragma once
#include <cstdint>
#include <optional>
struct ScholarComp {
  uint8_t id;
  std::optional<uint8_t> primId;
  std::optional<uint8_t> secId;
  std::optional<uint8_t> splId;
};