// ================================================================
//
// monsterData.hpp
// 
// Struct that holds data for a monster.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class Element;
enum class EquipType;
enum class MonsterID;

struct AIAction;

#include <functional>
#include <string>
#include <vector>
#include "knownAbility.hpp"
#include "statMod.hpp"
#include "../entity/monster.hpp"

struct MonsterData {
	std::string Name = "Unknown Name";
	std::string Title = "Unknown Title";
	std::string Filename = "unknown.png";

	bool IsUnique = false;
	bool IsBoss = false;
	bool CanSwim = false;
	bool CanFly = false;
	bool CanTunnel = false;

	bool IsStationary = false;
	int ChaseTurns = 0;

	int Level = 1;

	int BaseHP = 0;
	int BaseMP = 0;
	int BaseSP = 0;

	int BaseSTR = 0;
	int BaseDEX = 0;
	int BaseMAG = 0;
	int BaseVIT = 0;
	int BaseSPI = 0;

	int BaseArmor = 0;
	int BaseMagicArmor = 0;
	int BaseEvasion = 0;

	int BaseAttackPower = 0;
	int BaseSpellPower = 0;

	int BaseHitChance = 0;
	int BaseAttackRange = 100;
	int BaseAttackSpeed = 100;
	int BaseWeaponDamageMultiplier = 1000;
	Element AttackElement{};
	EquipType AttackType{};

	int BaseLineOfSight = 100;
	int BaseMoveCost = 100;

	int EXPDrop = 0;
	int GoldDrop = 0;
	int LootDrop = 0;

	std::vector<StatMod> StatMods;
	std::vector<KnownAbility> Abilities;

	std::function<void(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t amount)> OnEvent;
	std::function<AIAction(Actor* monster, DungeonScene* dungeonScene)> AI;
};