#include "HeroTradeSys.h"
#include "AdvMapSys.h"
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

static bool clickPrim(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < 2; i++) {
    leftUp.x += i * 490;
    posRect = {static_cast<float>(leftUp.x + 102 + 1), leftUp.y + 46, 32, 32};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showPrimComfirm(clickType, 4);
    }

    posRect = {static_cast<float>(leftUp.x + 138 + 1), leftUp.y + 46, 32, 32};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showPrimComfirm(clickType, 5);
    }
  }

  for (uint8_t i = 0; i < 4; i++) {
    leftUp.x = (Global::viewPort.w - 800) / 2;
    posRect = {static_cast<float>(leftUp.x + 383 + 1), leftUp.y + 18 + 36 * i,
               32, 32};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      HeroScrSys::showPrimComfirm(clickType, i);
    }
  }
  return false;
}

static bool clickEquip(uint8_t clickType) {
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

static bool clickCre(uint8_t clickType) {
  constexpr float CREATURE_SIZE = 32.0f;
  constexpr float START_X = 67.0f;
  constexpr float START_Y = 132.0f;
  constexpr float SPACING = 36.0f;
  constexpr float PANEL_OFFSET = 418.0f;
  constexpr uint8_t CREATURES_PER_HERO = 7;
  constexpr uint8_t INVALID_INDEX = 0xFF;

  SDL_FPoint mousePoint = {
      static_cast<float>(static_cast<int>(Window::mouseX)),
      static_cast<float>(static_cast<int>(Window::mouseY))};

  SDL_FPoint leftUp = {(Global::viewPort.w - 800.0f) / 2.0f,
                       (Global::viewPort.h - 600.0f) / 2.0f};

  entt::registry *registries[2] = {&World::registrys[World::level],
                                   &World::registrys[Global::goalLevel]};

  entt::entity heroEntities[2] = {Global::heroEnt, Global::goalEnt};

  auto getHeroComp = [&](uint8_t index) -> HeroComp & {
    return registries[index]->get<HeroComp>(heroEntities[index]);
  };

  auto isPointInCreatureRect = [&](uint8_t panel,
                                   uint8_t creatureIndex) -> bool {
    SDL_FRect posRect = {leftUp.x + START_X + (panel * PANEL_OFFSET) +
                             (creatureIndex * SPACING),
                         leftUp.y + START_Y, CREATURE_SIZE, CREATURE_SIZE};
    return SDL_PointInRectFloat(&mousePoint, &posRect);
  };

  auto handleLeftClick = [&](uint8_t panel, uint8_t creatureIndex,
                             HeroComp &heroComp) {
    if (Global::splitOn) {
      auto *currentCre = &heroComp.creatures[creatureIndex];
      if (Global::splitCre[0] != currentCre &&
          (currentCre->second == 0 ||
           currentCre->first == Global::splitCre[0]->first)) {
        Global::splitCre[1] = currentCre;
        World::enterSplitCre();
        Global::splitOn = false;
        Global::goalIndex = INVALID_INDEX;
      }
      return;
    }

    uint8_t clickedIndex = panel * CREATURES_PER_HERO + creatureIndex;

    if (Global::goalIndex == clickedIndex) {
      uint8_t level = (panel == 0) ? World::level : Global::goalLevel;
      World::enterCreature({level, heroEntities[panel]},
                           heroComp.creatures[creatureIndex],
                           static_cast<uint8_t>(Enum::CRETYPE::MOD_HERO));
      Global::goalIndex = INVALID_INDEX;
    } else if (Global::goalIndex == INVALID_INDEX) {
      if (heroComp.creatures[creatureIndex].second != 0) {
        Global::goalIndex = clickedIndex;
      }
    } else {
      uint8_t sourcePanel = Global::goalIndex / CREATURES_PER_HERO;
      uint8_t sourceIndex = Global::goalIndex % CREATURES_PER_HERO;

      auto &sourceCreatures = getHeroComp(sourcePanel).creatures;
      auto &targetCreature = heroComp.creatures[creatureIndex];
      auto &sourceCreature = sourceCreatures[sourceIndex];

      if (targetCreature.second == 0 ||
          targetCreature.first != sourceCreature.first) {
        std::swap(targetCreature, sourceCreature);
      } else {
        targetCreature.second += sourceCreature.second;
        sourceCreature = {0xFFFF, 0};
      }
      Global::goalIndex = INVALID_INDEX;
    }
  };

  auto handleRightClick = [&](uint8_t panel, uint8_t creatureIndex,
                              HeroComp &heroComp) {
    uint8_t level = (panel == 0) ? World::level : Global::goalLevel;
    World::enterCreature({level, heroEntities[panel]},
                         heroComp.creatures[creatureIndex],
                         static_cast<uint8_t>(Enum::CRETYPE::POP_HERO));
  };

  for (uint8_t panel = 0; panel < 2; ++panel) {
    HeroComp &heroComp = getHeroComp(panel);

    for (uint8_t creatureIndex = 0; creatureIndex < heroComp.creatures.size();
         ++creatureIndex) {
      if (!isPointInCreatureRect(panel, creatureIndex)) {
        continue;
      }

      if (clickType == static_cast<uint8_t>(Enum::CLICKTYPE::L_UP)) {
        handleLeftClick(panel, creatureIndex, heroComp);
      } else {
        handleRightClick(panel, creatureIndex, heroComp);
      }
      return true;
    }
  }

  return false;
}

bool HeroTradeSys::leftMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_DOWN;
  if (clickEquip(clickType)) {
    return false;
  }
  return true;
}

static bool clickSecSki(uint8_t clickType) {
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
        HeroScrSys::showSecSkiComfirm(clickType, index, level);
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
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickSecSki(clickType)) {
    return false;
  }
  if (clickPrim(clickType)) {
    return false;
  }
  if (clickCre(clickType)) {
    return false;
  }
  if (clickEquip(clickType)) {
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
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickPrim(clickType)) {
    return false;
  }
  if (clickCre(clickType)) {
    return false;
  }
  if (clickSecSki(clickType)) {
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