#include "TavernSys.h"
#include "AdvMapSys.h"

#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/TownComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "Set/HeroSet.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/VideoSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <cstdint>

void TavernSys::refreshHero(uint8_t playerId, uint8_t index) {
  int arr[101];
  for (int i = 0; i <= 100; ++i) {
    arr[i] = i;
  }
  std::set<int> numbers(arr, arr + 101);
  for (auto m : {0, 1}) {
    auto &registry = World::registrys[m];
    for (auto ent : registry.view<HeroComp>()) {
      auto hComp = registry.get<HeroComp>(ent);
      numbers.erase(hComp.portrait);
    }
  }
  if (numbers.size() > 0) {
    int random = rand() % numbers.size();
    auto it = std::next(numbers.begin(), random);

    auto heroEnt = World::registrys[0].create();
    auto hId = *it;
    auto hComp = Ent::loadDefaultHeroComp(hId);
    World::registrys[0].emplace<HeroComp>(heroEnt, hComp);

    numbers.erase(it);
    Global::tavernHeros[playerId][index] = heroEnt;
  }
}

static bool canBuy() {
  bool r = false;
  auto &gold = Global::resources[Global::playerId][6];
  if (gold >= 2500) {
    r = true;
  }
  if (Global::goalIndex == 0xff) {
    r = false;
  }
  if (Global::heroEnt == entt::null) {
    auto [level, townEnt] = Global::townScnPair;
    auto &registry = World::registrys[level];
    auto &tComp = registry.get<TownComp>(townEnt);
    if (tComp.heroEnt[1].has_value()) {
      r = false;
    }
  }
  return r;
}

static void close() {
  VideoSys::close();
  World::exitScrn();
}

static void buy() {
  auto registry = &World::registrys[World::level];
  Global::fadeCallBack = []() {
    World::LMouseUpSysBak.pop_back();
    World::LMouseDownSysBak.pop_back();
    World::RMouseUpSysBak.pop_back();
    World::RMouseDownSysBak.pop_back();
    World::keyUpSysBak.pop_back();
    Global::cursorBack.pop_back();
    return true;
  };
  VideoSys::close();
  World::iterateSystems.pop_back();
  World::iterateSystems.pop_back();
  World::iterateSystems.pop_back();
  World::iterateSystemsBak.push_back(World::iterateSystems);
  World::iterateSystemsBak.back().push_back(CursorSys::run);
  World::iterateSystems.push_back([registry]() {
    auto ent = Global::tavernHeros[Global::playerId][Global::goalIndex];
    auto hComp = World::registrys[0].get<HeroComp>(ent);
    entt::entity heroEnt;
    if (Global::heroEnt == entt::null) {
      auto [level, townEnt] = Global::townScnPair;
      auto &registry = World::registrys[level];
      auto oComp = registry.get<ObjectComp>(townEnt);
      auto x = oComp.x + oComp.accessTiles[0].first + 1;
      auto y = oComp.y + oComp.accessTiles[0].second;
      heroEnt =
          Ent::loadHero(hComp, Global::playerId, x, y, World::level, 2, 0);
      auto &tComp = registry.get<TownComp>(townEnt);
      tComp.heroEnt[1] = heroEnt;
      SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                        (Global::viewPort.h - 600) / 2};
      Global::fadeRect = {leftUp.x, leftUp.y, 800, 600};
    } else {
      auto x = registry->get<ObjectComp>(Global::goalEnt).x;
      auto y = registry->get<ObjectComp>(Global::goalEnt).y;
      heroEnt =
          Ent::loadHero(hComp, Global::playerId, x, y, World::level, 2, 0);
      Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                          Global::viewPort.h - 47};
    }
    Global::heros[Global::playerId].push_back({World::level, heroEnt});
    Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;

    World::registrys[0].destroy(ent);
    TavernSys::refreshHero(Global::playerId, Global::goalIndex);
    return true;
  });
  World::iterateSystems.push_back(World::enterFadeScrn);
  return;
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["TPTAV01.DEF/0"];
  b.r = {272, 355, 96, 54};
  b.func = buy;
  b.disable = !canBuy();
  v.push_back(b);

  b.textures = Global::defCache["ICANCEL.DEF/0"];
  b.r = {310, 428, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["TPTAV02.DEF/0"];
  b.r = {22, 428, 64, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 504) / 2};
  auto texture = Global::pcxCache["TpTavern.pcx"][Global::playerId];
  posRect = {leftUp.x, leftUp.y, 395, 504};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(16);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 15,
                          strPool[927 + (uint8_t)ObjectType::TAVERN]);
  FreeTypeSys::setSize(17);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2 - 50, leftUp.y + 272,
                          strPool[3037]);
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(248, 240, 216, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 190,
                          strPool[2885]);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 210,
                          Global::tavernStr);
  FreeTypeSys::drawCenter(leftUp.x + 320, leftUp.y + 317, 2500);
}

