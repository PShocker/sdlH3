#pragma once

#include <string>
struct VideoSys {
  static void init(const std::string &path, float x, float y);
  static void close();
  static bool run();
};