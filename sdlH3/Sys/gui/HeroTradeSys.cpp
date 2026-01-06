#include "HeroTradeSys.h"
#include "AdvMapSys.h"
#include "Cfg/ArtifactCfg.h"
#include "Cfg/HeroCfg.h"
#include "Comp/HeroComp.h"
#include "Comp/PlayerIdComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "HeroScrSys.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui//base/ArtifactsOfHeroSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <vector>

static void close() {
  auto [index, artId] = Global::artPair;
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  if (artId != 0xffff) {
    auto heroComp =
        &registry[Global::artClick]->get<HeroComp>(heroEnts[Global::artClick]);
    std::vector<uint16_t> &artifactsBack = heroComp->artifactsInBackpack;
    std::vector<uint16_t> &artifacts = heroComp->artifacts;
    if (Global::artBackClick) {
      artifactsBack.insert(artifactsBack.begin() + index, artId);
    } else {
      artifacts[index] = artId;
    }
    Global::artPair = {0xff, 0xffff};
  }
  World::exitScrn();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {732, 567, 64, 30};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["hsbtns4.DEF/0"];
  b.r = {10, 44, 52, 36};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawCreature() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  for (uint8_t m = 0; m <= 1; m++) {
    auto heroComp = &registry[m]->get<HeroComp>(heroEnts[m]);
    for (uint8_t i = 0; i < heroComp->creatures.size(); i++) {
      auto [id, count] = heroComp->creatures[i];
      if (count == 0) {
        continue;
      }
      auto texture = Global::defCache["CPRSMALL.def/0"][id + 2];
      posRect = {(float)leftUp.x + 67 + 418 * m + i * 36, leftUp.y + 132, 32,
                 32};
      // SDL_RenderFillRect(Window::renderer, &posRect);
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      FreeTypeSys::setSize(12);
      FreeTypeSys::setColor(255, 255, 255, 255);
      auto num = FreeTypeSys::str(count);
      FreeTypeSys::drawLeft(posRect.x + 32, posRect.y + 16, num);
      if (Global::goalIndex != 0xff) {
        auto x = Global::goalIndex / 7;
        auto y = Global::goalIndex % 7;
        if (x == m && y == i) {
          SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
          SDL_RenderRect(Window::renderer, &posRect);
        }
      }
    }
  }
}

static void drawHeroSecSkill() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  for (uint8_t i = 0; i <= 1; i++) {
    auto heroComp = &registry[i]->get<HeroComp>(heroEnts[i]);
    for (int m = 0; m < heroComp->secSkills.size(); ++m) {
      posRect = {(float)leftUp.x + 32 + 36 * m + 454 * i, leftUp.y + 88, 32,
                 32};
      auto [index, level] = heroComp->secSkills.at(m);
      auto texture = Global::defCache["SECSK32.def/0"][(index + 1) * 3 + level];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
  }
}

static void drawHeroPortraitSpec() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  for (uint8_t i = 0; i < 2; i++) {
    posRect = {(float)leftUp.x + 257 + 228 * i, leftUp.y + 13, 58, 64};
    auto heroComp = &registry[i]->get<HeroComp>(heroEnts[i]);
    auto texture =
        Global::pcxCache[HeroCfg::heroLargePor[heroComp->portrait]][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    posRect = {(float)leftUp.x + 67 + 490 * i, leftUp.y + 46, 32, 32};
    texture = Global::defCache["UN32.def/0"][heroComp->portrait];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
}

static void drawPSKIL() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};

  for (uint8_t i = 0; i < 2; i++) {
    leftUp.x += i * 490;
    auto texture = Global::defCache["PSKIL32.def/0"][4];
    posRect = {static_cast<float>(leftUp.x + 102 + 1), leftUp.y + 46, 32, 32};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    texture = Global::defCache["PSKIL32.def/0"][5];
    posRect = {static_cast<float>(leftUp.x + 138 + 1), leftUp.y + 46, 32, 32};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }

  for (uint8_t i = 0; i < 4; i++) {
    leftUp.x = (Global::viewPort.w - 800) / 2;
    auto texture = Global::defCache["PSKIL32.def/0"][i];
    posRect = {static_cast<float>(leftUp.x + 383 + 1), leftUp.y + 18 + 36 * i,
               32, 32};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
}

