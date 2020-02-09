// ================================================================
//
// actor.cpp
//
// ================================================================

#include "actor.hpp"

#include <algorithm>
#include "../scene/dungeonScene.hpp"

void Actor::UpdateHUD(float secondsPerUpdate) {
	actorHUD.Update(*this, secondsPerUpdate);
}

void Actor::DrawHUD(sf::RenderTarget& window, float timeRatio) {
	if (IsOnScreen(window)) {
		actorHUD.Draw(window, timeRatio);
	}
}

void Actor::SetDungeonScene(DungeonScene* ds) {
	dungeonScene = ds;
}

DungeonScene* Actor::GetDungeonScene() {
	return dungeonScene;
}

size_t Actor::GetIndex() {
	return index;
}

std::string Actor::GetName() {
	return name;
}

sf::Vector2i Actor::GetLocation() {
	return location;
}

int Actor::GetLevel() {
	return level;
}

int Actor::GetExhaustion() {
	return exhaustion;
}

void Actor::DecrementExhaustion() {
	for (auto& au : auras) {
		au.Tick(this);
	}
	for (auto& ab : abilities) {
		ab.DecrementCooldown(this);
	}
	
	// HP Regen
	hpRegenOverflow += static_cast<double>(GetHPRegen()) / 1000.0;
	if (hpRegenOverflow >= 1.0) {
		int regen = static_cast<int>(std::floor(hpRegenOverflow));
		currentHP = std::min(currentHP + regen, GetMaxHP());
		hpRegenOverflow -= static_cast<double>(regen);
	}

	// MP Regen
	mpRegenOverflow += static_cast<double>(GetMPRegen()) / 1000.0;
	if (mpRegenOverflow >= 1.0) {
		int regen = static_cast<int>(std::floor(mpRegenOverflow));
		currentMP = std::min(currentMP + regen, GetMaxMP());
		mpRegenOverflow -= static_cast<double>(regen);
	}

	// SP Regen
	spRegenOverflow += static_cast<double>(GetSPRegen()) / 1000.0;
	if (spRegenOverflow >= 1.0) {
		int regen = static_cast<int>(std::floor(spRegenOverflow));
		currentSP = std::min(currentSP + regen, GetMaxSP());
		spRegenOverflow -= static_cast<double>(regen);
	}

	if (IsStunned() == false && exhaustion > 0) {
		exhaustion--;
	}

	//if (exhaustion > 0) {
	//	exhaustion--;
	//	for (auto& ab : abilities) {
	//		ab.DecrementCooldown();
	//	}
	//	for (auto& au : auras) {
	//		au.Tick(this);
	//	}
	//}

	RemoveExpiredAuras();
	actorHUD.UpdateElements(*this);
}

bool Actor::IsReadyToAct() {
	if (IsResting()) {
		return false;
	}

	if (IsStunned()) {
		return false;
	}
	
	return exhaustion == 0;
}

void Actor::Walk(sf::Vector2i destination, int moveMod) {
	int cost = getBaseStat(StatModType::MovementSpeed) * 1000 / GetMovementSpeed();
	cost = cost * moveMod / 1000;
	// diagonal
	if (location.x != destination.x && location.y != destination.y) {
		cost = cost * 1414 / 1000;
	}
	//messageLog.AddMessage("MS: " + std::to_string(GetMovementSpeed()) + ", Move Cost: " + std::to_string(cost));
	// actual movement and exhaustion
	exhaustion += cost;
	location = destination;
	MoveToTile(destination, 0.f);
	actorHUD.UpdateElements(*this);
}

void Actor::Warp(sf::Vector2i destination) {
	location = destination;
	MoveToTile(destination, 0.f);
}

void Actor::Wait(int timeToWait) {
	exhaustion += timeToWait;
}

