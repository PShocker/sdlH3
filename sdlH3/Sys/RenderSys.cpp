#include "RenderSys.h"
#include "Comp/PositionComp.h"
#include "Comp/TextureComp.h"
#include "Global/Global.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "Window/Window.h"
#include "World/World.h"

bool RenderSys::run() {
  auto &registry = World::registrys[World::level];
  const auto &viewPort = Global::viewPort; // 缓存到局部变量
  // 预计算视口边界，避免重复计算
  const float leftBound = viewPort.x - 256.0f;
  const float rightBound = viewPort.x + viewPort.w + 256.0f;
  const float topBound = viewPort.y - 192.0f;
  const float bottomBound = viewPort.y + viewPort.h + 192.0f;
  // 使用结构化绑定，减少重复调用registry.get
  for (auto [entity, positionComp, textureComp] :
       registry.view<PositionComp, TextureComp>().each()) {
    const auto &point = positionComp.point;
    // 快速边界检查
    if (point.x >= leftBound && point.x <= rightBound && point.y >= topBound &&
        point.y <= bottomBound) {
      auto texture = Global::defCache.at(textureComp.path)[textureComp.index];
      SDL_FRect posRect{(float)(int)positionComp.point.x,
                        (float)(int)positionComp.point.y, (float)texture->w,
                        (float)texture->h};
      if (SDL_HasRectIntersectionFloat(&viewPort, &posRect)) {
        posRect.x -= (int)viewPort.x;
        posRect.y -= (int)viewPort.y;
        SDL_RenderTextureRotated(Window::renderer, texture, nullptr, &posRect,
                                 0, nullptr, (SDL_FlipMode)positionComp.flip);
      }
    }
  }
  return true;
}