#include "H3mFeatures.h"

void H3mFeatures::FeaturesROE() {
  levelROE = true;
  factionsBytes = 1;
  heroesBytes = 16;
  artifactsBytes = 16;
  skillsBytes = 4;
  resourcesBytes = 4;
  spellsBytes = 9;
  buildingsBytes = 6;

  factionsCount = 8;
  heroesCount = 128;
  heroesPortraitsCount =
      130; // +General Kendal, +Catherine (portrait-only in RoE)
  artifactsCount = 127;
  resourcesCount = 7;
  creaturesCount = 118;
  spellsCount = 70;
  skillsCount = 28;
  terrainsCount = 10;
  artifactSlotsCount = 18;
  buildingsCount = 41;
  roadsCount = 3;
  riversCount = 4;

  heroIdentifierInvalid = 0xff;
  artifactIdentifierInvalid = 0xff;
  creatureIdentifierInvalid = 0xff;
  spellIdentifierInvalid = 0xff;
}

void H3mFeatures::FeaturesAB() {
  FeaturesROE();
  levelAB = true;

  factionsBytes = 2; // + Conflux
  factionsCount = 9;

  creaturesCount = 145; // + Conflux and new neutrals

  heroesCount = 156;          // + Conflux and campaign heroes
  heroesPortraitsCount = 159; // +Kendal, +young Cristian, +Ordwald
  heroesBytes = 20;

  artifactsCount = 129; // + Armaggedon Blade and Vial of Dragon Blood
  artifactsBytes = 17;

  artifactIdentifierInvalid = 0xffff; // Now uses 2 bytes / object
  creatureIdentifierInvalid = 0xffff; // Now uses 2 bytes / object
}

void H3mFeatures::FeaturesSOD() {
  FeaturesAB();
  levelSOD = true;
  artifactsCount = 144; // + Combined artifacts + 3 unfinished
                        // artifacts (required for some maps)
  artifactsBytes = 18;
  heroesPortraitsCount = 163; // +Finneas +young Gem +young Sandro +young Yog
  artifactSlotsCount = 19;    // + MISC_5 slot
}