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

	{1,	5, 1000, {
		{MonsterID::BrownSnake, 1000}
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

	{2,	6, 500, {
		{MonsterID::KoboldMiner, 1000},
		{MonsterID::KoboldMiner, 750}
	}},

	{2, 6, 800, {
		{MonsterID::KoboldScout, 1000},
		{MonsterID::KoboldMiner, 500}
	}},

	{2, 6, 700, {
		{MonsterID::KoboldGeomancer, 1000}
	}},

	{2, 6, 800, {
		{MonsterID::KoboldCrossbowman, 1000}
	}},

	{3, 10, 1000, {
		{MonsterID::ArcaneSentry, 1000}
	}},

	{3, 10, 500, {
		{MonsterID::Imp, 1000}
	}},

	{4,	11, 1000, {
		{MonsterID::Cobra, 1000}
	}},

	{4, 10, 1000, {
		{MonsterID::LesserFlameblade, 1000}
	}},

	{5,	12, 1000, {
		{MonsterID::FireAnt, 1000}
	}},

	{5,	12, 750, {
		{MonsterID::BlueSlime, 1000}
	}},

	{5, 15, 600, {
		{MonsterID::Wolf, 1000},
		{MonsterID::Wolf, 1000},
		{MonsterID::Wolf, 1000},
		{MonsterID::Wolf, 500}
	}},

	{6,	14, 1000, {
		{MonsterID::GoblinWarrior, 1000}
	}},

	{6,	14, 600, {
		{MonsterID::GoblinWizard, 1000}
	}},

	{6,	14, 500, {
		{MonsterID::BrownBear, 1000}
	}},

	{6,	14, 500, {
		{MonsterID::DemonEye, 1000}
	}},

	{7, 15, 1000, {
		{MonsterID::VenomousRat, 1000},
		{MonsterID::VenomousRat, 500},
		{MonsterID::VenomousRat, 500}
	}},

	{7, 15, 750, {
		{MonsterID::WaterMare, 1000}
	}},

	{8, 15, 1000, {
		{MonsterID::Tiger, 1000}
	}},

	{8, 16, 333, {
		{MonsterID::Trickster, 1000}
	}},

	// Should never be seen by player.
	{101, std::numeric_limits<int>::max(), 1000, {
		{MonsterID::TargetDummy, 1000},
		{MonsterID::TargetDummy,  500}
	}}
};

std::vector<Encounter> DungeonScene::uniqueEncounterTable = {
	// MinDepth, MaxDepth, Weight, Monsters{ID, Chance}
	{2, 100, 1000, {
		{MonsterID::Fenrok, 1000}
	}},

	{3, 100, 1000, {
		{MonsterID::Norgash, 1000},
		{MonsterID::KoboldCrossbowman, 1000},
		{MonsterID::KoboldGeomancer, 1000}
	}},

	{3, 100, 1000, {
		{MonsterID::Tergar, 1000}
	}},

	{4, 100, 1000, {
		{MonsterID::Luther, 1000}
	}},

	{5, 100, 1000, {
		{MonsterID::Incindia, 1000},
		{MonsterID::LesserFlameblade, 1000},
		{MonsterID::LesserFlameblade, 1000}
	}},

	{8, 100, 1000, {
		{MonsterID::RatKing, 1000},
		{MonsterID::VenomousRat, 1000},
		{MonsterID::VenomousRat, 1000},
		{MonsterID::GiantRat, 1000},
		{MonsterID::GiantRat, 1000},
		{MonsterID::GiantRat, 1000},
		{MonsterID::GiantRat, 1000},
		{MonsterID::GiantRat, 1000},
		{MonsterID::GiantRat, 1000}
	}},

	{8, 100, 1000, {
		{MonsterID::Marbix, 1000},
		{MonsterID::GoblinWarrior, 1000},
		{MonsterID::GoblinWarrior, 1000},
		{MonsterID::GoblinWizard, 1000}
	}}
};