#include "IdolFortuneSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/HeroComp.h"
#include "Comp/IdolFortuneComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static bool visited() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  if (heroComp.visited.contains(ObjectType::IDOL_OF_FORTUNE)) {
    return true;
  } else {
    return false;
  }
}

static void receive() {
  World::exitScrn();
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  heroComp.visited.insert(ObjectType::IDOL_OF_FORTUNE);
  auto &oComp = World::registrys[World::level].get<ObjectComp>(Global::goalEnt);
  heroComp.visitedIndex.insert(oComp.index);
  if (!visited()) {
    {
      AdventureBonus bonus = {
          .src = ObjectType::FOUNTAIN_OF_YOUTH,
          .type = Enum::ADVENTURE_MORALE,
          .subType = 0,
          .val = 1,
      };
      heroComp.adventureBonus.insert({Enum::ADVENTURE_MORALE, bonus});
    }
  }
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> buttons;
  {
    Button button;
    button.textures = Global::defCache["iOKAY.def/0"];
    button.r = {bakW / 2 - 32, bakH - 60, 64, 30};
    button.clickFunc = receive;
    button.disableFunc = []() { return false; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }
  return buttons;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto oName = strPool[927 + ObjectType::IDOL_OF_FORTUNE];
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15, oName);
  return;
}

const SDL_FRect lukPosition = {bakW / 2 - 41, bakH / 3, 82, 93};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  if (!visited()) {
    auto texture = Global::defCache["ilck82.def/0"][4];
    posRect = {leftUp.x + lukPosition.x, leftUp.y + lukPosition.y,
               lukPosition.w, lukPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == IdolFortuneSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, buttonInfo());
}

bool IdolFortuneSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickLuk() {
  if (!visited()) {
    SDL_FRect posRect;
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    posRect = {leftUp.x + lukPosition.x, leftUp.y + lukPosition.y,
               lukPosition.w, lukPosition.h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      return true;
    }
  }
  return false;
}

bool IdolFortuneSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, buttonInfo(), clickType)) {
    return false;
  }
  return true;
}

bool IdolFortuneSys::keyUp(uint16_t key) {
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