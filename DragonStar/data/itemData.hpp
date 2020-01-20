// ================================================================
//
// itemData.hpp
// 
// Struct that holds data for an item.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class Category;
enum class Element;
enum class EquipType;
enum class EventType;
enum class ItemID;

enum class ItemType {
	Undefined,
	Potion,
	Scroll,
	Rod,
	Tome,
	Consumable,
	Equipment
};

class Actor;

#include <functional>
#include <string>
#include <vector>

#include "statMod.hpp"

struct ItemData {
	std::string Name = "Unknown Item";
	std::string IconFilePath = "";
	std::string EquipFilePath = "";

	bool HideHair = false; // Only checked for helms.

	ItemID ItemID{};
	ItemType ItemType{};

	AbilityID InvokeAbility{}; // Triggers a given ability at rank 0(1) when used. Has no effect on equipment.

	int MaxStacks = 1;

	int BaseValue = 0;

	bool Artifact = false;
	bool TwoHanded = false;
	EquipType EquipType{};
	Element AttackElement{};
	int HitChance = 0;
	int AttackRange = 0;
	int AttackSpeed = 0;
	int WeaponDamageMultiplier = 0;

	std::vector<AbilityID> TeachableAbilities{};

	std::vector<StatMod> ImplicitStatMods;
	std::vector<StatMod> ExplicitStatMods;
	std::vector<std::string> BonusModStrings;

	std::function<void(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount)> OnEvent;
};
