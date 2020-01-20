// ================================================================
//
// button.hpp
// 
// UI widget for a button element.
//
// ================================================================

#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
	Button();

	// Updates the button. If the cursor is over the
	// button, change the background and font color.
	bool Update(float secondsPerUpdate, sf::Vector2i mousePos);

	// Renders the button to the screen.
	void Render(sf::RenderTarget& window);

	// Sets the string and automatically resizes the button.
	void SetString(std::string s);

	// Sets the string and font size and automatically resizes the button.
	void SetString(std::string s, unsigned int fontSize);

	// Sets the button's position.
	void SetPosition(sf::Vector2i pos);

	// Sets the button's position.
	void SetPosition(int x, int y);

	// Get's the buttons size;
	sf::Vector2f GetSize();

private:
	// Calculates the size for the background.
	void calcSize();
	
	static const float margin;
	sf::Font* font = nullptr;

	sf::RectangleShape background;
	sf::Text buttonText;
};