#include "Set/HeroSet.h"

void HeroSet::init() {
  for (auto &heros : townHeros) {
    for (auto &hero : *heros) {   // 使用引用
      fullHeros.push_back(&hero); // 如果 hero 本身就是指针，这里要调整
    }
  }
  std::ranges::sort(fullHeros, {}, &HeroSetI::index);
}
