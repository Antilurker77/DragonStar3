// ================================================================
//
// waitCommand.cpp
//
// ================================================================

#include "waitCommand.hpp"

#include "../entity/actor.hpp"

WaitCommand::WaitCommand(int waitTime) {
	timeToWait = waitTime;
}

void WaitCommand::Execute(Actor* actor) {
	actor->Wait(timeToWait);
}