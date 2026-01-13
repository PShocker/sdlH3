#include "TownSys.h"
#include "BMPFont/BMPFont.h"
#include "CameraSys.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/TownCfg.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TownComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Lang/Lang.h"
#include "Pcx/Pcx.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "Sys/FreeTypeSys.h"
#include "Sys/gui/AdvMapSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <functional>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

static std::optional<uint8_t> mouseBuildId;
static std::unordered_map<uint8_t, std::vector<bool>> townAreaBuilds[8];

static std::unordered_set<uint8_t> townVisiableBuild() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto s = TownCfg::townDefaultAni[townComp->id];
  for (const auto &pair : townComp->buildings) {
    s.insert(pair.first);
  }
  if (s.contains((uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_1)) {
    s.erase((uint8_t)TownCfg::Building::DWELLING_LEVEL_1);
  }
  if (s.contains((uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_2)) {
    s.erase((uint8_t)TownCfg::Building::DWELLING_LEVEL_2);
  }
  if (s.contains((uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_3)) {
    s.erase((uint8_t)TownCfg::Building::DWELLING_LEVEL_3);
  }
  if (s.contains((uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_4)) {
    s.erase((uint8_t)TownCfg::Building::DWELLING_LEVEL_4);
  }
  if (s.contains((uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_5)) {
    s.erase((uint8_t)TownCfg::Building::DWELLING_LEVEL_5);
  }
  if (s.contains((uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_6)) {
    s.erase((uint8_t)TownCfg::Building::DWELLING_LEVEL_6);
  }
  if (s.contains((uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_7)) {
    s.erase((uint8_t)TownCfg::Building::DWELLING_LEVEL_7);
  }
  if (s.contains((uint8_t)TownCfg::Building::MAGE_GUILD_5)) {
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_1);
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_2);
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_3);
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_4);
  }
  if (s.contains((uint8_t)TownCfg::Building::MAGE_GUILD_4)) {
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_1);
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_2);
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_3);
  }
  if (s.contains((uint8_t)TownCfg::Building::MAGE_GUILD_3)) {
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_1);
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_2);
  }
  if (s.contains((uint8_t)TownCfg::Building::MAGE_GUILD_2)) {
    s.erase((uint8_t)TownCfg::Building::MAGE_GUILD_1);
  }
  if (s.contains((uint8_t)TownCfg::Building::CAPITOL)) {
    s.erase((uint8_t)TownCfg::Building::TOWN_HALL);
    s.erase((uint8_t)TownCfg::Building::CITY_HALL);
    s.erase((uint8_t)TownCfg::Building::VILLAGE_HALL);
  }
  if (s.contains((uint8_t)TownCfg::Building::CITY_HALL)) {
    s.erase((uint8_t)TownCfg::Building::TOWN_HALL);
    s.erase((uint8_t)TownCfg::Building::VILLAGE_HALL);
  }
  if (s.contains((uint8_t)TownCfg::Building::TOWN_HALL)) {
    s.erase((uint8_t)TownCfg::Building::VILLAGE_HALL);
  }
  if (s.contains((uint8_t)TownCfg::Building::CASTLE)) {
    s.erase((uint8_t)TownCfg::Building::FORT);
    s.erase((uint8_t)TownCfg::Building::CITADEL);
  }
  if (s.contains((uint8_t)TownCfg::Building::CITADEL)) {
    s.erase((uint8_t)TownCfg::Building::FORT);
  }
  return s;
}

static void close() {
  Global::splitOn = false;
  World::enterAdvScrn();
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  if (townComp->heroEnt[1].has_value()) {
    auto heroEnt = townComp->heroEnt[1].value();
    AdvMapSys::heroFocus(heroEnt, level);
  }
}

