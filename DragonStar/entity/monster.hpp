// ================================================================
//
// monster.hpp
//
// Class for enemy monsters.
//
// ================================================================

#pragma once

class Command;

enum class MonsterID;
enum class Element;
enum class EquipType;

#include <memory>
#include <unordered_map>
#include "actor.hpp"
#include "../core/saveFile.hpp"
#include "../data/monsterData.hpp"
#include "../data/statMod.hpp"

typedef std::unique_ptr<Command> CommandPtr;

enum class AIState {
	Undefined = 0,
	Sleeping,
	Idle,
	Chasing,
	Alert
};

class Monster : public Actor {
public:
	Monster(size_t index);
	Monster(MonsterID id, size_t index);
	Monster(MonsterID id, sf::Vector2i spawnLocation, size_t index);
	Monster(ActorSave& actorSave, size_t index);

	// Sets the monster's properties based on the given ID.
	void Initialize(MonsterID id);

	// Calculates what command this monster should take.
	CommandPtr CalcAI();

	// Returns the monster ID for this monster.
	MonsterID GetMonsterID();

	// Returns true if the monster is unique.
	bool IsUnique();

	int GetWeaponHitChance();
	int GetAttackRange();
	int GetAttackSpeed();
	Element GetAttackElement();
	int GetWeaponDamageMultiplier();

	int GetEXPReward();
	int GetGoldDrop();
	int GetLootPoints();

private:
	int getBaseStat(StatModType statModType);
	std::vector<StatMod>& getBaseStatMods();
	
	// List of all monster types.
	static std::unordered_map<MonsterID, MonsterData> monsterList;

	// monster info
	MonsterID monsterID{};
	MonsterData* monsterData = nullptr;
	AIState aiState{};
	int chaseTurnsRemaining = 0;
};