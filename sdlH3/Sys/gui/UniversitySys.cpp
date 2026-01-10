#include "UniversitySys.h"
#include "AdvMapSys.h"
#include "Comp/HeroComp.h"
#include "Comp/UniversComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <unordered_map>
#include <vector>

static void clear() { Global::goalIndex = 0xff; }

static void close() {
  World::exitScrn();
  clear();
}

static void study() {
  auto universComp =
      World::registrys[World::level].get<UniversComp>(Global::goalEnt);
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  heroComp.secSkills.push_back(universComp.secSkills[Global::goalIndex]);
  clear();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  auto gold = Global::resources[Global::playerId][6];
  if (Global::goalIndex == 0xff) {
    b.textures = Global::defCache["iOKAY.def/0"];
    b.r = {200, 313, 64, 32};
    b.func = close;
    b.disable = false;
    v.push_back(b);

  } else {
    b.textures = Global::defCache["IBY6432.DEF/0"];
    b.r = {148, 299, 64, 32};
    b.func = study;
    if (gold < 1000) {
      b.disable = true;
    } else {
      b.disable = false;
    }
    v.push_back(b);

    b.textures = Global::defCache["ICANCEL.DEF/0"];
    b.r = {252, 299, 64, 32};
    b.func = clear;
    b.disable = false;
    v.push_back(b);
  }

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 465) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 388) / 2)};
  posRect = {leftUp.x, leftUp.y, 465, 388};
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 15,
                          strPool[926 + (uint8_t)ObjectType::UNIVERSITY]);
  if (Global::goalIndex == 0xff) {
    auto texture = Global::pcxCache["UNIVERS1.PCX"][Global::playerId];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    texture = Global::pcxCache["univbldg.pcx"][0];
    // texture = TextureComp::textureCacheComps.at("AVSuniv0.def").textures[0];
    posRect = {leftUp.x + 465 / 2 - 114 / 2, leftUp.y + 38, 114, 80};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  } else {
    auto texture = Global::pcxCache["UNIVERS2.PCX"][Global::playerId];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
}

const static std::vector<SDL_FRect> secPosition = {
    {54, 234, 44, 44},
    {158, 234, 44, 44},
    {262, 234, 44, 44},
    {366, 234, 44, 44},
};

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 465) / 2,
                    (Global::viewPort.h - 388) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == UniversitySys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawSecSkill() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 465) / 2,
                    (Global::viewPort.h - 388) / 2};
  auto universComp =
      World::registrys[World::level].get<UniversComp>(Global::goalEnt);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(12);
  FreeTypeSys::setColor(255, 255, 255, 255);
  if (Global::goalIndex == 0xff) {
    auto heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    std::unordered_map<uint8_t, uint8_t> heroSecMap;
    for (auto pair : heroComp.secSkills) {
      heroSecMap[pair.first] = pair.second;
    }
    for (uint8_t i = 0; i < 4; i++) {
      int8_t canStudy = 1;
      if (heroSecMap.contains(universComp.secSkills[i].first)) {
        canStudy = 0;
      }
      if (canStudy == 1) {
        if (heroComp.secSkills.size() == 8) {
          canStudy = -1;
        }
      }
      auto secSkillId = 3 * (universComp.secSkills[i].first + 1);
      auto texture = Global::defCache["SECSKILL.def/0"][secSkillId];
      posRect.x = (int)(leftUp.x + secPosition[i].x);
      posRect.y = (int)(leftUp.y + secPosition[i].y);
      posRect.w = secPosition[i].w;
      posRect.h = secPosition[i].h;
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      auto x = posRect.x;
      auto y = posRect.y;
      SDL_Texture *textures[3] = {Global::pcxCache["UNIVRED.PCX"][0],
                                  Global::pcxCache["UNIVGOLD.PCX"][0],
                                  Global::pcxCache["UNIVGREN.PCX"][0]};
      auto level = universComp.secSkills[i].second;
      auto index = universComp.secSkills[i].first;
      for (uint8_t m = 0; m < 2; m++) {
        texture = textures[canStudy + 1];
        posRect.x = x - 28;
        posRect.y = y - 22;
        posRect.w = texture->w;
        posRect.h = texture->h;
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        FreeTypeSys::drawCenter(posRect.x + posRect.w / 2, posRect.y,
                                strPool[1147 + index]);

        posRect.x = x - 28;
        posRect.y = y + 48;
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        FreeTypeSys::drawCenter(posRect.x + posRect.w / 2, posRect.y,
                                strPool[5 + level]);
      }
    }
  } else {
    auto secSkillId = 3 * (universComp.secSkills[Global::goalIndex].first + 1);
    auto texture = Global::defCache["SECSKILL.def/0"][secSkillId];
    posRect = {leftUp.x + 211, leftUp.y + 51, static_cast<float>(texture->w),
               static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    auto level = universComp.secSkills[Global::goalIndex].second;
    auto index = universComp.secSkills[Global::goalIndex].first;
    posRect = {leftUp.x + 179, leftUp.y + 28, 104, 21};
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2, posRect.y,
                            strPool[1147 + index]);
    posRect.y += 70;
    FreeTypeSys::drawCenter(posRect.x + posRect.w / 2, posRect.y,
                            strPool[5 + level]);
  }
}

bool UniversitySys::run() {
  drawBackGround();
  drawSecSkill();
  drawButton();
  return true;
}

static bool clickSec(uint8_t clickType) {
  SDL_FPoint leftUp{(Global::viewPort.w - 465) / 2,
                    (Global::viewPort.h - 388) / 2};
  SDL_FRect posRect;
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto universComp =
      World::registrys[World::level].get<UniversComp>(Global::goalEnt);
  auto heroComp = World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  std::unordered_map<uint8_t, uint8_t> heroSecMap;
  for (auto pair : heroComp.secSkills) {
    heroSecMap[pair.first] = pair.second;
  }
  for (uint8_t i = 0; i < secPosition.size(); i++) {
    posRect = secPosition[i];
    posRect.x += leftUp.x;
    posRect.y += leftUp.y;
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        int8_t canStudy = 1;
        if (heroSecMap.contains(universComp.secSkills[i].first)) {
          canStudy = 0;
        }
        if (canStudy == 1) {
          if (heroComp.secSkills.size() == 8) {
            canStudy = -1;
          }
        }
        if (canStudy == 1) {
          Global::goalIndex = i;
        }
      } else {
        auto id = universComp.secSkills[i].first;
        auto lvl = universComp.secSkills[i].second;
        HeroScrSys::showSecSkiComfirm(clickType, id, lvl);
      }
      return true;
    }
  }
  return false;
}

bool UniversitySys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 465) / 2,
                    (Global::viewPort.h - 388) / 2};
  SDL_FPoint point = {(float)(int)x, (float)(int)y};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickSec(clickType)) {
    return false;
  }

  return true;
}

bool UniversitySys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickSec(clickType)) {
    return false;
  }
  return true;
}

bool UniversitySys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    if (Global::goalIndex != 0xff) {
      Global::goalIndex = 0xff;
    } else {
      close();
    }
    break;
  }
  default:
    break;
  }
  return true;
}