static std::pair<uint16_t, uint32_t> *cre() {
  std::pair<uint16_t, uint32_t> *crePtr = nullptr;
  auto [li, lm] = std::pair{Global::townScnIndex / 8, Global::townScnIndex % 8};
  if (Global::townScnIndex == 0xff || lm == 0) {
    return crePtr;
  }
  lm -= 1;
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  if (li == 0) {
    if (townComp->heroEnt[0].has_value()) {
      auto heroEnt = townComp->heroEnt[0].value();
      auto &creatures = registry.get<HeroComp>(heroEnt).creatures;
      crePtr = &creatures[lm];
    } else {
      auto &creatures = townComp->garCreatures;
      crePtr = &creatures[lm];
    }
  } else {
    auto heroEnt = townComp->heroEnt[1].value();
    auto &creatures = registry.get<HeroComp>(heroEnt).creatures;
    crePtr = &creatures[lm];
  }
  return crePtr;
}

static void split() {
  Global::splitCre[0] = cre();
  Global::splitOn = true;
}

static std::vector<Button> buttonInfo() {
  std::vector<Button> v;
  Button b;

  auto t = Global::defCache["tsbtns.def/0"];

  std::vector<SDL_Texture *> vec;
  vec = {t[0], t[1], t[2]};
  b.textures = vec;
  b.r = {744, 382, 48, 28};
  b.func = split;
  b.disable = cre() == nullptr ? true : false;
  v.push_back(b);

  vec = {t[4], t[5]};
  b.textures = vec;
  b.r = {744, 544, 48, 28};
  b.func = close;
  b.disable = false;
  v.push_back(b);

  if (Global::townScnType == (uint8_t)Enum::SCNTYPE::POP) {
    for (auto &b : v) {
      b.disable = true;
    }
  }

  return v;
}

static void drawScrn() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto texture = Global::pcxCache[TownCfg::backGroundsStr[townComp->id]][0];
  SDL_FRect posRect = {leftUp.x, leftUp.y, 800, 374};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  posRect = {leftUp.x, leftUp.y + 374, 800, 226};
  texture = Global::pcxCache["townScrn.pcx"][Global::playerId];
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
}

static void drawBuilds() {
  SDL_FRect posRect;

  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  SDL_FPoint mousePoint = {Window::mouseX, Window::mouseY};

  auto builds = townVisiableBuild();
  mouseBuildId = std::nullopt;
  std::vector<uint8_t> sortBuild;
  for (auto build : TownCfg::townZ[townComp->id]) {
    if (builds.contains(build)) {
      auto textures =
          Global::defCache[TownCfg::townBuilds[townComp->id].at(build) + "/0"];
      auto frame = Global::bldFrameIndex % textures.size();
      auto townPoint = TownCfg::townPoint[townComp->id].at(build);
      posRect = {leftUp.x + townPoint.x, leftUp.y + townPoint.y,
                 static_cast<float>(textures[frame]->w),
                 static_cast<float>(textures[frame]->h)};
      if (posRect.x <= mousePoint.x && mousePoint.x < posRect.x + posRect.w &&
          posRect.y <= mousePoint.y && mousePoint.y < posRect.y + posRect.h) {
        uint32_t point = (mousePoint.x - posRect.x) +
                         textures[0]->w * (mousePoint.y - posRect.y);
        if (!townAreaBuilds[townComp->id].contains(build) &&
            TownCfg::townBorder[townComp->id].contains(build)) {
          townAreaBuilds[townComp->id][build] =
              Pcx("./Data/H3bitmap.lod/" +
                  TownCfg::townArea[townComp->id].at(build))
                  .loadArea();
        }
        if (townAreaBuilds[townComp->id].contains(build) &&
            townAreaBuilds[townComp->id][build][point]) {
          mouseBuildId = build;
        }
      }
      sortBuild.push_back(build);
    }
  }
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto funcPtr = topFunc.target<bool (*)()>();
  auto top = (funcPtr && *topFunc.target<bool (*)()>() == TownSys::run);
  for (auto build : sortBuild) {
    auto textures =
        Global::defCache[TownCfg::townBuilds[townComp->id].at(build) + "/0"];
    auto frame = Global::bldFrameIndex % textures.size();
    auto townPoint = TownCfg::townPoint[townComp->id].at(build);
    posRect = {leftUp.x + townPoint.x, leftUp.y + townPoint.y,
               static_cast<float>(textures[frame]->w),
               static_cast<float>(textures[frame]->h)};
    SDL_RenderTexture(Window::renderer, textures[0], nullptr, &posRect);
    SDL_RenderTexture(Window::renderer, textures[frame], nullptr, &posRect);
    if (mouseBuildId == build && top) {
      auto texture = Global::pcxCache[TownCfg::townBorder[townComp->id].at(
          mouseBuildId.value())][0];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    }
  }
}

