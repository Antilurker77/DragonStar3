// ================================================================
//
// records.hpp
// 
// Global object that stores information about the players's
// current playthrough.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class AuraID;
enum class ItemID;
enum class MonsterID;

#include <string>
#include <unordered_map>
#include <vector>

struct Identity {
	std::string Label;
	ItemID ItemID{};
	bool Identified = false;
};

class Record {
public:
	Record();

	// Sets the kill counts and found artifacts.
	void Load(std::vector<int>& artifacts, std::vector<int>& slain, std::vector<int>& count);

	// Sets identified items. Must be done after dungeon generation.
	void LoadIdentities(std::vector<int> identifiedItems);

	// Randomizes the identifaction tables based on the given seed.
	void RandomizeIdentities(uint64_t seed);

	// Returns true if the item is identified.
	bool IsIdentified(ItemID id);

	// Returns true if the player has slain this monster at least once.
	bool HasKilled(MonsterID id);

	// Returns how many of each monster has been slain.
	std::unordered_map<MonsterID, int> GetKillCounts();

	// Returns which artifacts have been spawned.
	std::vector<ItemID> GetSpawnedArtifacts();

	// Returns which items have been identified.
	std::vector<ItemID> GetIdentifiedItems();

	// Returns the label for an item.
	std::string GetLabel(ItemID id);

	// Identifies the givem item.
	void Identify(ItemID id);

	// Returns true if the artifact has spawned before.
	bool SeenArtifact(ItemID id);

	// Marks the monster as killed.
	void MarkKilled(MonsterID id);

	// Marks the artifact as spawned.
	void MarkSpawnedArtifact(ItemID id);

private:
	static std::vector<std::string> potionColors;
	static std::vector<ItemID> potionList;

	std::vector<Identity> potionIdentities;

	std::vector<ItemID> spawnedArtifacts;

	std::unordered_map<MonsterID, int> killCount;
};

extern Record records;
