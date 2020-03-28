// ================================================================
//
// item.hpp
// 
// Class for all items, including consumables and equipment.
//
// ================================================================

#pragma once

class Actor;

#include <string>
#include <unordered_map>
#include <SFML/System.hpp>
#include "ability.hpp"
#include "itemData.hpp"
#include "statMod.hpp"
#include "../core/saveFile.hpp"

enum class Element;
enum class EquipType;
enum class EventType;
enum class ItemID;
enum class Rarity;

struct ItemWeight {
	int MinItemLevel = 0;
	int MaxItemLevel = 0;
	int Weight = 1000;
	ItemID ItemID{};
};

struct AffixWeight {
	int MinItemLevel = 0;
	int Weight = 1000;
	StatModType StatMod{};
	int MinValue = 0;
	int MaxValue = 0;
};

class Item {
public:
	Item();
	Item(ItemID id);
	Item(ItemSave& itemSave);

	// Sets the item's properties based on the given ID.
	void Initialize(ItemID id);

	// Initializes the item as a random item.
	void InitRandomItem(int itemLevel);

	// Initializes the item as a random poition.
	void InitPotion(int itemLevel);

	// Initializes the item as a random scroll.
	void InitScroll(int itemLevel);

	// Initializes the item as a random tome.
	void InitTome(int itemLevel);

	// Initializes the item as a random piece of equipment.
	void InitEquipment(int itemLevel);
	
	// Uses the item.
	void UseItem(Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& area);

	// Triggers procs. Amount will be bloated by 1000.
	void OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount);

	// Returns true if the item has no ID.
	bool IsNull();

	// Returns the ID of the item.
	ItemID GetItemID();

	// Returns the item rarity of the item.
	Rarity GetRarity();

	// Returns the item type of the item.
	ItemType GetItemType();

	// Returns the max stack size of the item.
	int GetMaxStackSize();

	// Returns the ability that is invoked when this ability is used. Returns a nullptr if no ability is assigned.
	Ability* GetInvokedAbility();

	// Returns the ability IDs of the abilities that can be taught. Should only be used for tomes.
	std::vector<AbilityID>& GetTeachableAbilities();

	// Returns the name of the item.
	std::string GetName();

	// Returns the file name of the texture used for inventory icons.
	std::string GetIconFilePath();

	// Returns the file name of the texture for drawing equipment on characters.
	std::string GetEquipFilePath();

	// Returns true if hair should be hidden while this item is equipped. Should only be used for helm equipment.
	bool HideHair();

	// Returns the gold value of the item.
	int GetValue();

	// Returns the equipment type of the item. Should only be used for equipment.
	EquipType GetEquipType();

	// Returns true if the item is a weapon.
	bool IsWeapon();

	// Returns true if the weapon is two-handed, based on the equip type. Should only be used for weapons.
	bool IsTwoHanded();

	// Returns the elemental type of the item. Should only be used for weapons.
	Element GetAttackElement();

	// Returns the base hit chance of the item. Should only be used for weapons, scrolls, and rods.
	int GetHitChance();

	// Returns the attack range of the weapon. Should only be used for weapons.
	int GetAttackRange();

	// Returns the base attack speed of the weapon. Should only be used for weapons.
	int GetAttackSpeed();

	// Return the weapon damage multiplier of the item. Should only be used for weapons.
	int GetWeaponDamageMultiplier();

	// Returns the stat mods of the item. Should only be used for equipment.
	std::vector<StatMod> GetStatMods();

	// Returns all implicit stat mods of the item. Should only be used for equipment.
	std::vector<StatMod>& GetImplicitStatMods();

	// Returns all explicit stat mods of the item. Should only be used for equipment.
	std::vector<StatMod>& GetExplicitStatMods();

	// Returns all the generated stat mods of the item. Should only be used for equipment.
	std::vector<StatMod>& GetRandomStatMods();

	// Returns all the bonus mod strings for artifacts. Should only be used for artifact equipment.
	std::vector<std::string>& GetBonusModStrings();

private:
	// List of all items.
	static std::unordered_map<ItemID, ItemData> itemList;

	// Item generation weights.
	static std::vector<std::pair<ItemType, int>> itemTypeWeights;
	static std::vector<std::pair<EquipType, int>> equipTypeWeights;
	static std::vector<std::pair<Rarity, int>> rarityWeights;
	static std::unordered_map<EquipType, std::vector<ItemWeight>> baseTypeWeights;
	static std::unordered_map<EquipType, std::vector<ItemWeight>> artifactWeights;
	static std::unordered_map<EquipType, std::vector<AffixWeight>> affixWeights;

	static std::vector<ItemWeight> potionWeights;
	static std::vector<ItemWeight> scrollWeights;
	static std::vector<ItemWeight> tomeWeights;

	Ability invokedAbility;
	ItemID itemID{};
	ItemData* itemData = nullptr;
	Rarity rarity{};
	std::vector<StatMod> randomStatMods;
};