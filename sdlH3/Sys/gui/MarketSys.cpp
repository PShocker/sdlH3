#include "MarketSys.h"
#include "AdvMapSys.h"
#include "Cfg/ArtifactCfg.h"
#include "Comp/HeroComp.h"
#include "Comp/MarketComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/base/ArtifactPanelSys.h"
#include "Sys/gui/base/ArtifactsOfHeroSys.h"
#include "Sys/gui/base/CreaturesPanelSys.h"
#include "Sys/gui/base/PlayersPanelSys.h"
#include "Sys/gui/base/ResourcesPanelSys.h"
#include "Sys/gui/base/SliderSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "base/ResourcesPanelSys.h"
#include <array>
#include <cstdint>
#include <string>
#include <vector>

// 把金币转为资源
static uint32_t resConvert(uint32_t gold, uint8_t i, uint8_t makNum) {
  uint32_t r = gold;
  switch (i) {
  case 0:
  case 2: {
    r = r / 125;
    break;
  }
  case 1:
  case 3:
  case 4:
  case 5: {
    r = r / 250;
    break;
  }
  default: {
    break;
  }
  }
  return r;
}

// 把资源转为金币
static uint32_t resConvert2(uint8_t i, uint32_t num, uint8_t makNum) {
  uint32_t r = num;
  switch (i) {
  case 0:
  case 2: {
    r = r * 125;
    break;
  }
  case 1:
  case 3:
  case 4:
  case 5: {
    r = r * 250;
    break;
  }
  default: {
    break;
  }
  }
  return r;
}

static bool checkTrade() {
  bool r = false;
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    if (Global::makSliderNum != 0) {
      r = true;
    }
    break;
  }
  case Enum::MARKET::RES_SEND: {
    if (Global::makIndex[0] != 0xff && Global::makIndex[1] != 0xff) {
      r = true;
    }
    break;
  }
  case Enum::MARKET::ART_BUY: {
    if (Global::makIndex[0] != 0xff && Global::makIndex[1] != 0xff) {
      auto &mComp =
          World::registrys[World::level].get<MarketComp>(Global::goalEnt);
      auto id = mComp.artifacts[Global::makIndex[1]];
      auto cost = resConvert(ArtifactCfg::artCost[id], Global::makIndex[0], 10);
      if (Global::resources[Global::playerId][Global::makIndex[0]] >= cost) {
        r = true;
      }
    }
    break;
  }
  case Enum::MARKET::ART_SELL: {
    Global::makType = (uint8_t)Enum::MARKET::ART_BUY;
    break;
  }
  default:
    break;
  }
  return r;
}

static void close() { World::exitScrn(); }

static void changeType() {
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    Global::makType = (uint8_t)Enum::MARKET::RES_SEND;
    break;
  }
  case Enum::MARKET::RES_SEND: {
    Global::makType = (uint8_t)Enum::MARKET::RES_BUY;
    break;
  }
  case Enum::MARKET::ART_BUY: {
    Global::makType = (uint8_t)Enum::MARKET::ART_SELL;
    break;
  }
  case Enum::MARKET::ART_SELL: {
    Global::makType = (uint8_t)Enum::MARKET::ART_BUY;
    break;
  }
  default:
    break;
  }
  Global::makIndex[0] = Global::makIndex[1] = 0xff;
}

static void maxResource() { World::exitScrn(); }