void Actor::UseAbility(DungeonScene* dungeonScene, AbilityID id, sf::Vector2i cursor) {
	// Find the index of the ability.
	auto it = std::find_if(abilities.begin(), abilities.end(), [&](Ability& a) { return a.GetAbilityID() == id; });
	if (it != abilities.end()) {
		size_t index = std::distance(abilities.begin(), it);

		// Get area.
		std::vector<sf::Vector2i> area = abilities[index].GetTargetArea(cursor, this, dungeonScene);

		// Get actors in range.
		std::vector<Actor*> targets = dungeonScene->GetActorsInArea(area);

		// Execute ability.
		abilities[index].Execute(this, targets, cursor, area);
	}
	actorHUD.UpdateElements(*this);
}

int Actor::TakeDamage(int damage) {
	int result = damage;

	if (result > currentHP) {
		result = currentHP;
	}

	currentHP -= result;
	actorHUD.UpdateElements(*this);
	return result;
}

int Actor::Heal(int amount, AttributeType attribute) {
	int result = amount;

	switch (attribute) {
		case AttributeType::HP:
			if (result + currentHP > GetMaxHP()) {
				result = GetMaxHP() - currentHP;
			}
			currentHP += result;
			break;
		case AttributeType::MP:
			if (result + currentMP > GetMaxMP()) {
				result = GetMaxMP() - currentMP;
			}
			currentMP += result;
			break;
		case AttributeType::SP:
			if (result + currentSP > GetMaxSP()) {
				result = GetMaxSP() - currentSP;
			}
			currentSP += result;
			break;
		default:
			// default to HP if undefined, this should never trigger
			if (result + currentHP > GetMaxHP()) {
				result = GetMaxHP() - currentHP;
			}
			currentHP += result;
			break;
	}

	actorHUD.UpdateElements(*this);
	return result;
}

void Actor::SpendResource(int amount, EventOptions& eventOptions, AttributeType attribute) {
	switch (attribute) {
		case AttributeType::HP:
			amount = amount * (1000 - GetHPCostReduction(eventOptions, true)) / 1000;
			currentHP = std::max(currentHP - amount, 0);
			break;
		case AttributeType::MP:
			amount = amount * (1000 - GetMPCostReduction(eventOptions, true)) / 1000;
			currentMP = std::max(currentMP - amount, 0);
			break;
		case AttributeType::SP:
			amount = amount * (1000 - GetSPCostReduction(eventOptions, true)) / 1000;
			currentSP = std::max(currentSP - amount, 0);
			break;
		default:
			break;
	}
}

void Actor::HealOnKill(EventOptions& eventOptions) {
	int hpOnKill = GetHPOnKill(eventOptions, true);
	currentHP = std::min(currentHP + hpOnKill, GetMaxHP());

	int mpOnKill = GetMPOnKill(eventOptions, true);
	currentMP = std::min(currentMP + mpOnKill, GetMaxMP());

	int spOnKill = GetSPOnKill(eventOptions, true);
	currentSP = std::min(currentSP + spOnKill, GetMaxSP());

	actorHUD.UpdateElements(*this);
}

std::vector<Aura>& Actor::GetAuras() {
	return auras;
}

bool Actor::HasAura(AuraID id) {
	for (auto& au : auras) {
		if (au.GetAuraID() == id) {
			return true;
		}
	}

	return false;
}

void Actor::AddAura(AuraID auraID, int rank, Actor* source) {
	size_t sourceIndex = source->GetIndex();
	for (size_t i = 0; i < auras.size(); i++) {
		if (auras[i].GetAuraID() == auraID) {
			// Unique Aura: Refresh duration and change ownership.
			if (auras[i].IsUnique()) {
				auras[i].Refresh(source, sourceIndex, rank);
				return;
			}
			// Unique By Actor Aura: Refresh duration if source actors match.
			else if (auras[i].IsUniqueByActor() && auras[i].GetSourceIndex() == sourceIndex) {
				auras[i].Refresh(source, sourceIndex, rank);
				return;
			}
		}
	}

	// Did not match existing auras, safe to add.
	Aura aura(auraID, rank, source, sourceIndex);
	auras.push_back(aura);

	actorHUD.UpdateElements(*this);
}

