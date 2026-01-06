#include "SpellSys.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/SpellCfg.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <any>
#include <cstdint>
#include <iterator>
#include <map>
#include <unordered_map>
#include <vector>

std::pair<uint8_t, uint8_t> SpellSys::heroSplLevel(HeroComp *heroComp,
                                                   uint8_t spellId) {
  uint8_t r = 0;
  uint8_t school = 0;
  auto vec = SpellCfg::SpellSchool.at(spellId);
  for (uint8_t i = 0; i < vec.size(); i++) {
    if (vec[i]) {
      school = i;
    }
  }
  std::unordered_map<uint8_t, uint8_t> skillMap;
  for (auto [key, val] : heroComp->secSkills) {
    switch (key) {
    case (uint8_t)HeroCfg::SecondarySkill::EARTH_MAGIC: {
      skillMap[0] = val + 1;
      break;
    }
    case (uint8_t)HeroCfg::SecondarySkill::WATER_MAGIC: {
      skillMap[1] = val + 1;
      break;
    }
    case (uint8_t)HeroCfg::SecondarySkill::FIRE_MAGIC: {
      skillMap[2] = val + 1;
      break;
    }
    case (uint8_t)HeroCfg::SecondarySkill::AIR_MAGIC: {
      skillMap[3] = val + 1;
      break;
    }
    default: {
      break;
    }
    }
  }
  for (uint8_t i = 0; i < 4; i++) {
    if (skillMap.contains(i) && vec[i]) {
      if (skillMap.at(i) >= r) {
        r = skillMap.at(i);
        school = i;
      }
    }
  }
  return {school, r};
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  auto texture = Global::pcxCache["SpelBack.pcx"][Global::playerId];
  posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

const uint8_t schools[5] = {3, 0, 2, 1, 4};

static void drawSchoolTab() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  const uint8_t schoolsIndex[5] = {1, 3, 2, 0, 4};
  auto textures = Global::defCache["SpelTab.DEF/0"];
  textures = {textures[0], textures[3], textures[1], textures[2], textures[4]};
  auto texture = textures[schoolsIndex[Global::splSchool]];
  posRect = {leftUp.x + 524, leftUp.y + 88, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static std::multimap<uint8_t, uint8_t> curSpellsBook(HeroComp &heroComp) {
  std::multimap<uint8_t, uint8_t> spellsMap;
  std::set<uint8_t> spellsSet = heroComp.spells;
  if (Global::splBattle) {
    auto it = spellsSet.lower_bound(10);
    spellsSet.erase(spellsSet.begin(), it);
  } else {
    auto it = spellsSet.upper_bound(10);
    spellsSet.erase(it, spellsSet.end());
  }
  if (Global::splSchool == 4) {
    for (auto spell : spellsSet) {
      spellsMap.insert({SpellCfg::SpellLevel.at(spell), spell});
    }
  } else {
    for (auto spell : spellsSet) {
      if (SpellCfg::SpellSchool.at(spell)[Global::splSchool]) {
        spellsMap.insert({SpellCfg::SpellLevel.at(spell), spell});
      }
    }
  }
  auto endIt = std::next(spellsMap.begin(), 16 * Global::splPage);
  spellsMap.erase(spellsMap.begin(), endIt);
  return spellsMap;
}

const static SDL_FRect splSlot[16] = {
    {(float)(117), (float)(90), 78, 65},  {(float)(202), (float)(90), 78, 65},
    {(float)(117), (float)(165), 78, 65}, {(float)(202), (float)(165), 78, 65},
    {(float)(117), (float)(240), 78, 65}, {(float)(202), (float)(240), 78, 65},
    {(float)(117), (float)(315), 78, 65}, {(float)(202), (float)(315), 78, 65},

    {(float)(337), (float)(90), 78, 65},  {(float)(422), (float)(90), 78, 65},
    {(float)(337), (float)(165), 78, 65}, {(float)(422), (float)(165), 78, 65},
    {(float)(337), (float)(240), 78, 65}, {(float)(422), (float)(240), 78, 65},
    {(float)(337), (float)(315), 78, 65}, {(float)(422), (float)(315), 78, 65}};

static void drawSchoolBook() {
  // areas for spells
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  auto &registry = World::registrys[World::level];
  auto heroComp = registry.get<HeroComp>(Global::heroEnt);
  std::multimap<uint8_t, uint8_t> spellsMap = curSpellsBook(heroComp);
  uint8_t i = 0;
  for (auto [spelLevel, spelVal] : spellsMap) {
    if (i >= 16) {
      break;
    }
    posRect = {splSlot[i].x + leftUp.x, splSlot[i].y + leftUp.y, 78, 65};
    auto textures = Global::defCache["Spells.DEF/0"];
    auto texture = textures[spelVal];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    auto spellPair = SpellSys::heroSplLevel(&heroComp, spelVal);
    switch (Global::splSchool) {
    case 0: {
      texture = Global::defCache["SplevE.DEF/0"][spellPair.second];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      break;
    }
    case 1: {
      texture = Global::defCache["SplevW.DEF/0"][spellPair.second];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      break;
    }
    case 2: {
      texture = Global::defCache["SplevF.DEF/0"][spellPair.second];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      break;
    }
    case 3: {
      texture = Global::defCache["SplevA.DEF/0"][spellPair.second];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      break;
    }
    case 4: {
      switch (spellPair.first) {
      case 0: {
        texture = Global::defCache["SplevE.DEF/0"][spellPair.second];
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        break;
      }
      case 1: {
        texture = Global::defCache["SplevW.DEF/0"][spellPair.second];
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        break;
      }
      case 2: {
        texture = Global::defCache["SplevF.DEF/0"][spellPair.second];
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        break;
      }
      case 3: {
        texture = Global::defCache["SplevA.DEF/0"][spellPair.second];
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        break;
      }
      }
      break;
    }
    }
    i++;
  }
}

static bool hasLeftPage() { return Global::splPage > 0; }

static bool hasRightPage() {
  auto &registry = World::registrys[World::level];
  auto heroComp = registry.get<HeroComp>(Global::heroEnt);
  std::multimap<uint8_t, uint8_t> spellsMap;
  std::set<uint8_t> spellsSet = heroComp.spells;
  if (Global::splBattle) {
    auto it = spellsSet.lower_bound(10);
    spellsSet.erase(spellsSet.begin(), it);
  } else {
    auto it = spellsSet.upper_bound(10);
    spellsSet.erase(it, spellsSet.end());
  }
  if (Global::splSchool == 4) {
    for (auto spell : spellsSet) {
      spellsMap.insert({SpellCfg::SpellLevel.at(spell), spell});
    }
  } else {
    for (auto spell : spellsSet) {
      if (SpellCfg::SpellSchool.at(spell)[Global::splSchool]) {
        spellsMap.insert({SpellCfg::SpellLevel.at(spell), spell});
      }
    }
  }
  return (Global::splPage + 1) * 16 < spellsMap.size();
}

static void drawPage() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  if (hasLeftPage()) {
    posRect = {static_cast<float>(leftUp.x) + 97,
               static_cast<float>(leftUp.y) + 77, 33, 39};
    SDL_RenderTexture(Window::renderer, Global::pcxCache["SpelTrnL.pcx"][0],
                      nullptr, &posRect);
  }
  if (hasRightPage()) {
    posRect = {static_cast<float>(leftUp.x) + 487,
               static_cast<float>(leftUp.y) + 72, 33, 39};
    SDL_RenderTexture(Window::renderer, Global::pcxCache["SpelTrnR.pcx"][0],
                      nullptr, &posRect);
  }
}
bool SpellSys::run() {
  drawBackGround();
  drawSchoolTab();
  drawSchoolBook();
  drawPage();
  return true;
}

static bool clickTabs() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  const SDL_FRect tabs[5] = {{leftUp.x + 524, leftUp.y + 95, 84, 35},
                             {leftUp.x + 524, leftUp.y + 151, 84, 35},
                             {leftUp.x + 524, leftUp.y + 209, 84, 35},
                             {leftUp.x + 524, leftUp.y + 271, 84, 35},
                             {leftUp.x + 524, leftUp.y + 331, 84, 35}};
  for (uint8_t i = 0; i < std::size(tabs); i++) {
    if (SDL_PointInRectFloat(&point, &tabs[i])) {
      if (schools[i] != Global::splSchool) {
        Global::splSchool = schools[i];
        Global::splPage = 0;
        return true;
      }
    }
  }
  return false;
}

