#pragma once

#include "H3mLoader/H3mData.h"
#include "SDL3/SDL_render.h"
#include <cstdint>
#include <string>
struct TextureComp {
  std::string path;
  uint8_t index = 0;
  uint8_t time = 0;
};
