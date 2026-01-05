#include "BMPFont.h"
#include "Reader/Reader.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "Window/Window.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>

void BMPFont::loadFont(const std::string &path) {
  Reader reader("./Data/H3bitmap.lod/" + path);
  reader.seek(5);
  auto height = reader.readU32();

  constexpr size_t symbolsInFile = 0x100;
  constexpr size_t baseIndex = 32;
  constexpr size_t offsetIndex = baseIndex + symbolsInFile * 12;
  constexpr size_t dataIndex = offsetIndex + symbolsInFile * 4;

  for (uint32_t charIndex = 0; charIndex < symbolsInFile; ++charIndex) {
    EntryFNT symbol;

    reader.seek(baseIndex + charIndex * 12);

    symbol.leftOffset = reader.readU32();
    symbol.width = reader.readU32();
    symbol.rightOffset = reader.readU32();
    symbol.height = height;

    if (symbol.width == 0) {
      continue;
    }

    reader.seek(offsetIndex + charIndex * 4);
    uint32_t pixelDataOffset = reader.readU32();
    uint32_t pixelsCount = height * symbol.width;

    auto pixels = (uint8_t *)SDL_malloc(pixelsCount);

    reader.seek(dataIndex + pixelDataOffset);
    SDL_ReadIO(reader.stream, pixels, pixelsCount);

    // 创建texture
    SDL_Palette *pal = SDL_CreatePalette(256);

    pal->colors[0] = {0, 0, 0, 0};
    pal->colors[1] = {0, 0, 0, SDL_ALPHA_OPAQUE}; // black shadow

    auto texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_INDEX8,
                                     SDL_TEXTUREACCESS_STATIC, symbol.width,
                                     symbol.height);
    SDL_UpdateTexture(texture, NULL, pixels, symbol.width);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTexturePalette(texture, pal);
    SDL_DestroyPalette(pal);

    symbol.texture = texture;
    fontCache[path][charIndex] = symbol;
  }
}

// VCMI CBitmapFont::CBitmapFont(const std::string & filename):
void BMPFont::init() {
  const std::vector<std::string> filePaths = {"bigfont.fnt", "verd10b.fnt"};
  for (const auto &path : filePaths) {
    loadFont(path);
  }
  return;
}