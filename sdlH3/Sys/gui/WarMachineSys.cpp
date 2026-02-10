#include "WarMachineSys.h"
#include "AdvMapSys.h"
#include "Cfg/CreatureCfg.h"
#include "Cfg/WarMachineCfg.h"
#include "Comp/HeroComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "WarMachineFacSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <string>

static void close() { World::exitScrn(); }

static void dismiss() {
  auto index = Global::goalIndex;
  entt::entity heroEnt = Global::heroEnt;
  if (Global::creIndex) {
    heroEnt = Global::goalEnt;
  }
  Global::confirmCallBack = [heroEnt, index]() {
    auto registry = &World::registrys[World::level];
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
  b.func = close;
  b.disable = false;
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

static void drawMachine() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  auto id = Global::crePair.first;
  auto group = Global::creGroup;
  auto defPath = WarMachineCfg::warMachineGraphics.at(id);
  auto textures = Global::defCache[defPath + "/" + std::to_string(group)];
  WarMachineFacSys::drawMachineBak(leftUp.x + 20, leftUp.y + 47, id, group,
                                   Global::creFrameIndex % textures.size(), 0);
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == WarMachineSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

void WarMachineSys::warAnimate(uint64_t &warFrameTime, uint64_t &warFrameIndex,
                               uint64_t &warGroup, uint16_t warId) {

  warFrameTime += Window::deltaTime;
  if (warFrameTime >= 90) {
    warFrameTime = 0;
    warFrameIndex += 1;

    auto textures =
        Global::defCache[WarMachineCfg::warMachineGraphics.at(warId) + "/" +
                         std::to_string(warGroup)];
    if (warFrameIndex >= textures.size()) {
      warFrameIndex = 0;
      std::vector<uint8_t> arr;
      arr = {
          CreatureCfg::ACTION_DEFEND,
          CreatureCfg::ACTION_STAND,
          CreatureCfg::ACTION_GET_HIT,
      };
      if (Global::defCache.contains(
              WarMachineCfg::warMachineGraphics.at(warId) + "/11")) {
        arr.push_back(CreatureCfg::ACTION_SHOOT_UP);
      }
      std::uniform_int_distribution<> distrib(0, std::size(arr) - 1);
      // 生成随机索引并选择元素
      int randomIndex = distrib(Global::gen);
      warGroup = arr[randomIndex];
    }
  }
}

bool WarMachineSys::run() {
  warAnimate(Global::creFrameTime, Global::creFrameIndex, Global::creGroup,
             Global::crePair.first);
  drawBackGround();
  drawMachine();
  drawButton();
  return true;
}

bool WarMachineSys::keyUp(uint16_t key) {
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

bool WarMachineSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 311) / 2)};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool WarMachineSys::rightMouseUp(float x, float y) {
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