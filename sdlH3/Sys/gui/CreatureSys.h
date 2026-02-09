#pragma once

#include "entt/entity/fwd.hpp"
#include <cstdint>
struct CreatureSys {
  static bool run();
  static bool leftMouseUp(float x, float y);
  static bool rightMouseUp(float x, float y);
  static bool keyUp(uint16_t key);

  static int32_t heroCreMor(uint8_t level, entt::entity heroEnt, uint16_t creId,
                            uint8_t creType);
  static int32_t heroCreLuk(uint8_t level, entt::entity heroEnt, uint16_t creId,
                            uint8_t creType);

  static void showLukComfirm(uint8_t clickType);
  static void showMorComfirm(uint8_t clickType);

  static void creAnimate(uint64_t &creFrameTime, uint64_t &creFrameIndex,
                         uint64_t &creGroup,uint16_t creId);
};