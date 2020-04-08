// ================================================================
//
// characterCreationScene.hpp
// 
// Scene that lets player choose their name and starting goods.
//
// ================================================================

#pragma once

enum class GameState;

#include <SFML/Graphics.hpp>
#include "../ui/button.hpp"
#include "../ui/textBox.hpp"

class CharacterCreationScene {
public:
	CharacterCreationScene();

	// Reads input.
	void ReadInput(sf::RenderWindow& window);

	// Updates the scene.
	GameState Update(float secondsPerUpdate);

	// Draws the scene.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Sets the positions of the UI elements.
	void InitializePositions();

private:
	sf::Vector2i mousePos;
	bool leftClick = false;

	sf::Text headerText;
	sf::Text nameText;
	TextBox nameTextBox;
	Button startGameButton;
};
