#pragma once

#include <cstdint>
#include <string>
struct NetWork {
  static void init(std::string src_addr_str, uint32_t src_port);
  static bool send(const uint8_t *data, size_t length, std::string pos_addr_str,
                   uint32_t pos_port);
};