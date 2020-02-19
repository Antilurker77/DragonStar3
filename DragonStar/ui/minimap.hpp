// ================================================================
//
// minimap.hpp
// 
// UI element that displays a map of the dungeon in the upper right
// corner of the screen.
//
// ================================================================

#pragma once

#include <SFML/Graphics.hpp>

class DungeonScene;

class Minimap {
public:
	Minimap();

	// Draws the minimap.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Updates the minimap.
	void UpdateMinimap(DungeonScene* dungeonScene);

private:

	sf::RectangleShape background;
	sf::VertexArray minimap;
	sf::Texture* minimapTexture;

	const float tileSize = 4.f;
};
