// ================================================================
//
// aura.hpp
// 
// Class for an individual instance of an aura (status effect).
//
// ================================================================

#pragma once

class Actor;
class DungeonScene;

enum class AuraID;
enum class EventType;

#include <string>
#include <vector>
#include <unordered_map>
#include "auraData.hpp"
#include "../core/combat.hpp"

class Aura {
public:
	Aura();
	Aura(AuraID id, int rank, int ssDamage, int ssCritChance, int ssResPen, Actor* user, size_t userIndex);
	Aura(AuraID, int rank, int duration, int nextTick, int stacks, int ssDamage, int ssCritChance, int ssResPen, size_t userIndex);

	// Sets the ID of this aura.
	void Initialize(AuraID id);

	// Sets the owner pointer.
	void SetOwnerPointer(DungeonScene* dungeonScene);

	// Returns the source actor of this aura.
	Actor* GetSource();

	// Ticks down the duration of the aura.
	void Tick(Actor* owner);

	// Fires of procs. Amount will be bloated by 1000.
	void OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount);

	// Adds a stack if possible, and refreshes the aura to it's max duration.
	void Refresh(Actor* newSource, size_t newSourceIndex, int rank, int ssDamage, int ssCritChance, int ssResPen);

	// Removes a stack of this aura.
	void RemoveStack();

	// Tells this aura if it was activated or not.
	void WasUsed(bool used);

	// Returns the index for the owner of this aura.
	size_t GetSourceIndex();

	// Returns the current duration of the aura.
	int GetCurrentDuration();

	// Returns when the next tick of the aura will happen.
	int GetNextTick();

	// Returns the number of stacks this aura has.
	int GetCurrentStackSize();

	// Returns the current snapshot damage value.
	int GetSnapshotDamage();

	// Returns the current snapshot crit chance value.
	int GetSnapshotCritChance();

	// Returns the current snapshot resistance penetration value.
	int GetSnapshotResistancePen();

	// Returns true if the aura's stack count is 0.
	bool IsExpired(Actor* owner);

	// Returns the name of this aura, including it's rank.
	std::string GetName();

	// Returns the description of this aura.
	std::string GetDescription();

	// Returns the full filepath of the aura's icon.
	std::string GetIcon();

	// Returns the aura ID.
	AuraID GetAuraID();

	// Returns the rank of the aura.
	int GetRank();

	// Returns true if the buff has a duration.
	bool HasDuration();

	// Returns true if the aura is a buff.
	bool IsBuff();

	// Returns true if the aura is unique.
	bool IsUnique();

	// Returns true if the aura is unique by actor.
	bool IsUniqueByActor();

	// Returns true if the aura is a resting aura.
	bool IsRest();

	// Returns true if the aura stuns.
	bool IsStun();

	// Returns true if the aura disarms.
	bool IsDisarm();

	// Returns the stat mods for this aura.
	std::vector<StatMod> GetStatMods();

private:
	EventOptions getEventOptions();

	static std::unordered_map<AuraID, AuraData> auraList;

	AuraID auraID{};
	AuraData* auraData = nullptr;
	Actor* source = nullptr;
	size_t sourceIndex = 0;
	int currentRank = 0;
	int currentDuration = 0;
	int nextTick = 0;
	int currentStacks = 0;
	bool wasUsed = false;

	int snapshotDamage = 1000;
	int snapshotCritChance = 0;
	int snapshotResistancePen = 0;
};
