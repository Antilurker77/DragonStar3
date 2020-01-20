// ================================================================
//
// ability.hpp
// 
// Class for an individual instance of an ability.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class EventType;

class Actor;

#include <unordered_map>
#include "abilityData.hpp"

class Ability {
public:
	Ability();
	Ability(AbilityID id, int rank);

	// Sets the ID of this ability.
	void Initialize(AbilityID id);

	// Returns true if the ability is unitialized.
	bool IsNull();

	// Reduces cooldown by 1 tick.
	void DecrementCooldown();

	// Returns the current rank of the ability. 0 = Ability Rank 1
	int GetCurrentRank();

	// Returns the max rank of the ability. 4 = Max Rank 5
	int GetMaxRank();

	// Increases the rank of the ability.
	void IncreaseRank();

	// Returns true if the ability is usable.
	// Checks resource costs, cooldowns, stuns, ect.
	bool IsUsable(Actor* user);

	// Returns true if this ability is passive.
	bool IsPassive();

	// Returns the remaining cooldown of the ability.
	int GetCurrentCooldown();

	// Returns the range of the ability. 100 Range = 1 Tile
	int GetRangeValue(Actor* user);

	// Returns true if the ability is a projectile.
	bool IsProjectile();

	// Returns true if the ability ignores line of sight.
	bool IgnoreLineOfSight();

	// Returns true if the ability is a spell.
	bool IsSpell();

	// Returns the range area of the ability.
	std::vector<sf::Vector2i> GetRange(Actor* user, DungeonScene* dungeonScene);

	// Returns the range area of the ability as if the user was standing in the given location.
	std::vector<sf::Vector2i> GetRange(Actor* user, DungeonScene* dungeonScene, sf::Vector2i location);

	// Returns the target area based on the cursor for the ability.
	std::vector<sf::Vector2i> GetTargetArea(sf::Vector2i cursor, Actor* user, DungeonScene* dungeonScene);

	// Returns the extra area based on the cursor for the ability.
	std::vector<sf::Vector2i> GetExtraArea(sf::Vector2i cursor, Actor* user, DungeonScene* dungeonScene);

	// Executes the ability.
	void Execute(Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& area);

	// Triggers procs. Amount will be bloated by 1000.
	void OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount);

	// Returns the current ID of the ability.
	AbilityID GetAbilityID();

	// Returns the name of the current ability.
	std::string GetName();

	// Returns the icon of the current ability.
	std::string GetIcon();

	// Returns the use time of the ability.
	// If user is nullptr, will return -1 (meaning weapon speed).
	int GetUseTime(Actor* user);

	// Returns the base cooldown of the ability.
	int GetCooldown(Actor* user);

	// Returns the MP cost of the ability.
	int GetMPCost();

	// Returns the SP cost of the ability.
	int GetSPCost();

	// Returns the passive bonuses of the abilites.
	std::vector<StatMod> GetStatMods();

	// Returns the description of the ability. If actor is nullptr, ratios will be listed instead of damage estimates.
	std::string GetDescription(Actor* user);

private:
	// Builds an EventOpions object based on the ability's paramaters.
	EventOptions getEventOptions();

	// Executes a double strike.
	void doubleStrike(Actor* user, Actor* target);

	// List of abilities in the game.
	static std::unordered_map<AbilityID, AbilityData> abilityList;

	// Event option list for a double strike trigger.
	static EventOptions doubleStrikeEO;

	AbilityID abilityID{};
	AbilityData* abilityData = nullptr;
	int currentRank = 0;
	int remainingCooldown = 0;
	int charges = 0;
};
