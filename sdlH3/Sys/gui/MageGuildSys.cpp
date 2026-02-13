#include "MageGuildSys.h"
#include "AdvMapSys.h"
#include "Comp/MageGuildComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SpellSys.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

void MageGuildSys::visit() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);

  std::set<uint8_t> r;
  for (auto i : {(uint8_t)TownCfg::Building::MAGE_GUILD_1,
                 (uint8_t)TownCfg::Building::MAGE_GUILD_2,
                 (uint8_t)TownCfg::Building::MAGE_GUILD_3,
                 (uint8_t)TownCfg::Building::MAGE_GUILD_4,
                 (uint8_t)TownCfg::Building::MAGE_GUILD_5}) {
    if (townComp->buildings.contains(i)) {
      auto mEnt = townComp->buildings[i];
      auto &mComp = registry.get<MageGuildComp>(mEnt);
      r.insert(mComp.spells.begin(), mComp.spells.end());
    }
  }

  for (auto h : townComp->heroEnt) {
    if (h.has_value()) {
      auto heroEnt = h.value();
      auto &heroComp = registry.get<HeroComp>(heroEnt);
      int8_t wisdom = HeroScrSys::heroSecLevel(
          heroComp, (uint8_t)HeroCfg::SecondarySkill::WISDOM);
      std::set<uint8_t> s;
      if (wisdom == -1) {
        // 只能学习1-2级技能
        auto v1 = SpellCfg::SpellLevels[1];
        auto v2 = SpellCfg::SpellLevels[2];

        s.insert(v1.begin(), v1.end());
        s.insert(v2.begin(), v2.end());

      } else {
        for (auto i = 1; i <= wisdom + 3; i++) {
          auto v = SpellCfg::SpellLevels[i];
          s.insert(v.begin(), v.end());
        }
      }
      heroComp.spells.insert(s.begin(), s.end());
    }
  }
}

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["TPMAGE1.DEF/0"];
  b.r = {748, 556, 48, 40};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  posRect = {leftUp.x, leftUp.y, 800, 600};
  auto texture = Global::pcxCache["TPMAGE.pcx"][0];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  return;
}

static const std::vector<std::vector<SDL_FPoint>> spellPositions = {
    {{222, 445}, {312, 445}, {402, 445}, {520, 445}, {610, 445}, {700, 445}},
    {{48, 53}, {48, 147}, {48, 241}, {48, 335}, {48, 429}},
    {{570, 82}, {672, 82}, {570, 157}, {672, 157}},
    {{183, 42}, {183, 148}, {183, 253}},
    {{491, 325}, {591, 325}}};

static void drawSpells() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  for (uint8_t m = 0; m < spellPositions.size(); m++) {
    auto buildId = (uint8_t)TownCfg::Building::MAGE_GUILD_1 + m;
    if (townComp->buildings.contains(buildId)) {
      auto ent = townComp->buildings[buildId];
      auto mComp = &registry.get<MageGuildComp>(ent);
      for (uint8_t i = 0; i < mComp->spells.size(); i++) {
        posRect = {leftUp.x + spellPositions[m][i].x,
                   leftUp.y + spellPositions[m][i].y, 83, 61};
        auto texture = Global::defCache["SpellScr.def/0"][mComp->spells[i]];
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      }
    }
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == MageGuildSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawWindow() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto windowStr = TownCfg::guildWindowStr[townComp->id];
  auto texture = Global::pcxCache[windowStr][0];
  posRect = {0, 0, 83, 61};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

bool MageGuildSys::run() {
  drawBackGround();
  drawWindow();
  drawSpells();
  drawButton();
  return true;
}

bool MageGuildSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

static bool clickSpells(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 800) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 600) / 2)};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};

  for (uint8_t m = 0; m < spellPositions.size(); m++) {
    auto buildId = (uint8_t)TownCfg::Building::MAGE_GUILD_1 + m;
    if (townComp->buildings.contains(buildId)) {
      auto ent = townComp->buildings[buildId];
      auto mComp = &registry.get<MageGuildComp>(ent);
      for (uint8_t i = 0; i < mComp->spells.size(); i++) {
        posRect = {leftUp.x + spellPositions[m][i].x,
                   leftUp.y + spellPositions[m][i].y, 83, 61};
        if (SDL_PointInRectFloat(&point, &posRect)) {
          SpellSys::showSplComfirm(clickType, mComp->spells[i], 0);
        }
      }
    }
  }
  return false;
}

bool MageGuildSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickSpells(clickType)) {
    return false;
  }
  return true;
}

bool MageGuildSys::keyUp(uint16_t key) {
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