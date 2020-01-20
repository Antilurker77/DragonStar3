// ================================================================
//
// button.cpp
//
// ================================================================

#include "button.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"

const float Button::margin = 8.f;

Button::Button() {
	// Background Setup
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));

	// Text Setup
	font = assetManager.LoadFont(settings.Font);

	buttonText.setFont(*font);
	buttonText.setCharacterSize(20);
}

bool Button::Update(float secondsPerUpdate, sf::Vector2i mousePos) {
	bool contained = false;

	if (background.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		contained = true;
		background.setFillColor(sf::Color(255, 255, 255, 255));
		buttonText.setFillColor(sf::Color(0, 0, 0, 255));
	}
	else {
		background.setFillColor(sf::Color(0, 0, 0, 255));
		buttonText.setFillColor(sf::Color(255, 255, 255, 255));
	}

	return contained;
}

void Button::Render(sf::RenderTarget& window) {
	window.draw(background);
	window.draw(buttonText);
}

void Button::SetString(std::string s) {
	buttonText.setString(s);
	calcSize();
}

void Button::SetString(std::string s, unsigned int fontSize) {
	buttonText.setString(s);
	buttonText.setCharacterSize(fontSize);
	calcSize();
}

void Button::SetPosition(sf::Vector2i pos) {
	SetPosition(pos.x, pos.y);
}

void Button::SetPosition(int x, int y) {
	sf::Vector2f size = background.getSize();
	x -= static_cast<int>(size.x / 2);
	y -= static_cast<int>(size.y / 2);
	background.setPosition(static_cast<float>(x), static_cast<float>(y));
	buttonText.setPosition(static_cast<float>(x) + margin, static_cast<float>(y) + margin - (buttonText.getCharacterSize() / 4));
}

sf::Vector2f Button::GetSize() {
	return background.getSize();
}

void Button::calcSize() {
	auto size = buttonText.getLocalBounds();
	background.setSize(sf::Vector2f(size.width + (margin * 2.f), size.height + (margin * 2.f)));
}