static void drawMoraleLuck() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  for (uint8_t i = 0; i < 2; i++) {
    leftUp.x += i * 490;
    auto texture = Global::defCache["IMRL22.def/0"][0];
    posRect = {static_cast<float>(leftUp.x + 174 + 2), leftUp.y + 46, 30, 20};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    texture = Global::defCache["ILCK22.def/0"][0];
    posRect = {static_cast<float>(leftUp.x + 210 + 2), leftUp.y + 46, 30, 20};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
}
static void drawBackGround() {
  SDL_FRect srcRect;
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  auto playerId = registry[0]->get<PlayerIdComp>(heroEnts[0]).id;
  auto textures = Global::pcxCache["Trade2.pcx"];
  auto texture = textures[playerId];
  srcRect = {0, 0, 400, 600};
  posRect = {leftUp.x, leftUp.y, 400, 600};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);

  playerId = registry[1]->get<PlayerIdComp>(heroEnts[1]).id;
  texture = textures[playerId];
  leftUp.x = leftUp.x + 400;
  srcRect = {400, 0, 400, 600};
  posRect = {leftUp.x, leftUp.y, 400, 600};
  SDL_RenderTexture(Window::renderer, texture, &srcRect, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == HeroTradeSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawArtifacts() {
  const SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                          (Global::viewPort.h - 600) / 2};

  const auto drawArtifact = [&](HeroComp *heroComp, int32_t x, int32_t y,
                                uint8_t index) -> void {
    // 绘制背包和装备栏并获取点击信息
    ArtifactsOfHeroSys::drawBackPack(heroComp, leftUp.x + x, leftUp.y + y,
                                     Global::artPageIndex[index]);
    ArtifactsOfHeroSys::drawEquip(heroComp, leftUp.x + x, leftUp.y + y);

    return;
  };

  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};

  auto heroComp = &registry[0]->get<HeroComp>(Global::heroEnt);
  drawArtifact(heroComp, -269, 159, 0);

  heroComp = &registry[1]->get<HeroComp>(Global::goalEnt);
  drawArtifact(heroComp, 163, 159, 1);

  auto &[selectedIndex, selectedArtId] = Global::artPair;
  bool hasSelectedArtifact = selectedArtId != 0xffff;
  uint16_t selectedArtIdBack = selectedArtId;
  // 绘制被拖动的物品
  if (hasSelectedArtifact) {
    ArtifactsOfHeroSys::drawArtSlot(selectedArtIdBack, leftUp.x - 269,
                                    leftUp.y + 159);
    ArtifactsOfHeroSys::drawArtSlot(selectedArtIdBack, leftUp.x + 163,
                                    leftUp.y + 159);
    auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
    auto top = (*topFunc.target<bool (*)()>() == HeroTradeSys::run);
    if (!top) {
      return;
    }
    auto texture = Global::defCache["Artifact.def/0"][selectedArtIdBack];
    SDL_FRect dragRect = {Window::mouseX - 22, Window::mouseY - 22, 44, 44};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &dragRect);
  }
}
bool HeroTradeSys::run() {
  drawBackGround();
  drawButton();
  drawMoraleLuck();
  drawPSKIL();
  drawHeroPortraitSpec();
  drawHeroSecSkill();
  drawCreature();
  drawArtifacts();
  return true;
}

