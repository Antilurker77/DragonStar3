// ================================================================
//
// waitCommand.hpp
//
// Command for making an actor wait for a certain amount of time.
//
// ================================================================

#pragma once

#include "command.hpp"

class WaitCommand : public Command {
public:
	WaitCommand(int waitTime);
	void Execute(Actor* actor);
private:
	int timeToWait = 0;
};