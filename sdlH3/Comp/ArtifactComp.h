#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct ArtifactComp {
  uint8_t id;

  std::string message;
  std::vector<std::pair<uint16_t, uint32_t>> guards;
};