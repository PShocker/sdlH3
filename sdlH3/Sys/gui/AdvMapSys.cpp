#include "AdvMapSys.h"
#include "CameraSys.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/TownCfg.h"
#include "Comp/ArenaComp.h"
#include "Comp/DwellingComp.h"
#include "Comp/HeroComp.h"
#include "Comp/MarlettoComp.h"
#include "Comp/MerCampComp.h"
#include "Comp/MineComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/SchoolMagComp.h"
#include "Comp/SchoolWarComp.h"
#include "Comp/StarAxisComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Pal/PlayerPal.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "Sys/BorderSys.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

// 查看王国
static void viewKingdom() { World::enterKingdom(); }

static void viewAdvLog() {}

static void heroSleep() {
  auto heroIndex = Global::herosIndex[Global::playerId];
  if (heroIndex >= 8) {
    return;
  }
  auto heroPair = Global::heros[Global::playerId][heroIndex];
  auto heroEnt = heroPair.second;
  auto &registry = World::registrys[heroPair.first];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  heroComp->sleep = !heroComp->sleep;
}

static void heroMove() {
  auto heroIndex = Global::herosIndex[Global::playerId];
  if (heroIndex >= 8) {
    return;
  }
  auto heroPair = Global::heros[Global::playerId][heroIndex];
  auto heroEnt = heroPair.second;
  auto &registry = World::registrys[heroPair.first];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  if (!heroComp->pathEnts.empty()) {
    heroComp->move = true;
  }
}
static void heroSpell() {
  auto heroIndex = Global::herosIndex[Global::playerId];
  if (heroIndex >= 8) {
    return;
  }
  auto heroPair = Global::heros[Global::playerId][heroIndex];
  auto heroEnt = heroPair.second;
  World::enterSpell(heroEnt);
}
static void viewAdvOpt() { World::enterAdvOpt(); }
static void viewAdvSet() { World::enterAdvSet(); }
void AdvMapSys::heroFocus() {
  if (Global::herosIndex[Global::playerId] != 0xff) {
    auto &[level, heroEnt] =
        Global::heros[Global::playerId][Global::herosIndex[Global::playerId]];
    World::level = level;
    auto &registry = World::registrys[level];
    auto positionComp = &registry.get<PositionComp>(heroEnt);
    CameraSys::focus(positionComp->point.x + 48, positionComp->point.y + 48);
  }
}
// 切换地层
static void switchWorld() { World::level = World::level == 1 ? 0 : 1; }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;

  Button b;
  b.textures =
      Global::defCache["IAM002.DEF/" + std::to_string(Global::playerId)];
  b.r = {121, 196, 32, 32};
  b.func = viewKingdom;
  b.disable = false;
  v.push_back(b);

  if (World::level == 0) {
    b.textures =
        Global::defCache["IAM010.DEF/" + std::to_string(Global::playerId)];
  } else {
    b.textures =
        Global::defCache["IAM003.DEF/" + std::to_string(Global::playerId)];
  }
  b.r = {89, 196, 32, 32};
  b.func = switchWorld;
  b.disable = false;
  v.push_back(b);

  b.textures =
      Global::defCache["IAM004.DEF/" + std::to_string(Global::playerId)];
  b.r = {121, 228, 32, 32};
  b.func = viewAdvLog;
  b.disable = false;
  v.push_back(b);

  auto heroIndex = Global::herosIndex[Global::playerId];
  if (heroIndex < 8) {
    auto heroPair = Global::heros[Global::playerId][heroIndex];
    auto heroEnt = heroPair.second;
    auto &registry = World::registrys[heroPair.first];
    auto heroComp = &registry.get<HeroComp>(heroEnt);
    if (heroComp->sleep) {
      b.textures =
          Global::defCache["IAM011.DEF/" + std::to_string(Global::playerId)];
    } else {
      b.textures =
          Global::defCache["IAM005.DEF/" + std::to_string(Global::playerId)];
    }
    b.func = heroSleep;
    b.disable = false;
    b.r = {89, 228, 32, 32};
    v.push_back(b);

    b.textures =
        Global::defCache["IAM006.DEF/" + std::to_string(Global::playerId)];
    b.func = heroMove;
    b.r = {121, 260, 32, 32};
    if (heroComp->pathEnts.empty() && heroComp->pathEntsBack.empty()) {
      b.disable = true;
    } else {
      b.disable = false;
    }
    v.push_back(b);

    b.textures =
        Global::defCache["IAM007.DEF/" + std::to_string(Global::playerId)];
    b.disable = false;
    b.r = {89, 260, 32, 32};
    b.func = heroSpell;
    v.push_back(b);

    b.textures =
        Global::defCache["IAM000.DEF/" + std::to_string(Global::playerId)];
    b.disable = false;
    b.r = {121, 324, 64, 32};
    b.func = []() { AdvMapSys::heroFocus(); };
    v.push_back(b);
  } else {
    b.textures =
        Global::defCache["IAM004.DEF/" + std::to_string(Global::playerId)];
    b.disable = true;
    b.r = {89, 228, 32, 32};
    b.func = heroSleep;
    v.push_back(b);

    b.textures =
        Global::defCache["IAM006.DEF/" + std::to_string(Global::playerId)];
    b.disable = true;
    b.r = {121, 260, 32, 32};
    b.func = heroMove;
    v.push_back(b);

    b.textures =
        Global::defCache["IAM007.DEF/" + std::to_string(Global::playerId)];
    b.disable = true;
    b.r = {89, 260, 32, 32};
    b.func = heroSpell;
    v.push_back(b);

    b.textures =
        Global::defCache["IAM000.DEF/" + std::to_string(Global::playerId)];
    b.disable = true;
    b.r = {121, 324, 64, 32};
    b.func = []() { AdvMapSys::heroFocus(); };
    v.push_back(b);
  }

  b.textures =
      Global::defCache["IAM008.DEF/" + std::to_string(Global::playerId)];
  b.disable = false;
  b.r = {121, 292, 32, 32};
  b.func = viewAdvOpt;
  v.push_back(b);

  b.textures =
      Global::defCache["IAM009.DEF/" + std::to_string(Global::playerId)];
  b.disable = false;
  b.r = {89, 292, 32, 32};
  b.func = viewAdvSet;
  v.push_back(b);

  b.textures =
      Global::defCache["IAM001.DEF/" + std::to_string(Global::playerId)];
  b.disable = false;
  b.r = {121, 356, 64, 32};
  b.func = viewAdvSet;
  v.push_back(b);

  // iam012
  b.textures =
      Global::defCache["IAM012.DEF/" + std::to_string(Global::playerId)];
  if (Global::advPages[Global::playerId].first > 0) {
    b.disable = false;
  } else {
    b.disable = true;
  }
  b.r = {191, 196, 64, 16};
  b.func = []() { Global::advPages[Global::playerId].first -= 1; };
  v.push_back(b);

  b.textures =
      Global::defCache["IAM013.DEF/" + std::to_string(Global::playerId)];
  if (Global::advPages[Global::playerId].first + 5 <
      Global::heros[Global::playerId].size()) {
    b.disable = false;
  } else {
    b.disable = true;
  }
  b.r = {191, 372, 64, 16};
  b.func = []() { Global::advPages[Global::playerId].first += 1; };
  v.push_back(b);

  b.textures =
      Global::defCache["IAM014.DEF/" + std::to_string(Global::playerId)];
  if (Global::advPages[Global::playerId].second > 0) {
    b.disable = false;
  } else {
    b.disable = true;
  }
  b.r = {52, 196, 48, 16};
  b.func = []() { Global::advPages[Global::playerId].second -= 1; };
  v.push_back(b);

  b.textures =
      Global::defCache["IAM015.DEF/" + std::to_string(Global::playerId)];
  if (Global::advPages[Global::playerId].second + 5 <
      Global::towns[Global::playerId].size()) {
    b.disable = false;
  } else {
    b.disable = true;
  }
  b.r = {52, 372, 64, 16};
  b.func = []() { Global::advPages[Global::playerId].second += 1; };
  v.push_back(b);

  return v;
}