static void trade() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    b.textures = Global::defCache["TPMRKBU1.DEF/0"];
    b.r = {18, 520, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["IRCBTNS.DEF/0"];
    b.r = {227, 520, 64, 32};
    b.func = maxResource;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["TPMRKB.DEF/0"];
    b.r = {307, 520, 64, 32};
    b.func = trade;
    b.disable = !checkTrade();
    v.push_back(b);

    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = close;
    b.disable = false;
    v.push_back(b);

    break;
  }
  case Enum::MARKET::RES_SEND: {
    b.textures = Global::defCache["TPMRKBU5.DEF/0"];
    b.r = {18, 520, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["IRCBTNS.DEF/0"];
    b.r = {227, 520, 64, 32};
    b.func = maxResource;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["TPMRKB.DEF/0"];
    b.r = {307, 520, 64, 32};
    b.func = trade;
    b.disable = !checkTrade();
    v.push_back(b);

    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = close;
    b.disable = false;
    v.push_back(b);

    break;
  }
  case Enum::MARKET::ART_BUY: {
    b.textures = Global::defCache["TPMRKBU3.DEF/0"];
    b.r = {18, 520, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["TPMRKB.DEF/0"];
    b.r = {268, 520, 64, 32};
    b.func = trade;
    b.disable = !checkTrade();
    v.push_back(b);

    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = close;
    b.disable = false;
    v.push_back(b);

    break;
  }
  case Enum::MARKET::ART_SELL: {
    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = close;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["TPMRKBU2.DEF/0"];
    b.r = {18, 520, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["TPMRKB.DEF/0"];
    b.r = {268, 520, 64, 32};
    b.func = trade;
    b.disable = !checkTrade();
    v.push_back(b);

    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = close;
    b.disable = false;
    v.push_back(b);

    break;
  }
  case Enum::MARKET::CRE_SELL: {
    b.textures = Global::defCache["TPMRKB.DEF/0"];
    b.r = {268, 520, 64, 32};
    b.func = trade;
    b.disable = !checkTrade();
    v.push_back(b);

    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = close;
    b.disable = false;
    v.push_back(b);

    break;
  }
  default:
    break;
  }
  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  posRect = {leftUp.x, leftUp.y, 601, 593};
  SDL_Texture *texture;
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    texture = Global::pcxCache["TPMrkReS.pcx"][Global::playerId];
    break;
  }
  case Enum::MARKET::RES_SEND: {
    texture = Global::pcxCache["TPMrkPtS.pcx"][Global::playerId];
    break;
  }
  case Enum::MARKET::ART_BUY: {
    texture = Global::pcxCache["TPMrkAbS.pcx"][Global::playerId];
    break;
  }
  case Enum::MARKET::ART_SELL: {
    texture = Global::pcxCache["TPMrkAsS.pcx"][Global::playerId];
    break;
  }
  case Enum::MARKET::CRE_SELL: {
    texture = Global::pcxCache["TPMrkCrS.pcx"][Global::playerId];
    break;
  }
  default:
    break;
  }
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 15,
                          strPool[926 + (uint8_t)ObjectType::BLACK_MARKET]);
}

static void drawButton() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == MarketSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawArts() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::ART_BUY: {
    auto &mComp =
        World::registrys[World::level].get<MarketComp>(Global::goalEnt);
    ArtifactPanelSys::draw(leftUp.x + 327, leftUp.y + 180, mComp.artifacts,
                           Global::makIndex[1]);
    if (Global::makIndex[0] != 0xff) {
      std::array<std::u16string, 7> r;
      for (uint8_t i = 0; i < 7; i++) {
        auto id = mComp.artifacts[i];
        auto cost = ArtifactCfg::artCost[id];
        r[i] = u"1/" + FreeTypeSys::str(
                           resConvert(cost * 2.5, Global::makIndex[0], 10));
      }
      ArtifactPanelSys::drawNum(leftUp.x + 327, leftUp.y + 180, r);
    }
    break;
  }
  case Enum::MARKET::ART_SELL: {
    // 绘制背包和装备栏并获取点击信息
    auto &heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    ArtifactsOfHeroSys::drawBackPack(&heroComp, leftUp.x - 297, leftUp.y + 53,
                                     Global::artPageIndex[0]);
    ArtifactsOfHeroSys::drawEquip(&heroComp, leftUp.x - 295, leftUp.y + 55);
    break;
  }
  default:
    break;
  }
}

