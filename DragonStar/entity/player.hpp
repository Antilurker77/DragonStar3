// ================================================================
//
// player.hpp
//
// Class for the player character.
//
// ================================================================

#pragma once

enum class RaceID;

class Inventory;
struct InventorySlot;

#include "actor.hpp"

#include <array>
#include <unordered_map>
#include "../core/saveFile.hpp"
#include "../data/item.hpp"
#include "../data/raceData.hpp"

class Player : public Actor {
public:
	Player();
	Player(ActorSave& actorSave, PlayerSave& playerSave);

	// Initializes the race for the player.
	void Initialize(RaceID id);

	// Returns the race ID for the player.
	RaceID GetRaceID();

	// Attempts to equip an item. Automatically picks the correct slot based
	// on the item type. For rings, equips to empty slots first. Otherwise,
	// replace ring in the first slot.
	void Equip(InventorySlot& inventorySlot);

	// Attempts to equip an item in the selected slot. If the item is equipped
	// it will swap the argument with the replaced item.
	void Equip(Item& item, size_t index);

	// Unequips the item in the designated slot.
	Item Unequip(size_t index);

	// Unequips the item in the given index and places it into the inventory.
	// If inventory is full, nothing will happen.
	// Returns true if the item was unequipped, false if it wasn't.
	bool Unequip(Inventory& inventory, size_t index);

	// Awards exp to the player. Will level up if the player has accumulated enough EXP.
	void AwardEXP(int amount);

	// Spends 1 ability point to learn an ability, or upgrade to the next rank if already known.
	void LearnAbility(AbilityID id);

	// Spends 1 stat point to increase a main attribute by 1.
	// Attributes are STR, DEX, MAG, VIT, SPI.
	void SpendStatPoint(StatModType attribute);

	void OnEvent(EventType eventType, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount);

	EquipType GetWeaponEquipType();
	int GetWeaponHitChance();
	int GetAttackRange();
	int GetAttackSpeed();
	Element GetAttackElement();
	int GetWeaponDamageMultiplier();

	int GetEXPReward();
	int GetLootPoints();

	// Gets the equipment the character is wearing.
	std::array<Item, 10>& GetEquipment();

	// Returns true if the equipment slot has nothing in it.
	bool IsEquipmentSlotEmpty(size_t index);

	// Returns the current amount of expierence points.
	int GetCurrentEXP();

	// Returns the amount of expierence points required to reach
	// the next level.
	int GetNextLevelEXP();

	// Returns the number of stat points the player has.
	int GetStatPoints();

	// Returns the number of ability points the player has.
	int GetAbilityPoints();

private:
	int getBaseStat(StatModType statModType);
	std::vector<StatMod>& getBaseStatMods();
	int getStatFromEquipment(int base, StatModType statModType, EventOptions& eventOptions);

	// Sets up the sprites for equipment. Should always be called after changing equipment.
	void setEquipmentSprites();

	static std::unordered_map<RaceID, RaceData> raceList;

	RaceID raceID{};
	std::string raceName = "Unknown Race";

	bool isFemale = true;

	int exp = 0;
	int statPoints = 0;
	int abilityPoints = 0;

	// Strength, Dexterity, Magic, Vitality, Spirit
	std::array<int, 5> bonusPoints = { 0, 0, 0, 0, 0 };

	// Equipment
	// Slot 0: Main-Hand
	// Slot 1: Off-Hand
	// Slot 2: Head
	// Slot 3: Body
	// Slot 4: Hands
	// Slot 5: Feet
	// Slot 6: Neck
	// Slot 7: Ring 1
	// Slot 8: Ring 2
	// Slot 9: Light Source
	std::array<Item, 10> equipment;
};