static void drawSpellMask() {
  auto cursorType = Global::cursorType;
  if (cursorType != (uint8_t)Enum::CURSOR::SPELL) {
    return;
  }
  auto &registry = World::registrys[World::level];
  auto heroPair =
      Global::heros[Global::playerId][Global::herosIndex[Global::playerId]];
  auto heroEnt = heroPair.second;
  auto positionComp = &registry.get<PositionComp>(heroEnt);
  auto cursorIndex = Global::cursorIndex;
  switch ((Enum::CRADVNTR)Global::cursorIndex) {
  case Enum::CRADVNTR::T1_SAIL:
  case Enum::CRADVNTR::SCUTTLE_BOAT: {
    BorderSys::drawMaskWithHole(positionComp->point.x, positionComp->point.y,
                                96, 96, 128);
    break;
  }
  case Enum::CRADVNTR::TELEPORT: {
    BorderSys::drawMaskWithHole(positionComp->point.x + 32 - 7 * 32,
                                positionComp->point.y + 32 - 7 * 32, 15 * 32,
                                15 * 32, 128);
    break;
  }
  default:
    break;
  }
}

static void drawAdvMap() {
  SDL_FRect srcRect;
  SDL_FRect posRect;
  SDL_Texture *texture;
  texture = Global::pcxCache["AdvMap.pcx"][Global::playerId];
  // backgroundLeftTop
  srcRect = {0, 0, 7, 52};
  posRect = srcRect;
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundLeftCenter
  srcRect = {0, 52, 7, 1};
  posRect = {0, 52, 7, Global::viewPort.h - 91};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundLeftBottom
  srcRect = {0, 509, 7, 91};
  posRect = {0, Global::viewPort.h - 91, 7, 91};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundTopLeft
  srcRect = {7, 0, 193, 7};
  posRect = srcRect;
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundTopCenter
  srcRect = {200, 0, 1, 7};
  posRect = {200, 0, Global::viewPort.w - 444, 7};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundTopRight
  srcRect = {556, 0, 45, 7};
  posRect = {Global::viewPort.w - 244, 0, 45, 7};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundBottomLeft
  srcRect = {7, 553, 44, 47};
  posRect = {7, Global::viewPort.h - 47, 44, 47};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundBottomCenter
  srcRect = {51, 553, 505, 47};
  posRect = {51, Global::viewPort.h - 47, Global::viewPort.w - 295, 47};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundBottomRight
  srcRect = {556, 553, 45, 47};
  posRect = {Global::viewPort.w - 244, Global::viewPort.h - 47, 45, 47};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundRightMinimap
  srcRect = {601, 0, 199, 196};
  posRect = {Global::viewPort.w - 199, 0, 199, 196};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundHeroListBorderLeft
  srcRect = {601, 196, 8, 193};
  posRect = {Global::viewPort.w - 199, 196, 8, Global::viewPort.h - 407};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // backgroundTownListBorderRight
  srcRect = {795, 196, 5, 193};
  posRect = {Global::viewPort.w - 5, 196, 5, Global::viewPort.h - 407};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // listContainerSmall
  srcRect = {607, 196, 193, 196};
  posRect = {Global::viewPort.w - 193, 196, 193, 196};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  // emptyAreaFillSmall
  srcRect = {601, 389, 199, 211};
  posRect = {Global::viewPort.w - 199, Global::viewPort.h - 211, 199, 211};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
}

void AdvMapSys::drawResBar(float x, float y) {
  SDL_FRect srcRect;
  SDL_FRect posRect;
  auto texture = Global::pcxCache["AResBar.pcx"][Global::playerId];
  srcRect = {0, 0, 595, 22};
  posRect = {x, y, 595, 22};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  posRect.x += 34;
  posRect.y += 2;
  FreeTypeSys::setSize(12);
  FreeTypeSys::setColor(255, 255, 255, 255);
  for (uint8_t i = 0; i < 7; i++) {
    FreeTypeSys::draw(posRect.x, posRect.y,
                      Global::resources[Global::playerId][i]);
    posRect.x += 84;
  }
}

