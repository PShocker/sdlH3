#include "HeroScrSys.h"
#include "AdvMapSys.h"
#include "BMPFont/BMPFont.h"
#include "Cfg/ArtifactCfg.h"
#include "Cfg/HeroCfg.h"
#include "Comp/HeroComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui//base/ArtifactsOfHeroSys.h"
#include "Sys/gui/CursorSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <algorithm>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

static void close() {
  auto [index, artId] = Global::artPair;
  if (artId != 0xffff) {
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    std::vector<uint16_t> &artifactsBack = heroComp->artifactsInBackpack;
    std::vector<uint16_t> &artifacts = heroComp->artifacts;
    if (Global::artClick) {
      artifactsBack.insert(artifactsBack.begin() + index,
                           Global::artPair.second);
    } else {
      artifacts[index] = artId;
    }
    Global::artPair = {0xff, 0xffff};
  }
  World::exitScrn();
}

static void dismiss() {
  Global::confirmCallBack = []() {
    Global::fadeCallBack = []() {
      for (uint8_t i = 0; i < 2; i++) {
        World::LMouseUpSysBak.pop_back();
        World::LMouseDownSysBak.pop_back();
        World::RMouseUpSysBak.pop_back();
        World::RMouseDownSysBak.pop_back();
        World::keyUpSysBak.pop_back();
        Global::cursorBack.pop_back();
      }
      return true;
    };
    World::iterateSystems.pop_back();
    World::iterateSystems.pop_back();
    World::iterateSystems.pop_back();
    World::iterateSystemsBak.push_back(World::iterateSystems);
    World::iterateSystemsBak.back().push_back(CursorSys::run);
    World::iterateSystems.push_back([]() {
      auto [level, heroEnt] = Global::heroScnPair;
      for (uint8_t i = 0; i < Global::heros[Global::playerId].size(); i++) {
        if (Global::heros[Global::playerId][i].second == heroEnt &&
            Global::heros[Global::playerId][i].first == level) {
          Global::heros[Global::playerId].erase(
              Global::heros[Global::playerId].begin() + i);
          if (Global::herosIndex[Global::playerId] == i) {
            Global::herosIndex[Global::playerId] = 0xff;
          }
          break;
        }
      }
      auto heroComp = &World::registrys[level].get<HeroComp>(heroEnt);
      if (heroComp->curEnt.has_value()) {
        auto curEnt = heroComp->curEnt.value();
        if (auto townComp =
                World::registrys[World::level].try_get<TownComp>(curEnt)) {
          for (auto &ent : townComp->heroEnt) {
            if (ent == heroEnt) { // std::optional 支持直接比较
              ent = std::nullopt;
              break;
            }
          }
        }
      }
      for (auto pathEnt : heroComp->pathEnts) {
        World::registrys[World::level].destroy(pathEnt);
      }
      World::registrys[World::level].destroy(heroComp->flagEnt);
      World::registrys[World::level].destroy(heroEnt);
      World::needSort = true;
      Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
      if (Global::advPages[Global::playerId].first > 0) {
        Global::advPages[Global::playerId].first -= 1;
      }
      return true;
    });
    Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                        Global::viewPort.h - 47};
    World::iterateSystems.push_back(World::enterFadeScrn);
  };
  Global::confirmOnlyOK = false;
  Global::confirmdraw = []() {

  };
  World::enterConfirm(410, 200, ((uint8_t)Enum::SCNTYPE::MOD));
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  auto strPool = *Lang::strPool[Global::langIndex];

  b.textures = Global::defCache["hsbtns.DEF/0"];
  b.r = {609, 516, 52, 36};
  b.func = close;
  b.disable = false;
  b.title = u"";
  b.info = strPool[2880];
  v.push_back(b);

  b.textures = Global::defCache["hsbtns4.DEF/0"];
  b.r = {314, 429, 52, 36};
  b.func = close;
  b.disable = false;
  b.title = u"";
  b.info = strPool[2859];
  v.push_back(b);

  b.textures = Global::defCache["hsbtns2.DEF/0"];
  b.r = {534, 429, 52, 36};
  b.func = dismiss;
  b.disable = false;
  b.info = strPool[2866];
  v.push_back(b);

  b.textures = Global::defCache["hsbtns6.DEF/0"];
  b.r = {481, 483, 52, 36};
  b.func = close;
  b.disable = false;
  b.info = strPool[2870];
  v.push_back(b);

  b.textures = Global::defCache["hsbtns7.DEF/0"];
  b.r = {481, 519, 52, 36};
  b.func = close;
  b.disable = false;
  b.info = strPool[2871];
  v.push_back(b);

  b.textures = Global::defCache["hsbtns8.DEF/0"];
  b.r = {539, 483, 52, 36};
  b.func = close;
  b.disable = false;
  b.info = strPool[2876];
  v.push_back(b);

  // split
  b.textures = Global::defCache["hsbtns9.DEF/0"];
  b.r = {539, 519, 52, 36};
  b.func = []() {
    Global::splitOn = true;
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    Global::splitCre[0] = &heroComp->creatures.at(Global::heroScnIndex);
  };
  if (Global::heroScnIndex != 0xff) {
    b.disable = false;
  } else {
    b.disable = true;
  }
  b.info = strPool[2879];
  v.push_back(b);

  if (Global::heroScnType == (uint8_t)Enum::SCNTYPE::POP) {
    for (auto &b : v) {
      b.disable = true;
    }
  }

  return v;
}

