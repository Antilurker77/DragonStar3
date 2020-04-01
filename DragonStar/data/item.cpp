// ================================================================
//
// item.cpp
//
// ================================================================

#include "item.hpp"

#include <algorithm>
#include "ability.hpp"
#include "id/category.hpp"
#include "id/element.hpp"
#include "id/equipType.hpp"
#include "id/itemID.hpp"
#include "id/rarity.hpp"
#include "../core/random.hpp"
#include "../core/records.hpp"

Item::Item() {
	itemID = ItemID::Undefined;
}

Item::Item(ItemID id) {
	Initialize(id);
}

Item::Item(ItemSave& itemSave) {
	rarity = static_cast<Rarity>(itemSave.Rarity);
	Initialize(static_cast<ItemID>(itemSave.ItemID));
	
	randomStatMods.reserve(itemSave.StatModTypes.size());
	for (size_t i = 0; i < itemSave.StatModTypes.size(); i++) {
		if (itemSave.StatModElements[i] == 0) {
			randomStatMods.push_back(StatMod(static_cast<StatModType>(itemSave.StatModTypes[i]), itemSave.StatModValues[i]));
		}
		else if (static_cast<StatModType>(itemSave.StatModTypes[i]) == StatModType::OnHitDamage) {
			randomStatMods.push_back(StatMod(static_cast<StatModType>(itemSave.StatModTypes[i]), itemSave.StatModValues[i], Category::Direct));
		}
		else {
			randomStatMods.push_back(StatMod(static_cast<StatModType>(itemSave.StatModTypes[i]), itemSave.StatModValues[i], static_cast<Element>(itemSave.StatModElements[i])));
		}
	}
}

void Item::Initialize(ItemID id) {
	itemID = id;

	if (id != ItemID::Undefined) {
		itemData = &itemList[id];

		if (itemList[itemID].InvokeAbility != static_cast<AbilityID>(0)) {
			invokedAbility = Ability(itemData->InvokeAbility, 0);
		}

		if (itemList[itemID].ItemType != ItemType::Equipment) {
			rarity = Rarity::Item;
		}
		else if (itemList[itemID].Artifact) {
			rarity = Rarity::FixedArtifact;
		}
	}
}

void Item::InitRandomItem(int itemLevel) {
	ItemType choosenType;
	int randSum = 0;
	for (auto& weight : itemTypeWeights) {
		randSum += weight.second;
	}
	
	int random = Random::RandomInt(1, randSum);

	for (auto& weight : itemTypeWeights) {
		random -= weight.second;
		if (random <= 0) {
			choosenType = weight.first;
			break;
		}
	}
	
	switch (choosenType) {
	case ItemType::Equipment:
		InitEquipment(itemLevel);
		break;
	case ItemType::Potion:
		InitPotion(itemLevel);
		break;
	case ItemType::Scroll:
		InitScroll(itemLevel);
		break;
	case ItemType::Tome:
		InitTome(itemLevel);
		break;
	case ItemType::Consumable:
		Initialize(ItemID::Rations);
		break;
	default:
		break;
	}

}

void Item::InitPotion(int itemLevel) {
	ItemID potionToGenerate{};
	std::vector<ItemWeight> possiblePotions;
	possiblePotions.reserve(potionWeights.size());
	int weightSum = 0;

	for (auto& weight : potionWeights) {
		if (itemLevel >= weight.MinItemLevel && itemLevel <= weight.MaxItemLevel) {
			possiblePotions.push_back(weight);
			weightSum += weight.Weight;
		}
	}

	int random = Random::RandomInt(1, weightSum);

	for (auto& weight : possiblePotions) {
		random -= weight.Weight;
		if (random <= 0) {
			potionToGenerate = weight.ItemID;
			break;
		}
	}

	Initialize(potionToGenerate);
}

void Item::InitScroll(int itemLevel) {
	ItemID scrollToGenerate{};
	std::vector<ItemWeight> possibleScrolls;
	possibleScrolls.reserve(scrollWeights.size());
	int weightSum = 0;

	for (auto& weight : scrollWeights) {
		if (itemLevel >= weight.MinItemLevel && itemLevel <= weight.MaxItemLevel) {
			possibleScrolls.push_back(weight);
			weightSum += weight.Weight;
		}
	}

	int random = Random::RandomInt(1, weightSum);

	for (auto& weight : possibleScrolls) {
		random -= weight.Weight;
		if (random <= 0) {
			scrollToGenerate = weight.ItemID;
			break;
		}
	}

	Initialize(scrollToGenerate);
}

