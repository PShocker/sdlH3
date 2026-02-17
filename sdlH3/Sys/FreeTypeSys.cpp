#include "FreeTypeSys.h"
#include "Enum/Enum.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include <SDL3/SDL.h>
#include <cstdint>
#include <ft2build.h>
#include <map>
#include <ranges>
#include <string>
#include <tuple>

#include FT_FREETYPE_H

static FT_Library library = nullptr;
static FT_Face face = nullptr;
static uint8_t size;
static SDL_Color color;

static std::map<
    std::tuple<char16_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>,
    std::tuple<float, int, SDL_Texture *>>
    tCache;

bool FreeTypeSys::init(uint8_t i) {
  if (library) {
    FT_Done_FreeType(library);
    FT_Done_Face(face);
    for (auto [k, v] : tCache) {
      SDL_DestroyTexture(std::get<2>(v));
    }
    tCache.clear();
  }
  FT_Init_FreeType(&library);
  switch ((Enum::LANG)i) {
  case Enum::LANG::ENGLISH: {
    break;
  }
  case Enum::LANG::CHINESE: {
    FT_New_Face(library, "./Font/simsun.ttc", 0, &face);
    break;
  }
  default: {
    return false;
  }
  }
  FT_Select_Charmap(face, FT_ENCODING_UNICODE);
  return true;
}

void FreeTypeSys::setSize(uint8_t i) {
  size = i;
  FT_Set_Pixel_Sizes(face, 0, i);
}

void FreeTypeSys::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
}

static float drawChar(float x, float y, char16_t c) {
  std::tuple<char16_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t> t(
      c, size, color.r, color.g, color.b, color.a);
  SDL_Texture *texture = nullptr;
  auto lineHeight = face->size->metrics.height >> 6;
  float advance = 0;
  int bearingY = 0;
  if (tCache.contains(t)) {
    std::tie(advance, bearingY, texture) = tCache.at(t);
  } else {
    FT_Load_Char(face, c, FT_LOAD_RENDER | FT_LOAD_TARGET_MONO);
    auto *bitmap = &face->glyph->bitmap;
    advance = face->glyph->advance.x >> 6;
    bearingY = face->glyph->metrics.horiBearingY >> 6;
    auto cWidth = bitmap->width;
    auto cHeight = bitmap->rows;
    if (cWidth == 0 || cHeight == 0) {
      return advance;
    }
    // argb888
    uint8_t *buffer = (uint8_t *)SDL_calloc(1, cWidth * cHeight * 4);
    for (int y = 0; y < bitmap->rows; ++y) {
      for (int x = 0; x < bitmap->width; ++x) {
        auto value =
            bitmap->buffer[y * bitmap->pitch + (x >> 3)] & (0x80 >> (x & 7));
        if (value != 0) {
          buffer[(y * bitmap->width + x) * 4] = color.b;     // B
          buffer[(y * bitmap->width + x) * 4 + 1] = color.g; // G
          buffer[(y * bitmap->width + x) * 4 + 2] = color.r; // R
          buffer[(y * bitmap->width + x) * 4 + 3] = color.a; // A
        }
      }
    }
    texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STATIC, cWidth, cHeight);
    SDL_UpdateTexture(texture, NULL, buffer, cWidth * 4);
    SDL_free(buffer);
    tCache[t] = {advance, bearingY, texture};
  }
  // 纹理的顶部位置 = 基线位置 - bearingY
  auto posY = y + lineHeight - bearingY;

  auto posX = x + (advance - texture->w) / 2;
  SDL_FRect posRect{
      static_cast<float>((int)(posX)), static_cast<float>((int)(posY)),
      static_cast<float>(texture->w), static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  return advance;
}

static void drawLine(float x, float y, const std::u16string &str) {
  auto l = x;
  auto t = y;
  auto lineHeight = face->size->metrics.height >> 6;

  for (auto c : str) {
    l += drawChar(l, t, c);
  }
}

void FreeTypeSys::draw(float x, float y, const std::u16string &str) {
  auto lineHeight = face->size->metrics.height >> 6;
  auto next = std::views::split(str, u'\n') | std::views::common;
  for (const auto s : next) {
    auto ss = std::u16string{s.begin(), s.end()};
    drawLine(x, y, ss);
    y += lineHeight * 1.3;
  }
}

void FreeTypeSys::draw(float x, float y, const int num) {
  draw(x, y, str(num));
}

float FreeTypeSys::strWidth(const std::u16string &str) {
  float w = 0;
  for (auto c : str) {
    FT_Load_Char(face, c, FT_LOAD_DEFAULT);
    w += face->glyph->advance.x >> 6;
  }
  return w;
}

float FreeTypeSys::strWidth(int num) { return strWidth(str(num)); }

void FreeTypeSys::drawCenter(float x, float y, const std::u16string &str) {
  auto l = x;
  auto t = y;
  // 1. 计算文本尺寸
  auto lineHeight = face->size->metrics.height >> 6;
  auto next = std::views::split(str, u'\n') | std::views::common;
  for (const auto s : next) {
    auto ss = std::u16string{s.begin(), s.end()};
    auto w = strWidth(ss);
    auto posX = l - w / 2;
    drawLine(posX, y, ss);
    y += lineHeight * 1.3;
  }
}

void FreeTypeSys::drawCenter(float x, float y, const int num) {
  drawCenter(x, y, str(num));
}

void FreeTypeSys::drawLeft(float x, float y, const std::u16string &str) {
  auto l = x;
  auto t = y;
  // 1. 计算文本尺寸
  auto lineHeight = face->size->metrics.height >> 6;
  auto next = std::views::split(str, u'\n') | std::views::common;
  for (const auto s : next) {
    auto ss = std::u16string{s.begin(), s.end()};
    auto w = strWidth(ss);
    auto posX = l - w;
    drawLine(posX, y, ss);
    y += lineHeight * 1.3;
  }
}

void FreeTypeSys::drawLeft(float x, float y, const int num) {
  drawLeft(x, y, str(num));
}

std::u16string FreeTypeSys::str(int num) {
  auto str = std::to_string(abs(num));
  return std::u16string(str.begin(), str.end());
}

std::u16string FreeTypeSys::str(const char *u8Str) {
  size_t utf8Len = std::strlen(u8Str);
  // 转换（包含终止符确保完整性）
  char *utf16Data = SDL_iconv_string("UTF-16LE", "UTF-8", u8Str, utf8Len);
  // 计算实际UTF-16长度
  const char16_t *u16Ptr = reinterpret_cast<const char16_t *>(utf16Data);
  size_t u16Len = 0;
  // 查找UTF-16的空终止符
  while (u16Len < utf8Len && u16Ptr[u16Len] != 0) {
    u16Len++;
  }
  auto u16Str = std::u16string(u16Ptr, u16Len);
  SDL_free(utf16Data);
  return u16Str;
}