// ================================================================
//
// dropdown.hpp
//
// UI widget for a dropdown menu.
//
// ================================================================

#pragma once

#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../core/assetManager.hpp"
#include "../core/settings.hpp"

template <typename T>
class Dropdown {
public:
	Dropdown();

	// Updates the menu. Returns true if the widget is currently open.
	bool Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool scrollUp, bool scrollDown, bool dragging);

	// Draws the widget to the screen.
	void Draw(sf::RenderTarget& window);

	// Removes all items from the dropdown widget.
	void ClearOptions();

	// Adds an item to the dropdown widget.
	void AddOption(std::string name, T value);

	// Sets the length of the option box.
	void SetLength(unsigned int l);

	// Sets the position for the dropdown box.
	void SetPosition(int x, int y);

	// Returns the value of the selected option.
	T GetSelectedValue();

private:
	std::vector<std::pair<std::string, T>> options;

	bool isOpen = false;
	bool dragged = false;
	int prevMouseY = 0;
	size_t selected = 0;
	size_t top = 0;
	size_t maxVisible = 8;
	size_t optionsToDraw = 0;
	std::vector<sf::Text> optionTexts;
	std::vector<sf::RectangleShape> optionBGs;

	sf::Font* font;
	const unsigned int fontSize = 12;
	int length = 120;
	const int height = 20;

	sf::RectangleShape selectedBG;
	sf::RectangleShape arrowBG;
	sf::Text selectedText;

	sf::RectangleShape scrollBG;
	sf::RectangleShape scrollBar;

	// Sets the texts to be displayed.
	void setTexts();

	// Updates the scroll bar.
	void updateScrollBar();
};

// ==========================================================

template <typename T>
Dropdown<T>::Dropdown() {
	font = assetManager.LoadFont(settings.Font);

	selectedBG.setFillColor(sf::Color(0, 0, 0, 255));
	selectedBG.setOutlineThickness(1.f);
	selectedBG.setOutlineColor(sf::Color(255, 255, 255, 255));
	selectedBG.setSize(sf::Vector2f(static_cast<float>(length), static_cast<float>(height)));

	arrowBG.setFillColor(sf::Color(0, 0, 0, 255));
	arrowBG.setOutlineThickness(1.f);
	arrowBG.setOutlineColor(sf::Color(255, 255, 255, 255));
	arrowBG.setSize(sf::Vector2f(static_cast<float>(height), static_cast<float>(height))); // square

	selectedText.setCharacterSize(fontSize);
	selectedText.setFont(*font);

	for (size_t i = 0; i < maxVisible; i++) {
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color(0, 0, 0, 255));
		rect.setOutlineThickness(1.f);
		rect.setOutlineColor(sf::Color(255, 255, 255, 255));
		rect.setSize(sf::Vector2f(static_cast<float>(length), static_cast<float>(height)));
		optionBGs.push_back(rect);

		sf::Text t;
		t.setCharacterSize(fontSize);
		t.setFont(*font);
		optionTexts.push_back(t);
	}

	scrollBG.setFillColor(sf::Color(0, 0, 0, 255));
	scrollBG.setOutlineThickness(1.f);
	scrollBG.setOutlineColor(sf::Color(255, 255, 255, 255));
	scrollBG.setSize(sf::Vector2f(static_cast<float>(height), static_cast<float>((height + 1) * static_cast<int>(maxVisible) - 1)));

	scrollBar.setFillColor(sf::Color(191, 191, 191, 255));
}

