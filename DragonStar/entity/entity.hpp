// ================================================================
//
// entity.hpp
// 
// Base class for any object that appears in the dungeon. If an
// entity is using multiple sprites, they will be stacked on top
// of each other.
//
// ================================================================

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../core/assetManager.hpp"

class Entity {
public:
	Entity();
	Entity(sf::Vector2f spawnPosition, std::vector<std::string> textureFilePaths);
	Entity(sf::Vector2i tileSpawnPosition, std::vector<std::string> textureFilePaths);

	// Updates entity.
	void Update(float secondsPerUpdate);

	// Draws the entity to the screen.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Draws the entity at a specified position and scale instead of it's own.
	void Draw(sf::RenderTarget& window, float timeRatio, sf::Vector2f pos, float scale = 1.f);

	// Moves the sprite to the specified location. If the velocity is set to 0, the move will be instant.
	void Move(sf::Vector2f target, float unitsPerSecond = 0.f);

	// Moves the sprite to the specified tile. If the velocity is set to 0, the move will be instant.
	void MoveToTile(sf::Vector2i target, float unitsPerSecond = 0.f);

	// Returns the position of the sprite.
	sf::Vector2f GetSpritePosition();

	// Returns true if the entity is currently moving.
	bool IsMoving();

	// Returns true if the entity is on screen.
	bool IsOnScreen(sf::RenderTarget& window);

protected:
	std::vector<sf::Sprite> sprites;
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f velocityPerUpdate = { 0.f, 0.f };
	sf::Vector2f updatePos;
	sf::Vector2f destination;
	float speed = 0.f;
};
