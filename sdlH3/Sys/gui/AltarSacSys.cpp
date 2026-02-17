#include "AltarSacSys.h"

#include "Comp/HeroComp.h"
#include "Comp/PlayerIdComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "HeroScrSys.h"
#include "SDL3/SDL_render.h"
#include "Set/ArtifactSet.h"
#include "Set/CreatureSet.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/base/AltArtPanelSys.h"
#include "Sys/gui/base/ArtifactsOfHeroSys.h"
#include "Sys/gui/base/SliderSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "base/AltCrePanelSys.h"
#include <cstdint>
#include <vector>

static uint32_t maxExp() {
  uint32_t e = 0;
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    for (auto [k, v] : Global::alts) {
      auto exp = ArtifactSet::artifacts.at(v).experience;
      e += exp;
    }
    break;
  }
  case Enum::ALTAR::CRE: {
    for (auto [k, v] : Global::alts) {
      if (k == -1) {
        continue;
      }

      // auto exp = CreatureCfg::creatureExp.at(k);
      auto exp = CreatureSet::fullCreatures[k]->experience;
      e += exp * v;
    }
    break;
  }
  case Enum::ALTAR::SKE:
    break;
  }
  return e;
}

static void changeType() {
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    Global::altType = (uint8_t)Enum::ALTAR::CRE;
    Global::alts.assign(7, {-1, 0});
    Global::altSliderNum = 0;
    break;
  }
  case Enum::ALTAR::CRE: {
    Global::altType = (uint8_t)Enum::ALTAR::ART;
    Global::alts.clear();
    break;
  }
  default:
    break;
  }
}

static void deal() {
  auto heroComp =
      &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto alt = Global::alts;
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    for (const auto &pair : alt) {
      auto i = pair.first;
      auto artId = pair.second;
      if (i != 0xff) {
        if (i < 0) {
          i = -i - 1;
          heroComp->artifacts[i] = 0xff;
        } else {
          heroComp->artifactsInBackpack[i] = 0xff;
        }
        heroComp->exp += ArtifactSet::artifacts.at(artId).experience;
      }
    }
    break;
  }
  case Enum::ALTAR::CRE: {
    for (uint8_t i = 0; i < alt.size(); i++) {
      const auto &pair = alt[i];
      auto id = pair.first;
      auto num = pair.second;
      if (id != 0xff && num != 0) {
        heroComp->creatures[i].first -= num;
        heroComp->exp += CreatureSet::fullCreatures[id]->experience;
      }
    }
    break;
  }
  default:
    break;
  }
  Global::alts.clear();
  Global::altIndex = 0xff;
  Global::altSliderNum = 0;
}

static void toMax() {
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  auto count = heroComp.creatures[Global::altIndex].second;
  Global::altSliderNum = count;
  Global::alts[Global::altIndex] = {
      heroComp.creatures[Global::altIndex].first,
      heroComp.creatures[Global::altIndex].second};
}

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    b.textures = Global::defCache["ALTSACC.DEF/0"];
    b.r = {516, 421, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["ALTSACR.DEF/0"];
    b.r = {268, 520, 64, 32};
    b.func = changeType;
    if (maxExp() != 0) {
      b.disable = false;
    } else {
      b.disable = true;
    }
    v.push_back(b);

    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);
    break;
  }
  case Enum::ALTAR::CRE: {

    b.textures = Global::defCache["ALTART.DEF/0"];
    b.r = {516, 421, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["IRCBTNS.DEF/0"];
    b.r = {145, 520, 64, 32};
    b.func = toMax;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["ALTSACR.DEF/0"];
    b.r = {268, 520, 64, 32};
    b.func = changeType;
    if (maxExp() != 0) {
      b.disable = false;
    } else {
      b.disable = true;
    }
    v.push_back(b);

    b.textures = Global::defCache["ALTARMY.DEF/0"];
    b.r = {393, 520, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    b.textures = Global::defCache["IOK6432.def/0"];
    b.r = {516, 520, 64, 32};
    b.func = changeType;
    b.disable = false;
    v.push_back(b);

    break;
  }
  case Enum::ALTAR::SKE:
    break;
  }
  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  auto playerId =
      World::registrys[World::level].get<PlayerIdComp>(Global::heroEnt).id;
  SDL_Texture *texture;
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    texture = Global::pcxCache["ALTRART2.pcx"][Global::playerId];
    break;
  }
  case Enum::ALTAR::CRE: {
    texture = Global::pcxCache["ALTARMON.pcx"][Global::playerId];
    break;
  }
  default:
    break;
  }
  posRect = {leftUp.x, leftUp.y, static_cast<float>(texture->w),
             static_cast<float>(texture->h)};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
}

