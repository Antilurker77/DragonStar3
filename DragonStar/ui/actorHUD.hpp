// ================================================================
//
// actorHUD.hpp
// 
// UI element that displays information about a specific actor.
// Includes life bar and current exhaustion.
//
// ================================================================

#pragma once

class Actor;

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "richText.hpp"

class ActorHUD {
public:
	ActorHUD();

	// Updates the positions of the elements to match the actor's position.
	void Update(Actor& actor, float secondsPerUpdate);

	// Updates the text, life bar size, ect.
	void UpdateElements(Actor& actor);

	// Draws the UI element. Should be drawn to the world, not the screen.
	void Draw(sf::RenderTarget& window, float timeRatio);

private:
	bool displayExhastion = false;
	sf::RectangleShape exhaustionBackground;
	sf::Text exhaustionText;

	sf::RectangleShape lifeBarBackground;
	sf::RectangleShape lifeBar;

};