void Actor::SetAuraOwnerPointer() {
	if (dungeonScene != nullptr) {
		for (auto& au : auras) {
			au.SetOwnerPointer(dungeonScene);
		}
	}
}

void Actor::RemoveAuraStack(AuraID id) {
	for (auto& a : auras) {
		if (a.GetAuraID() == id) {
			a.RemoveStack();
		}
	}

	RemoveExpiredAuras();
	actorHUD.UpdateElements(*this);
}

void Actor::RemoveExpiredAuras() {
	if (!auras.empty()) {
		auto removed = std::remove_if(auras.begin(), auras.end(), [&](Aura& au){ return au.IsExpired(this); });
		auras.erase(removed, auras.end());
	}
}

void Actor::ClearAuras() {
	auras.clear();
}

void Actor::OnEvent(EventType eventType, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
	for (auto& ab : abilities) {
		ab.OnEvent(eventType, this, target, eventOptions, eventResult, amount);
	}

	for (auto& au : auras) {
		au.OnEvent(eventType, this, target, eventOptions, eventResult, amount);
	}
}

void Actor::SetFlag(size_t index, int value) {
	flags[index] = value;
}

int Actor::GetFlag(size_t index) {
	return flags[index];
}

bool Actor::IsAlive() {
	return currentHP > 0;
}

bool Actor::IsResting() {
	for (auto& a : auras) {
		if (a.IsRest()) {
			return true;
		}
	}
	return false;
}

bool Actor::IsStunned() {
	for (auto& a : auras) {
		if (a.IsStun()) {
			return true;
		}
	}
	return false;
}

bool Actor::IsDisarmed() {
	for (auto& aura : auras) {
		if (aura.IsDisarm()) {
			return true;
		}
	}
	return false;
}

int Actor::GetCurrentHP() {
	return currentHP;
}

int Actor::GetCurrentMP() {
	return currentMP;
}

int Actor::GetCurrentSP() {
	return currentSP;
}

int Actor::GetMaxHP() {
	int result = 0;
	int hpPerLevel = getStat(0, StatModType::HPPerLevel, false, false);
	int base = getBaseStat(StatModType::HP) + (level * hpPerLevel) + (GetVIT() * 5);
	int multi = 1000;

	base = getStat(base, StatModType::HP, false, false);
	multi = getStat(multi, StatModType::HPMulti, true, false);

	result = base * multi / 1000;
	result = std::max(0, result); // never less than 0
	return result;
}

int Actor::GetHPRegen() {
	int result = 0;
	int base = getStat(0, StatModType::HPRegen, false, false);

	result = base;
	return result;
}

int Actor::GetHPLeech(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::HPLeech, eventOptions, false, consumeBuffs);

	result = std::max(0, base);
	return result;
}

int Actor::GetHPOnHit(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::HPOnHit, eventOptions, false, consumeBuffs);

	result = std::max(0, base);
	return result;
}

int Actor::GetHPOnKill(EventOptions& eventOptions, bool consumeBuffs) {
	int base = GetVIT(); // 1 VIT = 1 HP On Kill
	int result = getStat(base, StatModType::HPOnKill, eventOptions, false, consumeBuffs);

	result = std::max(0, result);
	return result;
}

int Actor::GetMaxMP() {
	int result = 0;
	int mpPerLevel =getStat(0, StatModType::MPPerLevel, false, false);
	int base = getBaseStat(StatModType::MP) + (level * mpPerLevel) + (GetSPI() * 2);
	int multi = 1000;

	base = getStat(base, StatModType::MP, false, false);
	multi = getStat(multi, StatModType::MPMulti, true, false);

	result = base * multi / 1000;
	result = std::max(0, result); // never less than 0
	return result;
}

int Actor::GetMPRegen() {
	int result = 0;
	int base = getStat(0, StatModType::MPRegen, false, false);

	result = base;
	return result;
}

