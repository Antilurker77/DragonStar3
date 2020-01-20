// ================================================================
//
// tooltip.hpp
// 
// UI element that displays a miniwindow describing the properties
// of a given item or ability.
//
// ================================================================

#pragma once

class Ability;
class Aura;
class Actor;
class Item;
enum class AbilityID;

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "richText.hpp"

class Tooltip {
public:
	Tooltip();

	// Updates the tooltip.
	void Update(float secondsPerUpdate);

	// Renders the tooltip.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Sets the position of the tooltip.
	void SetPosition(float x, float y, bool worldTooltip = false);

	// Sets the position of the tooltip.
	void SetPosition(sf::Vector2f position, bool worldTooltip = false);

	// Returns the size of the tooltip.
	sf::Vector2f GetSize();

	// Puts actor information in the tooltip.
	void SetTooltip(Actor& actor);

	// Puts item information in the tooltip.
	void SetTooltip(Item& item, bool displayCost = false);

	// Puts ability information in the tooltip.
	void SetTooltip(Actor* user, Ability& ability);

	// Puts aura information in the tooltip.
	void SetTooltip(Aura& aura);

private:
	// Sets the size for the tooltip.
	void setSizes();

	sf::Vector2f pos{ 0.f, 0.f };

	sf::RectangleShape background;
	sfe::RichText titleText;
	std::vector<sfe::RichText> tooltipText;

	const unsigned int titleFontSize = 12u;
	const unsigned int textFontSize = 12u;

};