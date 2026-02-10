
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct HeroSetSpec {
  uint8_t id;
  uint8_t subId;
  uint8_t val;
};

struct HeroSetI {
  uint8_t index;
  uint8_t clasz; // class
  bool female;
  std::vector<std::pair<uint8_t, uint8_t>> secSkill;
  std::vector<std::pair<uint8_t, uint8_t>> defaultCre;
  std::string smallPor;
  std::string largePor;
  HeroSetSpec spec;
};

struct CastleHeroSet {
  std::vector<HeroSetI> heros = {
      {// orrin
       .index = 0,
       .clasz = 0,
       .female = false,
       .secSkill = {{0, 0}},
       .defaultCre = {{0, 0}},
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               .id = 0,
               .subId = 0,
               .val = 0,
           }},
      {// valeska
       .index = 1,
       .clasz = 0,
       .female = false,
       .secSkill = {{0, 0}},
       .defaultCre = {{0, 0}},
       .smallPor = "",
       .largePor = "",
       .spec =
           {
               .id = 0,
               .subId = 0,
               .val = 0,
           }},
  };
};