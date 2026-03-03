#include "H3mSaver.h"
#include <bitset>
#include <cstdint>
#include <set>

static void saveBitMask(Writer &writer, H3mData &data, std::set<uint8_t> set,
                        uint8_t byteSize) {
  for (uint8_t i = 0; i < byteSize; i++) {
    auto b = i * 8;
    std::bitset<8> bitset;
    for (uint8_t m = 0; m < 8; m++) {
      if (set.contains(b + m)) {
        bitset.set(m);
      }
    }
    writer.writeU8((uint8_t)bitset.to_ulong());
  }
};

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
    auto &playerInfos = data.playerInfos;
    writer.writeU8((uint8_t)playerInfos[i].canHumanPlay);
    writer.writeU8((uint8_t)playerInfos[i].canComputerPlay);
    if ((!(playerInfos[i].canHumanPlay || playerInfos[i].canComputerPlay))) {
      if (data.features.levelROE)
        writer.fill(6, 0);
      if (data.features.levelAB)
        writer.fill(6, 0);
      if (data.features.levelSOD)
        writer.fill(1, 0);
      continue;
    }
    // aiTactic
    writer.writeU8((uint8_t)playerInfos[i].aiTactic);
    if (data.features.levelSOD)
      writer.writeU8(0);
    saveBitMask(writer, data, playerInfos[i].allowedFactions,
                data.features.factionsBytes);
    // isFactionRandom
    writer.writeU8(playerInfos[i].isFactionRandom);
    writer.writeU8(playerInfos[i].hasMainTown);
    if (playerInfos[i].hasMainTown) {
      if (data.features.levelAB) {
        writer.writeU8(playerInfos[i].generateHeroAtMainTown);
        writer.writeU8(0);
      }
      writer.writeU8(playerInfos[i].posOfMainTown[0]);
      writer.writeU8(playerInfos[i].posOfMainTown[1]);
      writer.writeU8(playerInfos[i].posOfMainTown[2]);
    }

    writer.writeU8(playerInfos[i].hasRandomHero);
    writer.writeU8(playerInfos[i].mainCustomHeroId);

    if (playerInfos[i].mainCustomHeroId !=
        (int8_t)data.features.heroIdentifierInvalid) {
      writer.writeU8(playerInfos[i].mainCustomHeroPortrait);
      writer.writeString(playerInfos[i].mainCustomHeroNameTextId);
    }

    if (data.features.levelAB) {
      writer.writeU8(0);
      writer.writeU32(playerInfos[i].heroCount);
      for (size_t pp = 0; pp < playerInfos[i].heroCount; ++pp) {
        writer.writeU8(playerInfos[i].heroId[pp]);
        writer.writeString(playerInfos[i].heroName[pp]);
      }
    }
  }
}

void H3mSaver::saveMap(Writer &writer, H3mData &data) {
  saveMapHeader(writer, data);
  savePlayerInfo(writer, data);
}