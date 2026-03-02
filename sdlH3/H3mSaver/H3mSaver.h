#pragma once

#include "H3mLoader/H3mData.h"
#include "Writer/Writer.h"
struct H3mSaver {
  static void saveMapHeader(Writer &writer, H3mData &data);
  static void savePlayerInfo(Writer &writer, H3mData &data);
  static void saveMap(Writer &writer, H3mData &data);
};