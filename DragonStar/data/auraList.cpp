// ================================================================
//
// auraList.cpp
//
// ================================================================

#include "aura.hpp"

#include <iostream>
#include "id/auraID.hpp"
#include "id/category.hpp"
#include "id/element.hpp"
#include "id/eventType.hpp"
#include "../core/combat.hpp"
#include "../entity/actor.hpp"

static std::unordered_map<AuraID, AuraData> initList() {
	std::unordered_map<AuraID, AuraData> list;

	list[AuraID::Resting] = [] {
		AuraData ad;

		ad.Name = "Resting";
		ad.Icon = "heal.png";
		ad.AuraID = AuraID::Resting;

		ad.Categories = {
			Category::Healing,
			Category::OverTime
		};
		ad.Elements = {
			
		};

		ad.MaxRank = 0;

		ad.BaseDuration = { 2000 };
		ad.MaxDuration = { 2000 };
		ad.MaxStacks = { 0 };

		ad.Values = {};
		ad.StatMods = {};

		ad.IsBuff = true;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = true;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank]);
			desc = "Restores 5% + 1 every 1s. Removed when taking direct damage.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			int hp = target->GetMaxHP() / 20 + 1;
			int mp = target->GetMaxMP() / 20 + 1;
			int sp = target->GetMaxSP() / 20 + 1;

			Combat::FixedHeal(user, target, eventOptions, hp, AttributeType::HP);
			Combat::FixedHeal(user, target, eventOptions, mp, AttributeType::MP);
			Combat::FixedHeal(user, target, eventOptions, sp, AttributeType::SP);
		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damaged) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Damaging) != eventOptions.Categories.end()) {
						Combat::RemoveAuraStack(target, AuraID::Resting);
					}
				}
			}
		};

		return ad;
	}();

	list[AuraID::ArcanistGloves] = [] {
		AuraData ad;

		ad.Name = "Arcanist Gloves";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::ArcanistGloves;

		ad.Categories = {

		};
		ad.Elements = {
			Element::Arcane
		};

		ad.MaxRank = 0;

		ad.BaseDuration = { 1000 };
		ad.MaxDuration = { 1000 };
		ad.MaxStacks = { 1 };

		ad.Values = {
			{ 5 }
		};
		ad.StatMods = {
			{
				StatMod(StatModType::MAG, ad.Values[0][0])
			}
		};

		ad.IsBuff = true;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank]);
			desc = "Increases magic by " + value + ".";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::Boulder] = [] {
		AuraData ad;

		ad.Name = "Boulder";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::Boulder;

		ad.Categories = {

		};
		ad.Elements = {
			Element::Physical
		};

		ad.MaxRank = 0;

		ad.BaseDuration = { 200 };
		ad.MaxDuration = { 200 };
		ad.MaxStacks = { 1 };

		ad.Values = {
			{ 200 }
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = true;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 100);
			desc = "Stunned for " + value + "s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::Chilled] = []{
		AuraData ad;

		ad.Name = "Chilled";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::Chilled;

		ad.Categories = {};
		ad.Elements = { Element::Ice };

		ad.MaxRank = 4;

		ad.BaseDuration = { 500, 500, 500, 500, 500 };
		ad.MaxDuration = { 500, 500, 500, 500, 500 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{ -250, -250, -250, -250, -250 }
		};
		ad.StatMods = {
			{ StatMod(StatModType::MovementSpeed, ad.Values[0][0]) },
			{ StatMod(StatModType::MovementSpeed, ad.Values[0][1]) },
			{ StatMod(StatModType::MovementSpeed, ad.Values[0][2]) },
			{ StatMod(StatModType::MovementSpeed, ad.Values[0][3]) },
			{ StatMod(StatModType::MovementSpeed, ad.Values[0][4]) }
		};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = true;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 10);
			desc = "Movement speed reduced by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::CobraBite] = [] {
		AuraData ad;

		ad.Name = "Cobra Bite";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::CobraBite;

		ad.Categories = {
			Category::Damaging,
			Category::OverTime,
			Category::Attack,
			Category::SingleTarget
		};
		ad.Elements = {
			Element::Poison
		};

		ad.MaxRank = 0;

		ad.BaseDuration = { 500 };
		ad.MaxDuration = { 500 };
		ad.MaxStacks = { 3 };

		ad.Values = {
			{ 100 }
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = false;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = true;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::AttackDamageEstimate(user, eventOptions, Values[0][rank] * aura->GetCurrentStackSize())) + " #default ";
			}
			desc = "Deals " + value + "poison damage every 1s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};
		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			Combat::AttackDamage(user, target, eventOptions, Values[0][rank] * aura->GetCurrentStackSize());
		};
		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::CrushArmor] = [] {
		AuraData ad;

		ad.Name = "Crush Armor";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::CrushArmor;

		ad.Categories = {};
		ad.Elements = { Element::Physical };

		ad.MaxRank = 4;

		ad.BaseDuration = { 1250, 1312, 1375, 1437, 1500 };
		ad.MaxDuration = { 1250, 1312, 1375, 1437, 1500 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{ -250, -250, -250, -250, -250 }
		};
		ad.StatMods = {
			{ StatMod(StatModType::ArmorMulti, ad.Values[0][0]) },
			{ StatMod(StatModType::ArmorMulti, ad.Values[0][1]) },
			{ StatMod(StatModType::ArmorMulti, ad.Values[0][2]) },
			{ StatMod(StatModType::ArmorMulti, ad.Values[0][3]) },
			{ StatMod(StatModType::ArmorMulti, ad.Values[0][4]) }
		};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / -10);
			desc = "Reduces armor by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::CrushingBlow] = [] {
		AuraData ad;

		ad.Name = "Crushing Blow";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::CrushingBlow;

		ad.Categories = {

		};
		ad.Elements = {
			Element::Physical
		};

		ad.MaxRank = 4;

		ad.BaseDuration = { 300, 300, 300, 300, 300 };
		ad.MaxDuration = { 300, 300, 300, 300, 300 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{ 300, 300, 300, 300, 300 }
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = true;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 100);
			desc = "Stunned for " + value + "s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::Disarm] = [] {
		AuraData ad;

		ad.Name = "Disarm";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::Disarm;

		ad.Categories = {

		};
		ad.Elements = {
			Element::Physical
		};

		ad.MaxRank = 4;

		ad.BaseDuration = { 800, 800, 900, 900, 1000 };
		ad.MaxDuration = { 800, 800, 900, 900, 1000 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{ 800, 800, 900, 900, 1000 }
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = true;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 100);
			desc = "Disarmed for " + value + "s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::ElementalEnergy] = [] {
		AuraData ad;

		ad.Name = "Elemental Energy";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::ElementalEnergy;

		ad.Categories = { Category::Spell };
		ad.Elements = {
			Element::Arcane,
			Element::Fire,
			Element::Water,
			Element::Ice,
			Element::Lightning,
			Element::Poison,
			Element::Light,
			Element::Dark
		};

		ad.MaxRank = 4;

		ad.BaseDuration = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxDuration = { 1500, 1500, 1500, 1500, 1500 };
		ad.MaxStacks = { 1 };

		ad.Values = {
			{ 200, 210, 220, 230, 240 } // Elemental Damage
		};
		ad.StatMods = {
			{ StatMod(StatModType::Damage, ad.Values[0][0], ad.Elements) },
			{ StatMod(StatModType::Damage, ad.Values[0][1], ad.Elements) },
			{ StatMod(StatModType::Damage, ad.Values[0][2], ad.Elements) },
			{ StatMod(StatModType::Damage, ad.Values[0][3], ad.Elements) },
			{ StatMod(StatModType::Damage, ad.Values[0][4], ad.Elements) }
		};

		ad.IsBuff = true;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 10);
			desc = "Increases elemental damage dealt by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::FlameStrike] = [] {
		AuraData ad;

		ad.Name = "Flame Strike";
		ad.Icon = "flame_strike.png";
		ad.AuraID = AuraID::FlameStrike;

		ad.Categories = {};
		ad.Elements = { Element::Fire };

		ad.MaxRank = 4;

		ad.BaseDuration = { 500, 500, 500, 500, 500 };
		ad.MaxDuration = { 500, 500, 500, 500, 500 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{ 100, 100, 100, 100, 100 }
		};
		ad.StatMods = {
			{ StatMod(StatModType::Damage, ad.Values[0][0], Element::Fire), StatMod(StatModType::SnapshotDamage, ad.Values[0][0], Element::Fire) },
			{ StatMod(StatModType::Damage, ad.Values[0][1], Element::Fire), StatMod(StatModType::SnapshotDamage, ad.Values[0][1], Element::Fire) },
			{ StatMod(StatModType::Damage, ad.Values[0][2], Element::Fire), StatMod(StatModType::SnapshotDamage, ad.Values[0][2], Element::Fire) },
			{ StatMod(StatModType::Damage, ad.Values[0][3], Element::Fire), StatMod(StatModType::SnapshotDamage, ad.Values[0][3], Element::Fire) },
			{ StatMod(StatModType::Damage, ad.Values[0][4], Element::Fire), StatMod(StatModType::SnapshotDamage, ad.Values[0][4], Element::Fire) }
		};

		ad.IsBuff = true;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = true;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 10);
			desc = "Increases the damage of your next fire ability by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::Ignite] = [] {
		AuraData ad;

		ad.Name = "Ignite";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::Ignite;

		ad.Categories = {
			Category::Damaging,
			Category::OverTime,
			Category::Spell,
			Category::SingleTarget
		};
		ad.Elements = {
			Element::Fire
		};

		ad.MaxRank = 4;

		ad.BaseDuration = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxDuration = { 1300, 1300, 1300, 1300, 1300 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{150, 157, 165, 172, 180}
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = false;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = true;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}
			desc = "Deals " + value + "fire damage every 1s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};
		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			Combat::SpellDamage(user, target, eventOptions, Values[0][rank]);
		};
		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::Maul] = [] {
		AuraData ad;

		ad.Name = "Maul";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::Maul;

		ad.Categories = {
			Category::Damaging,
			Category::OverTime,
			Category::Attack,
			Category::SingleTarget
		};
		ad.Elements = {
			Element::Physical
		};

		ad.MaxRank = 0;

		ad.BaseDuration = { 300 };
		ad.MaxDuration = { 500 };
		ad.MaxStacks = { 1 };

		ad.Values = {
			{ 250 }
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = false;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = true;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}
			desc = "Deals " + value + "physical damage every 1s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			Combat::SkillDamage(user, target, eventOptions, Values[0][rank]);
		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::MysticBlast] = [] {
		AuraData ad;

		ad.Name = "Mystic Blast";
		ad.Icon = "mystic_blast.png";
		ad.AuraID = AuraID::MysticBlast;

		ad.Categories = {};
		ad.Elements = { Element::Arcane };

		ad.MaxRank = 4;

		ad.BaseDuration = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxDuration = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{ -300, -300, -300, -300, -300 }
		};
		ad.StatMods = {
			{ StatMod(StatModType::MagicArmorMulti, ad.Values[0][0]) },
			{ StatMod(StatModType::MagicArmorMulti, ad.Values[0][1]) },
			{ StatMod(StatModType::MagicArmorMulti, ad.Values[0][2]) },
			{ StatMod(StatModType::MagicArmorMulti, ad.Values[0][3]) },
			{ StatMod(StatModType::MagicArmorMulti, ad.Values[0][4]) }
		};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / -10);
			desc = "Reduces spell defense by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::RendingSlash] = [] {
		AuraData ad;

		ad.Name = "Rending Slash";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::RendingSlash;

		ad.Categories = {
			Category::Damaging,
			Category::OverTime,
			Category::Skill,
			Category::Attack,
			Category::SingleTarget
		};
		ad.Elements = {
			Element::Physical
		};

		ad.MaxRank = 4;

		ad.BaseDuration = { 1000, 1000, 1000, 1000, 1000 };
		ad.MaxDuration = { 1300, 1300, 1300, 1300, 1300 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{100, 111, 122, 133, 144}
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = false;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = true;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Attack Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}
			desc = "Deals " + value + "physical damage every 1s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			Combat::SkillDamage(user, target, eventOptions, Values[0][rank]);
		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::ShadowEnergy] = [] {
		AuraData ad;

		ad.Name = "Shadow Energy";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::ShadowEnergy;

		ad.Categories = {
			Category::Damaging,
			Category::Spell,
			Category::SingleTarget
		};
		ad.Elements = {
			Element::Dark
		};

		ad.MaxRank = 0;

		ad.BaseDuration = { 0 };
		ad.MaxDuration = { 0 };
		ad.MaxStacks = { 1 };

		ad.Values = {
			{ 250 }
		};
		ad.StatMods = {};

		ad.IsBuff = true;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = true;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% SP#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}
			desc = "Deals " + value + " bonus shadow damage on attacks.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			
		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			
		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			
		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						Combat::SpellDamage(user, target, auraOptions, Values[0][rank]);
					}
				}
			}
		};

		return ad;
	}();
	list[AuraID::SlimeSplash] = [] {
		AuraData ad;

		ad.Name = "Slime Splash";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::SlimeSplash;

		ad.Categories = {};
		ad.Elements = {};

		ad.MaxRank = 0;

		ad.BaseDuration = { 500 };
		ad.MaxDuration = { 500 };
		ad.MaxStacks = { 1 };

		ad.Values = {
			{ -100 } // Haste
		};
		ad.StatMods = {
			{ StatMod(StatModType::Haste, ad.Values[0][0]) }
		};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / -10);
			desc = "Reduces haste by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::Speed] = [] {
		AuraData ad;

		ad.Name = "Speed";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::Speed;

		ad.Categories = {};
		ad.Elements = {};

		ad.MaxRank = 0;

		ad.BaseDuration = { 3000 };
		ad.MaxDuration = { 3000 };
		ad.MaxStacks = { 1 };

		ad.Values = {
			{ 250 }, // Haste
			{ 250 } // Movement Speed
		};
		ad.StatMods = {
			{ StatMod(StatModType::Haste, ad.Values[0][0]), StatMod(StatModType::MovementSpeed, ad.Values[1][0]) }
		};

		ad.IsBuff = true;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0 };
		ad.BonusResistancePen = { 0 };
		ad.BonusCritChance = { 0 };
		ad.BonusCritPower = { 0 };
		ad.BonusDoubleStrikeChance = { 0 };
		ad.BonusHPLeech = { 0 };
		ad.BonusMPLeech = { 0 };
		ad.BonusSPLeech = { 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 10);
			desc = "Increases haste and movement speed by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::ThunderStrike] = [] {
		AuraData ad;

		ad.Name = "Thunder Strike";
		ad.Icon = "placeholder.png";
		ad.AuraID = AuraID::ThunderStrike;

		ad.Categories = {

		};
		ad.Elements = {
			Element::Physical
		};

		ad.MaxRank = 4;

		ad.BaseDuration = { 300, 300, 300, 300, 300 };
		ad.MaxDuration = { 300, 300, 300, 300, 300 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{ 300, 300, 300, 300, 300 }
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = true;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = true;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = false;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 100);
			desc = "Stunned for " + value + "s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();
	list[AuraID::Venom] = [] {
		AuraData ad;

		ad.Name = "Venom";
		ad.Icon = "venom.png";
		ad.AuraID = AuraID::Venom;

		ad.Categories = {
			Category::Damaging,
			Category::OverTime,
			Category::Spell,
			Category::SingleTarget
		};
		ad.Elements = {
			Element::Poison
		};

		ad.MaxRank = 4;

		ad.BaseDuration = { 1000, 1000, 1100, 1100, 1200 };
		ad.MaxDuration = { 1300, 1300, 1400, 1400, 1500 };
		ad.MaxStacks = { 1, 1, 1, 1, 1 };

		ad.Values = {
			{100, 110, 110, 120, 120}
		};
		ad.StatMods = {};

		ad.IsBuff = false;
		ad.Unique = false;
		ad.UniqueByActor = true;
		ad.ConsumeOnUse = false;
		ad.StacksExpireOneByOne = false;
		ad.MultiplyStatModsByStacks = false;

		ad.IsRest = false;
		ad.IsStun = false;
		ad.IsDisarm = false;
		ad.IsSilence = false;
		ad.IsSnare = false;

		ad.CanCrit = true;
		ad.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ad.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ad.BonusCritChance = { 0, 0, 0, 0, 0 };
		ad.BonusCritPower = { 0, 0, 0, 0, 0 };
		ad.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ad.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ad.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank, Aura* aura){
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% Spell Power #default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + " #default ";
			}
			desc = "Deals " + value + "poison damage every 1s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};
		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			Combat::SpellDamage(user, target, eventOptions, Values[0][rank]);
		};
		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, Aura* aura) {
			return;
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Aura* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();

	return list;
}

std::unordered_map<AuraID, AuraData> Aura::auraList = initList();