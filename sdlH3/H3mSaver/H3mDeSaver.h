#pragma once
#include "Reader/Reader.h"
struct H3mDeSaver {
  static void afterEntLoad(Reader &reader);
  static void loadMap(Reader &reader);
};