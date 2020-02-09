// ================================================================
//
// ability.cpp
//
// ================================================================

#include "ability.hpp"

#include "id/abilityID.hpp"
#include "id/category.hpp"
#include "../core/combat.hpp"
#include "../core/random.hpp"
#include "../core/tileMath.hpp"
#include "../entity/actor.hpp"
#include "../entity/player.hpp"
#include "../scene/dungeonScene.hpp"

Ability::Ability() {
	abilityID = AbilityID::Undefined;
	currentRank = -1;
}

Ability::Ability(AbilityID id, int rank) {
	currentRank = rank;
	Initialize(id);
}

void Ability::Initialize(AbilityID id) {
	abilityID = id;
	abilityData = &abilityList[id];

	charges = abilityData->MaxCharges[currentRank];
}

bool Ability::IsNull() {
	return abilityData == nullptr;
}

void Ability::DecrementCooldown(Actor* user) {
	if (abilityData != nullptr && charges < abilityData->MaxCharges[currentRank]) {
		remainingCooldown--;
		if (remainingCooldown == 0) {
			charges++;
			if (charges < abilityData->MaxCharges[currentRank]) {
				EventOptions eo = getEventOptions();
				remainingCooldown = abilityData->Cooldown[currentRank] * (1000 - user->GetCooldownReduction(eo, true)) / 1000;
			}
		}
	}
}

void Ability::SetCooldownAndCharges(int cooldown, int charges) {
	this->remainingCooldown = cooldown;
	this->charges = charges;
}

int Ability::GetCurrentRank() {
	return currentRank;
}

int Ability::GetMaxRank() {
	return abilityData->MaxRank;
}

void Ability::IncreaseRank() {
	currentRank = std::min(currentRank + 1, abilityData->MaxRank);
}

bool Ability::IsUsable(Actor* user) {
	if (abilityData->IsPassive) {
		return false;
	}
	
	int checkRank = std::clamp(currentRank, 0, abilityData->MaxRank); // stop out of bounds error
	
	if (charges < 1) {
		return false;
	}

	EventOptions eo = getEventOptions();
	int hpCost = abilityData->HPCost[checkRank] * (1000 - user->GetHPCostReduction(eo, false)) / 1000;
	if (hpCost > 0 && hpCost > user->GetCurrentHP()) {
		return false;
	}
	int mpCost = abilityData->MPCost[checkRank] * (1000 - user->GetMPCostReduction(eo, false)) / 1000;
	if (mpCost > 0 && mpCost > user->GetCurrentMP()) {
		return false;
	}
	int spCost = abilityData->SPCost[checkRank] * (1000 - user->GetSPCostReduction(eo, false)) / 1000;
	if (spCost > 0 && spCost > user->GetCurrentSP()) {
		return false;
	}

	if (user->IsPlayer()) {
		Player* player = static_cast<Player*>(user);
		EquipType weaponType = player->GetWeaponEquipType();
		auto& allowedTypes = abilityData->RequiredWeaponTypes;
		if (!allowedTypes.empty() && std::find(allowedTypes.begin(), allowedTypes.end(), weaponType) == allowedTypes.end()) {
			return false;
		}
	}

	// todo: status checks
	if (user->IsDisarmed()) {
		auto& categories = abilityData->Categories;
		if (std::find(categories.begin(), categories.end(), Category::Skill) != categories.end()) {
			return false;
		}
	}

	return true;
}

bool Ability::IsPassive() {
	return abilityData->IsPassive;
}

int Ability::GetCurrentCooldown() {
	return remainingCooldown;
}

int Ability::GetCurrentCharges() {
	return charges;
}

int Ability::GetRangeValue(Actor* user) {
	int range = abilityData->Range[currentRank];

	if (user != nullptr) {
		EventOptions eventOptions = getEventOptions();
		range += user->GetRange(eventOptions, false);
	}

	return range;
}

bool Ability::IsProjectile() {
	return abilityData->IsProjectile;
}

bool Ability::IgnoreLineOfSight() {
	return abilityData->IgnoreLineOfSight;
}

bool Ability::IsSpell() {
	auto& categories = abilityData->Categories;
	return std::find(categories.begin(), categories.end(), Category::Spell) != categories.end();
}

