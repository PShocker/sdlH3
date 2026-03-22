#include "World.h"

#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TerrainComp.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "Set/TerrainSet.h"
#include "Sys/AnimateSys.h"
#include "Sys/AudioSys.h"
#include "Sys/BorderSys.h"
#include "Sys/FadeSys.h"
#include "Sys/FogSys.h"
#include "Sys/HeroSys.h"
#include "Sys/RenderSys.h"
#include "Sys/VideoSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Sys/gui/AdvOptionSys.h"
#include "Sys/gui/AdvPopSys.h"
#include "Sys/gui/AdvSetSys.h"
#include "Sys/gui/AltarSacSys.h"
#include "Sys/gui/ArenaSys.h"
#include "Sys/gui/ArtifactSys.h"
#include "Sys/gui/BattleSys.h"
#include "Sys/gui/BuoySys.h"
#include "Sys/gui/CameraSys.h"
#include "Sys/gui/CartographerSys.h"
#include "Sys/gui/ConfirmSys.h"
#include "Sys/gui/CorpseSys.h"
#include "Sys/gui/CreatureSys.h"
#include "Sys/gui/CursorSys.h"
#include "Sys/gui/DwellingSys.h"
#include "Sys/gui/FaerieRingSys.h"
#include "Sys/gui/FouFortuneSys.h"
#include "Sys/gui/FouYouthSys.h"
#include "Sys/gui/FreeGuildSys.h"
#include "Sys/gui/GarRevSys.h"
#include "Sys/gui/GarrisonSys.h"
#include "Sys/gui/HeroScrSys.h"
#include "Sys/gui/HeroTradeSys.h"
#include "Sys/gui/HillFtSys.h"
#include "Sys/gui/HutMagSys.h"
#include "Sys/gui/IdolFortuneSys.h"
#include "Sys/gui/KingdomSys.h"
#include "Sys/gui/KnoTreeSys.h"
#include "Sys/gui/LearnStoneSys.h"
#include "Sys/gui/LearnSys.h"
#include "Sys/gui/LevelUpSys.h"
#include "Sys/gui/LibrarySys.h"
#include "Sys/gui/MagSpringSys.h"
#include "Sys/gui/MagWellSys.h"
#include "Sys/gui/MageGuildSys.h"
#include "Sys/gui/MarketSys.h"
#include "Sys/gui/MarlettoSys.h"
#include "Sys/gui/MerCampSys.h"
#include "Sys/gui/MermaidSys.h"
#include "Sys/gui/MineSys.h"
#include "Sys/gui/PandoraSys.h"
#include "Sys/gui/PrisonSys.h"
#include "Sys/gui/PuzzleSys.h"
#include "Sys/gui/RalFlagSys.h"
#include "Sys/gui/ScholarSys.h"
#include "Sys/gui/SchoolMagSys.h"
#include "Sys/gui/SchoolWarSys.h"
#include "Sys/gui/SeaChestSys.h"
#include "Sys/gui/ShipyardSys.h"
#include "Sys/gui/ShrineMagicSys.h"
#include "Sys/gui/SirensSys.h"
#include "Sys/gui/SpellSys.h"
#include "Sys/gui/SpliteCreSys.h"
#include "Sys/gui/StablesSys.h"
#include "Sys/gui/StarAxisSys.h"
#include "Sys/gui/TavernSys.h"
#include "Sys/gui/TempleSys.h"
#include "Sys/gui/TownBuildSys.h"
#include "Sys/gui/TownFortSys.h"
#include "Sys/gui/TownHallSys.h"
#include "Sys/gui/TownPortalSys.h"
#include "Sys/gui/TownSys.h"
#include "Sys/gui/TreasureSys.h"
#include "Sys/gui/UniversitySys.h"
#include "Sys/gui/ViewWorldSys.h"
#include "Sys/gui/WarMachineFacSys.h"
#include "Sys/gui/WarMachineSys.h"
#include "Sys/gui/WarTombSys.h"
#include "Sys/gui/WaterHoleSys.h"
#include "Sys/gui/WaterWheelSys.h"
#include "Sys/gui/WhirlPoolSys.h"
#include "Sys/gui/WindMillSys.h"
#include "Sys/gui/WitchHutSys.h"
#include "Window/Window.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <algorithm>
#include <cstdint>
#include <utility>

