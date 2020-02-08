// ================================================================
//
// playerHUD.hpp
// 
// UI element that displays the players status, auras, and action
// bars.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class ItemID;

class Actor;
class DungeonScene;

#include <array>
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include "tooltip.hpp"

struct Shortcut {
	AbilityID AbilityID{};
	ItemID ItemID{};
};

class PlayerHUD {
public:
	PlayerHUD();

	// Loads ability shortcuts into the bar.
	void Load(std::array<int, 24> shortcutAbilities);

	// Gets input.
	void GetInput(sf::RenderWindow& window, sf::Event& ev);

	// Updates the information on the display.
	void Update(Actor* player, DungeonScene& dungeonScene, float secondsPerUpdate);

	// Draws the screen.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Initializes elements based on the screen resolution. Should be called whenever the
	// screen resolution is changed.
	void Initialize();

	// Sets a shortcut in the specified slot to the specified ability.
	void SetShortcut(size_t index, AbilityID id);

	// Returns all shortcuts.
	std::array<Shortcut, 24> GetShortcuts();

	// Checks to see if there is a ability at this locaiton.
	void GetDraggableAbility(sf::Vector2i location, AbilityID& id);

	// Releases the ability from the cursor and assigns it to the slot.
	void ReleaseDraggableAbility(sf::Vector2i location, AbilityID& id);

private:
	// Shortcuts
	std::array<Shortcut, 24> shortcuts;

	// Input
	sf::Vector2i mousePos;
	bool leftClick = false;
	size_t usingShortcut = 24; // index of shortcut being used, if equal to size no shortcut was pressed

	// UI Elements
	sf::RectangleShape background;
	std::array<sf::RectangleShape, 24> shortcutSlots;
	std::array<sf::Sprite, 24> shortcutIcons;
	std::array<bool, 24> displayShortcutIcons;
	std::array<sf::RectangleShape, 24> unavailableSquare;
	std::array<bool, 24> displayUnavailableSquare;
	std::array<sf::Text, 24> cooldownText;
	std::array<bool, 24> displayCooldownText;
	std::array<sf::Text, 24> chargeText;
	std::array<bool, 24> displayChargeText;

	sf::RectangleShape hpBarBackground;
	sf::RectangleShape hpBar;
	sf::Text hpText;

	sf::RectangleShape mpBarBackground;
	sf::RectangleShape mpBar;
	sf::Text mpText;

	sf::RectangleShape spBarBackground;
	sf::RectangleShape spBar;
	sf::Text spText;

	std::vector<sf::RectangleShape> buffBackgrounds;
	std::vector<sf::Sprite> buffIcons;
	std::vector<sf::Text> buffDurationText;
	std::vector<bool> displayBuffDurationText;
	std::vector<sf::Text> buffStackText;
	std::vector<bool> displayBuffStackText;
	std::vector<size_t> buffIndex;

	std::vector<sf::RectangleShape> debuffBackgrounds;
	std::vector<sf::Sprite> debuffIcons;
	std::vector<sf::Text> debuffDurationText;
	std::vector<bool> displayDebuffDurationText;
	std::vector<sf::Text> debuffStackText;
	std::vector<bool> displayDebuffStackText;
	std::vector<size_t> debuffIndex;

	Tooltip tooltip;
	bool displayTooltip = false;

	const float iconSize = 40.f;
	const unsigned int barTextFontSize = 16u;

};