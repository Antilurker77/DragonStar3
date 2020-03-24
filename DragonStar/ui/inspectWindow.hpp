// ================================================================
//
// inspectWindow.hpp
// 
// Shows stats and abilities of a monster.
//
// ================================================================

#pragma once

class Actor;

#include <SFML/Graphics.hpp>
#include "richText.hpp"
#include "tooltip.hpp"

class InspectWindow {
public:
	InspectWindow();

	// Gets input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates the inspect window. Returns false if the window should be closed.
	bool Update(float secondsPerUpdate);

	// Draws the window to the screen.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Sets the actor who's stats and abilities will be displayed.
	void SetActor(Actor* actor);

private:
	sf::RectangleShape background;

	Actor* target = nullptr;

	const unsigned int fontSize = 14u;
	sfe::RichText nameText;
	sfe::RichText levelText;
	sfe::RichText hpmpspText;
	sfe::RichText powerText;
	sfe::RichText defenseText;
	sfe::RichText critText;
	sfe::RichText hastedsText;
	sfe::RichText resistanceHeaderText;
	sfe::RichText resistanceFirstText;
	sfe::RichText resistanceSecondText;
	sfe::RichText abilityHeaderText;
	sfe::RichText auraHeaderText;

	std::vector<sf::RectangleShape> abilityBackgrounds;
	std::vector<sf::Sprite> abilityIcons;

	std::vector<sf::RectangleShape> auraBackgrounds;
	std::vector<sf::Sprite> auraIcons;

	sf::Vector2i mousePos;
	bool leftClick = false;
	bool rightClick = false;
	bool wantToClose = false;

	Tooltip tooltip;
	bool displayTooltip = false;
};
