// ================================================================
//
// characterCreationScene.hpp
// 
// Scene that lets player choose their name and starting goods.
//
// ================================================================

#pragma once

enum class GameState;
enum class RaceID;

#include <SFML/Graphics.hpp>
#include "../ui/button.hpp"
#include "../ui/dropdown.hpp"
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

	// Returns the name of the player.
	std::string GetPlayerName();

	// Returns the race selected in the dropdown menu.
	RaceID GetPlayerRace();

private:
	sf::Vector2i mousePos;
	bool leftClick = false;
	bool dragging = false;
	float dragTime = 0.f;
	bool scrollUp = false;
	bool scrollDown = false;

	sf::Text headerText;
	sf::Text nameText;
	TextBox nameTextBox;

	Dropdown<RaceID> raceDropdown;

	bool isDropdownOpen = false;
	bool isRaceDropdownOpen = false;

	Button startGameButton;
};
