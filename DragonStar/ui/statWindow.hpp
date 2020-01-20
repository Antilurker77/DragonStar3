// ================================================================
//
// statWindow.hpp
// 
// UI element that allows the player to spend stat points.
//
// ================================================================

#pragma once

class Player;

#include <array>
#include <string>
#include "richText.hpp"
#include "SFML/Graphics.hpp"

class StatWindow {
public:
	StatWindow();

	// Gets input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates. Returns false if user wants to close the window.
	bool Update(float secondsPerUpdate);

	// Draws.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Sets the position of the window based on the resolution. Should be called whenever the resolution is changed.
	void Initialize();

	// Sets the player reference.
	void SetPlayer(Player* p);

private:
	Player* player = nullptr;

	sf::RectangleShape background;

	std::array<sfe::RichText, 5> statText;
	std::array<sf::Sprite, 5> statButtons;
	std::array<std::string, 5> statDescriptions;

	sf::Vector2i mousePos;
	bool leftClick = false;
	bool rightClick = false;
};

