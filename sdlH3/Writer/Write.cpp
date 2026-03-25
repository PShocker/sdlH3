#include "Writer.h"

void Writer::writeU8(uint8_t i) { SDL_WriteU8(stream, i); }

void Writer::writeU16(uint16_t i) { SDL_WriteU16LE(stream, i); }

void Writer::writeU32(uint32_t i) { SDL_WriteU32LE(stream, i); }

void Writer::flush() { SDL_FlushIO(stream); }

void Writer::fill(uint32_t num, uint8_t i) {
  for (int i = 0; i < num; ++i) {
    writeU8(i);
  }
}

void Writer::writeString(const std::string &str) {
  auto length = str.size();
  writeU32(length);
  for (int i = 0; i < length; ++i) {
    writeU8(str[i]);
  }
}

Writer::Writer(std::string filePath) {
  stream = SDL_IOFromFile(filePath.c_str(), "wb");
}