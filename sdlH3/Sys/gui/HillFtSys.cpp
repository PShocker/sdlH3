#include "HillFtSys.h"
#include "AdvMapSys.h"
#include "Comp/HeroComp.h"
#include "Comp/PlayerIdComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static void upgrade() {}

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {294, 278, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
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
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::drawCenter(leftUp.x + 652 / 2, leftUp.y + 15, strPool[959]);
}

static void drawCreature() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  auto heroComp =
      &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  for (uint8_t i = 0; i < heroComp->creatures.size(); i++) {
    auto [id, count] = heroComp->creatures[i];
    if (count == 0) {
      posRect = {leftUp.x + 107 + i * 76, leftUp.y + 171, 58, 29};
      auto texture = Global::defCache["APHLF1R.def/0"][2];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      continue;
    }
    posRect = {leftUp.x + 107 + i * 76, leftUp.y + 60, 58, 64};
    auto texture = Global::defCache["TWCRPORT.def/0"][id + 2];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    posRect = {leftUp.x + 107 + i * 76, leftUp.y + 171, 58, 29};
    std::vector<SDL_Texture *> textures;
    if (CreatureCfg::creatureUpgradeTo.at(id) != -1) {
      textures = Global::defCache["APHLF1G.def/0"];
    } else {
      textures = Global::defCache["APHLF1Y.def/0"];
    }
    texture = textures[0];
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (Window::mouseState & SDL_BUTTON_LMASK) {
        texture = textures[1];
      }
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == HillFtSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool HillFtSys::run() {
  drawBackGround();
  drawCreature();
  drawButton();
  return true;
}

static bool clickCre(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto heroComp =
      &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  for (uint8_t i = 0; i < heroComp->creatures.size(); i++) {
    auto [id, count] = heroComp->creatures[i];
    if (count == 0) {
      continue;
    }
    posRect = {leftUp.x + 107 + i * 76, leftUp.y + 60, 58, 64};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      auto creature = heroComp->creatures[i];
      uint8_t creType;
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        creType = (uint8_t)Enum::CRETYPE::MOD_HERO;
      } else {
        creType = (uint8_t)Enum::CRETYPE::POP_HERO;
      }
      World::enterCreature({World::level, Global::heroEnt}, creature, creType);
      return true;
    }
  }
  return false;
}

bool HillFtSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 652) / 2,
                    (Global::viewPort.h - 348) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool HillFtSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickCre(clickType)) {
    return false;
  }
  return true;
}

bool HillFtSys::keyUp(uint16_t key) {
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
