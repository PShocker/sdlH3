#include "CursorSys.h"
#include "AdvMapSys.h"
#include "CameraSys.h"

#include "Comp/BoatComp.h"
#include "Comp/HeroComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TerrainComp.h"
#include "Ent/Ent.h"
#include "Enum/Enum.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SpellSys.h"
#include "Sys/HeroSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <algorithm>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <numbers>
#include <optional>
#include <queue>
#include <ranges>
#include <unordered_set>
#include <utility>
#include <vector>

const int windowEdge = 30;

static void drawMouseRect() {
  if (Window::mouseX > Global::viewPort.w - 199 ||
      Window::mouseY > Global::viewPort.h - 47) {
    return;
  }
  if (Global::cursorType == (uint8_t)Enum::CURSOR::ADVENTURE) {
    if (!Global::heroMove) {
      SDL_FPoint point = {Global::viewPort.x + Window::mouseX,
                          Global::viewPort.y + Window::mouseY};
      auto [x, y] = CursorSys::goalPoint(point);
      auto vX = x * 32 - Global::viewPort.x;
      auto vY = y * 32 - Global::viewPort.y;
      SDL_FRect posRect{(float)vX, vY, 32, 32};
      SDL_SetRenderDrawColor(Window::renderer, 240, 224, 104, 200); //
      SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);

      SDL_RenderRect(Window::renderer, &posRect);
    }
  }
}

static uint8_t spell(uint8_t index) {
  if (!(Window::mouseX + Global::viewPort.x < 0 ||
        Window::mouseY + Global::viewPort.y < 0 ||
        Window::mouseX + Global::viewPort.x >= Global::mapSize * 32 ||
        Window::mouseY + Global::viewPort.y >= Global::mapSize * 32)) {
    index = Global::cursorIndex;
    auto &registry = World::registrys[World::level];
    auto heroPair =
        Global::heros[Global::playerId][Global::herosIndex[Global::playerId]];
    auto heroEnt = heroPair.second;
    auto positionComp = &registry.get<PositionComp>(heroEnt);
    uint8_t heroX = (positionComp->point.x / 32.0) + 1;
    uint8_t heroY = (positionComp->point.y / 32.0) + 1;
    SDL_FPoint point = {Global::viewPort.x + Window::mouseX,
                        Global::viewPort.y + Window::mouseY};
    auto p = CursorSys::goalPoint(point);
    uint8_t goalX = p.x;
    uint8_t goalY = p.y;
    switch ((Enum::CRADVNTR)Global::cursorIndex) {
    case Enum::CRADVNTR::T1_SAIL: {
      SDL_FRect posRect = {positionComp->point.x + 32 - 1 * 32,
                           positionComp->point.y + 32 - 1 * 32, 96, 96};
      if (!SDL_PointInRectFloat(&point, &posRect)) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      goalX = std::clamp(goalX, (uint8_t)(heroX - 1), (uint8_t)(heroX + 1));
      goalY = std::clamp(goalY, (uint8_t)(heroY - 1), (uint8_t)(heroY + 1));
      auto [_, ent] = CursorSys::choose(false, goalX * 32 - Global::viewPort.x,
                                        goalY * 32 - Global::viewPort.y);
      if (ent != entt::null) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      auto goalPoint = goalX + goalY * Global::mapSize;
      if (!Global::waterBlock[World::level].contains(goalPoint)) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      break;
    }
    case Enum::CRADVNTR::SCUTTLE_BOAT: {
      SDL_FRect posRect = {positionComp->point.x + 32 - 1 * 32,
                           positionComp->point.y + 32 - 1 * 32, 96, 96};
      if (!SDL_PointInRectFloat(&point, &posRect)) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      goalX = std::clamp(goalX, (uint8_t)(heroX - 1), (uint8_t)(heroX + 1));
      goalY = std::clamp(goalY, (uint8_t)(heroY - 1), (uint8_t)(heroY + 1));
      auto [_, ent] = CursorSys::choose(false, goalX * 32 - Global::viewPort.x,
                                        goalY * 32 - Global::viewPort.y);
      if (!registry.all_of<BoatComp>(ent)) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      break;
    }
    case Enum::CRADVNTR::TELEPORT: {
      SDL_FRect posRect = {positionComp->point.x + 32 - 7 * 32,
                           positionComp->point.y + 32 - 7 * 32, 15 * 32,
                           15 * 32};
      if (!SDL_PointInRectFloat(&point, &posRect)) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      uint8_t minX = std::max((int16_t)heroX - 7, 0);
      uint8_t maxX = std::min((int16_t)heroX + 7, Global::mapSize);

      uint8_t minY = std::max((int16_t)heroY - 7, 0);
      uint8_t maxY = std::min((int16_t)heroY + 7, Global::mapSize);

      goalX = std::clamp(goalX, minX, maxX);
      goalY = std::clamp(goalY, minY, maxY);
      auto goalPoint = goalX + goalY * Global::mapSize;
      auto [_, ent] = CursorSys::choose(false, goalX * 32 - Global::viewPort.x,
                                        goalY * 32 - Global::viewPort.y);
      if (ent != entt::null) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      if (Global::rockBlock[World::level].contains(goalPoint) ||
          Global::waterBlock[World::level].contains(goalPoint)) {
        index = (uint8_t)Enum::CRADVNTR::POINTER;
        break;
      }
      break;
    }
    default:
      break;
    }
  }
  return index;
}

