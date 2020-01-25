// ================================================================
//
// aura.cpp
//
// ================================================================

#include "aura.hpp"

#include "../entity/actor.hpp"
#include "../scene/dungeonScene.hpp"

Aura::Aura() {

}

Aura::Aura(AuraID id, int rank, Actor* user, size_t userIndex) {
	currentRank = rank;
	source = user;
	sourceIndex = userIndex;
	Initialize(id);
}

Aura::Aura(AuraID id, int rank, int duration, int nextTick, int stacks, size_t userIndex) {
	currentRank = rank;
	sourceIndex = userIndex;
	Initialize(id);
	currentDuration = duration;
	currentStacks = stacks;
	this->nextTick = nextTick;
}

void Aura::Initialize(AuraID id) {
	auraID = id;
	auraData = &auraList[id];

	currentDuration = auraData->BaseDuration[currentRank];
	nextTick = auraData->TickRate;
	currentStacks = 1;
}

void Aura::SetOwnerPointer(DungeonScene* dungeonScene) {
	source = dungeonScene->GetActorByIndex(sourceIndex);
}

void Aura::Tick(Actor* owner) {
	if (nextTick > 0) {
		nextTick--;
		if (nextTick == 0) {
			EventOptions eo = getEventOptions();
			auraData->OnTick(source, owner, eo, currentRank);
			nextTick = auraData->TickRate;
		}
	}
	
	if (currentDuration > 0) {
		currentDuration--;
		if (currentDuration == 0) {
			EventOptions eo = getEventOptions();
			auraData->OnExpiry(source, owner, eo, currentRank);
			if (auraData->StacksExpireOneByOne) {
				currentStacks--;
				currentDuration = auraData->BaseDuration[currentRank];
			}
			else {
				currentStacks = 0;
			}
		}
	}
}

void Aura::OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
	if (auraData != nullptr) {
		EventOptions auraOptions = getEventOptions();
		auraData->OnEvent(eventType, auraOptions, currentRank, user, target, eventOptions, eventResult, amount);
	}
}

void Aura::Refresh(Actor* newSource, size_t newSourceIndex, int rank) {
	source = newSource;
	sourceIndex = newSourceIndex;
	currentRank = rank;

	currentDuration += auraData->BaseDuration[currentRank];
	int maxDuration = auraData->MaxDuration[currentRank];
	if (currentDuration > maxDuration) {
		currentDuration = maxDuration;
	}

	if (currentStacks < auraData->MaxStacks[currentRank]) {
		currentStacks++;
	}
}

void Aura::RemoveStack() {
	if (currentStacks > 0) {
		currentStacks--;
	}
}

std::string Aura::GetName() {
	std::string name = auraData->Name;

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

std::string Aura::GetDescription() {
	auto eo = getEventOptions();
	return auraData->GetDescription(source, eo, currentRank);
}

std::string Aura::GetIcon() {
	return "gfx/icon/ability/" + auraData->Icon;
}

size_t Aura::GetSourceIndex() {
	return sourceIndex;
}

int Aura::GetCurrentDuration() {
	return currentDuration;
}

int Aura::GetNextTick() {
	return nextTick;
}

int Aura::GetCurrentStackSize() {
	return currentStacks;
}

bool Aura::IsExpired() {
	return currentStacks == 0;
}

AuraID Aura::GetAuraID() {
	return auraID;
}

int Aura::GetRank() {
	return currentRank;
}

bool Aura::HasDuration() {
	return auraData->MaxDuration[currentRank] != 0;
}

bool Aura::IsBuff() {
	return auraData->IsBuff;
}

bool Aura::IsUnique() {
	return auraData->Unique;
}

bool Aura::IsUniqueByActor() {
	return auraData->UniqueByActor;
}

bool Aura::IsRest() {
	if (auraData != nullptr) {
		return auraData->IsRest;
	}
	return false;
}

bool Aura::IsStun() {
	if (auraData != nullptr) {
		return auraData->IsStun;
	}
	return false;
}


std::vector<StatMod> Aura::GetStatMods() {
	if (!auraData->StatMods.empty()) {
		return auraData->StatMods[currentRank];
	}
	return {};
}

EventOptions Aura::getEventOptions() {
	EventOptions eo;

	eo.EventName = GetName();

	eo.AuraID = auraID;

	eo.Categories = auraData->Categories;
	eo.Elements = auraData->Elements;

	eo.CanDodge = false;
	eo.CanBlock = false;
	eo.CanCounter = false;
	eo.CanCrit = auraData->CanCrit;
	eo.CanDoubleStrike = false;

	eo.BaseHitChance = 1000;
	eo.BonusArmorPen = auraData->BonusArmorPen[currentRank];
	eo.BonusResistencePen = auraData->BonusResistancePen[currentRank];
	eo.BonusCritChance = auraData->BonusCritChance[currentRank];
	eo.BonusCritPower = auraData->BonusCritPower[currentRank];
	eo.BonusDoubleStrikeChance = auraData->BonusDoubleStrikeChance[currentRank];
	eo.BonusHPLeech = auraData->BonusHPLeech[currentRank];
	eo.BonusMPLeech = auraData->BonusMPLeech[currentRank];
	eo.BonusSPLeech = auraData->BonusSPLeech[currentRank];

	return eo;
}