int Actor::GetMPLeech(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::MPLeech, eventOptions, false, consumeBuffs);

	result = std::max(0, base);
	return result;
}

int Actor::GetMPOnHit(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::MPOnHit, eventOptions, false, consumeBuffs);

	result = std::max(0, base);
	return result;
}

int Actor::GetMPOnKill(EventOptions& eventOptions, bool consumeBuffs) {
	int base = GetSPI() / 2; // 2 SPI = 1 MP On Kill
	int result = getStat(base, StatModType::MPOnKill, eventOptions, false, consumeBuffs);

	result = std::max(0, result);
	return result;
}

int Actor::GetMaxSP() {
	int result = 0;
	int spPerLevel = getStat(0, StatModType::SPPerLevel, false, false);
	int base = getBaseStat(StatModType::SP) + (level * spPerLevel);
	int multi = 1000;

	base = getStat(base, StatModType::SP, false, false);
	multi = getStat(multi, StatModType::SPMulti, true, false);

	result = base * multi / 1000;
	result = std::max(0, result);
	return result;
}

int Actor::GetSPRegen() {
	int base = 50; // base 5 sp per sec
	int result = getStat(base, StatModType::SPRegen, false, false);

	return result;
}

int Actor::GetSPLeech(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::SPLeech, eventOptions, false, consumeBuffs);

	result = std::max(0, base);
	return result;
}

int Actor::GetSPOnHit(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::SPOnHit, eventOptions, false, consumeBuffs);

	result = std::max(0, base);
	return result;
}

int Actor::GetSPOnKill(EventOptions& eventOptions, bool consumeBuffs) {
	int base = 0;
	int result = getStat(base, StatModType::SPOnKill, eventOptions, false, consumeBuffs);

	result = std::max(0, result);
	return result;
}

int Actor::GetSTR() {
	int result = 0;
	int base = getBaseStat(StatModType::STR);
	int multi = 1000;
	int aaMulti = 1000;

	base = getStat(base, StatModType::STR, false, false);
	base = getStat(base, StatModType::AllAttributes, false, false);

	multi = getStat(multi, StatModType::STRMulti, true, false);
	aaMulti = getStat(aaMulti, StatModType::AllAttributeMulti, true, false);

	result = base * (multi + aaMulti - 1000) / 1000;
	return result;
}

int Actor::GetDEX() {
	int result = 0;
	int base = getBaseStat(StatModType::DEX);
	int multi = 1000;
	int aaMulti = 1000;

	base = getStat(base, StatModType::DEX, false, false);
	base = getStat(base, StatModType::AllAttributes, false, false);

	multi = getStat(multi, StatModType::DEXMulti, true, false);
	aaMulti = getStat(aaMulti, StatModType::AllAttributeMulti, true, false);

	result = base * (multi + aaMulti - 1000) / 1000;
	return result;
}

int Actor::GetMAG() {
	int result = 0;
	int base = getBaseStat(StatModType::MAG);
	int multi = 1000;
	int aaMulti = 1000;

	base = getStat(base, StatModType::MAG, false, false);
	base = getStat(base, StatModType::AllAttributes, false, false);

	multi = getStat(multi, StatModType::MAGMulti, true, false);
	aaMulti = getStat(aaMulti, StatModType::AllAttributeMulti, true, false);

	result = base * (multi + aaMulti - 1000) / 1000;
	return result;
}

int Actor::GetVIT() {
	int result = 0;
	int base = getBaseStat(StatModType::VIT);
	int multi = 1000;
	int aaMulti = 1000;

	base = getStat(base, StatModType::VIT, false, false);
	base = getStat(base, StatModType::AllAttributes, false, false);

	multi = getStat(multi, StatModType::VITMulti, true, false);
	aaMulti = getStat(aaMulti, StatModType::AllAttributeMulti, true, false);

	result = base * (multi + aaMulti - 1000) / 1000;
	return result;
}

