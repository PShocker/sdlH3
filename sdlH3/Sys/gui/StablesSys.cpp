#include "StablesSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstddef>
#include <cstdint>

static float bakW = 450;
static float bakH = 240;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  if (heroComp.visited.contains((uint8_t)ObjectType::STABLES)) {
    return true;
  }
  return false;
}

static bool upgrade() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  for (auto [creId, num] : heroComp.creatures) {
    if (creId == Enum::CAVALIER) {
      return true;
    }
  }
  return false;
}

static void receive() {
  World::exitScrn();
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  if (!heroComp.visited.contains((uint8_t)ObjectType::STABLES)) {
    heroComp.movement += 100;
    for (auto &[creId, num] : heroComp.creatures) {
      if (creId == Enum::CAVALIER) {
        creId = Enum::CHAMPION;
      }
    }
  }
  heroComp.visited.insert((uint8_t)ObjectType::STABLES);
}

void StablesSys::init() {
  buttons.clear();
  {
    Button button;
    button.textures = Global::defCache["iOKAY.def/0"];
    button.r ={bakW / 2 - 32, bakH - 60, 64, 30};
    button.clickFunc = receive;
    button.disableFunc = []() { return false; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto oName = strPool[927 + ObjectType::STABLES];

  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15, oName);
  return;
}

static void draw() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  if (visited()) {
    FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 40,
                            strPool[717]);
  } else {
    if (upgrade()) {
      FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 40,
                              strPool[719]);
      auto texture = Global::defCache["TWCRPORT.def/0"][Enum::CHAMPION + 2];
      SDL_FRect posRect{Global::viewPort.w / 2 - texture->w / 2,
                        y - bakH / 2 + 90, static_cast<float>(texture->w),
                        static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    } else {
      FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 40,
                              strPool[718]);
    }
  }
}

static void drawButton() {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == StablesSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, StablesSys::buttons);
}

bool StablesSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

bool StablesSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, StablesSys::buttons, clickType)) {
    return false;
  }
  return true;
}

bool StablesSys::keyUp(uint16_t key) {
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