static bool clickPrim(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < 2; i++) {
    leftUp.x += i * 490;
    posRect = {static_cast<float>(leftUp.x + 102 + 1), leftUp.y + 46, 32, 32};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showPrimComfirm(leftClick, 4);
    }

    posRect = {static_cast<float>(leftUp.x + 138 + 1), leftUp.y + 46, 32, 32};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showPrimComfirm(leftClick, 5);
    }
  }

  for (uint8_t i = 0; i < 4; i++) {
    leftUp.x = (Global::viewPort.w - 800) / 2;
    posRect = {static_cast<float>(leftUp.x + 383 + 1), leftUp.y + 18 + 36 * i,
               32, 32};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showPrimComfirm(leftClick, i);
    }
  }
  return false;
}

static bool clickEquip(bool leftClick) {
  const SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                          (Global::viewPort.h - 600) / 2};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  const auto artifactClick = [&](HeroComp *heroComp, int32_t x, int32_t y,
                                 uint8_t index) -> bool {
    // 绘制背包和装备栏并获取点击信息
    auto [backpackIndex, backpackArtId] = ArtifactsOfHeroSys::clickBackPack(
        heroComp, leftUp.x + x, leftUp.y + y, Global::artPageIndex[index]);
    auto [equipIndex, equipArtId] =
        ArtifactsOfHeroSys::clickEquip(heroComp, leftUp.x + x, leftUp.y + y);

    // 处理选中物品的绘制
    auto &[selectedIndex, selectedArtId] = Global::artPair;

    // 处理物品交互逻辑
    bool clickedBackpack = backpackIndex != 0xff;
    bool clickedEquipment = equipIndex != 0xff && !clickedBackpack;

    if (!clickedBackpack && !clickedEquipment)
      return false;

    uint8_t targetIndex = clickedBackpack ? backpackIndex : equipIndex;
    uint16_t targetArtId = clickedBackpack ? backpackArtId : equipArtId;
    if (!leftClick && targetArtId != 0xffff) {
      HeroScrSys::showArtifactComfirm(targetArtId);
      return true;
    }
    bool isBackpackOperation = clickedBackpack;
    auto &artifactsBack = heroComp->artifactsInBackpack;
    auto &artifacts = heroComp->artifacts;

    if (selectedArtId != 0xffff) {
      // 放置物品
      if (isBackpackOperation) {
        if (targetIndex >= artifactsBack.size()) {
          artifactsBack.resize(targetIndex + 1, 0xffff);
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
            auto size = registry[Global::artClick]
                            ->get<HeroComp>(heroEnts[Global::artClick])
                            .artifactsInBackpack.size();
            Global::artPair = {size, targetArtId};
            Global::artBackClick = true;
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
      Global::artBackClick = isBackpackOperation;
      Global::artClick = index;
      if (isBackpackOperation) {
        artifactsBack.erase(artifactsBack.begin() + targetIndex);
      } else {
        artifacts[targetIndex] = 0xffff;
      }
      Global::cursorType = (uint8_t)Enum::CURSOR::HIDE;
      return true;
    }
    return true;
  };
  auto heroComp = &registry[0]->get<HeroComp>(heroEnts[0]);
  if (artifactClick(heroComp, -269, 159, 0)) {
    return true;
  }
  heroComp = &registry[1]->get<HeroComp>(heroEnts[1]);
  if (artifactClick(heroComp, 163, 159, 1)) {
    return true;
  }
  return true;
}

static bool clickCre(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t m = 0; m <= 1; m++) {
    auto heroComp = &registry[m]->get<HeroComp>(heroEnts[m]);
    for (uint8_t i = 0; i < heroComp->creatures.size(); i++) {
      auto [id, count] = heroComp->creatures[i];
      posRect = {(float)leftUp.x + 67 + 418 * m + i * 36, leftUp.y + 132, 32,
                 32};
      if (SDL_PointInRectFloat(&point, &posRect)) {
        if (leftClick) {
          if (Global::splitOn) {
            auto crePtr = &heroComp->creatures.at(i);
            if (Global::splitCre[0] != crePtr &&
                (crePtr->second == 0 ||
                 crePtr->first == Global::splitCre[0]->first)) {
              Global::splitCre[1] = crePtr;
              World::enterSplitCre();
              Global::splitOn = false;
              Global::goalIndex = 0xff;
            }
          } else if (Global::goalIndex == (m * 7 + i)) {
            auto level = m == 0 ? World::level : Global::goalLevel;
            std::pair<uint8_t, entt::entity> heroPair = {level, heroEnts[m]};
            World::enterCreature(heroPair, heroComp->creatures[i],
                                 (uint8_t)Enum::CRETYPE::MOD_HERO);
            Global::goalIndex = 0xff;
          } else if (Global::goalIndex == 0xff) {
            if (count != 0) {
              Global::goalIndex = (m * 7 + i);
            }
          } else {
            auto i0 = Global::goalIndex / 7;
            auto i1 = Global::goalIndex % 7;
            auto &creatures0 =
                registry[i0]->get<HeroComp>(heroEnts[i0]).creatures;
            if (heroComp->creatures[i].second == 0 ||
                heroComp->creatures[i].first != creatures0[i1].first) {
              std::swap(heroComp->creatures[i], creatures0[i1]);
            } else {
              heroComp->creatures[i].second += creatures0[i1].second;
              creatures0[i1] = {0xffff, 0};
            }
            Global::goalIndex = 0xff;
          }
        } else {
          auto level = m == 0 ? World::level : Global::goalLevel;
          std::pair<uint8_t, entt::entity> heroPair = {level, heroEnts[m]};
          World::enterCreature(heroPair, heroComp->creatures[i],
                               (uint8_t)Enum::CRETYPE::POP_HERO);
        }
      }
    }
  }

  return true;
}

