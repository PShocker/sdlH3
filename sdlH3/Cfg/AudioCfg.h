#pragma once

#include "H3mLoader/H3mObject.h"
#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
struct AudioCfg {
  const static inline std::vector<std::string> townAudio = {
      "CstleTown", "Rampart", "TowerTown",  "InfernoTown",
      "NecroTown", "Dungeon", "Stronghold", "FortressTown"};

  const static inline std::vector<std::string> terrainHorseAudio = {
      "CstleTown", "Rampart", "TowerTown",  "InfernoTown",
      "NecroTown", "Dungeon", "Stronghold", "FortressTown"};

  const static inline std::vector<std::string> terrainAudio = {
      "CstleTown", "Rampart", "TowerTown",  "InfernoTown",
      "NecroTown", "Dungeon", "Stronghold", "FortressTown"};

  enum AudioType : uint8_t {
    AMBIENT,
    VISIT,
    REMOVAL,
  };

  // 使用 std::array 存储三类音频
  const static inline std::unordered_map<
      uint8_t, std::array<std::vector<std::string>, 3>>
      objectAudio = {
          // land
          {0,
           {
               std::vector<std::string>{},              // ambient
               std::vector<std::string>{},              // visit
               std::vector<std::string>{"killfade.wav"} // removal
           }},
          // prison
          {62,
           {
               std::vector<std::string>{},            // ambient
               std::vector<std::string>{"ROGUE.wav"}, // visit
               std::vector<std::string>{}             // removal
           }},

          // pandoraBox - 有多个移除音效
          {6,
           {
               std::vector<std::string>{},              // ambient
               std::vector<std::string>{"MYSTERY.wav"}, // visit
               std::vector<std::string>{"PICKUP01.wav", "PICKUP02.wav",
                                        "PICKUP03.wav", "PICKUP04.wav",
                                        "PICKUP05.wav", "PICKUP06.wav",
                                        "PICKUP07.wav"} // removal
           }},

          // event - 无音频
          {26,
           {std::vector<std::string>{}, std::vector<std::string>{},
            std::vector<std::string>{}}},

          // whirlpool
          {111,
           {
               std::vector<std::string>{"LOOPWHIR.wav"}, // ambient
               std::vector<std::string>{"DANGER.wav"},   // visit
               std::vector<std::string>{}                // removal
           }},

          // subterraneanGate
          {103,
           {
               std::vector<std::string>{"LOOPGATE.wav"}, // ambient
               std::vector<std::string>{"CAVEHEAD.wav"}, // visit
               std::vector<std::string>{}                // removal
           }},

          // refugeeCamp
          {78,
           {
               std::vector<std::string>{"LOOPMERC.wav"}, // ambient
               std::vector<std::string>{"MILITARY.wav"}, // visit
               std::vector<std::string>{}                // removal
           }},
          // resource
          {79,
           {
               std::vector<std::string>{}, // ambient
               std::vector<std::string>{}, // visit
               std::vector<std::string>{"PICKUP01.wav", "PICKUP02.wav",
                                        "PICKUP03.wav", "PICKUP04.wav",
                                        "PICKUP05.wav", "PICKUP06.wav",
                                        "PICKUP07.wav"} // removal
           }},
          // warMachineFactory
          {106,
           {
               std::vector<std::string>{"LOOPFACT.wav"}, // ambient
               std::vector<std::string>{"MILITARY.wav"}, // visit
               std::vector<std::string>{}                // removal
           }},

          // eyeOfTheMagi
          {27,
           {
               std::vector<std::string>{},                 // ambient
               std::vector<std::string>{"LIGHTHOUSE.wav"}, // visit
               std::vector<std::string>{}                  // removal
           }},

          // hutOfTheMagi
          {37,
           {
               std::vector<std::string>{},                 // ambient
               std::vector<std::string>{"LIGHTHOUSE.wav"}, // visit
               std::vector<std::string>{}                  // removal
           }},

          // obelisk
          {57,
           {
               std::vector<std::string>{},              // ambient
               std::vector<std::string>{"MYSTERY.wav"}, // visit
               std::vector<std::string>{}               // removal
           }},

          // oceanBottle
          {59,
           {
               std::vector<std::string>{},            // ambient
               std::vector<std::string>{"STORE.wav"}, // visit
               std::vector<std::string>{}             // removal
           }},

          // shipyard
          {87,
           {
               std::vector<std::string>{"LOOPLUMB.wav"}, // ambient
               std::vector<std::string>{"STORE.wav"},    // visit
               std::vector<std::string>{}                // removal
           }},

          // sign
          {91,
           {
               std::vector<std::string>{},            // ambient
               std::vector<std::string>{"STORE.wav"}, // visit
               std::vector<std::string>{}             // removal
           }},

          // sirens
          {92,
           {
               std::vector<std::string>{"LOOPSIRE.wav"}, // ambient
               std::vector<std::string>{"DANGER.wav"},   // visit
               std::vector<std::string>{}                // removal
           }},

          // denOfThieves
          {97,
           {
               std::vector<std::string>{"LOOPDEN.wav"}, // ambient
               std::vector<std::string>{"MYSTERY.wav"}, // visit
               std::vector<std::string>{}               // removal
           }},

          // questGuard - 有多个移除音效
          {215,
           {
               std::vector<std::string>{},               // ambient
               std::vector<std::string>{"CAVEHEAD.wav"}, // visit
               std::vector<std::string>{"PICKUP01.wav", "PICKUP02.wav",
                                        "PICKUP03.wav", "PICKUP04.wav",
                                        "PICKUP05.wav", "PICKUP06.wav",
                                        "PICKUP07.wav"} // removal
           }},

          // hillFort
          {35,
           {
               std::vector<std::string>{"LOOPSWAR.wav"}, // ambient
               std::vector<std::string>{"MILITARY.wav"}, // visit
               std::vector<std::string>{}                // removal
           }},

          // tavern
          {95,
           {
               std::vector<std::string>{"LOOPTAV.wav"}, // ambient
               std::vector<std::string>{"STORE.wav"},   // visit
               std::vector<std::string>{}               // removal
           }},

          // sanctuary
          {80,
           {
               std::vector<std::string>{"LOOPSANC.wav"},      // ambient
               std::vector<std::string>{"GETPROTECTION.wav"}, // visit
               std::vector<std::string>{}                     // removal
           }},

          // cursedGround
          {21,
           {
               std::vector<std::string>{"LOOPCURS.wav"}, // ambient
               std::vector<std::string>{},               // visit
               std::vector<std::string>{}                // removal
           }},

          // magicPlains
          {46,
           {
               std::vector<std::string>{"LOOPMAGI.wav"}, // ambient
               std::vector<std::string>{},               // visit
               std::vector<std::string>{}                // removal
           }},

          // volcano
          {158,
           {
               std::vector<std::string>{"LOOPVOLC.wav"}, // ambient
               std::vector<std::string>{},               // visit
               std::vector<std::string>{}                // removal
           }},

          // cursedGroundDUPLICATE
          {223,
           {
               std::vector<std::string>{"LOOPCURS.wav"}, // ambient
               std::vector<std::string>{},               // visit
               std::vector<std::string>{}                // removal
           }},

          // magicPlainsDUPLICATE
          {230,
           {
               std::vector<std::string>{"LOOPMAGI.wav"}, // ambient
               std::vector<std::string>{},               // visit
               std::vector<std::string>{}                // removal
           }},
  };
};