static bool clickEquip(uint8_t clickType) {
  const SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                          (Global::viewPort.h - 586) / 2};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);

  auto r = ArtifactsOfHeroSys::clickBackPack(heroComp, leftUp.x, leftUp.y);

  // 绘制背包和装备栏并获取点击信息
  auto [backpackIndex, backpackArtId] = ArtifactsOfHeroSys::clickBackPack(
      heroComp, leftUp.x, leftUp.y, Global::artPageIndex[0]);
  auto [equipIndex, equipArtId] =
      ArtifactsOfHeroSys::clickEquip(heroComp, leftUp.x, leftUp.y);

  // 处理选中物品的绘制
  auto &[selectedIndex, selectedArtId] = Global::artPair;

  // 处理物品交互逻辑
  bool clickedBackpack = backpackIndex != 0xff;
  bool clickedEquipment = equipIndex != 0xff && !clickedBackpack;

  if (!clickedBackpack && !clickedEquipment)
    return false;

  uint8_t targetIndex = clickedBackpack ? backpackIndex : equipIndex;
  uint16_t targetArtId = clickedBackpack ? backpackArtId : equipArtId;
  if (!(clickType == (uint8_t)Enum::CLICKTYPE::L_DOWN) &&
      targetArtId != 0xffff) {
    HeroScrSys::showArtifactComfirm(targetArtId);
    return true;
  }
  bool isBackpackOperation = clickedBackpack;
  auto &artifactsBack = heroComp->artifactsInBackpack;
  auto &artifacts = heroComp->artifacts;

  if (selectedArtId != 0xffff) {
    // 放置物品
    if (isBackpackOperation) {
      if (targetIndex > artifactsBack.size()) {
        artifactsBack.resize(targetIndex, 0xffff);
      }
      if (artifactsBack[targetIndex] == 0xffff) {
        artifactsBack[targetIndex] = selectedArtId;
      } else {
        artifactsBack.insert(artifactsBack.begin() + targetIndex,
                             selectedArtId);
      }
      selectedArtId = 0xffff;
    } else {
      auto validSlots = ArtifactCfg::artSlot.at(selectedArtId);
      if (validSlots[targetIndex]) {
        if (artifacts[targetIndex] != 0xffff) {
          auto targetArtId = artifacts[targetIndex];
          artifacts[targetIndex] = selectedArtId;
          Global::artPair = {artifactsBack.size(), targetArtId};
          Global::artClick = true;
          return true;
        } else {
          artifacts[targetIndex] = selectedArtId;
          selectedArtId = 0xffff;
        }
      } else {
        return true;
      }
    }
    Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
    return true;
  } else if (targetArtId != 0xffff) {
    // 拾取物品
    Global::artPair = {targetIndex, targetArtId};
    Global::artClick = isBackpackOperation;

    if (isBackpackOperation) {
      artifactsBack.erase(artifactsBack.begin() + targetIndex);
    } else {
      artifacts[targetIndex] = 0xffff;
    }
    Global::cursorType = (uint8_t)Enum::CURSOR::HIDE;
    return true;
  }
  return true;
}

static bool clickCre(uint8_t clickType) {
  constexpr float CREATURE_WIDTH = 58.0f;
  constexpr float CREATURE_HEIGHT = 64.0f;
  constexpr float START_X = 14.0f;
  constexpr float START_Y = 484.0f;
  constexpr float SPACING = 66.0f;
  constexpr uint8_t INVALID_INDEX = 0xFF;
  constexpr uint8_t LEFT_CLICK = static_cast<uint8_t>(Enum::CLICKTYPE::L_UP);
  constexpr uint8_t POP_HERO = static_cast<uint8_t>(Enum::CRETYPE::POP_HERO);
  constexpr uint8_t MOD_HERO = static_cast<uint8_t>(Enum::CRETYPE::MOD_HERO);

  const SDL_FPoint mousePos = {
      static_cast<float>(static_cast<int>(Window::mouseX)),
      static_cast<float>(static_cast<int>(Window::mouseY))};

  const SDL_FPoint panelPos = {(Global::viewPort.w - 672.0f) * 0.5f,
                               (Global::viewPort.h - 586.0f) * 0.5f};

  const auto &[level, heroEnt] = Global::heroScnPair;
  auto &heroComp = World::registrys[level].get<HeroComp>(heroEnt);
  auto &creatures = heroComp.creatures;

  for (uint8_t i = 0; i < creatures.size(); ++i) {
    const SDL_FRect creatureRect = {panelPos.x + START_X + i * SPACING,
                                    panelPos.y + START_Y, CREATURE_WIDTH,
                                    CREATURE_HEIGHT};

    if (!SDL_PointInRectFloat(&mousePos, &creatureRect)) {
      continue;
    }

    auto &currentCreature = creatures[i];

    if (clickType == LEFT_CLICK) {
      // 左键点击处理逻辑
      if (Global::splitOn) {
        auto *crePtr = &currentCreature;
        if (Global::splitCre[0] != crePtr &&
            (crePtr->second == 0 ||
             crePtr->first == Global::splitCre[0]->first)) {
          Global::splitCre[1] = crePtr;
          World::enterSplitCre();
          Global::splitOn = false;
          Global::heroScnIndex = INVALID_INDEX;
        }
        return true;
      }

      if (Global::heroScnIndex == i) {
        World::enterCreature(Global::heroScnPair, currentCreature, MOD_HERO);
        Global::heroScnIndex = INVALID_INDEX;
        return true;
      }

      if (Global::heroScnIndex == INVALID_INDEX) {
        if (currentCreature.second != 0) {
          Global::heroScnIndex = i;
        }
        return true;
      }

      // 交换或合并生物
      auto &selectedCreature = creatures[Global::heroScnIndex];
      if (currentCreature.second == 0 ||
          currentCreature.first != selectedCreature.first) {
        std::swap(currentCreature, selectedCreature);
      } else {
        currentCreature.second += selectedCreature.second;
        selectedCreature = {0xFFFF, 0};
      }
      Global::heroScnIndex = INVALID_INDEX;
    } else {
      // 右键点击处理
      World::enterCreature(Global::heroScnPair, currentCreature, POP_HERO);
    }
    return true;
  }
  return false;
}

