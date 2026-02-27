#pragma once
#include "Enum/Enum.h"
#include "H3mLoader/H3mObject.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct GenericSet {
  const static inline std::vector<ObjectSetI> generics = {
      {
          .index = ObjectType::PRISON,
          .sound =
              {
                  .ambient = "",
                  .visit = "ROGUE.wav",
                  .removal = {},
              },
      },
      {
          .index = ObjectType::PANDORAS_BOX,
          .sound =
              {
                  .ambient = "",
                  .visit = "ROGUE.wav",
                  .removal = {},
              },
      },
  };
};