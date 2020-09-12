// ================================================================
//
// saveFile.hpp
// 
// Global struct that stores save file information.
//
// ================================================================

#pragma once

#include <string>
#include <vector>
#include <cereal/types/array.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

struct ItemSave {
	int ItemID;
	int Rarity;
	int StackSize;
	std::vector<int> StatModTypes;
	std::vector<int> StatModElements;
	std::vector<int> StatModValues;
	std::string RandArtName;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(
			ItemID,
			Rarity,
			StackSize,
			StatModTypes,
			StatModElements,
			StatModValues,
			RandArtName
		);
	}
};

struct LootSave {
	int XLocation;
	int YLocation;
	int Gold;
	std::vector<ItemSave> Items;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(
			XLocation,
			YLocation,
			Gold,
			Items
		);
	}
};

struct GroundEffectSave {
	int XLocation;
	int YLocation;
	int GroundEffectID;
	size_t SourceIndex;
	int CurrentDuration;
	int NextTick;
	int Rank;
	int SSDamage;
	int SSCritChance;
	int SSResPen;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(
			XLocation,
			YLocation,
			GroundEffectID,
			SourceIndex,
			CurrentDuration,
			NextTick,
			Rank,
			SSDamage,
			SSCritChance,
			SSResPen
		);
	}
};

struct ActorSave {
	int MonsterID = 0; // undefined for player
	int AIState = 0; // undefined for player
	int AIChaseTurns = 0; // undefined for player
	size_t EncounterIndex;
	int CurrentHP;
	int CurrentMP;
	int CurrentSP;
	int Exhaustion;
	int XLocation;
	int YLocation;

	std::array<int, 16> Flags;

	std::vector<int> AbilityCooldowns;
	std::vector<int> AbilityCharges;

	std::vector<int> AuraIDs;
	std::vector<int> AuraRanks;
	std::vector<int> AuraDurations;
	std::vector<int> AuraNextTicks;
	std::vector<int> AuraStacks;
	std::vector<int> AuraSSDamage;
	std::vector<int> AuraSSCritChance;
	std::vector<int> AuraSSResPen;
	std::vector<size_t> AuraSource;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(
			MonsterID,
			AIState,
			AIChaseTurns,
			EncounterIndex,
			CurrentHP,
			CurrentMP,
			CurrentSP,
			Exhaustion,
			XLocation,
			YLocation,
			Flags,
			AbilityCooldowns,
			AbilityCharges,
			AuraIDs,
			AuraRanks,
			AuraDurations,
			AuraNextTicks,
			AuraStacks,
			AuraSSDamage,
			AuraSSCritChance,
			AuraSSResPen,
			AuraSource
		);
	}
};

struct PlayerSave {
	std::string PlayerName;
	int RaceID;
	int PlayerLevel;
	int PlayerEXP;
	int StatPoints;
	int AbilityPoints;
	std::array<int, 5> BonusPoints;

	std::vector<int> Abilities;
	std::vector<int> AbilityRanks;

	std::array<ItemSave, 10> Equipment;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(
			PlayerName,
			RaceID,
			PlayerLevel,
			PlayerEXP,
			StatPoints,
			AbilityPoints,
			BonusPoints,
			Abilities,
			AbilityRanks,
			Equipment
		);
	}
};

struct SaveFile {
	int CurrentFloor;
	uint64_t Seed;

	std::vector<std::vector<int>> Vision;

	std::vector<LootSave> Loot;

	std::vector<GroundEffectSave> GroundEffects;

	std::vector<std::array<ItemSave, 24>> ShopItems;

	std::vector<int> SpawnedArtifacts;
	std::vector<int> IdentifiedItems;
	std::vector<int> SlainMonsters;
	std::vector<int> SlainMonsterCount;

	PlayerSave Player;
	std::vector<ActorSave> Actors;

	int PlayerGold;
	std::array<ItemSave, 40> Inventory;

	std::array<int, 24> ShortcutAbilities;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(
			Player,
			CurrentFloor,
			Seed,
			Vision,
			Loot,
			GroundEffects,
			ShopItems,
			SpawnedArtifacts,
			IdentifiedItems,
			SlainMonsters,
			SlainMonsterCount,
			Actors,
			PlayerGold,
			Inventory,
			ShortcutAbilities
		);
	}
};

//extern SaveFile saveFile;