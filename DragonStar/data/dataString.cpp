// ================================================================
//
// dataString.cpp
//
// ================================================================

#include "dataString.hpp"

#include <algorithm>
#include <unordered_map>
#include "ability.hpp"
#include "id/category.hpp"
#include "id/element.hpp"
#include "id/equipType.hpp"
#include "id/statModType.hpp"

// Category Map
static std::unordered_map<Category, std::string> categoryMap = {
	{Category::Undefined, "Undefined"},
	{Category::Damaging, "Damaging"},
	{Category::Healing, "Healing"},
	{Category::SingleTarget, "Single Target"},
	{Category::AreaOfEffect, "Area of Effect"},
	{Category::Direct, "Direct"},
	{Category::OverTime, "Over Time"},
	{Category::Attack, "Attack"},
	{Category::Skill, "Skill"},
	{Category::Tech, "Technique"},
	{Category::Spell, "Spell"},
	{Category::Unarmed, "Unarmed"},
	{Category::Sword, "Sword"},
	{Category::Axe, "Axe"},
	{Category::Mace, "Mace"},
	{Category::Dagger, "Dagger"},
	{Category::Spear, "Spear"},
	{Category::Bow, "Bow"},
	{Category::Wand, "Wand"},
	{Category::Staff, "Staff"},
	{Category::Passive, "Passive"}
};

// Element Map
static std::unordered_map<Element, std::string> elementMap = {
	{Element::Undefined, "undefined"},
	{Element::None, "nonelemental"},
	{Element::Physical, "physical"},
	{Element::Arcane, "arcane"},
	{Element::Fire, "fire"},
	{Element::Ice, "ice"},
	{Element::Lightning, "lightning"},
	{Element::Water, "water"},
	{Element::Poison, "poison"},
	{Element::Light, "light"},
	{Element::Dark, "dark"},
	{Element::Astral, "astral"},
	{Element::Healing, "healing"}
};

// Equip Type Map
static std::unordered_map<EquipType, std::string> equipTypeMap = {
	{EquipType::Undefined, "Undefined"},
	{EquipType::Sword, "Sword"},
	{EquipType::Axe, "Axe"},
	{EquipType::Mace, "Mace"},
	{EquipType::Dagger, "Dagger"},
	{EquipType::Spear, "Spear"},
	{EquipType::Bow, "Bow"},
	{EquipType::Wand, "Wand"},
	{EquipType::Staff, "Staff"},
	{EquipType::Shield, "Shield"},
	{EquipType::LightHead, "Light Helmet"},
	{EquipType::LightBody, "Light Body Armor"},
	{EquipType::LightHands, "Light Gloves"},
	{EquipType::LightFeet, "Light Boots"},
	{EquipType::MediumHead, "Medium Helmet"},
	{EquipType::MediumBody, "Medium Body Armor"},
	{EquipType::MediumHands, "Medium Gloves"},
	{EquipType::MediumFeet, "Medium Boots"},
	{EquipType::HeavyHead, "Heavy Helmet"},
	{EquipType::HeavyBody, "Heavy Body Armor"},
	{EquipType::HeavyHands, "Heavy Gloves"},
	{EquipType::HeavyFeet, "Heavy Boots"},
	{EquipType::Neck, "Necklace"},
	{EquipType::Ring, "Ring"},
	{EquipType::LightSource, "Light Source"}
};

// Stat Mod Type Map
static std::unordered_map<StatModType, std::string> statMap = {
	{StatModType::Undefined, "ERROR_UNKNOWN"},
	{StatModType::HP, "Maximum HP"},
	{StatModType::HPMulti, "Maximum HP"},
	{StatModType::HPPerLevel, "Maximum HP per Level"},
	{StatModType::HPRegen, "HP Regenerated per Second"},
	{StatModType::HPLeech, "Life Leech"},
	{StatModType::HPOnHit, "HP Restored on Hit"},
	{StatModType::HPOnKill, "HP Restored on Kill"},
	{StatModType::MP, "Maximum MP"},
	{StatModType::MPMulti, "Maximum MP"},
	{StatModType::MPPerLevel, "Maximum MP per Level"},
	{StatModType::MPRegen, "MP Regenerated per Second"},
	{StatModType::MPLeech, "Mana Leech"},
	{StatModType::MPOnHit, "MP Restored on Hit"},
	{StatModType::MPOnKill, "MP Restored on Kill"},
	{StatModType::SP, "Maximum SP"},
	{StatModType::SPMulti, "Maximum SP"},
	{StatModType::SPPerLevel, "Maximum SP per Level"},
	{StatModType::SPRegen, "SP Regenerated per Second"},
	{StatModType::SPLeech, "Stamina Leech"},
	{StatModType::SPOnHit, "SP Restored on Hit"},
	{StatModType::SPOnKill, "SP Restored on Kill"},
	{StatModType::STR, "Strength"},
	{StatModType::STRMulti, "Strength"},
	{StatModType::DEX, "Dexterity"},
	{StatModType::DEXMulti, "Dexterity"},
	{StatModType::MAG, "Magic"},
	{StatModType::MAGMulti, "Magic"},
	{StatModType::VIT, "Vitality"},
	{StatModType::VITMulti, "Vitality"},
	{StatModType::SPI, "Spirit"},
	{StatModType::SPIMulti, "Spirit"},
	{StatModType::AllAttributes, "All Attributes"},
	{StatModType::AllAttributeMulti, "All Attributes"},
	{StatModType::Armor, "Armor"},
	{StatModType::ArmorMulti, "Armor"},
	{StatModType::ArmorPerLevel, "Armor per Level"},
	{StatModType::ArmorPen, "Armor Penetration"},
	{StatModType::MagicArmor, "Spell Defense"},
	{StatModType::MagicArmorMulti, "Spell Defense"},
	{StatModType::MagicArmorPerLevel, "Spell Defense per Level"},
	{StatModType::MagicArmorPen, "Spell Defense Penetration"},
	{StatModType::Evasion, "Evasion"},
	{StatModType::EvasionMulti, "Evasion"},
	{StatModType::EvasionPerLevel, "Evasion per Level"},
	{StatModType::Resistance, "Resistance"},
	{StatModType::ResistancePen, "Resistance Penetration"},
	{StatModType::AttackPower, "Attack Power"},
	{StatModType::SpellPower, "Spell Power"},
	{StatModType::Accuracy, "Accuracy"},
	{StatModType::BlockChance, "Block Chance"},
	{StatModType::Range, "Range"},
	{StatModType::Damage, "Damage"},
	{StatModType::DamageTaken, "Damage Taken"},
	{StatModType::Healing, "Healing"},
	{StatModType::HealingTaken, "Healing Taken"},
	{StatModType::CritChance, "Critical Strike Chance"},
	{StatModType::CritPower, "Critical Strike Power"},
	{StatModType::CritProtection, "Chance to be Critically Struck"},
	{StatModType::CritPowerProtection, "Power of Critical Stikes Taken"},
	{StatModType::Haste, "Haste"},
	{StatModType::DoubleStrikeChance, "Double Strike Chance"},
	{StatModType::DoubleStrikeDamage, "Double Strike Damage"},
	{StatModType::CounterChance, "Counter Chance"},
	{StatModType::OnHitDamage, "Damage on Hit"},
	{StatModType::DeathResistance, "Instant Death Resistance"},
	{StatModType::StunResistance, "Stun Resistance"},
	{StatModType::SnareResistance, "Snare Resistance"},
	{StatModType::DisarmResistance, "Disarm Resistance"},
	{StatModType::SilenceResistance, "Silence Resistance"},
	{StatModType::MovementSpeed, "Movement Speed"},
	{StatModType::SightRadius, "Vision Range"},
	{StatModType::GoldFind, "Gold Find"},
	{StatModType::EXPBoost, "EXP Earned"}
};