static void drawBorder() {
  // 绘制边框
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FRect posRect = {leftUp.x, leftUp.y, 800, 374};
  SDL_SetRenderDrawColor(Window::renderer, 247, 222, 123, 255); //
  SDL_RenderRect(Window::renderer, &posRect);
}

static void drawButton() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto funcPtr = topFunc.target<bool (*)()>();
  auto top = (funcPtr && *topFunc.target<bool (*)()>() == TownSys::run);
  AdvMapSys::drawButtons(leftUp.x, leftUp.y, top, v);
}

void drawCreature(uint8_t i,
                  std::vector<std::pair<uint16_t, uint32_t>> *creature) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FRect posRect;
  for (uint8_t m = 0; m < creature->size(); m++) {
    auto [id, count] = creature->at(m);
    posRect = {leftUp.x + 304 + m * 62, leftUp.y + 387 + i * 96, 58, 64};
    if (count == 0) {
      if (Global::splitOn) {
        SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
        SDL_RenderRect(Window::renderer, &posRect);
      }
      continue;
    }
    auto texture = Global::defCache["TWCRPORT.def/0"][id + 2];
    SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
    if (Global::splitOn) {
      std::pair<uint16_t, uint32_t> *crePtr = &creature->at(m);
      if (Global::splitCre[0] != crePtr &&
          crePtr->first == Global::splitCre[0]->first) {
        SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
        SDL_RenderRect(Window::renderer, &posRect);
      }
    }

    posRect.x += 58;
    posRect.y = posRect.y + 48;
    while (count > 0) {
      auto digit = count % 10; // 获取当前最低位
      texture = BMPFont::fontCache["verd10b.fnt"]['0' + digit].texture;
      posRect = {posRect.x - texture->w, posRect.y,
                 static_cast<float>(texture->w),
                 static_cast<float>(texture->h)};
      SDL_RenderTexture(Window::renderer, texture, NULL, &posRect);
      count /= 10; // 去掉最低位
    }
  }
}

static void drawHeroPor() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FRect posRect;
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  for (auto i = 0; i <= 1; i++) {
    if (townComp->heroEnt[i].has_value()) {
      auto heroEnt = townComp->heroEnt[i].value();
      auto heroComp = &registry.get<HeroComp>(heroEnt);
      posRect = {leftUp.x + 242, leftUp.y + 387 + i * 96, 58, 64};
      auto texture =
          Global::pcxCache[HeroCfg::heroLargePor[heroComp->portrait]][0];
      SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      drawCreature(i, &heroComp->creatures);
    } else if (i == 0) {
      auto playerId = registry.get<PlayerIdComp>(townEnt).id;
      posRect = {leftUp.x + 241, leftUp.y + 387, 58, 64};
      SDL_RenderTexture(Window::renderer,
                        Global::defCache["CREST58.def/0"][playerId], nullptr,
                        &posRect);
      drawCreature(i, &townComp->garCreatures);
    }
  }
  if (Global::townScnIndex != 0xff && !Global::splitOn) {
    auto i = Global::townScnIndex / 8;
    auto m = Global::townScnIndex % 8;
    posRect = {leftUp.x + 242 + m * 62, leftUp.y + 387 + i * 96, 58, 64};
    SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 255);
    SDL_RenderRect(Window::renderer, &posRect);
  }
}
static void buildAnimate() {
  Global::bldFrameTime += Window::deltaTime;
  if (Global::bldFrameTime >= 120) {
    Global::bldFrameTime = 0;
    Global::bldFrameIndex++;
  }
}

