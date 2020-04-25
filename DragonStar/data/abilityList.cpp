// ================================================================
//
// abilityList.cpp
//
// ================================================================

#include "ability.hpp"

#include "id/abilityID.hpp"
#include "id/auraID.hpp"
#include "id/category.hpp"
#include "id/element.hpp"
#include "id/eventType.hpp"
#include "id/equipType.hpp"
#include "id/itemID.hpp"
#include "../core/combat.hpp"
#include "../core/random.hpp"
#include "../core/records.hpp"
#include "../core/tileMath.hpp"
#include "../entity/actor.hpp"
#include "../scene/dungeonScene.hpp"
#include "../ui/messageLog.hpp"

static std::unordered_map<AbilityID, AbilityData> initList() {
	std::unordered_map<AbilityID, AbilityData> list;

	// Active Abilities
	list[AbilityID::Attack] = []{
		AbilityData ad;

		ad.Name = "Attack";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::Attack;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { -1 };
		ad.UseTime = { -1000 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 1000 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;
		
		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			if (user == nullptr) {
				desc = "Attack an enemy with your equipped weapon, dealing#damage 100% Attack Power #default weapon damage.";
			}
			else {
				std::string dmg = std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank]));
				desc = "Attack an enemy with your equipped weapon, dealing #damage " + dmg + " #default weapon damage.";
			}

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};


		return ad;
	}();
	list[AbilityID::ArcaneSpear] = [] {
		AbilityData ad;

		ad.Name = "Arcane Spear";
		ad.Icon = "arcane_spear.png";
		ad.ID = AbilityID::ArcaneSpear;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 800, 800, 800, 800, 800 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 7, 7, 7, 7, 7 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1500, 1575, 1650, 1725, 1800 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Toss a spear of arcane energy, dealing " + value + " arcane damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Bite] = [] {
		AbilityData ad;

		ad.Name = "Bite";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::Bite;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = { Element::Physical };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { -1 };
		ad.UseTime = { -1000 };
		ad.Cooldown = { 400 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 50 };

		ad.Values = {
			{ 1250 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user != nullptr) {
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
			}
			else {
				value = std::to_string(Values[0][rank] / 10) + "% Attack Power";
			}
			desc = "Deal #damage " + value + " #default physical damage to the target.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::BoltOfDarkness] = [] {
		AbilityData ad;

		ad.Name = "Bolt of Darkness";
		ad.Icon = "bolt_of_darkness.png";
		ad.ID = AbilityID::BoltOfDarkness;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Dark };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 250, 250, 250, 250, 250 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 8, 8, 8, 8, 8 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1300, 1365, 1430, 1495, 1560 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Fire a bolt of darkness at your target, dealing " + value + "dark damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::BoltOfLight] = [] {
		AbilityData ad;

		ad.Name = "Bolt of Light";
		ad.Icon = "bolt_of_light.png";
		ad.ID = AbilityID::BoltOfLight;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Light };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 8, 8, 8, 8, 8 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 800, 840, 880, 920, 960 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 700, 700, 700, 700, 700 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 500, 500, 500, 500, 500 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Fire a bolt of light at your target, dealing " + value + " light damage. Heals the caster for 50% of damage dealt.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Bonechill] = [] {
		AbilityData ad;

		ad.Name = "Bonechill";
		ad.Icon = "bonechill.png";
		ad.ID = AbilityID::Bonechill;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Ice };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 1600, 1600, 1600, 1600, 1600 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 9, 9, 9, 9, 9 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1600, 1680, 1760, 1840, 1920 },
			{ 50, 50, 50, 50, 50 }, // Haste Reduction
			{ 800, 800, 800, 800, 800 } // Debuff Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string hasteReduction = std::to_string(Values[1][rank] / 10);
			std::string duration = std::to_string(Values[2][rank] / 100);

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Freeze the target to the bone, dealing " + value + "ice damage and reducing the target's haste by " + hasteReduction + "% for " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Bonechill, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Boulder] = [] {
		AbilityData ad;

		ad.Name = "Boulder";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Boulder;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Physical };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 350 };
		ad.UseTime = { 200 };
		ad.Cooldown = { 2000 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 10 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 1100 },
			{ 200 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string stun = std::to_string(Values[1][rank] / 100);

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Conjures a boulder and drops it on the target, dealing " + value + " physical damage and stunning it for " + stun + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Boulder, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Chopper] = [] {
		AbilityData ad;

		ad.Name = "Chopper";
		ad.Icon = "chopper.png";
		ad.ID = AbilityID::Chopper;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Axe
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 40, 40, 40, 40, 40 };

		ad.Values = {
			{ 1400, 1400, 1400, 1400, 1400 }, // Attack Power
			{ 400, 490, 580, 670, 760 } // Bonus Double Strike Chance
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { ad.Values[1][0], ad.Values[1][1], ad.Values[1][2], ad.Values[1][3], ad.Values[1][4] };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string dsChance;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power#default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			dsChance = std::to_string(Values[1][rank] / 10);

			desc = "Deliver a chopper's swing with your axe, dealing " + dmg + " weapon damage. Has a " + dsChance + "% bonus chance to double strike. Requires an axe.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Cleave] = [] {
		AbilityData ad;

		ad.Name = "Cleave";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Cleave;

		ad.Categories = {
			Category::AreaOfEffect,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 100, 100, 100, 100, 100 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1200, 1200, 1200, 1200, 1200 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 35, 35, 35, 35, 35 };

		ad.Values = {
			{ 800, 840, 880, 920, 960 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = true;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			// XXX
			//  @		
			std::vector<sf::Vector2i> area{
				{-1, -1},
				{0, -1},
				{1, -1}
			};

			area = TileMath::Offset(area, user->GetLocation());
			area = TileMath::Rotate(area, user->GetLocation(), TileMath::AdjacentDegree(user->GetLocation(), cursorTarget));

			return area;
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = std::to_string(Values[0][rank] / 10) + "% Attack Power";
			}
			else {
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
			}
			desc = "Swing in an arc in front of you, dealing #damage " + value + " #default weapon damage. Requires a sword or axe.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			for (auto& target : targets) {
				Combat::SkillDamage(user, target, eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::CobraBite] = [] {
		AbilityData ad;

		ad.Name = "Cobra Bite";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::CobraBite;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = { Element::Poison };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { -1 };
		ad.UseTime = { -1000 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 40 };

		ad.Values = {
			{ 1000 },
			{ 100 }, // Poison DoT
			{ 500 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string dotDamage;
			std::string duration = std::to_string(Values[2][rank] / 100);

			if (user != nullptr) {
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
				dotDamage = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[1][rank]));
			}
			else {
				value = std::to_string(Values[0][rank] / 10) + "% Attack Power";
				dotDamage = std::to_string(Values[1][rank] / 10) + "% Attack Power";
			}
			desc = "Deal #damage " + value + " #default poison damage and an additional #damage " + dotDamage + " #default poison damage every 1s for " + duration + "s. This effect can stack up to 3 times.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::CobraBite, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ConcentratedVenom] = [] {
		AbilityData ad;

		ad.Name = "Concentrated Venom";
		ad.Icon = "poison.png";
		ad.ID = AbilityID::ConcentratedVenom;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = { Element::Poison };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 250 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 1200 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 50 };

		ad.Values = {
			{ 600 },
			{ 400 }, // DoT Damage
			{ 600 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string dotValue;
			std::string duration = std::to_string(Values[2][rank] / 100);

			if (user != nullptr) {
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
				dotValue = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[1][rank]));
			}
			else {
				value = std::to_string(Values[0][rank] / 10) + "% Attack Power";
				dotValue = std::to_string(Values[0][rank] / 10) + "% Attack Power";
			}
			desc = "Deal #damage " + value + " #default poison damage to the target and an additional #damage " + dotValue + " #default poison damage every 1s for " + duration + "s.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::ConcentratedVenom, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::CriticalShot] = [] {
		AbilityData ad;

		ad.Name = "Critical Shot";
		ad.Icon = "critical_shot.png";
		ad.ID = AbilityID::CriticalShot;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Bow
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 50, 50, 50, 50, 50 };

		ad.Values = {
			{ 1000, 1050, 1100, 1150, 1200 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Focus your aim and fire a shot at the target's weakpoint, dealing " + dmg + "weapon damage. Critical Shot has a 100% bonus critical strike chance. Requires a bow.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::CrushArmor] = [] {
		AbilityData ad;

		ad.Name = "Crush Armor";
		ad.Icon = "crush_armor.png";
		ad.ID = AbilityID::CrushArmor;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Mace
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 45, 45, 45, 45, 45 };

		ad.Values = {
			{ 1300, 1300, 1300, 1300, 1300 }, // Damage
			{ 1250, 1312, 1375, 1437, 1500 }, // Debuff Duration
			{ 250, 250, 250, 250, 250 } // Armor Reduction Amount
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string duration = std::to_string(Values[1][rank] / 100) + "." + std::to_string(Values[1][rank] % 100);
			std::string reduction = std::to_string(Values[2][rank] / 10);

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Deal a crushing blow to your target, dealing " + dmg + "weapon damage and reducing its armor by " + reduction + "% for " + duration + "s. Requires a mace.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::CrushArmor, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::CrushingBlow] = [] {
		AbilityData ad;

		ad.Name = "Crushing Blow";
		ad.Icon = "crushing_blow.png";
		ad.ID = AbilityID::CrushingBlow;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Mace
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 2000, 2000, 2000, 2000, 2000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 60, 60, 60, 60, 60 };

		ad.Values = {
			{ 2400, 2520, 2640, 2760, 2880 }, // Damage
			{ 300, 300, 300, 300, 300 } // Stun Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string stun = std::to_string(Values[1][rank] / 100);

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Swing your mace to deal a massive blow to the target, dealing " + dmg + "weapon damage. If Crushing Blow deals at least 20% of the target's max HP as damage, the target is stunned for " + stun + "s. Requires a mace.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				int hpThreshold = targets[0]->GetMaxHP() * 20 / 100;
				if (result.DidHit && result.TotalDamage >= hpThreshold) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::CrushingBlow, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::DemonBlade] = [] {
		AbilityData ad;

		ad.Name = "Demon Blade";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::DemonBlade;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = { Element::Dark };
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Dagger
		};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { -1 };
		ad.UseTime = { -1000 };
		ad.Cooldown = { 1600 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 45 };

		ad.Values = {
			{ 1500 }, // Damage
			{ 800 }, // Debuff Duration
			{ 100 } // Damage Taken Amount
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string duration = std::to_string(Values[1][rank] / 100);
			std::string reduction = std::to_string(Values[2][rank] / 10);

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Deals " + dmg + "dark damage and increases the amount of damage the target takes by " + reduction + "% for " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::DemonBlade, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Disarm] = [] {
		AbilityData ad;

		ad.Name = "Disarm";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Disarm;

		ad.Categories = {
			Category::SingleTarget
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 3000, 3000, 3000, 3000, 3000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 35, 33, 33, 30, 30 };

		ad.Values = {
			{ 800, 800, 900, 900, 1000 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = true;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string duration = std::to_string(Values[0][rank] / 100);

			desc = "Disarm the target for " + duration + "s, preventing it from using weapon skills.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Disarm, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::DragonBreath] = [] {
		AbilityData ad;

		ad.Name = "Dragon Breath";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::DragonBreath;

		ad.Categories = {
			Category::AreaOfEffect,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = { Element::Fire };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 100 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 2000 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 20 };

		ad.Values = {
			{ 1100 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 750 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = true;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			// XXX
			//  X
			//  @		
			std::vector<sf::Vector2i> area{
				{0, -1},
				{-1, -2},
				{0, -2},
				{1, -2},
			};
			
			area = TileMath::Offset(area, user->GetLocation());
			area = TileMath::Rotate(area, user->GetLocation(), TileMath::AdjacentDegree(user->GetLocation(), cursorTarget));

			return area;
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = std::to_string(Values[0][rank] / 10) + "% Attack Power";
			}
			else {			
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
			}
			desc = "Breathe fire, dealing #damage " + value + " #default fire damage everything in an area in front of you.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			for (auto& target : targets) {
				Combat::AttackDamage(user, target, eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::DragonfireBolt] = [] {
		AbilityData ad;

		ad.Name = "Dragonfire Bolt";
		ad.Icon = "dragonfire_bolt.png";
		ad.ID = AbilityID::DragonfireBolt;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Fire };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 1200, 1200, 1200, 1200, 1200 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 8, 8, 8, 8, 8 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 2000, 2100, 2200, 2300, 2400 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Fire a bolt of draconic fire at your target, dealing " + value + " fire damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ElectricSurge] = [] {
		AbilityData ad;

		ad.Name = "Electric Surge";
		ad.Icon = "electric_surge.png";
		ad.ID = AbilityID::ElectricSurge;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Lightning };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 150, 150, 150, 150, 150 };
		ad.Cooldown = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 7, 7, 7, 7, 7 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1200, 1260, 1320, 1380, 1440 }, // Damage
			{ 50, 50, 50, 50, 50 }, // Crit Buff
			{ 1200, 1200, 1200, 1200, 1200 } // Buff Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string buffValue = std::to_string(Values[1][rank] / 10);
			std::string buffDuration = std::to_string(Values[2][rank] / 100);

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Surge electricity at your target, dealing " + value + "lightning damage and increasing your critical strike chance by " + buffValue + "% for " + buffDuration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
			Combat::AddAuraStack(user, user, eventOptions, AuraID::ElectricSurge, rank);
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ElementalEnergy] = [] {
		AbilityData ad;

		ad.Name = "Elemental Energy";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ElementalEnergy;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { 
			Element::Arcane,
			Element::Fire,
			Element::Water,
			Element::Lightning,
			Element::Ice,
			Element::Poison,
			Element::Light,
			Element::Dark
		};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 6000, 6000, 6000, 6000, 6000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 5, 5, 5, 5, 5 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 200, 210, 220, 230, 240 }, // Elemental Damage Increase
			{ 1500, 1500, 1500, 1500, 1500 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = true;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string duration;

			value = std::to_string(Values[0][rank] / 10);
			duration = std::to_string(Values[1][rank] / 100);

			desc = "Channel raw elemental energy, increasing elemental damage dealt by " + value + "% for " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			Combat::AddAuraStack(user, user, eventOptions, AuraID::ElementalEnergy, rank);
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::FearfulGaze] = [] {
		AbilityData ad;

		ad.Name = "Fearful Gaze";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::FearfulGaze;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = { Element::Dark };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 350 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 1000 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 30 };

		ad.Values = {
			{ 1250 }, // Damage
			{ 150 }, // Damage Reduction
			{ 1000 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string damageReduction = std::to_string(Values[1][rank] / 10);
			std::string duration = std::to_string(Values[2][rank] / 100);

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Deals " + value + "dark damage and reduces the damage of the target's next ability by " + damageReduction + "%. Lasts " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::FearfulGaze, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::FieryTouch] = [] {
		AbilityData ad;

		ad.Name = "Fiery Touch";
		ad.Icon = "fiery_touch.png";
		ad.ID = AbilityID::FieryTouch;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Fire };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 150, 150, 150, 150, 150 };
		ad.UseTime = { 100, 100, 100, 100, 100 };
		ad.Cooldown = { 750, 750, 750, 750, 750 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 4, 4, 4, 4, 4 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1400, 1470, 1540, 1610, 1680 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Burn the target with your hands, dealing " + value + "fire damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::FlameBolt] = [] {
		AbilityData ad;

		ad.Name = "Flame Bolt";
		ad.Icon = "flame_bolt.png";
		ad.ID = AbilityID::FlameBolt;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Fire };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 6, 6, 6, 6, 6 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1100, 1155, 1210, 1265, 1320 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Fire a bolt of flames at your target, dealing " + value + " fire damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::FlameStrike] = [] {
		AbilityData ad;

		ad.Name = "Flame Strike";
		ad.Icon = "flame_strike.png";
		ad.ID = AbilityID::FlameStrike;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = { Element::Fire };
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Mace,
			EquipType::Dagger,
			EquipType::Spear,
			EquipType::Staff
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 30, 30, 30, 30, 30 };

		ad.Values = {
			{ 1500, 1575, 1650, 1725, 1800 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Coat your weapon in flames and strike the target, dealing " + dmg + "fire damage. Increases the damage of your next fire ability by 10%. Lasts 5s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				Combat::AddAuraStack(user, user, eventOptions, AuraID::FlameStrike, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::FlashStrike] = [] {
		AbilityData ad;

		ad.Name = "Flash Strike";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::FlashStrike;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Dagger
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -500, -500, -500, -500, -500 };
		ad.Cooldown = { 600, 600, 600, 600, 600 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 20, 20, 20, 20, 20 };

		ad.Values = {
			{ 700, 735, 770, 805, 840 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "A quick strike that deals " + dmg + "weapon damage. Requies a dagger.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::FuriousStrike] = [] {
		AbilityData ad;

		ad.Name = "Furious Strike";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::FuriousStrike;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Mace,
			EquipType::Dagger,
			EquipType::Spear,
			EquipType::Staff
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1200, 1200, 1100, 1100, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 35, 33, 33, 30, 30 };

		ad.Values = {
			{ 1400, 1400, 1400, 1400, 1400 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Strike your target with utmost fury, dealing " + dmg + "weapon damage and increasing the damage of Furious Strike by 25%. Stacks up to 4 times and lasts 20s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				Combat::AddAuraStack(user, user, eventOptions, AuraID::FuriousStrike, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::HasteAllies] = [] {
		AbilityData ad;

		ad.Name = "Haste Allies";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::HasteAllies;

		ad.Categories = {
			Category::AreaOfEffect,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 3000 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 15 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 250 }, // Haste Increase
			{ 3000 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = true;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return TileMath::AreaOfEffect(cursorTarget, 150);
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string duration;

			value = std::to_string(Values[0][rank] / 10);
			duration = std::to_string(Values[1][rank] / 100);

			desc = "Increase the caster's and adjacent allies' haste and movement speed by " + value + "% for " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			for (auto& target : targets) {
				if (user->IsPlayer() == target->IsPlayer()) {
					Combat::AddAuraStack(user, target, eventOptions, AuraID::Speed, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Heal] = [] {
		AbilityData ad;

		ad.Name = "Heal";
		ad.Icon = "heal.png";
		ad.ID = AbilityID::Heal;

		ad.Categories = {
			Category::SingleTarget,
			Category::Healing,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Healing };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 250, 250, 250, 250, 250 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 20, 19, 18, 17, 16 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 2000, 2000, 2000, 2000, 2000 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string amount;

			if (user == nullptr) {
				amount = "#heal " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				amount = "#heal " + std::to_string(Combat::SpellHealEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Call upon divine energy, restoring " + amount + "HP.";
			return desc;
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellHeal(user, targets[0], eventOptions, Values[0][rank], AttributeType::HP);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::HerosTriumph] = [] {
		AbilityData ad;

		ad.Name = "Hero's Triumph";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::HerosTriumph;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Mace,
			EquipType::Dagger,
			EquipType::Spear,
			EquipType::Staff
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 3000, 3000, 3000, 3000, 3000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 50, 50, 50, 50, 50 };

		ad.Values = {
			{ 3000, 3150, 3300, 3450, 3600 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Swing your weapon for a mighty heroic blow, dealing " + dmg + "weapon damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Icicle] = [] {
		AbilityData ad;

		ad.Name = "Icicle";
		ad.Icon = "icicle.png";
		ad.ID = AbilityID::Icicle;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Ice };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 6, 6, 6, 6, 6 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 900, 945, 990, 1035, 1080 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Hurl an icicle at your target, dealing " + value + "ice damage and chilling it, reducing movement speed by 25% for 5s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Chilled, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Ignite] = [] {
		AbilityData ad;

		ad.Name = "Ignite";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Ignite;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Fire };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 100, 100, 100, 100, 100 };
		ad.Cooldown = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 4, 4, 4, 4, 4 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 150, 157, 165, 172, 180 }, // Fire DoT
			{ 1000, 1000, 1000, 1000, 1000 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dotValue;
			std::string dotDuration;

			if (user == nullptr) {
				dotValue = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				dotValue = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}
			dotDuration = std::to_string(Values[1][rank] / 100);

			desc = "Light the target on fire, dealing " + dotValue + "fire damage every 1s for " + dotDuration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Ignite, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Infect] = [] {
		AbilityData ad;

		ad.Name = "Infect";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Infect;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Poison };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 100, 100, 100, 100, 100 };
		ad.Cooldown = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 8, 8, 8, 8, 8 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 250, 262, 275, 287, 300 },
			{ 250, 262, 275, 287, 300 }, // DoT Damage
			{ 900, 900, 900, 900, 900 } // DoT Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string dotValue;
			std::string dotDuration;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
				dotValue = "#damage " + std::to_string(Values[1][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
				dotValue = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[1][rank])) + " #default ";
			}
			dotDuration = std::to_string(Values[2][rank] / 100);

			desc = "Infect the target with deadly poison, dealing " + value + "poison damage and an additional " + dotValue + " poison damage every 1s for " + dotDuration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Infect, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ImpactWave] = [] {
		AbilityData ad;

		ad.Name = "Impact Wave";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ImpactWave;

		ad.Categories = {
			Category::AreaOfEffect,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 100, 100, 100, 100, 100 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 30, 30, 30, 30, 30 };

		ad.Values = {
			{ 1300, 1365, 1430, 1495, 1560 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = true;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			// X
			// X
			// @		
			std::vector<sf::Vector2i> area{
				{0, -1},
				{0, -2}
			};

			area = TileMath::Offset(area, user->GetLocation());
			area = TileMath::Rotate(area, user->GetLocation(), TileMath::AdjacentDegree(user->GetLocation(), cursorTarget));

			return area;
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = std::to_string(Values[0][rank] / 10) + "% Attack Power";
			}
			else {
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
			}
			desc = "Strike with concussive force, dealing #damage " + value + " #default weapon damage in a line of length 2.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			for (auto& target : targets) {
				Combat::SkillDamage(user, target, eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::MagicMissile] = [] {
		AbilityData ad;

		ad.Name = "Magic Missile";
		ad.Icon = "magic_missile.png";
		ad.ID = AbilityID::MagicMissile;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = {Element::Arcane};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 5, 5, 5, 5, 5 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1000, 1050, 1100, 1150, 1200 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Fire a bolt of arcane energy at your target, dealing " + value + " arcane damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Maul] = [] {
		AbilityData ad;

		ad.Name = "Maul";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Maul;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { -1 };
		ad.UseTime = { -1000 };
		ad.Cooldown = { 600 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 25 };

		ad.Values = {
			{ 1000 }, // Damage
			{ 300 }, // Bleed Duration
			{ 250 } // Bleed Damage
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string duration = std::to_string(Values[1][rank] / 100);
			std::string bleedDmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
				bleedDmg = "#damage " + std::to_string(Values[2][rank] / 10) + "." + std::to_string(Values[2][rank] % 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
				bleedDmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[2][rank])) + " #default ";
			}

			desc = "Deals " + dmg + "weapon damage and an additional " + bleedDmg + "every 1s for " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Maul, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::MysticBlast] = [] {
		AbilityData ad;

		ad.Name = "Mystic Blast";
		ad.Icon = "mystic_blast.png";
		ad.ID = AbilityID::MysticBlast;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 100, 100, 100, 100, 100 };
		ad.Cooldown = { 3000, 3000, 3000, 3000, 3000 };
		ad.MaxCharges = { 2, 2, 2, 2, 2 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 10, 10, 10, 10, 10 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1500, 1575, 1650, 1725, 1800 },
			{ 300, 300, 300, 300, 300 }, // Magic Armor Reduction
			{ 1000, 1000, 1000, 1000, 1000 } // Reduction Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string maReduction = std::to_string(Values[1][rank] / 10);
			std::string maDuration = std::to_string(Values[2][rank] / 100);

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Fire a blast of mystical arcane energy at the target, dealing " + value + "arcane damage and reducing the target's spell defense by " + maReduction + "% for " + maDuration + "s. Has 2 charges.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::MysticBlast, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PhaseDoor] = [] {
		AbilityData ad;

		ad.Name = "Phase Door";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::PhaseDoor;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 100, 100, 100, 100, 100 };
		ad.Cooldown = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 9, 8, 7, 6, 5 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 300, 300, 300, 300, 300 }, // Min Distance
			{ 900, 900, 900, 900, 900 } // Max Distance
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string minDistance = std::to_string(Values[0][rank] / 100);
			std::string maxDistance = std::to_string(Values[1][rank] / 100);

			desc = "Teleports the caster to a random tile between " + minDistance + " and " + maxDistance + " tiles away.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			std::vector<sf::Vector2i> possibleTiles;
			DungeonScene* dungeon = user->GetDungeonScene();
			auto size = dungeon->GetDungeonSize();
			auto userLocation = user->GetLocation();
			for (size_t x = 0; x < size.x; x++) {
				for (size_t y = 0; y < size.y; y++) {
					sf::Vector2i tile{ static_cast<int>(x), static_cast<int>(y) };
					if (dungeon->IsWalkable(user, tile) && !dungeon->IsOccupiedByActor(tile)) {
						int distance = static_cast<int>(TileMath::Distance(userLocation, tile) * 100.0);
						if (distance >= Values[0][rank] && distance <= Values[1][rank]) {
							possibleTiles.push_back(tile);
						}
					}
				}
			}
			if (!possibleTiles.empty()) {
				size_t index = Random::RandomSizeT(0, possibleTiles.size() - 1);
				user->Warp(possibleTiles[index]);
				dungeon->UpdateVision();
			}
			else {
				messageLog.AddMessage("Phase Door failed!");
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PoisonArrow] = [] {
		AbilityData ad;

		ad.Name = "Poison Arrow";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::PoisonArrow;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {
			Element::Poison
		};
		ad.RequiredWeaponTypes = {
			EquipType::Bow
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1200, 1200, 1200, 1200, 1200 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 25, 25, 25, 25, 25 };

		ad.Values = {
			{ 1000, 1000, 1000, 1000, 1000 }, // Damage
			{ 600, 600, 600, 600, 600 }, // Poison Duration
			{ 100, 113, 126, 140, 154 } // Poison Damage
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string duration = std::to_string(Values[1][rank] / 100);
			std::string bleedDmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
				bleedDmg = "#damage " + std::to_string(Values[2][rank] / 10) + "." + std::to_string(Values[2][rank] % 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
				bleedDmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[2][rank])) + " #default ";
			}

			desc = "Fire a poisoned arrow at the target, dealing " + dmg + "poison damage and an additional " + bleedDmg + "poison damage every 1s for " + duration + "s. Requires a bow.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::PoisonArrow, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PowerShot] = [] {
		AbilityData ad;

		ad.Name = "Power Shot";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::PowerShot;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Bow
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 30, 30, 30, 30, 30 };

		ad.Values = {
			{ 1600, 1680, 1760, 1840, 1920 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Shoot a powerful arrow at your target, dealing " + dmg + "weapon damage. Requires a bow.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PowerStrike] = [] {
		AbilityData ad;

		ad.Name = "Power Strike";
		ad.Icon = "power_strike.png";
		ad.ID = AbilityID::PowerStrike;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Mace,
			EquipType::Dagger,
			EquipType::Spear,
			EquipType::Staff
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1200, 1200, 1100, 1100, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 40, 38, 38, 35, 35 };

		ad.Values = {
			{ 2000, 2000, 2000, 2000, 2000 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Deal a powerful strike to your target, dealing " + dmg + "weapon damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::RendingSlash] = [] {
		AbilityData ad;

		ad.Name = "Rending Slash";
		ad.Icon = "rending_slash.png";
		ad.ID = AbilityID::RendingSlash;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {
			Element::Physical
		};
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Dagger
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 2000, 2000, 2000, 2000, 2000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 30, 30, 30, 30, 30 };

		ad.Values = {
			{ 1200, 1200, 1200, 1200, 1200 }, // Damage
			{ 1000, 1000, 1000, 1000, 1000 }, // Bleed Duration
			{ 100, 111, 122, 133, 144} // Bleed Damage
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string duration = std::to_string(Values[1][rank] / 100);
			std::string bleedDmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
				bleedDmg = "#damage " + std::to_string(Values[2][rank] / 10) + "." + std::to_string(Values[2][rank] % 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
				bleedDmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[2][rank])) + " #default ";
			}

			desc = "Slash the target causing a deep wound, dealing " + dmg + "physical damage and an additional " + bleedDmg + "every 1s for " + duration + "s. Requires a sword, axe, or dagger.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::RendingSlash, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ShadowEnergy] = [] {
		AbilityData ad;

		ad.Name = "Shadow Energy";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ShadowEnergy;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Dark };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 12 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 250 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Imbue yourself with shadow energy, addind " + value + " dark damage to every attack.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			messageLog.AddMessage(user->GetName() + " casts Shadow Energy.");
			if (!targets.empty()) {
				Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::ShadowEnergy, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ShadowFlay] = [] {
		AbilityData ad;

		ad.Name = "Shadow Flay";
		ad.Icon = "shadow_flay.png";
		ad.ID = AbilityID::ShadowFlay;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Dark };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 250, 250, 250, 250, 250 };
		ad.Cooldown = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 11, 11, 11, 11, 11 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 2400, 2520, 2640, 2760, 2880 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Assault the target with shadows, dealing " + value + "dark damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ShiningPrism] = [] {
		AbilityData ad;

		ad.Name = "Shining Prism";
		ad.Icon = "shining_prism.png";
		ad.ID = AbilityID::ShiningPrism;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Light };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 175, 175, 175, 175, 175 };
		ad.Cooldown = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 10, 10, 10, 10, 10 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1400, 1470, 1540, 1610, 1680 },
			{ 200, 210, 220, 230, 240 }, // Heal
			{ 1500, 1500, 1500, 1500, 1500 } // Debuff Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string heal;
			std::string duration = std::to_string(Values[2][rank] / 100);

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
				heal = "#heal " + std::to_string(Values[1][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
				heal = "#heal " + std::to_string(Combat::SpellHealEstimate(user, eventOptions, Values[1][rank])) + " #default ";
			}

			desc = "Encase the target in a prism of light, dealing " + value + "light damage and causing all direct hits against the target to heal the attacker for " + heal + "HP. Lasts " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::ShiningPrism, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Shock] = [] {
		AbilityData ad;

		ad.Name = "Shock";
		ad.Icon = "shock.png";
		ad.ID = AbilityID::Shock;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Lightning };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 150, 150, 150, 150, 150 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 4, 4, 4, 4, 4 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 700, 735, 770, 805, 840 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Arc lightning at your target, dealing " + value + "lightning damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::SlimeSplash] = [] {
		AbilityData ad;

		ad.Name = "Slime Splash";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::SlimeSplash;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = { Element::Water };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 250 };
		ad.UseTime = { 150 };
		ad.Cooldown = { 600 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 50 };

		ad.Values = {
			{ 900 },
			{ 100 }, // Haste Reduction
			{ 500 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 750 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string reduction = std::to_string(Values[1][rank] / 10);
			std::string duration = std::to_string(Values[2][rank] / 100);

			if (user != nullptr) {
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
			}
			else {
				value = std::to_string(Values[0][rank] / 10) + "% Attack Power";
			}
			desc = "Deal #damage " + value + " #default water damage to the target and reduce its haste by " + reduction + "% for " + duration + "s.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::SlimeSplash, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Splash] = [] {
		AbilityData ad;

		ad.Name = "Splash";
		ad.Icon = "splash.png";
		ad.ID = AbilityID::Splash;

		ad.Categories = {
			Category::AreaOfEffect,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Water };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 150, 150, 150, 150, 150 };
		ad.Cooldown = { 900, 900, 900, 900, 900 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 4, 4, 4, 4, 4 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 500, 525, 550, 575, 600 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return TileMath::AreaOfEffect(cursorTarget, 150);
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Hurl a ball of water that splashes the targeted location, dealing " + value + "water damage in an area with radius 1.5.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			for (auto& target : targets) {
				Combat::SpellDamage(user, target, eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Stalagmite] = [] {
		AbilityData ad;

		ad.Name = "Stalagmite";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Stalagmite;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Physical };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 5, 5, 5, 5, 5 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 900, 945, 990, 1035, 1080 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "A pillar of rock erupts from the ground, dealing " + value + " physical damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Teleport] = [] {
		AbilityData ad;

		ad.Name = "Teleport";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Teleport;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 100, 100, 100, 100, 100 };
		ad.Cooldown = { 2000, 2000, 2000, 2000, 2000 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 14, 13, 12, 11, 10 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 1000, 1000, 1000, 1000, 1000 } // Min Distance
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000, 1000, 1000, 1000, 1000 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string minDistance = std::to_string(Values[0][rank] / 100);

			desc = "Teleports the caster to a random tile at least " + minDistance + " tiles away.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			std::vector<sf::Vector2i> possibleTiles;
			DungeonScene* dungeon = user->GetDungeonScene();
			auto size = dungeon->GetDungeonSize();
			auto userLocation = user->GetLocation();
			for (size_t x = 0; x < size.x; x++) {
				for (size_t y = 0; y < size.y; y++) {
					sf::Vector2i tile{ static_cast<int>(x), static_cast<int>(y) };
					if (dungeon->IsWalkable(user, tile) && !dungeon->IsOccupiedByActor(tile)) {
						int distance = static_cast<int>(TileMath::Distance(userLocation, tile) * 100.0);
						if (distance >= Values[0][rank]) {
							possibleTiles.push_back(tile);
						}
					}
				}
			}
			if (!possibleTiles.empty()) {
				size_t index = Random::RandomSizeT(0, possibleTiles.size() - 1);
				user->Warp(possibleTiles[index]);
				dungeon->UpdateVision();
			}
			else {
				messageLog.AddMessage("Teleport failed!");
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ThunderStrike] = [] {
		AbilityData ad;

		ad.Name = "Thunder Strike";
		ad.Icon = "thunder_strike.png";
		ad.ID = AbilityID::ThunderStrike;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {
			Element::Physical
		};
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Mace,
			EquipType::Dagger,
			EquipType::Spear,
			EquipType::Staff
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { -1, -1, -1, -1, -1 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1800, 1800, 1800, 1800, 1800 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 40, 40, 40, 40, 40 };

		ad.Values = {
			{ 1500, 1575, 1650, 1725, 1800 }, // Damage
			{ 300, 300, 300, 300, 300 } // Stun Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string stun = std::to_string(Values[1][rank] / 100);

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Strike your target with a thunderous crack, dealing " + dmg + "physical damage and stunning for " + stun + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::ThunderStrike, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::TornadoStrike] = [] {
		AbilityData ad;

		ad.Name = "Tornado Strike";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::TornadoStrike;

		ad.Categories = {
			Category::AreaOfEffect,
			Category::Damaging,
			Category::Attack,
			Category::Skill,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {
			EquipType::Sword,
			EquipType::Axe,
			EquipType::Mace,
			EquipType::Dagger,
			EquipType::Spear,
			EquipType::Staff
		};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { -1000, -1000, -1000, -1000, -1000 };
		ad.Cooldown = { 1200, 1200, 1200, 1200, 1200 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 50, 45, 45, 40, 40 };

		ad.Values = {
			{ 700, 700, 770, 770, 840 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { -1, -1, -1, -1, -1 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			std::vector<sf::Vector2i> area(TileMath::AreaOfEffect(cursorTarget, user->GetAttackRange()));
			
			area.erase(std::remove(area.begin(), area.end(), user->GetLocation()), area.end());

			return area;
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power#default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Whirl your weapon with the power of wind, dealing " + dmg + " weapon damage to all enemies in attack range.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				for (auto& t : targets) {
					Combat::SkillDamage(user, t, eventOptions, Values[0][rank]);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Trample] = [] {
		AbilityData ad;

		ad.Name = "Trample";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Trample;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Attack,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { -1 };
		ad.UseTime = { -1000 };
		ad.Cooldown = { 500 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 30 };

		ad.Values = {
			{ 500 }, // Damage
			{ 50 } // Stun Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = true;
		ad.CanCrit = true;
		ad.CanDoubleStrike = true;

		ad.HitChance = { 375 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string dmg;
			std::string stun = std::to_string(Values[1][rank] / 100) + "." + std::to_string(Values[1][rank] / 10);

			if (user == nullptr) {
				dmg = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				dmg = "#damage " + std::to_string(Combat::SkillDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}

			desc = "Hit the target 3 times. Each hit deals " + dmg + "weapon damage and stuns for " + stun + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				for (size_t i = 0; i < 3; i++) {
					EventResult result = Combat::SkillDamage(user, targets[0], eventOptions, Values[0][rank]);
					if (result.DidHit) {
						Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Trample, rank);
					}
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::Venom] = [] {
		AbilityData ad;

		ad.Name = "Venom";
		ad.Icon = "venom.png";
		ad.ID = AbilityID::Venom;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Poison };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 100, 100, 100, 100, 100 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 5, 5, 5, 5, 5 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 400, 400, 400, 400, 400 },
			{ 100, 110, 110, 120, 120 }, // Venom Aura Damage
			{ 1000, 1000, 1100, 1100, 1200 } // Venom Aura Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string dotValue;
			std::string dotDuration;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
				dotValue = "#damage " + std::to_string(Values[1][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
				dotValue = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[1][rank])) + " #default ";
			}
			dotDuration = std::to_string(Values[2][rank] / 100);

			desc = "Fling venom at your target, dealing " + value + "poison damage and an additional " + dotValue + " poison damage every 1s for " + dotDuration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				auto result = Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
				if (result.DidHit) {
					Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Venom, rank);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::WaterBolt] = [] {
		AbilityData ad;

		ad.Name = "Water Bolt";
		ad.Icon = "water_bolt.png";
		ad.ID = AbilityID::WaterBolt;

		ad.Categories = {
			Category::SingleTarget,
			Category::Damaging,
			Category::Spell,
			Category::Direct
		};
		ad.Elements = { Element::Water };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 350, 350, 350, 350, 350 };
		ad.UseTime = { 200, 200, 200, 200, 200 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 1, 1, 1, 1, 1 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 4, 3, 3, 2, 2 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 700, 700, 770, 770, 840 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = true;
		ad.CanBlock = true;
		ad.CanCounter = false;
		ad.CanCrit = true;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 800, 800, 800, 800, 800 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = true;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}

			desc = "Fire a bolt of water at your target, dealing " + value + " water damage.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();

	// Potions
	list[AbilityID::PotionFruitJuice] = [] {
		AbilityData ad;

		ad.Name = "Fruit Juice";
		ad.Icon = "heal.png";
		ad.ID = AbilityID::PotionFruitJuice;

		ad.Categories = {
			Category::SingleTarget,
			Category::Healing,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 1 },
			{ 1 },
			{ 1 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			if (user == nullptr) {
				desc = "Restores #heal 1 #default HP, #spell 1 #default MP, and #skill 1 #default SP. Refreshing!";
			}
			else {
				desc = "Restores #heal 1 #default HP, #spell 1 #default MP, and #skill 1 #default SP. Refreshing!";
			}

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::FixedHeal(user, targets[0], eventOptions, Values[0][rank], AttributeType::HP);
				Combat::FixedHeal(user, targets[0], eventOptions, Values[1][rank], AttributeType::MP);
				Combat::FixedHeal(user, targets[0], eventOptions, Values[2][rank], AttributeType::SP);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PotionMinorHealing] = [] {
		AbilityData ad;

		ad.Name = "Minor Healing Potion";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::PotionMinorHealing;

		ad.Categories = {
			Category::SingleTarget,
			Category::Healing,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 80 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string heal = std::to_string(Values[0][rank]);

			desc = "Restores #heal " + heal + " #default HP.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::FixedHeal(user, targets[0], eventOptions, Values[0][rank], AttributeType::HP);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PotionMinorMana] = [] {
		AbilityData ad;

		ad.Name = "Minor Mana Potion";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::PotionMinorMana;

		ad.Categories = {
			Category::SingleTarget,
			Category::Healing,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 30 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			if (user == nullptr) {
				desc = "Restores #spell 30 #default MP.";
			}
			else {
				desc = "Restores #spell 30 #default MP.";
			}

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::FixedHeal(user, targets[0], eventOptions, Values[0][rank], AttributeType::MP);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PotionSpeed] = [] {
		AbilityData ad;

		ad.Name = "Speed Potion";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::PotionSpeed;

		ad.Categories = {
			Category::SingleTarget
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 250 },
			{ 250 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			desc = "Increases haste and movement speed by " + std::to_string(Values[0][rank] / 10) + "% for 30s.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Speed, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::PotionStamina] = [] {
		AbilityData ad;

		ad.Name = "Stamina Potion";
		ad.Icon = "attack.png";
		ad.ID = AbilityID::PotionStamina;

		ad.Categories = {
			Category::SingleTarget,
			Category::Healing,
			Category::Direct
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 100 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			if (user == nullptr) {
				desc = "Restores #skill 100 #default SP.";
			}
			else {
				desc = "Restores #skill 100 #default SP.";
			}

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::FixedHeal(user, targets[0], eventOptions, Values[0][rank], AttributeType::SP);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();

	// Scrolls
	list[AbilityID::ScrollIdentify] = [] {
		AbilityData ad;

		ad.Name = "Identify Scroll";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ScrollIdentify;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			desc = "Identifies an item.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (records.IsIdentified(ItemID::ScrollIdentify)) {
				user->GetDungeonScene()->SetIdentifyMode(true);
			}
			else {
				messageLog.AddMessage("The #item Scroll of Identify #default identified itself.");
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ScrollLightningStorm] = [] {
		AbilityData ad;

		ad.Name = "Lightning Storm Scroll";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ScrollLightningStorm;

		ad.Categories = {
			Category::AreaOfEffect,
			Category::Direct,
			Category::Damaging,
			Category::Spell
		};
		ad.Elements = { Element::Lightning };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 45 }, // Base Damage
			{ 5 } // Bonus Per Level
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string damage;

			if (user != nullptr) {
				int stormDamage = Values[0][rank] + Values[1][rank] * user->GetLevel();
				damage = "#damage " + std::to_string(stormDamage) + " #default ";
			}
			else {
				damage = "#damage " + std::to_string(Values[0][rank]) + " plus " + std::to_string(Values[1][rank]) + " per level #default ";
			}

			desc = "Deals " + damage + "lightning damage to all enemies within 3.5 range.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			auto area = TileMath::AreaOfEffect(cursor, 350);
			targets = user->GetDungeonScene()->GetActorsInArea(area);
			int damage = Values[0][rank] + Values[1][rank] * user->GetLevel();
			for (auto& target : targets) {
				if (user != target) {
					Combat::FixedDamage(user, target, eventOptions, damage);
				}
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ScrollPhaseDoor] = [] {
		AbilityData ad;

		ad.Name = "Phase Door Scroll";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ScrollPhaseDoor;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 300 }, // Min Distance
			{ 900 } // Max Distance
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string minDistance = std::to_string(Values[0][rank] / 100);
			std::string maxDistance = std::to_string(Values[1][rank] / 100);

			desc = "Teleports the caster to a random tile between " + minDistance + " and " + maxDistance + " tiles away.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			std::vector<sf::Vector2i> possibleTiles;
			DungeonScene* dungeon = user->GetDungeonScene();
			auto size = dungeon->GetDungeonSize();
			auto userLocation = user->GetLocation();
			for (size_t x = 0; x < size.x; x++) {
				for (size_t y = 0; y < size.y; y++) {
					sf::Vector2i tile{ static_cast<int>(x), static_cast<int>(y) };
					if (dungeon->IsWalkable(user, tile) && !dungeon->IsOccupiedByActor(tile)) {
						int distance = static_cast<int>(TileMath::Distance(userLocation, tile) * 100.0);
						if (distance >= Values[0][rank] && distance <= Values[1][rank]) {
							possibleTiles.push_back(tile);
						}
					}
				}
			}
			if (!possibleTiles.empty()) {
				size_t index = Random::RandomSizeT(0, possibleTiles.size() - 1);
				user->Warp(possibleTiles[index]);
				dungeon->UpdateVision();
			}
			else {
				messageLog.AddMessage("Phase Door failed!");
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ScrollSpellProtection] = [] {
		AbilityData ad;

		ad.Name = "Spell Protection Scroll";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ScrollSpellProtection;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 500 },
			{ 1500 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			desc = "Increases spell defence by " + std::to_string(Values[0][rank] / 10) + "% for " + std::to_string(Values[1][rank] / 100) + "s.";

			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::SpellProtection, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ScrollTeleport] = [] {
		AbilityData ad;

		ad.Name = "Teleport Scoll";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ScrollTeleport;

		ad.Categories = {
			Category::SingleTarget,
			Category::Spell
		};
		ad.Elements = { Element::Arcane };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 4;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 1000 } // Min Distance
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string minDistance = std::to_string(Values[0][rank] / 100);

			desc = "Teleports the caster to a random tile at least " + minDistance + " tiles away.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			std::vector<sf::Vector2i> possibleTiles;
			DungeonScene* dungeon = user->GetDungeonScene();
			auto size = dungeon->GetDungeonSize();
			auto userLocation = user->GetLocation();
			for (size_t x = 0; x < size.x; x++) {
				for (size_t y = 0; y < size.y; y++) {
					sf::Vector2i tile{ static_cast<int>(x), static_cast<int>(y) };
					if (dungeon->IsWalkable(user, tile) && !dungeon->IsOccupiedByActor(tile)) {
						int distance = static_cast<int>(TileMath::Distance(userLocation, tile) * 100.0);
						if (distance >= Values[0][rank]) {
							possibleTiles.push_back(tile);
						}
					}
				}
			}
			if (!possibleTiles.empty()) {
				size_t index = Random::RandomSizeT(0, possibleTiles.size() - 1);
				user->Warp(possibleTiles[index]);
				dungeon->UpdateVision();
			}
			else {
				messageLog.AddMessage("Teleport failed!");
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();

	// Misc
	list[AbilityID::Rest] = [] {
		AbilityData ad;

		ad.Name = "Rest";
		ad.Icon = "heal.png";
		ad.ID = AbilityID::Rest;

		ad.Categories = {
			Category::SingleTarget,
			Category::Healing
		};
		ad.Elements = { Element::Healing };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = false;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 100 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 1 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 0 }
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 1000 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			desc = "Restores 5% + 1 HP, MP, and SP every 1s for 20s. Taking direct damage will remove this effect.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			messageLog.AddMessage(user->GetName() + " begins to rest.");
			if (!targets.empty()) {
				Combat::AddAuraStack(user, targets[0], eventOptions, AuraID::Resting, rank);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();

	// Passive Abilities
	list[AbilityID::Constitution] = [] {
		AbilityData ad;

		ad.Name = "Constitution";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Constitution;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 40, 80, 120, 160, 200 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::HPMulti, ad.Values[0][0]) } },
			{ { StatMod(StatModType::HPMulti, ad.Values[0][1]) } },
			{ { StatMod(StatModType::HPMulti, ad.Values[0][2]) } },
			{ { StatMod(StatModType::HPMulti, ad.Values[0][3]) } },
			{ { StatMod(StatModType::HPMulti, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = std::to_string(Values[0][rank] / 10);
			}
			else {
				value = std::to_string(Values[0][rank] / 10);
			}

			desc = "Increases your maximum HP by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::DeadlyForce] = [] {
		AbilityData ad;

		ad.Name = "Deadly Force";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::DeadlyForce;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 30, 60, 90, 120, 150 }, // Damage Bonus
			{ 500, 500, 500, 500, 500 } // Duration
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value = std::to_string(Values[0][rank] / 10);
			std::string duration = std::to_string(Values[1][rank] / 100);


			desc = "Dealing a direct critical strike increases your damage by " + value + "% for " + duration + "s.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {

		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {
			if (eventType == EventType::Damage) {
				if (eventResult.DidCrit && std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					int rank = ability->GetCurrentRank();
					EventOptions eo;
					Combat::AddAuraStack(user, user, eo, AuraID::DeadlyForce, rank);
				}
			}
		};

		return ad;
	}();
	list[AbilityID::Focus] = [] {
		AbilityData ad;

		ad.Name = "Focus";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Focus;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 20, 40, 60, 80, 100 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::CritChance, ad.Values[0][0]) } },
			{ { StatMod(StatModType::CritChance, ad.Values[0][1]) } },
			{ { StatMod(StatModType::CritChance, ad.Values[0][2]) } },
			{ { StatMod(StatModType::CritChance, ad.Values[0][3]) } },
			{ { StatMod(StatModType::CritChance, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = std::to_string(Values[0][rank] / 10);
			}
			else {
				value = std::to_string(Values[0][rank] / 10);
			}

			desc = "Increases your critical strike chance by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ImprovedDexterity] = [] {
		AbilityData ad;

		ad.Name = "Improved Dexterity";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ImprovedDexterity;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 20, 40, 60, 80, 100 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::DEXMulti, ad.Values[0][0]) } },
			{ { StatMod(StatModType::DEXMulti, ad.Values[0][1]) } },
			{ { StatMod(StatModType::DEXMulti, ad.Values[0][2]) } },
			{ { StatMod(StatModType::DEXMulti, ad.Values[0][3]) } },
			{ { StatMod(StatModType::DEXMulti, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value = std::to_string(Values[0][rank] / 10);

			desc = "Increases your dexterity by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ImprovedMagic] = [] {
		AbilityData ad;

		ad.Name = "Improved Magic";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ImprovedMagic;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 20, 40, 60, 80, 100 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::MAGMulti, ad.Values[0][0]) } },
			{ { StatMod(StatModType::MAGMulti, ad.Values[0][1]) } },
			{ { StatMod(StatModType::MAGMulti, ad.Values[0][2]) } },
			{ { StatMod(StatModType::MAGMulti, ad.Values[0][3]) } },
			{ { StatMod(StatModType::MAGMulti, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value = std::to_string(Values[0][rank] / 10);

			desc = "Increases your magic by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ImprovedSpirit] = [] {
		AbilityData ad;

		ad.Name = "Improved Spirit";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ImprovedSpirit;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 20, 40, 60, 80, 100 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::SPIMulti, ad.Values[0][0]) } },
			{ { StatMod(StatModType::SPIMulti, ad.Values[0][1]) } },
			{ { StatMod(StatModType::SPIMulti, ad.Values[0][2]) } },
			{ { StatMod(StatModType::SPIMulti, ad.Values[0][3]) } },
			{ { StatMod(StatModType::SPIMulti, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value = std::to_string(Values[0][rank] / 10);

			desc = "Increases your spirit by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ImprovedStrength] = [] {
		AbilityData ad;

		ad.Name = "Improved Strength";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ImprovedStrength;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 20, 40, 60, 80, 100 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::STRMulti, ad.Values[0][0]) } },
			{ { StatMod(StatModType::STRMulti, ad.Values[0][1]) } },
			{ { StatMod(StatModType::STRMulti, ad.Values[0][2]) } },
			{ { StatMod(StatModType::STRMulti, ad.Values[0][3]) } },
			{ { StatMod(StatModType::STRMulti, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value = std::to_string(Values[0][rank] / 10);

			desc = "Increases your strength by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ImprovedVitality] = [] {
		AbilityData ad;

		ad.Name = "Improved Vitality";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ImprovedVitality;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 20, 40, 60, 80, 100 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::VITMulti, ad.Values[0][0]) } },
			{ { StatMod(StatModType::VITMulti, ad.Values[0][1]) } },
			{ { StatMod(StatModType::VITMulti, ad.Values[0][2]) } },
			{ { StatMod(StatModType::VITMulti, ad.Values[0][3]) } },
			{ { StatMod(StatModType::VITMulti, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value = std::to_string(Values[0][rank] / 10);

			desc = "Increases your vitality by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::ManaSpring] = [] {
		AbilityData ad;

		ad.Name = "Mana Spring";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::ManaSpring;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 4;

		ad.Range = { 0, 0, 0, 0, 0 };
		ad.UseTime = { 0, 0, 0, 0, 0 };
		ad.Cooldown = { 0, 0, 0, 0, 0 };
		ad.MaxCharges = { 0, 0, 0, 0, 0 };
		ad.HPCost = { 0, 0, 0, 0, 0 };
		ad.MPCost = { 0, 0, 0, 0, 0 };
		ad.SPCost = { 0, 0, 0, 0, 0 };

		ad.Values = {
			{ 40, 80, 120, 160, 200 }
		};
		ad.PassiveBonuses = {
			{ { StatMod(StatModType::MPMulti, ad.Values[0][0]) } },
			{ { StatMod(StatModType::MPMulti, ad.Values[0][1]) } },
			{ { StatMod(StatModType::MPMulti, ad.Values[0][2]) } },
			{ { StatMod(StatModType::MPMulti, ad.Values[0][3]) } },
			{ { StatMod(StatModType::MPMulti, ad.Values[0][4]) } }

		};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0, 0, 0, 0, 0 };
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = std::to_string(Values[0][rank] / 10);
			}
			else {
				value = std::to_string(Values[0][rank] / 10);
			}

			desc = "Increases your maximum MP by " + value + "%.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {
			if (!targets.empty()) {
				Combat::SpellDamage(user, targets[0], eventOptions, Values[0][rank]);
			}
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {

		};

		return ad;
	}();
	list[AbilityID::VenomousWound] = [] {
		AbilityData ad;

		ad.Name = "Venomous Wound";
		ad.Icon = "poison.png";
		ad.ID = AbilityID::VenomousWound;

		ad.Categories = {
			Category::Passive,
			Category::Attack,
			Category::OverTime
		};
		ad.Elements = { Element::Poison };
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 0 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 0 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {
			{ 50 }, // Damage
			{ 500 }, // Duration
 			{ 10 } // Max Stacks
		};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;
			std::string value;
			std::string duration = std::to_string(Values[1][rank] / 100);
			std::string stacks = std::to_string(Values[2][rank]);

			if (user == nullptr) {
				value = std::to_string(Values[0][rank] / 10);
			}
			else {
				value = std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank]));
			}

			desc = "Attacks inflict Venomous Wound, dealing #damage " + value + " #default poison damage every 1s for " + duration + "s. Stacks up to " + stacks + " times.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {

		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {
			if (eventType == EventType::Damage) {
				auto& cat = eventOptions.Categories;
				if (std::find(cat.begin(), cat.end(), Category::Attack) != cat.end() && std::find(cat.begin(), cat.end(), Category::Direct) != cat.end()) {
					Combat::AddAuraStack(user, target, eventOptions, AuraID::VenomousWound, 0);
				}
			}
		};

		return ad;
	}();
	list[AbilityID::Vigor] = [] {
		AbilityData ad;

		ad.Name = "Vigor";
		ad.Icon = "placeholder.png";
		ad.ID = AbilityID::Vigor;

		ad.Categories = {
			Category::Passive
		};
		ad.Elements = {};
		ad.RequiredWeaponTypes = {};

		ad.IsPassive = true;
		ad.MaxRank = 0;

		ad.Range = { 0 };
		ad.UseTime = { 0 };
		ad.Cooldown = { 0 };
		ad.MaxCharges = { 0 };
		ad.HPCost = { 0 };
		ad.MPCost = { 0 };
		ad.SPCost = { 0 };

		ad.Values = {};
		ad.PassiveBonuses = {};

		ad.CanDodge = false;
		ad.CanBlock = false;
		ad.CanCounter = false;
		ad.CanCrit = false;
		ad.CanDoubleStrike = false;

		ad.HitChance = { 0 };
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.FixedRange = false;
		ad.HideRange = false;

		ad.IsProjectile = false;
		ad.IgnoreLineOfSight = false;

		ad.AreaIgnoreLineOfSight = false;
		ad.AreaIgnoreBodyBlock = false;

		ad.GetTargetArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{ cursorTarget };
		};

		ad.GetExtraArea = [&](Actor* user, DungeonScene* dungeonScene, sf::Vector2i cursorTarget, int rank) {
			return std::vector<sf::Vector2i>{};
		};

		ad.CustomUseCondition = []() {
			return true;
		};
		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank) {
			std::string desc;

			desc = "Increases damage by up to 100%, based on current HP.";
			return desc;
		};
		ad.Execute = [Values = ad.Values](Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& targetArea, EventOptions& eventOptions, int rank) {

		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount, Ability* ability) {
			if (eventType == EventType::PreCalcDamage) {
				int damageMult = user->GetCurrentHP() * 1000 / user->GetMaxHP();
				amount = amount * (1000 + damageMult) / 1000;
			}
		};

		return ad;
	}();

	return list;
}

std::unordered_map<AbilityID, AbilityData> Ability::abilityList = initList();