const static SDL_FRect lukPosition = {240, 184, 42, 38};

const static SDL_FRect morPosition = {182, 184, 42, 38};

static bool clickLuk(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + lukPosition.x, leftUp.y + lukPosition.y, lukPosition.w,
             lukPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    HeroScrSys::showLukComfirm(clickType, *heroComp);
    return true;
  }
  return false;
}

static bool clickMor(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y, morPosition.w,
             morPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    HeroScrSys::showMorComfirm(clickType, *heroComp);
    return true;
  }
  return false;
}

static bool clickSpe(uint8_t clickType) {

  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + 18, leftUp.y + 180, 136, 42};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    HeroScrSys::showSpeConfirm(clickType, heroComp->portrait);
    return true;
  }
  return false;
}

static bool clickHeroLargePor(uint8_t clickType) {
  SDL_FRect posRect;
  const SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                          (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {(float)leftUp.x + 18, leftUp.y + 18, 58, 64};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    HeroScrSys::showHeroBiosComfirm(clickType, heroComp->portrait);
    return true;
  }
  return false;
}

bool HeroScrSys::leftMouseDown(float x, float y) {
  if (Global::heroScnType == (uint8_t)Enum::SCNTYPE::MOD) {
    auto clickType = (uint8_t)Enum::CLICKTYPE::L_DOWN;
    if (clickEquip(clickType)) {
      return false;
    }
  }
  return true;
}

static void drawCreature() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);
  for (uint8_t i = 0; i < heroComp->creatures.size(); i++) {
    auto [id, count] = heroComp->creatures[i];
    posRect = {leftUp.x + 14 + i * 66, leftUp.y + 484, 58, 64};
    if (count == 0) {
      if (Global::splitOn) {
        SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
        SDL_RenderRect(Window::renderer, &posRect);
      }
      continue;
    }
    auto texture = Global::defCache["TWCRPORT.def/0"][id + 2];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (Global::splitOn) {
      auto crePtr = &heroComp->creatures.at(i);
      if (Global::splitCre[0] != crePtr &&
          crePtr->first == Global::splitCre[0]->first) {
        SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
        SDL_RenderRect(Window::renderer, &posRect);
      }
    } else if (Global::heroScnIndex == i) {
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
      SDL_RenderRect(Window::renderer, &posRect);
    }

    posRect.x += 58;
    posRect.y = posRect.y + 48;
    while (count > 0) {
      auto digit = count % 10; // 获取当前最低位
      texture = BMPFont::fontCache["verd10b.fnt"]['0' + digit].texture;
      posRect = {posRect.x - texture->w, posRect.y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
      count /= 10; // 去掉最低位
    }
  }
}

static void drawMoraleLuck() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);
  auto heroMor = HeroScrSys::heroMor(*heroComp);
  heroMor = std::clamp(heroMor, -3, 3);
  posRect = {static_cast<float>((int)(leftUp.x + 182)),
             static_cast<float>((int)(leftUp.y + 184)), 42, 38};

  auto texture = Global::defCache["IMRL42.def/0"][heroMor + 3];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  auto heroLuk = HeroScrSys::heroLuk(*heroComp);
  heroLuk = std::clamp(heroLuk, -3, 3);
  texture = Global::defCache["ILCK42.def/0"][heroLuk + 3];

  posRect = {static_cast<float>((int)(leftUp.x + 240)),
             static_cast<float>((int)(leftUp.y + 184)), 42, 38};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == HeroScrSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

