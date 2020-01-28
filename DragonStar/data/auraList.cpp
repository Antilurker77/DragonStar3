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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank]);
			desc = "Restores 5% + 1 every 1s. Removed when taking direct damage.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			int hp = target->GetMaxHP() / 20 + 1;
			int mp = target->GetMaxMP() / 20 + 1;
			int sp = target->GetMaxSP() / 20 + 1;

			Combat::FixedHeal(user, target, eventOptions, hp, AttributeType::HP);
			Combat::FixedHeal(user, target, eventOptions, mp, AttributeType::MP);
			Combat::FixedHeal(user, target, eventOptions, sp, AttributeType::SP);
		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank]);
			desc = "Increases magic by " + value + ".";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 100);
			desc = "Stunned for " + value + "s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 10);
			desc = "Movement speed reduced by " + value + "%.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
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

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			return;
		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			Combat::SkillDamage(user, target, eventOptions, Values[0][rank]);
		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			return;
		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
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

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			
		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			
		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			
		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
			std::string desc;
			std::string value;

			value = std::to_string(Values[0][rank] / 100);
			desc = "Stunned for " + value + "s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {

		};

		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

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

		ad.GetDescription = [Values = ad.Values](Actor* user, EventOptions& eventOptions, int rank){
			std::string desc;
			std::string value;

			if (user == nullptr) {
				value = "#damage " + std::to_string(Values[0][rank] / 10) + "% SP#default ";
			}
			else {
				value = "#damage " + std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank])) + "#default ";
			}
			desc = "Deals " + value + " poison damage every 1s.";

			return desc;
		};

		ad.OnApplication = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			return;
		};
		ad.OnTick = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			Combat::SpellDamage(user, target, eventOptions, Values[0][rank]);
		};
		ad.OnExpiry = [Values = ad.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank) {
			return;
		};
		ad.OnEvent = [Values = ad.Values](EventType eventType, EventOptions& auraOptions, int rank, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return ad;
	}();

	return list;
}

std::unordered_map<AuraID, AuraData> Aura::auraList = initList();