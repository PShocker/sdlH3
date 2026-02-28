#pragma once
#include "Enum/Enum.h"
#include "H3mLoader/H3mObject.h"
#include "Set/StructSet.h"
#include <vector>

struct CreatureBankSet {
  const static inline std::vector<ObjectSetI> creatureBanks = {
      {
          .index = ObjectType::CREATURE_BANK,
          .sound =
              {
                  .ambient = "LOOPCURS.wav",
                  .visit = "GETPROTECTION.wav",
              },
      },
  };
};