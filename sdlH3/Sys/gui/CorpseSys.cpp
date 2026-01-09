#include "CorpseSys.h"
#include "AdvMapSys.h"
#include "AdvPopSys.h"
#include "Comp/CorpseComp.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "HeroScrSys.h"
#include "Lang/Lang.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <optional>
#include <vector>

static float bakW = 450;
static float bakH = 340;

static bool visited() {
  auto &cpComp =
      World::registrys[World::level].get<CorpseComp>(Global::goalEnt);
  if (cpComp.artifacts.has_value()) {
    return true;
  }
  return false;
}

static void receive() {
  auto &cpComp =
      World::registrys[World::level].get<CorpseComp>(Global::goalEnt);
  auto &heroComp =
      World::registrys[World::level].get<HeroComp>(Global::heroEnt);
  if (cpComp.artifacts.has_value()) {
    heroComp.artifactsInBackpack.push_back(cpComp.artifacts.value());
    cpComp.artifacts = std::nullopt;
  }
  heroComp.visited.insert((uint8_t)ObjectType::CORPSE);
  World::exitScrn();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["iOKAY.def/0"];
  b.r = {bakW / 2 - 32, bakH - 60, 64, 30};
  b.func = receive;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  auto x = Global::viewPort.w / 2;
  auto y = Global::viewPort.h / 2;
  AdvPopSys::drawBackGround(x, y, bakW, bakH, Global::playerId);

  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(240, 224, 104, 255);
  auto strPool = *Lang::strPool[Global::langIndex];
  std::u16string s = strPool[945];
  FreeTypeSys::drawCenter(x + bakW / 2, y - bakH / 2 + 50, s);
  return;
}

const SDL_FRect artPosition = {bakW / 2 - 22, bakH / 3, 44, 44};

static void draw() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto &cpComp =
      World::registrys[World::level].get<CorpseComp>(Global::goalEnt);
  if (cpComp.artifacts.has_value()) {
    auto texture = Global::defCache["Artifact.def/0"][cpComp.artifacts.value()];
    posRect = {leftUp.x + artPosition.x, leftUp.y + artPosition.y,
               artPosition.w, artPosition.h};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
  }
}

static void drawButton() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == CorpseSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

bool CorpseSys::run() {
  drawBackGround();
  draw();
  drawButton();
  return true;
}

static bool clickArt(bool leftClick) {
  if (!visited()) {
    SDL_FRect posRect;
    SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                      Global::viewPort.h / 2 - bakH / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    posRect = {leftUp.x + artPosition.x, leftUp.y + artPosition.y,
               artPosition.w, artPosition.h};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      auto &cpComp =
          World::registrys[World::level].get<CorpseComp>(Global::goalEnt);
      HeroScrSys::showArtifactComfirm(cpComp.artifacts.value());
      return true;
    }
  }
  return false;
}

bool CorpseSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{Global::viewPort.w / 2 - bakW / 2,
                    Global::viewPort.h / 2 - bakH / 2};
  auto v = buttonInfo();
  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, true)) {
    return false;
  }
  return true;
}

bool CorpseSys::rightMouseDown(float x, float y) {
  if (clickArt(false)) {
    return false;
  }
  return true;
}

bool CorpseSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    receive();
    break;
  }
  default:
    break;
  }
  return true;
}