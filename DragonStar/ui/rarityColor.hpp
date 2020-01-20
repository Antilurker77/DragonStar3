// ================================================================
//
// rarityColor.hpp
// 
// Helper function that returns the color for an item rarity.
//
// ================================================================

#pragma once

enum class Rarity;

#include <SFML/Graphics.hpp>

namespace RarityColor {
	// Returns the color based on the given rarity.
	sf::Color GetColor(Rarity rarity);
}
