#include "CreatureSys.h"
#include "AdvMapSys.h"
#include "Cfg/CreatureCfg.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/DwellingSys.h"
#include "Sys/gui/HeroScrSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <string>
#include <vector>

int32_t CreatureSys::heroCreLuk(uint8_t level, entt::entity heroEnt,
                                uint16_t creId, uint8_t creType) {
  int32_t r = 0;
  auto &hComp = World::registrys[level].get<HeroComp>(heroEnt);
  r = HeroScrSys::heroLuk(hComp);
  // 获取生物幸运
  switch (creType) {}
  return r;
}

int32_t CreatureSys::heroCreMor(uint8_t level, entt::entity heroEnt,
                                uint16_t creId, uint8_t creType) {
  int32_t r = 0;
  if (creId) {
  }
  auto &hComp = World::registrys[level].get<HeroComp>(heroEnt);
  r = HeroScrSys::heroMor(hComp);
  // 获取生物士气
  switch (creType) {}
  return r;
}

static void close() { World::exitScrn(); }

static bool canDissmiss() {
  if (Global::creType == (uint8_t)Enum::CRETYPE::MOD_HERO) {
    auto [level, heroEnt] = Global::creHeroPair;
    auto registry = &World::registrys[level];
    auto heroComp = &registry->get<HeroComp>(heroEnt);
    int8_t num = 0;
    for (auto [id, count] : heroComp->creatures) {
      if (count != 0) {
        num++;
      }
    }
    if (num > 1) {
      return true;
    }
  }
  return false;
}

static void dismiss() {
  auto index = Global::creIndex;
  auto [level, heroEnt] = Global::creHeroPair;
  Global::confirmCallBack = [heroEnt, level, index]() {
    auto registry = &World::registrys[level];
    auto heroComp = &registry->get<HeroComp>(heroEnt);
    heroComp->creatures[index] = {0xffff, 0};
  };
  World::enterConfirm(100, 100, ((uint8_t)Enum::SCNTYPE::MOD));
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  if (Global::creType == (uint8_t)Enum::CRETYPE::POP_BAT ||
      Global::creType == (uint8_t)Enum::CRETYPE::POP_HERO ||
      Global::creType == (uint8_t)Enum::CRETYPE::POP_DWE) {
    return v;
  }
  Button b;

  b.textures = Global::defCache["hsbtns.DEF/0"];
  b.r = {230, 236, 52, 36};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["IVIEWCR2.DEF/0"];
  b.r = {232, 188, 46, 32};
  b.func = dismiss;
  b.disable = !canDissmiss();
  v.push_back(b);

  b.textures = Global::defCache["IViewCr.DEF/0"];
  b.r = {180, 188, 46, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  posRect = {leftUp.x, leftUp.y, 298, 311};
  auto texture = Global::pcxCache["CrStkPu.pcx"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(248, 240, 216, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::draw(leftUp.x + 153, leftUp.y + 46, strPool[2339]);
  FreeTypeSys::draw(leftUp.x + 153, leftUp.y + 65, strPool[2340]);
  FreeTypeSys::draw(leftUp.x + 153, leftUp.y + 84, strPool[2341]);
  FreeTypeSys::draw(leftUp.x + 153, leftUp.y + 103, strPool[2342]);
  FreeTypeSys::draw(leftUp.x + 153, leftUp.y + 122, strPool[2343]);
  FreeTypeSys::draw(leftUp.x + 153, leftUp.y + 141, strPool[2344]);
  FreeTypeSys::draw(leftUp.x + 153, leftUp.y + 160, strPool[2345]);
}

static void drawCreatures() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  auto id = Global::crePair.first;
  auto group = Global::creGroup;
  auto textures = Global::defCache[CreatureCfg::creatureGraphics.at(id) + "/" +
                                   std::to_string(group)];
  DwellingSys::drawCreatureBak(leftUp.x + 20, leftUp.y + 47, id, group,
                               Global::creFrameIndex % textures.size(), 0xff);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == CreatureSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void creAnimate() {
  Global::creFrameTime += Window::deltaTime;
  if (Global::creFrameTime >= 90) {
    Global::creFrameTime = 0;
    Global::creFrameIndex += 1;
    // if (condition) {
    // }
  }
}

static void drawCreInfo() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  auto id = Global::crePair.first;
  auto v = CreatureCfg::creatureAttr.at(id);
  // Hit Points,Speed,Attack,Defense,Low,High,Shots,Spells,Low,High
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(248, 240, 216, 255);
  switch (Global::creType) {
  case (uint8_t)Enum::CRETYPE::MOD_DWE:
  case (uint8_t)Enum::CRETYPE::POP_DWE: {
    // atk
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 46, v[2]);
    // def
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 65, v[3]);
    // shoot
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 84, v[6]);
    // dmg
    auto str = FreeTypeSys::str(v[4]) + u"-" + FreeTypeSys::str(v[5]);
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 103, str);

    // life
    str = FreeTypeSys::str(v[0]);
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 122, str);

    // speed
    str = FreeTypeSys::str(v[1]);
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 160, str);

    break;
  }
  case (uint8_t)Enum::CRETYPE::MOD_HERO:
  case (uint8_t)Enum::CRETYPE::POP_HERO: {
    auto [level, heroEnt] = Global::creHeroPair;
    auto hComp = World::registrys[level].get<HeroComp>(heroEnt);
    // atk
    auto str = FreeTypeSys::str(v[2]) + u"(" +
               FreeTypeSys::str(v[2] + hComp.primSkills[0]) + u")";
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 46, str);
    // def
    str = FreeTypeSys::str(v[3]) + u"(" +
          FreeTypeSys::str(v[3] + hComp.primSkills[1]) + u")";
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 65, str);
    // shoot
    str = FreeTypeSys::str(v[6]);
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 84, str);
    // dmg
    str = FreeTypeSys::str(v[4]) + u"-" + FreeTypeSys::str(v[5]);
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 103, str);

    // life
    str = FreeTypeSys::str(v[0]);
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 122, str);
    // remain life
    // str = FreeTypeSys::str(v[4]) + u"-" + FreeTypeSys::str(v[0]);
    // FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 141, str);

    // speed
    str = FreeTypeSys::str(v[1]);
    FreeTypeSys::drawLeft(leftUp.x + 276, leftUp.y + 160, str);
    break;
  }
  case (uint8_t)Enum::CRETYPE::MOD_BAT:
  case (uint8_t)Enum::CRETYPE::POP_BAT: {

    break;
  }
  }
}

