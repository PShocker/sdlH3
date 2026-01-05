#include "Reader.h"
#include "SDL3/SDL_iostream.h"
#include <cstdint>
#include <string>

uint32_t Reader::cursor() { return SDL_TellIO(stream); }

uint32_t Reader::size() { return SDL_GetIOSize(stream); }

void Reader::close() { SDL_CloseIO(stream); }

void Reader::skip(uint32_t num) { SDL_SeekIO(stream, num, SDL_IO_SEEK_CUR); }

void Reader::seek(uint32_t num) { SDL_SeekIO(stream, num, SDL_IO_SEEK_SET); }

uint8_t Reader::readU8() {
  uint8_t r;
  SDL_ReadU8(stream, &r);
  return r;
}

uint16_t Reader::readU16() {
  uint16_t r;
  SDL_ReadU16LE(stream, &r);
  return r;
}

uint32_t Reader::readU32() {
  uint32_t r;
  SDL_ReadU32LE(stream, &r);
  return r;
}

std::string Reader::readString(uint32_t num) {
  auto r = cursor() + num;
  std::string result{};
  for (int i = 0; i < num; ++i) {
    auto c = readU8();
    if (c != 0) {
      result.push_back(c);
    } else {
      break;
    }
  }
  seek(r);
  return result;
}

std::string Reader::readString() {
  auto length = readU32();
  return readString(length);
}

Reader::Reader(std::string filePath) {
  stream = SDL_IOFromFile(filePath.c_str(), "r");
}

Reader::Reader(void *buffer, uint32_t size) {
  stream = SDL_IOFromDynamicMem();
  SDL_WriteIO(stream, buffer, size);
  SDL_SeekIO(stream, 0, SDL_IO_SEEK_SET);
}