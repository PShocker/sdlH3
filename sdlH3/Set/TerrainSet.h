#pragma once

#include "Enum/Enum.h"
#include "SDL3/SDL_pixels.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <string>
#include <vector>

struct TerrainSetI {
  uint8_t index;
  uint32_t moveCost;
  SDL_Color minimapUnblocked;
  SDL_Color minimapBlocked;
  std::string music;
  std::string horseSound;
  std::string horseSoundPenalty;
  std::vector<uint8_t> battleFields;
  TerrainSetSound sound;
  std::vector<uint8_t> benefitFaction;
};

struct TerrainSet {

  const static inline std::vector<TerrainSetI> terrains = {
      // 0: DIRT
      {
          .index = Enum::TERRAIN_DIRT,
          .moveCost = 100,
          .minimapUnblocked = SDL_Color{82, 56, 8, 255},
          .minimapBlocked = SDL_Color{57, 40, 8, 255},
          .music = "Dirt.wav",
          .horseSound = "horse00.wav",
          .horseSoundPenalty = "horse00.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_DIRT_BIRCHES,
                  Enum::BATTLE_FIELD_DIRT_HILLS,
                  Enum::BATTLE_FIELD_DIRT_PINES,
              },
      },
      // 1: SAND
      {
          .index = Enum::TERRAIN_SAND,
          .moveCost = 150,
          .minimapUnblocked = SDL_Color{222, 207, 140, 255},
          .minimapBlocked = SDL_Color{165, 158, 107, 255},
          .music = "Sand.wav",
          .horseSound = "horse_sand.wav",
          .horseSoundPenalty = "horse_sand_penalty.wav",
          .battleFields = {Enum::BATTLE_FIELD_SAND_MESAS},
      },
      // 2: GRASS
      {
          .index = Enum::TERRAIN_GRASS,
          .moveCost = 100,
          .minimapUnblocked = SDL_Color{0, 65, 0, 255},
          .minimapBlocked = SDL_Color{0, 48, 0, 255},
          .music = "Grass.wav",
          .horseSound = "horse_grass.wav",
          .horseSoundPenalty = "horse_grass_penalty.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_GRASS_HILLS,
                  Enum::BATTLE_FIELD_GRASS_PINES,
              },
      },
      // 3: SNOW
      {
          .index = Enum::TERRAIN_SNOW,
          .moveCost = 150,
          .minimapUnblocked = SDL_Color{181, 199, 198, 255},
          .minimapBlocked = SDL_Color{140, 158, 156, 255},
          .music = "Snow.wav",
          .horseSound = "horse_snow.wav",
          .horseSoundPenalty = "horse_snow_penalty.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_SNOW_MOUNTAINS,
                  Enum::BATTLE_FIELD_SNOW_TREES,
              },
      },
      // 4: SWAMP
      {
          .index = Enum::TERRAIN_SWAMP,
          .moveCost = 175,
          .minimapUnblocked = SDL_Color{74, 134, 107, 255},
          .minimapBlocked = SDL_Color{33, 89, 66, 255},
          .music = "Swamp.wav",
          .horseSound = "horse_swamp.wav",
          .horseSoundPenalty = "horse_swamp_penalty.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_SWAMP_TREES,
              },
      },
      // 5: ROUGH
      {
          .index = Enum::TERRAIN_ROUGH,
          .moveCost = 125,
          .minimapUnblocked = SDL_Color{132, 113, 49, 255},
          .minimapBlocked = SDL_Color{99, 81, 33, 255},
          .music = "Rough.wav",
          .horseSound = "horse_rough.wav",
          .horseSoundPenalty = "horse_rough_penalty.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_ROUGH,
              },
      },
      // 6: SUBTERRA
      {
          .index = Enum::TERRAIN_SUBTERRA,
          .moveCost = 100,
          .minimapUnblocked = SDL_Color{132, 48, 0, 255},
          .minimapBlocked = SDL_Color{90, 8, 0, 255},
          .music = "Subterra.wav",
          .horseSound = "horse_subterra.wav",
          .horseSoundPenalty = "horse_subterra_penalty.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_SUBTERRANEAN,
              },
      },
      // 7: LAVA
      {
          .index = Enum::TERRAIN_LAVA,
          .moveCost = 100,
          .minimapUnblocked = SDL_Color{74, 73, 74, 255},
          .minimapBlocked = SDL_Color{41, 40, 41, 255},
          .music = "Lava.wav",
          .horseSound = "horse_lava.wav",
          .horseSoundPenalty = "horse_lava_penalty.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_LAVA,
              },
      },
      // 8: WATER
      {.index = Enum::TERRAIN_WATER,
       .moveCost = 100,
       .minimapUnblocked = SDL_Color{8, 81, 148, 255},
       .minimapBlocked = SDL_Color{8, 81, 148, 255},
       .music = "Water.wav",
       .horseSound = "horse_water.wav",
       .horseSoundPenalty = "horse_water_penalty.wav",
       .battleFields =
           {
               Enum::BATTLE_FIELD_SHIP,
           },
       .sound =
           {
               .ambient = "LOOPOCEA.wav",
           }},
      // 9: ROCK
      {
          .index = Enum::TERRAIN_ROCK,
          .moveCost = 255,
          .minimapUnblocked = SDL_Color{0, 0, 0, 255},
          .minimapBlocked = SDL_Color{0, 0, 0, 255},
          .music = "Rock.wav",
          .horseSound = "horse_rock.wav",
          .horseSoundPenalty = "horse_rock_penalty.wav",
          .battleFields =
              {
                  Enum::BATTLE_FIELD_ROCKLANDS,
              },
      },
  };
};