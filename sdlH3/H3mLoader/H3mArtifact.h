#pragma once
#include <cstdint>

enum class ArtifactType {
  NONE = -1,
  SPELLBOOK = 0,
  SPELL_SCROLL = 1,
  GRAIL = 2,
  CATAPULT = 3,
  BALLISTA = 4,
  AMMO_CART = 5,
  FIRST_AID_TENT = 6,
  VIAL_OF_DRAGON_BLOOD = 127,
  ARMAGEDDONS_BLADE = 128,
  ANGELIC_ALLIANCE = 129,
  TITANS_THUNDER = 135,
  ART_SELECTION = 144,
  ART_LOCK = 145, // FIXME: We must get rid of this one since it's conflict with
                  // artifact from mods. See issue 2455
};