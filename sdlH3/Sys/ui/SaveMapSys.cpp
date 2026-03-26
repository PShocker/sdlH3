#include "/Sys/ui/SaveMapSys.h"
#include "Global/Global.h"
#include "H3mLoader/H3mData.h"
#include "H3mSaver/H3mSaver.h"
#include "SDL3/SDL_iostream.h"
#include "Writer/Writer.h"
#include <cstdint>

// 存档，和解析地图文件类似
bool SaveMapSys::save() {
  auto &data = Global::mapData;
  Writer writer("./1.h3s");
  H3mSaver::saveMap(writer);

  return true;
}