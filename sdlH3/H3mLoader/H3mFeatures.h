#pragma once
struct H3mFeatures {
  int factionsBytes;
  int heroesBytes;
  int artifactsBytes;
  int skillsBytes;
  int resourcesBytes;
  int spellsBytes;
  int buildingsBytes;

  int factionsCount;
  int heroesCount;
  int heroesPortraitsCount; // +General Kendal, +Catherine (portrait-only in
                            // RoE)
  int artifactsCount;
  int resourcesCount;
  int creaturesCount;
  int spellsCount;
  int skillsCount;
  int terrainsCount;
  int artifactSlotsCount;
  int buildingsCount;
  int roadsCount;
  int riversCount;

  int heroIdentifierInvalid;
  int artifactIdentifierInvalid;
  int creatureIdentifierInvalid;
  int spellIdentifierInvalid;

  bool levelROE = false;
  bool levelAB = false;
  bool levelSOD = false;

  void FeaturesROE();
  void FeaturesAB();
  void FeaturesSOD();
};