#pragma once

#include "Reader/Reader.h"
#include "SDL3/SDL_render.h"
#include <cstdint>
#include <string>
#include <vector>
struct Pcx {
  // First 8 colors in def palette used for transparency
  static const inline SDL_Color sourcePalette[8] = {
      {0, 255, 255, SDL_ALPHA_OPAQUE},   {255, 150, 255, SDL_ALPHA_OPAQUE},
      {255, 100, 255, SDL_ALPHA_OPAQUE}, {255, 50, 255, SDL_ALPHA_OPAQUE},
      {255, 0, 255, SDL_ALPHA_OPAQUE},   {255, 255, 0, SDL_ALPHA_OPAQUE},
      {180, 0, 255, SDL_ALPHA_OPAQUE},   {0, 255, 0, SDL_ALPHA_OPAQUE}};

  static const inline SDL_Color targetPalette[8] = {
      {0, 0, 0, 0},   {0, 0, 0, 64},  {0, 0, 0, 64},
      {0, 0, 0, 128}, {0, 0, 0, 128}, {255, 255, 0, SDL_ALPHA_OPAQUE},
      {0, 0, 0, 128}, {0, 0, 0, 64}};

  enum Epcxformat { PCX8B, PCX24B };
  Epcxformat format;
  uint32_t size;
  uint32_t width;
  uint32_t height;

  Reader reader;
  SDL_Color palette[256];

  Pcx(std::string filePath);

  void loadPixels(uint8_t *pixels);
  SDL_Texture *load();
  std::vector<bool> loadArea();
};