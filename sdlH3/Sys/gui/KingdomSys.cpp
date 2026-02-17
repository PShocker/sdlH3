#include "KingdomSys.h"
#include "AdvMapSys.h"
#include "Comp/HeroComp.h"
#include "Comp/TownComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Set/HeroSet.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <vector>

static void close() { World::exitScrn(); }

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  auto t = Global::defCache["OVBUTN1.def/0"];

  std::vector<SDL_Texture *> vec = {t[0], t[1], t[2]};
  b.textures = vec;
  b.r = {748, 493, 48, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  vec = {t[3], t[4]};
  b.textures = vec;
  b.r = {748, 565, 48, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  b.textures = Global::defCache["OVBUTN6.def/0"];
  b.r = {748, 529, 48, 32};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  t = Global::defCache["OVBUTN4.def/0"];
  vec = {t[0], t[1]};
  b.textures = vec;
  b.r = {733, 4, 61, 18};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  t = Global::defCache["OVBUTN4.def/0"];
  vec = {t[4], t[5]};
  b.textures = vec;
  b.r = {733, 24, 61, 18};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  t = Global::defCache["OVBUTN4.def/0"];
  vec = {t[6], t[7]};

  b.textures = vec;
  b.r = {733, 446, 61, 18};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  t = Global::defCache["OVBUTN4.def/0"];
  vec = {t[2], t[3]};
  b.textures = vec;
  b.r = {733, 466, 61, 18};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  return v;
}

static void drawBackGround() {
  SDL_FRect posRect;
  auto playerId = Global::playerId;
  auto texture = Global::pcxCache["OvCast.pcx"][playerId];
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  posRect = {leftUp.x, leftUp.y, 800, 600};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawButton() {
  const SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                          (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto top = (*topFunc.target<bool (*)()>() == KingdomSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

static void drawMines() {
  const SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                          (Global::viewPort.h - 600) / 2};
  auto texture = Global::defCache["OVMINES.def/0"];
  for (int i = 0; i < 7; i++) {
    SDL_FRect posRect = {leftUp.x + 20 + i * 80, leftUp.y + 495, 68, 54};
    SDL_RenderTexture(Window::renderer, texture[i], nullptr, &posRect);
  }
}

static void drawTown() {
  if (!Global::kdmTown) {
    return;
  }
  const SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                          (Global::viewPort.h - 600) / 2};
  auto index = Global::kdmPage;
  SDL_Texture *texture;
  for (uint8_t i = index;
       i < index + 4 && i < Global::towns[Global::playerId].size() + index;
       i++) {
    const auto x = leftUp.x + 21;
    const auto y = leftUp.y + static_cast<float>(21 + (i - index) * 117);
    SDL_FRect posRect = {x, y, 701, 114};
    texture = Global::defCache["OVSLOT.def/0"][6];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    auto [level, townEnt] = Global::towns[Global::playerId][i];
    auto townComp = &World::registrys[level].get<TownComp>(townEnt);
    if (townComp->hasBuild) {
      texture = Global::defCache["itpt.def/0"][townComp->id * 2 + 1];
    } else {
      texture = Global::defCache["itpt.def/0"][townComp->id * 2];
    }
    posRect = {x + 5, y + 6, 58, 64};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    for (auto m = 0; m <= 1; m++) {
      posRect = {x + 243 + m * 232, y + 6, 58, 64};
      SDL_RenderFillRect(Window::renderer, &posRect);
      for (auto n = 0; n < 7; n++) {
        int col;
        if (n > 3) {
          col = n - 3;
          posRect = {x + 295 + m * 232 + col * 36, y + 40, 32, 32};
        } else {
          col = n;
          posRect = {x + 314 + m * 232 + col * 36, y + 3, 32, 32};
        }
        SDL_RenderFillRect(Window::renderer, &posRect);
      }
    }

    if (townComp->buildings.contains(Enum::BUILD_FORT)) {
      texture = Global::defCache["ITMCLS.def/0"][0];
    } else if (townComp->buildings.contains(
                   Enum::BUILD_CITADEL)) {
      texture = Global::defCache["ITMCLS.def/0"][1];
    } else if (townComp->buildings.contains(Enum::BUILD_CASTLE)) {
      texture = Global::defCache["ITMCLS.def/0"][2];
    } else {
      texture = Global::defCache["ITMCLS.def/0"][3];
    }
    posRect = {x + 113, y + 33, 34, 34};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    if (townComp->buildings.contains(Enum::BUILD_TOWN_HALL)) {
      texture = Global::defCache["ITMTLS.def/0"][1];
    } else if (townComp->buildings.contains(Enum::BUILD_CITY_HALL)) {
      texture = Global::defCache["ITMTLS.def/0"][2];
    } else if (townComp->buildings.contains(Enum::BUILD_CAPITOL)) {
      texture = Global::defCache["ITMTLS.def/0"][3];
    } else {
      texture = Global::defCache["ITMTLS.def/0"][0];
    }
    // posRect = {Global::viewPort.w - 120, Global::viewPort.h - 168, 34,
    //              34};
    posRect = {x + 71, y + 33, 34, 34};
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_RenderFillRect(Window::renderer, &posRect);

    for (auto m = 0; m <= 1; m++) {
      for (auto n = 0; n < 8; n++) {
        posRect = {x + 56 + m * 353 + n * 37, y + 78, 32, 32};
        SDL_RenderFillRect(Window::renderer, &posRect);
      }
    }
  }
}

static void drawHero() {
  if (Global::kdmTown) {
    return;
  }

  const SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                          (Global::viewPort.h - 600) / 2};
  auto index = Global::kdmPage;
  SDL_Texture *texture;
  for (uint8_t i = index; i < Global::heros[Global::playerId].size(); i++) {
    auto x = leftUp.x + 21;
    auto y = leftUp.y + static_cast<float>(21 + (i - index) * 117);
    SDL_FRect posRect = {x, y, 701, 114};
    if (Global::kdmArtIndex[i] >= 2) {
      texture = Global::defCache["OVSLOT.def/0"][5];
    } else {
      texture = Global::defCache["OVSLOT.def/0"][4];
    }
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_RenderFillRect(Window::renderer, &posRect);
    auto [level, heroEnt] = Global::heros[Global::playerId][i];
    auto &heroComp = World::registrys[level].get<HeroComp>(heroEnt);
    posRect = {x + 5, y + 6, 58, 64};
    auto largePor=HeroSet::fullHeros[heroComp.portrait]->largePor;
    texture = Global::pcxCache[largePor][0];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    for (auto m = 0; m < 4; m++) {
      posRect = {x + static_cast<float>(78 + (int)m * 36), y + 26, 32, 32};
      texture = Global::defCache["PSKIL32.def/0"][m];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
    for (auto m = 0; m < heroComp.secSkills.size() && m < 8; m++) {
      posRect = {x + static_cast<float>(410 + (int)m * 36), y + 5, 32, 32};
      auto [index, level] = heroComp.secSkills.at(m);
      texture = Global::defCache["SECSK32.def/0"][(index + 1) * 3 + level];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
    posRect = {x + 375, y + 5, 32, 32};
    texture = Global::defCache["UN32.def/0"][heroComp.portrait];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    posRect = {x + 330, y + 5, 32, 32};
    texture = Global::defCache["PSKIL32.def/0"][4];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    posRect = {x + 280, y + 5, 32, 32};
    texture = Global::defCache["PSKIL32.def/0"][5];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);

    posRect = {x + 223, y + 55, 30, 20};
    texture = Global::defCache["IMRL30.def/0"][5];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_RenderRect(Window::renderer, &posRect);

    posRect = {x + 223, y + 30, 30, 20};
    texture = Global::defCache["ILCK30.def/0"][5];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    // SDL_RenderRect(Window::renderer, &posRect);

    for (uint8_t m = 0; m < heroComp.creatures.size(); m++) {
      auto [id, count] = heroComp.creatures[m];
      if (count == 0) {
        continue;
      }
      texture = Global::defCache["CPRSMALL.def/0"][id + 2];
      posRect = {x + 6 + m * 36, y + 78, 32, 32};
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }

    for (auto m = 0; m < 3; m++) {
      posRect = {x + 364 + (int)m * 112, y + 46, 108, 16};
      SDL_FPoint point = {(float)(int)Window::mouseX,
                          (float)(int)Window::mouseY};
      if (SDL_PointInRectFloat(&point, &posRect) &&
          Window::mouseState & SDL_BUTTON_LMASK) {
        texture = Global::defCache["OVBUTN3.def/0"][1];
      } else {
        texture = Global::defCache["OVBUTN3.def/0"][0];
      }
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }

    switch (Global::kdmArtIndex[i]) {
    case 0: {
      for (auto m = 0; m < 9; m++) {
        auto artId = heroComp.artifacts[m];
        if (artId != 0xffff) {
          posRect = {static_cast<float>(x + 269 + m * 48),
                     static_cast<float>(y + 66), 44, 44};
          SDL_RenderTexture(Window::renderer,
                            Global::defCache["Artifact.def/0"][artId], nullptr,
                            &posRect);
        }
      }
      break;
    }
    case 1: {
      for (auto m = 0; m < 9; m++) {
        auto artId = heroComp.artifacts[m + 9];
        if (artId != 0xffff) {
          posRect = {static_cast<float>(x + 269 + m * 48),
                     static_cast<float>(y + 66), 44, 44};
          SDL_RenderTexture(Window::renderer,
                            Global::defCache["Artifact.def/0"][artId], nullptr,
                            &posRect);
        }
      }
      break;
    }
    default: {
      auto artIndex = Global::kdmArtIndex[i] - 2;
      SDL_FPoint point = {(float)(int)Window::mouseX,
                          (float)(int)Window::mouseY};
      posRect = {static_cast<float>(x + 269), static_cast<float>(y + 66), 22,
                 46};
      if (artIndex == 0) {
        SDL_RenderTexture(Window::renderer,
                          Global::defCache["hsbtns3.def/0"][2], nullptr,
                          &posRect);
      } else if (SDL_PointInRectFloat(&point, &posRect) &&
                 Window::mouseState & SDL_BUTTON_LMASK) {
        SDL_RenderTexture(Window::renderer,
                          Global::defCache["hsbtns3.def/0"][1], nullptr,
                          &posRect);
      } else {
        SDL_RenderTexture(Window::renderer,
                          Global::defCache["hsbtns3.def/0"][0], nullptr,
                          &posRect);
      }
      posRect = {static_cast<float>(x + 675), static_cast<float>(y + 66), 22,
                 46};
      if (!(artIndex + 8 < heroComp.artifactsInBackpack.size())) {
        SDL_RenderTexture(Window::renderer,
                          Global::defCache["hsbtns5.def/0"][2], nullptr,
                          &posRect);
      } else if (SDL_PointInRectFloat(&point, &posRect) &&
                 Window::mouseState & SDL_BUTTON_LMASK) {
        SDL_RenderTexture(Window::renderer,
                          Global::defCache["hsbtns5.def/0"][1], nullptr,
                          &posRect);
      } else {
        SDL_RenderTexture(Window::renderer,
                          Global::defCache["hsbtns5.def/0"][0], nullptr,
                          &posRect);
      }

      for (uint8_t m = index; m < index + 8; m++) {
        posRect = {static_cast<float>(x + 294 + 48 * (m - index)),
                   static_cast<float>(y + 66), 44, 44};
        if (i < heroComp.artifactsInBackpack.size()) {
          SDL_RenderTexture(Window::renderer,
                            Global::defCache["Artifact.def/0"]
                                            [heroComp.artifactsInBackpack[m]],
                            nullptr, &posRect);
        }
        // SDL_RenderFillRect(Window::renderer, &posRect);
      }

      break;
    }
    }
  }
}
bool KingdomSys::run() {
  drawBackGround();
  drawTown();
  drawHero();
  drawMines();
  drawButton();
  return true;
}

// const static std::vector<std::function<void()>> buttonsFunc = {
//     []() {
//       Global::kdmTown = false;
//       Global::kdmPage = 0;
//     },
//     []() {
//       Global::kdmTown = true;
//       Global::kdmPage = 0;
//     },
//     KingdomSys::close,
//     []() { Global::kdmPage = 0; },
//     []() {
//       if (Global::kdmPage >= 1) {
//         Global::kdmPage -= 1;
//       }
//     },
//     []() {
//       if (Global::kdmPage < Global::heros[Global::playerId].size() - 4 &&
//           Global::heros[Global::playerId].size() > 4) {
//         Global::kdmPage += 1;
//       }
//     },
//     []() {
//       if (Global::heros[Global::playerId].size() > 4) {
//         Global::kdmPage = Global::heros[Global::playerId].size() - 4;
//       }
//     }};

static bool clickdmArt() {
  if (!Global::kdmTown) {
    SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                      (Global::viewPort.h - 600) / 2};
    SDL_FPoint point = {(float)(int)Window::mouseX, (float)(int)Window::mouseY};
    auto index = Global::kdmPage;
    for (uint8_t i = index; i < index + 4; i++) {
      auto x = leftUp.x + 21;
      auto y = leftUp.y + static_cast<float>(21 + i * 117);
      for (auto m = 0; m < 3; m++) {
        SDL_FRect posRect = {x + 364 + (int)m * 112, y + 46, 108, 16};
        if (SDL_PointInRectFloat(&point, &posRect)) {
          Global::kdmArtIndex[i] = m;
          return true;
        }
      }
    }
  }
  return false;
}

bool KingdomSys::leftMouseUp(float x, float y) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickdmArt()) {
    return false;
  }
  return true;
}

bool KingdomSys::keyUp(uint16_t key) {
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