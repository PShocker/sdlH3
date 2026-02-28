#pragma once
#include "Enum/Enum.h"
#include "H3mLoader/H3mObject.h"
#include "Set/StructSet.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct GenericSet {
  const static inline std::vector<ObjectSetI> generics = {
      {
          .index = ObjectType::PRISON,
          .sound =
              {
                  .ambient = "",
                  .visit = "ROGUE.wav",
                  .removal = {},
              },
      },
      {
          .index = ObjectType::PANDORAS_BOX,
          .sound =
              {
                  .ambient = "",
                  .visit = "ROGUE.wav",
                  .removal =
                      {
                          "PICKUP01.wav",
                          "PICKUP02.wav",
                          "PICKUP03.wav",
                          "PICKUP04.wav",
                          "PICKUP05.wav",
                          "PICKUP06.wav",
                          "PICKUP07.wav",
                      },
              },
      },
      {
          .index = ObjectType::WHIRLPOOL,
          .sound =
              {
                  .ambient = "LOOPWHIR.wav",
                  .visit = "DANGER.wav",
              },
      },
      {
          .index = ObjectType::SUBTERRANEAN_GATE,
          .sound =
              {
                  .ambient = "LOOPGATE.wav",
                  .visit = "LOOPGATE.wav",
              },
      },
      {
          .index = ObjectType::REFUGEE_CAMP,
          .sound =
              {
                  .ambient = "LOOPMERC.wav",
                  .visit = "MILITARY.wav",
              },
      },
      {
          .index = ObjectType::WAR_MACHINE_FACTORY,
          .sound =
              {
                  .ambient = "LOOPFACT.wav",
                  .visit = "MILITARY.wav",
              },
      },
      {
          .index = ObjectType::EYE_OF_MAGI,
          .sound =
              {
                  .visit = "LIGHTHOUSE.wav",
              },
      },
      {
          .index = ObjectType::HUT_OF_MAGI,
          .sound =
              {
                  .visit = "LIGHTHOUSE.wav",
              },
      },
      {
          .index = ObjectType::OBELISK,
          .sound =
              {
                  .visit = "MYSTERY.wav",
              },
      },
      {
          .index = ObjectType::OCEAN_BOTTLE,
          .sound =
              {
                  .visit = "STORE.wav",
              },
      },
      {
          .index = ObjectType::SHIPYARD,
          .sound =
              {
                  .ambient = "LOOPLUMB.wav",
                  .visit = "STORE.wav",
              },
      },
      {
          .index = ObjectType::SIGN,
          .sound =
              {
                  .visit = "STORE.wav",
              },
      },
      {
          .index = ObjectType::SIRENS,
          .sound =
              {
                  .ambient = "LOOPSIRE.wav",
                  .visit = "DANGER.wav",
              },
      },
      {
          .index = ObjectType::DEN_OF_THIEVES,
          .sound =
              {
                  .ambient = "LOOPDEN.wav",
                  .visit = "MYSTERY.wav",
              },
      },
      {
          .index = ObjectType::QUEST_GUARD,
          .sound =
              {
                  .ambient = "",
                  .visit = "CAVEHEAD.wav",
                  .removal =
                      {
                          "PICKUP01.wav",
                          "PICKUP02.wav",
                          "PICKUP03.wav",
                          "PICKUP04.wav",
                          "PICKUP05.wav",
                          "PICKUP06.wav",
                          "PICKUP07.wav",
                      },
              },
      },
      {
          .index = ObjectType::HILL_FORT,
          .sound =
              {
                  .ambient = "LOOPSWAR.wav",
                  .visit = "MILITARY.wav",
              },
      },
      {
          .index = ObjectType::TAVERN,
          .sound =
              {
                  .ambient = "LOOPTAV.wav",
                  .visit = "STORE.wav",
              },
      },
      {
          .index = ObjectType::SANCTUARY,
          .sound =
              {
                  .ambient = "LOOPSANC.wav",
                  .visit = "GETPROTECTION.wav",
              },
      },
      //   Passive objects
      {
          .index = ObjectType::CURSED_GROUND1,
          .sound =
              {
                  .ambient = "LOOPCURS.wav",
                  .visit = "GETPROTECTION.wav",
              },
          .passive =
              ObjectPassive{.battleField = Enum::BATTLE_FIELD_CURSED_GROUND},
      },
  };
};