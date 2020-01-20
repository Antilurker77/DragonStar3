// ================================================================
//
// statMod.cpp
//
// ================================================================

#include "statMod.hpp"

#include "id/abilityID.hpp"
#include "id/auraID.hpp"
#include "id/category.hpp"
#include "id/element.hpp"

StatMod::StatMod() {
	statModType = StatModType::Undefined;
	value = 0;
	categories = {};
	elements = {};
	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, std::vector<Category> categories, Element element, AbilityID abilityID, AuraID auraID) {
	this->statModType = smt;
	this->value = value;
	this->categories = categories;
	this->elements = { element };
	this->abilityID = abilityID;
	this->auraID = auraID;
}

StatMod::StatMod(StatModType smt, int value, std::vector<Category> categories, std::vector<Element> elements, AbilityID abilityID, AuraID auraID) {
	this->statModType = smt;
	this->value = value;
	this->categories = categories;
	this->elements = elements;
	this->abilityID = abilityID;
	this->auraID = auraID;
}

StatMod::StatMod(StatModType smt, int value) {
	this->statModType = smt;
	this->value = value;

	categories = {};
	elements = {};
	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, std::vector<Category> categories) {
	this->statModType = smt;
	this->value = value;
	this->categories = categories;

	elements = {};
	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, Category category) {
	this->statModType = smt;
	this->value = value;
	this->categories = { category };

	elements = {};
	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, Element element) {
	this->statModType = smt;
	this->value = value;
	this->elements = { element };

	categories = {};
	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, std::vector<Element> elements) {
	this->statModType = smt;
	this->value = value;
	this->elements = elements;

	categories = {};
	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, std::vector<Category> categories, Element element) {
	this->statModType = smt;
	this->value = value;
	this->categories = categories;
	this->elements = { element };

	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, std::vector<Category> categories, std::vector<Element> elements) {
	this->statModType = smt;
	this->value = value;
	this->categories = categories;
	this->elements = elements;

	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, Category category, Element element) {
	this->statModType = smt;
	this->value = value;
	this->categories = { category };
	this->elements = { element };

	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, Category category, std::vector<Element> elements) {
	this->statModType = smt;
	this->value = value;
	this->categories = { category };
	this->elements = elements;

	abilityID = AbilityID::Undefined;
	auraID = AuraID::Undefined;
}


StatMod::StatMod(StatModType smt, int value, AbilityID abilityID) {
	this->statModType = smt;
	this->value = value;
	this->abilityID = abilityID;

	categories = {};
	elements = {};
	auraID = AuraID::Undefined;
}

StatMod::StatMod(StatModType smt, int value, AuraID auraID) {
	this->statModType = smt;
	this->value = value;
	this->auraID = auraID;

	categories = {};
	elements = {};
	abilityID = AbilityID::Undefined;
}