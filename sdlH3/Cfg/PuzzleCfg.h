#pragma once

#include "SDL3/SDL_rect.h"
#include <string>
#include <utility>
#include <vector>
struct PuzzleCfg {
  const static inline std::vector<
      std::vector<std::pair<std::string, SDL_FPoint>>>
      puzzleVec = {
          // 0
          {
              {"PUZCAS00.pcx", {7, 8}},     {"PUZCAS01.pcx", {7, 30}},
              {"PUZCAS02.pcx", {7, 102}},   {"PUZCAS03.pcx", {7, 156}},
              {"PUZCAS04.pcx", {7, 202}},   {"PUZCAS05.pcx", {7, 320}},
              {"PUZCAS06.pcx", {16, 8}},    {"PUZCAS07.pcx", {22, 406}},
              {"PUZCAS08.pcx", {70, 301}},  {"PUZCAS09.pcx", {72, 194}},
              {"PUZCAS10.pcx", {101, 332}}, {"PUZCAS11.pcx", {106, 8}},
              {"PUZCAS12.pcx", {106, 31}},  {"PUZCAS13.pcx", {114, 60}},
              {"PUZCAS14.pcx", {126, 329}}, {"PUZCAS15.pcx", {128, 191}},
              {"PUZCAS16.pcx", {152, 347}}, {"PUZCAS17.pcx", {154, 239}},
              {"PUZCAS18.pcx", {157, 429}}, {"PUZCAS19.pcx", {166, 470}},
              {"PUZCAS20.pcx", {185, 127}}, {"PUZCAS21.pcx", {212, 335}},
              {"PUZCAS22.pcx", {214, 191}}, {"PUZCAS23.pcx", {217, 226}},
              {"PUZCAS24.pcx", {235, 147}}, {"PUZCAS25.pcx", {245, 77}},
              {"PUZCAS26.pcx", {266, 384}}, {"PUZCAS27.pcx", {288, 288}},
              {"PUZCAS28.pcx", {298, 8}},   {"PUZCAS29.pcx", {321, 177}},
              {"PUZCAS30.pcx", {346, 67}},  {"PUZCAS31.pcx", {354, 459}},
              {"PUZCAS32.pcx", {355, 397}}, {"PUZCAS33.pcx", {375, 162}},
              {"PUZCAS34.pcx", {382, 255}}, {"PUZCAS35.pcx", {408, 32}},
              {"PUZCAS36.pcx", {408, 111}}, {"PUZCAS37.pcx", {421, 147}},
              {"PUZCAS38.pcx", {422, 466}}, {"PUZCAS39.pcx", {426, 8}},
              {"PUZCAS40.pcx", {436, 238}}, {"PUZCAS41.pcx", {458, 336}},
              {"PUZCAS42.pcx", {486, 8}},   {"PUZCAS43.pcx", {487, 144}},
              {"PUZCAS44.pcx", {517, 145}}, {"PUZCAS45.pcx", {520, 68}},
              {"PUZCAS46.pcx", {524, 234}}, {"PUZCAS47.pcx", {525, 327}},
          },
  };
};