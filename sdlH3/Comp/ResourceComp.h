#pragma once

#include <cstdint>
#include <string>
#include <vector>
struct ResourceComp {
  uint8_t id;
  uint32_t count;

  std::string message;
  std::vector<std::pair<uint16_t, uint32_t>> guards;
};