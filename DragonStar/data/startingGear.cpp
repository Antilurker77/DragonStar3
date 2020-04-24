// ================================================================
//
// startingGear.cpp
// 
// Contains list of starting gear packages.
//
// ================================================================

#include "../ui/inventory.hpp"

#include "id/itemID.hpp"
#include "id/starterID.hpp"

static std::unordered_map<StarterID, std::pair<int, std::vector<ItemID>>> initStarterList() {
	std::unordered_map<StarterID, std::pair<int, std::vector<ItemID>>> list;

	list[StarterID::Warrior] = {
		100,
		{
			ItemID::TomeCombatBasics,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::TravelerBlade,
			ItemID::IronArmor
		}
	};

	list[StarterID::Archer] = {
		100,
		{
			ItemID::TomeLearningArchery,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::TrainingBow,
			ItemID::LeatherArmor
		}
	};

	list[StarterID::Sorcerer] = {
		100,
		{
			ItemID::TomeMagicForBeginners,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::RunedStick,
			ItemID::SilkRobes
		}
	};

	list[StarterID::Priest] = {
		100,
		{
			ItemID::TomeIntroductionToSpirituality,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::RunedStick,
			ItemID::SilkRobes
		}
	};

	list[StarterID::Merchant] = {
		250,
		{
			ItemID::Rations,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::Rations,
			ItemID::SilkRobes,
			ItemID::LeatherBoots
		}
	};

	return list;
}

std::unordered_map<StarterID, std::pair<int, std::vector<ItemID>>> Inventory::starterList = initStarterList();