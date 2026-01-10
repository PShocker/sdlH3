#include "HutMagSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/MagEyeComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Sys/FogSys.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/CameraSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static void view() {
  auto registrys = &World::registrys[World::level];
  if (registrys->view<MagEyeComp>()->size() > 0) {
    Global::hutMagIndex = 0;
    Global::hutMagTime = Window::dtNow + 5000;
  } else {
    World::exitScrn();
  }
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  b.func = view;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, y - bakH / 2 + 15,
                          strPool[926 + (uint8_t)ObjectType::HUT_OF_MAGI]);
  return;
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == HutMagSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static bool drawMagEye() {
  auto registry = &World::registrys[World::level];
  auto view = registry->view<MagEyeComp>();
  if (Global::hutMagIndex + 1 > view->size()) {
    auto positionComp = &registry->get<PositionComp>(Global::heroEnt);
    CameraSys::focus(positionComp->point.x + 48, positionComp->point.y + 48);
    return false;
  }
  std::vector<entt::entity> v(view.begin(), view.end());
  auto ent = v[Global::hutMagIndex];
  auto &oComp = registry->get<ObjectComp>(ent);
  auto playerIdComp = &registry->get<PlayerIdComp>(Global::heroEnt);

  for (const auto point : FogSys::generateVerticalHexagon(5)) {
    int16_t rX =
        std::clamp((int)oComp.x + point.x, 0, (int)Global::mapSize - 1);
    int16_t rY =
        std::clamp((int)oComp.y + point.y, 0, (int)Global::mapSize - 1);
    Global::fogs[playerIdComp->id][World::level][rX + rY * Global::mapSize] =
        true;
  }

  CameraSys::focus(oComp.x * 32 + 16, oComp.y * 32 + 16);
  if (Global::hutMagTime <= Window::dtNow) {
    Global::hutMagTime = Window::dtNow + 5000;
    Global::hutMagIndex += 1;
  }

  return true;
}
bool HutMagSys::run() {
  if (Global::hutMagIndex == -1) {
    drawBackGround();
    drawButton();
  } else if (!drawMagEye()) {
    World::exitScrn();
  }
  return true;
}

bool HutMagSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool HutMagSys::keyUp(uint16_t key) { return true; }