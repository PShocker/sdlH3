#pragma once

#include "Chinese.h"
#include "English.h"
#include <string>

struct Lang {
  const static inline std::vector<const std::vector<std::u16string> *> strPool =
      {
          &English::strPool,
          &Chinese::strPool,
  };
};