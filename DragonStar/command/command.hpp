// ================================================================
//
// command.hpp
//
// Base class for making actors do an action.
//
// ================================================================

#pragma once

class Actor;

#include <memory>

class Command {
public:
	virtual void Execute(Actor* actor) = 0;
protected:

};

typedef std::unique_ptr<Command> CommandPtr;