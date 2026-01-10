#include "SchoolMagSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/SchoolMagComp.h"
#include "Enum/Enum.h"
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
#include <vector>

static float bakW = 480;
static float bakH = 300;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &schMComp =
      World::registrys[World::level].get<SchoolMagComp>(Global::goalEnt);
  if (schMComp.visitHeros.contains(heroComp.portrait)) {
    return true;
  }
  return false;
}

static void close() { World::exitScrn(); }

static void receive() {
  auto &gold = Global::resources[Global::playerId][6];
  if (gold < 1000) {
    return;
  }
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto &schMComp =
      World::registrys[World::level].get<SchoolMagComp>(Global::goalEnt);
  if (!schMComp.visitHeros.contains(heroComp.portrait)) {
    if (Global::goalIndex == 0) {
      heroComp.primSkills[2] += 1;
    } else {
      heroComp.primSkills[3] += 1;
    }
    heroComp.visitedLog.insert(
        {(uint8_t)ObjectType::SCHOOL_OF_MAGIC, Global::goalIndex});
  }
  heroComp.visited.insert((uint8_t)ObjectType::SCHOOL_OF_MAGIC);
  schMComp.visitHeros.insert(heroComp.portrait);
  close();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;
  auto &gold = Global::resources[Global::playerId][6];

  if (gold < 1000) {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    b.func = close;
    b.disable = false;
    v.push_back(b);

  } else {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {bakW / 2 - 32 - 48, bakH - 60, 64, 30};
    b.func = receive;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["ICANCEL.DEF/0"];
    b.r = {bakW / 2 - 32 + 48, bakH - 60, 64, 30};
    b.func = close;
    b.disable = false;
    v.push_back(b);
  }

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2,
                          strPool[926 + (uint8_t)ObjectType::SCHOOL_OF_WAR]);
}

const static std::vector<SDL_FRect> primPosition = {
    {bakW / 2 - 41 - 82, bakH / 3, 82, 93},
    {bakW / 2 - 41 + 82, bakH / 3, 82, 93},
};

static void drawPrim() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};

  const static std::vector<SDL_Texture *> priTexture = {
      {Global::defCache["PSKILL.def/0"][2],
       Global::defCache["PSKILL.def/0"][3]}};
  for (uint8_t i = 0; i < priTexture.size(); i++) {
    auto texture = priTexture[i];
    posRect = {leftUp.x + primPosition[i].x, leftUp.y + primPosition[i].y,
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
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == SchoolMagSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool SchoolMagSys::run() {
  drawBackGround();
  drawPrim();
  drawButton();
  return true;
}

static bool clickPrim(uint8_t clickType) {
  auto &gold = Global::resources[Global::playerId][6];
  if (!visited() && gold >= 1000) {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    SDL_FRect posRect;
    for (uint8_t i = 0; i < primPosition.size(); i++) {
      posRect = primPosition[i];
      posRect.x += leftUp.x;
      posRect.y += leftUp.y;
      if (SDL_PointInRectFloat(&point, &posRect)) {
        if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
          Global::goalIndex = i;
        } else {
          HeroScrSys::showPrimComfirm(clickType, i + 2);
        }
        return true;
      }
    }
  }

  return false;
}

bool SchoolMagSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickPrim(clickType)) {
    return false;
  }
  return true;
}

bool SchoolMagSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickPrim(clickType)) {
    return true;
  }
  return true;
}

bool SchoolMagSys::keyUp(uint16_t key) {
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
