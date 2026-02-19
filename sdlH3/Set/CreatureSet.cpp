#include "Set/CreatureSet.h"

void CreatureSet::init() {

  for (auto &creatures : townCreatures) {
    for (auto &creature : *creatures) {   // 使用引用
      fullCreatures.push_back(&creature); // 如果 hero 本身就是指针，这里要调整
    }
  }
  std::ranges::sort(fullCreatures, {}, &CreatureSetI::index);
}
