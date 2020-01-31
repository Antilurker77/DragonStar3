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

	// test worm spam for ai bug
	//{1, 100, 1000, {
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000},
	//	{MonsterID::Worm, 1000}
	//}}

	{1,	100, 1000, {
		{MonsterID::GiantRat, 1000}
	}},

	{1,	100, 300, {
		{MonsterID::GiantRat, 1000},
		{MonsterID::GiantRat, 1000}
	}},

	{1,	100, 750, {
		{MonsterID::GreenSlime, 1000}
	}},

	{1,	100, 1000, {
		{MonsterID::Worm, 1000},
		{MonsterID::Worm, 1000},
		{MonsterID::Worm, 500},
		{MonsterID::Worm, 500},
		{MonsterID::Worm, 500}
	}},

	{1,	100, 500, {
		{MonsterID::KoboldMiner, 1000},
		{MonsterID::KoboldMiner, 750},
		{MonsterID::KoboldMiner, 750}
	}},

	{1, 100, 800, {
		{MonsterID::KoboldScout, 1000},
		{MonsterID::KoboldMiner, 500}
	}},

	{1, 100, 700, {
		{MonsterID::KoboldGeomancer, 1000}
	}},

	{1, 100, 800, {
		{MonsterID::KoboldCrossbowman, 1000}
	}},

	{1, 100, 1000, {
		{MonsterID::ArcaneSentry, 1000}
	}},

	{2, 100, 1000, {
		{MonsterID::LesserFlameblade, 1000}
	}},
};

std::vector<Encounter> DungeonScene::uniqueEncounterTable = {
	// MinDepth, MaxDepth, Weight, Monsters{ID, Chance}
	{1, 100, 1000, {
		{MonsterID::Fenrok, 1000}
	}}
};