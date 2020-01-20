// ================================================================
//
// learnAbilityWindow.hpp
// 
// UI element that allows the player to learn new abilities from
// a spellbook/tome.
//
// ================================================================

#pragma once

class Item;
class Player;

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "richText.hpp"
#include "tooltip.hpp"

class LearnAbilityWindow {
public:
	LearnAbilityWindow();

	// Gets input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates. Returns false if the window should be closed.
	bool Update(float secondsPerUpdate);

	// Draws the window.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Initializes the position of the window and sets up the ability UI elements.
	void Initialize(Item* sb, Player* p);


private:
	Item* spellbook = nullptr;
	Player* player = nullptr;

	bool leftClick = false;
	bool rightClick = false;
	sf::Vector2f mousePos;

	sf::RectangleShape background;
	sfe::RichText abilityPointText;
	std::vector<sf::Sprite> abilityIcons;
	std::vector<sf::Text> abilityText;
	std::vector<sf::Sprite> plusIcons;
	std::vector<bool> drawPlusIcons;

	Tooltip tooltip;
	bool displayTooltip = false;
};
