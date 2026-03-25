#pragma once

#include "H3mLoader/H3mData.h"
#include "Writer/Writer.h"
struct H3mSaver {
  static void saveMap(Writer &writer, H3mData &data);
};