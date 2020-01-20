// ================================================================
//
// abilityCommand.cpp
//
// ================================================================

#include "abilityCommand.hpp"

#include "../entity/actor.hpp"

AbilityCommand::AbilityCommand(DungeonScene* ds, AbilityID id, sf::Vector2i cursor) {
	dungeonScene = ds;
	abilityID = id;
	cursorLocation = cursor;
}

void AbilityCommand::Execute(Actor* actor) {
	actor->UseAbility(dungeonScene, abilityID, cursorLocation);
}