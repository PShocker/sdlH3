#pragma once

#include "Enum/Enum.h"
#include "Set/StructSet.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

struct ArtifactBonus {
  uint8_t type; // Bonus type, corresponds to Enum::ARTIFACT_BONUS_TYPE
  uint8_t
      subType; // Subtype, e.g., PRIMARY_SKILL_ATTACK, SPELL_SCHOOL_FIRE, etc.
  int32_t val; // Bonus value
};

struct ArtifactData {
  uint8_t index; // Artifact ID, corresponds to Enum::ARTIFACT_ID
  std::vector<ArtifactBonus> bonus; // List of bonuses provided by the artifact
  uint32_t experience;              // Experience provided by the artifact
  std::array<uint32_t, 7> cost;     // Purchase cost
  std::array<bool, 19> slot;        // Equip slots [0-18]
  std::vector<uint8_t> components;  // Combined artifact component IDs
};

struct ArtifactSet {
  const static inline std::
      vector<ArtifactData>
          artifacts =
              {
                  // Basic artifacts (0-6)
                  {
                      // SPELL_BOOK
                      .index = 0,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SPELL_SCROLL
                      .index = 1,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // GRAIL
                      .index = 2,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CATAPULT
                      .index = 3,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BALLISTA
                      .index = 4,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // AMMO_CART
                      .index = 5,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // FIRST_AID_TENT
                      .index = 6,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Weapons - Attack (7-12)
                  {
                      // CENTAUR_AXE
                      .index = 7,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_ATTACK,
                                  .val = 2,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BLACKSHARD_OF_THE_DEAD_KNIGHT
                      .index = 8,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_ATTACK,
                                  .val = 3,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // GREATER_GNOLDS_FLAIL
                      .index = 9,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 4},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // OGRES_CLUB_OF_HAVOC
                      .index = 10,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 5},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SWORD_OF_HELLFIRE
                      .index = 11,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 6},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TITANS_GLADIUS
                      .index = 12,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 12},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = -3},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Shields - Defence (13-18)
                  {
                      // SHIELD_OF_THE_DWARVEN_LORDS
                      .index = 13,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SHIELD_OF_THE_YAWNING_DEAD
                      .index = 14,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 3},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BUCKLER_OF_THE_GNOLF_KING
                      .index = 15,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 4},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TARG_OF_THE_RAMPAGING_OGRE
                      .index = 16,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 5},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SHIELD_OF_THE_DAMNED
                      .index = 17,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_DEFENCE,
                                  .val = 6,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SENTINELS_SHIELD
                      .index = 18,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_DEFENCE,
                                  .val = 12,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_ATTACK,
                                  .val = -3,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Helmets - Knowledge (19-24)
                  {
                      // HELM_OF_THE_ALABASTER_UNICORN
                      .index = 19,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SKULL_HELMET
                      .index = 20,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 2,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // HELM_OF_CHAOS
                      .index = 21,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 3,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CROWN_OF_THE_SUPREME_MAGI
                      .index = 22,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 4,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // HELLSTORM_HELMET
                      .index = 23,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 5,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // THUNDER_HELMET
                      .index = 24,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 10,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                                  .val = -2,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Armor - Spell Power (25-30)
                  {
                      // BREASTPLATE_OF_PETRIFIED_WOOD
                      .index = 25,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // RIB_CAGE
                      .index = 26,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SCALES_OF_THE_GREATER_BASILISK
                      .index = 27,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 3},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TUNIC_OF_THE_CYCLOPS_KING
                      .index = 28,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 4},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BREASTPLATE_OF_BRIMSTONE
                      .index = 29,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 5},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TITANS_CUIRASS
                      .index = 30,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 10},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = -2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Combined artifact components - All stats (31-36)
                  {
                      // ARMOR_OF_WONDER
                      .index = 31,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 1},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 1},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 1},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SANDALS_OF_THE_SAINT
                      .index = 32,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 2},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 2},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 2},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CELESTIAL_NECKLACE_OF_BLISS
                      .index = 33,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 3},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 3},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 3},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 3},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // LIONS_SHIELD_OF_COURAGE
                      .index = 34,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 4},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 4},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 4},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 4},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SWORD_OF_JUDGEMENT
                      .index = 35,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 5},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 5},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 5},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 5},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // HELM_OF_HEAVENLY_ENLIGHTENMENT
                      .index = 36,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 6},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 6},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 6},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 6},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Dragon series (37-45)
                  {
                      // QUIET_EYE_OF_THE_DRAGON
                      .index = 37,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 1},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // RED_DRAGON_FLAME_TONGUE
                      .index = 38,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 2},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // DRAGON_SCALE_SHIELD
                      .index = 39,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 3},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 3},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // DRAGON_SCALE_ARMOR
                      .index = 40,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_ATTACK,
                               .val = 4},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_DEFENCE,
                               .val = 4},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // DRAGONBONE_GREAVES
                      .index = 41,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 1},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // DRAGON_WING_TABARD
                      .index = 42,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 2},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // NECKLACE_OF_DRAGONTEETH
                      .index = 43,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 3},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 3},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CROWN_OF_DRAGONTOOTH
                      .index = 44,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                               .val = 4},
                              {.type = Enum::ARTIFACT_PRIMARY_SKILL,
                               .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                               .val = 4},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // STILL_EYE_OF_THE_DRAGON
                      .index = 45,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MORALE,
                               .subType = 0,
                               .val = 1},
                              {.type = Enum::ARTIFACT_LUCK,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Luck artifacts (46-48)
                  {
                      // CLOVER_OF_FORTUNE
                      .index = 46,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_LUCK,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CARDS_OF_PROPHECY
                      .index = 47,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_LUCK,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // LADYBIRD_OF_LUCK
                      .index = 48,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_LUCK,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Morale artifacts (49-51)
                  {
                      // BADGE_OF_COURAGE
                      .index = 49,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MORALE,
                               .subType = 0,
                               .val = 1},
                              {.type = Enum::ARTIFACT_MIND_IMMUNITY,
                               .subType = 0,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CREST_OF_VALOR
                      .index = 50,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MORALE,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // GLYPH_OF_GALLANTRY
                      .index = 51,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MORALE,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Sight radius artifacts (52-53)
                  {
                      // SPECULUM
                      .index = 52,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SIGHT_RADIUS,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SPYGLASS
                      .index = 53,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SIGHT_RADIUS,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Necromancy artifacts (54-56)
                  {
                      // AMULET_OF_THE_UNDERTAKER
                      .index = 54,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_UNDEAD_RAISE_PERCENTAGE,
                               .subType = 0,
                               .val = 5},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // VAMPIRES_COWL
                      .index = 55,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_UNDEAD_RAISE_PERCENTAGE,
                               .subType = 0,
                               .val = 10},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // DEAD_MANS_BOOTS
                      .index = 56,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_UNDEAD_RAISE_PERCENTAGE,
                               .subType = 0,
                               .val = 15},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Magic resistance artifacts (57-59)
                  {
                      // GARNITURE_OF_INTERFERENCE
                      .index = 57,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MAGIC_RESISTANCE,
                               .subType = 0,
                               .val = 5},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SURCOAT_OF_COUNTERPOISE
                      .index = 58,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MAGIC_RESISTANCE,
                               .subType = 0,
                               .val = 10},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BOOTS_OF_POLARITY
                      .index = 59,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MAGIC_RESISTANCE,
                               .subType = 0,
                               .val = 15},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Archery artifacts (60-62)
                  {
                      // BOW_OF_ELVEN_CHERRYWOOD
                      .index = 60,
                      .bonus =
                          {
                              {
                                  .type = Enum::
                                      ARTIFACT_PERCENTAGE_DAMAGE_BOOST_RANGED,
                                  .subType = 0,
                                  .val = 5,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BOWSTRING_OF_THE_UNICORNS_MANE
                      .index = 61,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PERCENTAGE_DAMAGE_BOOST_RANGED,
                                  .subType = 0,
                                  .val = 10,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ANGEL_FEATHER_ARROWS
                      .index = 62,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PERCENTAGE_DAMAGE_BOOST,
                                  .subType = 0,
                                  .val = 15,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Battle spell learning artifacts (63-65)
                  {
                      // BIRD_OF_PERCEPTION
                      .index = 63,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_LEARN_BATTLE_SPELL_CHANCE,
                               .subType = 0,
                               .val = 5},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // STOIC_WATCHMAN
                      .index = 64,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_LEARN_BATTLE_SPELL_CHANCE,
                               .subType = 0,
                               .val = 10},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // EMBLEM_OF_COGNIZANCE
                      .index = 65,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_LEARN_BATTLE_SPELL_CHANCE,
                               .subType = 0,
                               .val = 15},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Surrender discount artifacts (66-68)
                  {
                      // STATESMANS_MEDAL
                      .index = 66,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SURRENDER_DISCOUNT,
                               .subType = 0,
                               .val = 10},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // DIPLOMATS_RING
                      .index = 67,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SURRENDER_DISCOUNT,
                               .subType = 0,
                               .val = 10},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // AMBASSADORS_SASH
                      .index = 68,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SURRENDER_DISCOUNT,
                               .subType = 0,
                               .val = 10},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Movement artifacts (69-72)
                  {
                      // RING_OF_THE_WAYFARER
                      .index = 69,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_STACKS_SPEED,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // EQUESTRIANS_GLOVES
                      .index = 70,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MOVEMENT_LAND,
                               .subType = 0,
                               .val = 300},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // NECKLACE_OF_OCEAN_GUIDANCE
                      .index = 71,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_MOVEMENT_SEA,
                                  .subType = 0,
                                  .val = 1000,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ANGEL_WINGS
                      .index = 72,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_FLYING_MOVEMENT,
                                  .subType = 0,
                                  .val = 0,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Mana regeneration artifacts (73-75)
                  {
                      // CHARM_OF_MANA
                      .index = 73,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_MANA_REGENERATION,
                                  .subType = 0,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TALISMAN_OF_MANA
                      .index = 74,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_MANA_REGENERATION,
                                  .subType = 0,
                                  .val = 2,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // MYSTIC_ORB_OF_MANA
                      .index = 75,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_MANA_REGENERATION,
                                  .subType = 0,
                                  .val = 3,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Spell duration artifacts (76-78)
                  {
                      // COLLAR_OF_CONJURING
                      .index = 76,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELL_DURATION,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // RING_OF_CONJURING
                      .index = 77,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELL_DURATION,
                               .subType = 0,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CAPE_OF_CONJURING
                      .index = 78,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELL_DURATION,
                               .subType = 0,
                               .val = 3},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Spell damage artifacts (79-82)
                  {
                      // ORB_OF_THE_FIRMAMENT
                      .index = 79,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELL_DAMAGE,
                               .subType = Enum::SPELL_SCHOOL_AIR,
                               .val = 50},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ORB_OF_SILT
                      .index = 80,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELL_DAMAGE,
                               .subType = Enum::SPELL_SCHOOL_EARTH,
                               .val = 50},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ORB_OF_TEMPESTUOUS_FIRE
                      .index = 81,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELL_DAMAGE,
                               .subType = Enum::SPELL_SCHOOL_FIRE,
                               .val = 50},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ORB_OF_DRIVING_RAIN
                      .index = 82,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELL_DAMAGE,
                               .subType = Enum::SPELL_SCHOOL_WATER,
                               .val = 50},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Special magic artifacts (83-93)
                  {
                      // RECANTERS_CLOAK
                      .index = 83,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_BLOCK_MAGIC_ABOVE,
                               .subType = 0,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SPIRIT_OF_OPPRESSION
                      .index = 84,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_MORALE,
                               .subType = 0,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // HOURGLASS_OF_THE_EVIL_HOUR
                      .index = 85,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_LUCK,
                               .subType = 0,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TOME_OF_FIRE_MAGIC
                      .index = 86,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELLS_OF_SCHOOL,
                               .subType = Enum::SPELL_SCHOOL_FIRE,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TOME_OF_AIR_MAGIC
                      .index = 87,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELLS_OF_SCHOOL,
                               .subType = Enum::SPELL_SCHOOL_AIR,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TOME_OF_WATER_MAGIC
                      .index = 88,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELLS_OF_SCHOOL,
                               .subType = Enum::SPELL_SCHOOL_WATER,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TOME_OF_EARTH_MAGIC
                      .index = 89,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_SPELLS_OF_SCHOOL,
                               .subType = Enum::SPELL_SCHOOL_EARTH,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BOOTS_OF_LEVITATION
                      .index = 90,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_WATER_WALKING,
                               .subType = 0,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // GOLDEN_BOW
                      .index = 91,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_NO_DISTANCE_PENALTY,
                               .subType = 0,
                               .val = 0},
                              {.type = Enum::ARTIFACT_NO_WALL_PENALTY,
                               .subType = 0,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SPHERE_OF_PERMANENCE
                      .index = 92,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::DISPEL,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ORB_OF_VULNERABILITY
                      .index = 93,
                      .bonus =
                          {
                              {.type =
                                   Enum::ARTIFACT_NEGATE_ALL_NATURAL_IMMUNITIES,
                               .subType = 0,
                               .val = 0},
                              {.type = Enum::ARTIFACT_MAGIC_RESISTANCE,
                               .subType = 0,
                               .val = 0},
                              {.type = Enum::ARTIFACT_SPELL_RESISTANCE_AURA,
                               .subType = 0,
                               .val = 0},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Health artifacts (94-96)
                  {
                      // RING_OF_VITALITY
                      .index = 94,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_STACK_HEALTH,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // RING_OF_LIFE
                      .index = 95,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_STACK_HEALTH,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // VIAL_OF_LIFEBLOOD
                      .index = 96,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_STACK_HEALTH,
                               .subType = 0,
                               .val = 2},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Speed artifacts (97-99)
                  {
                      // NECKLACE_OF_SWIFTNESS
                      .index = 97,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_STACKS_SPEED,
                               .subType = 0,
                               .val = 1},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // BOOTS_OF_SPEED
                      .index = 98,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_MOVEMENT_LAND,
                                  .subType = 0,
                                  .val = 600,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // CAPE_OF_VELOCITY
                      .index = 99,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_STACKS_SPEED,
                                  .subType = 0,
                                  .val = 2,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Pendants - Spell immunity (100-108)
                  {
                      // PENDANT_OF_DISPASSION
                      .index = 100,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::BERSERK,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_SECOND_SIGHT
                      .index = 101,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::BLIND,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_HOLINESS
                      .index = 102,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::CURSE,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_LIFE
                      .index = 103,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::DEATH_RIPPLE,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_DEATH
                      .index = 104,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::DESTROY_UNDEAD,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_FREE_WILL
                      .index = 105,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::HYPNOTIZE,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_NEGATIVITY
                      .index = 106,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::LIGHTNING_BOLT,
                              },
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::CHAIN_LIGHTNING,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_TOTAL_RECALL
                      .index = 107,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::FORGETFULNESS,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // PENDANT_OF_COURAGE
                      .index = 108,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_MORALE,
                                  .subType = 0,
                                  .val = 3,
                              },
                              {
                                  .type = Enum::ARTIFACT_LUCK,
                                  .subType = 0,
                                  .val = 3,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Resource generation artifacts (109-117)
                  {
                      // EVERFLOWING_CRYSTAL_CLOAK
                      .index = 109,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::CRYSTAL,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // RING_OF_INFINITE_GEMS
                      .index = 110,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::GEM,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // EVERPOURING_VIAL_OF_MERCURY
                      .index = 111,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::MERCURY,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // INEXHAUSTIBLE_CART_OF_ORE
                      .index = 112,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::ORE,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // EVERSMOKING_RING_OF_SULFUR
                      .index = 113,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::SULFUR,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // INEXHAUSTIBLE_CART_OF_LUMBER
                      .index = 114,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::WOOD,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ENDLESS_SACK_OF_GOLD
                      .index = 115,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::GOLD,
                                  .val = 1000,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ENDLESS_BAG_OF_GOLD
                      .index = 116,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::GOLD,
                                  .val = 750,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ENDLESS_PURSE_OF_GOLD
                      .index = 117,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                                  .subType = Enum::GOLD,
                                  .val = 500,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Legion series (118-122)
                  {
                      // LEGS_OF_LEGION
                      .index = 118,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_CREATURE_GROWTH,
                                  .subType = 2,
                                  .val = 5,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // LOINS_OF_LEGION
                      .index = 119,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_CREATURE_GROWTH,
                                  .subType = 3,
                                  .val = 4,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // TORSO_OF_LEGION
                      .index = 120,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_CREATURE_GROWTH,
                                  .subType = 4,
                                  .val = 3,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ARMS_OF_LEGION
                      .index = 121,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_CREATURE_GROWTH,
                                  .subType = 5,
                                  .val = 2,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // HEAD_OF_LEGION
                      .index = 122,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_CREATURE_GROWTH,
                                  .subType = 6,
                                  .val = 1,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Hats (123-124)
                  {
                      // SEA_CAPTAINS_HAT
                      .index = 123,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_WHIRLPOOL_PROTECTION,
                                  .subType = 0,
                                  .val = 0,
                              },
                              {
                                  .type = Enum::ARTIFACT_MOVEMENT_SEA,
                                  .subType = 0,
                                  .val = 500,
                              },
                              {
                                  .type = Enum::ARTIFACT_SPELL,
                                  .subType = 0,
                                  .val = Enum::SUMMON_BOAT,
                              },
                              {
                                  .type = Enum::ARTIFACT_SPELL,
                                  .subType = 0,
                                  .val = Enum::SCUTTLE_BOAT,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // SPELLBINDERS_HAT
                      .index = 124,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELLS_OF_LEVEL,
                                  .subType = 0,
                                  .val = 5,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },

                  // Special artifacts (125-140)
                  {
                      // SHACKLES_OF_WAR
                      .index = 125,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_BATTLE_NO_FLEEING,
                                  .subType = 0,
                                  .val = 0,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ORB_OF_INHIBITION
                      .index = 126,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_BLOCK_ALL_MAGIC,
                                  .subType = 0,
                                  .val = 0,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // VIAL_OF_DRAGON_BLOOD
                      .index = 127,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_ATTACK,
                                  .val = 5,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_DEFENCE,
                                  .val = 5,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ARMAGEDDONS_BLADE
                      .index = 128,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL,
                                  .subType = 0,
                                  .val = Enum::ARMAGEDDON,
                              },
                              {
                                  .type = Enum::ARTIFACT_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = Enum::ARMAGEDDON,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_ATTACK,
                                  .val = 3,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_DEFENCE,
                                  .val = 3,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                                  .val = 3,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 6,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // ANGELIC_ALLIANCE
                      .index = 129,
                      .bonus =
                          {
                              {.type = Enum::ARTIFACT_NONEVIL_ALIGNMENT_MIX,
                               .subType = 0,
                               .val = 0},
                              {.type = Enum::ARTIFACT_OPENING_BATTLE_SPELL,
                               .subType = 0,
                               .val = Enum::PRAYER},
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_ARMOR_OF_WONDER,
                              Enum::ARTIFACT_SANDALS_OF_THE_SAINT,
                              Enum::ARTIFACT_CELESTIAL_NECKLACE_OF_BLISS,
                              Enum::ARTIFACT_LIONS_SHIELD_OF_COURAGE,
                              Enum::ARTIFACT_SWORD_OF_JUDGEMENT,
                              Enum::ARTIFACT_HELM_OF_HEAVENLY_ENLIGHTENMENT,
                          },
                  },
                  {
                      // CLOAK_OF_THE_UNDEAD_KING
                      .index = 130,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_IMPROVED_NECROMANCY,
                                  .subType = Enum::SKELETON,
                                  .val = 0,
                              },
                              {
                                  .type = Enum::ARTIFACT_IMPROVED_NECROMANCY,
                                  .subType = Enum::WALKING_DEAD,
                                  .val = 1,
                              },
                              {
                                  .type = Enum::ARTIFACT_IMPROVED_NECROMANCY,
                                  .subType = Enum::WIGHT,
                                  .val = 2,
                              },
                              {
                                  .type = Enum::ARTIFACT_IMPROVED_NECROMANCY,
                                  .subType = Enum::LICH,
                                  .val = 3,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {Enum::ARTIFACT_AMULET_OF_THE_UNDERTAKER,
                                     Enum::ARTIFACT_VAMPIRES_COWL,
                                     Enum::ARTIFACT_DEAD_MANS_BOOTS},
                  },
                  {
                      // ELIXIR_OF_LIFE
                      .index = 131,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_STACK_HEALTH,
                                  .subType = 0,
                                  .val = 25,
                              },
                              {
                                  .type = Enum::ARTIFACT_HP_REGENERATION,
                                  .subType = 0,
                                  .val = 50,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {Enum::ARTIFACT_RING_OF_VITALITY,
                                     Enum::ARTIFACT_RING_OF_LIFE,
                                     Enum::ARTIFACT_VIAL_OF_LIFEBLOOD},
                  },
                  {
                      // ARMOR_OF_THE_DAMNED
                      .index = 132,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL,
                                  .subType = 0,
                                  .val = Enum::SLOW,
                              },
                              {
                                  .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL,
                                  .subType = 0,
                                  .val = Enum::CURSE,
                              },
                              {
                                  .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL,
                                  .subType = 0,
                                  .val = Enum::WEAKNESS,
                              },
                              {
                                  .type = Enum::ARTIFACT_OPENING_BATTLE_SPELL,
                                  .subType = 0,
                                  .val = Enum::MISFORTUNE,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_BLACKSHARD_OF_THE_DEAD_KNIGHT,
                              Enum::ARTIFACT_SHIELD_OF_THE_YAWNING_DEAD,
                              Enum::ARTIFACT_SKULL_HELMET,
                              Enum::ARTIFACT_RIB_CAGE,
                          },
                  },
                  {
                      // STATUE_OF_LEGION
                      .index = 133,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_CREATURE_GROWTH_PERCENT,
                                  .subType = 0,
                                  .val = 50,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_LEGS_OF_LEGION,
                              Enum::ARTIFACT_LOINS_OF_LEGION,
                              Enum::ARTIFACT_TORSO_OF_LEGION,
                              Enum::ARTIFACT_ARMS_OF_LEGION,
                              Enum::ARTIFACT_HEAD_OF_LEGION,
                          },
                  },
                  {
                      // POWER_OF_THE_DRAGON_FATHER
                      .index = 134,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_LEVEL_SPELL_IMMUNITY,
                                  .subType = 0,
                                  .val = 4,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_ATTACK,
                                  .val = 6,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_DEFENCE,
                                  .val = 6,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_SPELLPOWER,
                                  .val = 6,
                              },
                              {
                                  .type = Enum::ARTIFACT_PRIMARY_SKILL,
                                  .subType = Enum::PRIMARY_SKILL_KNOWLEDGE,
                                  .val = 6,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_QUIET_EYE_OF_THE_DRAGON,
                              Enum::ARTIFACT_RED_DRAGON_FLAME_TONGUE,
                              Enum::ARTIFACT_DRAGON_SCALE_SHIELD,
                              Enum::ARTIFACT_DRAGON_SCALE_ARMOR,
                              Enum::ARTIFACT_DRAGONBONE_GREAVES,
                              Enum::ARTIFACT_DRAGON_WING_TABARD,
                              Enum::ARTIFACT_NECKLACE_OF_DRAGONTEETH,
                              Enum::ARTIFACT_CROWN_OF_DRAGONTOOTH,
                              Enum::ARTIFACT_STILL_EYE_OF_THE_DRAGON,
                          },
                  },
                  {
                      // TITANS_THUNDER
                      .index = 135,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL,
                                  .subType = 0,
                                  .val = Enum::TITANS_LIGHTNING_BOLT,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_TITANS_GLADIUS,
                              Enum::ARTIFACT_SENTINELS_SHIELD,
                              Enum::ARTIFACT_THUNDER_HELMET,
                              Enum::ARTIFACT_TITANS_CUIRASS,
                          },
                  },
                  {
                      // ADMIRALS_HAT
                      .index = 136,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_FREE_SHIP_BOARDING,
                                  .subType = 0,
                                  .val = 0,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_NECKLACE_OF_OCEAN_GUIDANCE,
                              Enum::ARTIFACT_SEA_CAPTAINS_HAT,
                          },
                  },
                  {
                      // BOW_OF_THE_SHARPSHOOTER
                      .index = 137,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_NO_DISTANCE_PENALTY,
                                  .subType = 0,
                                  .val = 0,
                              },
                              {
                                  .type = Enum::ARTIFACT_NO_WALL_PENALTY,
                                  .subType = 0,
                                  .val = 0,
                              },
                              {
                                  .type = Enum::ARTIFACT_FREE_SHOOTING,
                                  .subType = 0,
                                  .val = 0,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {Enum::ARTIFACT_BOW_OF_ELVEN_CHERRYWOOD,
                           Enum::ARTIFACT_BOWSTRING_OF_THE_UNICORNS_MANE,
                           Enum::ARTIFACT_ANGEL_FEATHER_ARROWS},
                  },
                  {
                      // WIZARDS_WELL
                      .index = 138,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_FULL_MANA_REGENERATION,
                                  .subType = 0,
                                  .val = 0,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_CHARM_OF_MANA,
                              Enum::ARTIFACT_TALISMAN_OF_MANA,
                              Enum::ARTIFACT_MYSTIC_ORB_OF_MANA,
                          },
                  },
                  {
                      // RING_OF_THE_MAGI
                      .index = 139,
                      .bonus =
                          {
                              {
                                  .type = Enum::ARTIFACT_SPELL_DURATION,
                                  .subType = 0,
                                  .val = 50,
                              },
                          },
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components =
                          {
                              Enum::ARTIFACT_COLLAR_OF_CONJURING,
                              Enum::ARTIFACT_RING_OF_CONJURING,
                              Enum::ARTIFACT_CAPE_OF_CONJURING,
                          },
                  },
                  {// CORNUCOPIA
                   .index = 140,
                   .bonus =
                       {
                           {
                               .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                               .subType = Enum::CRYSTAL,
                               .val = 4,
                           },
                           {
                               .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                               .subType = Enum::GEM,
                               .val = 4,
                           },
                           {
                               .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                               .subType = Enum::MERCURY,
                               .val = 4,
                           },
                           {
                               .type = Enum::ARTIFACT_GENERATE_RESOURCE,
                               .subType = Enum::SULFUR,
                               .val = 4,
                           },
                       },
                   .experience = 0,
                   .cost = {},
                   .slot = {},
                   .components =
                       {
                           Enum::ARTIFACT_RECANTERS_CLOAK,
                           Enum::ARTIFACT_RING_OF_INFINITE_GEMS,
                           Enum::ARTIFACT_EVERPOURING_VIAL_OF_MERCURY,
                           Enum::ARTIFACT_EVERSMOKING_RING_OF_SULFUR,
                       }},

                  // Unused artifacts (141-143)
                  {
                      // UNUSED_1
                      .index = 141,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // UNUSED_2
                      .index = 142,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
                  {
                      // UNUSED_3
                      .index = 143,
                      .bonus = {},
                      .experience = 0,
                      .cost = {},
                      .slot = {},
                      .components = {},
                  },
  };
};