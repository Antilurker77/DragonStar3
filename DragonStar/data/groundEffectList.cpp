// ================================================================
//
// groundEffectList.cpp
//
// ================================================================

#include "groundEffect.hpp"

#include "id/abilityID.hpp"
#include "id/auraID.hpp"
#include "id/category.hpp"
#include "id/element.hpp"
#include "id/eventType.hpp"
#include "id/equipType.hpp"
#include "id/groundEffectID.hpp"
#include "id/itemID.hpp"
#include "../core/combat.hpp"
#include "../core/random.hpp"
#include "../core/records.hpp"
#include "../core/tileMath.hpp"
#include "../entity/actor.hpp"
#include "../scene/dungeonScene.hpp"
#include "../ui/messageLog.hpp"

static std::unordered_map<GroundEffectID, GroundEffectData> initList() {
	std::unordered_map<GroundEffectID, GroundEffectData> list;

	list[GroundEffectID::Blaze] = []{
		GroundEffectData ged;

		ged.Name = "Blaze";
		ged.GroundEffectID = GroundEffectID::Blaze;

		ged.Categories = {
			Category::Spell,
			Category::SingleTarget,
			Category::Damaging,
			Category::OverTime
		};
		ged.Elements = {
			Element::Fire
		};

		ged.MaxRank = 4;

		ged.Duration = { 500, 500, 500, 500, 500 };
		ged.TickRate = 100;

		ged.Values = {
			{ 200, 210, 220, 230, 240 }
		};
		ged.StatMods = {};

		ged.IsBuff = false;

		ged.IsStun = false;
		ged.IsDisarm = false;
		ged.IsSilence = false;

		ged.CanCrit = true;
		ged.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ged.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ged.BonusCritChance = { 0, 0, 0, 0, 0 };
		ged.BonusCritPower = { 0, 0, 0, 0, 0 };
		ged.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ged.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ged.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ged.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ged.GetDescription = [Values = ged.Values](Actor* user, EventOptions& eventOptions, int rank, GroundEffect* aura) {
			std::string desc;
			std::string damage;

			if (user != nullptr) {
				damage = std::to_string(Combat::SpellDamageEstimate(user, eventOptions, Values[0][rank]));
			}
			else {
				damage = std::to_string(Values[0][rank] / 10) + "% Spell Power";
			}

			desc = "Deals #damage " + damage + " #default fire damage every 1s.";

			return desc;
		};

		ged.OnTick = [Values = ged.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, GroundEffect* aura) {
			Combat::SpellDamage(user, target, eventOptions, Values[0][rank]);
		};

		ged.OnExpiry = [Values = ged.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, GroundEffect* aura) {
			return;
		};

		ged.OnEvent = [Values = ged.Values](EventType eventType, EventOptions& geOptions, int rank, GroundEffect* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			return;
		};


		return ged;
	}();
	list[GroundEffectID::CastingCircle] = [] {
		GroundEffectData ged;

		ged.Name = "Casting Circle";
		ged.GroundEffectID = GroundEffectID::CastingCircle;

		ged.Categories = {
			Category::Spell
		};
		ged.Elements = {
			Element::Arcane
		};

		ged.MaxRank = 4;

		ged.Duration = { 2000, 2000, 2000, 2000, 2000 };
		ged.TickRate = 0;

		ged.Values = {
			{ 100, 110, 110, 120, 120 }, // Spell Damage
			{ 100, 100, 110, 110, 120 } // Spell Haste
		};
		ged.StatMods = {
			{ StatMod(StatModType::Damage, ged.Values[0][0], Category::Spell), StatMod(StatModType::Haste, ged.Values[1][0], Category::Spell) },
			{ StatMod(StatModType::Damage, ged.Values[0][1], Category::Spell), StatMod(StatModType::Haste, ged.Values[1][1], Category::Spell) },
			{ StatMod(StatModType::Damage, ged.Values[0][2], Category::Spell), StatMod(StatModType::Haste, ged.Values[1][2], Category::Spell) },
			{ StatMod(StatModType::Damage, ged.Values[0][3], Category::Spell), StatMod(StatModType::Haste, ged.Values[1][3], Category::Spell) },
			{ StatMod(StatModType::Damage, ged.Values[0][4], Category::Spell), StatMod(StatModType::Haste, ged.Values[1][4], Category::Spell) }
		};

		ged.IsBuff = true;

		ged.IsStun = false;
		ged.IsDisarm = false;
		ged.IsSilence = false;

		ged.CanCrit = false;
		ged.BonusArmorPen = { 0, 0, 0, 0, 0 };
		ged.BonusResistancePen = { 0, 0, 0, 0, 0 };
		ged.BonusCritChance = { 0, 0, 0, 0, 0 };
		ged.BonusCritPower = { 0, 0, 0, 0, 0 };
		ged.BonusDoubleStrikeChance = { 0, 0, 0, 0, 0 };
		ged.BonusHPLeech = { 0, 0, 0, 0, 0 };
		ged.BonusMPLeech = { 0, 0, 0, 0, 0 };
		ged.BonusSPLeech = { 0, 0, 0, 0, 0 };

		ged.GetDescription = [Values = ged.Values](Actor* user, EventOptions& eventOptions, int rank, GroundEffect* aura) {
			std::string desc;
			std::string spellDamage = std::to_string(Values[0][rank] / 10);
			std::string spellHaste = std::to_string(Values[1][rank] / 10);

			desc = "Increases spell damage by " + spellDamage + "% and spell haste by " + spellHaste + "%.";

			return desc;
		};

		ged.OnTick = [Values = ged.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, GroundEffect* aura) {
			return;
		};

		ged.OnExpiry = [Values = ged.Values](Actor* user, Actor* target, EventOptions& eventOptions, int rank, GroundEffect* aura) {
			return;
		};

		ged.OnEvent = [Values = ged.Values](EventType eventType, EventOptions& geOptions, int rank, GroundEffect* aura, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			return;
		};


		return ged;
	}();

	return list;
}

std::unordered_map<GroundEffectID, GroundEffectData> GroundEffect::groundEffectList = initList();