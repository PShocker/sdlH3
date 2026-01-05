#include "Def.h"
#include "Pal/PlayerPal.h"
#include "Pcx/Pcx.h"
#include "Window/Window.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <string>

// 生物边框透明
// void ScalableImageParameters::setOverlayColor(const SDL_Palette *
// originalPalette, const ColorRGBA & color, bool includeShadow)

Def::Def(std::string filePath) : reader(filePath) {
  // 获取pcx文件信息
  reader.seek(12);
  uint32_t totalBlocks = reader.readU32();
  for (auto i = 0; i < 256; i++) {
    palette[i].r = reader.readU8();
    palette[i].g = reader.readU8();
    palette[i].b = reader.readU8();
    palette[i].a = SDL_ALPHA_OPAQUE;

    for (uint8_t i = 0; i < std::size(Pcx::sourcePalette); i++) {
      if (Pcx::sourcePalette[i].r == palette[i].r &&
          Pcx::sourcePalette[i].g == palette[i].g &&
          Pcx::sourcePalette[i].b == palette[i].b) {
        palette[i].r = Pcx::targetPalette[i].r;
        palette[i].g = Pcx::targetPalette[i].g;
        palette[i].b = Pcx::targetPalette[i].b;
        palette[i].a = Pcx::targetPalette[i].a;
      }
    }
  }
  for (auto i = 0; i < totalBlocks; i++) {
    size_t blockID = reader.readU32();
    auto totalEntries = reader.readU32();
    reader.skip(8);
    // 8 unknown bytes - skipping

    // 13 bytes for name of every frame in this block - not used, skipping
    reader.skip(13 * (int)totalEntries);

    for (auto j = 0; j < totalEntries; j++) {
      size_t currOffset = reader.readU32();
      offset[blockID].push_back(currOffset);
    }
  }
}

void Def::setColor(uint8_t i) {
  for (auto &pal : palette) {
    if (pal.r == 255 && pal.g == 255 && pal.b == 0) {
      pal = PlayerPal::colors[i];
    }
  }
}

