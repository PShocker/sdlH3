#pragma once

#include "Reader/Reader.h"
#include "SDL3/SDL.h"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

struct Def {
  Reader reader;
  SDL_Color palette[256];
  std::map<size_t, std::vector<size_t>> offset;

  Def(std::string filePath);

  void setColor(uint8_t i);
  SDL_Texture *loadFrame(uint8_t id, uint8_t frame);
  std::vector<SDL_Texture *>
  loadPalette(std::vector<std::pair<uint8_t, uint8_t>> pair, uint8_t frame);
  std::vector<SDL_Texture *> loadGroup(uint8_t id);
};