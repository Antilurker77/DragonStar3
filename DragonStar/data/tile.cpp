// ================================================================
//
// tile.cpp
//
// ================================================================

#pragma once

#include "tile.hpp"

Tile TileInfo::GetTile(TileID id) {
	Tile tile;
	tile.TileType = id;
	tile.SpriteNumber = static_cast<uint8_t>(id);

	switch (id) {
	case TileID::DownStairs: {
		tile.Name = "Down Stairs";
		tile.MoveMod = 1000;
		tile.IsPassible = true;
		tile.IsOpeque = false;
		tile.RequireFlight = false;
		tile.RequireSwimming = false;
		break;
	}
	case TileID::StoneWall: {
		tile.Name = "Stone Wall";
		tile.MoveMod = 1000;
		tile.IsPassible = false;
		tile.IsOpeque = true;
		tile.RequireFlight = false;
		tile.RequireSwimming = false;
		break;
	}
	case TileID::StoneFloor: {
		tile.Name = "Stone Floor";
		tile.MoveMod = 1000;
		tile.IsPassible = true;
		tile.IsOpeque = false;
		tile.RequireFlight = false;
		tile.RequireSwimming = false;
		break;
	}
	case TileID::StoneBrickWall: {
		tile.Name = "Stone Brick Wall";
		tile.MoveMod = 1000;
		tile.IsPassible = false;
		tile.IsOpeque = true;
		tile.RequireFlight = false;
		tile.RequireSwimming = false;
		break;
	}
	default: {
		tile.Name = "Void";
		tile.MoveMod = 1000;
		tile.IsPassible = false;
		tile.IsOpeque = false;
		tile.RequireFlight = false;
		tile.RequireSwimming = false;
		break;
	}
	}

	return tile;
}