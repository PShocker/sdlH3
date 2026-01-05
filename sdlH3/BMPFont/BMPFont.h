#pragma once

#include "SDL3/SDL_render.h"
#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

struct BMPFont {
  struct EntryFNT {
    int32_t leftOffset;
    uint32_t width;
    uint32_t height;
    int32_t rightOffset;
    SDL_Texture *texture;
  };

  static void init();
  static void loadFont(const std::string &path);

  static inline std::unordered_map<std::string, std::array<EntryFNT, 256>>
      fontCache;
};