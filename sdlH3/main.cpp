#include "BMPFont/BMPFont.h"
#include "Ent/Ent.h"
#include "Global/Global.h"
#include "H3mLoader/H3mData.h"
#include "Pal/PlayerPal.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_mouse.h"
#include "Sys/AudioSys.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/VideoSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <zlib.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppIterate(void *appstate) {
  Window::tick();
  Window::clear();
  for (auto sys : World::iterateSystems) {
    if (!sys()) {
      break;
    };
  }
  Window::update();
  return SDL_APP_CONTINUE;
}

int32_t width = 800;
int32_t height = 600;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  if (argc == 3) {
    width = SDL_atoi(argv[1]);
    height = SDL_atoi(argv[2]);
  }
  std::srand(std::time(0));

  H3mData data("./Maps/Good to Go.h3m");
  data.init();
  Global::mapW = data.header.width * 32;
  Global::mapH = data.header.height * 32;
  Global::viewPort = {0, 0, (float)width, (float)height};

  Global::mapSize = data.header.width;

  Window::createWindow("H3Test", width, height);
  PlayerPal::init();
  Global::init();
  BMPFont::init();
  Ent::load(data);
  Global::startGame();
  FreeTypeSys::init(1);
  VideoSys::init("./Video/TAVERN.BIK");

  World::enterAdvScrn();

  // AudioSys::init();

  SDL_HideCursor();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  auto r = (event->type == SDL_EVENT_QUIT) ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      for (auto sys : World::LMouseUpSys) {
        if (!sys(event->button.x, event->button.y)) {
          return r;
        }
      }
    } else if (event->button.button == SDL_BUTTON_RIGHT) {
      for (auto sys : World::RMouseUpSys) {
        if (!sys(event->button.x, event->button.y)) {
          return r;
        }
      }
    }
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      for (auto sys : World::LMouseDownSys) {
        if (!sys(event->button.x, event->button.y)) {
          return r;
        }
      }
    } else if (event->button.button == SDL_BUTTON_RIGHT) {
      for (auto sys : World::RMouseDownSys) {
        if (!sys(event->button.x, event->button.y)) {
          return r;
        }
      }
    }
  }
  if (event->type == SDL_EVENT_KEY_UP) {
    for (auto sys : World::keyUpSys) {
      if (!sys(event->key.scancode)) {
        return r;
      }
    }
  }
  if (event->type == SDL_EVENT_KEY_DOWN) {
    for (auto sys : World::keyDownSys) {
      if (!sys(event->key.scancode)) {
        return r;
      }
    }
  }
  if (event->type == SDL_EVENT_TEXT_EDITING) {
    if (World::textEditSys.has_value()) {
      World::textEditSys.value()(event->edit.text);
    }
  }
  if (event->type == SDL_EVENT_TEXT_INPUT) {
    if (World::textInputSys.has_value()) {
      World::textInputSys.value()(event->edit.text);
    }
  }
  return r;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) { SDL_Quit(); }