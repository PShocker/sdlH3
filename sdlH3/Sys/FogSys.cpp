#include "FogSys.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include "World/World.h"
#include "gui/HeroScrSys.h"
#include <bitset>
#include <cstdint>

std::vector<SDL_Point> FogSys::generateVerticalHexagon(int r) {
  std::vector<SDL_Point> points;
  for (int y = -r; y <= r; ++y) {
    for (int x = -r; x <= r; ++x) {
      if (x * x + y * y <= r * r + (r / 2) * (r / 2)) {
        points.push_back({x, y});
      }
    }
  }
  return points;
}

bool FogSys::run() {
  auto &registry = World::registrys[World::level];

  for (auto ent : registry.view<PlayerIdComp>()) {
    auto playerIdComp = &registry.get<PlayerIdComp>(ent);
    if (playerIdComp->id != Global::playerId) {
      continue;
    }
    auto objectComp = &registry.get<ObjectComp>(ent);
    int16_t accessX = objectComp->x + objectComp->accessTiles[0].first;
    int16_t accessY = objectComp->y + objectComp->accessTiles[0].second;

    auto r = 5;
    switch (objectComp->type) {
    case (uint8_t)ObjectType::HERO: {
      auto &hComp = registry.get<HeroComp>(ent);
      r += HeroScrSys::heroSight(hComp);
      break;
    }
    default: {
      break;
    }
    }

    for (const auto point : generateVerticalHexagon(r)) {
      int16_t rX =
          std::clamp((int)accessX + point.x, 0, (int)Global::mapSize - 1);
      int16_t rY =
          std::clamp((int)accessY + point.y, 0, (int)Global::mapSize - 1);
      Global::fogs[playerIdComp->id][World::level][rX + rY * Global::mapSize] =
          true;
    }
  }

  auto &fog = Global::fogs[Global::playerId][World::level];
  auto viewPort = Global::viewPort;

  auto width = viewPort.w / 32 + 2;
  auto height = viewPort.h / 32 + 2;

  int16_t x = viewPort.x / 32 - 1;
  int16_t y = viewPort.y / 32 - 1;

  for (uint16_t i = 0; i <= height; i++) {
    for (uint16_t j = 0; j <= width; j++) {
      int16_t tileX = std::clamp(x + j, 0, (int)Global::mapSize - 1);
      int16_t tileY = std::clamp(y + i, 0, (int)Global::mapSize - 1);
      if (fog[(tileX) + (tileY)*Global::mapSize]) {
        continue;
      }
      // 567
      // 3 4
      // 012
      const auto checkTile = [&](int dx, int dy) -> bool {
        if (tileX + dx < 0 || tileX + dx >= Global::mapSize || tileY + dy < 0 ||
            tileY + dy >= Global::mapSize) {
          return false;
        } else {
          return fog[(tileX + dx) + (tileY + dy) * Global::mapSize];
        }
      };

      std::bitset<8> d;
      // sides
      d[1] = checkTile(0, +1);
      d[3] = checkTile(-1, 0);
      d[4] = checkTile(+1, 0);
      d[6] = checkTile(0, -1);
      // corners - select visible image if either corner or adjacent sides are
      // visible
      d[0] = d[1] || d[3] || checkTile(-1, +1);
      d[2] = d[1] || d[4] || checkTile(+1, +1);
      d[5] = d[3] || d[6] || checkTile(-1, -1);
      d[7] = d[4] || d[6] || checkTile(+1, -1);
      static const int8_t visBitmaps[256] = {
          -1, 34, 4,  4,  22, 23, 4,  4,  36, 36, 38, 38, 47, 47, 38, 38, // 16
          3,  25, 12, 12, 3,  25, 12, 12, 9,  9,  6,  6,  9,  9,  6,  6,  // 32
          35, 39, 48, 48, 41, 43, 48, 48, 36, 36, 38, 38, 47, 47, 38, 38, // 48
          26, 49, 28, 28, 26, 49, 28, 28, 9,  9,  6,  6,  9,  9,  6,  6,  // 64
          0,  45, 29, 29, 24, 33, 29, 29, 37, 37, 7,  7,  50, 50, 7,  7,  // 80
          13, 27, 44, 44, 13, 27, 44, 44, 8,  8,  10, 10, 8,  8,  10, 10, // 96
          0,  45, 29, 29, 24, 33, 29, 29, 37, 37, 7,  7,  50, 50, 7,  7,  // 112
          13, 27, 44, 44, 13, 27, 44, 44, 8,  8,  10, 10, 8,  8,  10, 10, // 128
          15, 17, 30, 30, 16, 19, 30, 30, 46, 46, 40, 40, 32, 32, 40, 40, // 144
          2,  25, 12, 12, 2,  25, 12, 12, 9,  9,  6,  6,  9,  9,  6,  6,  // 160
          18, 42, 31, 31, 20, 21, 31, 31, 46, 46, 40, 40, 32, 32, 40, 40, // 176
          26, 49, 28, 28, 26, 49, 28, 28, 9,  9,  6,  6,  9,  9,  6,  6,  // 192
          0,  45, 29, 29, 24, 33, 29, 29, 37, 37, 7,  7,  50, 50, 7,  7,  // 208
          13, 27, 44, 44, 13, 27, 44, 44, 8,  8,  10, 10, 8,  8,  10, 10, // 224
          0,  45, 29, 29, 24, 33, 29, 29, 37, 37, 7,  7,  50, 50, 7,  7,  // 240
          13, 27, 44, 44, 13, 27, 44, 44, 8,  8,  10, 10, 8,  8,  10, 10  // 256
      };
      auto bitmapID = visBitmaps[d.to_ulong()];
      SDL_FRect posRect{(float)(int)tileX * 32 - (int)viewPort.x,
                        (float)(int)tileY * 32 - (int)viewPort.y, 32, 32};
      if (bitmapID < 0) {
        uint8_t pseudorandomNumber = ((tileX * 997) ^ (tileY * 1009)) / 101;
        uint8_t imageIndex = pseudorandomNumber % 4;
        auto texture = Global::defCache["TSHRC.def"][imageIndex];
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      } else {
        auto texture = Global::defCache["TSHRE.def"][bitmapID];
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      }
    }
  }
  return true;
}