static bool savaMask() {
  if (Global::maskTexture) {
    SDL_DestroyTexture(Global::maskTexture);
  }
  SDL_Rect r{static_cast<int>(0), static_cast<int>(0),
             static_cast<int>(Global::viewPort.w),
             static_cast<int>(Global::viewPort.h)};
  auto surface = SDL_RenderReadPixels(Window::renderer, &r);
  Global::maskTexture = SDL_CreateTextureFromSurface(Window::renderer, surface);
  // SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 128);
  if (World::iterateSystemsBak.size() <= 1) {
    SDL_SetTextureColorMod(Global::maskTexture, 128, 128, 128);
  }
  SDL_DestroySurface(surface);
  return true;
}

static bool renderMask() {
  SDL_FRect posRect = {0, 0, Global::viewPort.w, Global::viewPort.h};
  // SDL_SetTextureColorMod(Global::maskTexture, 128, 128, 128);

  SDL_RenderTexture(Window::renderer, Global::maskTexture, nullptr, &posRect);
  return true;
}

void World::enterAdvScrn() {
  AdvMapSys::init();
  LMouseUpSys.clear();
  LMouseDownSys.clear();
  RMouseUpSys.clear();
  RMouseDownSys.clear();
  keyUpSys.clear();
  keyDownSys.clear();

  LMouseUpSysBak.clear();
  LMouseDownSysBak.clear();
  RMouseUpSysBak.clear();
  RMouseDownSysBak.clear();
  keyUpSysBak.clear();
  keyDownSysBak.clear();

  iterateSystems.clear();
  iterateSystems.push_back(AnimateSys::run);
  iterateSystems.push_back(CameraSys::run);
  iterateSystems.push_back(World::run);
  iterateSystems.push_back(RenderSys::run);
  iterateSystems.push_back(FogSys::run);
  iterateSystems.push_back(BorderSys::run);
  iterateSystems.push_back(AdvMapSys::run);
  iterateSystems.push_back(HeroSys::run);
  iterateSystems.push_back(AudioSys::run);
  iterateSystems.push_back(CursorSys::run);

  iterateSystemsBak.clear();

  RMouseUpSys.push_back(CursorSys::rightMouseUp);

  LMouseUpSys.push_back(AdvMapSys::leftMouseUp);
  LMouseUpSys.push_back(CursorSys::leftMouseUp);

  LMouseDownSys.push_back(AdvMapSys::leftMouseDown);
  LMouseDownSys.push_back(CursorSys::leftMouseDown);

  RMouseDownSys.push_back(CursorSys::rightMouseDown);
  RMouseDownSys.push_back(AdvMapSys::rightMouseDown);

  keyUpSys.push_back(AdvMapSys::keyUp);
  keyDownSys.push_back(AdvMapSys::keyDown);

  Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
}

void World::enterTownScrn(uint8_t level, entt::entity ent, uint8_t type) {
  TownSys::init();
  enterScrn();

  iterateSystems.push_back([type] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(TownSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(TownSys::leftMouseUp);
    RMouseUpSys.push_back(TownSys::rightMouseUp);
    RMouseDownSys.push_back(TownSys::rightMouseDown);
    keyUpSys.push_back(TownSys::keyUp);

    CursorSys::run();

    if (type == (uint8_t)Enum::SCNTYPE::MOD) {
      TownSys::heroTownBonus();
    }

    return false;
  });

  Global::townScnPair = {level, ent};
  Global::townScnType = type;
  Global::goalIndex = 0xff;
  Global::townScnIndex = 0xff;

  auto pId = Global::playerId;
  for (uint8_t i = 0; i < Global::towns[pId].size(); i++) {
    auto pair = Global::towns[pId][i];
    if (pair.first == level && pair.second == ent) {
      if (i == 0) {
        Global::townScnPage = 0;
      } else if (i == Global::towns[pId].size() - 1) {
        Global::townScnPage = i - 2;
      } else {
        Global::townScnPage = i - 1;
      }
      break;
    }
  }

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterTownHall() {
  TownHallSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(TownHallSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(TownHallSys::leftMouseUp);

    CursorSys::run();

    return false;
  });

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterTownFort() {
  TownFortSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(TownFortSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(TownFortSys::leftMouseUp);
    CursorSys::run();

    return false;
  });

  Global::townFortFrameIndex = {};
  Global::townFortFrameTime = {};
  Global::townFortGroup = {};

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

bool World::enterFadeScrn() {
  iterateSystems = World::iterateSystemsBak.back();
  World::iterateSystemsBak.pop_back();

  enterScrn();
  iterateSystems.push_back(FadeSys::run);

  if (Global::fadeTexture) {
    SDL_DestroyTexture(Global::fadeTexture);
  }
  SDL_Rect r{static_cast<int>(Global::fadeRect.x),
             static_cast<int>(Global::fadeRect.y),
             static_cast<int>(Global::fadeRect.w),
             static_cast<int>(Global::fadeRect.h)};
  auto surface = SDL_RenderReadPixels(Window::renderer, &r);
  Global::fadeTexture = SDL_CreateTextureFromSurface(Window::renderer, surface);
  Global::fadeSpeed = 0.7f;
  Global::fadeAlpha = 255;

  SDL_DestroySurface(surface);

  Global::cursorType = (uint8_t)Enum::CURSOR::FADE;

  CursorSys::run();
  return false;
}

void World::exitScrn() {
  iterateSystems = iterateSystemsBak.back();

  LMouseUpSys = LMouseUpSysBak.back();
  LMouseDownSys = LMouseDownSysBak.back();
  RMouseUpSys = RMouseUpSysBak.back();
  RMouseDownSys = RMouseDownSysBak.back();

  keyUpSys = keyUpSysBak.back();

  LMouseUpSysBak.pop_back();
  LMouseDownSysBak.pop_back();
  RMouseUpSysBak.pop_back();
  RMouseDownSysBak.pop_back();

  iterateSystemsBak.pop_back();

  keyUpSysBak.pop_back();

  Global::cursorType = Global::cursorBack.back();
  Global::cursorBack.pop_back();
}

bool World::enterHeroScrn(uint8_t level, entt::entity ent, uint8_t type) {
  HeroScrSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(HeroScrSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(HeroScrSys::leftMouseUp);
    LMouseDownSys.push_back(HeroScrSys::leftMouseDown);
    RMouseUpSys.push_back(HeroScrSys::rightMouseUp);
    RMouseDownSys.push_back(HeroScrSys::rightMouseDown);
    keyUpSys.push_back(HeroScrSys::keyUp);
    CursorSys::run();

    return false;
  });

  Global::artPair = {0xff, 0xffff};
  Global::artPageIndex[0] = 0;

  Global::heroScnType = type;
  Global::heroScnIndex = 0Xff;
  Global::heroScnPair = {level, ent};
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;

  return true;
}

