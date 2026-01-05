#include "ArenaSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/ArenaComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <string>
#include <vector>

static float bakW = 480;
static float bakH = 300;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &schMComp =
      World::registrys[World::level].get<ArenaComp>(Global::goalEnt);
  if (schMComp.visitHeros.contains(heroComp.portrait)) {
    return true;
  } else {
    return false;
  }
}

static void receive() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &schMComp =
      World::registrys[World::level].get<ArenaComp>(Global::goalEnt);
  if (!visited()) {
    if (Global::goalIndex == 0) {
      heroComp.primSkills[0] += 2;
    } else {
      heroComp.primSkills[1] += 2;
    }
    heroComp.visitedLog.insert({(uint8_t)ObjectType::ARENA, Global::goalIndex});
    schMComp.visitHeros.insert(heroComp.portrait);
  }
  heroComp.visited.insert((uint8_t)ObjectType::ARENA);
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
  std::u16string s = strPool[928];
  FreeTypeSys::drawCenter(x, y - bakH / 2 + 15, s);
}

const static std::vector<SDL_FRect> primPosition = {
    {bakW / 2 - 41 - 82, bakH / 3, 82, 93},
    {bakW / 2 - 41 + 82, bakH / 3, 82, 93},
};

static void drawPrim() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  FreeTypeSys::setSize(13);
  auto strPool = *Lang::strPool[Global::langIndex];
  if (!visited()) {
    const static std::vector<SDL_Texture *> textures = {
        {Global::defCache["PSKILL.def/0"][0],
         Global::defCache["PSKILL.def/0"][1]}};
    for (uint8_t i = 0; i < textures.size(); i++) {
      auto texture = textures[i];
      posRect = {leftUp.x + primPosition[i].x, leftUp.y + primPosition[i].y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      if (Global::goalIndex == i) {
        SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
        SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderRect(Window::renderer, &posRect);
      }
      auto str = strPool[1 + i];
      FreeTypeSys::setColor(255, 255, 255, 255);
      FreeTypeSys::drawCenter(posRect.x + posRect.w / 2,
                              posRect.y + posRect.h + 4, u"+2 " + str);
    }
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[593]);
  } else {
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + bakW / 2, leftUp.y + 40, strPool[594]);
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == ArenaSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool ArenaSys::run() {
  drawBackGround();
  drawPrim();
  drawButton();
  return true;
}

static bool clickPrim(bool leftClick) {
  if (!visited()) {
    SDL_FRect posRect;
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    for (uint8_t i = 0; i < primPosition.size(); i++) {
      posRect = primPosition[i];
      posRect.x += leftUp.x;
      posRect.y += leftUp.y;
      if (SDL_PointInRectFloat(&point, &posRect)) {
        if (leftClick) {
          Global::goalIndex = i;
        } else {
          HeroScrSys::showPrimComfirm(leftClick, i);
        }
        return true;
      }
    }
  }
  return false;
}

bool ArenaSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  if (clickPrim(true)) {
    return false;
  }
  return true;
}

bool ArenaSys::rightMouseDown(float x, float y) {
  if (clickPrim(false)) {
    return false;
  }
  return true;
}

bool ArenaSys::keyUp(uint16_t key) {
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
