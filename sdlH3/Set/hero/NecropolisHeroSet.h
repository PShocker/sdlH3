#include "Set/StructSet.h"
#include "Enum/Enum.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct NecropolisHeroSet {
  const static inline std::vector<HeroSetI> heros = {
      {// straker
       .index = 64,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::RESISTANCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WALKING_DEAD,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ZOMBIE,
                   .val = 5,
               },
           },
       .spells = {Enum::HASTE}},
      {// vokial
       .index = 65,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::ARTILLERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::BALLISTA, 1},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::VAMPIRE,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::VAMPIRE_LORD,
                   .val = 5,
               },
           },
       .spells = {Enum::STONE_SKIN}},
      {// moandor
       .index = 66,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::LEARNING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::LICH,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::POWER_LICH,
                   .val = 5,
               },
           },
       .spells = {Enum::SLOW}},
      {// charna
       .index = 67,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = true,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::TACTICS, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::WIGHT,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::ZOMBIE,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// tamika
       .index = 68,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = true,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::BLACK_KNIGHT,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::DREAD_KNIGHT,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// isra
       .index = 69,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = true,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::NECROMANCY,
                   .val = 5,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// clavius
       .index = 70,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::OFFENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_GENERATE_RESOURCE,
                   .subId = Enum::GOLD,
                   .val = 350,
               },
           },
       .spells = {Enum::MAGIC_ARROW}},
      {// galthran
       .index = 71,
       .clasz = Enum::HERO_CLASS_DEATH_KNIGHT,  // 死亡骑士 = 8
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::ARMORER, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::SKELETON,
                   .val = 5,
               },
               {
                   .id = Enum::SPECIAL_CREATURE,
                   .subId = Enum::SKELETON_WARRIOR,
                   .val = 5,
               },
           },
       .spells = {Enum::SHIELD}},
      {// septienna
       .index = 72,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = true,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::SCHOLAR, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::DEATH_RIPPLE,
                   .val = 3,
               },
           },
       .spells = {Enum::DEATH_RIPPLE}},
      {// aislinn
       .index = 73,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = true,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::WISDOM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::METEOR_SHOWER,
                   .val = 3,
               },
           },
       .spells = {Enum::METEOR_SHOWER}},
      {// sandro
       .index = 74,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::SORCERY, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::SORCERY,
                   .val = 5,
               },
           },
       .spells = {Enum::SLOW}},
      {// nimbus
       .index = 75,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::EAGLE_EYE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::EAGLE_EYE,
                   .val = 5,
               },
           },
       .spells = {Enum::SHIELD}},
      {// thant
       .index = 76,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::MYSTICISM, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::ANIMATE_DEAD,
                   .val = 3,
               },
           },
       .spells = {Enum::ANIMATE_DEAD}},
      {// xsi
       .index = 77,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = true,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::LEARNING, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SPECIFIC_SPELL,
                   .subId = Enum::STONE_SKIN,
                   .val = 0,
               },
           },
       .spells = {Enum::STONE_SKIN}},
      {// vidomina
       .index = 78,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = true,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::ADVANCED},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_SECONDARY_SKILL,
                   .subId = Enum::NECROMANCY,
                   .val = 5,
               },
           },
       .spells = {Enum::CURSE}},
      {// nagash
       .index = 79,
       .clasz = Enum::HERO_CLASS_NECROMANCER,  // 亡灵巫师 = 9
       .female = false,
       .secSkill =
           {
               {Enum::NECROMANCY, Enum::BASIC},
               {Enum::INTELLIGENCE, Enum::BASIC},
           },
       .defaultCre =
           {
               {Enum::SKELETON, 25},
               {Enum::WALKING_DEAD, 10},
               {Enum::WIGHT, 5},
           },
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               {
                   .id = Enum::SPECIAL_GENERATE_RESOURCE,
                   .subId = Enum::GOLD,
                   .val = 350,
               },
           },
       .spells = {Enum::PROTECTION_FROM_AIR}},
  };
};