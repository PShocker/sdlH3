#include "SpliteCreSys.h"
#include "AdvMapSys.h"
#include "BMPFont/BMPFont.h"

#include "CreatureSys.h"
#include "DwellingSys.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "Set/CreatureSet.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/base/SliderSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>

static uint32_t creNum() {
  return Global::splitCre[0]->second + Global::splitCre[1]->second;
}

static void close() {
  World::exitScrn();
  for (auto &i : Global::splitCre) {
    i = nullptr;
  }
}

static void ok() {
  auto count = Global::splitSliderNum;
  Global::splitCre[0]->second = creNum() - count;

  Global::splitCre[1]->first = Global::splitCre[0]->first;
  Global::splitCre[1]->second = count;
  close();
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  b.textures = Global::defCache["IOK6432.def/0"];
  b.r = {20, 263, 64, 32};
  b.func = ok;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["ICN6432.def/0"];
  b.r = {214, 263, 64, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  posRect = {leftUp.x, leftUp.y, 298, 337};
  auto texture = Global::pcxCache["GPuCrdiv.pcx"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

  auto strPool = *Lang::strPool[Global::langIndex];
  FreeTypeSys::setSize(14);
  FreeTypeSys::setColor(240, 224, 104, 255);
  FreeTypeSys::drawCenter(Global::viewPort.w / 2, leftUp.y + 20,
                          strPool[926 + (uint8_t)ObjectType::SWAN_POND]);
  return;
}

static void drawCreatures() {
  SDL_FRect posRect;
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  auto id = Global::splitCre[0]->first;
  auto group = Global::splitGroup;
  auto graphic = CreatureSet::fullCreatures[id]->graphics.animation;
  auto textures = Global::defCache[graphic + "/" + std::to_string(group)];
  DwellingSys::drawCreatureBak(leftUp.x + 20, leftUp.y + 54, id, group,
                               Global::splitFrameIndex % textures.size(), 0xff);
  DwellingSys::drawCreatureBak(leftUp.x + 177, leftUp.y + 54, id, group,
                               Global::splitFrameIndex % textures.size(), 0xff);
}

static void drawButton() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == SpliteCreSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawNum() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  auto count = creNum();
  auto leftNum = count - Global::splitSliderNum;
  SDL_FRect posRect;
  posRect.x = leftUp.x + 72;
  posRect.y = leftUp.y + 225;
  auto length = static_cast<int>(log10(leftNum)) + 1;
  posRect.x += length * 8 / 2;
  if (leftNum == 0) {
    auto texture = BMPFont::fontCache["bigfont.fnt"]['0'].texture;
    posRect = {posRect.x - texture->w, posRect.y,
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
  }
  while (leftNum > 0) {
    auto digit = leftNum % 10; // 获取当前最低位
    auto texture = BMPFont::fontCache["bigfont.fnt"]['0' + digit].texture;
    posRect = {posRect.x - texture->w, posRect.y,
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
    leftNum /= 10; // 去掉最低位
  }

  auto rightNum = Global::splitSliderNum;
  posRect.x = leftUp.x + 230;
  posRect.y = leftUp.y + 225;
  length = static_cast<int>(log10(rightNum)) + 1;
  posRect.x += length * 8 / 2;
  if (rightNum == 0) {
    auto texture = BMPFont::fontCache["bigfont.fnt"]['0'].texture;
    posRect = {posRect.x - texture->w, posRect.y,
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
  }
  while (rightNum > 0) {
    auto digit = rightNum % 10; // 获取当前最低位
    auto texture = BMPFont::fontCache["bigfont.fnt"]['0' + digit].texture;
    posRect = {posRect.x - texture->w, posRect.y,
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
    rightNum /= 10; // 去掉最低位
  }
}

static void drawSlider() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  auto count = creNum();
  if (count != 0) {
    SliderSys::drawHor(leftUp.x + 21, leftUp.y + 194, 257,
                       Global::splitSliderNum / (float)count);
  } else {
    SliderSys::drawHor(leftUp.x + 21, leftUp.y + 194, 257, 0);
  }
}

static void splitAnimate() {
  CreatureSys::creAnimate(Global::splitFrameTime, Global::splitFrameIndex,
                          Global::splitGroup, Global::splitCre[0]->first);
}

bool SpliteCreSys::run() {
  splitAnimate();
  drawBackGround();
  drawCreatures();
  drawButton();
  drawNum();
  drawSlider();
  return true;
}

static bool clickSlider() {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  // click slider
  auto count = creNum();
  if (auto num = SliderSys::clickHor(leftUp.x + 21, leftUp.y + 194, 257,
                                     Global::splitSliderNum, count);
      num != Global::splitSliderNum) {
    Global::splitSliderNum = num;
    return true;
  }
  return false;
}

bool SpliteCreSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickSlider()) {
    return false;
  }
  return true;
}

bool SpliteCreSys::rightMouseDown(float x, float y) {
  SDL_FPoint leftUp{static_cast<float>(((int)Global::viewPort.w - 298) / 2),
                    static_cast<float>(((int)Global::viewPort.h - 337) / 2)};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  return true;
}

bool SpliteCreSys::keyUp(uint16_t key) {
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