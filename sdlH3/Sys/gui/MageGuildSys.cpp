#include "MageGuildSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["TPMAGE1.DEF/0"];
  b.r = {748, 556, 48, 40};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  posRect = {leftUp.x, leftUp.y, 800, 600};
  auto texture = Global::pcxCache["TPMAGE.pcx"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  return;
}

static const std::vector<std::vector<SDL_Point>> positions = {
    {{222, 445}, {312, 445}, {402, 445}, {520, 445}, {610, 445}, {700, 445}},
    {{48, 53}, {48, 147}, {48, 241}, {48, 335}, {48, 429}},
    {{570, 82}, {672, 82}, {570, 157}, {672, 157}},
    {{183, 42}, {183, 148}, {183, 253}},
    {{491, 325}, {591, 325}}};

static void drawSpells() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == MageGuildSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool MageGuildSys::run() {
  drawBackGround();
  drawSpells();
  drawButton();
  return true;
}

bool MageGuildSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

static bool clickSpells(bool leftClick) { return false; }

bool MageGuildSys::rightMouseDown(float x, float y) {
  if (clickSpells(false)) {
    return false;
  }
  return true;
}

bool MageGuildSys::keyUp(uint16_t key) {
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