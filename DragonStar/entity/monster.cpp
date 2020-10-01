// ================================================================
//
// monster.cpp
//
// ================================================================

#include "monster.hpp"

#include "../command/abilityCommand.hpp"
#include "../command/moveCommand.hpp"
#include "../command/waitCommand.hpp"
#include "../core/random.hpp"
#include "../core/settings.hpp"
#include "../core/tileMath.hpp"
#include "../data/id/category.hpp"
#include "../data/id/element.hpp"
#include "../data/id/equipType.hpp"
//#include "../data/id/monsterID.hpp"
#include "../scene/dungeonScene.hpp"

Monster::Monster(size_t index) {
	this->index = index;
}

Monster::Monster(MonsterID id, size_t index) {
	this->index = index;
	Initialize(id);
}

Monster::Monster(MonsterID id, sf::Vector2i spawnLocation, size_t index, size_t encounterIndex) {
	this->index = index;
	this->encounterIndex = encounterIndex;
	Initialize(id);
	Warp(spawnLocation);
}

Monster::Monster(ActorSave& actorSave, size_t index) {
	this->index = index;
	encounterIndex = actorSave.EncounterIndex;
	Initialize(static_cast<MonsterID>(actorSave.MonsterID));
	Warp(sf::Vector2i(actorSave.XLocation, actorSave.YLocation));

	currentHP = actorSave.CurrentHP;
	currentMP = actorSave.CurrentMP;
	currentSP = actorSave.CurrentSP;
	exhaustion = actorSave.Exhaustion;

	flags = actorSave.Flags;

	aiState = static_cast<AIState>(actorSave.AIState);
	chaseTurnsRemaining = actorSave.AIChaseTurns;

	for (size_t i = 0; i < abilities.size(); i++) {
		abilities[i].SetCooldownAndCharges(actorSave.AbilityCooldowns[i], actorSave.AbilityCharges[i]);
	}

	auras.clear();
	auras.reserve(actorSave.AuraIDs.size());
	for (size_t i = 0; i < actorSave.AuraIDs.size(); i++) {
		Aura aura(static_cast<AuraID>(actorSave.AuraIDs[i]), actorSave.AuraRanks[i], actorSave.AuraDurations[i], actorSave.AuraNextTicks[i], actorSave.AuraStacks[i], actorSave.AuraSSDamage[i], actorSave.AuraSSCritChance[i], actorSave.AuraSSResPen[i], actorSave.AuraSource[i]);
		auras.push_back(aura);
	}

	actorHUD.UpdateElements(*this);
}

std::string Monster::GetTitle() {
	if (monsterData != nullptr) {
		return monsterData->Title;
	}
	return "";
}

void Monster::Initialize(MonsterID id) {
	monsterID = id;
	monsterData = &monsterList[monsterID];
	
	// AI State, Default to Sleep
	aiState = AIState::Sleeping;

	// Name
	name = monsterData->Name;

	// Level
	level = monsterData->Level;

	// Attributes
	currentHP = GetMaxHP();
	currentMP = GetMaxMP();
	currentSP = GetMaxSP();

	// Abilities
	abilities.reserve(size_t(1) + monsterData->Abilities.size());
	abilities.push_back(Ability(AbilityID(1), 0));
	for (auto ab : monsterData->Abilities) {
		abilities.push_back(Ability(ab.AbilityID, ab.Rank));
	}

	// Monster sprite.
	sf::Sprite s;
	std::string filepath = "gfx/" + settings.Tileset + "/actor/monster/";
	filepath += monsterData->IsUnique ? "unique/" : "common/";
	filepath += monsterData->Filename;
	s.setTexture(*assetManager.LoadTexture(filepath));
	sprites.push_back(s);
}

