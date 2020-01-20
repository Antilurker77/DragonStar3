// ================================================================
//
// shop.hpp
//
// Class that represents a shop in the dungeon.
//
// ================================================================

#pragma once

class Inventory;

#include <array>
#include <vector>
#include "entity.hpp"
#include "../data/item.hpp"

class Shop : public Entity {
public:
	// Initializes the shop with a random inventory.
	Shop(sf::Vector2i spawnLocation, int itemLevel, uint64_t seed);

	// Returns the tile location of this shop.
	sf::Vector2i GetLocation();

	// Returns the items the shop has for sale.
	std::array<Item, 24>& GetInventory();

	// Purchases the specified item if the player has enough gold.
	void BuyItem(Inventory& inv, size_t index);

private:
	// Generates inventory based on the seed.
	void generateInventory();

	sf::Vector2i location;
	int itemLevel;
	uint64_t seed;
	std::array<Item, 24> inventory;
};
