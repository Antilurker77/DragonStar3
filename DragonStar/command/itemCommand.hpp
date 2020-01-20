// ================================================================
//
// itemCommand.hpp
//
// Command for making the player use an item.
//
// ================================================================

#pragma once

class DungeonScene;
class Inventory;

#include "command.hpp"

#include <SFML\System.hpp>

class ItemCommand : public Command {
public:
	ItemCommand(DungeonScene* ds, Inventory* inv, sf::Vector2i cursor, size_t invIndex);
	void Execute(Actor* actor);
private:
	DungeonScene* dungeonScene;
	Inventory* inventory;
	sf::Vector2i cursorLocation;
	size_t index;
};