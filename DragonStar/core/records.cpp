// ================================================================
//
// records.cpp
//
// ================================================================

#include "records.hpp"

#include <random>
#include "random.hpp"
#include "../data/id/itemID.hpp"

Record records;

std::vector<std::string> Record::potionColors = {
	"Red",
	"Blue",
	"Yellow",
	"Green"
};

std::vector<ItemID> Record::potionList = {
	ItemID::PotionFruitJuice,
	ItemID::PotionMinorHealing
};

Record::Record() {

}

void Record::RandomizeIdentities(uint64_t seed) {
	std::mt19937_64 mt(seed);
	
	// Potions
	potionIdentities.clear();
	potionIdentities.reserve(potionList.size());
	std::vector<std::string> colors = potionColors;
	for (size_t i = 0; i < potionList.size(); i++) {
		size_t choosenColorIndex = Random::RandomSizeT(0, colors.size() - 1 - i);
		std::string color = colors[choosenColorIndex];
		std::swap(colors.back(), colors[choosenColorIndex]);
		potionIdentities.push_back(Identity{ color, potionList[i], false });
	}
}

bool Record::IsIdentified(ItemID id) {
	for (auto& i : potionIdentities) {
		if (i.ItemID == id) {
			return i.Identified;
		}
	}

	return false;
}

bool Record::HasKilled(MonsterID id) {
	return killCount[id] > 0;
}

std::string Record::GetLabel(ItemID id) {
	for (auto& i : potionIdentities) {
		if (i.ItemID == id) {
			return i.Label;
		}
	}

	return "";
}

void Record::Identify(ItemID id) {
	for (auto& i : potionIdentities) {
		if (i.ItemID == id) {
			i.Identified = true;
			return;
		}
	}
}

bool Record::SeenArtifact(ItemID id) {
	return std::find(spawnedArtifacts.begin(), spawnedArtifacts.end(), id) != spawnedArtifacts.end();
}

void Record::MarkKilled(MonsterID id) {
	killCount[id]++;
}

void Record::MarkSpawnedArtifact(ItemID id) {
	spawnedArtifacts.push_back(id);
}