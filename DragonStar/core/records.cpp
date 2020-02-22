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
	"Green",
	"Orange",
	"Purple",
	"Pink",
	"White",
	"Black"
};

std::vector<ItemID> Record::potionList = {
	ItemID::PotionFruitJuice,
	ItemID::PotionMinorHealing,
	ItemID::PotionMinorMana,
	ItemID::PotionSpeed,
	ItemID::PotionStamina
};

std::vector<std::string> Record::scrollNames = {
	"Adalis",
	"Bethion",
	"Censa",
	"Leanore",
	"Luminar"

};

std::vector<ItemID> Record::scrollList = {
	ItemID::ScrollIdentify,
	ItemID::ScrollPhaseDoor,
	ItemID::ScrollSpellProtection,
	ItemID::ScrollTeleport
};

Record::Record() {

}

void Record::Load(std::vector<int>& artifacts, std::vector<int>& slain, std::vector<int>& count) {
	spawnedArtifacts.clear();
	spawnedArtifacts.reserve(artifacts.size());
	for (auto id : artifacts) {
		spawnedArtifacts.push_back(static_cast<ItemID>(id));
	}
	
	killCount.clear();
	for (size_t i = 0; i < slain.size(); i++) {
		killCount[static_cast<MonsterID>(slain[i])] = count[i];
	}
}

void Record::LoadIdentities(std::vector<int> identifiedItems) {
	for (auto& id : potionIdentities) {
		int itemID = static_cast<int>(id.ItemID);
		if (std::find(identifiedItems.begin(), identifiedItems.end(), itemID) != identifiedItems.end()) {
			id.Identified = true;
		}
		else {
			id.Identified = false;
		}
	}
	for (auto& id : scrollIdentities) {
		int itemID = static_cast<int>(id.ItemID);
		if (std::find(identifiedItems.begin(), identifiedItems.end(), itemID) != identifiedItems.end()) {
			id.Identified = true;
		}
		else {
			id.Identified = false;
		}
	}
}

void Record::RandomizeIdentities(uint64_t seed) {
	std::mt19937_64 mt(seed);
	
	// Potions
	potionIdentities.clear();
	potionIdentities.reserve(potionList.size());
	std::vector<std::string> colors = potionColors;
	for (size_t i = 0; i < potionList.size(); i++) {
		size_t choosenColorIndex = Random::RandomSizeT(0, colors.size() - 1 - i, mt);
		std::string color = colors[choosenColorIndex];
		std::swap(colors.back(), colors[choosenColorIndex]);
		potionIdentities.push_back(Identity{ color, potionList[i], false });
	}

	// Scrolls
	scrollIdentities.clear();
	scrollIdentities.reserve(scrollList.size());
	std::vector<std::string> names = scrollNames;
	for (size_t i = 0; i < scrollList.size(); i++) {
		size_t choosenNameIndex = Random::RandomSizeT(0, names.size() - 1 - i, mt);
		std::string name = names[choosenNameIndex];
		std::swap(names.back(), names[choosenNameIndex]);
		scrollIdentities.push_back(Identity{ name, scrollList[i], false });
	}
}

bool Record::IsIdentified(ItemID id) {
	// Potions
	for (auto& i : potionIdentities) {
		if (i.ItemID == id) {
			return i.Identified;
		}
	}

	// Scrolls
	for (auto& i : scrollIdentities) {
		if (i.ItemID == id) {
			return i.Identified;
		}
	}

	return false;
}

bool Record::HasKilled(MonsterID id) {
	return killCount[id] > 0;
}

std::unordered_map<MonsterID, int> Record::GetKillCounts() {
	return killCount;
}

std::vector<ItemID> Record::GetSpawnedArtifacts() {
	return spawnedArtifacts;
}

std::vector<ItemID> Record::GetIdentifiedItems() {
	std::vector<ItemID> result;

	for (auto& id : potionIdentities) {
		if (id.Identified) {
			result.push_back(id.ItemID);
		}
	}

	for (auto& id : scrollIdentities) {
		if (id.Identified) {
			result.push_back(id.ItemID);
		}
	}

	return result;
}

std::string Record::GetLabel(ItemID id) {
	for (auto& i : potionIdentities) {
		if (i.ItemID == id) {
			return i.Label;
		}
	}
	for (auto& i : scrollIdentities) {
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
	for (auto& i : scrollIdentities) {
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