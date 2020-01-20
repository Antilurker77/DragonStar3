// ================================================================
//
// loot.hpp
//
// Class that represents items on the ground.
//
// ================================================================

#pragma once

class Inventory;

#include <vector>
#include "entity.hpp"
#include "../data/item.hpp"

class Loot : public Entity {
public:
	Loot(sf::Vector2i spawnPosition, int goldAmount);
	Loot(sf::Vector2i spawnPosition, std::vector<Item> droppedItems);
	Loot(sf::Vector2i spawnPosition, int goldAmount, std::vector<Item> droppedItems);

	// Returns the tile location of this loot pile.
	sf::Vector2i GetLocation();

	// Returns the amount of gold in this loot pile.
	int GetGold();

	// Returns the items in this loot pile.
	std::vector<Item>& GetItems();

	// Returns true if the loot pile is empty.
	bool IsEmpty();

	// Adds gold to the current pile.
	void AddGold(int amount);

	// Adds items to the current pile.
	void AddItems(std::vector<Item>& itemsToAdd);

	// Transfers gold from the lootpile to the player's inventory.
	void LootGold(Inventory& inventory);

	// Transfers an item from the lootpile to the player's inventory as long as it isn't full.
	void LootItem(Inventory& inventory, size_t index);

private:
	// Determines what graphic should be displayed while on the map.
	void setSpriteGraphic();
	
	sf::Vector2i location;
	int gold = 0;
	std::vector<Item> items;
};