static void drawButton() {
  auto v = buttonInfo();
  for (auto &b : v) {
    b.r.x = Global::viewPort.w - b.r.x;
  }
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 3];
  auto top = (*topFunc.target<bool (*)()>() == AdvMapSys::run);
  AdvMapSys::drawButtons(0, 0, top, v);
}

static void drawPortrait() {
  SDL_FRect posRect;
  // render small hero PortraitsSmall
  posRect = {(float)Global::viewPort.w - 183, 212, 48, 32};
  for (uint8_t i = 0; i < 5; i++) {
    auto index = i + Global::advPages[Global::playerId].first;
    if (index >= Global::heros[Global::playerId].size()) {
      break;
    }
    auto &[level, heroEnt] = Global::heros[Global::playerId][index];
    auto &registry = World::registrys[level];
    auto heroComp = &registry.get<HeroComp>(heroEnt);
    auto texture =
        Global::pcxCache[HeroCfg::heroSmallPor[heroComp->portrait]][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == Global::herosIndex[Global::playerId]) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
    posRect.y += 32;
  }

  // render small town PortraitsSmall
  posRect = {(float)Global::viewPort.w - 53, 212, 48, 32};
  for (uint8_t i = 0; i < 5; i++) {
    auto index = i + Global::advPages[Global::playerId].second;
    if (index >= Global::towns[Global::playerId].size()) {
      break;
    }
    auto &[level, townEnt] = Global::towns[Global::playerId][index];
    auto &registry = World::registrys[level];
    auto townComp = &registry.get<TownComp>(townEnt);
    auto texture = Global::defCache["ITPA.DEF/0"][2 + 2 * townComp->id];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == Global::townsIndex[Global::playerId]) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
    posRect.y += 32;
  }
}
static void drawAgem() {
  SDL_FRect posRect = {6, 6, 46, 46};
  auto texture = Global::defCache["agemUL.def/0"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  posRect = {Global::viewPort.w - 244, 6, 46, 46};
  texture = Global::defCache["agemUR.def/0"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  posRect = {6, Global::viewPort.h - 92, 46, 46};
  texture = Global::defCache["agemLL.def/0"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  posRect = {Global::viewPort.w - 244, Global::viewPort.h - 92, 46, 46};
  texture = Global::defCache["agemLR.def/0"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawIM() {
  SDL_FRect posRect = {(float)Global::viewPort.w - 189, 212, 6, 30};

  for (uint8_t i = 0; i < 5; i++) {
    auto index = i + Global::advPages[Global::playerId].first;
    if (index >= Global::heros[Global::playerId].size()) {
      break;
    }
    auto &[level, heroEnt] = Global::heros[Global::playerId][index];
    auto &registry = World::registrys[level];
    auto heroComp = &registry.get<HeroComp>(heroEnt);
    auto texture =
        Global::defCache["IMOBIL.def/0"]
                        [std::min((int)heroComp->movement / 100, 25)];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    posRect.x = (float)Global::viewPort.w - 135;
    texture =
        Global::defCache["IMANA.def/0"][std::min((int)heroComp->mana / 5, 25)];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    posRect.x = Global::viewPort.w - 189;
    posRect.y += 32;
  }
}

static void drawMiniMap() {
  auto miniMapTexture = SDL_CreateTexture(
      Window::renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET,
      Global::mapSize, Global::mapSize);
  SDL_SetTextureBlendMode(miniMapTexture, SDL_BLENDMODE_BLEND);
  SDL_SetTextureScaleMode(miniMapTexture, SDL_SCALEMODE_NEAREST);
  SDL_SetRenderTarget(Window::renderer, miniMapTexture);
  auto backTexture = Global::miniMaps[World::level];
  SDL_FRect posRect = {0, 0, (float)backTexture->w, (float)backTexture->h};
  SDL_RenderTexture(Window::renderer, backTexture, nullptr, &posRect);
  auto &registry = World::registrys[World::level];
  for (auto ent : registry.view<ObjectComp, PlayerIdComp>()) {
    auto objectComp = &registry.get<ObjectComp>(ent);
    auto playerIdComp = &registry.get<PlayerIdComp>(ent);
    auto playerColor = PlayerPal::colors[playerIdComp->id];

    for (const auto &vec : {objectComp->blockTiles, objectComp->accessTiles}) {
      for (const auto &i : vec) {
        auto x = objectComp->x + i.first;
        auto y = objectComp->y + i.second;
        SDL_SetRenderDrawColor(Window::renderer, playerColor.r, playerColor.g,
                               playerColor.b, 255); //
        SDL_RenderPoint(Window::renderer, x, y);
      }
    }
  }
  // render fog
  auto &fogs = Global::fogs[Global::playerId][World::level];
  for (int32_t i = 0; i < fogs.size(); i++) {
    if (!fogs[i]) {
      auto x = i % Global::mapSize;
      auto y = i / Global::mapSize;
      SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255); //
      SDL_RenderPoint(Window::renderer, x, y);
    }
  }
  SDL_SetRenderTarget(Window::renderer, nullptr);

  posRect = {(float)Global::viewPort.w - 170, 26, 144, 144};
  SDL_RenderTexture(Window::renderer, miniMapTexture, nullptr, &posRect);
  SDL_DestroyTexture(miniMapTexture);

  auto width = std::round((Global::viewPort.w - 199) / Global::mapW * 144);
  auto height = std::round((Global::viewPort.h - 47) / Global::mapH * 144);
  auto texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_UNKNOWN,
                                   SDL_TEXTUREACCESS_TARGET, width, height);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(Window::renderer, texture);
  auto color = PlayerPal::colors[Global::playerId];
  SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, 255); //
  SDL_FRect posRectTemp = {0, 0, width, height};
  SDL_RenderRect(Window::renderer, &posRectTemp);
  SDL_SetRenderTarget(Window::renderer, nullptr);
  posRectTemp = {(float)(int)(Global::viewPort.x / (Global::mapW) * 144 +
                              (Global::viewPort.w - 170)),
                 (float)(int)(Global::viewPort.y / (Global::mapH) * 144 + 26),
                 static_cast<float>(width), static_cast<float>(height)};
  SDL_FRect intersection;
  if (SDL_GetRectIntersectionFloat(&posRect, &posRectTemp, &intersection)) {
    SDL_FRect srcRect{intersection.x - posRectTemp.x,
                      intersection.y - posRectTemp.y, intersection.w,
                      intersection.h};
    SDL_RenderTexture(Window::renderer, texture, &srcRect, &intersection);
  }
  SDL_DestroyTexture(texture);

  // drag minimap
  if (Global::cursorType == (uint8_t)Enum::CURSOR::ADVENTURE) {
    posRect = {(float)Global::viewPort.w - 170, 26, 144, 144};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    if (SDL_PointInRectFloat(&point, &posRect) &&
        Window::mouseState & SDL_BUTTON_LMASK) {
      Global::viewPort.x = (point.x - width / 2 - (Global::viewPort.w - 170)) *
                           ((float)Global::mapW / 144);
      Global::viewPort.y =
          (point.y - height / 2 - 26) * ((float)Global::mapH / 144);
    }
  }
}

static void
drawCreatureStat(std::vector<std::pair<uint16_t, uint32_t>> creatures) {
  // 预计算所有可能的位置矩形（简化表达式）
  SDL_FRect posRects[7] = {
      // 第一行（i = 0, 1, 2）
      {Global::viewPort.w - 153, Global::viewPort.h - 126, 32, 32},
      {Global::viewPort.w - 117, Global::viewPort.h - 126, 32, 32},
      {Global::viewPort.w - 81, Global::viewPort.h - 126, 32, 32},
      // 第二行（i = 3, 4, 5, 6）
      {Global::viewPort.w - 171, Global::viewPort.h - 79, 32, 32},
      {Global::viewPort.w - 135, Global::viewPort.h - 79, 32, 32},
      {Global::viewPort.w - 99, Global::viewPort.h - 79, 32, 32},
      {Global::viewPort.w - 63, Global::viewPort.h - 79, 32, 32}};

  for (uint8_t i = 0; i < creatures.size(); i++) {
    auto [id, count] = creatures[i];
    if (count == 0) {
      continue;
    }
    auto texture = Global::defCache["CPRSMALL.def/0"][id + 2];

    // 直接使用预计算的位置
    SDL_FRect &posRect = posRects[i];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    if (Global::advCreIndex == i) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
      SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
      SDL_RenderRect(Window::renderer, &posRect);
    }

    FreeTypeSys::setSize(12);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(posRect.x + 16, posRect.y + 30, count);
  }
}

static void drawTownStat() {
  auto playerId = Global::playerId;
  auto townIndex = Global::townsIndex[playerId];
  if (townIndex < 0xffff) {
    auto [level, townEnt] = Global::towns[playerId][townIndex];
    auto townComp = &World::registrys[level].get<TownComp>(townEnt);
    SDL_Texture *texture;
    SDL_FRect posRect;
    if (townComp->hasBuild) {
      texture = Global::defCache["itpt.def/0"][townComp->id * 2 + 1];
    } else {
      texture = Global::defCache["itpt.def/0"][townComp->id * 2];
    }
    posRect = {Global::viewPort.w - 186, Global::viewPort.h - 199, 58, 64};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

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
    posRect = {Global::viewPort.w - 120, Global::viewPort.h - 168, 34, 34};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_RenderFillRect(Window::renderer, &posRect);

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
    posRect = {Global::viewPort.w - 84, Global::viewPort.h - 168, 34, 34};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_RenderFillRect(Window::renderer, &posRect);
    if (townComp->heroEnt[0].has_value()) {
      texture = Global::pcxCache["TOWNQKGH.pcx"][0];
      posRect = {Global::viewPort.w - 40, Global::viewPort.h - 126, 22, 30};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      // SDL_RenderFillRect(Window::renderer, &posRect);
    }
    drawCreatureStat(townComp->garCreatures);
  }
}

static void drawHeroStat() {
  auto playerId = Global::playerId;
  auto heroIndex = Global::herosIndex[playerId];
  if (heroIndex < 8) {
    auto [level, heroEnt] = Global::heros[playerId][heroIndex];
    auto heroComp = &World::registrys[level].get<HeroComp>(heroEnt);
    auto texture =
        Global::pcxCache[HeroCfg::heroLargePor[heroComp->portrait]][0];
    SDL_FRect posRect = {Global::viewPort.w - 186, Global::viewPort.h - 199, 58,
                         64};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    FreeTypeSys::setSize(12);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(posRect.x + 75, posRect.y + 48,
                            HeroScrSys::heroPrimAbility(*heroComp, 0));
    FreeTypeSys::drawCenter(posRect.x + 102, posRect.y + 48,
                            HeroScrSys::heroPrimAbility(*heroComp, 1));
    FreeTypeSys::drawCenter(posRect.x + 130, posRect.y + 48,
                            HeroScrSys::heroPrimAbility(*heroComp, 2));
    FreeTypeSys::drawCenter(posRect.x + 157, posRect.y + 48,
                            HeroScrSys::heroPrimAbility(*heroComp, 3));
    FreeTypeSys::drawCenter(posRect.x + 155, posRect.y + 87, heroComp->mana);

    auto strPool = *Lang::strPool[Global::langIndex];
    auto heroName = strPool[1258 + heroComp->portrait];
    FreeTypeSys::draw(posRect.x + 64, posRect.y, heroName);

    auto mor = HeroScrSys::heroMor(*heroComp);
    texture = Global::defCache["IMRL22.def/0"][mor];
    posRect = {posRect.x + 3, posRect.y + 74, 22, 12};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    auto luk = HeroScrSys::heroLuk(*heroComp);
    texture = Global::defCache["ILCK22.def/0"][luk];
    posRect = {posRect.x, posRect.y + 17, 22, 12};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    drawCreatureStat(heroComp->creatures);
  }
}

static void drawStat() {
  SDL_FRect posRect = {Global::viewPort.w - 189, Global::viewPort.h - 200, 176,
                       166};
  SDL_Texture *texture;
  if (Global::advStatTime >= Window::dtNow) {
    if (!Global::advStrs.empty()) {
      for (auto [point, color, str] : Global::advStrs) {
        FreeTypeSys::setSize(12);
        FreeTypeSys::setColor(color.r, color.g, color.b, color.a);
        FreeTypeSys::drawCenter(posRect.x + point.x, posRect.y + point.y, str);
      }
    }
    if (!Global::advStats.empty()) {
      auto totalWidth = 0;
      for (auto [texture, str] : Global::advStats) {
        totalWidth += texture->w;
      }
      auto padding = (184 - totalWidth) / (Global::advStats.size() + 1);
      for (auto i = 0; i < Global::advStats.size(); i++) {
        auto [texture, str] = Global::advStats[i];
        SDL_FRect pRect{posRect.x + padding * (i + 1) + i * texture->w,
                        posRect.y + 40, static_cast<float>(texture->w),
                        static_cast<float>(texture->h)};
        SDL_RenderTexture(Window::renderer, texture, nullptr, &pRect);
        FreeTypeSys::setSize(12);
        FreeTypeSys::setColor(255, 255, 255, 255);
        FreeTypeSys::drawCenter(pRect.x + pRect.w / 2, pRect.y + pRect.h + 2,
                                str);
      }
    }
  } else if (Global::herosIndex[Global::playerId] < 8) {
    texture = Global::pcxCache["ADSTATHR.pcx"][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    drawHeroStat();
  } else if (Global::townsIndex[Global::playerId] < 0xffff) {
    texture = Global::pcxCache["ADSTATCS.pcx"][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    drawTownStat();
  }
}

static void drawPageButton() {}

static void drawBottomInfo() {
  if (Global::IMEText.has_value()) {
    return;
  }
  if (Global::cursorType == (uint8_t)Enum::CURSOR::ADVENTURE ||
      Global::cursorType == (uint8_t)Enum::CURSOR::FADE) {
    if (Window::mouseX > Global::viewPort.w - 199 ||
        Window::mouseY > Global::viewPort.h - 47) {
      auto v = buttonInfo();
      return;
    }
    if (Window::mouseX + Global::viewPort.x < 0 ||
        Window::mouseY + Global::viewPort.y < 0 ||
        Window::mouseX + Global::viewPort.x >= Global::mapSize * 32 ||
        Window::mouseY + Global::viewPort.y >= Global::mapSize * 32) {
      return;
    }
    SDL_FPoint point = {Window::mouseX + Global::viewPort.x,
                        Window::mouseY + Global::viewPort.y};
    auto p = CursorSys::goalPoint(point);
    uint8_t goalX = p.x;
    uint8_t goalY = p.y;

    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(255, 255, 255, 255);
    auto strPool = *Lang::strPool[Global::langIndex];
    std::u16string s = u"";
    auto [index, ent] =
        CursorSys::choose(false, Window::mouseX, Window::mouseY);
    if (ent != entt::null) {
      auto objectComp = World::registrys[World::level].get<ObjectComp>(ent);
      switch (objectComp.type) {
      case (uint8_t)ObjectType::CREATURE_GENERATOR1: {
        auto &dComp = World::registrys[World::level].get<DwellingComp>(ent);
        s = strPool[2247 + dComp.id];
        break;
      }
      case (uint8_t)ObjectType::CREATURE_GENERATOR4: {
        auto &dComp = World::registrys[World::level].get<DwellingComp>(ent);
        s = strPool[2327 + dComp.id];
        break;
      }
      case (uint8_t)ObjectType::MINE: {
        auto &mComp = World::registrys[World::level].get<MineComp>(ent);
        s = strPool[918 + mComp.id];
        break;
      }
      case (uint8_t)ObjectType::HERO: {
        auto &hComp = World::registrys[World::level].get<HeroComp>(ent);
        s = strPool[1258 + hComp.portrait];
        break;
      }
      case (uint8_t)ObjectType::TOWN: {
        auto &tComp = World::registrys[World::level].get<TownComp>(ent);
        s = strPool[774 + tComp.id * 16 + tComp.nameIndex];
        break;
      }
      default: {
        s = strPool[926 + objectComp.type];
        break;
      }
      }
      // 判断是否访问
      switch (objectComp.type) {
      case (uint8_t)ObjectType::OBELISK:
      case (uint8_t)ObjectType::WATER_WHEEL:
      case (uint8_t)ObjectType::WINDMILL: {
        if (Global::advVisted[Global::playerId][World::level].contains(ent)) {
          s += u"(" + strPool[2329] + u")";
        }
        break;
      }
      case (uint8_t)ObjectType::IDOL_OF_FORTUNE:
      case (uint8_t)ObjectType::TEMPLE:
      case (uint8_t)ObjectType::STABLES:
      case (uint8_t)ObjectType::MAGIC_WELL: {
        if (Global::herosIndex[Global::playerId] < 8) {
          auto &[level, heroEnt] =
              Global::heros[Global::playerId]
                           [Global::herosIndex[Global::playerId]];
          auto hComp = World::registrys[level].get<HeroComp>(heroEnt);
          if (hComp.visited.contains(objectComp.type)) {
            s += u"(" + strPool[2329] + u")";
          }
        }
        break;
      }
      case (uint8_t)ObjectType::ARENA: {
        if (Global::herosIndex[Global::playerId] < 8) {
          auto &[level, heroEnt] =
              Global::heros[Global::playerId]
                           [Global::herosIndex[Global::playerId]];
          auto hComp = World::registrys[level].get<HeroComp>(heroEnt);

          auto aComp = World::registrys[World::level].get<ArenaComp>(ent);
          if (aComp.visitHeros.contains(hComp.portrait)) {
            s += u"(" + strPool[2329] + u")";
          }
        }
        break;
      }
      case (uint8_t)ObjectType::MARLETTO_TOWER: {
        if (Global::herosIndex[Global::playerId] < 8) {
          auto &[level, heroEnt] =
              Global::heros[Global::playerId]
                           [Global::herosIndex[Global::playerId]];
          auto hComp = World::registrys[level].get<HeroComp>(heroEnt);

          auto mComp = World::registrys[World::level].get<MarlettoComp>(ent);
          if (mComp.visitHeros.contains(hComp.portrait)) {
            s += u"(" + strPool[2329] + u")";
          }
        }
        break;
      }
      case (uint8_t)ObjectType::MERCENARY_CAMP: {
        if (Global::herosIndex[Global::playerId] < 8) {
          auto &[level, heroEnt] =
              Global::heros[Global::playerId]
                           [Global::herosIndex[Global::playerId]];
          auto hComp = World::registrys[level].get<HeroComp>(heroEnt);

          auto mComp = World::registrys[World::level].get<MerCampComp>(ent);
          if (mComp.visitHeros.contains(hComp.portrait)) {
            s += u"(" + strPool[2329] + u")";
          }
        }
        break;
      }
      case (uint8_t)ObjectType::SCHOOL_OF_WAR: {
        if (Global::herosIndex[Global::playerId] < 8) {
          auto &[level, heroEnt] =
              Global::heros[Global::playerId]
                           [Global::herosIndex[Global::playerId]];
          auto hComp = World::registrys[level].get<HeroComp>(heroEnt);

          auto sComp = World::registrys[World::level].get<SchoolWarComp>(ent);
          if (sComp.visitHeros.contains(hComp.portrait)) {
            s += u"(" + strPool[2329] + u")";
          }
        }
        break;
      }
      case (uint8_t)ObjectType::SCHOOL_OF_MAGIC: {
        if (Global::herosIndex[Global::playerId] < 8) {
          auto &[level, heroEnt] =
              Global::heros[Global::playerId]
                           [Global::herosIndex[Global::playerId]];
          auto hComp = World::registrys[level].get<HeroComp>(heroEnt);

          auto sComp = World::registrys[World::level].get<SchoolMagComp>(ent);
          if (sComp.visitHeros.contains(hComp.portrait)) {
            s += u"(" + strPool[2329] + u")";
          }
        }
        break;
      }
      case (uint8_t)ObjectType::STAR_AXIS: {
        if (Global::herosIndex[Global::playerId] < 8) {
          auto &[level, heroEnt] =
              Global::heros[Global::playerId]
                           [Global::herosIndex[Global::playerId]];
          auto hComp = World::registrys[level].get<HeroComp>(heroEnt);

          auto sComp = World::registrys[World::level].get<StarAxisComp>(ent);
          if (sComp.visitHeros.contains(hComp.portrait)) {
            s += u"(" + strPool[2329] + u")";
          }
        }
        break;
      }
      default: {
        break;
      }
      }
    }
    s += u'(' + FreeTypeSys::str(goalX) + u',' + FreeTypeSys::str(goalY) + u')';
    FreeTypeSys::drawCenter((Global::viewPort.w - 199) / 2,
                            (Global::viewPort.h - 46), s);
  }
}

static void drawIME() {
  if (Global::IMEText.has_value()) {
    /* Start-Stop */
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(255, 255, 255, 255);
    auto s = Global::IMEText.value() + Global::IMETextBak.value();
    FreeTypeSys::draw(12, (Global::viewPort.h - 46), s);
  }
}

bool AdvMapSys::run() {
  drawSpellMask();
  drawAdvMap();
  drawButton();
  drawPortrait();
  drawIM();
  drawMiniMap();
  drawAgem();
  drawResBar(3, Global::viewPort.h - 25);
  drawStat();
  drawPageButton();
  drawBottomInfo();
  drawIME();
  return true;
}
static uint8_t
clickCreatureStat(std::vector<std::pair<uint16_t, uint32_t>> creatures) {
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRects[7] = {
      // 第一行（i = 0, 1, 2）
      {Global::viewPort.w - 153, Global::viewPort.h - 126, 32, 32},
      {Global::viewPort.w - 117, Global::viewPort.h - 126, 32, 32},
      {Global::viewPort.w - 81, Global::viewPort.h - 126, 32, 32},
      // 第二行（i = 3, 4, 5, 6）
      {Global::viewPort.w - 171, Global::viewPort.h - 79, 32, 32},
      {Global::viewPort.w - 135, Global::viewPort.h - 79, 32, 32},
      {Global::viewPort.w - 99, Global::viewPort.h - 79, 32, 32},
      {Global::viewPort.w - 63, Global::viewPort.h - 79, 32, 32}};

  for (uint8_t i = 0; i < creatures.size(); i++) {
    auto [id, count] = creatures[i];
    SDL_FRect &posRect = posRects[i];
    if (SDL_PointInRectFloat(&point, &posRect)) {
      return i;
    }
  }
  return 0xff;
}

static bool clickStat(uint8_t clickType) {
  // 1. 使用常量定义矩形区域
  static const SDL_FRect STAT_RECT = {Global::viewPort.w - 189,
                                      Global::viewPort.h - 200, 176, 166};

  // 2. 鼠标位置检查
  const SDL_FPoint mousePoint = {static_cast<float>(Window::mouseX),
                                 static_cast<float>(Window::mouseY)};

  if (!SDL_PointInRectFloat(&mousePoint, &STAT_RECT)) {
    return false;
  }

  // 3. 冷却时间检查
  if (Global::advStatTime >= Window::dtNow) {
    Global::advStatTime = Window::dtNow;
    return true;
  }

  // 4. 定义局部变量
  std::vector<std::pair<uint16_t, uint32_t>> *creatures = nullptr;
  uint8_t level = 0;
  entt::entity heroEnt = entt::null;
  const auto playerId = Global::playerId;

  // 5. 获取生物列表（优化重复代码）
  if (Global::herosIndex[playerId] < 8) {
    const auto heroIndex = Global::herosIndex[playerId];
    const auto &heroData = Global::heros[playerId][heroIndex];
    level = heroData.first;
    heroEnt = heroData.second;
    creatures = &World::registrys[level].get<HeroComp>(heroEnt).creatures;
  } else if (Global::townsIndex[playerId] != 0xFFFF) {
    const auto townIndex = Global::townsIndex[playerId];
    const auto &townData = Global::towns[playerId][townIndex];
    level = townData.first;
    const auto townEnt = townData.second;
    creatures = &World::registrys[level].get<TownComp>(townEnt).garCreatures;
  }

  // 6. 检查有效性
  if (!creatures || creatures->empty()) {
    return false;
  }

  // 7. 获取点击的生物索引
  const uint8_t clickedIndex = clickCreatureStat(*creatures);
  if (clickedIndex == 0xFF) {
    return false;
  }

  // 8. 使用引用避免重复访问
  auto &clickedCreature = creatures->at(clickedIndex);

  // 9. 判断点击类型
  const bool isLeftClick =
      (clickType == static_cast<uint8_t>(Enum::CLICKTYPE::L_UP));
  const bool isRightClick =
      (clickType == static_cast<uint8_t>(Enum::CLICKTYPE::R_UP));

  // 10. 主要逻辑分支
  if (Global::advCreIndex == 0xFF && isLeftClick) {
    // 开始拖拽
    if (clickedCreature.second != 0) {
      Global::advCreIndex = clickedIndex;
    }
    return false;
  }

  if (Global::advCreIndex == clickedIndex || !isLeftClick) {
    // 放置或右键操作
    if (clickedCreature.second != 0) {
      const uint8_t creType =
          isLeftClick ? static_cast<uint8_t>(Enum::CRETYPE::MOD_HERO)
                      : static_cast<uint8_t>(Enum::CRETYPE::POP_HERO);

      if (isLeftClick) {
        Global::advCreIndex = 0xFF;
      }

      if (heroEnt != entt::null) {
        World::enterCreature({level, heroEnt}, clickedCreature, creType);
      } else {
        World::enterCreature(clickedCreature, creType);
      }
    }
    return true;
  }

  // 11. 交换或合并逻辑
  auto &draggedCreature = creatures->at(Global::advCreIndex);

  if (clickedCreature.first != draggedCreature.first) {
    // 交换
    std::swap(clickedCreature, draggedCreature);
  } else {
    // 合并
    clickedCreature.second += draggedCreature.second;
    draggedCreature.second = 0;
  }

  Global::advCreIndex = 0xFF;
  return true;
}

static bool clickHeroPor(uint8_t clickType) {
  // click small hero PortraitsSmall
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  posRect = {(float)Global::viewPort.w - 183, 212, 48, 32};

  for (uint8_t i = 0; i < 5; i++) {
    auto index = i + Global::advPages[Global::playerId].first;
    if (index >= Global::heros[Global::playerId].size()) {
      break;
    }
    if (SDL_PointInRectFloat(&point, &posRect)) {
      auto &[level, heroEnt] = Global::heros[Global::playerId][index];
      auto &registry = World::registrys[level];
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        if (Global::herosIndex[Global::playerId] == index) {
          World::enterHeroScrn(level, heroEnt, (uint8_t)Enum::SCNTYPE::MOD);
        } else {
          CursorSys::clearHeroPath();
          Global::advCreIndex = 0xff;
        }
        AdvMapSys::heroFocus(heroEnt, level);
      } else {
        World::enterHeroScrn(level, heroEnt, (uint8_t)Enum::SCNTYPE::POP);
      }
      return true;
    }
    posRect.y += 32;
  }
  return false;
}

static bool clickTownPor(uint8_t clickType) {
  // click small town PortraitsSmall
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {(float)Global::viewPort.w - 53, 212, 48, 32};
  for (uint8_t i = 0; i < 5; i++) {
    auto index = i + Global::advPages[Global::playerId].second;
    if (index >= Global::towns[Global::playerId].size()) {
      break;
    }
    if (SDL_PointInRectFloat(&point, &posRect)) {
      auto &[level, townEnt] = Global::towns[Global::playerId][index];
      auto &registry = World::registrys[level];
      if (clickType == static_cast<uint8_t>(Enum::CLICKTYPE::L_UP)) {
        if (Global::townsIndex[Global::playerId] == index) {
          World::enterTownScrn(level, townEnt, (uint8_t)Enum::SCNTYPE::MOD);
        }
        AdvMapSys::townFocus(townEnt, level);
      } else {
        World::enterTownScrn(level, townEnt, (uint8_t)Enum::SCNTYPE::POP);
      }
      return true;
    }
    posRect.y += 32;
  }
  return false;
}

bool AdvMapSys::leftMouseUp(float x, float y) {
  if (Global::heroMove) {
    return true;
  }
  auto button = buttonInfo();
  for (auto &b : button) {
    b.r.x = Global::viewPort.w - b.r.x;
  }
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;
  if (AdvMapSys::clickButtons(0, 0, button, clickType)) {
    return false;
  }
  if (clickHeroPor(clickType)) {
    return false;
  }
  if (clickTownPor(clickType)) {
    return false;
  }
  if (clickStat(clickType)) {
    return false;
  }

  return true;
}

bool AdvMapSys::leftMouseDown(float x, float y) {
  if (Global::heroMove) {
    return true;
  }
  auto button = buttonInfo();
  for (auto &b : button) {
    b.r.x = Global::viewPort.w - b.r.x;
  }
  if (AdvMapSys::clickButtons(0, 0, button, (uint8_t)Enum::CLICKTYPE::L_DOWN)) {
    return false;
  }
  return true;
}

bool AdvMapSys::rightMouseDown(float x, float y) {
  if (Global::heroMove) {
    return true;
  }
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;
  if (clickHeroPor(clickType)) {
    return false;
  }
  if (clickTownPor(clickType)) {
    return false;
  }
  if (clickStat(clickType)) {
    return false;
  }
  return true;
}

bool AdvMapSys::keyUp(uint16_t key) {
  if (Global::heroMove) {
    return true;
  }
  switch (key) {
  case SDL_SCANCODE_SPACE: {
    auto index = Global::herosIndex[Global::playerId];
    if (index < 8) {
      auto [level, heroEnt] = Global::heros[Global::playerId][index];
      World::level = level;
      auto &registry = World::registrys[level];
      auto heroComp = &registry.get<HeroComp>(heroEnt);
      if (!heroComp->pathEnts.empty()) {
        heroComp->move = true;
        Global::heroMove = true;
        return true;
      } else if (heroComp->curEnt.has_value()) {
        heroComp->goalEnt = heroComp->curEnt;
        heroComp->move = true;
        Global::heroMove = true;
        Global::cursorIndex = CursorSys::astar(false);
        if (Global::cursorIndex == 0) {
          Global::cursorIndex =
              CursorSys::choose(false, Window::mouseX, Window::mouseY).first;
        }
        return true;
      }
      auto positionComp = &registry.get<PositionComp>(heroEnt);
      CameraSys::focus(positionComp->point.x + 48, positionComp->point.y + 48);
      break;
    }
  }
  case SDL_SCANCODE_TAB: {
    Global::IMEText = u"";
    Global::IMETextBak = u"";
    const SDL_Rect posRect = {12, static_cast<int>((Global::viewPort.h - 52)),
                              static_cast<int>(Global::viewPort.w), 32};
    SDL_SetHint(SDL_HINT_IME_IMPLEMENTED_UI, "composition");
    SDL_Window *window = SDL_GetKeyboardFocus();
    /* Start-Stop */
    SDL_StartTextInput(window);
    SDL_SetTextInputArea(window, &posRect, 0);
    World::textEditSys = [](const char *text) {
      if (text[0] != '\0') {
        Global::IMETextBak.value() = FreeTypeSys::str(text);
      } else {
        Global::IMETextBak = u"";
      }
    };
    World::textInputSys = [](const char *text) {
      Global::IMEText.value() += FreeTypeSys::str(text);
    };
    break;
  }
  default:
    break;
  }
  return true;
}

bool AdvMapSys::keyDown(uint16_t key) {
  if (Global::heroMove) {
    return true;
  }
  switch (key) {
  case SDL_SCANCODE_BACKSPACE: {
    if (Global::IMEText.has_value() && !Global::IMEText->empty()) {
      Global::IMEText->pop_back();
    }
    return false;
  }
  case SDL_SCANCODE_RETURN: {
    if (Global::IMEText.has_value()) {
      Global::IMEText = std::nullopt;
      Global::IMETextBak = std::nullopt;

      SDL_Window *window = SDL_GetKeyboardFocus();
      SDL_StopTextInput(window);
      SDL_SetTextInputArea(window, nullptr, 0);
    }
    return false;
  }
  default: {
    break;
  }
  }
  return true;
}

void AdvMapSys::drawButtons(float x, float y, bool press,
                            std::vector<Button> &v) {
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < v.size(); i++) {
    auto textures = v[i].textures;
    auto texture = textures[0];
    posRect = {static_cast<float>((int)(x + v[i].r.x)),
               static_cast<float>((int)(y + v[i].r.y)),
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    if (v[i].disable) {
      if (textures.size() >= 3) {
        texture = textures[2];
      } else {
        continue;
      }
    } else if (SDL_PointInRectFloat(&point, &posRect)) {
      if (Window::mouseState & SDL_BUTTON_LMASK && press) {
        texture = textures[1];
      }
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
}

bool AdvMapSys::clickButtons(float x, float y, std::vector<Button> &v,
                             uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < v.size(); i++) {
    SDL_FRect posRect = {x + v[i].r.x, y + v[i].r.y, v[i].r.w, v[i].r.h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      switch (clickType) {
      case (uint8_t)Enum::CLICKTYPE::L_UP: {
        if (!v[i].disable) {
          v[i].func();
          Global::audioData["button.wav"] = 0;
        }
        break;
      }
      case (uint8_t)Enum::CLICKTYPE::R_DOWN: {
        if (v[i].title != u"" || v[i].info != u"") {
          auto confirmbakW = 450;
          auto confirmbakH = 130;
          auto title = v[i].title;
          auto info = v[i].info;
          Global::confirmdraw = [confirmbakW, confirmbakH, title, info]() {
            SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                              Global::viewPort.h / 2 - confirmbakH / 2};
            FreeTypeSys::setSize(13);
            FreeTypeSys::setColor(240, 224, 104, 255);
            FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                                    title);
            FreeTypeSys::setColor(255, 255, 255, 255);
            FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 55,
                                    info);
          };
          World::enterConfirm(confirmbakW, confirmbakH,
                              ((uint8_t)Enum::SCNTYPE::POP));
        }
        break;
      }
      default: {
        break;
      }
      }
      return true;
    }
  }
  return false;
}

