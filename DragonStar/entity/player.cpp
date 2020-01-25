// ================================================================
//
// player.cpp
//
// ================================================================

#include "player.hpp"

#include <iostream>
#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/id/abilityID.hpp"
#include "../data/id/element.hpp"
#include "../data/id/equipType.hpp"
#include "../data/id/itemID.hpp"
#include "../data/id/raceID.hpp"
#include "../ui/inventory.hpp"
#include "../ui/messageLog.hpp"

Player::Player() {	
	name = "Test Char";
	isPlayer = true;
	level = 1;
	isFemale = true;
	index = 0;

	Initialize(RaceID::Human);

	equipment[0].Initialize(ItemID::TravelerBlade);
	equipment[3].Initialize(ItemID::IronArmor);
	//equipment[0].Initialize(ItemID::Flametongue);
	//equipment[1].Initialize(ItemID::LastDefender);
	//equipment[4].Initialize(ItemID::ArenaGauntlets);
	//equipment[5].Initialize(ItemID::Windriders);
	equipment[8].Initialize(ItemID::DebugRing);
	setEquipmentSprites();

	// test
	//abilities.push_back(Ability(AbilityID::MagicMissile, 0));
	//abilities.push_back(Ability(AbilityID::BoltOfLight, 0));
	//abilities.push_back(Ability(AbilityID::FlameBolt, 0));
	//abilities.push_back(Ability(AbilityID::DragonfireBolt, 4));
	//abilities.push_back(Ability(AbilityID::WaterBolt, 0));
	//abilities.push_back(Ability(AbilityID::Shock, 0));
	//abilities.push_back(Ability(AbilityID::PowerStrike, 4));
	//abilities.push_back(Ability(AbilityID::Heal, 3));
	//abilities.push_back(Ability(AbilityID::Venom, 0));
	//abilities.push_back(Ability(AbilityID::DragonBreath, 0));

	//abilities.push_back(Ability(AbilityID::Constitution, 4));
	//abilities.push_back(Ability(AbilityID::Focus, 4));

	currentHP = GetMaxHP();
	currentMP = GetMaxMP();
	currentSP = GetMaxSP();
	abilityPoints = 2;
}

Player::Player(ActorSave& actorSave, PlayerSave& playerSave) {
	index = 0;
	isPlayer = true;
	
	name = playerSave.PlayerName;
	level = playerSave.PlayerLevel;
	exp = playerSave.PlayerEXP;
	statPoints = playerSave.StatPoints;
	abilityPoints = playerSave.AbilityPoints;
	isFemale = true; // todo: save gender

	Initialize(static_cast<RaceID>(playerSave.RaceID));

	currentHP = actorSave.CurrentHP;
	currentMP = actorSave.CurrentMP;
	currentSP = actorSave.CurrentSP;
	exhaustion = actorSave.Exhaustion;
	Warp(sf::Vector2i(actorSave.XLocation, actorSave.YLocation));

	for (size_t i = 0; i < playerSave.Equipment.size(); i++) {
		equipment[i] = Item(playerSave.Equipment[i]);
	}

	abilities.clear();
	abilities.reserve(playerSave.Abilities.size());
	for (size_t i = 0; i < playerSave.Abilities.size(); i++) {
		Ability ability(static_cast<AbilityID>(playerSave.Abilities[i]), playerSave.AbilityRanks[i]);
		ability.SetCooldownAndCharges(actorSave.AbilityCooldowns[i], actorSave.AbilityCharges[i]);
		abilities.push_back(ability);
	}

	auras.clear();
	auras.reserve(actorSave.AuraIDs.size());
	for (size_t i = 0; i < actorSave.AuraIDs.size(); i++) {
		Aura aura(static_cast<AuraID>(actorSave.AuraIDs[i]), actorSave.AuraRanks[i], actorSave.AuraDurations[i], actorSave.AuraNextTicks[i], actorSave.AuraStacks[i], actorSave.AuraSource[i]);
		auras.push_back(aura);
	}
}