void Item::InitTome(int itemLevel) {
	ItemID tomeToGenerate{};
	std::vector<ItemWeight> possibleTomes;
	possibleTomes.reserve(tomeWeights.size());
	int weightSum = 0;

	for (auto& weight : tomeWeights) {
		if (itemLevel >= weight.MinItemLevel && itemLevel <= weight.MaxItemLevel) {
			possibleTomes.push_back(weight);
			weightSum += weight.Weight;
		}
	}

	int random = Random::RandomInt(1, weightSum);

	for (auto& weight : possibleTomes) {
		random -= weight.Weight;
		if (random <= 0) {
			tomeToGenerate = weight.ItemID;
			break;
		}
	}

	Initialize(tomeToGenerate);
}

void Item::InitEquipment(int itemLevel) {
	EquipType equipType{};
	ItemID itemToGenerate{};
	size_t affixes = 0;

	// Rarity
	int raritySum = 0;
	for (auto& weight : rarityWeights) {
		raritySum += weight.second;
	}

	int rarityRoll = Random::RandomInt(1, raritySum);

	for (auto& weight : rarityWeights) {
		rarityRoll -= weight.second;
		if (rarityRoll <= 0) {
			rarity = weight.first;
			break;
		}
	}

	switch (rarity) {
		case Rarity::Common:
			break;
		case Rarity::Magical:
			affixes = 2;
			break;
		case Rarity::Rare:
			affixes = 5;
			break;
		case Rarity::RandomArtifact:
			affixes = 6;
			break;
		default:
			break;
	}

	// Pick equipment type.
	int typeSum = 0;
	for (auto& weight : equipTypeWeights) {
		typeSum += weight.second;
	}

	int typeRoll = Random::RandomInt(1, typeSum);

	for (auto& weight : equipTypeWeights) {
		typeRoll -= weight.second;
		if (typeRoll <= 0) {
			equipType = weight.first;
			break;
		}
	}

	// If fixed artifact, find out which artifacts haven't dropped.
	std::vector<ItemWeight> possibleArtifacts{};
	if (rarity == Rarity::FixedArtifact) {
		for (auto& w : artifactWeights[equipType]) {
			if (!records.SeenArtifact(w.ItemID) && itemLevel >= w.MinItemLevel && itemLevel <= w.MaxItemLevel) {
				possibleArtifacts.push_back(w);
			}
		}
		// If there are no possible artifacts found, allow low-level artifacts to drop.
		if (possibleArtifacts.empty()) {
			for (auto& w : artifactWeights[equipType]) {
				if (!records.SeenArtifact(w.ItemID) && itemLevel >= w.MinItemLevel) {
					possibleArtifacts.push_back(w);
				}
			}
		}
		// If still empty, drop a random artifact instead.
		if (possibleArtifacts.empty()) {
			rarity = Rarity::RandomArtifact;
			affixes = 6;
		}
	}

	// Pick item type.
	int baseSum = 0;
	int baseRoll = 0;
	std::vector<ItemWeight> possibleBases;

	if (rarity == Rarity::FixedArtifact) {
		possibleBases = possibleArtifacts;
	}
	else {
		for (auto& weight : baseTypeWeights[equipType]) {
			if (itemLevel >= weight.MinItemLevel && itemLevel <= weight.MaxItemLevel) {
				possibleBases.push_back(weight);
			}
		}
	}

	for (auto& weight : possibleBases) {
		baseSum += weight.Weight;
	}

	baseRoll = Random::RandomInt(1, baseSum);

	for (auto& weight : possibleBases) {
		baseRoll -= weight.Weight;
		if (baseRoll <= 0) {
			itemToGenerate = weight.ItemID;
			break;
		}
	}

	// Initialize item.
	Initialize(itemToGenerate);

	// Mark artifact as spawned.
	if (rarity == Rarity::FixedArtifact) {
		records.MarkSpawnedArtifact(itemToGenerate);
	}

	// Add affixes.
	std::vector<AffixWeight> choosenAffixes;
	std::vector<AffixWeight> possibleAffixes;
	choosenAffixes.reserve(affixes);
	possibleAffixes.reserve(affixWeights[equipType].size());

	for (size_t i = 0; i < affixes; i++) {
		int affixSum = 0;
		possibleAffixes.clear();
		for (auto& weight : affixWeights[equipType]) {
			if (weight.StatMod == StatModType::Resistance || std::find_if(choosenAffixes.begin(), choosenAffixes.end(), [&weight](AffixWeight& check) {return check.StatMod == weight.StatMod; }) == choosenAffixes.end()) {
				affixSum += weight.Weight;
				possibleAffixes.push_back(weight);
			}
		}

		int affixRoll = Random::RandomInt(1, affixSum);

		for (auto& weight : possibleAffixes) {
			affixRoll -= weight.Weight;
			if (affixRoll <= 0) {
				choosenAffixes.push_back(weight);
				break;
			}
		}
	}

	std::vector<Element> resistanceElements = { Element::Arcane, Element::Fire, Element::Ice, Element::Lightning, Element::Water, Element::Poison, Element::Dark };
	size_t resistanceCount = 0;
	for (auto& a : choosenAffixes) {
		int percent = (itemLevel - a.MinItemLevel) * 1000 / (100 - a.MinItemLevel);
		int value = a.MinValue + ((a.MaxValue - a.MinValue) * percent / 1000);
		value = value * Random::RandomInt(850, 1150) / 1000;
		value = std::clamp(value, a.MinValue, a.MaxValue);
		if (a.StatMod == StatModType::Resistance) {
			size_t elementIndex = Random::RandomSizeT(0, resistanceElements.size() - resistanceCount - 1);
			Element element = resistanceElements[elementIndex];
			randomStatMods.push_back(StatMod(a.StatMod, value, element));

			// don't pick same element twice
			resistanceCount++;
			std::swap(resistanceElements[elementIndex], resistanceElements.back());
		}
		else if (a.StatMod == StatModType::OnHitDamage) {
			randomStatMods.push_back(StatMod(a.StatMod, value, Category::Direct));
		}
		else {
			randomStatMods.push_back(StatMod(a.StatMod, value));
		}
	}

	// Sort
	std::sort(randomStatMods.begin(), randomStatMods.end(), [](StatMod& left, StatMod& right) {return left.statModType < right.statModType; });
}