void World::enterTownPortal() {
  TownPortalSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(TownPortalSys::run);
    iterateSystems.push_back(CursorSys::run);

    keyUpSys.push_back(TownPortalSys::keyUp);
    CursorSys::run();

    return false;
  });

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterSplitCre() {
  SpliteCreSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(SpliteCreSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(SpliteCreSys::leftMouseUp);
    RMouseDownSys.push_back(SpliteCreSys::rightMouseDown);
    keyUpSys.push_back(SpliteCreSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::splitSliderNum = Global::splitCre[1]->second + 1;
  Global::splitFrameIndex = 0;
  Global::splitFrameTime = 0;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterHeroTrade(entt::entity heroEnt, entt::entity goalEnt,
                           uint8_t goalLevel) {
  HeroTradeSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(HeroTradeSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(HeroTradeSys::leftMouseUp);
    LMouseDownSys.push_back(HeroTradeSys::leftMouseDown);
    RMouseDownSys.push_back(HeroTradeSys::rightMouseDown);
    keyUpSys.push_back(HeroTradeSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::artClick = false;
  Global::artPageIndex[0] = 0;
  Global::artPair = {0xff, 0xffff};

  Global::goalLevel = goalLevel;
  Global::goalIndex = 0xff;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterLearn(entt::entity heroEnt, entt::entity goalEnt,
                       uint8_t goalLevel) {
  LearnSys::init();

  enterScrn();

  iterateSystems.pop_back();
  iterateSystems.push_back(LearnSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(LearnSys::leftMouseUp);
  RMouseDownSys.push_back(LearnSys::rightMouseDown);
  keyUpSys.push_back(LearnSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::goalLevel = goalLevel;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterKingdom() {
  KingdomSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(KingdomSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(KingdomSys::leftMouseUp);
    keyUpSys.push_back(KingdomSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

bool World::enterAdvPop() {
  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    World::iterateSystems.push_back(AdvPopSys::run);
    World::iterateSystems.push_back(CursorSys::run);

    RMouseUpSys.push_back(AdvPopSys::rightMouseUp);

    CursorSys::run();

    SDL_SetTextureColorMod(Global::maskTexture, 255, 255, 255);

    return false;
  });

  Global::cursorPoint = {Window::mouseX, Window::mouseY};
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;

  return true;
}

void World::enterSpell(entt::entity heroEnt) {
  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(SpellSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(SpellSys::leftMouseUp);
    RMouseDownSys.push_back(SpellSys::rightMouseDown);

    keyUpSys.push_back(SpellSys::keyUp);

    CursorSys::run();

    // SDL_SetTextureColorMod(Global::maskTexture, 255, 255, 255);

    return false;
  });

  Global::splSchool = 4;
  Global::splBattle = false;
  Global::heroEnt = heroEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterAdvOpt() {
  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(AdvOptionSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(AdvOptionSys::leftMouseUp);
    keyUpSys.push_back(AdvOptionSys::keyUp);

    CursorSys::run();

    SDL_SetTextureColorMod(Global::maskTexture, 255, 255, 255);

    return false;
  });

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterViewWorld() {
  ViewWorldSys::init();

  enterScrn();
  iterateSystems.push_back([] {
    iterateSystems.clear();
    // iterateSystems.push_back(renderMask);
    iterateSystems.push_back(ViewWorldSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(ViewWorldSys::leftMouseUp);
    keyUpSys.push_back(ViewWorldSys::keyUp);

    CursorSys::run();

    SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);

    return false;
  });

  Global::viewWorldScale = 2;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterAdvSet() {
  // AdvSetSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(AdvSetSys::run);
  iterateSystems.push_back(CursorSys::run);

  // LMouseUpSys.push_back(SpellSys::leftMouseUp);
  keyUpSys.push_back(AdvSetSys::keyUp);

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterPuzzle(entt::entity goalEnt) {
  PuzzleSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(PuzzleSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(PuzzleSys::leftMouseUp);
  keyUpSys.push_back(PuzzleSys::keyUp);

  Global::puzzleFadeTime = Window::dtNow + 1000;

  Global::goalEnt = goalEnt;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterTreasure(entt::entity heroEnt, entt::entity goalEnt) {
  TreasureSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(TreasureSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(TreasureSys::leftMouseUp);
  RMouseDownSys.push_back(TreasureSys::rightMouseDown);
  keyUpSys.push_back(TreasureSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::goalIndex = (uint8_t)0xff;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterWaterWheel(entt::entity goalEnt) {
  WaterWheelSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(WaterWheelSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(WaterWheelSys::leftMouseUp);
  RMouseDownSys.push_back(WaterWheelSys::rightMouseDown);
  keyUpSys.push_back(WaterWheelSys::keyUp);

  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterWindMill(entt::entity goalEnt) {
  WindMillSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(WindMillSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(WindMillSys::leftMouseUp);
  RMouseDownSys.push_back(WindMillSys::rightMouseDown);
  keyUpSys.push_back(WindMillSys::keyUp);

  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMine(entt::entity goalEnt) {
  MineSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(MineSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MineSys::leftMouseUp);
  RMouseDownSys.push_back(MineSys::rightMouseDown);
  keyUpSys.push_back(MineSys::keyUp);

  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterWarTomb(entt::entity heroEnt, entt::entity goalEnt) {
  WarTombSys::init();

  Global::confirmCallBack = [heroEnt, goalEnt]() {
    exitScrn();
    enterScrn();
    iterateSystems.pop_back();
    iterateSystems.push_back(WarTombSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(WarTombSys::leftMouseUp);
    RMouseDownSys.push_back(WarTombSys::rightMouseDown);
    keyUpSys.push_back(WarTombSys::keyUp);

    Global::heroEnt = heroEnt;
    Global::goalEnt = goalEnt;
    Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
  };
  Global::confirmdraw = []() {

  };
  enterConfirm(100, 100, (uint8_t)Enum::SCNTYPE::MOD);
}

void World::enterPrison(entt::entity heroEnt, entt::entity goalEnt) {
  PrisonSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(PrisonSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(PrisonSys::leftMouseUp);
    RMouseDownSys.push_back(PrisonSys::rightMouseDown);
    keyUpSys.push_back(PrisonSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterWitchHut(entt::entity heroEnt, entt::entity goalEnt) {
  WitchHutSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(WitchHutSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(WitchHutSys::leftMouseUp);
  RMouseDownSys.push_back(WitchHutSys::rightMouseDown);
  keyUpSys.push_back(WitchHutSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterScholar(entt::entity heroEnt, entt::entity goalEnt) {
  ScholarSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(ScholarSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(ScholarSys::leftMouseUp);
    RMouseDownSys.push_back(ScholarSys::rightMouseDown);
    keyUpSys.push_back(ScholarSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterUnivers(entt::entity heroEnt, entt::entity goalEnt) {
  UniversitySys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(UniversitySys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(UniversitySys::leftMouseUp);
  RMouseDownSys.push_back(UniversitySys::rightMouseDown);
  keyUpSys.push_back(UniversitySys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::goalIndex = 0xff;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterShipyard(entt::entity heroEnt, entt::entity goalEnt) {
  ShipyardSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(ShipyardSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(ShipyardSys::leftMouseUp);
  keyUpSys.push_back(ShipyardSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterLvlup(entt::entity heroEnt) {
  LevelUpSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(LevelUpSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(LevelUpSys::leftMouseUp);
  RMouseDownSys.push_back(LevelUpSys::rightMouseDown);
  keyUpSys.push_back(LevelUpSys::keyUp);

  Global::goalIndex = 0;
  Global::heroEnt = heroEnt;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterTavern(entt::entity heroEnt, entt::entity goalEnt) {
  TavernSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(TavernSys::run);

    iterateSystems.push_back(VideoSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(TavernSys::leftMouseUp);
    RMouseDownSys.push_back(TavernSys::rightMouseDown);
    keyUpSys.push_back(TavernSys::keyUp);

    CursorSys::run();

    return false;
  });

  TavernSys::refreshHero(Global::playerId, 0);
  TavernSys::refreshHero(Global::playerId, 1);
  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::goalIndex = 0;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;

  // 定义分布范围 [2886, 3158]
  std::uniform_int_distribution<int> dist(2886, 3036);
  // 生成随机数
  auto r = dist(Global::gen);
  auto strPool = *Lang::strPool[Global::langIndex];
  Global::tavernStr = strPool[r];

  auto leftX = (Global::viewPort.w - 395) / 2 + 70;
  auto leftY = (Global::viewPort.h - 504) / 2 + 56;
  VideoSys::init("./Video/TAVERN.BIK", leftX, leftY);
}

void World::enterGarrison(entt::entity heroEnt, entt::entity goalEnt) {
  GarrisonSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(GarrisonSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(GarrisonSys::leftMouseUp);
  keyUpSys.push_back(GarrisonSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterDwe(entt::entity heroEnt, entt::entity goalEnt) {
  DwellingSys::init();

  enterScrn();
  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(DwellingSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(DwellingSys::leftMouseUp);
    RMouseDownSys.push_back(DwellingSys::rightMouseDown);
    keyUpSys.push_back(DwellingSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::dweIndex = 0;
  Global::dweGroup = {};
  Global::dweFrameIndex = {};
  Global::dweFrameTime = {};

  Global::dweSliderNum = DwellingSys::maxCount();

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMageGuild(uint8_t level, entt::entity ent) {
  MageGuildSys::init();

  enterScrn();

  iterateSystems.pop_back();
  iterateSystems.push_back(MageGuildSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MageGuildSys::leftMouseUp);
  RMouseDownSys.push_back(MageGuildSys::rightMouseDown);
  keyUpSys.push_back(MageGuildSys::keyUp);

  Global::townScnPair = {level, ent};
  Global::goalIndex = 0xff;
  Global::townScnIndex = 0xff;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterTownBuild(uint8_t bId) {
  TownBuildSys::init();

  enterScrn();
  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(TownBuildSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(TownBuildSys::leftMouseUp);
    keyUpSys.push_back(TownBuildSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::townBuildBid = bId;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterWarMachineFac(entt::entity heroEnt, entt::entity goalEnt) {
  WarMachineFacSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);

    iterateSystems.push_back(WarMachineFacSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(WarMachineFacSys::leftMouseUp);
    RMouseDownSys.push_back(WarMachineFacSys::rightMouseDown);
    keyUpSys.push_back(WarMachineFacSys::keyUp);

    CursorSys::run();
    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::dweIndex = 0;
  Global::dweGroup.fill(2);

  Global::dweSliderNum = WarMachineFacSys::maxCount();

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMarket(entt::entity heroEnt, entt::entity goalEnt) {
  MarketSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(MarketSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MarketSys::leftMouseUp);
  RMouseDownSys.push_back(MarketSys::rightMouseDown);
  keyUpSys.push_back(MarketSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::artPair = {0xff, 0xffff};
  Global::makIndex[0] = Global::makIndex[1] = 0xff;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterLearnStone(entt::entity heroEnt, entt::entity goalEnt) {
  LearnStoneSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(LearnStoneSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(LearnStoneSys::leftMouseUp);
  RMouseDownSys.push_back(LearnStoneSys::rightMouseDown);
  keyUpSys.push_back(LearnStoneSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterShrMag(entt::entity heroEnt, entt::entity goalEnt) {
  ShrineMagicSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(ShrineMagicSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(ShrineMagicSys::leftMouseUp);
  RMouseDownSys.push_back(ShrineMagicSys::rightMouseDown);
  keyUpSys.push_back(ShrineMagicSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMagWell(entt::entity heroEnt, entt::entity goalEnt) {
  MagWellSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(MagWellSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MagWellSys::leftMouseUp);
  RMouseDownSys.push_back(MagWellSys::rightMouseDown);
  keyUpSys.push_back(MagWellSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMagSpring(entt::entity heroEnt, entt::entity goalEnt) {
  MagSpringSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(MagSpringSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MagSpringSys::leftMouseUp);
  RMouseDownSys.push_back(MagSpringSys::rightMouseDown);
  keyUpSys.push_back(MagSpringSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterKnoTree(entt::entity heroEnt, entt::entity goalEnt) {
  KnoTreeSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(KnoTreeSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(KnoTreeSys::leftMouseUp);
  RMouseDownSys.push_back(KnoTreeSys::rightMouseDown);
  keyUpSys.push_back(KnoTreeSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterRalFlag(entt::entity heroEnt, entt::entity goalEnt) {
  RalFlagSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(RalFlagSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(RalFlagSys::leftMouseUp);
  RMouseDownSys.push_back(RalFlagSys::rightMouseDown);
  keyUpSys.push_back(RalFlagSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterSchoolWar(entt::entity heroEnt, entt::entity goalEnt) {
  SchoolWarSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(SchoolWarSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(SchoolWarSys::leftMouseUp);
  keyUpSys.push_back(SchoolWarSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterTemple(entt::entity heroEnt, entt::entity goalEnt) {
  TempleSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(TempleSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(TempleSys::leftMouseUp);
  keyUpSys.push_back(TempleSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterSchoolMag(entt::entity heroEnt, entt::entity goalEnt) {
  SchoolMagSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(SchoolMagSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(SchoolMagSys::leftMouseUp);
  keyUpSys.push_back(SchoolMagSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterPandora(entt::entity heroEnt, entt::entity goalEnt) {
  PandoraSys::init();

  Global::confirmCallBack = [heroEnt, goalEnt]() {
    exitScrn();
    enterScrn();
    iterateSystems.pop_back();
    iterateSystems.push_back(PandoraSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(PandoraSys::leftMouseUp);
    keyUpSys.push_back(PandoraSys::keyUp);

    Global::heroEnt = heroEnt;
    Global::goalEnt = goalEnt;

    Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
  };
  enterConfirm(100, 100, (uint8_t)Enum::SCNTYPE::MOD);
}

void World::enterIFortune(entt::entity heroEnt, entt::entity goalEnt) {
  IdolFortuneSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(IdolFortuneSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(IdolFortuneSys::leftMouseUp);
  keyUpSys.push_back(IdolFortuneSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterFFortune(entt::entity heroEnt, entt::entity goalEnt) {
  FouFortuneSys::init();
  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(FouFortuneSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(FouFortuneSys::leftMouseUp);
  keyUpSys.push_back(FouFortuneSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterCorpse(entt::entity heroEnt, entt::entity goalEnt) {
  CorpseSys::init();
  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(CorpseSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(CorpseSys::leftMouseUp);
  RMouseDownSys.push_back(CorpseSys::rightMouseDown);
  keyUpSys.push_back(CorpseSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterArtifact(entt::entity heroEnt, entt::entity goalEnt) {
  ArtifactSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(ArtifactSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(ArtifactSys::leftMouseUp);
    RMouseDownSys.push_back(ArtifactSys::rightMouseDown);
    keyUpSys.push_back(ArtifactSys::keyUp);
    CursorSys::run();

    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMarletto(entt::entity heroEnt, entt::entity goalEnt) {
  MarlettoSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(MarlettoSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MarlettoSys::leftMouseUp);
  RMouseDownSys.push_back(MarlettoSys::rightMouseDown);
  keyUpSys.push_back(MarlettoSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterArena(entt::entity heroEnt, entt::entity goalEnt) {
  ArenaSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(ArenaSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(ArenaSys::leftMouseUp);
  RMouseDownSys.push_back(ArenaSys::rightMouseDown);
  keyUpSys.push_back(ArenaSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterCartographer(entt::entity heroEnt, entt::entity goalEnt) {
  CartographerSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(CartographerSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(CartographerSys::leftMouseUp);
  keyUpSys.push_back(CartographerSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMermaid(entt::entity heroEnt, entt::entity goalEnt) {
  MermaidSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(MermaidSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MermaidSys::leftMouseUp);
  keyUpSys.push_back(MermaidSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterBuoy(entt::entity heroEnt, entt::entity goalEnt) {
  BuoySys::init();
  
  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(BuoySys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(BuoySys::leftMouseUp);
  RMouseDownSys.push_back(BuoySys::rightMouseDown);
  keyUpSys.push_back(BuoySys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterSeaChest(entt::entity heroEnt, entt::entity goalEnt) {
  SeaChestSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(SeaChestSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(SeaChestSys::leftMouseUp);
  keyUpSys.push_back(SeaChestSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterMerCamp(entt::entity heroEnt, entt::entity goalEnt) {
  MerCampSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(MerCampSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(MerCampSys::leftMouseUp);
  keyUpSys.push_back(MerCampSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterLibrary(entt::entity heroEnt, entt::entity goalEnt) {
  LibrarySys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(LibrarySys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(LibrarySys::leftMouseUp);
  RMouseDownSys.push_back(LibrarySys::rightMouseDown);
  keyUpSys.push_back(LibrarySys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterHutMag(entt::entity heroEnt, entt::entity goalEnt) {
  HutMagSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(HutMagSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(HutMagSys::leftMouseUp);
    keyUpSys.push_back(HutMagSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::hutMagIndex = -1;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterWhirlPool(entt::entity heroEnt, entt::entity goalEnt) {
  WhirlPoolSys::init();

  enterScrn();
  iterateSystems.pop_back();

  iterateSystems.push_back(WhirlPoolSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(WhirlPoolSys::leftMouseUp);
  keyUpSys.push_back(WhirlPoolSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterSirens(entt::entity heroEnt, entt::entity goalEnt) {
  SirensSys::init();

  Global::confirmCallBack = [heroEnt, goalEnt]() {
    exitScrn();
    enterScrn();
    iterateSystems.pop_back();
    iterateSystems.push_back(SirensSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(SirensSys::leftMouseUp);
    keyUpSys.push_back(SirensSys::keyUp);

    Global::heroEnt = heroEnt;
    Global::goalEnt = goalEnt;

    Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
  };
  enterConfirm(100, 100, (uint8_t)Enum::SCNTYPE::MOD);
}

void World::enterHillFt(entt::entity heroEnt, entt::entity goalEnt) {
  HillFtSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(HillFtSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(HillFtSys::leftMouseUp);
  RMouseDownSys.push_back(HillFtSys::rightMouseDown);
  keyUpSys.push_back(HillFtSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterFouYouth(entt::entity heroEnt, entt::entity goalEnt) {
  FouYouthSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(FouYouthSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(FouYouthSys::leftMouseUp);
  keyUpSys.push_back(FouYouthSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterWaterHole(entt::entity heroEnt, entt::entity goalEnt) {
  WaterHoleSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(WaterHoleSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(WaterHoleSys::leftMouseUp);
  keyUpSys.push_back(WaterHoleSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterGarRev(entt::entity heroEnt, entt::entity goalEnt) {
  GarRevSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(GarRevSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(GarRevSys::leftMouseUp);
  keyUpSys.push_back(GarRevSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterFreeGuild(entt::entity heroEnt, entt::entity goalEnt) {
  FreeGuildSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(FreeGuildSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(FreeGuildSys::leftMouseUp);
  keyUpSys.push_back(FreeGuildSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterFaerieRing(entt::entity heroEnt, entt::entity goalEnt) {
  FaerieRingSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(FaerieRingSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(FaerieRingSys::leftMouseUp);
  RMouseDownSys.push_back(FaerieRingSys::rightMouseDown);
  keyUpSys.push_back(FaerieRingSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterStarAxis(entt::entity heroEnt, entt::entity goalEnt) {
  StarAxisSys::init();

  enterScrn();
  iterateSystems.pop_back();

  iterateSystems.push_back(StarAxisSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(StarAxisSys::leftMouseUp);
  RMouseDownSys.push_back(StarAxisSys::rightMouseDown);
  keyUpSys.push_back(StarAxisSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterAltarSac(entt::entity heroEnt, entt::entity goalEnt) {
  AltarSacSys::init();

  enterScrn();
  iterateSystems.pop_back();
  iterateSystems.push_back(AltarSacSys::run);
  iterateSystems.push_back(CursorSys::run);

  LMouseUpSys.push_back(AltarSacSys::leftMouseUp);
  RMouseDownSys.push_back(AltarSacSys::rightMouseDown);
  keyUpSys.push_back(AltarSacSys::keyUp);

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;

  Global::alts.clear();
  Global::altIndex = 0xff;
  Global::altSliderNum = 0;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterCreature(std::pair<uint8_t, uint16_t> crePair,
                          uint8_t creType) {
  CreatureSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(CreatureSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(CreatureSys::leftMouseUp);
    RMouseUpSys.push_back(CreatureSys::rightMouseUp);
    keyUpSys.push_back(CreatureSys::keyUp);

    CursorSys::run();

    if (iterateSystemsBak.size() <= 1) {
      SDL_SetTextureColorMod(Global::maskTexture, 255, 255, 255);
    }
    return false;
  });

  Global::creType = creType;
  Global::crePair = crePair;

  Global::creFrameIndex = 0;
  Global::creFrameTime = 0;
  Global::creGroup = 2;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterCreature(std::pair<uint8_t, entt::entity> creHeroPair,
                          std::pair<uint8_t, uint16_t> crePair,
                          uint8_t creType) {
  enterCreature(crePair, creType);
  Global::creHeroPair = creHeroPair;
}

void World::enterWarMachine(uint16_t warMId, uint8_t warMType) {
  WarMachineSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(WarMachineSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(WarMachineSys::leftMouseUp);
    RMouseUpSys.push_back(WarMachineSys::rightMouseUp);
    keyUpSys.push_back(WarMachineSys::keyUp);
    CursorSys::run();

    return false;
  });

  Global::creType = warMType;
  Global::crePair = {warMId, 1};
  Global::creGroup = 2;

  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterStables(entt::entity heroEnt, entt::entity goalEnt) {
  StablesSys::init();

  enterScrn();
  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(StablesSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(StablesSys::leftMouseUp);
    keyUpSys.push_back(StablesSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterBattle(entt::entity heroEnt, entt::entity goalEnt,
                        uint8_t goalLevel) {
  BattleSys::init();

  enterScrn();
  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(BattleSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(BattleSys::leftMouseUp);
    keyUpSys.push_back(BattleSys::keyUp);

    CursorSys::run();

    return false;
  });

  auto &r = World::registrys[goalLevel];
  auto oComp = r.get<ObjectComp>(goalEnt);
  auto x = oComp.x + oComp.accessTiles[0].first;
  auto y = oComp.y + oComp.accessTiles[0].second;
  auto tEnt = Global::terrains[goalLevel][x][y].front();
  auto tComp = r.get<TerrainComp>(tEnt);
  Global::battleScn.field = TerrainSet::terrains[tComp.index].battleFields[0];
  switch (oComp.type) {
  case ObjectType::HERO: {
    Global::battleScn.type = BATTLE_FIELD_TYPE_HERO;
    break;
  }
  case ObjectType::TOWN: {
    Global::battleScn.type = BATTLE_FIELD_TYPE_TOWN;
    break;
  }
  default: {
    Global::battleScn.type = BATTLE_FIELD_TYPE_MONSTER;
    break;
  }
  }

  Global::heroEnt = heroEnt;
  Global::goalEnt = goalEnt;
  Global::goalLevel = goalLevel;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterConfirm(float bakW, float bakH, uint8_t confirmType) {
  ConfirmSys::init();

  enterScrn();

  iterateSystems.push_back([] {
    iterateSystems.clear();
    iterateSystems.push_back(renderMask);
    iterateSystems.push_back(ConfirmSys::run);
    iterateSystems.push_back(CursorSys::run);

    LMouseUpSys.push_back(ConfirmSys::leftMouseUp);
    RMouseUpSys.push_back(ConfirmSys::rightMouseUp);
    keyUpSys.push_back(ConfirmSys::keyUp);

    CursorSys::run();

    return false;
  });

  Global::confirmBakW = bakW;
  Global::confirmBakH = bakH;
  Global::confirmType = confirmType;
  Global::cursorType = (uint8_t)Enum::CURSOR::DEFAULT;
}

void World::enterScrn() {
  iterateSystemsBak.push_back(iterateSystems);
  iterateSystems.pop_back();
  iterateSystems.push_back(savaMask);

  LMouseUpSysBak.push_back(LMouseUpSys);
  LMouseDownSysBak.push_back(LMouseDownSys);
  RMouseUpSysBak.push_back(RMouseUpSys);
  RMouseDownSysBak.push_back(RMouseDownSys);

  keyUpSysBak.push_back(keyUpSys);

  LMouseUpSys.clear();
  LMouseDownSys.clear();
  RMouseUpSys.clear();
  RMouseDownSys.clear();

  keyUpSys.clear();

  Global::cursorBack.push_back(Global::cursorType);
}

bool World::run() {
  if (needSort) {
    for (auto &registry : registrys) {
      registry.sort<PositionComp>(
          [](const auto &l, const auto &r) { return l.z < r.z; });
      needSort = false;
    }
  }
  return true;
}