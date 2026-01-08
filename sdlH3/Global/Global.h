#pragma once

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "entt/entity/fwd.hpp"
#include <array>
#include <cstdint>
#include <functional>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

struct Global {
  static inline std::random_device rd = std::random_device();
  static inline std::mt19937 gen = std::mt19937(rd());

  static inline uint8_t langIndex = 1;

  static inline uint8_t playerId = 0;
  static inline std::vector<std::set<uint8_t>> playerAlliance = {{0, 1}};

  static inline std::array<std::array<uint32_t, 7>, 8> resources;

  static inline std::array<std::vector<std::vector<std::vector<entt::entity>>>,
                           2>
      terrains;

  static inline std::array<std::set<int32_t>, 2> landBlock;
  static inline std::array<std::set<int32_t>, 2> waterBlock;
  static inline std::array<std::set<int32_t>, 2> rockBlock;
  static inline std::array<std::set<int32_t>, 2> coastalBlock;

  static inline std::array<SDL_Texture *, 2> miniMaps;
  static inline std::array<SDL_Texture *, 2> puzzleMaps;

  static inline std::array<std::array<std::vector<bool>, 2>, 8> fogs;

  static inline std::array<std::vector<std::pair<uint8_t, entt::entity>>, 8>
      heros;
  static inline std::array<uint8_t, 8> herosIndex;
  static inline std::array<std::vector<std::pair<uint8_t, entt::entity>>, 8>
      towns;
  static inline std::array<uint32_t, 8> townsIndex;
  static inline bool heroMove;

  static inline SDL_FRect viewPort;
  static inline int mapSize;
  static inline int mapH;
  static inline int mapW;

  static inline std::array<std::pair<uint8_t, uint8_t>, 8> advPages;
  static inline uint8_t advCreIndex;
  static inline std::vector<std::pair<SDL_Texture *, std::u16string>> advStats;
  static inline uint64_t advStatTime;
  static inline std::vector<std::tuple<SDL_Point, SDL_Color, std::u16string>>
      advStrs;
  static inline std::array<std::array<std::set<entt::entity>, 2>, 8> advVisted;

  static inline uint8_t cursorType;
  static inline uint8_t cursorIndex;
  static inline SDL_FPoint cursorPoint;
  static inline std::vector<uint8_t> cursorBack;

  static inline SDL_Texture *fadeTexture;
  static inline int32_t fadeAlpha;
  static inline float fadeSpeed;
  static inline SDL_FRect fadeRect;
  static inline std::optional<std::function<bool()>> fadeCallBack;

  static inline entt::entity heroEnt;
  static inline entt::entity goalEnt;

  static inline uint8_t goalIndex;
  static inline uint8_t goalLevel;

  static inline std::pair<uint8_t, uint16_t> artPair;
  static inline int8_t artClick;
  static inline bool artBackClick;
  static inline std::array<uint8_t, 2> artPageIndex;

  static inline uint8_t splSchool;
  static inline bool splBattle;
  static inline uint8_t splPage;

  static inline std::array<uint8_t, 6> gameSets;

  static inline uint64_t bldFrameTime;
  static inline uint64_t bldFrameIndex;

  static inline uint64_t dweFrameTime;
  static inline uint64_t dweFrameIndex;
  static inline uint64_t dweGroup;
  static inline uint8_t dweIndex;
  static inline uint32_t dweSliderNum;

  static inline uint64_t creFrameTime;
  static inline uint64_t creFrameIndex;
  static inline uint64_t creGroup;

  static inline bool kdmTown;
  static inline uint8_t kdmPage;
  static inline std::array<uint8_t, 8> kdmArtIndex;

  static inline uint8_t makType;
  static inline std::array<uint8_t, 2> makIndex;
  static inline uint32_t makSliderNum;

  static inline uint8_t altType;
  static inline std::vector<std::pair<int16_t, uint32_t>> alts;
  static inline uint8_t altIndex;
  static inline uint32_t altSliderNum;

  static inline uint8_t creIndex;
  static inline uint8_t creType;
  static inline std::pair<uint16_t, uint32_t> crePair;
  static inline std::pair<uint8_t, entt::entity> creHeroPair;

  static inline std::optional<std::function<void()>> confirmCallBack;
  static inline bool confirmOnlyOK;
  static inline std::function<void()> confirmdraw;
  static inline uint8_t confirmType;
  static inline float confirmBakW;
  static inline float confirmBakH;

  static inline uint8_t lvlPrimIndex;
  static inline std::pair<uint8_t, uint8_t> lvlSecPair;

  static inline int32_t hutMagIndex;
  static inline uint64_t hutMagTime;

  static inline std::optional<std::pair<uint8_t, SDL_Point>> grailPair;

  static inline std::optional<SDL_Point> puzzleOffset;
  static inline uint64_t puzzleFadeTime;

  static inline std::array<std::set<uint8_t>, 8> puzzle;

  static inline std::pair<uint8_t, entt::entity> heroScnPair;
  static inline uint8_t heroScnType;
  static inline uint8_t heroScnIndex;

  static inline std::pair<uint8_t, entt::entity> townScnPair;
  static inline uint8_t townScnType;
  static inline uint8_t townScnIndex;

  static inline std::array<std::array<entt::entity, 2>, 8> tavernHeros;

  static inline std::optional<std::u16string> IMEText;
  static inline std::optional<std::u16string> IMETextBak;

  static inline uint8_t townPorPage;
  static inline uint8_t townPorIndex;

  static inline bool splitOn;
  static inline std::array<std::pair<uint16_t, uint32_t> *, 2> splitCre;
  static inline uint32_t splitSliderNum;
  static inline uint64_t splitFrameTime;
  static inline uint64_t splitFrameIndex;

  static inline uint8_t viewWorldScale;

  //   static inline std::unordered_map<std::string, std::any> stateCache;
  static inline std::unordered_map<std::string, std::vector<SDL_Texture *>>
      pcxCache;
  static inline std::unordered_map<std::string, std::vector<SDL_Texture *>>
      defCache;
  static inline std::unordered_map<std::string, std::vector<uint8_t>> pcmCache;
  static void init();
  static void startGame();
  static void endGame();
};