const static std::vector<SDL_FRect> secSkiPositions = {
    {18, 276, 44, 44},  // i=0
    {162, 276, 44, 44}, // i=1
    {18, 324, 44, 44},  // i=2
    {162, 324, 44, 44}, // i=3
    {18, 372, 44, 44},  // i=4
    {162, 372, 44, 44}, // i=5
    {18, 420, 44, 44},  // i=6
    {162, 420, 44, 44}  // i=7
};
static void drawHeroSecSkill() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(12);
  FreeTypeSys::setColor(255, 255, 255, 255);

  for (int i = 0; i < std::min((int)heroComp->secSkills.size(), 8); ++i) {
    posRect = {leftUp.x + secSkiPositions[i].x, leftUp.y + secSkiPositions[i].y,
               44, 44};
    auto [index, level] = heroComp->secSkills.at(i);
    auto texture = Global::defCache["SECSKILL.def/0"][(index + 1) * 3 + level];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    FreeTypeSys::draw(posRect.x + 50, posRect.y + 3, strPool[5 + level]);
    FreeTypeSys::draw(posRect.x + 50, posRect.y + 23, strPool[1147 + index]);
  }
}

static void drawHeroPortraitSpec() {
  SDL_FRect posRect;
  // render small hero PortraitsSmall
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  posRect = {(float)leftUp.x + 612, leftUp.y + 33, 48, 32};
  auto playerId = Global::playerId;
  auto strPool = *Lang::strPool[Global::langIndex];

  for (auto &[level, heroEnt] : Global::heros[playerId]) {
    posRect.y += 54;
    auto &registry = World::registrys[level];
    auto heroComp = &registry.get<HeroComp>(heroEnt);
    auto texture =
        Global::pcxCache[HeroCfg::heroSmallPor[heroComp->portrait]][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }

  auto &registry = World::registrys[World::level];
  posRect = {(float)leftUp.x + 18, leftUp.y + 18, 58, 64};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);
  auto texture = Global::pcxCache[HeroCfg::heroLargePor[heroComp->portrait]][0];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  FreeTypeSys::setSize(15);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto heroName = strPool[1259 + heroComp->portrait];
  FreeTypeSys::drawCenter(posRect.x + 170, posRect.y + 10, heroName);
  FreeTypeSys::setColor(255, 255, 255, 255);
  auto str = FreeTypeSys::str(heroComp->level) + strPool[2174] +
             strPool[2175 + heroComp->subId];
  FreeTypeSys::setSize(13);
  FreeTypeSys::drawCenter(posRect.x + 170, posRect.y + 35, str);

  posRect = {(float)leftUp.x + 18, leftUp.y + 180, 44, 44};
  SDL_RenderTexture(Window::renderer,
                    Global::defCache["UN44.def/0"][heroComp->portrait], nullptr,
                    &posRect);
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::draw(posRect.x + 50, posRect.y + 1, strPool[8]);

  FreeTypeSys::setColor(255, 255, 255, 255);
  FreeTypeSys::draw(posRect.x + 50, posRect.y + 21,
                    strPool[1862 + heroComp->portrait]);
}

const static std::vector<SDL_FRect> primPosition = {
    {32, 111, 42, 42},  {102, 111, 42, 42}, {172, 111, 42, 42},
    {242, 111, 42, 42}, {162, 230, 42, 42}, {20, 230, 42, 42},
};

