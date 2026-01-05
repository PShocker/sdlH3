#pragma once

#include <cstdint>
struct H3mTerrain {
  uint8_t terrainType;
  uint8_t riverType;
  uint8_t roadType;
  uint8_t terView;
  uint8_t riverDir;
  uint8_t roadDir;
  /// first two bits - how to rotate terrain graphic (next two - river graphic,
  /// next two - road);
  ///	7th bit - whether tile is coastal (allows disembarking if land or block
  ///movement if water); 8th bit - Favorable Winds effect
  uint8_t extTileFlags;
};