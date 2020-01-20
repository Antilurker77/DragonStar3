// ================================================================
//
// eventType.hpp
// 
// List of all event flags used for the proc system.
//
// ================================================================

#pragma once

enum class EventType {
	Undefined = 0,
	PreCalcDamage,
	PostCalcDamage,
	PreCalcHeal,
	PostCalcHeal,
	Damage,
	Damaged,
	Heal,
	Healed,
	Death
};
