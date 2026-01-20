#pragma once

#include <string>
struct VideoSys {
  static void init(const std::string &path);
  static bool run();
};