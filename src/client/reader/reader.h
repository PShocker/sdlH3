#pragma once
#include "SDL3/SDL_iostream.h"
#include <cstdint>
#include <string>

class Reader {
private:
  SDL_IOStream *stream;

public:
  void skip(uint32_t num);
  void seek(uint32_t num);
  void close();
  uint32_t size();
  uint32_t pos();

  uint8_t read_u8();
  uint16_t read_u16();
  uint32_t read_u32();
  uint64_t read_u64();

  std::string read_str(uint32_t num);
  std::string read_str();

  Reader(std::string filePath);
  Reader(void *buffer, uint32_t size);
  Reader() = default;
};