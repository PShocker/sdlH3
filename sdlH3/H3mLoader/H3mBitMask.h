#pragma once
#include "Reader/Reader.h"
#include <set>

struct H3mBitMask {
  static void readBitmask(Reader &reader, std::set<uint8_t> &dest,
                          int bytesToRead, int objectsToRead, bool invert);
};