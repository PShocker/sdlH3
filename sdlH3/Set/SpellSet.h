#pragma once
#include "Set/StructSet.h"
#include <algorithm>
#include <array>
#include <vector>

struct SpellSet {

  static void SummonBoat(std::any data);
  static void ScuttleBoat(std::any data);
  static void Visions(std::any data);
  static void ViewEarth(std::any data);
  static void Disguise(std::any data);
  static void ViewAir(std::any data);
  static void Fly(std::any data);
  static void WaterWalk(std::any data);
  static void DimensionDoor(std::any data);
  static void TownPortal(std::any data);
  static void Quicksand(std::any data);
  static void LandMine(std::any data);
  static void ForceField(std::any data);
  static void FireWall(std::any data);
  static void Earthquake(std::any data);
  static void MagicArrow(std::any data);
  static void IceBolt(std::any data);
  static void LightningBolt(std::any data);
  static void Implosion(std::any data);
  static void ChainLightning(std::any data);
  static void FrostRing(std::any data);
  static void Fireball(std::any data);
  static void Inferno(std::any data);
  static void MeteorShower(std::any data);
  static void DeathRipple(std::any data);
  static void DestroyUndead(std::any data);
  static void Armageddon(std::any data);
  static void Shield(std::any data);
  static void AirShield(std::any data);
  static void FireShield(std::any data);
  static void ProtectionfromAir(std::any data);
  static void ProtectionfromFire(std::any data);
  static void ProtectionfromWater(std::any data);
  static void ProtectionfromEarth(std::any data);
  static void AntiMagic(std::any data);
  static void Dispel(std::any data);
  static void MagicMirror(std::any data);
  static void Cure(std::any data);
  static void Resurrection(std::any data);
  static void AnimateDead(std::any data);
  static void Sacrifice(std::any data);
  static void Bless(std::any data);
  static void Curse(std::any data);
  static void Bloodlust(std::any data);
  static void Precision(std::any data);
  static void Weakness(std::any data);
  static void StoneSkin(std::any data);
  static void DisruptingRay(std::any data);
  static void Prayer(std::any data);
  static void Mirth(std::any data);
  static void Sorrow(std::any data);
  static void Fortune(std::any data);
  static void Misfortune(std::any data);
  static void Haste(std::any data);
  static void Slow(std::any data);
  static void Slayer(std::any data);
  static void Frenzy(std::any data);
  static void TitansLightningBolt(std::any data);
  static void Counterstrike(std::any data);
  static void Berserk(std::any data);
  static void Hypnotize(std::any data);
  static void Forgetfulness(std::any data);
  static void Blind(std::any data);
  static void Teleport(std::any data);
  static void RemoveObstacle(std::any data);
  static void MirrorImage(std::any data);
  static void SummonFireElemental(std::any data);
  static void SummonEarthElemental(std::any data);
  static void SummonWaterElemental(std::any data);
  static void SummonAirElemental(std::any data);

  static inline std::vector<const SpellI *> spellsAdv = {};

  static inline std::vector<const SpellI *> spellsBat = {};

  static inline std::vector<const SpellI *> spellsCre = {};

  static inline std::array<std::vector<const SpellI *>, 4> spellsSchool = {};

  static inline std::array<std::vector<const SpellI *>, 6> spellsLvl = {};

  static inline std::vector<SpellI> spells = {
      {
          .index = 0,
          .school = {},
          .manaCost = {1, 1, 1, 1},
          .level = 1,
          .type = 1,
          .func = SummonBoat,
      },
      {
          .index = 1,
          .school = {},
          .manaCost = {1, 1, 1, 1},
          .level = 1,
          .type = 1,
          .func = ScuttleBoat,
      },
  };
};