static void drawBackGround() {
  SDL_FRect posRect;
  auto playerId = Global::playerId;
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);

  auto texture = Global::pcxCache["HeroScr4.pcx"][playerId];
  auto x = (Global::viewPort.w - texture->w) / 2;
  auto y = (Global::viewPort.h - texture->h) / 2;
  posRect = {x, y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  texture = Global::defCache["CREST58.def/0"][playerId];
  posRect = {x + 606, y + 8, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  texture = Global::pcxCache["ADROLLVR.pcx"][0];
  posRect = {x + 7, y + 559, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawPrim() {
  const SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                          (Global::viewPort.h - 586) / 2};
  const std::vector<SDL_Texture *> textures = {
      Global::defCache["PSKIL42.def/0"][0],
      Global::defCache["PSKIL42.def/0"][1],
      Global::defCache["PSKIL42.def/0"][2],
      Global::defCache["PSKIL42.def/0"][5],
      Global::defCache["PSKIL42.def/0"][3],
      Global::defCache["PSKIL42.def/0"][4],
  };
  auto strPool = *Lang::strPool[Global::langIndex];
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);
  SDL_Texture *texture;
  for (auto i = 0; i < 4; i++) {
    SDL_FRect posRect{leftUp.x + primPosition[i].x,
                      leftUp.y + primPosition[i].y, primPosition[i].w,
                      primPosition[i].h};
    texture = textures[i];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(posRect.x + 22, posRect.y - 22, strPool[i + 1]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    auto num = HeroScrSys::heroPrimAbility(*heroComp, i);
    FreeTypeSys::drawCenter(posRect.x + 22, posRect.y + 44, num);
  }

  texture = textures[4];
  SDL_FRect posRect{leftUp.x + primPosition[4].x, leftUp.y + primPosition[4].y,
                    primPosition[4].w, primPosition[4].h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::draw(posRect.x + 50, posRect.y, strPool[9]);
  FreeTypeSys::setColor(255, 255, 255, 255);
  auto manaStr = FreeTypeSys::str(heroComp->mana) + u"/" +
                 FreeTypeSys::str(HeroScrSys::heroMaxMana(*heroComp));
  FreeTypeSys::draw(posRect.x + 50, posRect.y + 20, manaStr);

  texture = textures[5];
  posRect = {leftUp.x + primPosition[5].x, leftUp.y + primPosition[5].y,
             primPosition[5].w, primPosition[5].h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::draw(posRect.x + 50, posRect.y, strPool[10]);
  FreeTypeSys::draw(posRect.x + 50, posRect.y + 20, heroComp->exp);
}

static void drawArtifacts() {
  const SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                          (Global::viewPort.h - 586) / 2};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);

  // 绘制背包和装备栏并获取点击信息
  ArtifactsOfHeroSys::drawBackPack(heroComp, leftUp.x, leftUp.y,
                                   Global::artPageIndex[0]);
  ArtifactsOfHeroSys::drawEquip(heroComp, leftUp.x, leftUp.y);
  // 处理选中物品的绘制
  auto &[selectedIndex, selectedArtId] = Global::artPair;
  if (selectedArtId != 0xffff) {
    ArtifactsOfHeroSys::drawArtSlot(selectedArtId, leftUp.x, leftUp.y);
    auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
    auto top = (*topFunc.target<bool (*)()>() == HeroScrSys::run);
    if (!top) {
      return;
    }
    SDL_FRect dragRect = {Window::mouseX - 22, Window::mouseY - 22, 44, 44};
    auto texture = Global::defCache["Artifact.def/0"][selectedArtId];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &dragRect);
  }
}

static void drawBottomInfo() {
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect = {leftUp.x + lukPosition.x, leftUp.y + lukPosition.y,
                       lukPosition.w, lukPosition.h};
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[2215]);
    return;
  }
  posRect = {leftUp.x + morPosition.x, leftUp.y + morPosition.y, morPosition.w,
             morPosition.h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[2214]);
    return;
  }
  // atk
  posRect = {(float)leftUp.x + primPosition[0].x, leftUp.y + primPosition[0].y,
             primPosition[0].w, primPosition[0].h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[1]);
    return;
  }
  // def
  posRect = {(float)leftUp.x + primPosition[1].x, leftUp.y + primPosition[1].y,
             primPosition[1].w, primPosition[1].h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[2]);
    return;
  }
  // power
  posRect = {(float)leftUp.x + primPosition[2].x, leftUp.y + primPosition[2].y,
             primPosition[2].w, primPosition[2].h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[3]);
    return;
  }
  // kno
  posRect = {(float)leftUp.x + primPosition[3].x, leftUp.y + primPosition[3].y,
             primPosition[3].w, primPosition[3].h};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[4]);
    return;
  }
  // mana
  posRect = {(float)leftUp.x + primPosition[4].x, leftUp.y + primPosition[4].y,
             136, 44};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558, strPool[2871]);
    return;
  }
  // exp
  posRect = {(float)leftUp.x + primPosition[5].x, leftUp.y + primPosition[5].y,
             136, 44};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[10]);
    return;
  }
  // 特长
  posRect = {(float)leftUp.x + 18, leftUp.y + 180, 136, 44};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558, strPool[2876]);
    return;
  }
  // secSki
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);
  for (int i = 0; i < std::min((int)heroComp->secSkills.size(), 8); ++i) {
    posRect = {leftUp.x + secSkiPositions[i].x, leftUp.y + secSkiPositions[i].y,
               136, 44};
    auto [index, level] = heroComp->secSkills.at(i);
    if (SDL_PointInRectFloat(&point, &posRect)) {
      FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                              strPool[2860] + strPool[5 + level] +
                                  strPool[1150 + index]);
      return;
    }
  }
  // 绘制背包和装备栏并获取点击信息
  auto [backpackIndex, backpackArtId] = ArtifactsOfHeroSys::clickBackPack(
      heroComp, leftUp.x, leftUp.y, Global::artPageIndex[0]);
  auto [equipIndex, equipArtId] =
      ArtifactsOfHeroSys::clickEquip(heroComp, leftUp.x, leftUp.y);

  // 处理选中物品的绘制
  auto &[selectedIndex, selectedArtId] = Global::artPair;

  // 处理物品交互逻辑
  bool clickedBackpack = backpackIndex != 0xff;
  bool clickedEquipment = equipIndex != 0xff && !clickedBackpack;

  uint16_t targetArtId = clickedBackpack ? backpackArtId : equipArtId;
  if (targetArtId != 0xffff) {
    FreeTypeSys::drawCenter(leftUp.x + 336, leftUp.y + 558,
                            strPool[2860] + strPool[162 + targetArtId]);
    return;
  }
  auto v = buttonInfo();
  if (AdvMapSys::drawButtonsText(leftUp.x, leftUp.y, leftUp.x + 336,
                                 leftUp.y + 558, v)) {
    return;
  }
}

bool HeroScrSys::run() {
  drawBackGround();
  drawPrim();
  drawButton();
  drawHeroPortraitSpec();
  drawMoraleLuck();
  drawHeroSecSkill();
  drawCreature();
  drawArtifacts();
  drawBottomInfo();
  return true;
}

