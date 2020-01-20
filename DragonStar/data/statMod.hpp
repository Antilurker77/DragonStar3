// ================================================================
//
// statMod.hpp
// 
// Class that holds data for modifying stats.
//
// ================================================================

#pragma once

#include <vector>

enum class AbilityID;
enum class AuraID;
enum class Category;
enum class Element;

#include "id/statModType.hpp"

class StatMod {
public:
	StatMod();
	StatMod(StatModType smt, int value, std::vector<Category> categories, Element element, AbilityID abilityID, AuraID auraID);
	StatMod(StatModType smt, int value, std::vector<Category> categories, std::vector<Element> elements, AbilityID abilityID, AuraID auraID);

	StatMod(StatModType smt, int value);
	StatMod(StatModType smt, int value, std::vector<Category> categories);
	StatMod(StatModType smt, int value, Category category);
	StatMod(StatModType smt, int value, Element element);
	StatMod(StatModType smt, int value, std::vector<Element> elements);
	StatMod(StatModType smt, int value, std::vector<Category> categories, Element element);
	StatMod(StatModType smt, int value, std::vector<Category> categories, std::vector<Element> elements);
	StatMod(StatModType smt, int value, Category category, Element element);
	StatMod(StatModType smt, int value, Category category, std::vector<Element> elements);
	StatMod(StatModType smt, int value, AbilityID abilityID);
	StatMod(StatModType smt, int value, AuraID auraID);

	StatModType statModType;
	int value;
	std::vector<Category> categories;
	std::vector<Element> elements;
	AbilityID abilityID;
	AuraID auraID;
};
