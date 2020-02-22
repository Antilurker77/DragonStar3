// ================================================================
//
// inventory.hpp
// 
// UI element that displays the player's inventory, equipment, and
// stats.
//
// ================================================================

#pragma once

class Player;

#include <array>
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include "tooltip.hpp"
#include "../core/saveFile.hpp"
#include "../data/item.hpp"

struct InventorySlot {
	Item Item;
	int StackCount = 0;
};

class Inventory {
public:
	Inventory();

	// Loads saved data into inventory.
	void Load(int playerGold, std::array<ItemSave, 40>& items);

	// Get input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates the window. Returns false if the window should be closed.
	bool Update(float secondsPerUpdate, DungeonScene& dungeonScene);

	// Draws the inventory to the screen.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Positions UI elements based on the current resolution. Should be called
	// whenever the resolution is changed.
	void Initialize();

	// Returns the amount of gold in the player's inventory.
	int GetGold();

	// Returns the player's inventory.
	std::array<InventorySlot, 40>& GetInventory();

	// Add or removes gold from the player's inventory. Will never drop below 0.
	void ChangeGold(int amount);

	// Adds an item to the player's inventory if there's room. Returns false if item couldn't be looted.
	bool AddItem(Item& item);

	// Consumes the item in the designated slot.
	void ConsumeItem(size_t index);

	// Returns the item in the designated index.
	Item* GetItem(size_t index);

	// Transfers ownership of item to cursor container if possible.
	void GetDraggableItem(DungeonScene& dungeonScene, sf::Vector2i position, ItemID& id, Item& item, int& stackCount);

	// Transfers ownership of the item from the cursor container to the inventory if possible.
	// Equips and item if it is dropped in the right spot.
	void ReleaseDraggableItem(DungeonScene& dungeonScene, sf::Vector2i position, Item& item, int& stackCount);

	// Sets the cursor to identification mode.
	void IdentifyMode(bool usingScroll);

private:
	// Updates the specified item slot.
	void updateItemSlot(size_t index);

	// Updates the stats displayed.
	void updateStats(Player* player);

	int gold = 0;
	std::array<InventorySlot, 40> inventorySlots;

	sf::RectangleShape background;
	std::array<sf::RectangleShape, 40> slotBackgrounds;
	std::array<sf::Sprite, 40> slotIcons;
	std::array<bool, 40> displaySlotIcons;

	std::array<sf::Text, 40> stackText;
	std::array<bool, 40> displayStackText;

	sf::Text goldText;

	std::array<sf::RectangleShape, 10> equipBackgrounds;
	std::array<sf::Sprite, 10> equipIcons;
	std::array<bool, 10> displayEquipIcons;

	sf::Sprite statButton;
	sf::RectangleShape statBackground;
	sfe::RichText statTexts;
	sfe::RichText statTextsCol2;
	bool displayStats = false;

	Tooltip tooltip;
	bool displayTooltip = false;

	bool identifying = false;
	bool usingScroll = false;
	sf::Sprite identifySprite;

	static const float slotSize;
	static const float margin;
	static const unsigned int fontSize;

	// Input.
	sf::Vector2i mousePos;
	bool leftClick = false;
	bool rightClick = false;
};