static bool clickPrim(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};

  for (auto i = 0; i < 4; i++) {
    posRect = {leftUp.x + primPosition[i].x, leftUp.y + primPosition[i].y,
               primPosition[i].w, primPosition[i].h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      auto [level, ent] = Global::heroScnPair;
      auto heroComp = &World::registrys[level].get<HeroComp>(ent);
      HeroScrSys::showPrimComfirm(clickType, i);
      return true;
    }
  }
  return false;
}

static bool clickSecSki(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);
  for (int i = 0; i < std::min((int)heroComp->secSkills.size(), 8); ++i) {
    posRect = {leftUp.x + secSkiPositions[i].x, leftUp.y + secSkiPositions[i].y,
               136, 44};
    auto [index, level] = heroComp->secSkills.at(i);
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showSecSkiComfirm(clickType, index, level);
      return true;
    }
  }
  return false;
}

static bool clickMana(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + primPosition[4].x, leftUp.y + primPosition[4].y, 136,
             42};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    HeroScrSys::showManaComfirm(clickType, *heroComp);
    return true;
  }
  return false;
}

static bool clickExp(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                    (Global::viewPort.h - 586) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  posRect = {leftUp.x + primPosition[5].x, leftUp.y + primPosition[5].y, 136,
             42};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    auto [level, ent] = Global::heroScnPair;
    auto heroComp = &World::registrys[level].get<HeroComp>(ent);
    HeroScrSys::showExpComfirm(clickType, *heroComp);
    return true;
  }
  return false;
}

static void clickBackPage() {
  const SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                          (Global::viewPort.h - 586) / 2};
  auto [level, ent] = Global::heroScnPair;
  auto heroComp = &World::registrys[level].get<HeroComp>(ent);

  Global::artPageIndex[0] += ArtifactsOfHeroSys::clickPage(
      heroComp, leftUp.x, leftUp.y, Global::artPageIndex[0]);
}

bool HeroScrSys::leftMouseUp(float x, float y) {
  if (Global::heroScnType == (uint8_t)Enum::SCNTYPE::MOD) {
    const SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                            (Global::viewPort.h - 586) / 2};
    auto v = buttonInfo();
    auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

    if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
      return false;
    }

    if (clickCre(clickType)) {
      return false;
    }
    if (clickPrim(clickType)) {
      return false;
    }
    if (clickHeroLargePor(clickType)) {
      return false;
    }
    if (clickSecSki(clickType)) {
      return false;
    }
    if (clickMana(clickType)) {
      return false;
    }
    if (clickExp(clickType)) {
      return false;
    }
    if (clickLuk(clickType)) {
      return false;
    }
    if (clickMor(clickType)) {
      return false;
    }
    clickBackPage();
  }
  return true;
}

bool HeroScrSys::rightMouseUp(float x, float y) {
  if (Global::heroScnType == (uint8_t)Enum::SCNTYPE::POP) {
    World::iterateSystems.push_back([]() -> bool {
      World::exitScrn();
      return false;
    });
  }
  return false;
}

bool HeroScrSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    close();
    break;
  }
  default:
    break;
  }
  return false;
}

bool HeroScrSys::rightMouseDown(float x, float y) {
  if (Global::heroScnType == (uint8_t)Enum::SCNTYPE::MOD) {
    const SDL_FPoint leftUp{(Global::viewPort.w - 672) / 2,
                            (Global::viewPort.h - 586) / 2};
    auto v = buttonInfo();
    auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

    if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
      return false;
    }

    if (clickEquip(clickType)) {
      return false;
    }
    if (clickCre(clickType)) {
      return false;
    }
    if (clickHeroLargePor(clickType)) {
      return false;
    }
    if (clickPrim(clickType)) {
      return false;
    }
    if (clickMana(clickType)) {
      return false;
    }
    if (clickSpe(clickType)) {
      return false;
    }
    if (clickSecSki(clickType)) {
      return false;
    }
    if (clickExp(clickType)) {
      return false;
    }
    if (clickLuk(clickType)) {
      return false;
    }
    if (clickMor(clickType)) {
      return false;
    }
  }
  return true;
}

std::vector<std::pair<uint8_t, int8_t>>
HeroScrSys::heroArtifactAbility(HeroComp &hComp, uint8_t i) {
  std::vector<std::pair<uint8_t, int8_t>> r;
  for (auto a : hComp.artifacts) {
    if (a != 0xffff) {
      auto vec = ArtifactCfg::artBonuse.at(a);
      for (auto v : vec) {
        if (v.first == i) {
          r.push_back({a, v.second});
        }
      }
    }
  }
  return r;
}

int32_t HeroScrSys::heroPrimAbility(HeroComp &hComp, uint8_t i) {
  auto r = heroArtifactAbility(hComp, i);
  int32_t sum = 0;
  for (const auto &pair : r) {
    sum += pair.second;
  }
  return hComp.primSkills[i] + sum;
}

