// ================================================================
//
// knownAbility.hpp
// 
// Struct for storing learned abilities.
//
// ================================================================

#pragma once

enum class AbilityID;

// AbilityID, Rank
struct KnownAbility {
	AbilityID AbilityID{};
	int Rank = 0;
};