int Actor::GetSPI() {
	int result = 0;
	int base = getBaseStat(StatModType::SPI);
	int multi = 1000;
	int aaMulti = 1000;

	base = getStat(base, StatModType::SPI, false, false);
	base = getStat(base, StatModType::AllAttributes, false, false);

	multi = getStat(multi, StatModType::SPIMulti, true, false);
	aaMulti = getStat(aaMulti, StatModType::AllAttributeMulti, true, false);

	result = base * (multi + aaMulti - 1000) / 1000;
	return result;
}

int Actor::GetArmor(bool consumeBuffs) {
	int result = 0;
	int base = getBaseStat(StatModType::Armor);
	int armorPerLevel = 0;
	int armorMulti = 1000;

	base = getStat(base, StatModType::Armor, false, consumeBuffs);
	armorPerLevel = getStat(armorPerLevel, StatModType::ArmorPerLevel, false, consumeBuffs);
	armorMulti = getStat(armorMulti, StatModType::ArmorMulti, true, consumeBuffs);

	result = (base + armorPerLevel * level) * armorMulti / 1000;
	result = std::max(0, result);
	return result;
}

int Actor::GetArmorPen(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::ArmorPen, eventOptions, false, consumeBuffs);

	result = std::clamp(result, 0, 1000);
	return result;
}

int Actor::GetMagicArmor(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = GetMAG() + getBaseStat(StatModType::MagicArmor); // 1 mag = 1 magic armor
	int armorPerLevel = 0;
	int armorMulti = 1000;

	base = getStat(base, StatModType::MagicArmor, false, consumeBuffs);
	armorPerLevel = getStat(armorPerLevel, StatModType::MagicArmorPerLevel, false, consumeBuffs);
	armorMulti = getStat(armorMulti, StatModType::MagicArmorMulti, true, consumeBuffs);

	result = (base + armorPerLevel * level) * armorMulti / 1000;
	result = std::max(0, result);
	return result;
}

int Actor::GetMagicArmorPen(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getStat(0, StatModType::MagicArmorPen, eventOptions, false, consumeBuffs);

	result = std::clamp(result, 0, 1000);
	return result;
}

int Actor::GetEvasion(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = getBaseStat(StatModType::Evasion);
	int evasionPerLevel = 0;
	int evasionMulti = 1000;

	base = getStat(base, StatModType::Evasion, eventOptions, false, consumeBuffs);
	evasionPerLevel = getStat(evasionPerLevel, StatModType::EvasionPerLevel, eventOptions, false, consumeBuffs);
	evasionMulti = getStat(evasionMulti, StatModType::EvasionMulti, eventOptions, true, consumeBuffs);

	result = (base + evasionPerLevel * level) * evasionMulti / 1000;
	result = std::max(0, result); // never less than 0
	return result;
}

int Actor::GetResistance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;

	int base = getStat(0, StatModType::Resistance, eventOptions, false, consumeBuffs);

	// Players are capped at 60% resistance, monsters at 100%.
	if (isPlayer) {
		result = std::min(600, base);
	}
	else {
		result = std::min(1000, base);
	}
	return result;
}

int Actor::GetResistancePen(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	double base = getStat(0, StatModType::ResistancePen, eventOptions, false, consumeBuffs);

	result = std::clamp(result, 0, 1000);
	return result;
}

int Actor::GetAttackPower(EventOptions& eventOptions, bool consumeBuffs) {
	int base = GetSTR() + getBaseStat(StatModType::AttackPower); // 1 str = 1 ap

	base = getStat(base, StatModType::AttackPower, eventOptions, false, consumeBuffs);

	return base;
}

int Actor::GetSpellPower(EventOptions& eventOptions, bool consumeBuffs) {
	int base = GetMAG() + getBaseStat(StatModType::SpellPower); // 1 mag = 1 sp

	base = getStat(base, StatModType::SpellPower, eventOptions, false, consumeBuffs);

	return base;
}

