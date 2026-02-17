#include "PuzzleSys.h"
#include "AdvMapSys.h"

#include "Enum/Enum.h"
#include "Global/Global.h"

#include "SDL3/SDL_render.h"
#include "Set/FactionSet.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include <cstdint>

static void close() {
  World::exitScrn();
  if (Global::goalEnt != entt::null) {
    Global::advVisted[Global::playerId][World::level].insert(Global::goalEnt);
  }
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {670, 538, 64, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - 800 / 2,
                    Global::viewPort.h / 2 - 600 / 2};
  auto texture = Global::pcxCache["Puzzle.pcx"][0];
  posRect = {leftUp.x, leftUp.y, 800, 600};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  texture = Global::pcxCache["PUZZLOGO.pcx"][0];
  posRect = {leftUp.x + 607, leftUp.y + 3, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  if (Global::puzzleFadeTime > Window::dtNow) {
    auto pMap = FactionSet::fullFactions[0]->puzzleMap;
    for (auto [path, point] : pMap) {
      auto texture = Global::pcxCache[path][0];
      SDL_SetTextureAlphaMod(texture,
                             (float)(Global::puzzleFadeTime - Window::dtNow) /
                                 1000 * 255);
      posRect = {leftUp.x + point.x, leftUp.y + point.y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
  }
  return;
}

static void draw() {
  SDL_FRect srcRect;
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - 800 / 2,
                    Global::viewPort.h / 2 - 600 / 2};
  auto texture = Global::puzzleMaps[0];
  auto point = Global::grailPair->second;
  srcRect = {static_cast<float>(Global::puzzleOffset->x),
             static_cast<float>(Global::puzzleOffset->y), 595, 546};
  posRect = {leftUp.x + 7, leftUp.y + 7, 595, 546};
  // SDL_RenderFillRect(Window::renderer, &posRect);
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
  auto pMap = FactionSet::fullFactions[0]->puzzleMap;
  for (uint8_t i = 0; i < pMap.size(); i++) {
    if (!Global::puzzle[Global::playerId].contains(i)) {
      auto [path, point] = pMap[i];
      auto texture = Global::pcxCache[path][0];
      SDL_SetTextureAlphaMod(texture, 255);
      posRect = {leftUp.x + point.x, leftUp.y + point.y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - 800 / 2,
                    Global::viewPort.h / 2 - 600 / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == PuzzleSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool PuzzleSys::run() {
  draw();
  drawBackGround();
  drawButton();
  return true;
}

bool PuzzleSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - 800 / 2,
                    Global::viewPort.h / 2 - 600 / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool PuzzleSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    close();
    break;
  }
  default:
    break;
  }
  return true;
}