static bool cursorScrollUp() { return Window::mouseY <= windowEdge; }

static bool cursorScrollDown() {
  return Window::mouseY >= Global::viewPort.h - windowEdge;
}

static bool cursorScrollLeft() { return Window::mouseX <= windowEdge; }

static bool cursorScrollRight() {
  return Window::mouseX >= Global::viewPort.w - windowEdge;
}

static uint8_t scroll() {
  uint8_t index = (uint8_t)Enum::CRADVNTR::POINTER;
  if (Global::cursorType != (uint8_t)Enum::CURSOR::ADVENTURE) {
    return index;
  }
  // 判断是否在地图边缘
  if (cursorScrollLeft()) {
    index = (uint8_t)Enum::CRADVNTR::SCROLL_WEST;
    Global::viewPort.x -= 15;
  }
  if (cursorScrollUp()) {
    index = (uint8_t)Enum::CRADVNTR::SCROLL_NORTH;
    Global::viewPort.y -= 15;
  }
  if (cursorScrollRight()) {
    index = (uint8_t)Enum::CRADVNTR::SCROLL_EAST;
    Global::viewPort.x += 15;
  }
  if (cursorScrollDown()) {
    index = (uint8_t)Enum::CRADVNTR::SCROLL_SOUTH;
    Global::viewPort.y += 15;
  }
  if (cursorScrollLeft() && cursorScrollUp()) {
    return (uint8_t)Enum::CRADVNTR::SCROLL_NORTHWEST;
  }
  if (cursorScrollRight() && cursorScrollUp()) {
    return (uint8_t)Enum::CRADVNTR::SCROLL_NORTHEAST;
  }
  if (cursorScrollRight() && cursorScrollDown()) {
    return (uint8_t)Enum::CRADVNTR::SCROLL_SOUTHEAST;
  }
  if (cursorScrollLeft() && cursorScrollDown()) {
    return (uint8_t)Enum::CRADVNTR::SCROLL_SOUTHWEST;
  }
  CameraSys::fixViewPort();
  return index;
}

