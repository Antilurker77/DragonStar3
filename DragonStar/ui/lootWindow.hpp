// ================================================================
//
// lootWindow.hpp
// 
// UI element that displays all the loot currently available on a
// given tile.
//
// ================================================================

#pragma once

class Inventory;
class Loot;

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "richText.hpp"
#include "tooltip.hpp"
#include "../entity/loot.hpp"

class LootWindow {
public:
	LootWindow();

	// Reads the given input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates the window. Returns false if the window is closed.
	bool Update(float secondsPerUpdate, Inventory& inventory);

	// Draws the window.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Initializes the window based on the given loot.
	void Initialize(Loot& loot);

private:

	// Loot Reference
	Loot* lootPile = nullptr;

	// Graphical
	sf::RectangleShape background;

	sf::Text goldText;
	sf::RectangleShape goldTextHighlight;
	bool drawGoldTextHighlight = false;
	sf::Sprite goldIcon;

	std::vector<sfe::RichText> itemText;
	std::vector<sf::RectangleShape> itemTextHighlight;
	std::vector<sf::Sprite> itemIcons;
	bool drawItemTextHighlight = false;
	size_t selectedItem = 0;

	const unsigned int fontSize = 14u;

	Tooltip tooltip;
	bool displayTooltip = false;

	// Input
	sf::Vector2i mousePos;
	bool leftClick = false;
	bool rightClick = false;
	bool wantToClose = false;
	bool display = true;
	bool hasGold = false;
};
