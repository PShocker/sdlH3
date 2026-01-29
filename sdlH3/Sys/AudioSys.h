#pragma once

#include <cstdint>
#include <string>

struct Audio {
  std::string path;
  uint32_t current;
  float volume;
  float fadeSpeed;
  bool pause;
  bool cycle; // 是否循环，通常为bgm
};

struct AudioSys {
  static void push(std::string path, float volume, float fadeSpeed, bool cycle);
  static void init();
  static bool run();
};