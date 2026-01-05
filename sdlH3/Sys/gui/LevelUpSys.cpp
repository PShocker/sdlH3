#include "LevelUpSys.h"
#include "Cfg/HeroCfg.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <random>
#include <vector>

void LevelUpSys::studySecSki(HeroComp &heroComp, uint8_t sId) {
  auto level = sId % 3;
  sId = (sId / 3) - 1;
  int8_t r = -1;
  for (uint8_t i = 0; i < heroComp.secSkills.size(); i++) {
    if (heroComp.secSkills[i].first == sId) {
      r = i;
      break;
    }
  }
  if (r != -1) {
    heroComp.secSkills[r].second += 1;
  } else if (sId != 84) {
    heroComp.secSkills.push_back({sId, 0});
  }
}

static void receive() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  heroComp.level += 1;
  heroComp.primSkills[Global::lvlPrimIndex] += 1;
  uint8_t sId = Global::goalIndex == 0 ? Global::lvlSecPair.first
                                       : Global::lvlSecPair.second;

  LevelUpSys::studySecSki(heroComp, sId);
  if (!LevelUpSys::prepareLvlUp(heroComp)) {
    World::exitScrn();
  }
  Global::goalIndex = 0;
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {297, 413, 82, 93};
  b.func = receive;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  posRect = {leftUp.x, leftUp.y, 385, 470};
  auto texture = Global::pcxCache["lvlupbkg.pcx"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == LevelUpSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

const static SDL_FRect porPosition = {170, 66, 58, 64};

static void drawHeroPor() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  auto heroComp = World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto texture = Global::pcxCache[HeroCfg::heroLargePor[heroComp.portrait]][0];
  posRect = {leftUp.x + porPosition.x, leftUp.y + porPosition.y, porPosition.w,
             porPosition.h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

const static SDL_FRect primPosition = {174, 190, 42, 42};

static void drawPrimSki() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  auto texture = Global::defCache["PSKIL42.def/0"][Global::lvlPrimIndex];
  posRect = {leftUp.x + primPosition.x, leftUp.y + primPosition.y,
             primPosition.w, primPosition.h};
  auto strPool = *Lang::strPool[Global::langIndex];

  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  FreeTypeSys::drawCenter(posRect.x + 21, posRect.y + 56,
                          strPool[1 + Global::lvlPrimIndex] + u"+1");
}

const static std::vector<SDL_FRect> secSkiPosition2 = {
    {126, 320, 44, 44},
    {214, 320, 44, 44},
};

const static std::vector<SDL_FRect> secSkiPosition1 = {
    {170, 320, 44, 44},
};

static void drawSecSki() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  if (Global::lvlSecPair.first == 0xff && Global::lvlSecPair.second == 0xff) {
    return;
  }
  int8_t size = 0;
  if (Global::lvlSecPair.first != 0xff) {
    size += 1;
  }
  if (Global::lvlSecPair.second != 0xff) {
    size += 1;
  }
  std::vector<SDL_FRect> secSkiPosition;
  std::vector<uint8_t> secSkiIndex;
  if (size == 2) {
    secSkiPosition = secSkiPosition2;
    secSkiIndex = {Global::lvlSecPair.first, Global::lvlSecPair.second};
  } else {
    secSkiPosition = secSkiPosition1;
    secSkiIndex = {Global::lvlSecPair.first};
  }
  for (auto i = 0; i < secSkiPosition.size(); i++) {
    auto texture = Global::defCache["SECSKILL.def/0"][secSkiIndex[i]];
    posRect = {leftUp.x + secSkiPosition[i].x, leftUp.y + secSkiPosition[i].y,
               secSkiPosition[i].w, secSkiPosition[i].h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (Global::goalIndex == i) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
    auto level = secSkiIndex[i] % 3;
    auto index = secSkiIndex[i] / 3 - 1;
    FreeTypeSys::drawCenter(posRect.x + 22, posRect.y + 46, strPool[5 + level]);
    FreeTypeSys::drawCenter(posRect.x + 22, posRect.y + 64,
                            strPool[1147 + index]);
  }
}
bool LevelUpSys::run() {
  drawBackGround();
  drawButton();
  drawHeroPor();
  drawPrimSki();
  drawSecSki();
  return true;
}

bool LevelUpSys::prepareLvlUp(HeroComp &heroComp) {
  const auto randomId = [](std::vector<uint8_t> &v) {
    std::discrete_distribution<> dist(v.begin(), v.end());
    uint8_t r = dist(Global::gen);
    v[r] = 0;
    return r;
  };
  auto level = heroComp.level;
  auto exp = heroComp.exp;
  if (exp >= HeroCfg::heroLevelExp[level]) {
    auto primChance = HeroCfg::heroLowLevelChance.at(heroComp.subId);
    Global::lvlPrimIndex = randomId(primChance);
    auto secChance = HeroCfg::heroSecondarySkills.at(heroComp.subId);
    std::vector<uint8_t> secChance2;
    secChance2.assign(28, 0);
    uint8_t r = 0;
    for (auto secPair : heroComp.secSkills) {
      secChance[secPair.first] = 0;
      if (secPair.second != 2) {
        secChance2[secPair.first] = secPair.second + 1;
        r++;
      }
    }
    auto secChance2Bak = secChance2;
    if (heroComp.secSkills.size() < 8) {
      switch (r) {
      case 0: {
        Global::lvlSecPair.first = 3 * (randomId(secChance) + 1);
        Global::lvlSecPair.second = 3 * (randomId(secChance) + 1);
        break;
      }
      default: {
        auto sId = randomId(secChance2);
        sId = secChance2Bak[sId] + 3 * (sId + 1);
        Global::lvlSecPair.first = sId;
        Global::lvlSecPair.second = 3 * (randomId(secChance) + 1);
        break;
      }
      }
    } else {
      switch (r) {
      case 0: {
        Global::lvlSecPair = {0xff, 0xff};
        break;
      }
      case 1: {
        auto sId = randomId(secChance2);
        sId = secChance2Bak[sId] + 3 * (sId + 1);
        Global::lvlSecPair = {sId, 0xff};
        break;
      }
      default: {
        auto sId = randomId(secChance2);
        sId = secChance2Bak[sId] + 3 * (sId + 1);
        Global::lvlSecPair.first = sId;
        sId = randomId(secChance2);
        sId = secChance2Bak[sId] + 3 * (sId + 1);
        Global::lvlSecPair.second = sId;
        break;
      }
      }
    }
    return true;
  }
  return false;
}

bool LevelUpSys::keyUp(uint16_t key) { return false; }

static bool clickHeroPor(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + porPosition.x, leftUp.y + porPosition.y, porPosition.w,
             porPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (leftClick) {
      World::enterHeroScrn(World::level, Global::heroEnt,
                           (uint8_t)Enum::SCNTYPE::MOD);
    } else {
      World::enterHeroScrn(World::level, Global::heroEnt,
                           (uint8_t)Enum::SCNTYPE::POP);
    }
  }
  return false;
}

