// ================================================================
//
// abilityData.hpp
// 
// Struct that holds data for an ability.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class Category;
enum class Element;
enum class EquipType;
enum class EventType;

class Ability;
class Actor;
class DungeonScene;

#include <functional>
#include <string>
#include <vector>
#include "SFML/System.hpp"
#include "statMod.hpp"
#include "../core/combat.hpp"

struct AbilityData {
	std::string Name = "Unknown Ability";
	std::string Icon = "unknown.png";
	AbilityID ID{};

	std::vector<Category> Categories;
	std::vector<Element> Elements;
	std::vector<EquipType> RequiredWeaponTypes; // if empty, no weapon type is required

	bool IsPassive = false;
	int MaxRank = 4;

	std::vector<int> Range; // -1 value = use weapon range
	std::vector<int> UseTime; // -1 value = use weapon speed
	std::vector<int> Cooldown;
	std::vector<int> MaxCharges;
	std::vector<int> HPCost;
	std::vector<int> MPCost;
	std::vector<int> SPCost;

	std::vector<std::vector<int>> Values; // stores values like attack/spell power coeffecient or other values that should scale with rank
	std::vector<std::vector<StatMod>> PassiveBonuses;

	bool CanDodge = false;
	bool CanBlock = false;
	bool CanCounter = true;
	bool CanCrit = true;
	bool CanDoubleStrike = false;

	std::vector<int> HitChance; // -1 value = use weapon accuracy
	std::vector<int> BonusArmorPen;
	std::vector<int> BonusResistancePen;
	std::vector<int> BonusCritChance;
	std::vector<int> BonusCritPower;
	std::vector<int> BonusDoubleStrikeChance;
	std::vector<int> BonusHPLeech;
	std::vector<int> BonusMPLeech;
	std::vector<int> BonusSPLeech;

	bool FixedRange = false;
	bool HideRange = false;

	bool IsProjectile = false;
	bool IgnoreLineOfSight = false;

	bool AreaIgnoreLineOfSight = false;
	bool AreaIgnoreBodyBlock = false;

	std::function<std::vector<sf::Vector2i>(Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank)> GetTargetArea;
	std::function<std::vector<sf::Vector2i>(Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank)> GetExtraArea;
	std::function<bool()> CustomUseCondition;
	std::function<std::string(Actor* user, EventOptions& eventOptions, int rank)> GetDescription;
	std::function<void(Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank)> Execute;
	std::function<void(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability)> OnEvent;
};