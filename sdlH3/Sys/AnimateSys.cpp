#include "AnimateSys.h"
#include "Comp/TextureComp.h"
#include "Global/Global.h"
#include "Window/Window.h"
#include "World/World.h"
#include <cstdint>
#include <string>
#include <unordered_map>

static const std::unordered_map<std::string, uint8_t> delayMap = {
    {"AH00_.def/5", 60}, {"AH00_.def/6", 60}, {"AH00_.def/7", 60},
    {"AH00_.def/8", 60}, {"AH00_.def/9", 60}, {"AH01_.def/5", 60},
    {"AH01_.def/6", 60}, {"AH01_.def/7", 60}, {"AH01_.def/8", 60},
    {"AH01_.def/9", 60}, {"AH02_.def/5", 60}, {"AH02_.def/6", 60},
    {"AH02_.def/7", 60}, {"AH02_.def/8", 60}, {"AH02_.def/9", 60},
    {"AH03_.def/5", 60}, {"AH03_.def/6", 60}, {"AH03_.def/7", 60},
    {"AH03_.def/8", 60}, {"AH03_.def/9", 60}, {"AH04_.def/5", 60},
    {"AH04_.def/6", 60}, {"AH04_.def/7", 60}, {"AH04_.def/8", 60},
    {"AH04_.def/9", 60}, {"AH05_.def/5", 60}, {"AH05_.def/6", 60},
    {"AH05_.def/7", 60}, {"AH05_.def/8", 60}, {"AH05_.def/9", 60},
    {"AH06_.def/5", 60}, {"AH06_.def/6", 60}, {"AH06_.def/7", 60},
    {"AH06_.def/8", 60}, {"AH06_.def/9", 60}, {"AH07_.def/5", 60},
    {"AH07_.def/6", 60}, {"AH07_.def/7", 60}, {"AH07_.def/8", 60},
    {"AH07_.def/9", 60}, {"AH08_.def/5", 60}, {"AH08_.def/6", 60},
    {"AH08_.def/7", 60}, {"AH08_.def/8", 60}, {"AH08_.def/9", 60},
    {"AH09_.def/5", 60}, {"AH09_.def/6", 60}, {"AH09_.def/7", 60},
    {"AH09_.def/8", 60}, {"AH09_.def/9", 60}, {"AH10_.def/5", 60},
    {"AH10_.def/6", 60}, {"AH10_.def/7", 60}, {"AH10_.def/8", 60},
    {"AH10_.def/9", 60}, {"AH11_.def/5", 60}, {"AH11_.def/6", 60},
    {"AH11_.def/7", 60}, {"AH11_.def/8", 60}, {"AH11_.def/9", 60},
    {"AH12_.def/5", 60}, {"AH12_.def/6", 60}, {"AH12_.def/7", 60},
    {"AH12_.def/8", 60}, {"AH12_.def/9", 60}, {"AH13_.def/5", 60},
    {"AH13_.def/6", 60}, {"AH13_.def/7", 60}, {"AH13_.def/8", 60},
    {"AH13_.def/9", 60}, {"AH14_.def/5", 60}, {"AH14_.def/6", 60},
    {"AH14_.def/7", 60}, {"AH14_.def/8", 60}, {"AH14_.def/9", 60},
    {"AH15_.def/5", 60}, {"AH15_.def/6", 60}, {"AH15_.def/7", 60},
    {"AH15_.def/8", 60}, {"AH15_.def/9", 60}, {"AH16_.def/5", 60},
    {"AH16_.def/6", 60}, {"AH16_.def/7", 60}, {"AH16_.def/8", 60},
    {"AH16_.def/9", 60}, {"AH17_.def/5", 60}, {"AH17_.def/6", 60},
    {"AH17_.def/7", 60}, {"AH17_.def/8", 60}, {"AH17_.def/9", 60}};

bool AnimateSys::run() {
  auto &registry = World::registrys[World::level];
  for (auto ent : registry.view<TextureComp>()) {
    auto textureComp = &registry.get<TextureComp>(ent);
    auto textures = Global::defCache.at(textureComp->path);
    if (textures.size() > 1) {
      textureComp->time += Window::deltaTime;
      uint8_t delay = 180;
      if (delayMap.contains(textureComp->path)) {
        delay = delayMap.at(textureComp->path);
      }
      if (textureComp->time >= delay) {
        textureComp->time = 0;
        if (textureComp->index == textures.size() - 1) {
          textureComp->index = 0;
        } else {
          textureComp->index += 1;
        }
      }
    }
  }
  return true;
}