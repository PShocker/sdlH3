#include "ArtifactPanelSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Sys/FreeTypeSys.h"
#include "Window/Window.h"
#include <cstdint>
#include <vector>

const std::vector<SDL_Point> slotsPos = {
    {0, 0},    {83, 0},  {165, 0},  //
    {0, 79},   {83, 79}, {165, 79}, //
    {83, 158},
};

void ArtifactPanelSys::draw(int32_t x, int32_t y,
                            std::vector<uint16_t> &artifacts, uint8_t index) {
  auto textures = Global::defCache["Artifact.def/0"];
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    if (i >= artifacts.size()) {
      break;
    }
    if (artifacts[i] == 0xff) {
      continue;
    }
    auto texture = textures[artifacts[i]];
    posRect = {static_cast<float>(x + slotsPos[i].x + 13),
               static_cast<float>(y + slotsPos[i].y + 2),
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (index == i) {
      posRect = {static_cast<float>(x + slotsPos[i].x),
                 static_cast<float>(y + slotsPos[i].y), static_cast<float>(69),
                 static_cast<float>(68)};
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
  }
}

void ArtifactPanelSys::drawNum(int32_t x, int32_t y,
                               std::array<std::u16string, 7> &r) {
  FreeTypeSys::setSize(13);
  FreeTypeSys::setColor(255, 255, 255, 255);
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    FreeTypeSys::drawCenter(x + slotsPos[i].x + 35, y + slotsPos[i].y + 48,
                            r[i]);
  }
}

uint8_t ArtifactPanelSys::click(int32_t x, int32_t y) {
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    posRect = {static_cast<float>(x + slotsPos[i].x),
               static_cast<float>(y + slotsPos[i].y), 69, 68};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      return i;
    }
  }
  return 0xff;
}