bool HeroTradeSys::leftMouseDown(float x, float y) {
  if (clickEquip(true)) {
    return false;
  }
  return true;
}

static bool clickSecSki(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  for (uint8_t i = 0; i <= 1; i++) {
    auto heroComp = &registry[i]->get<HeroComp>(heroEnts[i]);
    for (int m = 0; m < heroComp->secSkills.size(); ++m) {
      posRect = {(float)leftUp.x + 32 + 36 * m + 454 * i, leftUp.y + 88, 32,
                 32};
      if (SDL_PointInRectFloat(&point, &posRect)) {
        auto [index, level] = heroComp->secSkills.at(m);
        HeroScrSys::showSecSkiComfirm(leftClick, index, level);
        return true;
      }
    }
  }
  return false;
}

bool HeroTradeSys::rightMouseDown(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, false)) {
    return false;
  }
  if (clickSecSki(false)) {
    return false;
  }
  if (clickPrim(false)) {
    return false;
  }
  if (clickCre(false)) {
    return false;
  }
  if (clickEquip(false)) {
    return false;
  }
  return true;
}

static void clickBackPage() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  entt::registry *registry[2] = {&World::registrys[World::level],
                                 &World::registrys[Global::goalLevel]};
  entt::entity heroEnts[2] = {Global::heroEnt, Global::goalEnt};
  const auto artifactPageClick = [&](HeroComp *heroComp, int32_t x, int32_t y,
                                     uint8_t index) -> void {
    Global::artPageIndex[index] += ArtifactsOfHeroSys::clickPage(
        heroComp, leftUp.x + x, leftUp.y + y, Global::artPageIndex[index]);
  };
  auto heroComp = &registry[0]->get<HeroComp>(heroEnts[0]);
  artifactPageClick(heroComp, -269, 159, 0);
  heroComp = &registry[1]->get<HeroComp>(heroEnts[1]);
  artifactPageClick(heroComp, 163, 159, 1);
}

bool HeroTradeSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FRect posRect;
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  if (clickPrim(true)) {
    return false;
  }
  if (clickCre(true)) {
    return false;
  }
  if (clickSecSki(true)) {
    return false;
  }
  clickBackPage();
  return true;
}

bool HeroTradeSys::keyUp(uint16_t key) {
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