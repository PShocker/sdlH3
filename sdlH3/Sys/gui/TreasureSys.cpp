#include "TreasureSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "Sys/gui/LevelUpSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>

static float bakW = 480;
static float bakH = 300;

static void receive() {
  Global::fadeCallBack = []() {
    World::LMouseUpSysBak.pop_back();
    World::LMouseDownSysBak.pop_back();
    World::RMouseUpSysBak.pop_back();
    World::RMouseDownSysBak.pop_back();
    World::keyUpSysBak.pop_back();
    Global::cursorBack.pop_back();

    auto &registry = World::registrys[World::level];
    if (Global::goalIndex == 0) {
      Global::resources[Global::playerId][6] += 1000;
    } else {
      auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
      heroComp.exp += 1000;
      if (LevelUpSys::prepareLvlUp(heroComp)) {
        World::exitScrn();
        World::enterLvlup(Global::heroEnt);
        World::enterLvlup(Global::heroEnt);
      }
    }
    return true;
  };
  World::iterateSystems.pop_back();
  World::iterateSystems.pop_back();
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystemsBak.back().push_back(CursorSys::run);
  World::iterateSystems.push_back([]() {
    auto &registry = World::registrys[World::level];
    registry.destroy(Global::goalEnt);
    World::needSort = true;
    return true;
  });
  Global::fadeRect = {0, 0, Global::viewPort.w - 199, Global::viewPort.h - 47};
  World::iterateSystems.push_back(World::enterFadeScrn);
}

static void close() { World::exitScrn(); }

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

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::TREASURE_CHEST]);
}

const static std::vector<SDL_FRect> trePosition = {
    {bakW / 2 - 41 - 82, bakH / 3, 82, 93},
    {bakW / 2 - 41 + 82, bakH / 3, 82, 93},
};

static void drawTre() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};

  const static std::vector<SDL_Texture *> treTexture = {
      {Global::defCache["RESOUR82.def/0"][6],
       Global::defCache["PSKILL.def/0"][4]}};
  for (uint8_t i = 0; i < treTexture.size(); i++) {
    auto texture = treTexture[i];
    posRect = {leftUp.x + trePosition[i].x, leftUp.y + trePosition[i].y,
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (Global::goalIndex == i) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
      SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
      SDL_RenderRect(Window::renderer, &posRect);
    }
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TreasureSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool TreasureSys::run() {
  drawBackGround();
  drawTre();
  drawButton();
  return true;
}

static bool clickTre(uint8_t clickType) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  for (uint8_t i = 0; i < trePosition.size(); i++) {
    posRect = trePosition[i];
    posRect.x += leftUp.x;
    posRect.y += leftUp.y;
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        Global::goalIndex = i;
      } else {
        if (i == 0) {
          HeroScrSys::showResConfirm(clickType, 0);
        } else {
          auto &registry = World::registrys[World::level];
          auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
          HeroScrSys::showExpComfirm(clickType, heroComp);
        }
      }
      return false;
    }
  }
  return false;
}

bool TreasureSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickTre(clickType)) {
    return false;
  }
  return true;
}

bool TreasureSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickTre(clickType)) {
    return false;
  }
  return true;
}

bool TreasureSys::keyUp(uint16_t key) {
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