static void drawResbar() {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  AdvMapSys::drawResBar(leftUp.x + 3, leftUp.y + 575);
}

static void drawBottomInfo() {
  auto &topFunc = World::iterateSystems[World::iterateSystems.size() - 2];
  auto funcPtr = topFunc.target<bool (*)()>();
  auto top = (funcPtr && *topFunc.target<bool (*)()>() == TownSys::run);
  if (top) {
    SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                      (Global::viewPort.h - 600) / 2};
    SDL_FRect posRect;
    auto [level, townEnt] = Global::townScnPair;
    auto &registry = World::registrys[level];
    auto townComp = &registry.get<TownComp>(townEnt);
    SDL_FPoint point = {Window::mouseX, Window::mouseY};

    FreeTypeSys::setSize(13);
    FreeTypeSys::setColor(255, 255, 255, 255);
    auto strPool = *Lang::strPool[Global::langIndex];
    std::u16string s = u"";
    for (auto i = 0; i <= 1; i++) {
      std::vector<std::pair<uint16_t, uint32_t>> *creature;
      if (townComp->heroEnt[i].has_value()) {
        auto heroEnt = townComp->heroEnt[i].value();
        auto heroComp = &registry.get<HeroComp>(heroEnt);
        creature = &heroComp->creatures;
        posRect = {leftUp.x + 242, leftUp.y + 387 + i * 96, 58, 64};
        if (SDL_PointInRectFloat(&point, &posRect)) {
          auto heroName = strPool[1262 + heroComp->portrait];
          s += strPool[2862] + heroName + u"(" + strPool[2883 + i] + u")";
          break;
        }
      } else if (i == 0) {
        creature = &townComp->garCreatures;
      }
      for (uint8_t m = 0; m < creature->size(); m++) {
        auto [id, count] = creature->at(m);
        posRect = {leftUp.x + 304 + m * 62, leftUp.y + 387 + i * 96, 58, 64};
        if (Global::splitOn) {
        }
      }
    }
    FreeTypeSys::drawCenter(leftUp.x + 400, leftUp.y + 554, s);
  }
}

bool TownSys::run() {
  buildAnimate();
  drawScrn();
  drawBuilds();
  drawBorder();
  drawButton();
  drawHeroPor();
  drawResbar();
  drawBottomInfo();
  return true;
}

// 修正版本：全局累加相同种类的数量
static std::vector<std::pair<uint16_t, uint32_t>>
mergeCreatures(const std::vector<std::pair<uint16_t, uint32_t>> &vec1,
               const std::vector<std::pair<uint16_t, uint32_t>> &vec2) {
  std::vector<std::pair<uint16_t, uint32_t>> v;
  for (uint8_t i = 0; i < vec1.size(); i++) {
    auto p1 = vec1[i];
    auto p2 = vec2[i];
    if (p1.second == 0 || p2.second == 0) {
      uint16_t id = p1.first == 0xffff ? p2.first : p1.first;
      v.push_back({id, p1.second + p2.second});
    } else if (p1.first == p2.first) {
      v.push_back({p1.first, p1.second + p2.second});
    } else {
      v.push_back(p1);
      v.push_back(p2);
    }
  }
  while (v.size() > 7) {
    auto last = v.back();
    for (uint8_t i = 6; i >= 0; i--) {
      if (v[i].first == last.first) {
        v[i].second += last.second;
        v.pop_back();
        break;
      } else if (v[i].second == 0) {
        v[i] = last;
        v.pop_back();
        break;
      }
    }
  }
  return v;
}

