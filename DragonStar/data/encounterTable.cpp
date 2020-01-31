// ================================================================
//
// encounterTable.cpp
//
// ================================================================

#include "../scene/dungeonScene.hpp"

#include "id/monsterID.hpp"

std::vector<Encounter> DungeonScene::encounterTable = {
	// MinDepth, MaxDepth, Weight, Monsters{ID, Chance}
	{std::numeric_limits<int>::min(),	0, 1000, {
		{MonsterID::TargetDummy, 1000}, 
		{MonsterID::TargetDummy,  500}
	}},

	{1,	5, 1000, {
		{MonsterID::GiantRat, 1000}
	}},

	{1,	10, 300, {
		{MonsterID::GiantRat, 1000},
		{MonsterID::GiantRat, 1000}
	}},

	{1, 5, 1000, {
		{MonsterID::CaveBat, 1000}
	}},

	{1, 5, 1000, {
		{MonsterID::WorkerAnt, 1000}
	}},

	{1,	5, 750, {
		{MonsterID::GreenSlime, 1000}
	}},

	{1, 5, 500, {
		{MonsterID::Jackal, 1000},
		{MonsterID::Jackal, 1000},
		{MonsterID::Jackal, 1000}
	}},

	{1,	3, 1000, {
		{MonsterID::Worm, 1000},
		{MonsterID::Worm, 1000},
		{MonsterID::Worm, 500},
		{MonsterID::Worm, 500},
		{MonsterID::Worm, 500}
	}},

	{2,	10, 500, {
		{MonsterID::KoboldMiner, 1000},
		{MonsterID::KoboldMiner, 750}
	}},

	{2, 100, 800, {
		{MonsterID::KoboldScout, 1000},
		{MonsterID::KoboldMiner, 500}
	}},

	{2, 10, 700, {
		{MonsterID::KoboldGeomancer, 1000}
	}},

	{2, 10, 800, {
		{MonsterID::KoboldCrossbowman, 1000}
	}},

	{3, 10, 1000, {
		{MonsterID::ArcaneSentry, 1000}
	}},

	{3, 10, 500, {
		{MonsterID::Imp, 1000}
	}},

	{4, 10, 1000, {
		{MonsterID::LesserFlameblade, 1000}
	}},
};

std::vector<Encounter> DungeonScene::uniqueEncounterTable = {
	// MinDepth, MaxDepth, Weight, Monsters{ID, Chance}
	{1, 100, 1000, {
		{MonsterID::Fenrok, 1000}
	}}
};