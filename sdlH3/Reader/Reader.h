#pragma once
#include "SDL3/SDL_iostream.h"
#include <cstdint>
#include <string>

struct Reader {
  SDL_IOStream *stream;
  void skip(uint32_t num);
  void seek(uint32_t num);
  void close();
  uint32_t size();
  uint32_t cursor();

  uint8_t readU8();
  uint16_t readU16();
  uint32_t readU32();

  std::string readString(uint32_t num);
  std::string readString();

  Reader(std::string filePath);
  Reader(void *buffer, uint32_t size);
};