// ================================================================
//
// raceData.hpp
// 
// Struct that holds data for a player race.
//
// ================================================================

#pragma once

enum class AbilityID;

#include <functional>
#include <string>
#include <vector>
#include "knownAbility.hpp"
#include "statMod.hpp"

struct RaceData {
	std::string Name = "Unknown Race";
	std::string Filename = "human";

	int BaseHP = 0;
	int BaseMP = 0;
	int BaseSP = 0;

	int BaseSTR = 0;
	int BaseDEX = 0;
	int BaseMAG = 0;
	int BaseVIT = 0;
	int BaseSPI = 0;

	int BaseLineOfSight = 350;
	int BaseMoveCost = 100;

	std::vector<StatMod> StatMods{};
	std::vector<KnownAbility> Abilities{};
};