int32_t HeroScrSys::heroMaxMana(HeroComp &hComp) {
  int32_t r = 0;
  auto kno = HeroScrSys::heroPrimAbility(hComp, 3);
  r = kno * 10;
  for (auto p : hComp.secSkills) {
    if (p.first == 24) {
      switch (p.second) {
      case 0: {
        r *= 1.25;
        break;
      }
      case 1: {
        r *= 1.5;
        break;
      }
      case 2: {
        r *= 2;
        break;
      }
      }
      break;
    }
  }
  return r;
}

int32_t HeroScrSys::heroMor(HeroComp &hComp) {
  int32_t r = 0;
  for (auto p : hComp.morale) {
    r += p.second;
  }
  // 装备
  auto i = (uint8_t)ArtifactCfg::BONUSE::MOR;
  auto v = HeroScrSys::heroArtifactAbility(hComp, i);
  for (const auto &pair : v) {
    r += pair.second;
  }
  // 辅助技能
  for (auto p : hComp.secSkills) {
    if (p.first == 6) {
      r += p.second + 1;
      break;
    }
  }
  // 特殊装备
  i = (uint8_t)ArtifactCfg::BONUSE::MAX_MOR;
  v = HeroScrSys::heroArtifactAbility(hComp, i);
  if (!v.empty()) {
    r = std::max(r, (int32_t)v[0].second);
  }
  return r;
}

int32_t HeroScrSys::heroLuk(HeroComp &hComp) {
  int32_t r = 0;
  for (auto p : hComp.luck) {
    r += p.second;
  }
  // 装备
  auto i = (uint8_t)ArtifactCfg::BONUSE::LUK;
  auto v = HeroScrSys::heroArtifactAbility(hComp, i);
  for (const auto &pair : v) {
    r += pair.second;
  }
  // 辅助技能
  for (auto p : hComp.secSkills) {
    if (p.first == 9) {
      r += p.second + 1;
      break;
    }
  }
  // 特殊装备
  i = (uint8_t)ArtifactCfg::BONUSE::MAX_LUK;
  v = HeroScrSys::heroArtifactAbility(hComp, i);
  if (!v.empty()) {
    r = std::max(r, (int32_t)v[0].second);
  }
  // 访问过的物体
  return r;
}

int32_t HeroScrSys::heroSight(HeroComp &hComp) {
  int32_t r = 0;
  auto i = (uint8_t)ArtifactCfg::BONUSE::SIGHT;
  auto v = HeroScrSys::heroArtifactAbility(hComp, i);

  for (const auto &pair : v) {
    r += pair.second;
  }
  // 辅助技能
  for (auto p : hComp.secSkills) {
    if (p.first == (uint8_t)HeroCfg::SecondarySkill::SCOUTING) {
      r += p.second + 1;
      break;
    }
  }

  return r;
}

void HeroScrSys::showResConfirm(uint8_t clickType, uint16_t i) {
  auto confirmbakW = 400;
  auto confirmbakH = 140;
  Global::confirmdraw = [confirmbakW, confirmbakH, i]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[1003]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2240 + i]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));
  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showArtifactComfirm(uint16_t i) {
  auto confirmbakW = 400;
  auto confirmbakH = 140;
  Global::confirmdraw = [confirmbakW, confirmbakH, i]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[162 + i]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[306 + i]);
  };
  World::enterConfirm(confirmbakW, confirmbakH, ((uint8_t)Enum::SCNTYPE::POP));
}