static void drawMorLuk() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  SDL_FRect posRect;

  auto mors = Global::defCache["IMRL42.def/0"];
  auto luks = Global::defCache["ILCK42.def/0"];

  switch (Global::creType) {
  case (uint8_t)Enum::CRETYPE::MOD_DWE:
  case (uint8_t)Enum::CRETYPE::POP_DWE: {
    auto texture = mors[3];
    posRect = {leftUp.x + 24, leftUp.y + 189, static_cast<float>(texture->w),
               static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    texture = luks[3];
    posRect = {leftUp.x + 76, leftUp.y + 189, static_cast<float>(texture->w),
               static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  }
  }
}

static void drawText() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  SDL_FRect posRect;
  FreeTypeSys::setSize(12);
  FreeTypeSys::setColor(248, 240, 216, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  std::u16string s = strPool[2347 + Global::crePair.first];
  FreeTypeSys::draw(leftUp.x + 22, leftUp.y + 235, s);
}

bool CreatureSys::run() {
  creAnimate();
  drawBackGround();
  drawCreatures();
  drawButton();
  drawCreInfo();
  drawMorLuk();
  drawText();
  return true;
}

bool CreatureSys::keyUp(uint16_t key) {
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

bool CreatureSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool CreatureSys::rightMouseUp(float x, float y) {
  if (Global::creType == (uint8_t)Enum::CRETYPE::POP_BAT ||
      Global::creType == (uint8_t)Enum::CRETYPE::POP_HERO ||
      Global::creType == (uint8_t)Enum::CRETYPE::POP_DWE) {
    World::iterateSystems.push_back([]() -> bool {
      World::exitScrn();
      return false;
    });
  }
  return false;
}