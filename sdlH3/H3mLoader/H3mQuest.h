#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

enum class ESeerHutRewardType : uint8_t
{
	NOTHING = 0,
	EXPERIENCE = 1,
	MANA_POINTS = 2,
	MORALE = 3,
	LUCK = 4,
	RESOURCES = 5,
	PRIMARY_SKILL = 6,
	SECONDARY_SKILL = 7,
	ARTIFACT = 8,
	SPELL = 9,
	CREATURE = 10,
};

enum class EQuestMission {
	NONE = 0,
	LEVEL = 1,
	PRIMARY_SKILL = 2,
	KILL_HERO = 3,
	KILL_CREATURE = 4,
	ARTIFACT = 5,
	ARMY = 6,
	RESOURCES = 7,
	HERO = 8,
	PLAYER = 9,
	HOTA_MULTI = 10,
	// end of H3 missions

	KEYMASTER = 11,
	HOTA_HERO_CLASS = 12,
	HOTA_REACH_DATE = 13,
	HOTA_GAME_DIFFICULTY = 13,
};

struct H3mQuest{
    uint8_t missionId;
    uint8_t primary[4];
    uint32_t heroLevel;
    uint32_t killTarget;
    std::vector<uint8_t> artifacts;
    std::vector<std::pair<uint16_t, uint16_t>> creatures;
    uint32_t resources[7];
    uint8_t hero;
    uint8_t player;

    uint32_t lastDay;
    std::string firstVisitText;
    std::string nextVisitText;
    std::string completedText;
};