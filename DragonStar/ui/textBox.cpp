// ================================================================
//
// textBox.cpp
//
// ================================================================

#include "textBox.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"

TextBox::TextBox() {
	box.setFillColor(sf::Color(0, 0, 0, 255));
	box.setOutlineThickness(1.f);
	box.setOutlineColor(sf::Color(255, 255, 255, 255));

	text.setFillColor(sf::Color(255, 255, 255, 255));
	text.setCharacterSize(16u);
	text.setFont(*assetManager.LoadFont(settings.Font));

	SetMaxChars(maxChars);
}

void TextBox::GetInput(sf::RenderWindow& window, sf::Event& ev) {
	sf::Mouse mouse;
	leftClick = false;

	mousePos = mouse.getPosition(window);

	switch (ev.type) {
	case sf::Event::MouseButtonReleased:
		leftClick = true;
		break;
	case sf::Event::TextEntered:
		if (ev.text.unicode == '\b' && !input.empty()) {
			input.erase(input.size() - 1, 1);
			text.setString(input);
		}	
		else if (input.size() < maxChars && isActive && ev.text.unicode < 127 && ev.text.unicode > 31) {
			input += ev.text.unicode;
			text.setString(input);
		}
		break;
	default:
		break;
	}
}

void TextBox::Update(float secondsPerUpdate) {
	sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	
	if (leftClick) {
		if (box.getGlobalBounds().contains(mouseF)) {
			isActive = true;
			box.setFillColor(sf::Color(16, 16, 16, 255));
		}
		else {
			isActive = false;
			box.setFillColor(sf::Color(0, 0, 0, 255));
		}
	}
}

void TextBox::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(box);
	window.draw(text);
}

void TextBox::SetString(std::string string) {
	input = string;
	text.setString(input);
}

std::string TextBox::GetString() {
	return input;
}

void TextBox::SetPosition(int x, int y) {
	sf::Vector2f pos;
	pos.x = std::roundf(static_cast<float>(x) - box.getSize().x / 2.f);
	pos.y = std::roundf(static_cast<float>(y) - box.getSize().y / 2.f);
	box.setPosition(pos);

	pos.x += margin;
	pos.y += margin;
	text.setPosition(pos);
}

void TextBox::SetMaxChars(size_t numChars) {
	maxChars = numChars;

	std::string placeholder;
	for (size_t i = 0; i < maxChars; i++) {
		placeholder += "W";
	}
	text.setString(placeholder);
	auto textSize = text.getLocalBounds();

	box.setSize(sf::Vector2f(textSize.width + margin * 2.f, 22.f + margin * 2.f));
	text.setString(input);
}