static void drawCreature() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::CRE: {
    auto heroComp =
        &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    AltCrePanelSys::draw(heroComp->creatures, leftUp.x + 46, leftUp.y + 111);
    std::vector<std::pair<uint16_t, uint32_t>> target;
    for (const auto &pair : Global::alts) {
      target.emplace_back(static_cast<uint16_t>(pair.first), pair.second);
    }
    AltCrePanelSys::draw(target, leftUp.x + 335, leftUp.y + 111);
    break;
  }
  default:
    break;
  }
}

static void drawArtifact() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    auto heroComp =
        &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    ArtifactsOfHeroSys::drawBackPack(heroComp, leftUp.x - 302, leftUp.y - 5);
    ArtifactsOfHeroSys::drawEquip(heroComp, leftUp.x - 300, leftUp.y - 3);
    AltArtPanelSys::draw(leftUp.x + 315, leftUp.y + 52);
    break;
  }
  default:
    break;
  }
}

static void drawArtBorder() {
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  auto alts = Global::alts;
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    for (auto [i, id] : alts) {
      if (i < 0) {
        ArtifactsOfHeroSys::drawEquipBorder(leftUp.x - 300, leftUp.y - 3,
                                            -i - 1);
      } else {
        ArtifactsOfHeroSys::drawBackPackBorder(leftUp.x - 302, leftUp.y - 5, i);
      }
    }
    break;
  }
  case Enum::ALTAR::CRE: {
    break;
  }
  default:
    break;
  }
}

static void drawCreBorder() {
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::CRE: {
    if (Global::altIndex != 0xff) {
      auto &heroComp =
          World::registrys[World::level].get<HeroComp>(Global::heroEnt);
      if (heroComp.creatures[Global::altIndex].second > 0) {
        AltCrePanelSys::drawBorder(leftUp.x + 46, leftUp.y + 111,
                                   Global::altIndex);
        AltCrePanelSys::drawBorder(leftUp.x + 335, leftUp.y + 111,
                                   Global::altIndex);
      }
    }
    break;
  }
  default:
    break;
  }
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == AltarSacSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawSelect() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    auto [backpackIndex, backpackArtId] = ArtifactsOfHeroSys::clickBackPack(
        &heroComp, leftUp.x - 302, leftUp.y - 5, Global::artPageIndex[0]);
    auto [equipIndex, equipArtId] =
        ArtifactsOfHeroSys::clickEquip(&heroComp, leftUp.x - 300, leftUp.y - 3);
    uint16_t artId = 0xffff;
    if (backpackIndex != 0xff) {
      artId = backpackArtId;
    } else if (equipIndex != 0xff) {
      artId = equipArtId;
    }
    if (artId != 0xffff) {
      auto textures = Global::defCache["Artifact.def/0"];
      auto texture = textures[artId];
      posRect = {static_cast<float>((int)leftUp.x + 280),
                 static_cast<float>((int)leftUp.y + 442),
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
    break;
  }
  case Enum::ALTAR::CRE: {
    if (Global::altIndex != 0xff) {
      auto cre = heroComp.creatures[Global::altIndex];
      if (cre.second != 0) {
        auto texture = Global::defCache["TWCRPORT.def/0"][cre.first + 2];
        posRect = {static_cast<float>((int)leftUp.x + 150),
                   static_cast<float>((int)leftUp.y + 423),
                   static_cast<float>(texture->w),
                   static_cast<float>(texture->h)};
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
        SDL_RenderRect(Window::renderer, &posRect);

        posRect.x += 246;
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
        SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
        SDL_RenderRect(Window::renderer, &posRect);
      }
    }
    break;
  }
  default:
    break;
  }
}