void Item::UseItem(Actor* user, std::vector<Actor*>& targets, sf::Vector2i cursor, std::vector<sf::Vector2i>& area) {
	if (itemData != nullptr && itemData->InvokeAbility != static_cast<AbilityID>(0)) {
		invokedAbility.Execute(user, targets, cursor, area);
	}
}

void Item::OnEvent(EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
	if (itemData != nullptr) {
		itemData->OnEvent(eventType, user, target, eventOptions, eventResult, amount);
	}
}

bool Item::IsNull() {
	return itemID == ItemID::Undefined;
}

ItemID Item::GetItemID() {
	return itemID;
}

Rarity Item::GetRarity() {
	return rarity;
}

ItemType Item::GetItemType() {
	return itemData->ItemType;
}

int Item::GetMaxStackSize() {
	return std::max(1, itemData->MaxStacks);
}

Ability* Item::GetInvokedAbility() {
	if (itemData != nullptr && itemData->InvokeAbility != static_cast<AbilityID>(0)) {
		return &invokedAbility;
	}
	return nullptr;
}

std::vector<AbilityID>& Item::GetTeachableAbilities() {
	return itemData->TeachableAbilities;
}

std::string Item::GetName() {
	ItemType type = itemData->ItemType;
	if (type == ItemType::Potion) {
		std::string name = records.GetLabel(itemID);
		if (records.IsIdentified(itemID)) {
			name += " " + itemData->Name;
		}
		else {
			name += " Potion";
		}
		return name;
	}
	if (type == ItemType::Scroll) {
		std::string name = "'" + records.GetLabel(itemID) + "'";
		if (records.IsIdentified(itemID)) {
			name += " " + itemData->Name;
		}
		else {
			name += " Scroll";
		}
		return name;
	}

	return itemData->Name;
}

std::string Item::GetIconFilePath() {
	return "gfx/icon/item/" + itemData->IconFilePath;
}

std::string Item::GetEquipFilePath() {
	return itemData->EquipFilePath;
}

bool Item::HideHair() {
	return itemData->HideHair;
}

