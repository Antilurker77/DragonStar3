// ================================================================
//
// camera.cpp
//
// ================================================================

#include "combat.hpp"

#include <sstream>
#include "records.hpp"
#include "../core/random.hpp"
#include "../data/dataString.hpp"
#include "../data/item.hpp"
#include "../data/id/category.hpp"
#include "../data/id/eventType.hpp"
#include "../entity/actor.hpp"
#include "../entity/monster.hpp"
#include "../entity/player.hpp"
#include "../scene/dungeonScene.hpp"
#include "../ui/messageLog.hpp"


// Hit roll.
static bool hitRoll(Actor* user, Actor* target, EventOptions& eventOptions) {
	int accuracy = user->GetAccuracy(eventOptions, true);
	int evasion = target->GetEvasion(eventOptions, true);

	// If the target has 0 evasion, it cannot dodge even if base hit chance is less than 100%.
	if (evasion > 0) {
		int accuracyEvasionRatio = accuracy * 1000 / evasion;
		int hitChance = eventOptions.BaseHitChance * accuracyEvasionRatio / 1000;
		int roll = Random::RandomInt(1, 1000);
		if (roll <= hitChance) {
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}

// Block roll.
static bool blockRoll(Actor* user, Actor* target, EventOptions& eventOptions) {
	int blockChance = user->GetBlockChance(eventOptions, true);

	if (blockChance > 0) {
		int roll = Random::RandomInt(1, 1000);
		if (roll <= blockChance) {
			return true;
		}
	}

	return false;
}

// Crit roll.
static bool critRoll(Actor* user, Actor* target, EventOptions& eventOptions) {
	int critChance = eventOptions.BonusCritChance + eventOptions.SnapshotCritChance + user->GetCritChance(eventOptions, true) + target->GetCritProtection(eventOptions, true);

	if (critChance > 0) {
		int roll = Random::RandomInt(1, 1000);
		if (roll <= critChance) {
			return true;
		}
	}
	return false;
}

// Double strike roll.
static bool doubleStrikeRoll(Actor* user, Actor* target, EventOptions& eventOptions) {
	return false;
}

// Block damage reduction.
static int64_t applyBlock(Actor* user, Actor* target, EventOptions& eventOptions, int64_t damage) {
	return damage * 600 / 1000;
}

// Crit power.
static int64_t applyCrit(Actor* user, Actor* target, EventOptions& eventOptions, int64_t damage) {
	int64_t result = damage;
	int critPower = user->GetCritPower(eventOptions, true) * (1000 + eventOptions.BonusCritPower) / 1000;

	critPower = (critPower - 1000) * target->GetCritPowerProtection(eventOptions, true) / 1000;
	critPower += 1000;

	critPower = std::max(1000, critPower);

	result = result * critPower / 1000;

	return result;
}

// On hit damage.
static int64_t applyOnHitDamage(Actor* user, Actor* target, EventOptions& eventOptions, int64_t damage, bool consumeBuffs) {
	int64_t result = damage;
	result = result + user->GetOnHitDamage(eventOptions, consumeBuffs);
	return result;
}

// Damage dealt.
static int64_t applyDamageDealt(Actor* user, EventOptions& eventOptions, int64_t damage, bool consumeBuffs) {
	int64_t result = damage;
	result = result * user->GetDamage(eventOptions, consumeBuffs) / 1000;
	result = result * eventOptions.SnapshotDamage / 1000;
	return result;
}

// Damage taken.
static int64_t applyDamageTaken(Actor* user, Actor* target, EventOptions& eventOptions, int64_t damage) {
	int64_t result = damage;
	result = result * user->GetDamageTaken(eventOptions, true) / 1000;
	return result;
}

// Healing dealt.
static int64_t applyHealingDealt(Actor* user, EventOptions& eventOptions, int64_t heal, bool consumeBuffs) {
	return heal * user->GetHealing(eventOptions, true) / 1000;
}

// Healing taken.
static int64_t applyHealingTaken(Actor* user, Actor* target, EventOptions& eventOptions, int64_t heal) {
	return heal * user->GetHealingTaken(eventOptions, true) / 1000;
}

// Armor mitigation.
static int64_t applyArmor(Actor* user, Actor* target, EventOptions& eventOptions, int64_t damage, bool isSpell) {
	int64_t result = damage;
	int armor = 0;
	int armorPen = 0;
	int armorMitigation = 0;
	int attackerLevel = user->GetLevel();

	if (isSpell) {
		armor = target->GetMagicArmor(eventOptions, true);
		armorPen = user->GetMagicArmorPen(eventOptions, true);
	}
	else {
		armor = target->GetArmor(true);
		armorPen = user->GetArmorPen(eventOptions, true);
	}

	armor = armor * (1000 - armorPen) / 1000;
	armorMitigation = (armor * 1000) / (armor + 45 + (attackerLevel * 5) + (static_cast<int>(pow(attackerLevel, 2)) / 10));
	result = result * (1000 - armorMitigation) / 1000;
	return result;
}

// Resistance mitigation.
static int64_t applyResistance(Actor* user, Actor* target, EventOptions& eventOptions, int64_t damage) {
	int64_t result = damage;
	int resistance = target->GetResistance(eventOptions, true);
	int resistancePen = std::min(1000, user->GetResistancePen(eventOptions, true) + eventOptions.BonusResistancePen + eventOptions.SnapshotResistancePen);
	if (resistance > 0) { // stops resistance pen from applying to negative resistance values
		resistance = resistance * (1000 - resistancePen) / 1000;
	}
	result = result * (1000 - resistance) / 1000;
	return result;
}

// Applies damage variance and reduces damage value to actual number.
static int applyVariance(int64_t damage, bool randomVariance = false) {
	int64_t result = damage;
	// +/- 1 damage based on how close the damage is to the next whole number
	int roundUpChance = damage % 1000;
	if (Random::RandomInt(1, 1000) <= roundUpChance) {
		result = result / 1000 + 1;
	}
	else {
		result = result / 1000;
	}

	if (randomVariance) {
		result = result * Random::RandomInt(850, 1150) / 1000;
	}

	return static_cast<int>(result);
}

// Applies leech effects.
static void applyLeech(Actor* user, EventOptions& eventOptions, int damage) {
	// HP Leech
	int hpLeech = user->GetHPLeech(eventOptions, true) + eventOptions.BonusHPLeech;
	int hpAmount = damage * hpLeech / 1000;
	if (hpAmount > 0) {
		user->Heal(hpAmount, false, AttributeType::HP);
	}

	// MP Leech
	int mpLeech = user->GetMPLeech(eventOptions, true) + eventOptions.BonusMPLeech;
	int mpAmount = damage * mpLeech / 1000;
	if (mpAmount > 0) {
		user->Heal(mpAmount, false, AttributeType::MP);
	}

	// SP Leech
	int spLeech = user->GetSPLeech(eventOptions, true) + eventOptions.BonusSPLeech;
	int spAmount = damage * spLeech / 1000;
	if (spAmount > 0) {
		user->Heal(spAmount, false, AttributeType::SP);
	}
}

// Outputs damage to the message log.
static void outputDamage(Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult) {
	std::stringstream s;
	if (user->IsPlayer()) {
		s << "#player ";
	}
	else {
		s << "#monster ";
	}

	s << user->GetName() << "'s #default " << eventOptions.EventName << " dealt #damage ";
	if (eventResult.DidCrit) {
		s << "\\*" << eventResult.TotalDamage << "\\*";
	}
	else {
		s << eventResult.TotalDamage;
	}
	s << " #default " << DataString::ElementString(eventOptions.Elements, false);
	s << " damage to ";
	if (target->IsPlayer()) {
		s << "#player ";
	}
	else {
		s << "#monster ";
	}
	s << target->GetName() << "#default .";
	messageLog.AddMessage(s.str());
}

// Outputs healing to the message log.
static void outputHealing(Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, AttributeType healingType) {
	std::stringstream s;
	if (user->IsPlayer()) {
		s << "#player ";
	}
	else {
		s << "#monster ";
	}

	s << user->GetName() << "'s #default " << eventOptions.EventName << " healed ";
	if (target->IsPlayer()) {
		s << "#player ";
	}
	else {
		s << "#monster ";
	}

	s << target->GetName() << " #default for #heal ";

	if (eventResult.DidCrit) {
		s << "\\*" << eventResult.TotalHealing << "\\*";
	}
	else {
		s << eventResult.TotalHealing;
	}
	
	switch (healingType) {
		case AttributeType::HP:
			s << " HP";
			break;
		case AttributeType::MP:
			s << " MP";
			break;
		case AttributeType::SP:
			s << " SP";
			break;
		default:
			s << " HP";
			break;
	}

	s << "#default .";
	messageLog.AddMessage(s.str());
}

void outputMiss(Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult) {
	std::stringstream s;
	if (user->IsPlayer()) {
		s << "#player ";
	}
	else {
		s << "#monster ";
	}
	s << user->GetName() << "'s #default " << eventOptions.EventName << " missed ";
	if (target->IsPlayer()) {
		s << "#player ";
	}
	else {
		s << "#monster ";
	}
	s << target->GetName() << "#default .";
	messageLog.AddMessage(s.str());

	target->AddMissFCT();
}

EventResult Combat::AttackDamage(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient) {
	EventResult result;
	int64_t damage = 0;
	int damageResult = 0;

	damage = user->GetAttackPower(eventOptions, true) * coefficient; // intentionally not dividing by 1000 for better precision

	user->OnEvent(EventType::PreCalcDamage, target, eventOptions, result, damage);

	// Hit check.
	if (eventOptions.CanDodge) {
		result.DidHit = hitRoll(user, target, eventOptions);
	}
	else {
		result.DidHit = true;
	}

	if (result.DidHit) {
		// Block check.
		if (eventOptions.CanBlock) {
			result.DidBlock = blockRoll(user, target, eventOptions);
			if (result.DidBlock) {
				damage = applyBlock(user, target, eventOptions, damage);
			}
		}

		// Crit check.
		if (eventOptions.CanCrit) {
			result.DidCrit = critRoll(user, target, eventOptions);
			if (result.DidCrit) {
				damage = applyCrit(user, target, eventOptions, damage);
			}
		}

		// On hit damage.
		damage = applyOnHitDamage(user, target, eventOptions, damage, true);

		// User damage multiplier.
		damage = applyDamageDealt(user, eventOptions, damage, true);

		// Target damage multiplier.
		damage = applyDamageTaken(user, target, eventOptions, damage);

		// Armor mitigation.
		damage = applyArmor(user, target, eventOptions, damage, false);

		// Resistance mitigation.
		damage = applyResistance(user, target, eventOptions, damage);

		user->OnEvent(EventType::PostCalcDamage, target, eventOptions, result, damage);

		// Damage variance.
		damageResult = applyVariance(damage, true);

		// Inflict damage.
		result.TotalDamage = target->TakeDamage(damageResult, result.DidCrit, eventOptions.Elements);
		result.DidKill = !target->IsAlive() && result.TotalDamage > 0;

		// Apply leech.
		applyLeech(user, eventOptions, result.TotalDamage);

		// Output.
		outputDamage(user, target, eventOptions, result);

		user->OnEvent(EventType::Damage, target, eventOptions, result, damage);
		target->OnEvent(EventType::Damaged, user, eventOptions, result, damage);

		if (result.DidKill) {
			Combat::AwardPrizes(user, target, eventOptions);
		}

	}
	else {
		// Miss message.
		outputMiss(user, target, eventOptions, result);
	}

	return result;
}

EventResult Combat::SkillDamage(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient) {
	EventResult result;
	int64_t damage = 0;
	int damageResult = 0;

	// Use weapon element if skill doesn't have an element.
	if (eventOptions.Elements.empty()) {
		eventOptions.Elements = { user->GetAttackElement() };
	}

	damage = user->GetAttackPower(eventOptions, true) * coefficient; // intentionally not dividing by 1000 for better precision
	damage = damage * user->GetWeaponDamageMultiplier() / 1000;

	user->OnEvent(EventType::PreCalcDamage, target, eventOptions, result, damage);

	// Hit check.
	if (eventOptions.CanDodge) {
		result.DidHit = hitRoll(user, target, eventOptions);
	}
	else {
		result.DidHit = true;
	}

	if (result.DidHit) {
		// Block check.
		if (eventOptions.CanBlock) {
			result.DidBlock = blockRoll(user, target, eventOptions);
			if (result.DidBlock) {
				damage = applyBlock(user, target, eventOptions, damage);
			}
		}
		
		// Crit check.
		if (eventOptions.CanCrit) {
			result.DidCrit = critRoll(user, target, eventOptions);
			if (result.DidCrit) {
				damage = applyCrit(user, target, eventOptions, damage);
			}
		}

		// On hit damage.
		damage = applyOnHitDamage(user, target, eventOptions, damage, true);

		// User damage multiplier.
		damage = applyDamageDealt(user, eventOptions, damage, true);

		// Target damage multiplier.
		damage = applyDamageTaken(user, target, eventOptions, damage);

		// Armor mitigation.
		damage = applyArmor(user, target, eventOptions, damage, false);

		// Resistance mitigation.
		damage = applyResistance(user, target, eventOptions, damage);

		user->OnEvent(EventType::PostCalcDamage, target, eventOptions, result, damage);

		// Damage variance.
		damageResult = applyVariance(damage, true);

		// Inflict damage.
		result.TotalDamage = target->TakeDamage(damageResult, result.DidCrit, eventOptions.Elements);
		result.DidKill = !target->IsAlive() && result.TotalDamage > 0;

		// Apply leech.
		applyLeech(user, eventOptions, result.TotalDamage);

		// Output.
		outputDamage(user, target, eventOptions, result);

		user->OnEvent(EventType::Damage, target, eventOptions, result, damage);
		target->OnEvent(EventType::Damaged, target, eventOptions, result, damage);

		if (result.DidKill) {
			Combat::AwardPrizes(user, target, eventOptions);
		}

	}
	else {
		// Miss message.
		outputMiss(user, target, eventOptions, result);
	}

	return result;
}

EventResult Combat::SpellDamage(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient) {
	EventResult result;

	int64_t damage = 0;
	int damageResult = 0;

	damage = user->GetSpellPower(eventOptions, true) * coefficient; // intentionally not dividing by 1000 for better precision

	user->OnEvent(EventType::PreCalcDamage, target, eventOptions, result, damage);

	// Hit check.
	if (eventOptions.CanDodge) {
		result.DidHit = hitRoll(user, target, eventOptions);
	}
	else {
		result.DidHit = true;
	}

	if (result.DidHit) {
		// Block check.
		if (eventOptions.CanBlock) {
			result.DidBlock = blockRoll(user, target, eventOptions);
			if (result.DidBlock) {
				damage = applyBlock(user, target, eventOptions, damage);
			}
		}

		// Crit check.
		if (eventOptions.CanCrit) {
			result.DidCrit = critRoll(user, target, eventOptions);
			if (result.DidCrit) {
				damage = applyCrit(user, target, eventOptions, damage);
			}
		}

		// On hit damage.
		damage = applyOnHitDamage(user, target, eventOptions, damage, true);

		// User damage multiplier.
		damage = applyDamageDealt(user, eventOptions, damage, true);

		// Target damage multiplier.
		damage = applyDamageTaken(user, target, eventOptions, damage);

		// Armor mitigation.
		damage = applyArmor(user, target, eventOptions, damage, false);

		// Resistance mitigation.
		damage = applyResistance(user, target, eventOptions, damage);

		user->OnEvent(EventType::PostCalcDamage, target, eventOptions, result, damage);

		// Damage variance.
		damageResult = applyVariance(damage, true);

		// Inflict damage.
		result.TotalDamage = target->TakeDamage(damageResult, result.DidCrit, eventOptions.Elements);
		result.DidKill = !target->IsAlive() && result.TotalDamage > 0;

		user->OnEvent(EventType::Damage, target, eventOptions, result, damage);
		target->OnEvent(EventType::Damaged, user, eventOptions, result, damage);

		// Apply leech.
		applyLeech(user, eventOptions, result.TotalDamage);

		// Output.
		outputDamage(user, target, eventOptions, result);

		if (result.DidKill) {
			Combat::AwardPrizes(user, target, eventOptions);
		}

	}
	else {
		// Miss message.
		outputMiss(user, target, eventOptions, result);
	}

	return result;
}

EventResult Combat::SpellHeal(Actor* user, Actor* target, EventOptions& eventOptions, int coefficient, AttributeType healingType) {
	EventResult result;
	int64_t heal = 0;
	int healResult = 0;

	heal = user->GetSpellPower(eventOptions, true) * coefficient; // intentionally not dividing here for more precision

	user->OnEvent(EventType::PreCalcHeal, target, eventOptions, result, heal);

	result.DidHit = true; // heals cannot be evaded

	// Crit check.
	if (eventOptions.CanCrit) {
		result.DidCrit = critRoll(user, target, eventOptions);
		if (result.DidCrit) {
			heal = applyCrit(user, target, eventOptions, heal);
		}
	}

	// Apply healing dealt.
	heal = applyHealingDealt(user, eventOptions, heal, true);

	// Apply healing taken.
	heal = applyHealingTaken(user, target, eventOptions, heal);

	user->OnEvent(EventType::PostCalcHeal, target, eventOptions, result, heal);

	// Apply variance.
	healResult = applyVariance(heal, true);
	result.TotalHealing = target->Heal(healResult, result.DidCrit, healingType);

	// Output.
	outputHealing(user, target, eventOptions, result, healingType);

	user->OnEvent(EventType::Heal, target, eventOptions, result, heal);
	target->OnEvent(EventType::Healed, user, eventOptions, result, heal);

	return result;
}

EventResult Combat::FixedDamage(Actor* user, Actor* target, EventOptions& eventOptions, int amount) {
	EventResult result;

	int64_t damage = amount * 1000;
	int damageResult = 0;

	user->OnEvent(EventType::PreCalcDamage, target, eventOptions, result, damage);

	// Hit check.
	if (eventOptions.CanDodge) {
		result.DidHit = hitRoll(user, target, eventOptions);
	}
	else {
		result.DidHit = true;
	}

	if (result.DidHit) {
		// Block check.
		if (eventOptions.CanBlock) {
			result.DidBlock = blockRoll(user, target, eventOptions);
			if (result.DidBlock) {
				damage = applyBlock(user, target, eventOptions, damage);
			}
		}

		// Crit check.
		if (eventOptions.CanCrit) {
			result.DidCrit = critRoll(user, target, eventOptions);
			if (result.DidCrit) {
				damage = applyCrit(user, target, eventOptions, damage);
			}
		}

		// On hit damage.
		damage = applyOnHitDamage(user, target, eventOptions, damage, true);

		// User damage multiplier.
		damage = applyDamageDealt(user, eventOptions, damage, true);

		// Target damage multiplier.
		damage = applyDamageTaken(user, target, eventOptions, damage);

		// Resistance mitigation.
		damage = applyResistance(user, target, eventOptions, damage);

		user->OnEvent(EventType::PostCalcDamage, target, eventOptions, result, damage);

		// Damage variance.
		damageResult = applyVariance(damage);

		// Inflict damage.
		result.TotalDamage = target->TakeDamage(damageResult, result.DidCrit, eventOptions.Elements);
		result.DidKill = !target->IsAlive() && result.TotalDamage > 0;

		user->OnEvent(EventType::Damage, target, eventOptions, result, damage);
		target->OnEvent(EventType::Damaged, user, eventOptions, result, damage);

		// Apply leech.
		applyLeech(user, eventOptions, result.TotalDamage);

		// Output.
		outputDamage(user, target, eventOptions, result);

		if (result.DidKill) {
			Combat::AwardPrizes(user, target, eventOptions);
		}

	}
	else {
		// Miss message.
		outputMiss(user, target, eventOptions, result);
	}



	return result;
}

EventResult Combat::FixedHeal(Actor* user, Actor* target, EventOptions& eventOptions, int amount, AttributeType healingType) {
	EventResult result;

	int64_t healAmount = 0;
	int healResult = 0;

	healAmount = amount * 1000; // multiply by 1000 for more precision

	user->OnEvent(EventType::PreCalcHeal, target, eventOptions, result, healAmount);

	result.DidHit = true; // heals cannot be evaded

	// Crit check.
	if (eventOptions.CanCrit) {
		result.DidCrit = critRoll(user, target, eventOptions);
		if (result.DidCrit) {
			healAmount = applyCrit(user, target, eventOptions, healAmount);
		}
	}

	// Apply healing dealt.
	healAmount = applyHealingDealt(user, eventOptions, healAmount, true);

	// Apply healing taken.
	healAmount = applyHealingTaken(user, target, eventOptions, healAmount);

	user->OnEvent(EventType::PostCalcHeal, target, eventOptions, result, healAmount);

	// Variance.
	healResult = applyVariance(healAmount);
	result.TotalHealing = target->Heal(healResult, result.DidCrit, healingType);

	// Output.
	outputHealing(user, target, eventOptions, result, healingType);

	user->OnEvent(EventType::Heal, target, eventOptions, result, healAmount);
	target->OnEvent(EventType::Healed, user, eventOptions, result, healAmount);

	return result;
}

void Combat::AddAuraStack(Actor* user, Actor* target, EventOptions& eventOptions, AuraID id, int rank) {
	target->AddAura(id, rank, user->GetSnapshotDamage(eventOptions, true), user->GetSnapshotCritChance(eventOptions, true), user->GetSnapshotResistancePen(eventOptions, true), user);
}

void Combat::RemoveAuraStack(Actor* target, AuraID id) {
	target->RemoveAuraStack(id);
}

int Combat::AttackDamageEstimate(Actor* user, EventOptions& eventOptions, int coefficient) {
	int64_t damage = 0;

	damage = user->GetAttackPower(eventOptions, false) * coefficient;
	damage = applyOnHitDamage(user, nullptr, eventOptions, damage, false);
	damage = applyDamageDealt(user, eventOptions, damage, false);
	return static_cast<int>(damage / 1000);
}

int Combat::SkillDamageEstimate(Actor* user, EventOptions& eventOptions, int coefficient) {
	int64_t damage = 0;

	if (eventOptions.Elements.empty()) {
		eventOptions.Elements = { user->GetAttackElement() };
	}

	damage = user->GetAttackPower(eventOptions, false) * coefficient;
	damage = damage * user->GetWeaponDamageMultiplier() / 1000;
	damage = applyOnHitDamage(user, nullptr, eventOptions, damage, false);
	damage = applyDamageDealt(user, eventOptions, damage, false);
	return static_cast<int>(damage / 1000);
}

int Combat::SpellDamageEstimate(Actor* user, EventOptions& eventOptions, int coefficient) {
	int64_t damage = 0;

	damage = user->GetSpellPower(eventOptions, false) * coefficient;
	damage = applyOnHitDamage(user, nullptr, eventOptions, damage, false);
	damage = applyDamageDealt(user, eventOptions, damage, false);
	return static_cast<int>(damage / 1000);
}

int Combat::SpellHealEstimate(Actor* user, EventOptions& eventOptions, int coefficient) {
	int64_t heal = 0;

	heal = user->GetSpellPower(eventOptions, false) * coefficient;
	heal = applyHealingDealt(user, eventOptions, heal, false);
	return static_cast<int>(heal / 1000);
}

void Combat::AwardPrizes(Actor* user, Actor* target, EventOptions& eventOptions) {
	if (!target->IsAlive()) {
		// Only non-players can drop items and award EXP.
		if (!target->IsPlayer()) {
			Monster* monster = static_cast<Monster*>(target);
				
			// Drops
			int dropCount = 0;
			int goldDropped = 0;
			std::vector<Item> items;
			int itemLevel = (user->GetDungeonScene()->GetCurrentFloor() + monster->GetLevel()) / 2;

			int gold = monster->GetGoldDrop();
			int lootPoints = monster->GetLootPoints();
			int randomLootPoints = Random::RandomInt(0, lootPoints / 2) + Random::RandomInt(0, lootPoints / 2);

			// Uniques always drop at least one item.
			if (monster->IsUnique()) {
				randomLootPoints = std::max(1000, randomLootPoints);
			}

			dropCount = randomLootPoints / 1000;
			if (Random::RandomInt(1, 1000) <= randomLootPoints % 1000) {
				dropCount++;
			}
				
			bool monsterDroppedGold = false;
			for (int i = 0; i < dropCount; i++) {
				if (!monsterDroppedGold && gold > 0) {
					// 50% Chance to Drop Gold for Every Item Generation
					// Unique Monsters Always Drop Gold
					if (Random::RandomInt(1, 1000) <= 500 || monster->IsUnique()) {
						goldDropped = gold * Random::RandomInt(900, 1100) / 1000;
						monsterDroppedGold = true;
						continue;
					}
				}
				Item item;
				item.InitRandomItem(itemLevel);
				items.push_back(item);

			}

			user->GetDungeonScene()->DropLoot(target->GetLocation(), goldDropped, items);

			// EXP
			// Only players can earn EXP.
			if (user->IsPlayer()) {
				Player* player = static_cast<Player*>(user);
				messageLog.AddMessage("#player " + player->GetName() + " #default earned #randart " + std::to_string(monster->GetEXPReward() * player->GetEXPBoost() / 1000) + " EXP #default from defeating #monster " + target->GetName() + "#default .");
				player->AwardEXP(monster->GetEXPReward());
					
				// Record the kill.
				records.MarkKilled(monster->GetMonsterID());
			}
		}

		// Trigger death events, including healing from kills.
		if (user != target) {
			int64_t value = 0;
			EventResult result;
			user->HealOnKill(eventOptions);

			target->OnEvent(EventType::Death, user, eventOptions, result, value);
		}
	}
}