static void heroIn(entt::entity heroEnt, entt::entity townEnt) {
  auto &registry = World::registrys[World::level];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  auto townComp = &registry.get<TownComp>(townEnt);
  auto heroComeIn = [&]() {
    registry.get<PositionComp>(heroEnt).z = INT32_MIN;
    heroComp->curEnt = townEnt;
    registry.get<PositionComp>(heroComp->flagEnt).z = INT32_MIN;
    for (auto i = 0; i < Global::heros[Global::playerId].size(); i++) {
      if (Global::heros[Global::playerId][i].second == heroEnt &&
          Global::heros[Global::playerId][i].first == World::level) {
        Global::heros[Global::playerId].erase(
            Global::heros[Global::playerId].begin() + i);
        break;
      }
    }
    townComp->heroEnt[0] = heroEnt;
    townComp->garCreatures.assign(7, {0xffff, 0});
    Global::herosIndex[Global::playerId] = 0xff;
    townComp->heroEnt[1] = std::nullopt;
    World::needSort = true;
  };
  if (townComp->garCreatures.empty()) {
    heroComeIn();
  } else {
    std::set<uint16_t> hCreatureSet;
    for (auto [type, count] : townComp->garCreatures) {
      if (count > 0) {
        hCreatureSet.insert(type);
      }
    }
    std::set<uint16_t> tCreatureSet;
    for (auto [type, count] : heroComp->creatures) {
      if (count > 0) {
        tCreatureSet.insert(type);
      }
    }
    std::set<uint16_t> aCreatureSet;
    aCreatureSet.insert(hCreatureSet.begin(), hCreatureSet.end());
    aCreatureSet.insert(tCreatureSet.begin(), tCreatureSet.end());
    if (aCreatureSet.size() <= 7) {
      auto creature =
          mergeCreatures(townComp->garCreatures, heroComp->creatures);
      heroComp->creatures = creature;
      heroComeIn();
    }
  }
}

static void heroOut(entt::entity heroEnt, entt::entity townEnt) {
  auto &registry = World::registrys[World::level];
  auto townComp = &registry.get<TownComp>(townEnt);
  townComp->heroEnt[0] = std::nullopt;
  townComp->heroEnt[1] = heroEnt;
  townComp->garCreatures.assign(7, {0xffff, 0});
  auto positionComp = &registry.get<PositionComp>(heroEnt);
  H3mObject object;
  object.printPriority = 0;
  object.id = (uint32_t)ObjectType::HERO;
  object.position[0] = registry.get<ObjectComp>(heroEnt).x;
  object.position[1] = registry.get<ObjectComp>(heroEnt).y;
  object.usedTiles = {{0x01, 0x07}};
  positionComp->z = Ent::loadZorder(0, object);
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  heroComp->curEnt = townEnt;
  registry.get<PositionComp>(heroComp->flagEnt).z = positionComp->z;
  Global::heros[Global::playerId].push_back({World::level, heroEnt});
  World::needSort = true;
}

static void heroSwap() {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto h0 = townComp->heroEnt[0].value();
  auto h1 = townComp->heroEnt[1].value();

  heroIn(h1, townEnt);
  heroOut(h0, townEnt);

  townComp->heroEnt[0] = h1;
  townComp->heroEnt[1] = h0;
}

static void clickCapitol(uint8_t clickType) { World::enterTownHall(); }

