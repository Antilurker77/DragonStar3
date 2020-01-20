// ================================================================
//
// cursorContainer.hpp
// 
// UI element for dragging and dropping items and abilities.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class ItemID;

class DungeonScene;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../data/item.hpp"

class CursorContainer {
public:
	CursorContainer();

	// Gets input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Update.
	void Update(float secondsPerUpdate, DungeonScene& dungeonScene);

	// Draws the icon of the dragged item or tooltip if dragging something.
	void Draw(sf::RenderTarget& window, float timeRatio);

private:
	sf::Vector2i mousePos;
	bool holdingDownMouse = false;
	bool dragging = false;
	float holdingDownTime = 0.f;

	sf::Sprite sprite;
	AbilityID draggedAbilityID{};
	ItemID draggedItemID{};
	Item draggedItem;
	int itemStackSize = 0;
};