void Player::Initialize(RaceID id) {
	raceID = id;

	// Attributes
	currentHP = GetMaxHP();
	currentMP = GetMaxMP();
	currentSP = GetMaxSP();

	// Abilities
	abilities.clear();
	abilities.reserve(1ull + raceList[raceID].Abilities.size());
	abilities.push_back(Ability(AbilityID(1), 0));
	for (auto ab : raceList[raceID].Abilities) {
		abilities.push_back(Ability(ab.AbilityID, ab.Rank));
	}

	// Sprites
	sprites.resize(1);
	std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/base";
	filepath += isFemale ? "_f.png" : "_m.png";
	sprites[0].setTexture(*assetManager.LoadTexture(filepath));
	setEquipmentSprites();
}

RaceID Player::GetRaceID() {
	return raceID;
}

void Player::Equip(InventorySlot& inventorySlot) {
	size_t slot = 0;

	switch (inventorySlot.Item.GetEquipType()) {
	case EquipType::Sword:
	case EquipType::Axe:
	case EquipType::Mace:
	case EquipType::Dagger:
	case EquipType::Spear:
	case EquipType::Bow:
	case EquipType::Wand:
	case EquipType::Staff:
		slot = 0;
		break;
	case EquipType::Shield:
		slot = 1;
		break;
	case EquipType::LightHead:
	case EquipType::MediumHead:
	case EquipType::HeavyHead:
		slot = 2;
		break;
	case EquipType::LightBody:
	case EquipType::MediumBody:
	case EquipType::HeavyBody:
		slot = 3;
		break;
	case EquipType::LightHands:
	case EquipType::MediumHands:
	case EquipType::HeavyHands:
		slot = 4;
		break;
	case EquipType::LightFeet:
	case EquipType::MediumFeet:
	case EquipType::HeavyFeet:
		slot = 5;
		break;
	case EquipType::Neck:
		slot = 6;
		break;
	case EquipType::Ring:
		if (equipment[7].IsNull()) {
			slot = 7;
			break;
		}
		else if (equipment[8].IsNull()) {
			slot = 8;
			break;
		}
		slot = 7;
		break;
	case EquipType::LightSource:
		slot = 9;
		break;
	default:
		return; // invalid type, don't try to equip
	}

	// equip the item
	std::swap(inventorySlot.Item, equipment[slot]);
	if (inventorySlot.Item.IsNull()) {
		inventorySlot.StackCount = 0;
	}
	setEquipmentSprites();
}

void Player::Equip(Item& item, size_t index) {
	size_t slot = 0;

	switch (item.GetEquipType()) {
	case EquipType::Sword:
	case EquipType::Axe:
	case EquipType::Mace:
	case EquipType::Dagger:
	case EquipType::Spear:
	case EquipType::Bow:
	case EquipType::Wand:
	case EquipType::Staff:
		slot = 0;
		break;
	case EquipType::Shield:
		slot = 1;
		break;
	case EquipType::LightHead:
	case EquipType::MediumHead:
	case EquipType::HeavyHead:
		slot = 2;
		break;
	case EquipType::LightBody:
	case EquipType::MediumBody:
	case EquipType::HeavyBody:
		slot = 3;
		break;
	case EquipType::LightHands:
	case EquipType::MediumHands:
	case EquipType::HeavyHands:
		slot = 4;
		break;
	case EquipType::LightFeet:
	case EquipType::MediumFeet:
	case EquipType::HeavyFeet:
		slot = 5;
		break;
	case EquipType::Neck:
		slot = 6;
		break;
	case EquipType::Ring:
		slot = 7;
		break;
	case EquipType::LightSource:
		slot = 9;
		break;
	default:
		return; // invalid type, don't try to equip
	}

	// index 8 is second ring slot
	if (index == slot || (slot == 7 && index == 8)) {
		std::swap(item, equipment[index]);
		setEquipmentSprites();
	}

	currentHP = std::min(currentHP, GetMaxHP());
	currentMP = std::min(currentMP, GetMaxMP());
	currentSP = std::min(currentSP, GetMaxSP());
}

Item Player::Unequip(size_t index) {
	Item eq = equipment[index];
	equipment[index] = Item();
	setEquipmentSprites();
	currentHP = std::min(currentHP, GetMaxHP());
	currentMP = std::min(currentMP, GetMaxMP());
	currentSP = std::min(currentSP, GetMaxSP());
	return eq;
}

bool Player::Unequip(Inventory& inventory, size_t index) {
	bool unequiped = inventory.AddItem(equipment[index]);
	if (unequiped) {
		equipment[index] = Item();
		setEquipmentSprites();
		return true;
	}
	return false;
}

