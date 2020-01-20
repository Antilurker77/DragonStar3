// ================================================================
//
// moveCommand.cpp
//
// ================================================================

#include "moveCommand.hpp"

#include "../entity/actor.hpp"
#include "../scene/dungeonScene.hpp"
#include "../ui/messageLog.hpp"

MoveCommand::MoveCommand(DungeonScene& d, sf::Vector2i t) {
	dungeonScene = &d;
	destination = t;
}

void MoveCommand::Execute(Actor* actor) {
	if (dungeonScene->IsWalkable(actor, destination) && !dungeonScene->IsOccupiedByActor(destination)) {
		actor->Walk(destination, 1000); // todo: get tile movemod
		dungeonScene->UpdateVision();
	}
}