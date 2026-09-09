#include "src/client/systems/systems.h"
#include "window/window.h"
#include <cstdint>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json; // 简写，方便使用

SDL_AppResult SDL_AppIterate(void *appstate) {
  window::tick();
  window::clear();
  for (const auto &fn : systems::logic_systems) {
    if (!fn()) {
      break;
    }
  }

  // shader_game_instance::start(shader_enum::grayscale);
  for (const auto &fn : systems::render_systems) {
    if (!fn()) {
      break;
    }
  }
  json j = {
      {"name", "张三"},
      {"age", 30},
      {"skills", {"C++", "Python", "JSON"}}, // 嵌套数组
      {"address", {{"city", "武汉"}, {"country", "中国"}}},
  };

  window::update();
  return SDL_APP_CONTINUE;
}

// 逻辑分辨率
static int32_t logic_w = 1366;
static int32_t logic_h = 768;

// 窗口分辨率
static int32_t window_w = 1366;
static int32_t window_h = 768;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  auto r = (event->type == SDL_EVENT_QUIT) ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
  for (auto &fn : systems::event_systems) {
    if (fn(event) == false) {
      break;
    }
  }
  return r;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) { SDL_Quit(); }