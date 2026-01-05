#include "Pcx.h"
#include "Window/Window.h"
#include <SDL3/SDL.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <vector>

Pcx::Pcx(std::string filePath) : reader(filePath) {
  size = reader.readU32();
  width = reader.readU32();
  height = reader.readU32();

  // 判断pcx格式类型
  if (size == width * height * 3) {
    format = PCX24B;
  } else {
    format = PCX8B;
    // 获取调色板
    reader.seek(reader.size() - 256 * 3);
    for (int i = 0; i < 256; i++) {
      palette[i].r = reader.readU8();
      palette[i].g = reader.readU8();
      palette[i].b = reader.readU8();
      palette[i].a = SDL_ALPHA_OPAQUE;

      for (uint8_t i = 0; i < std::size(sourcePalette); i++) {
        if (sourcePalette[i].r == palette[i].r &&
            sourcePalette[i].g == palette[i].g &&
            sourcePalette[i].b == palette[i].b) {
          palette[i].r = targetPalette[i].r;
          palette[i].g = targetPalette[i].g;
          palette[i].b = targetPalette[i].b;
          palette[i].a = targetPalette[i].a;
        }
      }
    }
  }
}

void Pcx::loadPixels(uint8_t *pixels) {
  if (format == PCX8B) {
    // 纹理数据从0xC开始
    reader.seek(0xC);
    SDL_ReadIO(reader.stream, pixels, height * width);

  } else {
    SDL_ReadIO(reader.stream, pixels, height * width * 3);
  }
}

SDL_Texture *Pcx::load() {
  SDL_Texture *texture;
  uint8_t *pixels = nullptr;
  if (format == PCX8B) {
    pixels = (uint8_t *)SDL_malloc(height * width);
    loadPixels(pixels);
    texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_INDEX8,
                                SDL_TEXTUREACCESS_STATIC, width, height);
    SDL_UpdateTexture(texture, NULL, pixels, width);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    auto pal = SDL_CreatePalette(256);
    SDL_SetPaletteColors(pal, palette, 0, 256);
    SDL_SetTexturePalette(texture, pal);
    SDL_DestroyPalette(pal);
  } else {
    // 直接存储的是BGR24格式数据,直接更新
    pixels = (uint8_t *)SDL_malloc(height * width * 3);
    loadPixels(pixels);
    texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_BGR24,
                                SDL_TEXTUREACCESS_STATIC, width, height);
    SDL_UpdateTexture(texture, NULL, pixels, width * 3);
  }
  SDL_free(pixels);
  return texture;
}

std::vector<bool> Pcx::loadArea() {
  std::vector<bool> r(height * width, false);
  uint8_t *pixels = nullptr;
  if (format == PCX8B) {
    pixels = (uint8_t *)SDL_malloc(height * width);
    loadPixels(pixels);
    for (int i = 0; i < (int)height * width; i++) {
      auto index = pixels[i]; // A
      if (palette[index].a != 0) {
        r[i] = true;
      }
    }
  }
  SDL_free(pixels);
  return r;
}