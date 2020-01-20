// ================================================================
//
// tileMath.hpp
// 
// Functions for calculating various tile algorithms.
//
// ================================================================

#pragma once

#include <vector>
#include <SFML/System.hpp>

// Hash function for Vector2i.
namespace std {

	template<>
	struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& v) const {
			//return static_cast<size_t>(v.x) << 32 | v.y;
			return std::hash<int>()(v.x) << 32 | std::hash<int>()(v.y);
			//return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
		}
	};
}

namespace TileMath {

	// Returns the distance between two tiles.
	double Distance(sf::Vector2i start, sf::Vector2i end);

	// Returns the closest tile if the designated tile is outside of an area.
	sf::Vector2i Closest(sf::Vector2i location, std::vector<sf::Vector2i>& area);

	// Returns the tile cordinates based on a given pixel location.
	sf::Vector2i PixelToTile(sf::Vector2i location);

	// Returns tiles adjacent to the given tile, including diagonals.
	std::vector<sf::Vector2i> Neighboors(sf::Vector2i location);

	// Returns the offset for given tiles.
	std::vector<sf::Vector2i> Offset(std::vector<sf::Vector2i>& area, sf::Vector2i offset);

	// Rotates tiles around a given point.
	std::vector<sf::Vector2i> Rotate(std::vector<sf::Vector2i>& area, sf::Vector2i center, double degrees);

	// Returns the rotation degree value for an adjacent tile. Only works in the four cardinal directions.
	double AdjacentDegree(sf::Vector2i center, sf::Vector2i tile);

	// Returns a square ring surrounding the square with a given radius.
	//std::vector<sf::Vector2i> SquareRing(sf::Vector2i loctaion, int radius);

	// Returns all tiles near the center with a given radius. 100 Radius = 1 Tile
	std::vector<sf::Vector2i> AreaOfEffect(sf::Vector2i center, int radius);

	// Returns all tiles in a line between two points.
	std::vector<sf::Vector2i> Line(sf::Vector2i start, sf::Vector2i end, bool negativeOffset = false);
}