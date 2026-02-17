#include "SpellSys.h"

#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Set/SpellSet.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <any>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

/*
 FIRE_MAGIC = ,
    AIR_MAGIC = ,
    WATER_MAGIC = ,
    EARTH_MAGIC = ,
*/

std::pair<uint8_t, uint8_t> SpellSys::spellLevel(HeroComp *heroComp,
                                                 uint8_t id) {
  uint8_t r = 0;
  uint8_t sch;
  auto school = SpellSet::spells[id].school;
  for (uint8_t i = 0; i < school.size(); i++) {
    if (school[i]) {
      auto secLevel = HeroScrSys::heroSecLevel(*heroComp, Enum::FIRE_MAGIC + i);
      auto r1 = secLevel + 1;
      if (r1 > r) {
        r = r1;
        sch = i;
      }
    }
  }
  return {sch, r};
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

static std::vector<uint8_t> spellsBook(HeroComp &heroComp) {
  std::vector<uint8_t> r;
  auto spells = heroComp.spells;
  if (Global::splBattle) {
    auto sAdv = SpellSet::spellsAdv;
    for (auto s : sAdv) {
      spells.erase(s->index);
    }
  } else {
    auto sBat = SpellSet::spellsBat;
    for (auto s : sBat) {
      spells.erase(s->index);
    }
  }
  if (Global::splSchool != 4) {
    auto sSch = SpellSet::spellsSchool[Global::splSchool];
    std::set<uint8_t> sSch2;
    for (auto s : sSch) {
      sSch2.insert(s->index);
    }
    std::erase_if(spells, [&](uint8_t val) { return !sSch2.contains(val); });
  }
  for (auto i = 0; i < SpellSet::spellsLvl.size(); i++) {
    auto splLvl = SpellSet::spellsLvl[i];
    for (auto s : splLvl) {
      if (spells.contains(s->index)) {
        r.push_back(s->index);
      }
    }
  }

  return r;
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
  auto spellBooks = spellsBook(heroComp);
  // for (auto [spelLevel, spelVal] : spellsMap) {
  for (uint8_t i = 0; i < 16; i++) {
    auto page = Global::splPage * 16;
    if (page > spellBooks.size()) {
      break;
    }
    auto spelVal = spellBooks[page + i];
    posRect = {splSlot[i].x + leftUp.x, splSlot[i].y + leftUp.y, 78, 65};
    auto textures = Global::defCache["Spells.DEF/0"];
    auto texture = textures[spelVal];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    auto spellPair = SpellSys::spellLevel(&heroComp, spelVal);
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
  }
}

static bool hasLeftPage() { return Global::splPage > 0; }

static bool hasRightPage() {
  auto &registry = World::registrys[World::level];
  auto heroComp = registry.get<HeroComp>(Global::heroEnt);
  auto spells = heroComp.spells;
  if (Global::splBattle) {
    auto sAdv = SpellSet::spellsAdv;
    for (auto s : sAdv) {
      spells.erase(s->index);
    }
  } else {
    auto sBat = SpellSet::spellsBat;
    for (auto s : sBat) {
      spells.erase(s->index);
    }
  }
  if (Global::splSchool != 4) {
    auto sSch = SpellSet::spellsSchool[Global::splSchool];
    std::set<uint8_t> sSch2;
    for (auto s : sSch) {
      sSch2.insert(s->index);
    }
    std::erase_if(spells, [&](uint8_t val) { return !sSch2.contains(val); });
  }
  return (Global::splPage + 1) * 16 < spells.size();
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

static bool clickSpell(uint8_t clickType) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 620) / 2,
                    (Global::viewPort.h - 595) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  auto &registry = World::registrys[World::level];
  auto &heroComp = registry.get<HeroComp>(Global::heroEnt);
  auto spellBooks = spellsBook(heroComp);
  for (uint8_t i = 0; i < 16; i++) {
    auto page = Global::splPage * 16;
    if (page > spellBooks.size()) {
      break;
    }
    auto spelVal = spellBooks[page + i];
    posRect = {splSlot[i].x + leftUp.x, splSlot[i].y + leftUp.y, 78, 65};
    auto [skillSch, skillLevel] = SpellSys::spellLevel(&heroComp, spelVal);
    auto secLevel =
        HeroScrSys::heroSecLevel(heroComp, Enum::FIRE_MAGIC + skillSch);
    auto manaCost = SpellSet::spells[spelVal].manaCost[secLevel + 1];
    if (SDL_PointInRectFloat(&point, &posRect) && heroComp.mana >= manaCost) {
      if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
        SpellSet::spells[spelVal].func(NULL);
      } else {
        SpellSys::showSpellComfirm(clickType, spelVal, skillLevel);
      }
      return true;
    }
  }

  return false;
}

bool SpellSys::leftMouseUp(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (clickTabs()) {
    return false;
  }
  if (clickPage()) {
    return false;
  }
  if (clickBottomButton()) {
    return false;
  }
  if (clickSpell(clickType)) {
    return false;
  }
  return true;
}

bool SpellSys::rightMouseDown(float x, float y) {
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickSpell(clickType)) {
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

void SpellSys::showSpellComfirm(uint8_t clickType, uint16_t id, uint16_t i) {
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
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    auto type = ((uint8_t)Enum::SCNTYPE::MOD);
    World::enterConfirm(confirmbakW, confirmbakH, type);
  } else {
    auto type = ((uint8_t)Enum::SCNTYPE::POP);
    World::enterConfirm(confirmbakW, confirmbakH, type);
  }
}