static bool clickPage() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  if (hasLeftPage()) {
    posRect = {static_cast<float>(leftUp.x) + 97,
               static_cast<float>(leftUp.y) + 77, 33, 39};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      Global::splPage -= 1;
      return true;
    }
  }
  if (hasRightPage()) {
    posRect = {static_cast<float>(leftUp.x) + 487,
               static_cast<float>(leftUp.y) + 72, 33, 39};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      Global::splPage += 1;
      return true;
    }
  }
  return false;
}

static bool clickBottomButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};

  posRect = {leftUp.x + 220, leftUp.y + 404, 35, 48};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    Global::splBattle = true;
    Global::splPage = 0;
    return true;
  }
  posRect = {leftUp.x + 354, leftUp.y + 404, 35, 48};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    Global::splBattle = false;
    Global::splPage = 0;
    return true;
  }
  posRect = {leftUp.x + 478, leftUp.y + 404, 35, 48};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    World::exitScrn();
    return true;
  }
  return false;
}

static bool clickSpell(bool leftClick) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto &registry = World::registrys[World::level];
  auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
  std::multimap<uint8_t, uint8_t> spellsMap = curSpellsBook(heroComp);
  uint8_t i = 0;
  for (auto [spelLevel, spelVal] : spellsMap) {
    if (i >= 16) {
      break;
    }
    posRect = {splSlot[i].x + leftUp.x, splSlot[i].y + leftUp.y, 78, 65};
    auto skillLevel = SpellSys::heroSplLevel(&heroComp, spelVal).second;
    auto manaCost = SpellCfg::SpellCost[spelVal][skillLevel];
    if (SDL_PointInRectFloat(&point, &posRect) && heroComp.mana >= manaCost) {
      if (leftClick) {
        SpellCfg::SpellFunc.at(spelVal)(
            std::pair<entt::entity, uint8_t>{Global::heroEnt, skillLevel});
        if (spelVal > 9) {
          heroComp.mana -= manaCost;
        }
      } else {
        SpellSys::showSplComfirm(leftClick, spelVal, skillLevel);
      }
      return true;
    }
    i++;
  }
  return false;
}