CommandPtr Monster::CalcAI() {
	CommandPtr result = std::make_unique<WaitCommand>(100);
	bool seePlayer = false;

	// Wait if player is dead.
	if (!dungeonScene->GetPlayer()->IsAlive()) {
		return result;
	}

	// Check if monster can see player.
	std::vector<sf::Vector2i> losTest = TileMath::AreaOfEffect(location, GetSightRadius());
	std::vector<sf::Vector2i> los;
	los.reserve(losTest.size());
	for (auto& t : losTest) {
		if (dungeonScene->InLineOfSight(location, t)) {
			los.emplace_back(t);
		}
	}
	if (!los.empty()) {
		Actor* player = dungeonScene->GetPlayer();
		sf::Vector2i playerLoc = player->GetLocation();
		if (std::find(los.begin(), los.end(), playerLoc) != los.end()) {
			seePlayer = true;
		}
	}

	// If sleeping or idle, check line of sight. If player is visable, awaken.
	if (aiState != AIState::Alert) {
		if (seePlayer) {
			if (aiState == AIState::Sleeping) {
				messageLog.AddMessage("#monster " + name + " #default woke up.");
			}
			dungeonScene->AlertGroup(encounterIndex);
			aiState = AIState::Alert;
		}
	}

	if (aiState == AIState::Alert) {
		if (!seePlayer) {
			if (monsterList[monsterID].ChaseTurns > 0) {
				aiState = AIState::Chasing;
				chaseTurnsRemaining = monsterData->ChaseTurns;
			}
			else {
				aiState = AIState::Idle;
				messageLog.AddMessage("#monster " + name + " #default lost the player.");
			}
		}
		else {
			AIAction ai = monsterData->AI(this, dungeonScene);

			// No AbilityID means the monster wants to move.
			if (ai.Ability == static_cast<AbilityID>(0)) {
				if (ai.Target != location) {
					// If the tile is occupied, look for the next closest tile.
					bool searching = true;
					int searchRange = 0;
					while (searching && searchRange < 250) {
						std::vector<sf::Vector2i> tiles = TileMath::AreaOfEffect(ai.Target, searchRange);
						std::vector<sf::Vector2i> walkable{};
						walkable.reserve(tiles.size());
						for (auto& t : tiles) {
							if (dungeonScene->IsWalkable(this, t) && !dungeonScene->IsOccupiedByActor(t)) {
								walkable.emplace_back(t);
							}
						}
						sf::Vector2i goal = ai.Target;
						for (auto& t : walkable) {
							int cheapest = std::numeric_limits<int>::max();
							std::vector<sf::Vector2i> path = dungeonScene->Pathfind(location, t, this);
							if (!path.empty()) {
								int cost = dungeonScene->GetPathCost(path);
								if (cost < cheapest) {
									cost = cheapest;
									goal = path.front();
									searching = false;
								}
							}
						}
						// Didn't find pathable tile, increase search range.
						if (searching) {
							if (searchRange == 0) {
								searchRange = 100; // Search range of 50 doesn't add new tiles, so skip to 100.
							}
							else {
								searchRange += 50;
							}
						}
						else {
							ai.Target = goal;
						}
					}

					// If increased search range and didn't find tile, wait instead.
					if (searching) {
						result = std::make_unique<WaitCommand>(100);
					}
					else {
						result = std::make_unique<MoveCommand>(*dungeonScene, ai.Target);
					}
				}
			}
			// Monster wants to use an ability.
			else {
				Ability* ability = GetAbility(ai.Ability);
				std::vector<sf::Vector2i> range = ability->GetRange(this, dungeonScene);

				// First check if monster is already in range.
				bool inRange = false;
				for (auto& t : range) {
					std::vector<sf::Vector2i> aoe = ability->GetTargetArea(t, this, dungeonScene);
					auto i = std::find_if(aoe.begin(), aoe.end(), [&](const sf::Vector2i& testLoc) { return testLoc == ai.Target; });
					if (i != aoe.end()) {
						sf::Vector2i targetTile = *i;
						// Projectile Test
						if (ability->IsProjectile()) {
							sf::Vector2i impactPoint = dungeonScene->GetProjectileImpactTile(location, targetTile, false);
							if (targetTile == impactPoint) {
								ai.Target = targetTile;
								inRange = true;
								break;
							}
						}
						else {
							ai.Target = targetTile;
							inRange = true;
							break;
						}
					}
				}

				// In range, make the command.
				if (inRange) {
					result = std::make_unique<AbilityCommand>(dungeonScene, ai.Ability, ai.Target);
					if (ai.FlagIndex < flags.size()) {
						flags[ai.FlagIndex] = ai.FlagValue;
					}
				}
				// Not in range, path monster to get closer to the target.
				else {
					std::vector<sf::Vector2i> testRange = ability->GetRange(this, dungeonScene, ai.Target);
					int cheapest = std::numeric_limits<int>::max();
					bool searching = true;
					for (auto& t : testRange) {
						if (!ability->IgnoreLineOfSight()) {
							if (!dungeonScene->InLineOfSight(ai.Target, t)) {
								continue; // If ability requires line of sight, don't check pathfinding to tiles the monster can't path to.
							}
						}
						std::vector<sf::Vector2i> path = dungeonScene->Pathfind(location, t, this);
						if (!path.empty()) {
							int cost = dungeonScene->GetPathCost(path);
							if (cost < cheapest) {
								ai.Target = path.front();
								cheapest = cost;
								searching = false;
							}
						}
					}

					// Can't get in range, move closer to the target.
					// Using Heuristic Distance instead of normal pathfinding for performance, may go back on this later.
					if (searching) {
						int distance = dungeonScene->GetHeuristicDistance(location, ai.Target, false);
						//sf::Vector2i closest = ai.second;
						sf::Vector2i closest = location;
						std::vector<sf::Vector2i> neighboors = TileMath::Neighboors(location);
						std::vector<sf::Vector2i> walkable{};
						walkable.reserve(neighboors.size());
						for (auto& t : neighboors) {
							if (dungeonScene->IsWalkable(this, t) && !dungeonScene->IsOccupiedByActor(t)) {
								walkable.push_back(t);
							}
						}
						for (auto& t : walkable) {
							int checkDistance = dungeonScene->GetHeuristicDistance(location, t, false);
							if (checkDistance < distance) {
								closest = t;
								distance = checkDistance;
							}
						}
						ai.Target = closest;
					}

					// Move if better location was found, wait if otherwise.
					// Stationary monsters always wait.
					if (ai.Target == location || monsterData->IsStationary) {
						result = std::make_unique<WaitCommand>(25);
					}
					else {
						result = std::make_unique<MoveCommand>(*dungeonScene, ai.Target);
					}
				}
			}
		}
	}

	// Attempt to chase the player and get them in line of sight again.
	if (aiState == AIState::Chasing) {
		if (chaseTurnsRemaining > 0) {
			chaseTurnsRemaining--;

			Actor* player = dungeonScene->GetPlayer();
			sf::Vector2i playerLoc = player->GetLocation();

			std::vector<sf::Vector2i> tilesInLineOfSight = TileMath::AreaOfEffect(playerLoc, GetSightRadius());
			std::vector<sf::Vector2i> tilesToCheck;
			tilesToCheck.reserve(tilesInLineOfSight.size());
			for (auto& t : tilesInLineOfSight) {
				if (dungeonScene->InLineOfSight(t, playerLoc)) {
					if (dungeonScene->IsWalkable(this, t) && !dungeonScene->IsOccupiedByActor(t)) {
						tilesToCheck.push_back(t);
					}
				}
			}
			tilesToCheck.shrink_to_fit();

			int cheapest = std::numeric_limits<int>::max();
			sf::Vector2i monPosition = GetLocation();
			sf::Vector2i destination(-1, -1);
			for (auto& t : tilesToCheck) {
				auto path = dungeonScene->Pathfind(monPosition, t);
				if (!path.empty()) {
					int cost = dungeonScene->GetPathCost(path);
					if (cost < cheapest) {
						cheapest = cost;
						destination = path.front();
					}
				}
			}
			// If the monster fails to find a tile it can move to, don't move.
			// Stationary monsters do not move.
			if (destination.x != -1 && !monsterData->IsStationary) {
				result = std::make_unique<MoveCommand>(*dungeonScene, destination);
			}
		}
		// Failed to catch player, go into idle mode.
		else {
			aiState = AIState::Idle;
			messageLog.AddMessage("#monster " + name + " #default lost the player.");
		}
	}

	// Awake but player not in sight, wander around.
	if (aiState == AIState::Idle) {
		std::vector<sf::Vector2i> neighboors = TileMath::Neighboors(location);
		std::vector<sf::Vector2i> walkable{};
		walkable.reserve(neighboors.size());
		for (auto& t : neighboors) {
			if (dungeonScene->IsWalkable(this, t) && !dungeonScene->IsOccupiedByActor(t)) {
				walkable.emplace_back(t);
			}
		}
		if (!walkable.empty() && !monsterData->IsStationary) {
			sf::Vector2i destination = walkable[Random::RandomSizeT(0, walkable.size() - 1)];
			result = std::make_unique<MoveCommand>(*dungeonScene, destination);
		}
		else {
			result = std::make_unique<WaitCommand>(50);
		}
	}

	return result;
}

