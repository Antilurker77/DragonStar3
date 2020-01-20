// ================================================================
//
// tile.hpp
// 
// Data for a single tile.
//
// ================================================================

#pragma once

#include <string>
#include "id/tileID.hpp"

struct Tile {
	TileID TileType;

	std::string Name;
	uint8_t SpriteNumber;
	int MoveMod;
	bool IsPassible;
	bool IsOpeque;
	bool RequireFlight;
	bool RequireSwimming;
};

namespace TileInfo {
	// Return Tile struct based on the ID given.
	Tile GetTile(TileID id);
}