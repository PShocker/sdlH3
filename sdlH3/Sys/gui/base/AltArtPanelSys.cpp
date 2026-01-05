#include "AltArtPanelSys.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

const std::vector<SDL_Point> slotsPos = {
    {0, 0},     {54, 0},    {108, 0},   {162, 0},  {216, 0},  {0, 70},
    {54, 70},   {108, 70},  {162, 70},  {216, 70}, {0, 140},  {54, 140},
    {108, 140}, {162, 140}, {216, 140}, {0, 210},  {54, 210}, {108, 210},
    {162, 210}, {216, 210}, {81, 280},  {135, 280}};

void AltArtPanelSys::draw(int32_t x, int32_t y) {
  auto textures = Global::defCache["Artifact.def/0"];
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    if (i >= Global::alts.size()) {
      break;
    }
    if (Global::alts[i].first == 0xff) {
      continue;
    }
    auto texture = textures[Global::alts[i].second];
    posRect = {static_cast<float>(x + slotsPos[i].x),
               static_cast<float>(y + slotsPos[i].y),
               static_cast<float>(texture->w), static_cast<float>(texture->h)};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
    SDL_RenderRect(Window::renderer, &posRect);
  }
}

std::pair<uint8_t, uint16_t> AltArtPanelSys::click(int32_t x, int32_t y) {
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  SDL_FRect posRect;
  for (uint8_t i = 0; i < slotsPos.size(); i++) {
    posRect = {static_cast<float>(x + slotsPos[i].x),
               static_cast<float>(y + slotsPos[i].y), 58, 64};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      //   return i;
      return Global::alts[i];
    }
  }
  return {0xff, 1};
}