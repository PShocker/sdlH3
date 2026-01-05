#include "Cfg/SpellCfg.h"
#include "Enum/Enum.h"
#include "Global/Global.h"

#include "World/World.h"
#include <any>
#include <cstdint>
#include "Sys/gui/AdvMapSys.h"

void DimensionDoor(std::any data) {
  World::enterAdvScrn();
  Global::cursorType=(uint8_t)Enum::CURSOR::SPELL;
  Global::cursorIndex=(uint8_t)Enum::CRADVNTR::TELEPORT;
  AdvMapSys::heroFocus();
  return;
}