#include "AdvPopSys.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/TownCfg.h"
#include "Comp/ArtifactComp.h"
#include "Comp/HeroComp.h"
#include "Comp/MonsterComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/ResourceComp.h"
#include "Comp/TextureComp.h"
#include "Comp/TownComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include <cstdint>
#include <string>

void AdvPopSys::drawBackGround(float x, float y, float w, float h,
                               uint8_t playerId) {
  SDL_FRect srcRect;
  SDL_FRect posRect;
  x = x - w / 2;
  y = y - h / 2;
  srcRect = {0, 0, 256, 256};
  posRect = {x, y, static_cast<float>(w), static_cast<float>(h)};
  auto texture = Global::pcxCache["DiBoxBck.pcx"][0];
  SDL_RenderTextureTiled(Window::renderer, texture, &srcRect, 1, &posRect);
  srcRect = {0, 0, 64, 64};
  posRect = {x, y, static_cast<float>(w), 64};
  auto textures = Global::defCache["DIALGBOX.def/" + std::to_string(playerId)];
  SDL_RenderTextureTiled(Window::renderer, textures[6], &srcRect, 1, &posRect);
  posRect = {x, y + static_cast<float>(h - 64), static_cast<float>(w), 64};
  SDL_RenderTextureTiled(Window::renderer, textures[7], &srcRect, 1, &posRect);
  srcRect = {0, 0, 64, 64};
  posRect = {x, y, 64, static_cast<float>(h - 64)};
  SDL_RenderTextureTiled(Window::renderer, textures[4], &srcRect, 1, &posRect);
  posRect = {x + static_cast<float>(w - 64), y, 64, static_cast<float>(h - 64)};
  SDL_RenderTextureTiled(Window::renderer, textures[5], &srcRect, 1, &posRect);
  posRect = {x, y, 64, 64};
  SDL_RenderTexture(Window::renderer, textures[0], nullptr, &posRect);
  posRect = {x + static_cast<float>(w - 64), y, 64, 64};
  SDL_RenderTexture(Window::renderer, textures[1], nullptr, &posRect);
  posRect = {x, y + static_cast<float>(h - 64), 64, 64};
  SDL_RenderTexture(Window::renderer, textures[2], nullptr, &posRect);
  posRect = {x + static_cast<float>(w - 64), y + static_cast<float>(h - 64), 64,
             64};
  SDL_RenderTexture(Window::renderer, textures[3], nullptr, &posRect);
}

static void drawCreature(std::vector<std::pair<uint16_t, uint32_t>> creatures,
                         int32_t x, int32_t y) {
  const SDL_FRect posRects[7] = {
      // 第一行（i = 0, 1, 2）
      {static_cast<float>(x + 46), static_cast<float>(y + 90), 32, 32},
      {static_cast<float>(x + 82), static_cast<float>(y + 90), 32, 32},
      {static_cast<float>(x + 118), static_cast<float>(y + 90), 32, 32},
      // 第二行
      {static_cast<float>(x + 28), static_cast<float>(y + 137), 32, 32},
      {static_cast<float>(x + 64), static_cast<float>(y + 137), 32, 32},
      {static_cast<float>(x + 100), static_cast<float>(y + 137), 32, 32},
      {static_cast<float>(x + 136), static_cast<float>(y + 137), 32, 32}};

  for (uint8_t i = 0; i < creatures.size(); i++) {
    auto [id, count] = creatures[i];
    if (count == 0) {
      continue;
    }
    auto texture = Global::defCache["CPRSMALL.def/0"][id + 2];
    SDL_FRect posRect = posRects[i];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_RenderFillRect(Window::renderer, &posRect);
  }
}

