// ================================================================
//
// defeatScene.hpp
// 
// Scene viewed when the player dies.
//
// ================================================================

#pragma once

enum class GameState;

#include <SFML/Graphics.hpp>
#include "../ui/button.hpp"

class DefeatScene {
public:
	DefeatScene();

	// Reads input.
	void ReadInput(sf::RenderWindow& window);

	// Updates the scene.
	GameState Update(float secondsPerUpdate);

	// Draws the scene.
	void Draw(sf::RenderTarget& window, float timeRatio);

private:
	sf::Text diedText;
	Button mainMenuButton;

	sf::Vector2i mousePos;
	bool leftClick = false;
};
