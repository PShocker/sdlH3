#include "FreeGuildSys.h"
#include "AdvMapSys.h"
#include "Comp/HeroComp.h"
#include "Comp/PlayerIdComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static void upgrade() {}

static void close() {}

void FreeGuildSys::init() {
  buttons.clear();
  {
    Button button;
    button.textures = Global::defCache["iOKAY.def/0"];
    button.r = {208, 320, 64, 30};
    button.clickFunc = upgrade;
    button.disableFunc = []() { return false; };
    button.showFunc = []() { return true; };
    buttons.push_back(button);
  }
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  auto playerId =
      World::registrys[World::level].get<PlayerIdComp>(Global::heroEnt).id;
  auto texture = Global::pcxCache["APHLFTBK.PCX"][playerId];
  posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  auto oName = strPool[927 + ObjectType::FREELANCERS_GUILD];
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 15, oName);
}

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
}

static void drawCreature() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  auto heroComp =
      &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == FreeGuildSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, FreeGuildSys::buttons);
}

bool FreeGuildSys::run() {
  drawBackGround();
  drawCreature();
  drawButton();
  return true;
}

bool FreeGuildSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, FreeGuildSys::buttons,
                              clickType)) {
    return false;
  }
  return true;
}

bool FreeGuildSys::keyUp(uint16_t key) {
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
