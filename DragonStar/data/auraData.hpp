// ================================================================
//
// auraData.hpp
// 
// Struct that holds data for an ability.
//
// ================================================================

#pragma once

enum class AuraID;
enum class Category;
enum class Element;
enum class EventType;

class Actor;
class Aura;
struct EventOptions;

#include <functional>
#include <string>
#include <vector>
#include "statMod.hpp"
#include "../core/combat.hpp"

struct AuraData {
	std::string Name = "Unknown Aura";
	std::string Icon = "unknown.png";
	AuraID AuraID{};

	std::vector<Category> Categories{};
	std::vector<Element> Elements{};

	int MaxRank = 4;

	std::vector<int> BaseDuration;
	std::vector<int> MaxDuration; // 0 = Unlimited Duration
	std::vector<int> MaxStacks;
	int TickRate = 100; // Time in between ticks.

	std::vector<std::vector<int>> Values;
	std::vector<std::vector<StatMod>> StatMods;

	bool IsBuff = false; // If true, aura is considered a positive effect (buff). Mostly for UI purposes.
	bool Unique = false; // If true, only one copy of this aura can be applied to an actor.
	bool UniqueByActor = false; // If true, each actor can apply one copy of this aura to an actor.
	bool ConsumeOnUse = false; // If true, the aura will lose a stack when one of it's stat mods is used in a combat calculation.
	bool StacksExpireOneByOne = false; // If true, the aura will lose one stack instead of all of them when an aura expires.
	bool MultiplyStatModsByStacks = false; // If true, the value of stat mods will be multiplied by the number of stacks.

	bool IsRest = false;
	bool IsStun = false;
	bool IsDisarm = false;
	bool IsSilence = false;
	bool IsSnare = false;

	bool CanCrit = false;
	std::vector<int> BonusArmorPen;
	std::vector<int> BonusResistancePen;
	std::vector<int> BonusCritChance;
	std::vector<int> BonusCritPower;
	std::vector<int> BonusDoubleStrikeChance;
	std::vector<int> BonusHPLeech;
	std::vector<int> BonusMPLeech;
	std::vector<int> BonusSPLeech;

	std::function<std::string(Actor* user, EventOptions& eventOptions, int rank, Aura* aura)> GetDescription;
	std::function<void(Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura)> OnApplication; // Called when the aura is applied.
	std::function<void(Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura)> OnTick; // Called when the aura ticks.
	std::function<void(Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura)> OnExpiry; // Called when a stack of the aura is lost.
	std::function<void(EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount)> OnEvent;
};