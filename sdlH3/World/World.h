#pragma once

#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include <array>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <vector>

struct World {
  static inline bool needSort;
  static inline uint8_t level = 0;

  static inline std::array<entt::registry, 2> registrys;
  static inline std::vector<std::function<bool()>> iterateSystems;
  static inline std::vector<std::function<bool(float, float)>> LMouseDownSys;
  static inline std::vector<std::function<bool(float, float)>> LMouseUpSys;
  static inline std::vector<std::function<bool(float, float)>> RMouseDownSys;
  static inline std::vector<std::function<bool(float, float)>> RMouseUpSys;

  static inline std::vector<std::vector<std::function<bool()>>>
      iterateSystemsBak;
  static inline std::vector<std::vector<std::function<bool(float, float)>>>
      LMouseDownSysBak;
  static inline std::vector<std::vector<std::function<bool(float, float)>>>
      LMouseUpSysBak;
  static inline std::vector<std::vector<std::function<bool(float, float)>>>
      RMouseDownSysBak;
  static inline std::vector<std::vector<std::function<bool(float, float)>>>
      RMouseUpSysBak;

  static inline std::vector<std::function<bool(uint16_t)>> keyUpSys;
  static inline std::vector<std::vector<std::function<bool(uint16_t)>>>
      keyUpSysBak;

  static inline std::vector<std::function<bool(uint16_t)>> keyDownSys;
  static inline std::vector<std::vector<std::function<bool(uint16_t)>>>
      keyDownSysBak;

  static inline std::optional<std::function<void(const char *)>> textEditSys;
  static inline std::optional<std::function<void(const char *)>> textInputSys;

  static void enterAdvScrn();
  static void enterTownScrn(uint8_t level, entt::entity ent, uint8_t type);
  static bool enterFadeScrn();
  static bool enterAdvPop();
  static bool enterHeroScrn(uint8_t level, entt::entity ent, uint8_t type);
  static void enterTownHall();
  static void enterTownFort();
  static void enterHeroTrade(entt::entity heroEnt, entt::entity goalEnt,
                             uint8_t goalLevel);
  static void enterKingdom();
  static void enterSpell(entt::entity heroEnt);
  static void enterAdvOpt();
  static void enterAdvSet();
  static void enterTownPortal();
  static void enterConfirm(float bakW, float bakH, uint8_t confirmType);
  static void enterPuzzle(entt::entity goalEnt);
  static void enterSplitCre();
  static void enterViewWorld();
  static void enterSpec10Build(uint8_t townId, entt::entity bEnt);
  static void enterSpec18Build(uint8_t townId, entt::entity bEnt);
  static void enterSpec19Build(uint8_t townId, entt::entity bEnt);
  static void enterSpec20Build(uint8_t townId, entt::entity bEnt);
  static void enterSpec21Build(uint8_t townId, entt::entity bEnt);
  static void enterMageGuild(uint8_t level, entt::entity ent);
  static void enterTownBuild(uint8_t bId);
  static void enterVideo(const std::string &path, float x, float y);

  static void enterTreasure(entt::entity heroEnt, entt::entity goalEnt);
  static void enterWindMill(entt::entity goalEnt);
  static void enterWaterWheel(entt::entity goalEnt);
  static void enterMine(entt::entity goalEnt);
  static void enterUnivers(entt::entity heroEnt, entt::entity goalEnt);
  static void enterShipyard(entt::entity heroEnt, entt::entity goalEnt);
  static void enterLvlup(entt::entity heroEnt);
  static void enterTavern(entt::entity heroEnt, entt::entity goalEnt);
  static void enterGarrison(entt::entity heroEnt, entt::entity goalEnt);
  static void enterDwe(entt::entity heroEnt, entt::entity goalEnt);
  static void enterWarTomb(entt::entity heroEnt, entt::entity goalEnt);
  static void enterMarket(entt::entity heroEnt, entt::entity goalEnt);
  static void enterLearnStone(entt::entity heroEnt, entt::entity goalEnt);
  static void enterShrMag(entt::entity heroEnt, entt::entity goalEnt);
  static void enterMagWell(entt::entity heroEnt, entt::entity goalEnt);
  static void enterMagSpring(entt::entity heroEnt, entt::entity goalEnt);
  static void enterKnoTree(entt::entity heroEnt, entt::entity goalEnt);
  static void enterSchoolWar(entt::entity heroEnt, entt::entity goalEnt);
  static void enterTemple(entt::entity heroEnt, entt::entity goalEnt);
  static void enterRalFlag(entt::entity heroEnt, entt::entity goalEnt);
  static void enterSchoolMag(entt::entity heroEnt, entt::entity goalEnt);
  static void enterPrison(entt::entity heroEnt, entt::entity goalEnt);
  static void enterWitchHut(entt::entity heroEnt, entt::entity goalEnt);
  static void enterScholar(entt::entity heroEnt, entt::entity goalEnt);
  static void enterPandora(entt::entity heroEnt, entt::entity goalEnt);
  static void enterIFortune(entt::entity heroEnt, entt::entity goalEnt);
  static void enterFFortune(entt::entity heroEnt, entt::entity goalEnt);
  static void enterCorpse(entt::entity heroEnt, entt::entity goalEnt);
  static void enterArtifact(entt::entity heroEnt, entt::entity goalEnt);
  static void enterMarletto(entt::entity heroEnt, entt::entity goalEnt);
  static void enterArena(entt::entity heroEnt, entt::entity goalEnt);
  static void enterCartographer(entt::entity heroEnt, entt::entity goalEnt);
  static void enterMermaid(entt::entity heroEnt, entt::entity goalEnt);
  static void enterBuoy(entt::entity heroEnt, entt::entity goalEnt);
  static void enterSeaChest(entt::entity heroEnt, entt::entity goalEnt);
  static void enterMerCamp(entt::entity heroEnt, entt::entity goalEnt);
  static void enterLibrary(entt::entity heroEnt, entt::entity goalEnt);
  static void enterHutMag(entt::entity heroEnt, entt::entity goalEnt);
  static void enterWhirlPool(entt::entity heroEnt, entt::entity goalEnt);
  static void enterSirens(entt::entity heroEnt, entt::entity goalEnt);
  static void enterHillFt(entt::entity heroEnt, entt::entity goalEnt);
  static void enterFouYouth(entt::entity heroEnt, entt::entity goalEnt);
  static void enterWaterHole(entt::entity heroEnt, entt::entity goalEnt);
  static void enterGarRev(entt::entity heroEnt, entt::entity goalEnt);
  static void enterFreeGuild(entt::entity heroEnt, entt::entity goalEnt);
  static void enterFaerieRing(entt::entity heroEnt, entt::entity goalEnt);
  static void enterAltarSac(entt::entity heroEnt, entt::entity goalEnt);
  static void enterWarMachineFac(entt::entity heroEnt, entt::entity goalEnt);
  static void enterStarAxis(entt::entity heroEnt, entt::entity goalEnt);
  static void enterLearn(entt::entity heroEnt, entt::entity goalEnt,
                         uint8_t goalLevel);
  static void enterCreature(std::pair<uint8_t, uint16_t> crePair,
                            uint8_t creType);
  static void enterCreature(std::pair<uint8_t, entt::entity> creHeroPair,
                            std::pair<uint8_t, uint16_t> crePair,
                            uint8_t creType);
  static void enterWarMachine(std::pair<uint8_t, uint16_t> crePair,
                              uint8_t creType);
  static void enterScrn();

  static void exitScrn();

  static bool run();
};
