#pragma once
#include "H3mLoader/H3mObject.h"
#include "Set/StructSet.h"
#include <any>
#include <array>
#include <cstdint>

struct ScuttleBoat {
  static void func(std::any data);

  const static inline SpellData spell = {
      .index = 1,
      .school = 1,
      .cost = {1, 1, 1, 1},
      .level = 1,
      .type = 1,
      .func = func,
      .extra =
          SpellAdventure{
              .goalType = ObjectType::BOAT,
              .cursor = 1,
              .range = 1,
          },
  };
};