void Player::AwardEXP(int amount) {
	exp += amount * GetEXPBoost() / 1000;
	int nextLevel = GetNextLevelEXP();
	while (exp >= nextLevel) {
		exp -= nextLevel;
		level++;
		statPoints += (level / 10) + 2;
		abilityPoints += 1;
		messageLog.AddMessage("#randart " + name + " has reached level " + std::to_string(level) + "!");
		messageLog.AddMessage("You have #randart " + std::to_string(statPoints) + " #default stat points and #randart " + std::to_string(abilityPoints) + " #default ability points to spend.");

		// full heal on level up because I'm nice
		currentHP = GetMaxHP();
		currentMP = GetMaxMP();
		currentSP = GetMaxSP();

		nextLevel = 89 + (level * 10) + static_cast<int>(pow(level, 2));
	}
}

void Player::LearnAbility(AbilityID id) {
	if (abilityPoints > 0) {
		for (auto& a : abilities) {
			if (a.GetAbilityID() == id && a.GetCurrentRank() < a.GetMaxRank()) {
				a.IncreaseRank();
				abilityPoints--;
				return;
			}
		}

		Ability newAbility(id, 0);
		abilities.push_back(newAbility);
		abilityPoints--;
	}
}

void Player::SpendStatPoint(StatModType attribute) {
	if (statPoints > 0) {
		switch (attribute) {
			case StatModType::STR:
				bonusPoints[0]++;
				statPoints--;
				break;
			case StatModType::DEX:
				bonusPoints[1]++;
				statPoints--;
				break;
			case StatModType::MAG:
				bonusPoints[2]++;
				statPoints--;
				break;
			case StatModType::VIT:
				bonusPoints[3]++;
				statPoints--;
				break;
			case StatModType::SPI:
				bonusPoints[4]++;
				statPoints--;
				break;
			default:
				break;
		}
	}
}

void Player::OnEvent(EventType eventType, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
	for (auto& ab : abilities) {
		ab.OnEvent(eventType, this, target, eventOptions, eventResult, amount);
	}

	for (auto& eq : equipment) {
		eq.OnEvent(eventType, this, target, eventOptions, eventResult, amount);
	}

	for (auto& au : auras) {
		au.OnEvent(eventType, this, target, eventOptions, eventResult, amount);
	}
}

int Player::GetWeaponHitChance() {
	int result = 700; // unarmed hit chance
	if (!equipment[0].IsNull()) {
		result = equipment[0].GetHitChance();
	}
	return result;
}

int Player::GetAttackRange() {
	int result = 100;
	if (!equipment[0].IsNull()) {
		result = equipment[0].GetAttackRange();
	}
	return result;
}

int Player::GetAttackSpeed() {
	int result = 100;
	if (!equipment[0].IsNull()) {
		result = equipment[0].GetAttackSpeed();
	}
	return result;
}

Element Player::GetAttackElement() {
	Element element = Element::Physical; // default physical for unarmed
	if (!equipment[0].IsNull()) {
		element = equipment[0].GetAttackElement();
	}
	return element;
}

int Player::GetWeaponDamageMultiplier() {
	int result = 1000;
	if (!equipment[0].IsNull()) {
		result = equipment[0].GetWeaponDamageMultiplier();
	}
	return result;
}

int Player::GetEXPReward() {
	return 0;
}

int Player::GetLootPoints() {
	return 0;
}

std::array<Item, 10>& Player::GetEquipment() {
	return equipment;
}

bool Player::IsEquipmentSlotEmpty(size_t index) {
	if (index < equipment.size()) {
		return equipment[index].IsNull();
	}
	return true;
}

int Player::GetCurrentEXP() {
	return exp;
}

int Player::GetNextLevelEXP() {
	return 89 + (level * 10) + static_cast<int>(pow(level, 2));
}

int Player::GetStatPoints() {
	return statPoints;
}

int Player::GetAbilityPoints() {
	return abilityPoints;
}

