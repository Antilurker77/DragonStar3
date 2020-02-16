// ================================================================
//
// shop.cpp
//
// ================================================================

#include "shop.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../core/random.hpp"
#include "../ui/inventory.hpp"

Shop::Shop(sf::Vector2i spawnLocation, int itemLevel, uint64_t seed) {
	sprites.resize(1);
	sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/shop.png"));

	location = spawnLocation;
	this->itemLevel = itemLevel;
	this->seed = seed;

	MoveToTile(location);
	generateInventory();
}

void Shop::Load(std::array<ItemSave, 24>& items) {
	for (size_t i = 0; i < items.size(); i++) {
		inventory[i] = Item(items[i]);
	}
}

sf::Vector2i Shop::GetLocation() {
	return location;
}

std::array<Item, 24>& Shop::GetInventory() {
	return inventory;
}

void Shop::BuyItem(Inventory& inv, size_t index) {
	int cost = inventory[index].GetValue();
	if (cost <= inv.GetGold()) {
		bool bought = inv.AddItem(inventory[index]); // returns false if inventory is full
		if (bought) {
			inventory[index] = Item();
			inv.ChangeGold(cost * -1);
		}
	}
}

void Shop::generateInventory() {
	std::mt19937_64 mt(seed);

	size_t numOfItems = Random::RandomSizeT(2, 8, mt) + Random::RandomSizeT(2, 8, mt);

	for (size_t i = 0; i < numOfItems; i++) {
		Item item;
		item.InitRandomItem(itemLevel);
		inventory[i] = item;
	}

}