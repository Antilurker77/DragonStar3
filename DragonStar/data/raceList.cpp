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

	return list;
}

std::unordered_map<RaceID, RaceData> Player::raceList = initList();