std::vector<sf::Vector2i> Ability::GetRange(Actor* user, DungeonScene* dungeonScene) {
	return GetRange(user, dungeonScene, user->GetLocation());
}

std::vector<sf::Vector2i> Ability::GetRange(Actor* user, DungeonScene* dungeonScene, sf::Vector2i location) {
	std::vector<sf::Vector2i> result;
	std::vector<sf::Vector2i> rangeArea;
	EventOptions eventOptions = getEventOptions();
	int range = abilityData->Range[currentRank];
	if (range == -1) {
		range = user->GetAttackRange();
	}
	range += user->GetRange(eventOptions, false);
	rangeArea = TileMath::AreaOfEffect(location, range);
	result.reserve(rangeArea.size());

	// line of sight
	for (auto t : rangeArea) {
		if (!dungeonScene->IsOpeque(t)) {
			if (abilityData->IgnoreLineOfSight || dungeonScene->InLineOfSight(location, t)) {
				result.push_back(t);
			}
		}
	}

	result.shrink_to_fit();
	return result;
}

std::vector<sf::Vector2i> Ability::GetTargetArea(sf::Vector2i cursor, Actor* user, DungeonScene* dungeonScene) {
	std::vector<sf::Vector2i> result;
	std::vector<sf::Vector2i> area = abilityData->GetTargetArea(user, dungeonScene, cursor, currentRank);

	result.reserve(area.size());
	// line of sight
	if (!abilityData->AreaIgnoreLineOfSight) {
		for (auto t : area) {
			if (dungeonScene->InLineOfSight(cursor, t) && !dungeonScene->IsOpeque(t)) {
				result.push_back(t);
			}
		}
	}
	result.shrink_to_fit();
	return result;
}

std::vector<sf::Vector2i> Ability::GetExtraArea(sf::Vector2i cursor, Actor* user, DungeonScene* dungeonScene) {
	int checkRank = std::max(currentRank, 0);
	return abilityData->GetExtraArea(user, dungeonScene, cursor, checkRank);
}

void Ability::Execute(Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& area) {
	EventOptions eventOptions = getEventOptions();

	// weapon accuracy
	if (eventOptions.BaseHitChance == -1) {
		eventOptions.BaseHitChance = user->GetWeaponHitChance();
	}

	// spend resources
	user->SpendResource(abilityData->HPCost[currentRank], eventOptions, AttributeType::HP);
	user->SpendResource(abilityData->MPCost[currentRank], eventOptions, AttributeType::MP);
	user->SpendResource(abilityData->SPCost[currentRank], eventOptions, AttributeType::SP);

	// use ability
	abilityData->Execute(user, targets, cursor, area, eventOptions, currentRank);

	// double stike
	if (abilityData->CanDoubleStrike && !targets.empty() && targets[0]->IsAlive() && Random::RandomInt(1, 1000) <= user->GetDoubleStrikeChance(eventOptions, true) + abilityData->BonusDoubleStrikeChance[currentRank]) {
		doubleStrike(user, targets[0]);
	}

	// exhaust user
	int cost = abilityData->UseTime[currentRank];

	// if negative, multiply by weapon attack speed
	if (cost < 0) {
		cost = user->GetAttackSpeed() * cost / 1000 * -1;
	}
	cost = cost * 1000 / user->GetHaste(eventOptions, true);
	user->Wait(cost);

	// trigger cooldown
	if (abilityData->Cooldown[currentRank] > 0) {
		charges--;
		if (remainingCooldown == 0) {
			remainingCooldown = abilityData->Cooldown[currentRank] * (1000 - user->GetCooldownReduction(eventOptions, true)) / 1000;
		}
	}

	// award prizes and trigger death events
	//Combat::AwardPrizes(user, targets, eventOptions);
}

void Ability::OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
	if (abilityData != nullptr) {
		abilityData->OnEvent(eventType, user, target, eventOptions, eventResult, amount, this);
	}
}

AbilityID Ability::GetAbilityID() {
	return abilityID;
}