uint8_t CursorSys::astar(bool click) {
  if (Window::mouseX + Global::viewPort.x < 0 ||
      Window::mouseY + Global::viewPort.y < 0 ||
      Window::mouseX + Global::viewPort.x >= Global::mapSize * 32 ||
      Window::mouseY + Global::viewPort.y >= Global::mapSize * 32) {
    return (uint8_t)Enum::CRADVNTR::POINTER;
  }
  if (Global::herosIndex[Global::playerId] > 7 ||
      Global::heros[Global::playerId][Global::herosIndex[Global::playerId]]
              .first != World::level ||
      Window::mouseX > Global::viewPort.w - 199 ||
      Window::mouseY > Global::viewPort.h - 47) {
    // 在这里直接设置指针类型
    Global::cursorIndex = (uint8_t)Enum::CRADVNTR::POINTER;
    return (uint8_t)Enum::CRADVNTR::POINTER;
  }
  SDL_FPoint point = {Window::mouseX + Global::viewPort.x,
                      Window::mouseY + Global::viewPort.y};
  auto p = CursorSys::goalPoint(point);
  uint8_t goalX = p.x;
  uint8_t goalY = p.y;

  int32_t goalPoint = goalX + goalY * Global::mapSize;

  uint8_t index = (uint8_t)Enum::CRADVNTR::POINTER;
  auto &registry = World::registrys[World::level];
  auto heroPair =
      Global::heros[Global::playerId][Global::herosIndex[Global::playerId]];
  auto heroEnt = heroPair.second;
  if (registry.get<ObjectComp>(heroEnt).x - 1 == goalX &&
      registry.get<ObjectComp>(heroEnt).y == goalY) {
    return (uint8_t)Enum::CRADVNTR::POINTER;
  }
  std::optional<entt::entity> goalEnt;
  ObjectComp *goalObjectComp = nullptr;

  std::unordered_set<int32_t> block;
  block.insert(Global::rockBlock[World::level].begin(),
               Global::rockBlock[World::level].end());

  auto heroComp = &registry.get<HeroComp>(heroEnt);
  if (heroComp->moveType == HeroComp::HORSE) {
    block.insert(Global::waterBlock[World::level].begin(),
                 Global::waterBlock[World::level].end());
    for (auto ent : registry.view<BoatComp>()) {
      auto objectComp = &registry.get<ObjectComp>(ent);
      block.erase(objectComp->x - 1 + objectComp->y * Global::mapSize);
    }
  } else if (heroComp->moveType == HeroComp::BOAT) {
    // Boat
    block.insert(Global::landBlock[World::level].begin(),
                 Global::landBlock[World::level].end());
    for (auto ent : registry.view<BoatComp>()) {
      auto objectComp = &registry.get<ObjectComp>(ent);
      block.insert(objectComp->x - 1 + objectComp->y * Global::mapSize);
    }
    if (Global::coastalBlock[World::level].contains(goalPoint)) {
      block.erase(goalPoint);
      goalEnt = Global::terrains[World::level][goalX][goalY].back();
    }
  } else {
    // WaterWalk or Fly
    if (Global::waterBlock[World::level].contains(goalPoint)) {
      bool boat = false;
      for (auto ent : registry.view<BoatComp>()) {
        auto objectComp = &registry.get<ObjectComp>(ent);
        if (objectComp->x - 1 == goalX && objectComp->y == goalY) {
          boat = true;
          break;
        }
      }
      if (!boat) {
        return (uint8_t)Enum::CRADVNTR::POINTER;
      }
    }
  }
  auto bakBlock = block;
  for (auto ent : registry.view<ObjectComp>()) {
    if (registry.get<PositionComp>(ent).z == INT32_MIN) {
      continue;
    }
    auto objectComp = &registry.get<ObjectComp>(ent);
    for (auto i : objectComp->blockTiles) {
      auto x = objectComp->x + i.first;
      auto y = objectComp->y + i.second;
      block.insert(x + y * Global::mapSize);
    }
  }
  if (block.contains(goalPoint)) {
    Global::cursorIndex = (uint8_t)Enum::CRADVNTR::POINTER;
    return (uint8_t)Enum::CRADVNTR::POINTER;
  }
  for (auto ent : registry.view<ObjectComp>(entt::exclude<HeroComp>)) {
    if (registry.get<PositionComp>(ent).z == INT32_MIN) {
      continue;
    }
    auto objectComp = &registry.get<ObjectComp>(ent);
    if (objectComp->type != (int16_t)ObjectType::MONSTER) {
      for (auto i : objectComp->accessTiles) {
        auto x = objectComp->x + i.first;
        auto y = objectComp->y + i.second;
        if (goalX == x && goalY == y) {
          goalEnt = ent;
          goalObjectComp = objectComp;
        } else {
          block.insert(x + y * Global::mapSize);
        }
      }
    }
  }
  for (auto ent : registry.view<HeroComp, ObjectComp, PositionComp>()) {
    if (registry.get<PositionComp>(ent).z == INT32_MIN) {
      continue;
    }
    auto objectComp = &registry.get<ObjectComp>(ent);
    for (auto i : objectComp->accessTiles) {
      auto x = objectComp->x + i.first;
      auto y = objectComp->y + i.second;
      if (goalX == x && goalY == y) {
        goalEnt = ent;
        goalObjectComp = objectComp;
      } else {
        block.insert(x + y * Global::mapSize);
      }
    }
  }
  for (auto ent : registry.view<ObjectComp>()) {
    if (registry.get<PositionComp>(ent).z == INT32_MIN) {
      continue;
    }
    auto objectComp = &registry.get<ObjectComp>(ent);
    if (objectComp->type == (int16_t)ObjectType::MONSTER) {
      if (goalX == objectComp->x && goalY == objectComp->y) {
        goalEnt = ent;
        goalObjectComp = objectComp;
      } else {
        for (auto i : objectComp->accessTiles) {
          auto x = objectComp->x + i.first;
          auto y = objectComp->y + i.second;
          if (goalX == x && goalY == y) {
            if (goalObjectComp == nullptr) {
              goalEnt = ent;
              goalObjectComp = objectComp;
              continue;
            }
          } else {
            block.insert(x + y * Global::mapSize);
          }
        }
      }
    }
  }

  // 方向数组
  const std::vector<SDL_Point> directions = {{-1, -1}, {0, -1}, {1, -1}, //
                                             {-1, 0},  {1, 0},           //
                                             {-1, 1},  {0, 1},  {1, 1}}; //
  if (heroComp->moveType == HeroComp::FLY) {
    std::swap(block, bakBlock);
  }

  uint8_t heroX = registry.get<PositionComp>(heroEnt).point.x / 32 + 1;
  uint8_t heroY = registry.get<PositionComp>(heroEnt).point.y / 32 + 1;

  const auto findPath = [heroX, heroY, directions, heroComp,
                         goalEnt](uint8_t x, uint8_t y,
                                  std::unordered_set<int32_t> block) {
    // 记录路径来源和移动力消耗
    std::unordered_map<int32_t, int32_t> cameFrom;
    std::unordered_map<int32_t, int32_t> costSoFar;
    const auto cmp = [](const std::pair<SDL_Point, int32_t> &a,
                        const std::pair<SDL_Point, int32_t> &b) {
      return a.second > b.second;
    };

    std::priority_queue<std::pair<SDL_Point, int>,
                        std::vector<std::pair<SDL_Point, int>>, decltype(cmp)>
        pq(cmp);
    pq.emplace(SDL_Point{heroX, heroY}, INT32_MAX);
    cameFrom[heroX + heroY * Global::mapSize] = INT32_MAX;
    costSoFar[heroX + heroY * Global::mapSize] = 0;

    while (!pq.empty()) {
      auto [current, _] = pq.top();
      pq.pop();

      if (current.x == x && current.y == y) {
        break;
      }
      auto dirs = directions;
      if (heroComp->moveType == HeroComp::BOAT &&
          !(std::abs(x - current.x) <= 1 && std::abs(y - current.y) <= 1 &&
            goalEnt == Global::terrains[World::level][x][y].back())) {
        auto currentPoint = current.x + current.y * Global::mapSize;
        std::bitset<4> d;
        //   1
        // 0   2
        //   3
        if (Global::coastalBlock[World::level].contains(currentPoint - 1)) {
          d[0] = true;
        }
        if (Global::coastalBlock[World::level].contains(currentPoint -
                                                        Global::mapSize)) {
          d[1] = true;
        }
        if (Global::coastalBlock[World::level].contains(currentPoint + 1)) {
          d[2] = true;
        }
        if (Global::coastalBlock[World::level].contains(currentPoint +
                                                        Global::mapSize)) {
          d[3] = true;
        }
        const std::vector<SDL_Point> dirBitmaps[16] = {
            // 0: 0000 (无遮挡)
            directions,
            // 1: 0001 (左遮挡)
            {{0, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1}, {1, 1}},
            // 2: 0010 (上遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}},
            // 3: 0011 (左+上遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}, {1, 1}},
            // 4: 0100 (右遮挡)
            {{-1, -1}, {0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}},
            // 5: 0101 (左+右遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 6: 0110 (上+右遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}},
            // 7: 0111 (左+上+右遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 8: 1000 (下遮挡)
            {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 9: 1001 (左+下遮挡)
            {{0, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 10: 1010 (上+下遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 11: 1011 (左+上+下遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 12: 1100 (右+下遮挡)
            {{-1, -1}, {0, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 13: 1101 (左+右+下遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 14: 1110 (上+右+下遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}},
            // 15: 1111 (左+上+右+下遮挡)
            {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}};
        dirs = dirBitmaps[d.to_ulong()];
      }
      // 检查相邻格子
      for (const auto &dir : dirs) {
        auto m = current.x + dir.x;
        auto n = current.y + dir.y;
        auto currentIndex = current.x + current.y * Global::mapSize;
        auto nextIndex = m + n * Global::mapSize;
        // 检查边界和可通行性
        if ((m < 0 || n < 0) ||
            (m >= Global::mapSize || n >= Global::mapSize) ||
            block.contains(nextIndex) ||
            !Global::fogs[Global::playerId][World::level][nextIndex]) {
          continue;
        }
        auto newCost = costSoFar[currentIndex];
        if (!costSoFar.contains(nextIndex) || newCost < costSoFar[nextIndex]) {
          costSoFar[nextIndex] = newCost;
          int32_t priority = newCost + (std::abs(x - m) + std::abs(y - n));
          pq.emplace(SDL_Point{m, n}, priority);
          cameFrom[nextIndex] = currentIndex;
        }
      }
    }
    return cameFrom;
  };
  uint32_t fullMoveCost = 0;
  auto cameFrom = findPath(goalX, goalY, block);
  auto bakGoalPoint = goalPoint;
  bool flyAccess = false;
  if (heroComp->moveType == HeroComp::FLY) {
    if (cameFrom.contains(goalPoint)) {
      if (goalObjectComp &&
          ((ObjectType)goalObjectComp->type == ObjectType::MONSTER ||
           (ObjectType)goalObjectComp->type == ObjectType::HERO ||
           (ObjectType)goalObjectComp->type == ObjectType::RESOURCE ||
           (ObjectType)goalObjectComp->type == ObjectType::ARTIFACT ||
           (ObjectType)goalObjectComp->type == ObjectType::TREASURE_CHEST)) {
        auto lastSecondPoint = cameFrom[goalPoint];
        if (bakBlock.contains(lastSecondPoint) &&
            cameFrom[lastSecondPoint] != INT32_MAX) {
          int32_t dis = INT32_MAX;
          for (auto dir : directions) {
            auto x = goalObjectComp->x + goalObjectComp->accessTiles[0].first +
                     dir.x;
            auto y = goalObjectComp->y + goalObjectComp->accessTiles[0].second +
                     dir.y;
            auto point = x + y * Global::mapSize;
            if (!bakBlock.contains(point)) {
              auto dx = x - heroX;
              auto dy = y - heroY;
              auto d = dx * dx + dy * dy;
              if (d < dis) {
                dis = d;
                goalX = x;
                goalY = y;
                goalPoint = point;
                cameFrom = findPath(goalX, goalY, block);
                flyAccess = true;
              }
            }
          }
          if (dis == INT32_MAX) {
            return (uint8_t)Enum::CRADVNTR::POINTER;
          }
        }
      }
    }
  }
  if (cameFrom.contains(goalPoint)) {
    //
    std::vector<SDL_Point> path;
    while (true) {
      path.push_back(
          {goalPoint % Global::mapSize, goalPoint / Global::mapSize});
      goalPoint = cameFrom[goalPoint];
      if (goalPoint == INT32_MAX) {
        break;
      }
    }
    std::reverse(path.begin(), path.end());
    if (flyAccess) {
      goalX = bakGoalPoint % Global::mapSize;
      goalY = bakGoalPoint / Global::mapSize;
      path.push_back({goalX, goalY});
    }
    uint16_t indexCost = UINT16_MAX;
    for (uint16_t i = 0; i < path.size() - 1; i++) {
      auto current = path[i];
      auto next = path[i + 1];
      auto terrainEnt =
          Global::terrains[World::level][current.x][current.y].back();
      auto moveCost = TerrainCfg::moveCost.at(
          World::registrys[World::level].get<TerrainComp>(terrainEnt).index);
      if (std::abs(next.x - current.x) + std::abs(next.y - current.y) == 2) {
        moveCost *= std::numbers::sqrt2;
      }
      fullMoveCost += moveCost;
      if (indexCost == UINT16_MAX && heroComp->movement > 0 &&
          fullMoveCost >= heroComp->movement) {
        indexCost = i;
      }
    }
    auto day = fullMoveCost / heroComp->movement;
    day = day > 3 ? 3 : day;
    index = heroComp->moveType != (HeroComp::BOAT)
                ? (uint8_t)Enum::CRADVNTR::T1_VISIT + day * 6
                : (uint8_t)Enum::CRADVNTR::T1_SAIL + day * 6;
    if (goalEnt.has_value()) {
      if (goalObjectComp == nullptr) {
        index = (uint8_t)Enum::CRADVNTR::T1_DISEMBARK + day * 6;
      } else {
        switch ((ObjectType)goalObjectComp->type) {
        case ObjectType::MONSTER: {
          index = (uint8_t)Enum::CRADVNTR::T1_ATTACK + day * 6;
          break;
        }
        case ObjectType::HERO: {
          if (goalEnt == heroEnt) {
            index = (uint8_t)Enum::CRADVNTR::POINTER;
          } else if (Global::playerId ==
                     registry.get<PlayerIdComp>(goalEnt.value()).id) {
            index = (uint8_t)Enum::CRADVNTR::T1_EXCHANGE + day * 6;
          } else {
            index = (uint8_t)Enum::CRADVNTR::T1_ATTACK + day * 6;
          }
          break;
        }
        case ObjectType::BOAT: {
          index = (uint8_t)Enum::CRADVNTR::T1_SAIL + day * 6;
          break;
        }
        default:
          break;
        }
      }
    } else if (heroComp->moveType == HeroComp::HORSE) {
      index = (uint8_t)Enum::CRADVNTR::T1_MOVE + day * 6;
    }
    // 点击
    if (click) {
      // 检查现有路径是否已到达目标
      if (!heroComp->pathEnts.empty()) {
        auto lastPathEnt =
            heroComp->pathEnts.back(); // 使用back()获取最后一个元素
        if (auto pathPoint = &registry.get<PositionComp>(lastPathEnt)) {
          if (pathPoint->point.x == goalX * 32 &&
              pathPoint->point.y == goalY * 32) {
            heroComp->move = true;
            heroComp->goalEnt = goalEnt;
            Global::heroMove = true;
            Global::cursorIndex = index;
            return index;
          }
        }
      }
      // 清理现有路径
      for (auto &pathEnt : heroComp->pathEnts) {
        registry.destroy(pathEnt);
      }
      World::needSort = true;
      heroComp->pathEnts.clear();
      // 加载新路径
      Ent::loadPath(path, heroPair.second, indexCost);
      heroComp->goalEnt = goalEnt;
    }
  }
  return index;
}

std::pair<uint8_t, entt::entity> CursorSys::choose(bool click, float x,
                                                   float y) {
  entt::entity goalEnt = entt::null;
  if (x > Global::viewPort.w - 199 || y > Global::viewPort.h - 47) {
    return {(uint8_t)Enum::CRADVNTR::POINTER, goalEnt};
  }
  if (x + Global::viewPort.x < 0 || y + Global::viewPort.y < 0 ||
      x + Global::viewPort.x >= Global::mapSize * 32 ||
      y + Global::viewPort.y >= Global::mapSize * 32) {
    return {(uint8_t)Enum::CRADVNTR::POINTER, goalEnt};
  }
  SDL_FPoint point = {x + Global::viewPort.x, y + Global::viewPort.y};
  auto p = CursorSys::goalPoint(point);
  uint8_t goalX = p.x;
  uint8_t goalY = p.y;

  auto &fogs = Global::fogs[Global::playerId][World::level];
  auto nextIndex = goalX + goalY * Global::mapSize;

  if (!fogs[nextIndex]) {
    return {(uint8_t)Enum::CRADVNTR::POINTER, goalEnt};
  }

  uint8_t index = (uint8_t)Enum::CRADVNTR::POINTER;
  auto &registry = World::registrys[World::level];
  for (auto ent : registry.view<ObjectComp>()) {
    auto positionComp = registry.get<PositionComp>(ent);
    if (positionComp.z == INT32_MIN) {
      continue;
    }
    auto objectComp = registry.get<ObjectComp>(ent);
    if (objectComp.type == (uint8_t)ObjectType::MONSTER) {
      objectComp.blockTiles.clear();
      objectComp.accessTiles = {{0, 0}};
    }
    for (const auto &vec : {objectComp.blockTiles, objectComp.accessTiles}) {
      if (index == (uint8_t)Enum::CRADVNTR::HERO) {
        break;
      }
      for (const auto &i : vec) {
        auto x = objectComp.x + i.first;
        auto y = objectComp.y + i.second;
        if (x == goalX && y == goalY) {
          goalEnt = ent;
          switch ((ObjectType)objectComp.type) {
          case ObjectType::HERO: {
            index = (uint8_t)Enum::CRADVNTR::HERO;
            if (click) {
              auto heroComp = &registry.get<HeroComp>(ent);
              auto &heros = Global::heros[Global::playerId];
              if (heros[Global::herosIndex[Global::playerId]].second == ent ||
                  Global::herosIndex[Global::playerId] ==
                      8 + heroComp->portrait) {
                CursorSys::clearHeroPath();
                auto positionComp = &registry.get<PositionComp>(ent);
                CameraSys::focus(positionComp->point.x + 48,
                                 positionComp->point.y + 48);
                World::enterHeroScrn(World::level, ent,
                                     (uint8_t)Enum::SCNTYPE::MOD);
                return {index, goalEnt};
              }
              auto playerIdComp = &registry.get<PlayerIdComp>(ent);
              if (playerIdComp->id == Global::playerId) {
                CursorSys::clearHeroPath();
                AdvMapSys::heroFocus(ent, World::level);
              } else {
                Global::herosIndex[Global::playerId] = 8 + heroComp->portrait;
              }
            }
            break;
          }
          case ObjectType::TOWN: {
            auto playerIdComp = &registry.get<PlayerIdComp>(ent);
            if (playerIdComp->id == Global::playerId) {
              index = (uint8_t)Enum::CRADVNTR::TOWN;
            }
            if (click) {
              auto &towns = Global::towns[Global::playerId];
              if (Global::townsIndex[Global::playerId] != 0xffff &&
                  towns[Global::townsIndex[Global::playerId]].second == ent) {
                World::enterTownScrn(World::level, ent,
                                     (uint8_t)Enum::SCNTYPE::MOD);
              } else {
                AdvMapSys::townFocus(ent, World::level);
              }
            }
            break;
          }
          default:
            break;
          }
        }
      }
    }
  }
  return {index, goalEnt};
}

bool CursorSys::run() {
  auto textures = Global::defCache["CRADVNTR.def/0"];
  uint8_t index = (uint8_t)Enum::CRADVNTR::POINTER;
  auto texture = textures[(uint8_t)Enum::CRADVNTR::POINTER];
  switch ((Enum::CURSOR)Global::cursorType) {
  case Enum::CURSOR::ADVENTURE: {
    if (Global::heroMove) {
      texture = textures[Global::cursorIndex];
      break;
    }
    if (index = scroll(); index != (uint8_t)Enum::CRADVNTR::POINTER) {
      texture = textures[index];
      break;
    }
    if (index = astar(false); index != (uint8_t)Enum::CRADVNTR::POINTER) {
      texture = textures[index];
      break;
    }
    if (index = choose(false, Window::mouseX, Window::mouseY).first;
        index != (uint8_t)Enum::CRADVNTR::POINTER) {
      texture = textures[index];
      break;
    }
    // 判断
    break;
  }
  case Enum::CURSOR::DEFAULT: {
    texture = textures[(uint8_t)Enum::CRADVNTR::POINTER];
    break;
  }
  case Enum::CURSOR::SPELL: {
    index = spell(index);
    texture = textures[index];
    break;
  }
  case Enum::CURSOR::FADE: {
    index = astar(false);
    texture = textures[index];
    break;
  }
  case Enum::CURSOR::HIDE: {
    return true;
  }
  default:
    break;
  }
  SDL_FRect posRect{(float)Window::mouseX, (float)Window::mouseY,
                    (float)texture->w, (float)texture->h};
  SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
  // drawMouseRect();
  return true;
}

static bool heroStop = false;

bool CursorSys::leftMouseUp(float x, float y) {
  switch (Global::cursorType) {
  case (uint8_t)Enum::CURSOR::SPELL: {
    if (x + Global::viewPort.x < 0 || y + Global::viewPort.y < 0 ||
        x + Global::viewPort.x >= Global::mapSize * 32 ||
        y + Global::viewPort.y >= Global::mapSize * 32) {
      return true;
    }
    auto &registry = World::registrys[World::level];
    auto heroPair =
        Global::heros[Global::playerId][Global::herosIndex[Global::playerId]];
    auto heroEnt = heroPair.second;
    auto positionComp = &registry.get<PositionComp>(heroEnt);
    uint8_t heroX = (positionComp->point.x / 32.0) + 1;
    uint8_t heroY = (positionComp->point.y / 32.0) + 1;
    SDL_FPoint point = {Global::viewPort.x + x, Global::viewPort.y + y};
    auto p = CursorSys::goalPoint(point);
    uint8_t goalX = p.x;
    uint8_t goalY = p.y;
    switch ((Enum::CRADVNTR)Global::cursorIndex) {
    case Enum::CRADVNTR::T1_SAIL: {
      SDL_FRect posRect = {positionComp->point.x + 32 - 1 * 32,
                           positionComp->point.y + 32 - 1 * 32, 96, 96};
      if (SDL_PointInRectFloat(&point, &posRect)) {
        goalX = std::clamp(goalX, (uint8_t)(heroX - 1), (uint8_t)(heroX + 1));
        goalY = std::clamp(goalY, (uint8_t)(heroY - 1), (uint8_t)(heroY + 1));
        auto goalPoint = goalX + goalY * Global::mapSize;
        if (!Global::waterBlock[World::level].contains(goalPoint)) {
          break;
        }
        auto [_, ent] =
            CursorSys::choose(false, goalX * 32 - Global::viewPort.x,
                              goalY * 32 - Global::viewPort.y);
        if (ent != entt::null) {
          break;
        }
        auto heroComp = &registry.get<HeroComp>(heroEnt);
        auto skillLevel = SpellSys::heroSplLevel(heroComp, 8).second;
        auto manaCost = SpellCfg::SpellCost.at(0).at(skillLevel);
        heroComp->mana -= manaCost;
        World::iterateSystemsBak.push_back(World::iterateSystems);
        World::iterateSystems.pop_back();
        World::iterateSystems.push_back([heroEnt, goalX, goalY]() {
          Ent::loadBoat("AB01_", goalX + 1, goalY, World::level, 2, 0);
          Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
          clearHeroPath();
          return true;
        });
        Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                            Global::viewPort.h - 47};
        World::iterateSystems.push_back(World::enterFadeScrn);
      }
      break;
    }
    case Enum::CRADVNTR::SCUTTLE_BOAT: {
      auto [_, ent] = CursorSys::choose(false, x, y);
      SDL_FRect posRect = {positionComp->point.x + 32 - 1 * 32,
                           positionComp->point.y + 32 - 1 * 32, 96, 96};
      if (SDL_PointInRectFloat(&point, &posRect)) {
        goalX = std::clamp(goalX, (uint8_t)(heroX - 1), (uint8_t)(heroX + 1));
        goalY = std::clamp(goalY, (uint8_t)(heroY - 1), (uint8_t)(heroY + 1));
        auto [_, ent] =
            CursorSys::choose(false, goalX * 32 - Global::viewPort.x,
                              goalY * 32 - Global::viewPort.y);
        if (!registry.all_of<BoatComp>(ent)) {
          break;
        }
        auto heroComp = &registry.get<HeroComp>(heroEnt);
        auto skillLevel = SpellSys::heroSplLevel(heroComp, 8).second;
        auto manaCost = SpellCfg::SpellCost.at(1).at(skillLevel);
        heroComp->mana -= manaCost;
        World::iterateSystemsBak.push_back(World::iterateSystems);
        World::iterateSystems.pop_back();
        World::iterateSystems.push_back([heroEnt, &registry, ent]() {
          registry.destroy(ent);
          World::needSort = true;
          Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
          clearHeroPath();
          return true;
        });
        Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                            Global::viewPort.h - 47};
        World::iterateSystems.push_back(World::enterFadeScrn);
      }
      break;
    }
    case Enum::CRADVNTR::TELEPORT: {
      SDL_FRect posRect = {positionComp->point.x + 32 - 7 * 32,
                           positionComp->point.y + 32 - 7 * 32, 15 * 32,
                           15 * 32};
      if (SDL_PointInRectFloat(&point, &posRect)) {
        uint8_t minX = std::max((int16_t)heroX - 7, 0);
        uint8_t maxX = std::min((int16_t)heroX + 7, Global::mapSize);

        uint8_t minY = std::max((int16_t)heroY - 7, 0);
        uint8_t maxY = std::min((int16_t)heroY + 7, Global::mapSize);

        goalX = std::clamp(goalX, minX, maxX);
        goalY = std::clamp(goalY, minY, maxY);
        auto goalPoint = goalX + goalY * Global::mapSize;
        if (Global::rockBlock[World::level].contains(goalPoint) ||
            Global::waterBlock[World::level].contains(goalPoint)) {
          break;
        }
        auto [_, ent] =
            CursorSys::choose(false, goalX * 32 - Global::viewPort.x,
                              goalY * 32 - Global::viewPort.y);
        if (ent != entt::null) {
          break;
        }
        auto heroComp = &registry.get<HeroComp>(heroEnt);
        auto skillLevel = SpellSys::heroSplLevel(heroComp, 8).second;
        auto manaCost = SpellCfg::SpellCost.at(8).at(skillLevel);
        heroComp->mana -= manaCost;
        World::iterateSystemsBak.push_back(World::iterateSystems);
        World::iterateSystems.pop_back();
        World::iterateSystems.push_back([heroEnt, goalX, goalY]() {
          HeroSys::heroTelePort(heroEnt, goalX, goalY);
          CameraSys::focus(goalX * 32 + 16, goalY * 32 + 16);
          Global::cursorType = (uint8_t)Enum::CURSOR::ADVENTURE;
          clearHeroPath();
          return true;
        });
        Global::fadeRect = {0, 0, Global::viewPort.w - 199,
                            Global::viewPort.h - 47};
        World::iterateSystems.push_back(World::enterFadeScrn);
      }
      break;
    }
    default:
      break;
    }
    return false;
  }
  case (uint8_t)Enum::CURSOR::ADVENTURE: {
    if (heroStop) {
      heroStop = false;
      return false;
    }
    if (auto index = astar(true); index != (uint8_t)Enum::CRADVNTR::POINTER) {
      return false;
    }
    if (auto index = choose(true, x, y).first;
        index != (uint8_t)Enum::CRADVNTR::POINTER) {
      return false;
    }
    break;
  }
  }
  return true;
}

void CursorSys::clearHeroPath() {
  auto heroIndex = Global::herosIndex[Global::playerId];
  if (heroIndex >= 8) {
    return;
  }
  auto heroPair = Global::heros[Global::playerId][heroIndex];
  auto heroEnt = heroPair.second;
  auto &registry = World::registrys[heroPair.first];
  auto heroComp = &registry.get<HeroComp>(heroEnt);
  if (heroComp->move && heroComp->pathEntsBack.empty()) {
    if (heroComp->pathEnts.size() > 1) {
      std::unordered_set<int32_t> block;
      block.insert(Global::rockBlock[World::level].begin(),
                   Global::rockBlock[World::level].end());
      if (heroComp->moveType != HeroComp::BOAT) {
        block.insert(Global::waterBlock[World::level].begin(),
                     Global::waterBlock[World::level].end());
      }
      for (auto ent : registry.view<ObjectComp>()) {
        if (registry.get<PositionComp>(ent).z == INT32_MIN) {
          continue;
        }
        auto objectComp = &registry.get<ObjectComp>(ent);
        for (auto vec : {objectComp->blockTiles, objectComp->accessTiles}) {
          for (auto i : vec) {
            auto x = objectComp->x + i.first;
            auto y = objectComp->y + i.second;
            block.insert(x + y * Global::mapSize);
          }
        }
      }
      for (int i = 0; i < heroComp->pathEnts.size(); i++) {
        auto pathEnt = heroComp->pathEnts[i];
        auto positionComp = &registry.get<PositionComp>(pathEnt);
        int x = positionComp->point.x / 32;
        int y = positionComp->point.y / 32;
        if (!block.contains(x + y * Global::mapSize)) {
          heroComp->pathEntsBack = std::vector<entt::entity>{
              heroComp->pathEnts.begin(), heroComp->pathEnts.begin() + i + 1};
          heroComp->pathEnts.erase(heroComp->pathEnts.begin(),
                                   heroComp->pathEnts.begin() + i + 1);
          std::swap(heroComp->pathEntsBack, heroComp->pathEnts);
          heroComp->goalEnt = std::nullopt;
          break;
        }
      }
    }
  } else if (heroComp->move == false && !Global::heroMove) {
    for (auto pathEnt : heroComp->pathEnts) {
      registry.destroy(pathEnt);
    }
    World::needSort = true;
    heroComp->pathEnts.clear();
  }
}

bool CursorSys::leftMouseDown(float x, float y) {
  if (Window::mouseX > Global::viewPort.w - 199 ||
      Window::mouseY > Global::viewPort.h - 47) {
    return true;
  }
  if (Window::mouseX + Global::viewPort.x < 0 ||
      Window::mouseY + Global::viewPort.y < 0 ||
      Window::mouseX + Global::viewPort.x >= Global::mapSize * 32 ||
      Window::mouseY + Global::viewPort.y >= Global::mapSize * 32) {
    return true;
  }

  if (Global::heroMove) {
    heroStop = true;
    CursorSys::clearHeroPath();
    return false;
  }
  return true;
}

bool CursorSys::rightMouseUp(float x, float y) { return true; }

bool CursorSys::rightMouseDown(float x, float y) {
  if (Global::cursorType == (uint8_t)Enum::CURSOR::ADVENTURE) {
    if (Window::mouseX > Global::viewPort.w - 199 ||
        Window::mouseY > Global::viewPort.h - 47) {
      return true;
    }
    if (Window::mouseX + Global::viewPort.x < 0 ||
        Window::mouseY + Global::viewPort.y < 0 ||
        Window::mouseX + Global::viewPort.x >= Global::mapSize * 32 ||
        Window::mouseY + Global::viewPort.y >= Global::mapSize * 32) {
      return true;
    }

    if (Global::heroMove) {
      CursorSys::clearHeroPath();
      return false;
    }
    World::enterAdvPop();
    return true;
  }
  return false;
}

SDL_Point CursorSys::goalPoint(SDL_FPoint point) {
  SDL_Point p;
  switch ((Enum::CRADVNTR)Global::cursorIndex) {
  case Enum::CRADVNTR::POINTER: {
    p.x = point.x / 32.0;
    p.y = point.y / 32.0;
    break;
  }
  default: {
    p.x = std::round((point.x) / 32.0);
    p.y = std::round((point.y) / 32.0);
    break;
  }
  }
  p.x = std::clamp((uint8_t)p.x, (uint8_t)0, (uint8_t)(Global::mapSize - 1));
  p.y = std::clamp((uint8_t)p.y, (uint8_t)0, (uint8_t)(Global::mapSize - 1));
  return p;
}