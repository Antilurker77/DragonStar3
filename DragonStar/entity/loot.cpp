// ================================================================
//
// loot.cpp
//
// ================================================================

#include "loot.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../ui/inventory.hpp"

Loot::Loot(sf::Vector2i spawnPosition, int goldAmount) {
	sprites.resize(1);
	gold = goldAmount;
	location = spawnPosition;
	setSpriteGraphic();
	MoveToTile(spawnPosition);
}

Loot::Loot(sf::Vector2i spawnPosition, std::vector<Item> itemsDropped) {
	sprites.resize(1);
	gold = 0;
	items = itemsDropped;
	location = spawnPosition;
	setSpriteGraphic();
	MoveToTile(spawnPosition);
}

Loot::Loot(sf::Vector2i spawnPosition, int goldAmount, std::vector<Item> itemsDropped) {
	sprites.resize(1);
	gold = goldAmount;
	items = itemsDropped;
	location = spawnPosition;
	setSpriteGraphic();
	MoveToTile(spawnPosition);
}

sf::Vector2i Loot::GetLocation() {
	return location;
}

int Loot::GetGold() {
	return gold;
}

std::vector<Item>& Loot::GetItems() {
	return items;
}

bool Loot::IsEmpty() {
	return gold <= 0 && items.empty();
}

void Loot::AddGold(int amount) {
	gold += amount;
}

void Loot::AddItems(std::vector<Item>& itemsToAdd) {
	items.insert(items.end(), itemsToAdd.begin(), itemsToAdd.end());
}

void Loot::LootGold(Inventory& inventory) {
	inventory.ChangeGold(gold);
	gold = 0;
}

void Loot::LootItem(Inventory& inventory, size_t index) {
	bool lootedItem = inventory.AddItem(items[index]);
	if (lootedItem) {
		items.erase(items.begin() + index);
		items.shrink_to_fit();
	}
}

void Loot::setSpriteGraphic() {
	// todo: lots of art and logic
	if (items.size() == 1) {
		if (items[0].GetItemType() == ItemType::Potion) {
			sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/potion.png"));
		}
		else if (items[0].GetItemType() == ItemType::Scroll) {
			sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/scroll.png"));
		}
		else if (items[0].IsWeapon()) {
			sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/weapon.png"));
		}
		else if (items[0].GetItemType() == ItemType::Equipment) {
			sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/armor.png"));
		}
		else {
			sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/loot1.png"));
		}
	}	
	else if (items.size() > 0) {
		sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/loot1.png"));
	}
	else {
		sprites[0].setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/gold1.png"));
	}

	
}