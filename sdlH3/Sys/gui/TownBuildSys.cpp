#include "TownBuildSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Cfg/TownCfg.h"
#include "Comp/TempleComp.h"
#include "Comp/TownComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CursorSys.h"
#include "TownSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <string>

static void close() { World::exitScrn(); }

static void buy() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  World::exitScrn();
  World::exitScrn();
  World::iterateSystemsBak.push_back(World::iterateSystems);

  World::iterateSystems.push_back([=]() {
    townComp->buildings[Global::townBuildBid] =
        Ent::loadBuild(level, townEnt, Global::townBuildBid);
    return true;
  });
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};

  Global::fadeRect = {leftUp.x, leftUp.y, 800, 600};
  World::iterateSystems.push_back(World::enterFadeScrn);

  auto now = Window::dtNow;
  Global::fadeCallBack = [now, townComp, leftUp]() {
    auto build = Global::townBuildBid;
    auto townPoint = TownCfg::townPoint[townComp->id].at(build);
    auto texture =
        Global::pcxCache[TownCfg::townBorder[townComp->id].at(build)][0];
    if (Window::dtNow >= now + 2000) {
      SDL_SetTextureAlphaModFloat(texture, 1);
      return true;
    }
    SDL_FRect posRect = {leftUp.x + townPoint.x, leftUp.y + townPoint.y,
                         static_cast<float>(texture->w),
                         static_cast<float>(texture->h)};
    float t = (Window::dtNow % 1000) / 1000.0f; // 1秒周期
    // 产生渐变色
    float top = 1.0f - fabsf(2.0f * t - 1.0f);
    SDL_SetTextureAlphaModFloat(texture, top);
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    return false;
  };
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["IBUY30.DEF/0"];
  b.r = {45, 446, 64, 30};
  b.func = buy;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ICANCEL.DEF/0"];
  b.r = {290, 445, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 521) / 2};

  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);

  auto texture = Global::pcxCache["TPUBUILD.pcx"][Global::playerId];
  posRect = {leftUp.x, leftUp.y, 395, 521};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(17);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto titleStr =
      strPool[3799] + strPool[3043 + (int8_t)Global::townBuildBid * 2];
  FreeTypeSys::drawCenter(leftUp.x + 395 / 2, leftUp.y + 15, titleStr);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(248, 240, 216, 255);
  auto title2Str = strPool[3044 + (int8_t)Global::townBuildBid * 2];
  FreeTypeSys::drawCenter(leftUp.x + 395 / 2, leftUp.y + 150, title2Str);

  std::u16string title3Str;
  if (townComp->buildings.contains(Global::townBuildBid)) {
    title3Str =
        strPool[3800] + strPool[3043 + (int8_t)Global::townBuildBid * 2];
  } else {

    title3Str = strPool[3803];
  }
  FreeTypeSys::drawCenter(leftUp.x + 395 / 2, leftUp.y + 230, title3Str);

  auto tStr = TownCfg::townBuildIcon[townComp->id].at(Global::townBuildBid);
  texture = Global::pcxCache[tStr][0];
  posRect = {leftUp.x + 125, leftUp.y + 50, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
  //   auto strPool = *Lang::strPool[Global::langIndex];
  //   FreeTypeSys::setSize(13);
  //   FreeTypeSys::setColor(240, 224, 104, 255);
  //   FreeTypeSys::drawCenter(x, y - bakH / 2 + 15,
  //                           strPool[926 +
  //                           (uint8_t)ObjectType::TREASURE_CHEST]);

  return;
}

static void drawBuild() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 521) / 2};
  auto texture = Global::defCache["imrl82.def/0"][4];
  //   posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y,
  //   morPosition.w,
  //              morPosition.h};
  //   SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  //   SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  //   SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 521) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == TownBuildSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool TownBuildSys::run() {
  drawBackGround();
  drawBuild();
  drawButton();
  return true;
}

bool TownBuildSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 395) / 2,
                    (Global::viewPort.h - 521) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool TownBuildSys::keyUp(uint16_t key) {
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