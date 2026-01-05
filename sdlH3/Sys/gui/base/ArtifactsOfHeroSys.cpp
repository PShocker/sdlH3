#include "ArtifactsOfHeroSys.h"
#include "Cfg/ArtifactCfg.h"
#include "Global/Global.h"

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include <cstdint>
#include <vector>

const std::vector<SDL_Point> slotPos = {
    {509, 30},  {568, 242}, {509, 80},  // 0-2
    {383, 69},  {562, 184}, {509, 131}, // 3-5
    {431, 69},  {610, 184}, {515, 295}, // 6-8
    {383, 143}, {399, 193}, {415, 244}, // 9-11
    {431, 295}, {564, 30},  {610, 30},  // 12-14
    {610, 76},  {610, 122}, {610, 310}, // 15-17
    {381, 295}                          // 18
};

void ArtifactsOfHeroSys::drawEquip(HeroComp *heroComp, int32_t x, int32_t y) {
  SDL_FRect posRect;
  for (uint16_t i = 0; i < heroComp->artifacts.size(); i++) {
    auto artId = heroComp->artifacts[i];
    posRect = {static_cast<float>(x + slotPos[i].x - 66),
               static_cast<float>(y + slotPos[i].y - 9), 44, 44};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    if (artId != 0xffff) {
      SDL_RenderTexture(Window::renderer,
                        Global::defCache["Artifact.def/0"][artId], nullptr,
                        &posRect);
      // SDL_RenderFillRect(Window::renderer, &posRect);
    }
  }
}

void ArtifactsOfHeroSys::drawEquipBorder(int32_t x, int32_t y, uint8_t index) {
  SDL_FRect posRect;
  posRect = {static_cast<float>(x + slotPos[index].x - 66),
             static_cast<float>(y + slotPos[index].y - 9), 44, 44};
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

void ArtifactsOfHeroSys::drawArtSlot(uint8_t artId, int32_t x, int32_t y) {
  auto slots = ArtifactCfg::artSlot.at(artId);
  for (uint8_t i = 0; i < slots.size(); i++) {
    if (slots[i]) {
      SDL_FRect posRect = {static_cast<float>(x + slotPos[i].x - 66),
                           static_cast<float>(y + slotPos[i].y - 9), 44, 44};
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
      SDL_RenderRect(Window::renderer, &posRect);
    }
  }
}

void ArtifactsOfHeroSys::drawBackPack(HeroComp *heroComp, int32_t x, int32_t y,
                                      uint8_t index) {
  SDL_FRect posRect;
  posRect = {static_cast<float>(x + 315), static_cast<float>(y + 357), 22, 46};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  if (index == 0) {

    SDL_RenderTexture(Window::renderer, Global::defCache["hsbtns3.def/0"][2],
                      nullptr, &posRect);
  } else if (SDL_PointInRectFloat(&point, &posRect) &&
             Window::mouseState & SDL_BUTTON_LMASK) {
    SDL_RenderTexture(Window::renderer, Global::defCache["hsbtns3.def/0"][1],
                      nullptr, &posRect);
  } else {
    SDL_RenderTexture(Window::renderer, Global::defCache["hsbtns3.def/0"][0],
                      nullptr, &posRect);
  }

  posRect = {static_cast<float>(x + 568), static_cast<float>(y + 357), 22, 46};
  if (!(index + 5 < heroComp->artifactsInBackpack.size())) {
    SDL_RenderTexture(Window::renderer, Global::defCache["hsbtns5.def/0"][2],
                      nullptr, &posRect);
  } else if (SDL_PointInRectFloat(&point, &posRect) &&
             Window::mouseState & SDL_BUTTON_LMASK) {
    SDL_RenderTexture(Window::renderer, Global::defCache["hsbtns5.def/0"][1],
                      nullptr, &posRect);
  } else {
    SDL_RenderTexture(Window::renderer, Global::defCache["hsbtns5.def/0"][0],
                      nullptr, &posRect);
  }

  for (uint8_t i = index; i < index + 5; i++) {
    posRect = {static_cast<float>(x + 338 + 46 * (i - index)),
               static_cast<float>(y + 356), 44, 44};
    if (i < heroComp->artifactsInBackpack.size()) {
      SDL_RenderTexture(
          Window::renderer,
          Global::defCache["Artifact.def/0"][heroComp->artifactsInBackpack[i]],
          nullptr, &posRect);
    }
    // SDL_RenderFillRect(Window::renderer, &posRect);
  }
}

void ArtifactsOfHeroSys::drawBackPackBorder(int32_t x, int32_t y,
                                            uint8_t index) {
  SDL_FRect posRect;
  posRect = {static_cast<float>(x + 338 + 46 * (index)),
             static_cast<float>(y + 356), 44, 44};
  SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

std::pair<uint8_t, uint16_t>
ArtifactsOfHeroSys::clickEquip(HeroComp *heroComp, int32_t x, int32_t y) {
  std::pair<uint8_t, uint16_t> r = {0xff, 0xffff};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint16_t i = 0; i < heroComp->artifacts.size(); i++) {
    auto artId = heroComp->artifacts[i];
    SDL_FRect posRect = {static_cast<float>(x + slotPos[i].x - 66),
                         static_cast<float>(y + slotPos[i].y - 9), 44, 44};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      r = {
          i,
          heroComp->artifacts[i],
      };
    }
  }
  return r;
}
std::pair<uint8_t, uint16_t>
ArtifactsOfHeroSys::clickBackPack(HeroComp *heroComp, int32_t x, int32_t y,
                                  uint8_t index) {
  std::pair<uint8_t, uint16_t> r = {0xff, 0xffff};
  SDL_FPoint point{(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  for (uint8_t i = 0; i < 5; i++) {
    SDL_FRect posRect = {static_cast<float>(x + 338 + 46 * i),
                         static_cast<float>(y + 356), 44, 44};
    if (SDL_PointInRectFloat(&point, &posRect)) {
      r.first = i + index;
      if (r.first >= heroComp->artifactsInBackpack.size()) {
        r.second = 0xffff;
      } else {
        r.second = heroComp->artifactsInBackpack[r.first];
      }
    }
  }
  return r;
}

int8_t ArtifactsOfHeroSys::clickPage(HeroComp *heroComp, int32_t x, int32_t y,
                                     uint8_t index) {
  SDL_FRect posRect;
  posRect = {static_cast<float>(x + 315), static_cast<float>(y + 357), 22, 46};
  SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (index > 0) {
      return -1;
    }
  }
  posRect = {static_cast<float>(x + 568), static_cast<float>(y + 357), 22, 46};
  if (SDL_PointInRectFloat(&point, &posRect)) {
    if (index + 5 < heroComp->artifactsInBackpack.size()) {
      return 1;
    }
  }
  return 0;
}