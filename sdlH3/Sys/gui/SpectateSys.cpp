#include "SpectateSys.h"
#include "Global/Global.h"
#include "Sys/gui/AdvMapSys.h"

void SpectateSys::drawRightTop() {}

void SpectateSys::drawRightButton() {}

bool SpectateSys::run() {
  auto playerId = Global::playerId;
  Global::playerId = Global::playerIdSelf;
  AdvMapSys::drawHeroList();
  AdvMapSys::drawTownList();
  SpectateSys::drawRightTop();
  AdvMapSys::drawAgem();
  AdvMapSys::drawResBar(3, Global::viewPort.h - 25);
  Global::playerId = playerId;
  return true;
}