bool LevelUpSys::rightMouseUp(float x, float y) { return true; }

static bool clickSecSki(bool leftClick) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  int8_t size = 0;
  if (Global::lvlSecPair.first != 0xff) {
    size += 1;
  }
  if (Global::lvlSecPair.second != 0xff) {
    size += 1;
  }
  std::vector<SDL_FRect> secSkiPosition;
  std::vector<uint8_t> secSkiIndex;
  if (size == 2) {
    secSkiPosition = secSkiPosition2;
    secSkiIndex = {Global::lvlSecPair.first, Global::lvlSecPair.second};
  } else {
    secSkiPosition = secSkiPosition1;
    secSkiIndex = {Global::lvlSecPair.first};
  }
  for (auto i = 0; i < secSkiPosition.size(); i++) {
    posRect = {leftUp.x + secSkiPosition[i].x, leftUp.y + secSkiPosition[i].y,
               secSkiPosition[i].w, secSkiPosition[i].h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (leftClick) {
        Global::goalIndex = i;
      } else {
        auto level = secSkiIndex[i] % 3;
        auto index = secSkiIndex[i] / 3 - 1;
        HeroScrSys::showSecSkiComfirm(leftClick, index, level);
      }
      return true;
    }
  }
  return false;
}

bool LevelUpSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 385) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 470) / 2)};
  if (clickSecSki(true)) {
    return false;
  }
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool LevelUpSys::rightMouseDown(float x, float y) {
  if (clickSecSki(false)) {
    return false;
  }
  if (clickHeroPor(false)) {
    return false;
  }
  return true;
}