void HeroScrSys::showPrimComfirm(uint8_t clickType, uint16_t i) {
  auto confirmbakW = 400;
  auto confirmbakH = 160;
  Global::confirmdraw = [confirmbakW, confirmbakH, i]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[1 + i]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2201 + i]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showLukComfirm(uint8_t clickType, HeroComp &hComp) {
  auto confirmbakW = 500;
  auto confirmbakH = 340;
  Global::confirmdraw = [confirmbakW, confirmbakH, &hComp]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto luk = HeroScrSys::heroLuk(hComp);
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    auto str = strPool[2214];
    if (luk < 0) {
      str = strPool[2213];
    } else if (luk > 0) {
      str = strPool[2215];
    }
    str += strPool[2212];
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15, str);

    str = strPool[2221];
    if (luk < 0) {
      str = strPool[2222];
    } else if (luk > 0) {
      str = strPool[2220];
    }
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40, str);

    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 60,
                            strPool[2223]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    auto y = leftUp.y + 60;
    for (auto p : hComp.luck) {
      y += 20;
      str = strPool[926 + p.first];
      auto num = p.second >= 0 ? u"+" + FreeTypeSys::str(p.second)
                               : u"-" + FreeTypeSys::str(p.second);
      FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, y,
                              strPool[2219] + str + num);
    }

    auto i = (uint8_t)ArtifactCfg::BONUSE::LUK;
    auto v = HeroScrSys::heroArtifactAbility(hComp, i);
    for (auto p : v) {
      y += 20;
      str = strPool[162 + p.first];
      auto num = p.second >= 0 ? u"+" + FreeTypeSys::str(p.second)
                               : u"-" + FreeTypeSys::str(p.second);
      FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, y, str + num);
    }
    for (auto p : hComp.secSkills) {
      if (p.first == 6) {
        y += 20;
        str = strPool[5 + p.second] + strPool[1156];
        auto num = u"+" + FreeTypeSys::str(p.second + 1);
        FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, y, str + num);
        break;
      }
    }
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showLukComfirm(uint8_t clickType) {
  auto confirmbakW = 400;
  auto confirmbakH = 200;
  Global::confirmdraw = [confirmbakW, confirmbakH]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];

    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2220]);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 60,
                            strPool[2222]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showMorComfirm(uint8_t clickType, HeroComp &hComp) {
  auto confirmbakW = 500;
  auto confirmbakH = 340;
  Global::confirmdraw = [confirmbakW, confirmbakH, &hComp]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};

    auto mor = HeroScrSys::heroMor(hComp);

    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    auto str = strPool[2214];
    if (mor < 0) {
      str = strPool[2213];
    } else if (mor > 0) {
      str = strPool[2215];
    }
    str += strPool[2211];
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15, str);

    str = strPool[2229];
    if (mor < 0) {
      str = strPool[2230];
    } else if (mor > 0) {
      str = strPool[2228];
    }
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40, str);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 60,
                            strPool[2231]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    auto y = leftUp.y + 60;
    for (auto p : hComp.morale) {
      y += 20;
      str = strPool[926 + p.first];
      auto num = p.second >= 0 ? u"+" + FreeTypeSys::str(p.second)
                               : u"-" + FreeTypeSys::str(p.second);
      FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, y,
                              strPool[2219] + str + num);
    }
    auto i = (uint8_t)ArtifactCfg::BONUSE::MOR;
    auto v = HeroScrSys::heroArtifactAbility(hComp, i);
    for (auto p : v) {
      y += 20;
      str = strPool[162 + p.first];
      auto num = p.second >= 0 ? u"+" + FreeTypeSys::str(p.second)
                               : u"-" + FreeTypeSys::str(p.second);
      FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, y, str + num);
    }
    for (auto p : hComp.secSkills) {
      if (p.first == 6) {
        y += 20;
        str = strPool[5 + p.second] + strPool[1153];
        auto num = u"+" + FreeTypeSys::str(p.second + 1);
        FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, y, str + num);
        break;
      }
    }
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showMorComfirm(uint8_t clickType) {
  auto confirmbakW = 400;
  auto confirmbakH = 160;
  Global::confirmdraw = [confirmbakW, confirmbakH]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2220]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 60,
                            strPool[2222]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showExpComfirm(uint8_t clickType) {
  auto confirmbakW = 420;
  auto confirmbakH = 200;
  Global::confirmdraw = [confirmbakW, confirmbakH]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[10]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2208]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));
  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}
void HeroScrSys::showExpComfirm(uint8_t clickType, HeroComp &hComp) {
  auto confirmbakW = 420;
  auto confirmbakH = 220;
  Global::confirmdraw = [confirmbakW, confirmbakH, hComp]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[10]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2208]);
    std::u16string str;
    if (hComp.level >= std::size(HeroCfg::heroLevelExp)) {
      str = strPool[2205] + strPool[2209];
    } else {
      str =
          strPool[2205] + FreeTypeSys::str(HeroCfg::heroLevelExp[hComp.level]);
    }
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 80, str);
    str = strPool[2206] + FreeTypeSys::str(hComp.exp);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 100, str);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showManaComfirm(uint8_t clickType, HeroComp &hComp) {
  auto confirmbakW = 430;
  auto confirmbakH = 160;

  Global::confirmdraw = [confirmbakW, confirmbakH, hComp]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[9]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2208]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showManaComfirm(uint8_t clickType) {
  auto confirmbakW = 430;
  auto confirmbakH = 160;

  Global::confirmdraw = [confirmbakW, confirmbakH]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[9]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2207]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showSpeConfirm(uint8_t clickType, uint16_t i) {
  auto confirmbakW = 430;
  auto confirmbakH = 160;

  Global::confirmdraw = [confirmbakW, confirmbakH, i]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[8]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[2018 + i]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}
void HeroScrSys::showSecSkiComfirm(uint8_t clickType, uint16_t id, uint16_t i) {
  auto confirmbakW = 600;
  auto confirmbakH = 360;
  Global::confirmdraw = [confirmbakW, confirmbakH, id, i]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    auto str = strPool[5 + i] + strPool[1147 + id];
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15, str);
    for (uint8_t m = 0; m < 3; m++) {
      if (m == i) {
        FreeTypeSys::setColor(240, 224, 104, 255);
      } else {
        FreeTypeSys::setColor(255, 255, 255, 255);
      }
      auto str = strPool[1175 + id * 3 + m];
      FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2,
                              leftUp.y + 40 + m * 20, str);
    }
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}

void HeroScrSys::showHeroBiosComfirm(uint8_t clickType, uint16_t i) {
  auto confirmbakW = 600;
  auto confirmbakH = 360;
  Global::confirmdraw = [confirmbakW, confirmbakH, i]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                            strPool[1259 + i]);
    FreeTypeSys::setColor(255, 255, 255, 255);
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40,
                            strPool[1415 + i]);
  };
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));

  } else {
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::POP));
  }
}