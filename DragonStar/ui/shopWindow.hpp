// ================================================================
//
// shopWindow.hpp
// 
// Window that allows the player to buy from shops.
//
// ================================================================

#pragma once

class Inventory;

#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "tooltip.hpp"
#include "../entity/shop.hpp"

class ShopWindow {
public:
	ShopWindow();

	// Get input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates the window. Returns false if window should be closed.
	bool Update(float secondsPerUpdate, Inventory& inventory);

	// Draws the window.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Assigns a shop to the window.
	void Initialize(Shop& shop);

private:
	Shop* shop;

	// UI
	sf::RectangleShape background;
	std::array<sf::RectangleShape, 24> slotBackgrounds;
	std::array<sf::Sprite, 24> itemIcons;
	std::array<bool, 24> displayIcons;

	sf::Text shopText;

	Tooltip itemTooltip;
	bool displayTooltip = false;

	// Input
	sf::Vector2i mousePos;
	bool leftClick = false;
	bool rightClick = false;
	bool wantToClose = false;
};