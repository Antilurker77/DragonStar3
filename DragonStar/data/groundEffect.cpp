// ================================================================
//
// groundEffect.cpp
//
// ================================================================

#include "groundEffect.hpp"

#include "../entity/actor.hpp"
#include "../scene/dungeonScene.hpp"

GroundEffect::GroundEffect() {

}

GroundEffect::GroundEffect(GroundEffectID id, int rank, sf::Vector2i location, int ssDamage, int ssCritChance, int ssResPen, Actor* user, size_t userIndex) {
	currentRank = rank;
	this->location = location;
	snapshotDamage = ssDamage;
	snapshotCritChance = ssCritChance;
	snapshotResistancePen = ssResPen;
	source = user;
	sourceIndex = userIndex;
	Initialize(id);
}

GroundEffect::GroundEffect(GroundEffectSave& geSave) {
	Initialize(static_cast<GroundEffectID>(geSave.GroundEffectID));
	location.x = geSave.XLocation;
	location.y = geSave.YLocation;
	currentDuration = geSave.CurrentDuration;
	nextTick = geSave.NextTick;
	currentRank = geSave.Rank;
	sourceIndex = geSave.SourceIndex;
	snapshotDamage = geSave.SSDamage;
	snapshotCritChance = geSave.SSCritChance;
	snapshotResistancePen = geSave.SSResPen;
}

void GroundEffect::Initialize(GroundEffectID id) {
	groundEffectID = id;
	groundEffectData = &groundEffectList[id];

	currentDuration = groundEffectData->Duration[currentRank];
	nextTick = groundEffectData->TickRate;
}

void GroundEffect::SetOwnerPointer(DungeonScene* dungeonScene) {
	source = dungeonScene->GetActorByIndex(sourceIndex);
}

Actor* GroundEffect::GetSource() {
	return source;
}

void GroundEffect::Tick(Actor* owner) {
	if (groundEffectData != nullptr) {
		if (nextTick > 0) {
			nextTick--;
			if (nextTick == 0) {
				if (owner != nullptr) {
					EventOptions eo = getEventOptions();
					groundEffectData->OnTick(source, owner, eo, currentRank, this);
				}
				nextTick = groundEffectData->TickRate;
			}
		}

		if (currentDuration > 0) {
			currentDuration--;
			if (currentDuration == 0 && owner != nullptr) {
				EventOptions eo = getEventOptions();
				groundEffectData->OnExpiry(source, owner, eo, currentRank, this);
			}
		}
	}
}

bool GroundEffect::IsExpired() {
	if (groundEffectData != nullptr) {
		if (groundEffectData->Duration[currentRank] > 0 && currentDuration == 0) {
			return true;
		}
	}
	return false;
}

void GroundEffect::OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
	if (groundEffectData != nullptr) {
		EventOptions eo = getEventOptions();
		groundEffectData->OnEvent(eventType, eo, currentRank, this, user, target, eventOptions, eventResult, amount);
	}
}

size_t GroundEffect::GetSourceIndex() {
	return sourceIndex;
}

int GroundEffect::GetCurrentDuration() {
	return currentDuration;
}

int GroundEffect::GetNextTick() {
	return nextTick;
}

sf::Vector2i GroundEffect::GetLocation() {
	return location;
}

int GroundEffect::GetSnapshotDamage() {
	return snapshotDamage;
}

int GroundEffect::GetSnapshotCritChance() {
	return snapshotCritChance;
}

int GroundEffect::GetSnapshotResistancePen() {
	return snapshotResistancePen;
}

std::string GroundEffect::GetName() {
	std::string name = "Unknown Ground Effect";

	if (groundEffectData != nullptr) {
		name = groundEffectData->Name;
	}

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

std::string GroundEffect::GetDescription() {
	if (groundEffectData != nullptr) {
		EventOptions eo = getEventOptions();
		return groundEffectData->GetDescription(source, eo, currentRank, this);
	}
	else {
		return "Description error.";
	}
}

GroundEffectID GroundEffect::GetGroundEffectID() {
	return groundEffectID;
}

int GroundEffect::GetRank() {
	return currentRank;
}

bool GroundEffect::HasDuration() {
	if (groundEffectData != nullptr) {
		return groundEffectData->Duration[currentRank] > 0;
	}
	return false;
}

bool GroundEffect::IsBuff() {
	if (groundEffectData != nullptr) {
		return groundEffectData->IsBuff;
	}
	return false;
}

bool GroundEffect::IsStun() {
	if (groundEffectData != nullptr) {
		return groundEffectData->IsStun;
	}
	return false;
}

bool GroundEffect::IsDisarm() {
	if (groundEffectData != nullptr) {
		return groundEffectData->IsDisarm;
	}
	return false;
}

bool GroundEffect::IsSilence() {
	if (groundEffectData != nullptr) {
		return groundEffectData->IsSilence;
	}
	return false;
}

std::vector<StatMod> GroundEffect::GetStatMods() {
	if (groundEffectData != nullptr && !groundEffectData->StatMods.empty()) {
		return groundEffectData->StatMods[currentRank];
	}
	return {};
}

EventOptions GroundEffect::getEventOptions() {
	EventOptions eo;

	eo.EventName = GetName();

	eo.GroundEffectID = groundEffectID;

	eo.Categories = groundEffectData->Categories;
	eo.Elements = groundEffectData->Elements;

	eo.CanDodge = false;
	eo.CanBlock = false;
	eo.CanCounter = false;
	eo.CanCrit = groundEffectData->CanCrit;
	eo.CanDoubleStrike = false;

	eo.BaseHitChance = 1000;
	eo.BonusArmorPen = groundEffectData->BonusArmorPen[currentRank];
	eo.BonusResistancePen = groundEffectData->BonusResistancePen[currentRank];
	eo.BonusCritChance = groundEffectData->BonusCritChance[currentRank];
	eo.BonusCritPower = groundEffectData->BonusCritPower[currentRank];
	eo.BonusDoubleStrikeChance = groundEffectData->BonusDoubleStrikeChance[currentRank];
	eo.BonusHPLeech = groundEffectData->BonusHPLeech[currentRank];
	eo.BonusMPLeech = groundEffectData->BonusMPLeech[currentRank];
	eo.BonusSPLeech = groundEffectData->BonusSPLeech[currentRank];

	eo.SnapshotDamage = snapshotDamage;
	eo.SnapshotCritChance = snapshotCritChance;
	eo.SnapshotResistancePen = snapshotResistancePen;


	return eo;
}