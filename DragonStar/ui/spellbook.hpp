// ================================================================
//
// spellbook.hpp
// 
// UI element that displays the player's abilities.
//
// ================================================================

#pragma once

class Ability;
class Actor;
enum class AbilityID;

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "richText.hpp"
#include "tooltip.hpp"

class Spellbook {
public:
	Spellbook();

	// Input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates.
	void Update(float secondsPerUpdate, Actor* player);

	// Draws the spellbook.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Positions UI elements based on the current resolution. Should be called
	// whenever the resolution is changed.
	void Initialize();

	// Checks if there is an ability at this location.
	void GetDraggableAbility(sf::Vector2i location, AbilityID& id);

private:

	sf::RectangleShape background;
	std::vector<sf::Sprite> abilityIcons;
	std::vector<sfe::RichText> abilityText;
	std::vector<sf::RectangleShape> abilityBackgrounds;
	std::vector<AbilityID> abilityIDs;

	size_t currentPage = 0;
	size_t maxPage = 0;

	sf::Sprite previousPageButton;
	sf::Sprite nextPageButton;
	bool displayPreviousPageButton = false;
	bool displayNextPageButton = false;
	sfe::RichText pageText;

	Tooltip tooltip;
	bool displayTooltip = false;

	const float iconSize = 40.f;
	const unsigned int fontSize = 12u;

	// Input
	sf::Vector2i mousePos;
	bool leftClick = false;
	bool rightClick = false;
};