static void clickBlackSmith(uint8_t clickType) {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  if (townComp->heroEnt[1].has_value()) {
    auto heroEnt = townComp->heroEnt[1].value();
    auto goalEnt =
        townComp->buildings.at((uint8_t)TownCfg::Building::BLACKSMITH);
    World::enterWarMachineFac(heroEnt, goalEnt);
  } else {
    Global::confirmOnlyOK = true;
    Global::confirmCallBack = std::nullopt;
    auto confirmbakW = 400;
    auto confirmbakH = 140;
    Global::confirmdraw = [confirmbakW, confirmbakH]() {
      SDL_FPoint leftUp{Global::viewPort.w / 2 - confirmbakW / 2,
                        Global::viewPort.h / 2 - confirmbakH / 2};
      auto strPool = *Lang::strPool[Global::langIndex];
      FreeTypeSys::setSize(13);
      FreeTypeSys::setColor(240, 224, 104, 255);
      FreeTypeSys::drawCenter(leftUp.x + confirmbakW / 2, leftUp.y + 15,
                              strPool[1003]);
    };
    World::enterConfirm(confirmbakW, confirmbakH,
                        ((uint8_t)Enum::SCNTYPE::MOD));
  }
}

static void clickDwe(uint8_t clickType) {
  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto townComp = &registry.get<TownComp>(townEnt);
  auto buildId = mouseBuildId.value();
  if (clickType == (uint8_t)Enum::CLICKTYPE::L_UP) {
    entt::entity srcEnt;
    auto goalEnt = townComp->buildings[buildId];
    if (townComp->heroEnt[0].has_value()) {
      srcEnt = townComp->heroEnt[0].value();
    } else {
      srcEnt = townEnt;
    }
    World::enterDwe(srcEnt, goalEnt);
  } else {
  }
}

static void clickMageGuild(uint8_t clickType) {
  auto [level, townEnt] = Global::townScnPair;
  World::enterMageGuild(level, townEnt);
}

static bool clickBuild(uint8_t clickType) {
  if (mouseBuildId.has_value()) {
    // 说明点击到了建筑上
    auto buildId = mouseBuildId.value();
    auto [level, townEnt] = Global::townScnPair;
    auto &registry = World::registrys[level];
    auto townComp = &registry.get<TownComp>(townEnt);
    auto factionId = townComp->id;

    switch (buildId) {
    case (uint8_t)TownCfg::Building::SPECIAL_19: {
      switch (factionId) {
      case (uint8_t)TownCfg::Faction::CASTLE: {
        auto goalEnt = townComp->buildings[(uint8_t)TownCfg::Building::TAVERN];
        World::enterTavern(entt::null, goalEnt);
      }
      }
      break;
    }
    case (uint8_t)TownCfg::Building::CAPITOL: {
      clickCapitol(clickType);
      break;
    }
    case (uint8_t)TownCfg::Building::BLACKSMITH: {
      clickBlackSmith(clickType);
      break;
    }
    case (uint8_t)TownCfg::Building::DWELLING_LEVEL_1:
    case (uint8_t)TownCfg::Building::DWELLING_LEVEL_2:
    case (uint8_t)TownCfg::Building::DWELLING_LEVEL_3:
    case (uint8_t)TownCfg::Building::DWELLING_LEVEL_4:
    case (uint8_t)TownCfg::Building::DWELLING_LEVEL_5:
    case (uint8_t)TownCfg::Building::DWELLING_LEVEL_6:
    case (uint8_t)TownCfg::Building::DWELLING_LEVEL_7:
    case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_1:
    case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_2:
    case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_3:
    case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_4:
    case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_5:
    case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_6:
    case (uint8_t)TownCfg::Building::DWELLING_UPGRADE_LEVEL_7: {
      clickDwe(clickType);
      break;
    }
    case (uint8_t)TownCfg::Building::MAGE_GUILD_1:
    case (uint8_t)TownCfg::Building::MAGE_GUILD_2:
    case (uint8_t)TownCfg::Building::MAGE_GUILD_3:
    case (uint8_t)TownCfg::Building::MAGE_GUILD_4:
    case (uint8_t)TownCfg::Building::MAGE_GUILD_5: {
      clickMageGuild(clickType);
      break;
    }
    default: {
      break;
    }
    }
    return true;
  }
  return false;
}