SDL_Texture *Def::loadFrame(uint8_t id, uint8_t frame) {
  auto frameDef = offset[id][frame];
  reader.seek(frameDef);
  auto size = reader.readU32();
  auto format = reader.readU32();
  auto fullWidth = reader.readU32();
  auto fullHeight = reader.readU32();
  auto width = reader.readU32();
  auto height = reader.readU32();
  auto leftMargin = reader.readU32();
  auto topMargin = reader.readU32();

  const auto BaseOffset = reader.cursor() - frameDef;

  uint8_t *pixels = (uint8_t *)SDL_calloc(1, fullWidth * fullHeight);
  switch (format) {
  case 0: {
    // pixel data is not compressed, copy data to surface
    for (uint32_t i = 0; i < height; i++) {
      // 根据索引从调色板获取颜色
      for (int j = 0; j < width; j++) {
        auto index = reader.readU8();
        // 填充到像素缓冲区
        size_t pixelOffset = ((i + topMargin) * fullWidth + j + leftMargin);
        pixels[pixelOffset] = index;
      }
    }
    break;
  }
  case 1: {
    // for each line we have offset of pixel data
    auto currentOffset = BaseOffset;
    for (uint32_t i = 0; i < height; i++) {
      reader.seek(frameDef + BaseOffset + i * 4);
      currentOffset = BaseOffset + reader.readU32();
      reader.seek(frameDef + currentOffset);
      uint32_t TotalRowLength = 0;
      while (TotalRowLength < width) {
        uint8_t segmentType = reader.readU8();
        uint32_t length = reader.readU8() + 1;
        // 标准的RLE格式
        if (segmentType == 0xFF) // Raw data
        {
          // 根据索引从调色板获取颜色
          for (int j = 0; j < length; j++) {
            auto index = reader.readU8();
            // 填充到像素缓冲区
            size_t pixelOffset =
                ((i + topMargin) * fullWidth + TotalRowLength + leftMargin + j);
            pixels[pixelOffset] = index;
          }
        } else // RLE
        {
          auto index = segmentType;
          for (int j = 0; j < length; j++) {
            // 填充到像素缓冲区
            size_t pixelOffset =
                ((i + topMargin) * fullWidth + TotalRowLength + leftMargin + j);
            pixels[pixelOffset] = index;
          }
        }
        TotalRowLength += length;
      }
    }
    break;
  }
  case 2: {
    reader.seek(frameDef + BaseOffset);
    auto currentOffset = BaseOffset + reader.readU16();
    reader.seek(frameDef + currentOffset);
    for (uint32_t i = 0; i < height; i++) {
      uint32_t TotalRowLength = 0;
      while (TotalRowLength < width) {
        uint8_t segment = reader.readU8();
        uint8_t code = segment / 32;
        uint8_t length = (segment & 31) + 1;

        if (code == 7) // Raw data
        {
          // 根据索引从调色板获取颜色
          for (int j = 0; j < length; j++) {
            auto index = reader.readU8();
            // 填充到像素缓冲区
            size_t pixelOffset =
                ((i + topMargin) * fullWidth + TotalRowLength + leftMargin + j);
            pixels[pixelOffset] = index;
          }
        } else // RLE
        {
          auto index = code;
          // 根据索引从调色板获取颜色
          for (int j = 0; j < length; j++) {
            // 填充到像素缓冲区
            size_t pixelOffset =
                ((i + topMargin) * fullWidth + TotalRowLength + leftMargin + j);
            pixels[pixelOffset] = index;
          }
        }
        TotalRowLength += length;
      }
    }
    break;
  }
  case 3: {
    for (uint32_t i = 0; i < height; i++) {
      reader.seek(frameDef + BaseOffset + i * 2 * (width / 32));
      auto currentOffset = BaseOffset + reader.readU16();
      reader.seek(frameDef + currentOffset);
      uint32_t TotalRowLength = 0;

      while (TotalRowLength < width) {
        uint8_t segment = reader.readU8();
        uint8_t code = segment / 32;
        uint8_t length = (segment & 31) + 1;

        if (code == 7) // Raw data
        {
          // 根据索引从调色板获取颜色
          for (int j = 0; j < length; j++) {
            auto index = reader.readU8();
            // 填充到像素缓冲区
            size_t pixelOffset =
                ((i + topMargin) * fullWidth + TotalRowLength + leftMargin + j);
            pixels[pixelOffset] = index;
          }
        } else // RLE
        {
          auto index = code;
          for (int j = 0; j < length; j++) {
            // 填充到像素缓冲区
            size_t pixelOffset =
                ((i + topMargin) * fullWidth + TotalRowLength + leftMargin + j);
            pixels[pixelOffset] = index;
          }
        }
        TotalRowLength += length;
      }
    }
    break;
  }
  default:
    break;
  }
  // 创建texture
  auto texture =
      SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_INDEX8,
                        SDL_TEXTUREACCESS_STATIC, fullWidth, fullHeight);
  SDL_UpdateTexture(texture, NULL, pixels, fullWidth);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  auto pal = SDL_CreatePalette(256);
  SDL_SetPaletteColors(pal, palette, 0, 256);
  SDL_SetTexturePalette(texture, pal);
  SDL_DestroyPalette(pal);
  SDL_free(pixels);
  return texture;
}

std::vector<SDL_Texture *> Def::loadGroup(uint8_t id) {
  std::vector<SDL_Texture *> r;
  for (uint8_t i = 0; i < offset[id].size(); i++) {
    r.push_back(loadFrame(id, i));
  }
  return r;
}

std::vector<SDL_Texture *>
Def::loadPalette(std::vector<std::pair<uint8_t, uint8_t>> pair, uint8_t frame) {
  std::vector<SDL_Texture *> r;
  uint16_t lcm = 1;
  for (auto [first, second] : pair) {
    lcm = std::lcm(second, lcm);
  }
  for (uint16_t i = 0; i < lcm; i++) {
    r.push_back(loadFrame(0, frame));
    for (auto [first, second] : pair) {
      // 1. 保存末尾颜色
      SDL_Color temp = palette[first + second - 1];
      // 2. 向后移动颜色（start+length-2 → start+length-1, ..., start →
      for (int j = second - 1; j > 0; j--) {
        palette[first + j] = palette[first + j - 1];
      }
      // 3. 将末尾颜色放到起始位置
      palette[first] = temp;
    }
  }
  return r;
}