static void drawSlider() {
  if ((Enum::MARKET)Global::makType == Enum::MARKET::RES_BUY ||
      (Enum::MARKET)Global::makType == Enum::MARKET::RES_SEND ||
      (Enum::MARKET)Global::makType == Enum::MARKET::CRE_SELL) {
    SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                      static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
    auto count = Global::resources[Global::playerId][Global::makIndex[0]];
    SliderSys::drawHor(leftUp.x + 230, leftUp.y + 489, 137,
                       (float)Global::makSliderNum / count);
  }
}

static void drawResource() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    ResourcesPanelSys::draw(leftUp.x + 38, leftUp.y + 180, Global::makIndex[0]);
    ResourcesPanelSys::draw(leftUp.x + 327, leftUp.y + 180,
                            Global::makIndex[1]);
    break;
  }
  case Enum::MARKET::RES_SEND: {
    ResourcesPanelSys::draw(leftUp.x + 39, leftUp.y + 182, Global::makIndex[0]);
    break;
  }
  case Enum::MARKET::ART_BUY: {
    ResourcesPanelSys::draw(leftUp.x + 38, leftUp.y + 182, Global::makIndex[0]);
    std::array<std::u16string, 7> r;
    for (uint8_t i = 0; i < 7; i++) {
      r[i] = FreeTypeSys::str(Global::resources[Global::playerId][i]);
    }
    ResourcesPanelSys::drawNum(leftUp.x + 38, leftUp.y + 182, r);
    break;
  }
  case Enum::MARKET::ART_SELL: {
    ResourcesPanelSys::draw(leftUp.x + 325, leftUp.y + 182,
                            Global::makIndex[1]);
    break;
  }
  case Enum::MARKET::CRE_SELL: {
    ResourcesPanelSys::draw(leftUp.x + 325, leftUp.y + 182,
                            Global::makIndex[1]);
    break;
  }
  default:
    break;
  }
}

static void drawPlayer() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    break;
  }
  case Enum::MARKET::RES_SEND: {
    PlayersPanelSys::draw(leftUp.x + 327, leftUp.y + 83, Global::makIndex[1]);
    break;
  }
  case Enum::MARKET::ART_BUY: {
    break;
  }
  case Enum::MARKET::ART_SELL: {
    break;
  }
  default:
    break;
  }
}

static void drawCreature() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  if ((Enum::MARKET)Global::makType == Enum::MARKET::CRE_SELL) {
    auto &heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    CreaturesPanelSys::draw(leftUp.x + 45, leftUp.y + 123, heroComp.creatures);
    if (Global::makIndex[0] != 0xff) {
      if (heroComp.creatures[Global::makIndex[0]].second != 0) {
        CreaturesPanelSys::drawBorder(leftUp.x + 45, leftUp.y + 123,
                                      Global::makIndex[0]);
      }
    }
  }
}