static bool clickHeroCres(uint8_t clickType) {
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  SDL_FPoint point = {static_cast<float>(static_cast<int>(Window::mouseX)),
                      static_cast<float>(static_cast<int>(Window::mouseY))};

  // 检测点击位置
  uint8_t index = 0xFF;
  for (uint8_t i = 0; i < 2; i++) {
    for (uint8_t m = 0; m <= 7; m++) {
      SDL_FRect posRect = {leftUp.x + 242 + m * 62, leftUp.y + 387 + i * 96, 58,
                           64};
      if (SDL_PointInRectFloat(&point, &posRect)) {
        index = i * 8 + m;
        break;
      }
    }
    if (index != 0xFF)
      break;
  }

  if (index == 0xFF)
    return false;

  auto [i, m] = std::pair{index / 8, index % 8};
  auto [li, lm] = std::pair{Global::townScnIndex / 8, Global::townScnIndex % 8};

  auto [level, townEnt] = Global::townScnPair;
  auto &registry = World::registrys[level];
  auto *townComp = &registry.get<TownComp>(townEnt);

  // 右键点击处理
  if (!(clickType == (uint8_t)Enum::CLICKTYPE::L_UP)) {
    if (townComp->heroEnt[i].has_value()) {
      auto heroEnt = townComp->heroEnt[i].value();
      if (m == 0) {
        World::enterHeroScrn(level, heroEnt,
                             static_cast<uint8_t>(Enum::SCNTYPE::POP));
      } else {
        auto *heroComp = &registry.get<HeroComp>(heroEnt);
        World::enterCreature({level, heroEnt}, heroComp->creatures[m - 1],
                             static_cast<uint8_t>(Enum::CRETYPE::POP_HERO));
      }
    } else if (m >= 1 && i == 0) {
      World::enterCreature(townComp->garCreatures[m - 1],
                           static_cast<uint8_t>(Enum::CRETYPE::POP_DWE));
    }
    return true;
  }

  // 左键点击处理
  if (Global::townScnIndex != 0xFF) {
    // 获取第一次点击的目标
    struct FirstClickTarget {
      std::optional<entt::entity> hero;
      std::pair<uint16_t, uint32_t> *creature = nullptr;
    } firstClick;

    if (townComp->heroEnt[li].has_value()) {
      auto heroEnt = townComp->heroEnt[li].value();
      if (lm == 0) {
        firstClick.hero = heroEnt;
      } else {
        auto *heroComp = &registry.get<HeroComp>(heroEnt);
        firstClick.creature = &heroComp->creatures[lm - 1];
      }
    } else if (lm >= 1) {
      firstClick.creature = &townComp->garCreatures[lm - 1];
    }

    // 获取第二次点击的目标
    struct SecondClickTarget {
      std::optional<entt::entity> hero;
      std::pair<uint16_t, uint32_t> *creature = nullptr;
    } secondClick;

    if (townComp->heroEnt[i].has_value()) {
      auto heroEnt = townComp->heroEnt[i].value();
      if (m == 0) {
        secondClick.hero = heroEnt;
      } else {
        auto *heroComp = &registry.get<HeroComp>(heroEnt);
        secondClick.creature = &heroComp->creatures[m - 1];
      }
    } else if (m >= 1 && i == 0) {
      secondClick.creature = &townComp->garCreatures[m - 1];
    }

    // 处理不同的点击组合
    bool processed = false;

    // 双击英雄头像
    if (secondClick.hero && firstClick.hero &&
        secondClick.hero == firstClick.hero) {
      World::enterHeroScrn(level, *secondClick.hero,
                           static_cast<uint8_t>(Enum::SCNTYPE::MOD));
      processed = true;
    }
    // 英雄与空地交互
    else if (!secondClick.hero && firstClick.hero) {
      if (!secondClick.creature) {
        if (townComp->heroEnt[0].has_value()) {
          heroOut(*firstClick.hero, townEnt);
        } else {
          heroIn(*firstClick.hero, townEnt);
        }
        processed = true;
      } else if (secondClick.creature->second == 0) {
        processed = true;
      }
    }
    // 交换英雄
    else if (secondClick.hero && firstClick.hero) {
      heroSwap();
      processed = true;
    }
    // 双击生物
    else if (secondClick.creature && firstClick.creature && i == li &&
             m == lm) {
      if (!Global::splitOn) {
        if (townComp->heroEnt[i].has_value()) {
          auto heroEnt = townComp->heroEnt[i].value();
          World::enterCreature({level, heroEnt}, *secondClick.creature,
                               static_cast<uint8_t>(Enum::CRETYPE::MOD_HERO));
        } else {
          World::enterCreature(*secondClick.creature,
                               static_cast<uint8_t>(Enum::CRETYPE::MOD_HERO));
        }
      }
      Global::splitOn = false;
      processed = true;
    }
    // 交换/合并生物
    else if (secondClick.creature && firstClick.creature) {
      if (secondClick.creature->first == firstClick.creature->first) {
        if (Global::splitOn) {
          Global::splitCre[1] = secondClick.creature;
          World::enterSplitCre();
          Global::splitOn = false;
        } else {
          secondClick.creature->second += firstClick.creature->second;
          *firstClick.creature = {0xFF, 0};
        }

      } else {
        if (Global::splitOn) {
          Global::splitCre[1] = secondClick.creature;
          World::enterSplitCre();
        } else {
          std::swap(*secondClick.creature, *firstClick.creature);
        }
        Global::splitOn = false;
      }
      processed = true;
    }
    // 无效点击
    else if (!secondClick.hero) {
      processed = true;
    }

    if (processed) {
      index = 0xFF;
    }
  } else {
    // 首次点击验证
    if (townComp->heroEnt[i].has_value()) {
      auto heroEnt = townComp->heroEnt[i].value();
      auto *heroComp = &registry.get<HeroComp>(heroEnt);
      if (m != 0 && heroComp->creatures[m - 1].second == 0) {
        index = 0xFF;
      }
    } else if (i == 0 &&
               (m == 0 || townComp->garCreatures[m - 1].second == 0)) {
      index = 0xFF;
    } else if (i == 1) {
      index = 0xFF;
    }
  }
  Global::townScnIndex = index;
  return true;
}

