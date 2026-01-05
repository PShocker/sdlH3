#pragma once

#include <SDL3/SDL.h>

struct Window {
  static inline SDL_Window *window;
  static inline SDL_Renderer *renderer;

  static inline float mouseX;
  static inline float mouseY;

  static inline SDL_MouseButtonFlags prevMouseState;
  static inline SDL_MouseButtonFlags mouseState;
  static const inline bool *keyboardState = SDL_GetKeyboardState(nullptr);

  static inline const char *windowTitle;

  static inline unsigned int dtNow = 0;
  static inline unsigned int dtLast = 0;
  static inline int deltaTime = 0;
  static inline bool quit;

  static void createWindow(const char *title, unsigned int width,
                           unsigned int height);

  static void tick();

  static void clear();
  static void update();
};
