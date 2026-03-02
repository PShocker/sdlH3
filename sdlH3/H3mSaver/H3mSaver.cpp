#include "H3mSaver.h"

void H3mSaver::saveMapHeader(Writer &writer, H3mData &data) {
  //   version
  writer.writeU32((uint32_t)data.header.version);
  // areAnyPlayers
  writer.writeU8(0);
  // width
  writer.writeU32((uint32_t)data.header.width);
  // twoLevel
  writer.writeU8((uint32_t)data.header.twoLevel);
  // name
  writer.writeString(data.header.name);
  // description
  writer.writeString(data.header.description);
  // difficult
  writer.writeU8((uint8_t)data.header.difficulty);
  if (data.features.levelAB)
    writer.writeU8(0);
}

void H3mSaver::savePlayerInfo(Writer &writer, H3mData &data) {
  for (int i = 0; i < 8; ++i) {
    writer.writeU8((uint8_t)data.playerInfos[i].canHumanPlay);
    writer.writeU8((uint8_t)data.playerInfos[i].canComputerPlay);
    if ((!(data.playerInfos[i].canHumanPlay ||
           data.playerInfos[i].canComputerPlay))) {
      if (data.features.levelROE)
        writer.fill(6, 0);
      if (data.features.levelAB)
        writer.fill(6, 0);
      if (data.features.levelSOD)
        writer.fill(1, 0);
      continue;
    }
    // aiTactic
    writer.writeU8((uint8_t)data.playerInfos[i].aiTactic);
    if (data.features.levelSOD)
      writer.writeU8(0);
  }
}

void H3mSaver::saveMap(Writer &writer, H3mData &data) {
    saveMapHeader(writer, data);
    savePlayerInfo(writer, data);
}