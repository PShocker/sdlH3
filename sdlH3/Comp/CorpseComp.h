#pragma once

#include <cstdint>
#include <optional>
struct CorpseComp {
  uint8_t id;
  std::optional<uint8_t> artifacts;
};