MonsterID Monster::GetMonsterID() {
	return monsterID;
}

size_t Monster::GetEncounterIndex() {
	return encounterIndex;
}

AIState Monster::GetAIState() {
	return aiState;
}

int Monster::GetAIChaseTurns() {
	return chaseTurnsRemaining;
}

bool Monster::IsUnique() {
	return monsterData->IsUnique;
}

void Monster::Alert() {
	if (aiState == AIState::Sleeping) {
		messageLog.AddMessage("#monster " + GetName() + " #default woke up.");
	}
	
	aiState = AIState::Chasing;
	chaseTurnsRemaining = monsterData->ChaseTurns;
}

int Monster::GetWeaponHitChance() {
	return monsterData->BaseHitChance;
}

int Monster::GetAttackRange() {
	return monsterData->BaseAttackRange;
}

int Monster::GetAttackSpeed() {
	return monsterData->BaseAttackSpeed;
}

Element Monster::GetAttackElement() {
	return monsterData->AttackElement;
}

Category Monster::GetAttackCategory() {
	Category category = Category::Unarmed;

	if (monsterData != nullptr) {
		switch (monsterData->AttackType) {
		case EquipType::Sword:
			category = Category::Sword;
			break;
		case EquipType::Axe:
			category = Category::Axe;
			break;
		case EquipType::Mace:
			category = Category::Mace;
			break;
		case EquipType::Dagger:
			category = Category::Dagger;
			break;
		case EquipType::Spear:
			category = Category::Spear;
			break;
		case EquipType::Bow:
			category = Category::Bow;
			break;
		case EquipType::Wand:
			category = Category::Wand;
			break;
		case EquipType::Staff:
			category = Category::Staff;
			break;
		default:
			break;
		}
	}

	return category;
}

