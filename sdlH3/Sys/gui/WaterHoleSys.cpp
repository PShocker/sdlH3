#include "WaterHoleSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/RalFlagComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>

static float bakW = 450;
static float bakH = 340;

static void receive() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &ralComp =
      World::registrys[World::level].get<RalFlagComp>(Global::goalEnt);
  if (!ralComp.visitHeros.contains(heroComp.portrait)) {
    heroComp.movement += 1000;
    AdventureBonus bonus = {
        .src = ObjectType::WATERING_HOLE,
        .type = Enum::ADVENTURE_MORALE,
        .subType = 0,
        .val = 1,
    };
    heroComp.adventureBonus.insert({Enum::ADVENTURE_MORALE, bonus});
  }
  heroComp.visited.insert(ObjectType::WATERING_HOLE);
  ralComp.visitHeros.insert(heroComp.portrait);
  World::exitScrn();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  b.func = receive;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::WATERING_HOLE]);

  return;
}

const SDL_FRect morPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto texture = Global::defCache["imrl82.def/0"][4];
  posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y, morPosition.w,
             morPosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == WaterHoleSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool WaterHoleSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickMor(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y, morPosition.w,
             morPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    HeroScrSys::showMorComfirm(clickType);
    return true;
  }
  return false;
}

bool WaterHoleSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool WaterHoleSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickMor(clickType)) {
    return true;
  }
  return true;
}

bool WaterHoleSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    receive();
    break;
  }
  default:
    break;
  }
  return true;
}