int Actor::GetAccuracy(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = GetDEX(); // 1 dex = 1 acc

	base = getStat(base, StatModType::Accuracy, eventOptions, false, consumeBuffs);

	result = std::max(0, base); // never less than 0
	return result;
}

int Actor::GetBlockChance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	
	int base = getStat(0, StatModType::BlockChance, eventOptions, false, consumeBuffs);

	result = std::max(0, base);
	return result;
}

int Actor::GetRange(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;

	int base = getStat(0, StatModType::Range, eventOptions, false, consumeBuffs);

	result = std::min(5000, base);
	return result;
}

int Actor::GetDamage(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(1000, StatModType::Damage, eventOptions, true, consumeBuffs);
	result = std::max(0, result);
	return result;
}

int Actor::GetDamageTaken(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(1000, StatModType::DamageTaken, eventOptions, true, consumeBuffs);
	result = std::max(0, result);
	return result;
}

int Actor::GetHealing(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(1000, StatModType::Healing, eventOptions, true, consumeBuffs);
	result = std::max(0, result);
	return result;
}

int Actor::GetHealingTaken(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(1000, StatModType::HealingTaken, eventOptions, true, consumeBuffs);
	result = std::max(0, result);
	return result;
}

int Actor::GetCritChance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = 30; // base 3% crit chance
	base += GetDEX() * 2; // 1 dex = 0.2% crit

	result = getStat(base, StatModType::CritChance, eventOptions, false, consumeBuffs);

	result = std::max(0, result);
	return result;
}

int Actor::GetCritPower(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = 1400;
	base += GetSTR() * 10; // 1 str = 1% crit power

	result = getStat(base, StatModType::CritPower, eventOptions, true, consumeBuffs);

	result = std::max(0, result);
	return result;
}

int Actor::GetCritProtection(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = 0;

	result = getStat(base, StatModType::CritProtection, eventOptions, false, consumeBuffs);

	return result;
}

int Actor::GetCritPowerProtection(EventOptions& eventOptions, bool consumeBuffs) {
	int result = 0;
	int base = 1000;

	result = getStat(base, StatModType::CritPowerProtection, eventOptions, true, consumeBuffs);

	result = std::max(0, result);
	return result;
}

int Actor::GetHaste(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(1000, StatModType::Haste, eventOptions, true, consumeBuffs);
	return result;
}

int Actor::GetDoubleStrikeChance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::DoubleStrikeChance, eventOptions, false, consumeBuffs);
	result = std::clamp(result, 0, 1000);
	return result;
}

int Actor::GetDoubleStrikeDamage(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(1000, StatModType::DoubleStrikeDamage, eventOptions, true, consumeBuffs);
	result = std::max(0, result);
	return result;
}

int Actor::GetCounterChance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::CounterChance, eventOptions, false, consumeBuffs);
	result = std::clamp(result, 0, 1000);
	return result;
}

int Actor::GetOnHitDamage(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::OnHitDamage, eventOptions, false, consumeBuffs);
	result = std::max(0, result);
	return result;
}