std::string Ability::GetName() {
	std::string name = abilityData->Name;

	switch (currentRank) {
	case 1:
		name += " II";
		break;
	case 2:
		name += " III";
		break;
	case 3:
		name += " IV";
		break;
	case 4:
		name += " V";
		break;
	case 5:
		name += " VI";
		break;
	case 6:
		name += " VII";
		break;
	case 7:
		name += " VIII";
		break;
	case 8:
		name += " IX";
		break;
	case 9:
		name += " X";
		break;
	default:
		break;
	}

	return name;
}

std::string Ability::GetIcon() {
	return "gfx/icon/ability/" + abilityData->Icon;
}

int Ability::GetUseTime(Actor* user) {
	int cost = abilityData->UseTime[currentRank];

	if (cost < 0) {
		if (user != nullptr) {
			cost = user->GetAttackSpeed() * cost / 1000 * -1;
		}
		else {
			return -1; // UI element must deal with this
		}
	}

	if (user != nullptr) {
		EventOptions eventOptions = getEventOptions();
		cost = cost * 1000 / user->GetHaste(eventOptions, false);
	}

	return cost;
}

int Ability::GetCooldown(Actor* user) {
	int cooldown = abilityData->Cooldown[currentRank];

	if (cooldown > 0) {
		if (user != nullptr) {
			EventOptions eo = getEventOptions();
			cooldown = cooldown * (1000 - user->GetCooldownReduction(eo, false)) / 1000;
		}
	}

	return cooldown;
}

int Ability::GetMPCost(Actor* user) {
	int result = abilityData->MPCost[currentRank];
	
	if (user != nullptr) {
		EventOptions eo = getEventOptions();
		result = result * (1000 - user->GetMPCostReduction(eo, false)) / 1000;
	}

	return result;
}

int Ability::GetSPCost(Actor* user) {
	int result = abilityData->SPCost[currentRank];

	if (user != nullptr) {
		EventOptions eo = getEventOptions();
		result = result * (1000 - user->GetSPCostReduction(eo, false)) / 1000;
	}

	return result;
}

std::vector<StatMod> Ability::GetStatMods() {
	if (abilityData != nullptr && !abilityData->PassiveBonuses.empty()) {
		return abilityData->PassiveBonuses[currentRank];
	}
	return {};
}

std::string Ability::GetDescription(Actor* user) {
	auto eo = getEventOptions();
	return abilityData->GetDescription(user, eo, currentRank);
}

EventOptions Ability::getEventOptions() {
	EventOptions eventOptions;

	if (abilityData != nullptr) {
		eventOptions.EventName = GetName();

		eventOptions.AbilityID = abilityID;

		eventOptions.Categories = abilityData->Categories;
		eventOptions.Elements = abilityData->Elements;

		eventOptions.CanDodge = abilityData->CanDodge;
		eventOptions.CanBlock = abilityData->CanBlock;
		eventOptions.CanCounter = abilityData->CanCounter;
		eventOptions.CanCrit = abilityData->CanCrit;
		eventOptions.CanDoubleStrike = abilityData->CanDoubleStrike;

		eventOptions.BaseHitChance = abilityData->HitChance[currentRank];
		eventOptions.BonusArmorPen = abilityData->BonusArmorPen[currentRank];
		eventOptions.BonusResistencePen = abilityData->BonusResistancePen[currentRank];
		eventOptions.BonusCritChance = abilityData->BonusCritChance[currentRank];
		eventOptions.BonusCritPower = abilityData->BonusCritPower[currentRank];
		eventOptions.BonusDoubleStrikeChance = abilityData->BonusDoubleStrikeChance[currentRank];
		eventOptions.BonusHPLeech = abilityData->BonusHPLeech[currentRank];
		eventOptions.BonusMPLeech = abilityData->BonusMPLeech[currentRank];
		eventOptions.BonusSPLeech = abilityData->BonusSPLeech[currentRank];
	}

	return eventOptions;
}

void Ability::doubleStrike(Actor* user, Actor* target) {
	EventOptions eo = doubleStrikeEO;
	eo.BaseHitChance = user->GetWeaponHitChance();
	eo.Elements = { user->GetAttackElement() };

	Combat::SkillDamage(user, target, eo, user->GetDoubleStrikeDamage(eo, true));
}