template <typename T>
bool Dropdown<T>::Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool scrollUp, bool scrollDown, bool dragging) {
	sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	if (isOpen) {
		if (scrollUp) {
			if (top > 0) {
				top--;
				setTexts();
			}
		}
		else if (scrollDown) {
			if (top + maxVisible < options.size()) {
				top++;
				setTexts();
			}
		}

		if (dragging && prevMouseY != mousePos.y && scrollBar.getGlobalBounds().contains(mousePosFloat)) {
			dragged = true;
			int mouseDelta = mousePos.y - prevMouseY;

			// calculate how much the mouse needs to scroll to change visiable options
			int scrollPerOption = height * static_cast<int>(maxVisible) / static_cast<int>(options.size());

			// mouse moved down
			if (mouseDelta > 0) {
				while (mouseDelta > 0) {
					mouseDelta -= scrollPerOption;
					if (top + maxVisible < options.size()) {
						top++;
					}
				}
			}

			else {
				while (mouseDelta < 0) {
					mouseDelta += scrollPerOption;
					if (top > 0) {
						top--;
					}
				}
			}

			setTexts();
			updateScrollBar();
		}

		bool searching = true;
		for (size_t i = 0; i < optionsToDraw; i++) {
			if (searching && optionBGs[i].getGlobalBounds().contains(mousePosFloat)) {
				optionBGs[i].setFillColor(sf::Color(255, 255, 255, 255));
				optionTexts[i].setFillColor(sf::Color(0, 0, 0, 255));
				if (leftClick) {
					selected = i + top;

					isOpen = false;
					optionBGs[i].setFillColor(sf::Color(0, 0, 0, 255));
					optionTexts[i].setFillColor(sf::Color(255, 255, 255, 255));

					setTexts();
				}
				searching = false;
			}
			else {
				optionBGs[i].setFillColor(sf::Color(0, 0, 0, 255));
				optionTexts[i].setFillColor(sf::Color(255, 255, 255, 255));
			}
		}

		if (leftClick) {
			if (arrowBG.getGlobalBounds().contains(mousePosFloat)) {
				isOpen = false;
			}
			else if (!scrollBG.getGlobalBounds().contains(mousePosFloat)) {
				isOpen = false;
			}
		}
	}
	else {
		if (leftClick && (selectedBG.getGlobalBounds().contains(mousePosFloat) || arrowBG.getGlobalBounds().contains(mousePosFloat))) {
			isOpen = true;
			setTexts();
		}
	}

	prevMouseY = mousePos.y;

	return isOpen;
}

template <typename T>
void Dropdown<T>::Draw(sf::RenderTarget& window) {
	window.draw(selectedBG);
	window.draw(selectedText);
	window.draw(arrowBG);

	if (isOpen) {
		if (options.size() > optionsToDraw) {
			window.draw(scrollBG);
			window.draw(scrollBar);
		}
		for (size_t i = 0; i < optionsToDraw; i++) {
			window.draw(optionBGs[i]);
			window.draw(optionTexts[i]);
		}
	}
}

template <typename T>
void Dropdown<T>::ClearOptions() {
	options.clear();
	selected = 0;
	top = 0;
	optionsToDraw = 0;
}

template <typename T>
void Dropdown<T>::AddOption(std::string name, T value) {
	options.push_back(std::pair<std::string, T>(name, value));

	// set as default selected if this is the first option being added
	if (options.size() == 1) {
		selectedText.setString(name);
	}
}

template <typename T>
void Dropdown<T>::SetLength(unsigned int l) {
	length = l;

	selectedBG.setSize(sf::Vector2f(static_cast<float>(length), static_cast<float>(height)));

	for (size_t i = 0; i < optionBGs.size(); i++) {
		optionBGs[i].setSize(sf::Vector2f(static_cast<float>(length), static_cast<float>(height)));
	}
}

template <typename T>
void Dropdown<T>::SetPosition(int x, int y) {
	x = x - static_cast<int>(selectedBG.getSize().x / 2.f + arrowBG.getSize().x / 2.f);
	y = y - static_cast<int>(selectedBG.getSize().y / 2.f + arrowBG.getSize().y / 2.f);	
	
	selectedBG.setPosition(static_cast<float>(x), static_cast<float>(y));
	arrowBG.setPosition(static_cast<float>(x + length + 1), static_cast<float>(y));
	selectedText.setPosition(static_cast<float>(x + 3), static_cast<float>(y + 3));

	scrollBG.setPosition(static_cast<float>(x + length + 1), static_cast<float>(y + height + 1));

	for (size_t i = 0; i < optionBGs.size(); i++) {
		optionBGs[i].setPosition(static_cast<float>(x), static_cast<float>(y + ((height + 1) * (i + 1))));
		optionTexts[i].setPosition(static_cast<float>(x + 3), static_cast<float>(y + 3 + ((height + 1) * (i + 1))));
	}
}

template <typename T>
T Dropdown<T>::GetSelectedValue() {
	return options.at(selected).second;
}

template <typename T>
void Dropdown<T>::setTexts() {
	selectedText.setString(options[selected].first);

	optionsToDraw = 0;
	for (size_t i = top; i < top + maxVisible; i++) {
		if (i < options.size()) {
			optionTexts[optionsToDraw].setString(options[i].first);
			optionsToDraw++;
		}
	}

	updateScrollBar();
}

template <typename T>
void Dropdown<T>::updateScrollBar() {
	int maxSize = (height + 1) * static_cast<int>(maxVisible) - 1 - 4;

	float h = static_cast<float>(maxVisible) / static_cast<float>(options.size()) * static_cast<float>(maxSize);
	float w = static_cast<float>(height) - 4.f;

	sf::Vector2f pos(arrowBG.getPosition());
	pos.x += 2.f;
	pos.y += (float)top / (float)options.size() * (float)maxSize;
	pos.y += height + 3.f;

	scrollBar.setSize(sf::Vector2f(w, h));
	scrollBar.setPosition(pos);
}