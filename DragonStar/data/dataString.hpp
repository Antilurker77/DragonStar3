// ================================================================
//
// dataString.hpp
// 
// List of functions for turning data elements into strings.
//
// ================================================================

#pragma once

enum class AbilityID;
enum class Element;
enum class EquipType;

#include <string>
#include <vector>
#include "statMod.hpp"

namespace DataString {
	// Sorts and returns a string based on the given elements.
	std::string ElementString(std::vector<Element>& elements, bool capitalize = false);

	// Returns a string based on the given Equipment Type.
	std::string EquipTypeString(EquipType equipType);

	// Returns a string based on the given stat modifier.
	std::string StatModString(StatMod& statMod);

	// Returns the name of a given ability.
	std::string AbilityNameString(AbilityID abilityID);
}