bool AdvMapSys::drawButtonsText(float x, float y, float pX, float pY,
                                std::vector<Button> &v) {
  // button
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < v.size(); i++) {
    SDL_FRect r = v[i].r;
    r.x += x;
    r.y += y;
    if (SDL_PointInRectFloat(&point, &r)) {
      FreeTypeSys::drawCenter(pX, pY, v[i].info);
      return true;
    }
  }
  return false;
}

void AdvMapSys::heroFocus(entt::entity heroEnt, uint8_t level) {
  auto &registry = World::registrys[level];
  auto &heros = Global::heros[Global::playerId];
  for (uint8_t i = 0; i < heros.size(); i++) {
    if (heros[i].first == level && heros[i].second == heroEnt) {
      World::level = level;

      Global::townsIndex[Global::playerId] = 0xffff;
      Global::herosIndex[Global::playerId] = i;
      auto positionComp = &registry.get<PositionComp>(heroEnt);
      CameraSys::focus(positionComp->point.x + 48, positionComp->point.y + 48);

      if (i >= Global::advPages[Global::playerId].first + 5) {
        Global::advPages[Global::playerId].first = i - 4;
      } else if (i < Global::advPages[Global::playerId].first) {
        Global::advPages[Global::playerId].first = i;
      }

      break;
    }
  }
}

void AdvMapSys::townFocus(entt::entity townEnt, uint8_t level) {
  auto &registry = World::registrys[level];
  auto &towns = Global::towns[Global::playerId];
  for (uint8_t i = 0; i < towns.size(); i++) {
    if (towns[i].first == level && towns[i].second == townEnt) {
      World::level = level;
      CursorSys::clearHeroPath();
      Global::advCreIndex = 0xff;
      Global::herosIndex[Global::playerId] = 0xff;
      auto positionComp = &registry.get<PositionComp>(townEnt);
      Global::townsIndex[Global::playerId] = i;
      CameraSys::focus(positionComp->point.x + 112,
                       positionComp->point.y + 144);
      if (i >= Global::advPages[Global::playerId].second + 5) {
        Global::advPages[Global::playerId].second = i - 4;
      } else if (i < Global::advPages[Global::playerId].second) {
        Global::advPages[Global::playerId].second = i;
      }
      break;
    }
  }
}
