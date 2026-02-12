#pragma once
#include "Set/StructSet.h"

#include <any>
#include <array>
#include <cstdint>

struct Visions {
  static void func(std::any data);

  const static inline SpellData spell = {
      .school = 0,
      .cost = {1, 1, 1, 1},
      .level = 1,
      .type = 1,
      .func = func,
  };
};