const static std::vector<SDL_FRect> PorPosition = {
    {72, 299, 58, 64},
    {162, 299, 58, 64},
};

static void drawPortraits() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 504) / 2};
  auto &registry = World::registrys[World::level];

  for (uint8_t i = 0; i < 2; i++) {
    if (Global::tavernHeros[Global::playerId][i] == entt::null) {
      continue;
    }
    auto heroEnt = Global::tavernHeros[Global::playerId][i];
    auto heroComp = &World::registrys[0].get<HeroComp>(heroEnt);
    auto lagerPor = HeroSet::fullHeros[heroComp->portrait]->largePor;
    auto texture = Global::pcxCache[lagerPor][0];
    posRect = {leftUp.x + PorPosition[i].x, leftUp.y + PorPosition[i].y,
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (Global::goalIndex == i) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
      SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
      SDL_RenderRect(Window::renderer, &posRect);

      auto strPool = *Lang::strPool[Global::langIndex];

      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(248, 240, 216, 255);
      auto str = strPool[1262 + heroComp->portrait] + strPool[3038] +
                 FreeTypeSys::str(heroComp->level) + strPool[2177] +
                 strPool[2178 + heroComp->subId] + u",";
      FreeTypeSys::drawCenter(Global::viewPort.w / 2 - 45, leftUp.y + 370, str);

      auto equipNum = 0;
      for (auto i = 0; i < heroComp->artifacts.size(); i++) {
        if (i == Enum::SPELLBOOK || i == Enum::MACH1 || i == Enum::MACH2 ||
            i == Enum::MACH3 || i == Enum::MACH4) {
          continue;
        }
        if (heroComp->artifacts[i] != 0xffff) {
          equipNum++;
        }
      }
      equipNum += heroComp->artifactsInBackpack.size();
      str = strPool[3039] + FreeTypeSys::str(equipNum) + strPool[3040];
      FreeTypeSys::drawCenter(Global::viewPort.w / 2 - 45, leftUp.y + 388, str);
    }
  }
}

static void drawButton() {

  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 504) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 3];
  auto top = (*topFunc.target<bool (*)()>() == TavernSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool TavernSys::run() {
  drawBackGround();
  drawPortraits();
  drawButton();
  return true;
}

bool TavernSys::keyUp(uint16_t key) {
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

static bool clickHero(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 504) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < PorPosition.size(); i++) {
    posRect = PorPosition[i];
    posRect.x += leftUp.x;
    posRect.y += leftUp.y;
    if (SDL_PointInRectFloat(&point, &posRect)) {
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        Global::goalIndex = i;
      } else {
        auto heroEnt = Global::tavernHeros[Global::playerId][i];
        World::enterHeroScrn(0, heroEnt, (uint8_t)Enum::SCNTYPE::POP);
      }
      return true;
    }
  }
  return false;
}

bool TavernSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 504) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickHero(clickType)) {
    return false;
  }
  return true;
}

bool TavernSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickHero(clickType)) {
    return false;
  }
  return true;
}