bool SpellSys::leftMouseUp(float x, float y) {
  if (clickTabs()) {
    return false;
  }
  if (clickPage()) {
    return false;
  }
  if (clickBottomButton()) {
    return false;
  }
  if (clickSpell(true)) {
    return false;
  }
  return true;
}

bool SpellSys::rightMouseDown(float x, float y) {
  if (clickSpell(false)) {
    return false;
  }
  return true;
}

static void close() { World::exitScrn(); }

bool SpellSys::keyUp(uint16_t key) {
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

void SpellSys::showSplComfirm(bool leftClick, uint16_t id, uint16_t i) {
  auto confirmbakW = 480;
  auto confirmbakH = 230;
  Global::confirmdraw = [confirmbakW, confirmbakH, id, i]() {
    SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                      Global::viewPort.h / 2 - confirmbakH / 2};
    auto strPool = *Lang::strPool[Global::langIndex];
    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(240, 224, 104, 255);
    auto str = strPool[2497 + id * 5];
    if (i > 0) {
      str = strPool[5 + i - 1] + str;
    }
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15, str);
    FreeTypeSys::setColor(255, 255, 255, 255);
    str = strPool[2497 + id * 5 + i + 1];
    FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 40, str);
  };
  if (leftClick) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    auto type = ((uint8_t)Enum::SCNTYPE::MOD);
    World::enterConfirm(confirmbakW, confirmbakH, type);
  } else {
    auto type = ((uint8_t)Enum::SCNTYPE::POP);
    World::enterConfirm(confirmbakW, confirmbakH, type);
  }
}