int Player::getBaseStat(StatModType statModType) {
	int result = 0;

	switch (statModType) {
		case StatModType::HP:
			result = raceList[raceID].BaseHP;
			break;
		case StatModType::MP:
			result = raceList[raceID].BaseMP;
			break;
		case StatModType::SP:
			result = raceList[raceID].BaseSP;
			break;
		case StatModType::STR:
			result = raceList[raceID].BaseSTR + bonusPoints[0] + (level - 1) * raceList[raceID].BaseSTR / 10;
			break;
		case StatModType::DEX:
			result = raceList[raceID].BaseDEX + bonusPoints[1] + (level - 1) * raceList[raceID].BaseDEX / 10;
			break;
		case StatModType::MAG:
			result = raceList[raceID].BaseMAG + bonusPoints[2] + (level - 1) * raceList[raceID].BaseMAG / 10;
			break;
		case StatModType::VIT:
			result = raceList[raceID].BaseVIT + bonusPoints[3] + (level - 1) * raceList[raceID].BaseVIT / 10;
			break;
		case StatModType::SPI:
			result = raceList[raceID].BaseSPI + bonusPoints[4] + (level - 1) * raceList[raceID].BaseSPI / 10;
			break;
		case StatModType::SightRadius:
			result = raceList[raceID].BaseLineOfSight;
			break;
		case StatModType::MovementSpeed:
			result = raceList[raceID].BaseMoveCost;
			break;
		default:
			break;
	}

	return result;
}

std::vector<StatMod>& Player::getBaseStatMods() {
	return raceList[raceID].StatMods;
}

int Player::getStatFromEquipment(int base, StatModType statModType, EventOptions& eventOptions) {
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

	// Equipment
	// Equipment bonus are always addictive.
	for (auto& e : equipment) {
		if (!e.IsNull()) {
			for (auto& s : e.GetStatMods()) {
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
		}
	}

	return result;
}

void Player::setEquipmentSprites() {
	sprites.resize(1); // reset all equipment textures but leave player texture in place

	// ASCII does not use equipment sprites.
	if (settings.Tileset != "ascii") {

		sprites.reserve(8);

		// Must be done in this order so that sprites layer properly.
		// Feet
		if (!equipment[5].IsNull()) {
			sf::Sprite s;
			std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/feet/" + equipment[5].GetEquipFilePath();
			s.setTexture(*assetManager.LoadTexture(filepath));
			s.setPosition(sprites[0].getPosition());
			sprites.push_back(s);
		}

		// Body, if slot is empty use default linen armor
		if (!equipment[3].IsNull()) {
			sf::Sprite s;
			std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/armor" + (isFemale ? "_f/" : "/") + equipment[3].GetEquipFilePath();
			s.setTexture(*assetManager.LoadTexture(filepath));
			s.setPosition(sprites[0].getPosition());
			sprites.push_back(s);
		}
		else {
			sf::Sprite s;
			std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/armor" + (isFemale ? "_f/" : "/") + "linen.png";
			s.setTexture(*assetManager.LoadTexture(filepath));
			s.setPosition(sprites[0].getPosition());
			sprites.push_back(s);
		}

		// Hair
		bool showHair = true;
		if (!equipment[2].IsNull()) {
			showHair = !equipment[2].HideHair();
		}
		if (showHair) {
			sf::Sprite s;
			std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/hair" + (isFemale ? "_f/" : "/") + "brown.png";
			s.setTexture(*assetManager.LoadTexture(filepath));
			s.setPosition(sprites[0].getPosition());
			sprites.push_back(s);
		}

		// Head
		if (!equipment[2].IsNull()) {
			sf::Sprite s;
			std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/helm/" + equipment[2].GetEquipFilePath();
			s.setTexture(*assetManager.LoadTexture(filepath));
			s.setPosition(sprites[0].getPosition());
			sprites.push_back(s);
		}

		// Hands
		if (!equipment[4].IsNull()) {
			sf::Sprite s;
			std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/hand/" + equipment[4].GetEquipFilePath();
			s.setTexture(*assetManager.LoadTexture(filepath));
			s.setPosition(sprites[0].getPosition());
			sprites.push_back(s);
		}

		// Main-Hand
		if (!equipment[0].IsNull()) {
			sf::Sprite s;
			std::string filepath = "gfx/" + settings.Tileset + "/actor/" + raceList[raceID].Filename + "/weapon/" + equipment[0].GetEquipFilePath();
			s.setTexture(*assetManager.LoadTexture(filepath));
			s.setPosition(sprites[0].getPosition());
			sprites.push_back(s);
		}


		// Off-Hand

	}
	sprites.shrink_to_fit();
}