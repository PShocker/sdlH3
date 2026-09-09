#include "Reader.h"
#include "SDL3/SDL_iostream.h"
#include <cstdint>
#include <string>

uint32_t Reader::pos() { return SDL_TellIO(stream); }

uint32_t Reader::size() { return SDL_GetIOSize(stream); }

void Reader::close() { SDL_CloseIO(stream); }

void Reader::skip(uint32_t num) { SDL_SeekIO(stream, num, SDL_IO_SEEK_CUR); }

void Reader::seek(uint32_t num) { SDL_SeekIO(stream, num, SDL_IO_SEEK_SET); }

uint8_t Reader::read_u8() {
  uint8_t r;
  SDL_ReadU8(stream, &r);
  return r;
}

uint16_t Reader::read_u16() {
  uint16_t r;
  SDL_ReadU16LE(stream, &r);
  return r;
}

uint32_t Reader::read_u32() {
  uint32_t r;
  SDL_ReadU32LE(stream, &r);
  return r;
}

uint64_t Reader::read_u64() {
  uint64_t r;
  SDL_ReadU64LE(stream, &r);
  return r;
}

std::string Reader::read_str(uint32_t num) {
  auto r = pos() + num;
  std::string result{};
  for (int i = 0; i < num; ++i) {
    auto c = read_u8();
    if (c != 0) {
      result.push_back(c);
    } else {
      break;
    }
  }
  seek(r);
  return result;
}

std::string Reader::read_str() {
  auto length = read_u32();
  return read_str(length);
}

Reader::Reader(std::string filePath) {
  stream = SDL_IOFromFile(filePath.c_str(), "r");
}

Reader::Reader(void *buffer, uint32_t size) {
  stream = SDL_IOFromDynamicMem();
  SDL_WriteIO(stream, buffer, size);
  SDL_SeekIO(stream, 0, SDL_IO_SEEK_SET);
}