int Monster::GetWeaponDamageMultiplier() {
	return monsterData->BaseWeaponDamageMultiplier;
}

int Monster::GetEXPReward() {
	return monsterData->EXPDrop;
}

int Monster::GetGoldDrop() {
	return monsterData->GoldDrop;
}

int Monster::GetLootPoints() {
	return monsterData->LootDrop;
}

int Monster::getBaseStat(StatModType statModType) {
	int result = 0;

	switch (statModType) {
	case StatModType::HP:
		result = monsterData->BaseHP;
		break;
	case StatModType::MP:
		result = monsterData->BaseMP;
		break;
	case StatModType::SP:
		result = monsterData->BaseSP;
		break;
	case StatModType::STR:
		result = monsterData->BaseSTR;
		break;
	case StatModType::DEX:
		result = monsterData->BaseDEX;
		break;
	case StatModType::MAG:
		result = monsterData->BaseMAG;
		break;
	case StatModType::VIT:
		result = monsterData->BaseVIT;
		break;
	case StatModType::SPI:
		result = monsterData->BaseSPI;
		break;
	case StatModType::Armor:
		result = monsterData->BaseArmor;
		break;
	case StatModType::MagicArmor:
		result = monsterData->BaseMagicArmor;
		break;
	case StatModType::Evasion:
		result = monsterData->BaseEvasion;
		break;
	case StatModType::AttackPower:
		result = monsterData->BaseAttackPower;
		break;
	case StatModType::SpellPower:
		result = monsterData->BaseSpellPower;
		break;
	case StatModType::SightRadius:
		result = monsterData->BaseLineOfSight;
		break;
	case StatModType::MovementSpeed:
		result = monsterData->BaseMoveCost;
		break;
	default:
		break;
	}

	return result;
}

std::vector<StatMod>& Monster::getBaseStatMods() {
	return monsterData->StatMods;
}