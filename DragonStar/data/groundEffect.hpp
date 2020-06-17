// ================================================================
//
// groundEffect.hpp
// 
// Class for an individual instance of an ground effect.
//
// ================================================================

#pragma once

class Actor;
class DungeonScene;

enum class EventType;
enum class GroundEffectID;

#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/System.hpp>
#include "groundEffectData.hpp"
#include "../core/combat.hpp"

class GroundEffect {
public:
	GroundEffect();
	GroundEffect(GroundEffectID id, int rank, sf::Vector2i location, int ssDamage, int ssCritChance, int ssResPen, Actor* user, size_t userIndex);

	// Sets the ground effect ID and data for this ground effect.
	void Initialize(GroundEffectID id);

	// Sets the owner pointer.
	void SetOwnerPointer(DungeonScene* dungeonScene);

	// Returns the source actor of this ground effect.
	Actor* GetSource();

	// Ticks down the duration of this ground effect.
	void Tick(Actor* owner);

	// Returns true if the ground effect has expired.
	bool IsExpired();

	// Fires of procs. Amount will be bloated by 1000.
	void OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount);

	// Returns the index for the owner of this ground effect.
	size_t GetSourceIndex();

	// Returns the current duration of the ground effect.
	int GetCurrentDuration();

	// Returns when the next tick of the ground effect will happen.
	int GetNextTick();

	// Returns the location of the ground effect.
	sf::Vector2i GetLocation();

	// Returns the current snapshot damage value.
	int GetSnapshotDamage();

	// Returns the current snapshot crit chance value.
	int GetSnapshotCritChance();

	// Returns the current snapshot resistance penetration value.
	int GetSnapshotResistancePen();

	// Returns the name of the ground effect.
	std::string GetName();

	// Returns the description of this ground effect.
	std::string GetDescription();

	// Returns the ground effect ID.
	GroundEffectID GetGroundEffectID();

	// Returns the rank of the ground effect.
	int GetRank();

	// Returns true if the ground effect has a duration.
	bool HasDuration();

	// Returns true if the ground effect is a buff.
	bool IsBuff();

	// Returns true if the ground effect stuns.
	bool IsStun();

	// Returns true if the ground effect disarms.
	bool IsDisarm();

	// Returns true if the ground effect silences.
	bool IsSilence();

	// Returns the stat mods for this ground effect.
	std::vector<StatMod> GetStatMods();

private:
	// Builds and returns event options.
	EventOptions getEventOptions();

	static std::unordered_map<GroundEffectID, GroundEffectData> groundEffectList;

	GroundEffectID groundEffectID{};
	GroundEffectData* groundEffectData = nullptr;
	Actor* source = nullptr;
	size_t sourceIndex = 0;
	sf::Vector2i location = { -1, -1 };
	int currentRank = 0;
	int currentDuration = 0;
	int nextTick = 0;

	int snapshotDamage = 1000;
	int snapshotCritChance = 0;
	int snapshotResistancePen = 0;
};