int Actor::GetCooldownReduction(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::CooldownReduction, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetHPCostReduction(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::HPCostReduction, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetMPCostReduction(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::MPCostReduction, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetSPCostReduction(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::SPCostReduction, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetDeathResistance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::DeathResistance, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetStunResistance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::StunResistance, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetSnareResistance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::SnareResistance, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetDisarmResistance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::DisarmResistance, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetSilenceResistance(EventOptions& eventOptions, bool consumeBuffs) {
	int result = getStat(0, StatModType::SilenceResistance, eventOptions, false, consumeBuffs);
	result = std::min(1000, result);
	return result;
}

int Actor::GetMovementSpeed() {
	int result = getStat(1000, StatModType::MovementSpeed, true, false);
	result = std::max(0, result);
	return result;
}

int Actor::GetSightRadius() {
	int result = 0;
	int base = getBaseStat(StatModType::SightRadius);

	base = getStat(base, StatModType::SightRadius, false, false);

	result = std::max(100, base);
	return result;
}

int Actor::GetGoldFind() {
	int result = getStat(1000, StatModType::GoldFind, true, false);
	result = std::max(0, result);
	return result;
}

int Actor::GetEXPBoost() {
	int result = getStat(1000, StatModType::EXPBoost, true, false);
	result = std::max(0, result);
	return result;
}

bool Actor::IsPlayer() {
	return isPlayer;
}

Ability* Actor::GetAbility(AbilityID id) {
	for (auto& ab : abilities) {
		if (ab.GetAbilityID() == id) {
			return &ab;
		}
	}
	return nullptr;
}

std::vector<Ability>* Actor::GetAbilities() {
	return &abilities;
}

bool Actor::IsAbilityProjectile(AbilityID id) {
	for (auto& ab : abilities) {
		if (ab.GetAbilityID() == id) {
			return ab.IsUsable(this);
		}
	}
	return false;
}

bool Actor::IsAbilityUsable(AbilityID id) {
	for (auto& ab : abilities) {
		if (ab.GetAbilityID() == id) {
			return ab.IsUsable(this);
		}
	}
	return false;
}

std::vector<sf::Vector2i> Actor::GetAbilityRange(AbilityID id) {
	std::vector<sf::Vector2i> result;

	for (auto& ab : abilities) {
		if (ab.GetAbilityID() == id) {
			result = ab.GetRange(this, dungeonScene);
			break;
		}
	}

	return result;
}

std::vector<sf::Vector2i> Actor::GetTargetArea(AbilityID id, sf::Vector2i cursor) {
	std::vector<sf::Vector2i> result;

	for (auto& ab : abilities) {
		if (ab.GetAbilityID() == id) {
			result = ab.GetTargetArea(cursor, this, dungeonScene);
			break;
		}
	}

	return result;
}

std::vector<int> Actor::GetAbilityCooldowns() {
	std::vector<int> result;
	result.reserve(abilities.size());

	for (auto& a : abilities) {
		result.push_back(a.GetCurrentCooldown());
	}

	return result;
}

std::vector<int> Actor::GetAbilityCharges() {
	std::vector<int> result;
	result.reserve(abilities.size());

	for (auto& a : abilities) {
		result.push_back(a.GetCurrentCharges());
	}

	return result;
}

std::vector<int> Actor::GetAuraIDs() {
	std::vector<int> result;
	result.reserve(auras.size());

	for (auto& a : auras) {
		result.push_back(static_cast<int>(a.GetAuraID()));
	}

	return result;
}

std::vector<int> Actor::GetAuraRanks() {
	std::vector<int> result;
	result.reserve(auras.size());

	for (auto& a : auras) {
		result.push_back(a.GetRank());
	}

	return result;
}

std::vector<int> Actor::GetAuraDurations() {
	std::vector<int> result;
	result.reserve(auras.size());

	for (auto& a : auras) {
		result.push_back(a.GetCurrentDuration());
	}

	return result;
}

std::vector<int> Actor::GetAuraNextTicks() {
	std::vector<int> result;
	result.reserve(auras.size());

	for (auto& a : auras) {
		result.push_back(a.GetNextTick());
	}

	return result;
}

std::vector<int> Actor::GetAuraStacks() {
	std::vector<int> result;
	result.reserve(auras.size());

	for (auto& a : auras) {
		result.push_back(a.GetCurrentStackSize());
	}

	return result;
}

std::vector<size_t> Actor::GetAuraSources() {
	std::vector<size_t> result;
	result.reserve(auras.size());

	for (auto& a : auras) {
		result.push_back(a.GetSourceIndex());
	}

	return result;
}

std::array<int, 16> Actor::GetFlags() {
	return flags;
}

int Actor::getStatFromEquipment(int base, StatModType statModType, EventOptions& eventOptions) {
	return base;
}

int Actor::getStat(int base, StatModType statModType, bool isMultiplicative, bool consumeBuffs) {
	EventOptions eo;
	return getStat(base, statModType, eo, isMultiplicative, consumeBuffs);
}

int Actor::getStat(int base, StatModType statModType, EventOptions& eventOptions, bool isMultiplicative, bool consumeBuffs) {
	int result = base;

	// categories must be sorted for std::includes to work
	std::sort(eventOptions.Categories.begin(), eventOptions.Categories.end());

	// element vector compaison lambda, just checking if there are any matches
	auto elementCheck = [](std::vector<Element>& v1, std::vector<Element>& v2) {
		for (auto e : v2) {
			if (std::find(v1.begin(), v1.end(), e) != v1.end()) {
				return true;
			}
		}
		return false;
	};

	// stat mod check lambda
	auto statModCheck = [&](StatMod& s) {
		if (s.statModType == statModType) {
			bool match = false;
			if (eventOptions.AbilityID != static_cast<AbilityID>(0) && eventOptions.AbilityID == s.abilityID) {
				match = true;
			}
			else if (eventOptions.AuraID != static_cast<AuraID>(0) && eventOptions.AuraID == s.auraID) {
				match = true;
			}
			else if (s.elements.empty() || elementCheck(eventOptions.Elements, s.elements)) {
				// must be sorted for std::includes to work	
				std::sort(s.categories.begin(), s.categories.end());
				std::sort(eventOptions.Categories.begin(), eventOptions.Categories.end());
				if (s.categories.empty() || std::includes(eventOptions.Categories.begin(), eventOptions.Categories.end(), s.categories.begin(), s.categories.end())) {
					match = true;
				}
			}
			if (match) {
				if (isMultiplicative) {
					result = result * (1000 + s.value);
					result = result / 1000;
				}
				else {
					// resistances only partially apply to multi-element attacks
					if (s.statModType == StatModType::Resistance) {
						result += s.value / static_cast<int>(eventOptions.Elements.size());
					}
					else {
						result += s.value;
					}
				}
			}
		}
	};

	result = getStatFromEquipment(base, statModType, eventOptions);

	// Base Stat Mods
	for (auto& s : getBaseStatMods()) {
		statModCheck(s);
		//if (s.statModType == statModType) {
		//	bool match = false;
		//	if (eventOptions.AbilityID != static_cast<AbilityID>(0) && eventOptions.AbilityID == s.abilityID) {
		//		match = true;
		//	}
		//	else if (eventOptions.AuraID != static_cast<AuraID>(0) && eventOptions.AuraID == s.auraID) {
		//		match = true;
		//	}
		//	else if (s.elements.empty() || elementCheck(eventOptions.Elements, s.elements)) {
		//		// must be sorted for std::includes to work	
		//		std::sort(s.categories.begin(), s.categories.end());
		//		if (s.categories.empty() || std::includes(s.categories.begin(), s.categories.end(), eventOptions.Categories.begin(), eventOptions.Categories.end())) {
		//			match = true;
		//		}
		//	}
		//	if (match) {
		//		if (isMultiplicative) {
		//			result = result * (1000 + s.value);
		//			result = result / 1000;
		//		}
		//		else {
		//			// resistances only partially apply to multi-element attacks
		//			if (s.statModType == StatModType::Resistance) {
		//				result += s.value / static_cast<int>(eventOptions.Elements.size());
		//			}
		//			else {
		//				result += s.value;
		//			}
		//		}
		//	}
		//}
	}

	// Passive Abilities
	for (auto& ability : abilities) {
		for (auto& sm : ability.GetStatMods()) {
			statModCheck(sm);
		}
	}


	// Auras
	for (auto& aura : auras) {
		int testValue = result;
		for (auto& sm : aura.GetStatMods()) {
			statModCheck(sm);
		}

		if (consumeBuffs && testValue != result) {
			aura.WasUsed(consumeBuffs);
		}
	}

	// Ground Effects

	return result;
}

DungeonScene* Actor::dungeonScene = nullptr;