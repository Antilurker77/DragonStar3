// ================================================================
//
// textBox.hpp
// 
// UI widget for a text box element.
//
// ================================================================

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class TextBox {
public:
	TextBox();

	// Gets input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates the text box.
	void Update(float secondsPerUpdate);

	// Draws the text box.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Sets the string displayed in the text box.
	void SetString(std::string string);

	// Sets the position of the text box. The text box will be centered at the given position.
	void SetPosition(int x, int y);
	
	// Sets the max number of characters for the text box. Will adjust size of the box based on
	// the given number of characters.
	void SetMaxChars(size_t numChars);

private:

	sf::RectangleShape box;
	sf::Text text;
	std::string input = "";
	size_t maxChars = 20;
	const float margin = 1.f;

	bool isActive = false;

	sf::Vector2i mousePos;
	bool leftClick = false;
};