static std::vector<StatModType> percentMods = {
	StatModType::HPMulti,
	StatModType::HPLeech,
	StatModType::MPMulti,
	StatModType::MPLeech,
	StatModType::SPMulti,
	StatModType::SPLeech,
	StatModType::STRMulti,
	StatModType::DEXMulti,
	StatModType::MAGMulti,
	StatModType::VITMulti,
	StatModType::SPIMulti,
	StatModType::AllAttributeMulti,
	StatModType::ArmorMulti,
	StatModType::ArmorPen,
	StatModType::MagicArmorMulti,
	StatModType::MagicArmorPen,
	StatModType::EvasionMulti,
	StatModType::Resistance,
	StatModType::ResistancePen,
	StatModType::BlockChance,
	StatModType::Damage,
	StatModType::DamageTaken,
	StatModType::Healing,
	StatModType::HealingTaken,
	StatModType::CritChance,
	StatModType::CritPower,
	StatModType::CritProtection,
	StatModType::CritPowerProtection,
	StatModType::Haste,
	StatModType::DoubleStrikeChance,
	StatModType::DoubleStrikeDamage,
	StatModType::MovementSpeed,
	StatModType::DeathResistance,
	StatModType::StunResistance,
	StatModType::SnareResistance,
	StatModType::DisarmResistance,
	StatModType::SilenceResistance,
	StatModType::GoldFind,
	StatModType::EXPBoost
};

std::string DataString::ElementString(std::vector<Element>& elements, bool capitalize) {	
	std::string result;

	if (elements.empty() || elements[0] == Element::Undefined) {
		return result;
	}

	std::sort(elements.begin(), elements.end());
	for (size_t i = 0; i < elements.size(); i++) {
		if (i > 1) {
			result += "/";
		}
		std::string s = elementMap[elements[i]];
		if (capitalize) {
			s[0] = toupper(s[0]);
		}
		result += s;
	}

	return result;
}

std::string DataString::EquipTypeString(EquipType equipType) {
	return equipTypeMap[equipType];
}

std::string DataString::StatModString(StatMod& statMod) {
	std::string result;

	if (statMod.value >= 0) {
		result += "+";
	}
	else {
		//result += "-";
	}

	if (std::find(percentMods.begin(), percentMods.end(), statMod.statModType) != percentMods.end()) {
		result += std::to_string(statMod.value / 10) + "." + std::to_string(statMod.value % 10) + "% ";
	}
	else if (statMod.statModType == StatModType::SightRadius || statMod.statModType == StatModType::Range) {
		result += std::to_string(statMod.value / 100) + "." + std::to_string(statMod.value % 100) + " ";
	}
	else {
		result += std::to_string(statMod.value) + " ";
	}
	// ability name
	if (statMod.abilityID != static_cast<AbilityID>(0)) {
		result += AbilityNameString(statMod.abilityID) + " ";
	}

	// categories
	if (!statMod.categories.empty() && statMod.categories[0] != Category::Undefined) {
		for (auto& c : statMod.categories) {
			result += categoryMap[c] + " ";
		}
	}

	// elements
	if (!statMod.elements.empty() && statMod.elements[0] != Element::Undefined) {
		result += ElementString(statMod.elements, true) + " ";
	}

	result += statMap[statMod.statModType];

	return result;
}

std::string DataString::AbilityNameString(AbilityID abilityID) {
	Ability ab = Ability(abilityID, 0);
	return ab.GetName();
}