
#include "World/World.h"
#include <any>
#include <cstdint>
#include "Set/SpellSet.h"

void SpellSet::ViewEarth(std::any data) {
  World::enterAdvScrn();
  World::enterViewWorld();
  return;
}