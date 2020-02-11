// ================================================================
//
// doubleStrike.cpp
//
// ================================================================

#include "ability.hpp"

#include "id/category.hpp"

static EventOptions initDoubleStrikeEO() {
	EventOptions eo;

	eo.EventName = "Double Strike";

	eo.AbilityID = static_cast<AbilityID>(0);
	eo.AuraID = static_cast<AuraID>(0);

	eo.Categories = {
		Category::Damaging,
		Category::Attack,
		Category::SingleTarget,
		Category::Direct,
	};
	eo.Elements = {};

	eo.CanDodge = true;
	eo.CanBlock = true;
	eo.CanCounter = true;
	eo.CanCrit = true;
	eo.CanDoubleStrike = false;

	eo.BaseHitChance = -1;
	eo.BonusArmorPen = 0;
	eo.BonusResistancePen = 0;
	eo.BonusCritChance = 0;
	eo.BonusCritPower = 0;
	eo.BonusDoubleStrikeChance = 0;
	eo.BonusHPLeech = 0;
	eo.BonusMPLeech = 0;
	eo.BonusSPLeech = 0;

	return eo;
}

EventOptions Ability::doubleStrikeEO = initDoubleStrikeEO();