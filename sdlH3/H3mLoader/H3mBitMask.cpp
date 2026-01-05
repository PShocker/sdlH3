#include "H3mBitMask.h"

void H3mBitMask::readBitmask(Reader &reader, std::set<uint8_t> &dest,
                             int bytesToRead, int objectsToRead, bool invert) {
  for (int byte = 0; byte < bytesToRead; ++byte) {
    const auto mask = reader.readU8();
    for (int bit = 0; bit < 8; ++bit) {
      if (byte * 8 + bit < objectsToRead) {
        const size_t index = byte * 8 + bit;
        const bool flag = mask & (1 << bit);
        const bool result = (flag != false);
        if (result) {
          dest.insert(index);
        }
      }
    }
  }
}