bool TownSys::leftMouseUp(float x, float y) {
  if (Global::townScnType == (uint8_t)Enum::SCNTYPE::POP) {
    return false;
  }
  SDL_FPoint leftUp{(Global::viewPort.w - 800) / 2,
                    (Global::viewPort.h - 600) / 2};
  auto v = buttonInfo();
  auto clickType = (uint8_t)Enum::CLICKTYPE::L_UP;

  if (AdvMapSys::clickButtons(leftUp.x, leftUp.y, v, clickType)) {
    return false;
  }
  if (clickBuild(clickType)) {
    return false;
  }
  if (clickHeroCres(clickType)) {
    return false;
  }

  return true;
}

bool TownSys::rightMouseUp(float x, float y) {
  if (Global::townScnType == (uint8_t)Enum::SCNTYPE::POP) {
    World::iterateSystems.push_back([]() -> bool {
      World::exitScrn();
      return false;
    });
  }
  return false;
}

bool TownSys::rightMouseDown(float x, float y) {
  if (Global::townScnType == (uint8_t)Enum::SCNTYPE::POP) {
    return false;
  }
  auto clickType = (uint8_t)Enum::CLICKTYPE::R_DOWN;

  if (clickHeroCres(clickType)) {
    return false;
  }
  return true;
}

bool TownSys::keyUp(uint16_t key) {
  switch (key) {
  case SDL_SCANCODE_ESCAPE: {
    close();
    break;
  }
  default:
    break;
  }
  return true;
}