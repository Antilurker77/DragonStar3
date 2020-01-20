// ================================================================
//
// rarityColor.cpp
//
// ================================================================

#include "rarityColor.hpp"

#include "../data/id/rarity.hpp"

sf::Color RarityColor::GetColor(Rarity rarity) {
	switch (rarity) {
		case Rarity::Common:
			return sf::Color(255, 255, 255, 255);
			break;
		case Rarity::Magical:
			return sf::Color(0, 200, 200, 255);
			break;
		case Rarity::Rare:
			return sf::Color(175, 50, 175, 255);
			break;
		case Rarity::FixedArtifact:
			return sf::Color(240, 120, 0, 255);
			break;
		case Rarity::RandomArtifact:
			return sf::Color(240, 240, 0, 255);
			break;
		case Rarity::Item:
			return sf::Color(210, 180, 100, 255);
			break;
		default:
			return sf::Color(255, 255, 255, 255);
			break;
	}
}