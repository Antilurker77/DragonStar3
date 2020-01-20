// ================================================================
//
// abilityCommand.hpp
//
// Command for making an actor execute an ability.
//
// ================================================================

#pragma once

enum class AbilityID;
class DungeonScene;

#include "command.hpp"

#include <SFML\System.hpp>

class AbilityCommand : public Command {
public:
	AbilityCommand(DungeonScene* ds, AbilityID abilityID, sf::Vector2i cursor);
	void Execute(Actor* actor);
private:
	DungeonScene* dungeonScene;
	AbilityID abilityID{};
	sf::Vector2i cursorLocation{ 0, 0 };
};
