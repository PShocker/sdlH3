#pragma once

#include "SDL3/SDL_iostream.h"
#include <cstdint>
#include <string>

struct Writer {
  SDL_IOStream *stream;
  void skip(uint32_t num);
  void fill(uint32_t num, uint8_t i);
  void close();
  uint32_t cursor();

  void writeU8(uint8_t i);
  void writeU16(uint16_t i);
  void writeU32(uint32_t i);

  void flush();

  void writeString(const std::string &str);

  Writer(std::string filePath);
  Writer() = default;
};