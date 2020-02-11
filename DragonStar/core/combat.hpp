// ================================================================
//
// combat.hpp
// 
// Set of functions for handling combat actions and their results.
//
// ================================================================

#pragma once

class Actor;
class DungeonScene;

enum class AbilityID;
enum class AuraID;
enum class Category;
enum class Element;

#include <string>
#include <unordered_map>
#include <vector>

// Enum for what healing is restoring.
enum class AttributeType {
	Undefined,
	HP,
	MP,
	SP
};

// Struct that stores options for combat events.
struct EventOptions {
	std::string EventName = "Unknown Event";
	
	AbilityID AbilityID{};
	AuraID AuraID{};

	std::vector<Category> Categories{};
	std::vector<Element> Elements{};

	bool CanDodge = false;
	bool CanBlock = false;
	bool CanCounter = false;
	bool CanCrit = false;
	bool CanDoubleStrike = false;

	int BaseHitChance = 0;
	int BonusArmorPen = 0;
	int BonusResistancePen = 0;
	int BonusCritChance = 0;
	int BonusCritPower = 0;
	int BonusDoubleStrikeChance = 0;
	int BonusHPLeech = 0;
	int BonusMPLeech = 0;
	int BonusSPLeech = 0;

	int SnapshotDamage = 0;
	int SnapshotCritChance = 0;
	int SnapshotResistancePen = 0;
};

// Struct that stores the results of a combat event.
struct EventResult {
	int TotalDamage = 0; // cache for simplicity
	int TotalHealing = 0;

	bool DidEvent = false;
	bool DidHit = false;
	bool DidBlock = false;
	bool DidCrit = false;
	bool DidDoubleStrike = false;
	bool DidCounter = false;
	bool DidKill = false;
};

namespace Combat {
	// Deals attack damage that scales with attack power.
	// 1 Coefficient = 0.1% Power Multiplier
	EventResult AttackDamage(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient);

	// Deals attack damage that scales with attack power. Damage is multiplied by the weapon's damage multiplier. Used the user's weapon element if no element is specified.
	// 1 Coefficient = 0.1% Power Multiplier
	EventResult SkillDamage(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient);

	// Deals spell damage that scales with spell power.
	// 1 Coefficient = 0.1% Power Multiplier
	EventResult SpellDamage(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient);

	// Heals that scales with spell power.
	// 1 Coefficient = 0.1& Heal Multiplier
	EventResult SpellHeal(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient, AttributeType healingType);

	// Deals a fixed amount of damage.
	EventResult FixedDamage(Actor* user, Actor* target, EventOptions& eventOptions, int amount);

	// Heals the target for a specific amount.
	EventResult FixedHeal(Actor* user, Actor* target, EventOptions& eventOptions, int amount, AttributeType healingType);

	// Adds a stack of the specified aura to the target.
	void AddAuraStack(Actor* user, Actor* target, AuraID id, int rank);

	// Removes a stack of the specified aura, if possible.
	void RemoveAuraStack(Actor* target, AuraID id);

	// Gives an estimate of how much damage an attack would do.
	int AttackDamageEstimate(Actor* user, EventOptions& eventOptions, int coefficient);

	// Gives an estimate of how much damage a skill would do.
	int SkillDamageEstimate(Actor* user, EventOptions& eventOptions, int coefficient);

	// Gives an estimate of how much damage a spell would do.
	int SpellDamageEstimate(Actor* user, EventOptions& eventOptions, int coefficient);

	// Gives an estimate of how much healing a skill would do.
	int SpellHealEstimate(Actor* user, EventOptions& eventOptions, int coefficient);

	// Awards prizes from defeated monsters and triggers OnDeath events.
	void AwardPrizes(Actor* user, Actor* target, EventOptions& eventOptions);
}