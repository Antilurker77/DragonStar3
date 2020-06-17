// ================================================================
//
// groundEffectData.hpp
// 
// Struct that holds data for a ground effect.
//
// ================================================================

#pragma once

enum class Category;
enum class Element;
enum class EventType;
enum class GroundEffectID;

class Actor;
class GroundEffect;
struct EventOptions;

#include <functional>
#include <string>
#include <vector>
#include "statMod.hpp"
#include "../core/combat.hpp"

struct GroundEffectData {
	std::string Name = "Unknown Ground Effect";
	GroundEffectID GroundEffectID{};

	std::vector<Category> Categories;
	std::vector<Element> Elements;

	int MaxRank = 4;

	std::vector<int> Duration{}; // 0 = Unlimited Duration
	int TickRate = 100;

	std::vector<std::vector<int>> Values{};
	std::vector<std::vector<StatMod>> StatMods{};

	bool IsBuff = false;

	bool IsStun = false;
	bool IsDisarm = false;
	bool IsSilence = false;

	bool CanCrit = false;
	std::vector<int> BonusArmorPen;
	std::vector<int> BonusResistancePen;
	std::vector<int> BonusCritChance;
	std::vector<int> BonusCritPower;
	std::vector<int> BonusDoubleStrikeChance;
	std::vector<int> BonusHPLeech;
	std::vector<int> BonusMPLeech;
	std::vector<int> BonusSPLeech;

	std::function<std::string(Actor* user, EventOptions& eventOptions, int rank, GroundEffect* aura)> GetDescription;
	std::function<void(Actor* user, Actor* target, EventOptions& eventOptions, int rank, GroundEffect* aura)> OnTick; // Called when the ground effect ticks.
	std::function<void(Actor* user, Actor* target, EventOptions& eventOptions, int rank, GroundEffect* aura)> OnExpiry; // Called when the ground effect expires.
	std::function<void(EventType eventType, EventOptions& geOptions, int rank, GroundEffect* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount)> OnEvent;
};
