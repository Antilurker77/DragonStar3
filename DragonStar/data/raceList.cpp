// ================================================================
//
// raceList.cpp
//
// ================================================================

#include "../entity/player.hpp"

#include <iostream>
#include "id/abilityID.hpp"
#include "id/raceID.hpp"

static std::unordered_map<RaceID, RaceData> initList() {
	std::unordered_map<RaceID, RaceData> list;

	list[RaceID::Human] = [] {
		RaceData rd;

		rd.Name = "Human";
		rd.Filename = "human";

		rd.BaseHP = 50;
		rd.BaseMP = 20;
		rd.BaseSP = 100;

		rd.BaseSTR = 10;
		rd.BaseDEX = 10;
		rd.BaseMAG = 10;
		rd.BaseVIT = 10;
		rd.BaseSPI = 10;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();
	list[RaceID::Elf] = [] {
		RaceData rd;

		rd.Name = "Elf";
		rd.Filename = "elf";

		rd.BaseHP = 35;
		rd.BaseMP = 32;
		rd.BaseSP = 80;

		rd.BaseSTR = 6;
		rd.BaseDEX = 11;
		rd.BaseMAG = 14;
		rd.BaseVIT = 6;
		rd.BaseSPI = 12;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();
	list[RaceID::ShadowElf] = [] {
		RaceData rd;

		rd.Name = "Shadow Elf";
		rd.Filename = "shadow_elf";

		rd.BaseHP = 45;
		rd.BaseMP = 22;
		rd.BaseSP = 100;

		rd.BaseSTR = 9;
		rd.BaseDEX = 14;
		rd.BaseMAG = 8;
		rd.BaseVIT = 10;
		rd.BaseSPI = 9;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();
	list[RaceID::StoneDwarf] = [] {
		RaceData rd;

		rd.Name = "Stone Dwarf";
		rd.Filename = "stone_dwarf";

		rd.BaseHP = 70;
		rd.BaseMP = 10;
		rd.BaseSP = 110;

		rd.BaseSTR = 12;
		rd.BaseDEX = 9;
		rd.BaseMAG = 9;
		rd.BaseVIT = 14;
		rd.BaseSPI = 6;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();
	list[RaceID::Draconian] = [] {
		RaceData rd;

		rd.Name = "Draconian";
		rd.Filename = "draconian";

		rd.BaseHP = 60;
		rd.BaseMP = 16;
		rd.BaseSP = 120;

		rd.BaseSTR = 14;
		rd.BaseDEX = 7;
		rd.BaseMAG = 10;
		rd.BaseVIT = 12;
		rd.BaseSPI = 7;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();
	list[RaceID::Vulpine] = [] {
		RaceData rd;

		rd.Name = "Vulpine";
		rd.Filename = "vulpine";

		rd.BaseHP = 40;
		rd.BaseMP = 30;
		rd.BaseSP = 100;

		rd.BaseSTR = 7;
		rd.BaseDEX = 11;
		rd.BaseMAG = 12;
		rd.BaseVIT = 8;
		rd.BaseSPI = 14;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();
	list[RaceID::Anubian] = [] {
		RaceData rd;

		rd.Name = "Anubian";
		rd.Filename = "anubian";

		rd.BaseHP = 60;
		rd.BaseMP = 30;
		rd.BaseSP = 130;

		rd.BaseSTR = 6;
		rd.BaseDEX = 6;
		rd.BaseMAG = 6;
		rd.BaseVIT = 11;
		rd.BaseSPI = 11;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();
	list[RaceID::Runetouched] = [] {
		RaceData rd;

		rd.Name = "Runetouched";
		rd.Filename = "runetouched";

		rd.BaseHP = 55;
		rd.BaseMP = 24;
		rd.BaseSP = 90;

		rd.BaseSTR = 12;
		rd.BaseDEX = 7;
		rd.BaseMAG = 12;
		rd.BaseVIT = 11;
		rd.BaseSPI = 11;

		rd.BaseLineOfSight = 350;
		rd.BaseMoveCost = 100;

		rd.StatMods = {};
		rd.Abilities = {};

		return rd;
	}();

	return list;
}

std::unordered_map<RaceID, RaceData> Player::raceList = initList();