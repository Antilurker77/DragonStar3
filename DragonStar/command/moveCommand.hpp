// ================================================================
//
// moveCommand.hpp
//
// Command for making an actor move to a tile.
//
// ================================================================

#pragma once

class DungeonScene;

#include <SFML/System.hpp>
#include "command.hpp"

class MoveCommand : public Command {
public:
	MoveCommand(DungeonScene& d, sf::Vector2i t);
	void Execute(Actor* actor);
private:
	DungeonScene* dungeonScene;
	sf::Vector2i destination;
};