bool AdvPopSys::run() {
  auto x = Global::cursorPoint.x;
  auto y = Global::cursorPoint.y;
  auto [index, ent] = CursorSys::choose(false, x, y);
  if (ent != entt::null) {
    auto objectComp = World::registrys[World::level].get<ObjectComp>(ent);
    switch ((ObjectType)objectComp.type) {
    case ObjectType::HERO: {
      auto playerId = World::registrys[World::level].get<PlayerIdComp>(ent).id;
      auto w = 196;
      auto h = 190;
      drawBackGround(x, y, w, h, playerId);
      x = x - w / 2;
      y = y - h / 2;
      SDL_FRect posRect = {x + 10, y + 16, 176, 166};
      SDL_Texture *texture = Global::pcxCache["ADSTATHR.pcx"][0];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      auto heroComp = &World::registrys[World::level].get<HeroComp>(ent);
      texture = Global::pcxCache[HeroCfg::heroLargePor[heroComp->portrait]][0];
      posRect = {x + 12, y + 17, 58, 64};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(255, 255, 255, 255);
      auto heroName = strPool[1258 + heroComp->portrait];
      FreeTypeSys::draw(posRect.x + 64, posRect.y, heroName);

      drawCreature(heroComp->creatures, x, y);
      break;
    }
    case ObjectType::TOWN: {
      auto playerId = World::registrys[World::level].get<PlayerIdComp>(ent).id;
      auto w = 196;
      auto h = 190;
      drawBackGround(x, y, w, h, playerId);
      x = x - w / 2;
      y = y - h / 2;
      SDL_FRect posRect = {x + 10, y + 16, 176, 166};
      SDL_Texture *texture = Global::pcxCache["ADSTATCS.pcx"][0];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      auto townComp = &World::registrys[World::level].get<TownComp>(ent);
      if (townComp->hasBuild) {
        texture = Global::defCache["itpt.def/0"][townComp->id * 2 + 1];
      } else {
        texture = Global::defCache["itpt.def/0"][townComp->id * 2];
      }
      posRect = {x + 12, y + 17, 58, 64};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(255, 255, 255, 255);
      auto townName = strPool[774 + townComp->id * 16 + townComp->nameIndex];
      FreeTypeSys::draw(posRect.x + 64, posRect.y, townName);

      if (townComp->buildings.contains((uint8_t)TownCfg::Building::TOWN_HALL)) {
        texture = Global::defCache["ITMTLS.def/0"][1];
      } else if (townComp->buildings.contains(
                     (uint8_t)TownCfg::Building::CITY_HALL)) {
        texture = Global::defCache["ITMTLS.def/0"][2];
      } else if (townComp->buildings.contains(
                     (uint8_t)TownCfg::Building::CAPITOL)) {
        texture = Global::defCache["ITMTLS.def/0"][3];
      } else {
        texture = Global::defCache["ITMTLS.def/0"][0];
      }

      posRect = {x + 78, y + 48, 34, 34};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      if (townComp->buildings.contains((uint8_t)TownCfg::Building::FORT)) {
        texture = Global::defCache["ITMCLS.def/0"][0];
      } else if (townComp->buildings.contains(
                     (uint8_t)TownCfg::Building::CITADEL)) {
        texture = Global::defCache["ITMCLS.def/0"][1];
      } else if (townComp->buildings.contains(
                     (uint8_t)TownCfg::Building::CASTLE)) {
        texture = Global::defCache["ITMCLS.def/0"][2];
      } else {
        texture = Global::defCache["ITMCLS.def/0"][3];
      }
      posRect = {x + 114, y + 48, 34, 34};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      if (townComp->heroEnt[0].has_value()) {
        texture = Global::pcxCache["TOWNQKGH.pcx"][0];
        posRect = {x + 158, y + 90, 22, 30};
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      }

      drawCreature(townComp->garCreatures, x, y);
      break;
    }
    case ObjectType::MONSTER: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);

      auto &mComp = World::registrys[World::level].get<MonsterComp>(ent);
      auto texture = Global::defCache["TWCRPORT.def/0"][mComp.id + 2];
      SDL_FRect posRect = {x - texture->w / 2, y - texture->h / 2,
                           static_cast<float>(texture->w),
                           static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
      break;
    }
    case ObjectType::ARTIFACT: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);

      auto &afComp = World::registrys[World::level].get<ArtifactComp>(ent);
      auto texture = Global::defCache["Artifact.def/0"][afComp.id];
      SDL_FRect posRect = {x - texture->w / 2, y - texture->h / 2,
                           static_cast<float>(texture->w),
                           static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
      FreeTypeSys::drawCenter(x, posRect.y + 50, strPool[162 + afComp.id]);
      break;
    }
    case ObjectType::RESOURCE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);

      FreeTypeSys::setColor(255, 255, 255, 255);
      auto &rComp = World::registrys[World::level].get<ResourceComp>(ent);
      FreeTypeSys::drawCenter(x, y - 40, strPool[2250 + rComp.id]);

      break;
    }
    case ObjectType::BOAT: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      break;
    }
    case ObjectType::TAVERN: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      break;
    }
    case ObjectType::HILL_FORT: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::WATER_WHEEL: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::WINDMILL: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::WAGON: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::ALTAR_OF_SACRIFICE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::ARENA: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::BLACK_MARKET: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::BORDER_GATE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::BUOY: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CAMPFIRE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CORPSE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::BUSH: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CARTOGRAPHER: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CREATURE_GENERATOR1: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CREATURE_GENERATOR4: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CRYPT: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::COVER_OF_DARKNESS: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CANYON: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CACTUS: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CRATER: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::CREATURE_BANK: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::DERELICT_SHIP: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::DRAGON_UTOPIA: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::EYE_OF_MAGI: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::FAERIE_RING: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::FLOTSAM: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::OBELISK: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MYSTICAL_GARDEN: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MINE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MONOLITH_ONE_WAY_ENTRANCE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MONOLITH_ONE_WAY_EXIT: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MONOLITH_TWO_WAY: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MERMAID: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MERCENARY_CAMP: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MARLETTO_TOWER: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MANDRAKE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MAGIC_WELL: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::MAGIC_SPRING: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::LEAN_TO: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::LIGHTHOUSE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::LEARNING_STONE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::LAKE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::LAVA_FLOW: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::LAVA_LAKE: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::KEYMASTER: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    case ObjectType::KELP: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(x, y - 80, strPool[1003]);
      break;
    }
    default: {
      drawBackGround(x, y, 300, 190, Global::playerId);
      break;
    }
    }
  } else {
    // no obj
    drawBackGround(x, y, 300, 190, Global::playerId);
  }
  return true;
}

bool AdvPopSys::rightMouseUp(float x, float y) {
  World::iterateSystems.push_back([]() -> bool {
    World::exitScrn();
    return false;
  });
  return false;
}
bool AdvPopSys::leftMouseUp(float x, float y) { return true; }