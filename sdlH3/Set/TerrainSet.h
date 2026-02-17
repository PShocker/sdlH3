#pragma once

#include "Enum/Enum.h"
#include "SDL3/SDL_pixels.h"
#include <array>
#include <cstdint>
#include <flat_set>
#include <string>

struct TerrainSetI {
  uint8_t index;
  uint32_t moveCost;
  SDL_Color minimapUnblocked;
  SDL_Color minimapBlocked;
  std::string music;
  std::string horseSound;
  std::string horseSoundPenalty;
  std::flat_set<uint8_t> battleFields;
};

struct TerrainSet {

  const static inline std::vector<TerrainSetI> terrains = {
      {
          .index = Enum::TERRAIN_DIRT,
          .moveCost = 100,
          .minimapUnblocked = SDL_Color{82, 56, 8, 255},
          .minimapBlocked = SDL_Color{57, 40, 8, 255},
          .music = "Dirt.wav",
          .horseSound = "horse00.wav",
          .horseSoundPenalty = "horse00.wav",
      },
  };

  const static inline std::array moveCost = {
      100, // 0: dirt
      150, // 1: sand
      100, // 2: grass
      150, // 3: snow
      175, // 4: swamp
      125, // 5: rough
      100, // 6: subterra
      100, // 7: lava
      100, // 8: water
      255, // 9: rock (原值为-1，用255表示不可通行)
      75,  // 10: dirtRoad
      65,  // 11: gravelRoad
      50   // 12: cobblestoneRoad
  };

  const static inline std::array<SDL_Color, 16> minimapUnblocked = {
      SDL_Color{82, 56, 8, 255},     // 0: dirt
      SDL_Color{222, 207, 140, 255}, // 1: sand
      SDL_Color{0, 65, 0, 255},      // 2: grass
      SDL_Color{181, 199, 198, 255}, // 3: snow
      SDL_Color{74, 134, 107, 255},  // 4: swamp
      SDL_Color{132, 113, 49, 255},  // 5: rough
      SDL_Color{132, 48, 0, 255},    // 6: subterra
      SDL_Color{74, 73, 74, 255},    // 7: lava
      SDL_Color{8, 81, 148, 255},    // 8: water
      SDL_Color{0, 0, 0, 255},       // 9: rock
      SDL_Color{0, 0, 0, 0},         // 10:
      SDL_Color{0, 0, 0, 0},         // 11:
      SDL_Color{0, 0, 0, 0},         // 12:
      SDL_Color{0, 0, 0, 0},         // 13:
      SDL_Color{0, 0, 0, 0},         // 14:
      SDL_Color{0, 0, 0, 0}          // 15:
  };

  const static inline std::array<SDL_Color, 16> minimapBlocked = {
      SDL_Color{57, 40, 8, 255},     // 0: dirt (阻塞状态)
      SDL_Color{165, 158, 107, 255}, // 1: sand (阻塞状态)
      SDL_Color{0, 48, 0, 255},      // 2: grass (阻塞状态)
      SDL_Color{140, 158, 156, 255}, // 3: snow (阻塞状态)
      SDL_Color{33, 89, 66, 255},    // 4: swamp (阻塞状态)
      SDL_Color{99, 81, 33, 255},    // 5: rough (阻塞状态)
      SDL_Color{90, 8, 0, 255},      // 6: subterra (阻塞状态)
      SDL_Color{41, 40, 41, 255},    // 7: lava (阻塞状态)
      SDL_Color{8, 81, 148, 255},    // 8: water (阻塞状态)
      SDL_Color{0, 0, 0, 255},       // 9: rock (阻塞状态)
      SDL_Color{0, 0, 0, 0},         // 10:
      SDL_Color{0, 0, 0, 0},         // 11:
      SDL_Color{0, 0, 0, 0},         // 12:
      SDL_Color{0, 0, 0, 0},         // 13:
      SDL_Color{0, 0, 0, 0},         // 14:
      SDL_Color{0, 0, 0, 0}          // 15:
  };
};