static void drawSlider() {
  if ((Enum::ALTAR)Global::altType == Enum::ALTAR::CRE) {
    SDL_FRect posRect;
    SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                      (Global::viewPort.h - 595) / 2};
    auto num = Global::altSliderNum;
    auto heroComp =
        &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    auto count = heroComp->creatures[Global::altIndex].second;
    SliderSys::drawHor(leftUp.x + 231, leftUp.y + 481, 137, (float)num / count);
  }
}
bool AltarSacSys::run() {
  drawBackGround();
  drawCreature();
  drawArtifact();
  drawButton();
  drawArtBorder();
  drawCreBorder();
  drawSelect();
  drawSlider();
  return true;
}

bool AltarSacSys::leftMouseUp(float x, float y) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }

  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    auto &heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    auto [backpackIndex, backpackArtId] = ArtifactsOfHeroSys::clickBackPack(
        &heroComp, leftUp.x - 302, leftUp.y - 5, Global::artPageIndex[0]);
    auto [equipIndex, equipArtId] =
        ArtifactsOfHeroSys::clickEquip(&heroComp, leftUp.x - 300, leftUp.y - 3);
    int16_t index = 0xff;
    int16_t artId = 0xff;
    if (backpackIndex != 0xff) {
      index = backpackIndex;
      artId = backpackArtId;
    } else if (equipIndex != 0xff) {
      index = -(equipIndex + 1);
      artId = equipArtId;
    }
    if (index != 0xff) {
      auto it = std::find_if(Global::alts.begin(), Global::alts.end(),
                             [index](const std::pair<int16_t, uint32_t> &p) {
                               return p.first == index;
                             });
      if (it != Global::alts.end()) {
        // 如果存在，删除
        Global::alts.erase(it);
      } else {
        // 如果不存在，插入
        Global::alts.push_back({index, artId});
      }
    }
    break;
  }
  case Enum::ALTAR::CRE: {
    auto heroComp =
        &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    if (auto i = AltCrePanelSys::click(leftUp.x + 47, leftUp.y + 112);
        i != Global::altIndex && i != 0xff) {
      Global::altSliderNum = 0;
      Global::altIndex = i;
      return false;
    }
    auto count = heroComp->creatures[Global::altIndex].second;
    if (auto num = SliderSys::clickHor(leftUp.x + 231, leftUp.y + 481, 137,
                                       Global::altSliderNum, count);
        num != Global::altSliderNum) {
      Global::alts[Global::altIndex] = {
          heroComp->creatures[Global::altIndex].first, num};
      Global::altSliderNum = num;
      return false;
    }
    break;
  }
  default:
    break;
  }
  return true;
}

bool AltarSacSys::rightMouseDown(float x, float y) {
  SDL_FRect posRect;
  SDL_FPoint leftUp{(Global::viewPort.w - 601) / 2,
                    (Global::viewPort.h - 595) / 2};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};

  switch ((Enum::ALTAR)Global::altType) {
  case Enum::ALTAR::ART: {
    auto &heroComp =
        World::registrys[World::level].get<HeroComp>(Global::heroEnt);
    auto [backpackIndex, backpackArtId] = ArtifactsOfHeroSys::clickBackPack(
        &heroComp, leftUp.x - 302, leftUp.y - 5, Global::artPageIndex[0]);
    auto [equipIndex, equipArtId] =
        ArtifactsOfHeroSys::clickEquip(&heroComp, leftUp.x - 300, leftUp.y - 3);
    int16_t artId = 0xff;
    if (backpackIndex != 0xff) {
      artId = backpackArtId;
    } else if (equipIndex != 0xff) {
      artId = equipArtId;
    }
    if (artId != 0xff) {
      HeroScrSys::showArtifactComfirm(artId);
      return false;
    }
    break;
  }
  case Enum::ALTAR::CRE:
  case Enum::ALTAR::SKE: {
    if (auto i = AltCrePanelSys::click(leftUp.x + 47, leftUp.y + 112);
        i != 0xff) {
      auto heroComp =
          &World::registrys[World::level].get<HeroComp>(Global::heroEnt);
      if (heroComp->creatures[i].second != 0) {
        World::enterCreature({World::level, Global::heroEnt},
                             heroComp->creatures[i],
                             (uint8_t)Enum::CRETYPE::POP_HERO);
        return false;
      }
    }
    break;
  }
  }
  return true;
}

bool AltarSacSys::keyUp(uint16_t key) {
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