int Item::GetValue() {
	int value = 0;

	if (itemData != nullptr) {
		value = itemData->BaseValue;

		for (auto& sm : randomStatMods) {
			int multiplier = 0; // 0.00
			switch (sm.statModType) {
				case StatModType::HP:
					multiplier = 100;
					break;
				case StatModType::HPLeech:
					multiplier = 10;
					break;
				case StatModType::HPOnHit:
					multiplier = 300;
					break;
				case StatModType::HPOnKill:
					multiplier = 50;
				case StatModType::MP:
					multiplier = 125;
					break;
				case StatModType::MPLeech:
					multiplier = 12;
					break;
				case StatModType::MPOnHit:
					multiplier = 375;
					break;
				case StatModType::MPOnKill:
					multiplier = 62;
					break;
				case StatModType::SP:
					multiplier = 200;
					break;
				case StatModType::SPLeech:
					multiplier = 20;
					break;
				case StatModType::SPOnHit:
					multiplier = 600;
					break;
				case StatModType::SPOnKill:
					multiplier = 200;
					break;
				case StatModType::STR:
					multiplier = 500;
					break;
				case StatModType::DEX:
					multiplier = 500;
					break;
				case StatModType::MAG:
					multiplier = 500;
					break;
				case StatModType::VIT:
					multiplier = 500;
					break;
				case StatModType::SPI:
					multiplier = 500;
					break;
				case StatModType::AllAttributes:
					multiplier = 2500;
					break;
				case StatModType::Armor:
					multiplier = 200;
					break;
				case StatModType::ArmorPen:
					multiplier = 10;
					break;
				case StatModType::MagicArmor:
					multiplier = 200;
					break;
				case StatModType::MagicArmorPen:
					multiplier = 10;
					break;
				case StatModType::Evasion:
					multiplier = 300;
					break;
				case StatModType::Resistance:
					multiplier = 5;
					break;
				case StatModType::ResistancePen:
					multiplier = 5;
					break;
				case StatModType::AttackPower:
					multiplier = 300;
					break;
				case StatModType::SpellPower:
					multiplier = 300;
					break;
				case StatModType::Accuracy:
					multiplier = 300;
					break;
				case StatModType::BlockChance:
					multiplier = 20;
					break;
				case StatModType::Damage:
					multiplier = 10;
					break;
				case StatModType::DamageTaken:
					multiplier = -50;
					break;
				case StatModType::Healing:
					multiplier = 10;
					break;
				case StatModType::CritChance:
					multiplier = 10;
					break;
				case StatModType::CritPower:
					multiplier = 20;
					break;
				case StatModType::Haste:
					multiplier = 15;
					break;
				case StatModType::DoubleStrikeChance:
					multiplier = 10;
					break;
				case StatModType::OnHitDamage:
					multiplier = 300;
					break;
				case StatModType::CooldownReduction:
					multiplier = 20;
					break;
				case StatModType::MPCostReduction:
					multiplier = 20;
					break;
				case StatModType::SPCostReduction:
					multiplier = 40;
					break;
				case StatModType::StunResistance:
					multiplier = 2;
					break;
				case StatModType::SnareResistance:
					multiplier = 2;
					break;
				case StatModType::DisarmResistance:
					multiplier = 2;
					break;
				case StatModType::SilenceResistance:
					multiplier = 2;
					break;
				case StatModType::MovementSpeed:
					multiplier = 15;
					break;
				case StatModType::SightRadius:
					multiplier = 3;
					break;
				case StatModType::GoldFind:
					multiplier = 30;
					break;
				case StatModType::EXPBoost:
					multiplier = 30;
					break;
				default:
					multiplier = 100;
					break;
			}

			value += sm.value * multiplier / 100;
		}

		if (rarity == Rarity::Magical) {
			value = value * 120 / 100;
		}
		else if (rarity == Rarity::Rare) {
			value = value * 140 / 100;
		}
		else if (rarity == Rarity::RandomArtifact) {
			value = value * 160 / 100;
		}


	}

	return value;
}

EquipType Item::GetEquipType() {
	return itemData->EquipType;
}

bool Item::IsWeapon() {
	std::vector<EquipType> weaponTypes = {
		EquipType::Sword,
		EquipType::Axe,
		EquipType::Mace,
		EquipType::Dagger,
		EquipType::Spear,
		EquipType::Bow,
		EquipType::Wand,
		EquipType::Staff
	};
	return std::find(weaponTypes.begin(), weaponTypes.end(), itemData->EquipType) != weaponTypes.end();
}

bool Item::IsTwoHanded() {
	if (itemData->EquipType == EquipType::Bow) {
		return true;
	}
	return false;
}

Element Item::GetAttackElement() {
	return itemData->AttackElement;
}

int Item::GetHitChance() {
	return itemData->HitChance;
}

int Item::GetAttackRange() {
	return itemData->AttackRange;
}

int Item::GetAttackSpeed() {
	return itemData->AttackSpeed;
}

int Item::GetWeaponDamageMultiplier() {
	return itemData->WeaponDamageMultiplier;
}

std::vector<StatMod> Item::GetStatMods() {
	std::vector<StatMod> result(itemData->ImplicitStatMods);
	result.reserve(itemData->ImplicitStatMods.size() + itemData->ExplicitStatMods.size() + randomStatMods.size());
	result.insert(result.end(), itemData->ExplicitStatMods.begin(), itemData->ExplicitStatMods.end());
	result.insert(result.end(), randomStatMods.begin(), randomStatMods.end());
	return result;
}

std::vector<StatMod>& Item::GetImplicitStatMods() {
	return itemData->ImplicitStatMods;
}

std::vector<StatMod>& Item::GetExplicitStatMods() {
	return itemData->ExplicitStatMods;
}

std::vector<StatMod>& Item::GetRandomStatMods() {
	return randomStatMods;
}

std::vector<std::string>& Item::GetBonusModStrings() {
	return itemData->BonusModStrings;
}