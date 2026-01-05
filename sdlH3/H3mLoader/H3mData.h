#pragma once
#include "H3mCreatureSet.h"
#include "H3mEvent.h"
#include "H3mFeatures.h"
#include "H3mHearder.h"
#include "H3mHero.h"
#include "H3mLoader/H3mObject.h"
#include "H3mObject.h"
#include "H3mPlayerInfo.h"
#include "H3mQuest.h"
#include "H3mRumor.h"
#include "H3mTerrain.h"
#include "H3mVictoryLossConditions.h"
#include "Reader/Reader.h"
#include <cstdint>
#include <string>

struct H3mData {
  H3mHeader header;
  H3mFeatures features;
  H3mPlayerInfo playerInfos[8];
  H3mVictoryLossConditions victorylossCond;

  uint8_t howManyTeams;
  std::set<uint8_t> allowedHeroes;
  std::set<uint8_t>
      reservedCampaignHeroes; /// Heroes that have placeholders in this map and
                              /// are reserved for campaign
  std::vector<H3mHero> disposedHeroes;
  std::set<uint8_t>
      disposedHeroesPlayers; /// Who can hire this hero (bitfield).

  std::set<uint8_t> allowedArtifact;
  std::set<uint8_t> allowedSpells;
  std::set<uint8_t> allowedAbilities;

  std::vector<H3mRumor> rumors;
  std::vector<H3mHero> predefinedHeroes;

  std::vector<H3mTerrain> terrains;

  std::vector<H3mObject> originalTemplates;
  std::vector<H3mObject> remappedTemplates;

  std::vector<H3mEvent> events;

  std::vector<H3mObject> objects;

  void readHeader();
  void readPlayerInfo();
  void readVictoryLossConditions();
  void readTeamInfo();
  void readAllowedHeroes();
  void readDisposedHeroes();
  void readAllowedArtifacts();
  void readAllowedSpellsAbilities();
  void readMapOptions();
  void readRumors();
  void readPredefinedHeroes();
  void readTerrain();
  void readObjectTemplates();
  void readObjects();
  void readEventCommon(H3mEvent &event);
  void readEvents();

  void loadArtifactsOfHero(H3mHero &hero);
  void loadArtifactToSlot(H3mHero &hero, uint16_t slot);

  void readCreatureSet(H3mCreatureSet &creatureSet);
  void readMessageAndGuards(H3mObject &object);
  void readBoxContent(H3mObject &object);
  void readQuest(H3mQuest &quest);

  void init();
  Reader reader;
  H3mData(std::string filePath);
};