static void drawSelect() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    const std::vector<SDL_Point> slotsPos = {
        {141, 456},
        {430, 456},
    };
    auto textures = Global::defCache["RESOURCE.def/0"];
    for (auto i : {0, 1}) {
      if (Global::makIndex[i] == 0xff) {
        continue;
      }
      auto texture = textures[Global::makIndex[i]];
      posRect = {leftUp.x + slotsPos[i].x, leftUp.y + slotsPos[i].y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
    break;
  }
  case Enum::MARKET::RES_SEND: {
    const std::vector<SDL_Point> slotsPos = {
        {142, 458},
        {416, 451},
    };
    if (Global::makIndex[0] != 0xff) {
      auto textures = Global::defCache["RESOURCE.def/0"];
      auto texture = textures[Global::makIndex[0]];
      posRect = {leftUp.x + slotsPos[0].x, leftUp.y + slotsPos[0].y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
    if (Global::makIndex[1] != 0xff) {
      auto textures = Global::defCache["CREST58.def/0"];
      auto texture = textures[Global::makIndex[1]];
      posRect = {leftUp.x + slotsPos[1].x, leftUp.y + slotsPos[1].y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
    break;
  }
  case Enum::MARKET::ART_BUY: {
    if (Global::makIndex[0] != 0xff) {
      const std::vector<SDL_Point> slotsPos = {
          {142, 454},
          {424, 448},

      };
      if (Global::makIndex[0] != 0xff) {
        auto textures = Global::defCache["RESOURCE.def/0"];
        auto texture = textures[Global::makIndex[0]];
        posRect = {leftUp.x + slotsPos[0].x, leftUp.y + slotsPos[0].y,
                   static_cast<float>(texture->w),
                   static_cast<float>(texture->h)};
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      }
      if (Global::makIndex[1] != 0xff) {
        auto textures = Global::defCache["Artifact.def/0"];
        auto texture = textures[Global::makIndex[1]];
        posRect = {leftUp.x + slotsPos[1].x, leftUp.y + slotsPos[1].y,
                   static_cast<float>(texture->w),
                   static_cast<float>(texture->h)};
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      }
    }
    break;
  }
  case Enum::MARKET::ART_SELL: {
    if (Global::artPair.first != 0xff && Global::artPair.second != 0xffff) {
      if (Global::artBackClick) {
        ArtifactsOfHeroSys::drawBackPackBorder(leftUp.x - 297, leftUp.y + 53,
                                               Global::artPair.first);
      } else {
        ArtifactsOfHeroSys::drawEquipBorder(leftUp.x - 295, leftUp.y + 55,
                                            Global::artPair.first);
      }
      auto texture = Global::defCache["Artifact.def/0"][Global::artPair.second];
      posRect = {leftUp.x + 135, leftUp.y + 470, static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      // SDL_RenderFillRect(Window::renderer,  &posRect);
    }
    if (Global::makIndex[1] != 0xff) {
      const std::vector<SDL_Point> slotsPos = {
          {428, 480},
      };
      auto textures = Global::defCache["RESOURCE.def/0"];
      auto texture = textures[Global::makIndex[1]];
      posRect = {leftUp.x + slotsPos[0].x, leftUp.y + slotsPos[0].y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
    break;
  }
  case Enum::MARKET::CRE_SELL: {
    if (Global::makIndex[0] != 0xff) {
      auto &heroComp =
          World::registrys[World::level].get<HeroComp>(Global::heroEnt);
      auto cre = heroComp.creatures[Global::makIndex[0]];
      if (cre.second != 0 && cre.first != 0xffff) {
        auto texture = Global::defCache["TWCRPORT.def/0"][cre.first + 2];
        posRect = {leftUp.x + 128, leftUp.y + 450,
                   static_cast<float>(texture->w),
                   static_cast<float>(texture->h)};
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      }
    }
    if (Global::makIndex[1] != 0xff) {
      const std::vector<SDL_Point> slotsPos = {
          {428, 460},
      };
      auto textures = Global::defCache["RESOURCE.def/0"];
      auto texture = textures[Global::makIndex[1]];
      posRect = {leftUp.x + slotsPos[0].x, leftUp.y + slotsPos[0].y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
  }
  default:
    break;
  }
}

bool MarketSys::run() {
  drawBackGround();
  drawButton();
  drawSlider();
  drawResource();
  drawPlayer();
  drawArts();
  drawCreature();
  drawSelect();
  return true;
}

bool MarketSys::keyUp(uint16_t key) {
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
bool MarketSys::rightMouseUp(float x, float y) { return true; }

static bool clickFunc(uint8_t clickType) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};
  bool leftClick = clickType == (uint8_t)Enum::CLICKTYPE::L_UP;
  switch ((Enum::MARKET)Global::makType) {
  case Enum::MARKET::RES_BUY: {
    if (auto c = ResourcesPanelSys::click(leftUp.x + 38, leftUp.y + 180);
        c != 0xff) {
      if (leftClick) {
        Global::makIndex[0] = c;
      } else {
        HeroScrSys::showResConfirm(clickType, c);
      }
      return true;
    }
    if (auto c = ResourcesPanelSys::click(leftUp.x + 327, leftUp.y + 180);
        c != 0xff) {
      if (leftClick) {
        Global::makIndex[1] = c;
      } else {
        HeroScrSys::showResConfirm(clickType, c);
      }
      return true;
    }
    auto count = Global::resources[Global::playerId][Global::makIndex[0]];
    Global::makSliderNum = SliderSys::clickHor(
        leftUp.x + 230, leftUp.y + 489, 137, Global::makSliderNum, count);
    break;
  }
  case Enum::MARKET::RES_SEND: {
    if (auto c = ResourcesPanelSys::click(leftUp.x + 38, leftUp.y + 180);
        c != 0xff) {
      if (leftClick) {
        Global::makIndex[0] = c;
      } else {
        HeroScrSys::showResConfirm(clickType, c);
      }
      return true;
    }
    if (auto c = PlayersPanelSys::click(leftUp.x + 327, leftUp.y + 83);
        c != 0xff) {
      Global::makIndex[1] = c;
      return true;
    }
    auto count = Global::resources[Global::playerId][Global::makIndex[0]];
    Global::makSliderNum = SliderSys::clickHor(
        leftUp.x + 230, leftUp.y + 489, 137, Global::makSliderNum, count);
    break;
  }
  case Enum::MARKET::ART_BUY: {
    if (auto c = ResourcesPanelSys::click(leftUp.x + 38, leftUp.y + 180);
        c != 0xff) {
      if (leftClick) {
        Global::makIndex[0] = c;
      } else {
        HeroScrSys::showResConfirm(clickType, c);
      }
      return true;
    }
    if (auto c = ArtifactPanelSys::click(leftUp.x + 327, leftUp.y + 180);
        c != 0xff) {
      if (leftClick) {
        Global::makIndex[1] = c;
      } else {
        auto &mComp =
            World::registrys[World::level].get<MarketComp>(Global::goalEnt);
        HeroScrSys::showArtifactComfirm(mComp.artifacts[c]);
      }
      return true;
    }
    break;
  }
  case Enum::MARKET::ART_SELL: {
    // 绘制背包和装备栏并获取点击信息
    auto &heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    auto [backpackIndex, backpackArtId] = ArtifactsOfHeroSys::clickBackPack(
        &heroComp, leftUp.x - 297, leftUp.y + 53, Global::artPageIndex[0]);
    auto [equipIndex, equipArtId] = ArtifactsOfHeroSys::clickEquip(
        &heroComp, leftUp.x - 295, leftUp.y + 55);

    bool clickedBackpack = backpackIndex != 0xff;
    uint16_t targetArtId = clickedBackpack ? backpackArtId : equipArtId;
    if (!leftClick && targetArtId != 0xffff) {
      HeroScrSys::showArtifactComfirm(targetArtId);
      return true;
    }

    if (backpackIndex != 0xff) {
      Global::artPair = {backpackIndex, backpackArtId};
      Global::artBackClick = true;
      return true;
    } else if (equipIndex != 0xff) {
      Global::artPair = {equipIndex, equipArtId};
      Global::artBackClick = false;
      return true;
    }
    if (auto c = ResourcesPanelSys::click(leftUp.x + 325, leftUp.y + 182);
        c != 0xff) {
      Global::makIndex[1] = c;
      return true;
    }
    break;
  }
  case Enum::MARKET::CRE_SELL: {
    if (auto c = CreaturesPanelSys::click(leftUp.x + 45, leftUp.y + 123);
        c != 0xff) {
      Global::makIndex[0] = c;
      return true;
    }
    if (auto c = ResourcesPanelSys::click(leftUp.x + 325, leftUp.y + 182);
        c != 0xff) {
      Global::makIndex[1] = c;
      return true;
    }
  }
  default:
    break;
  }
  return false;
}

bool MarketSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 601) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 593) / 2)};

  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickFunc(clickType)) {
    return false;
  }
  return true;
}

bool MarketSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickFunc(clickType)) {
    return true;
  }
  return true;
}