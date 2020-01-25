// ================================================================
//
// inventory.cpp
//
// ================================================================

#include "inventory.hpp"

#include "rarityColor.hpp"
#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/id/element.hpp"
#include "../data/id/equipType.hpp"
#include "../entity/player.hpp"
#include "../scene/dungeonScene.hpp"

const float Inventory::slotSize = 32.f;
const float Inventory::margin = 4.f;
const unsigned int Inventory::fontSize = 16u;

Inventory::Inventory() {
	// main background
	background.setSize(sf::Vector2f((slotSize + margin) * 10.f + margin / 2.f, (slotSize + margin) * 4.f + margin / 2.f + 24.f + 200.f));
	background.setFillColor(sf::Color(0, 0, 0, 191));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 191));

	// inventory slots
	for (size_t i = 0; i < slotBackgrounds.size(); i++) {
		slotBackgrounds[i].setSize(sf::Vector2f(slotSize, slotSize));
		slotBackgrounds[i].setFillColor(sf::Color(0, 0, 0, 255));
		slotBackgrounds[i].setOutlineThickness(1.f);
		slotBackgrounds[i].setOutlineColor(sf::Color(255, 255, 255, 255));

		slotIcons[i].setScale(2.f, 2.f);

		displaySlotIcons[i] = false;

		stackText[i].setFont(*assetManager.LoadFont(settings.Font));
		stackText[i].setCharacterSize(fontSize);
		stackText[i].setOutlineThickness(1.f);

		displayStackText[i] = false;
	}

	// equipment slots
	for (size_t i = 0; i < equipBackgrounds.size(); i++) {
		equipBackgrounds[i].setSize(sf::Vector2f(slotSize, slotSize));
		equipBackgrounds[i].setFillColor(sf::Color(0, 0, 0, 255));
		equipBackgrounds[i].setOutlineThickness(1.f);
		equipBackgrounds[i].setOutlineColor(sf::Color(255, 255, 255, 255));

		equipIcons[i].setScale(2.f, 2.f);

		displayEquipIcons[i] = false;
	}

	// gold text
	goldText.setFont(*assetManager.LoadFont(settings.Font));
	goldText.setCharacterSize(14);
	goldText.setString(std::to_string(gold) + " Gold");

	// stat background
	statBackground.setSize(sf::Vector2f(400.f, background.getSize().y));
	statBackground.setFillColor(sf::Color(0, 0, 0, 191));
	statBackground.setOutlineThickness(1.f);
	statBackground.setOutlineColor(sf::Color(255, 255, 255, 191));

	// stat display button
	statButton.setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/arrow.png"));
	statButton.setTextureRect(sf::IntRect(0, 16, 16, 16));

	// stat text
	statTexts.setFont(*assetManager.LoadFont(settings.Font));
	statTexts.setCharacterSize(12u);
	statTextsCol2.setFont(*assetManager.LoadFont(settings.Font));
	statTextsCol2.setCharacterSize(12u);

	// test
	//Item book;
	//book.Initialize(static_cast<ItemID>(3));
	//AddItem(book);

	//Item bow;
	//bow.Initialize(static_cast<ItemID>(12));
	//AddItem(bow);
	//Item shield;
	//shield.Initialize(static_cast<ItemID>(16));
	//AddItem(shield);

	Item rations;
	rations.Initialize(static_cast<ItemID>(5));
	AddItem(rations);
	AddItem(rations);

	Item book;
	book.Initialize(static_cast<ItemID>(3));
	AddItem(book);

	book.Initialize(static_cast<ItemID>(4));
	AddItem(book);

	ChangeGold(100);

	Initialize();
}

void Inventory::Load(int playerGold, std::array<ItemSave, 40>& items) {
	gold = 0;
	ChangeGold(playerGold); // also sets gold text

	for (size_t i = 0; i < items.size(); i++) {
		inventorySlots[i].StackCount = items[i].StackSize;
		inventorySlots[i].Item = Item(items[i]);
	}
	Initialize();
}

void Inventory::GetInput(sf::RenderWindow& window, sf::Event& ev) {
	sf::Mouse mouse;
	leftClick = false;
	rightClick = false;

	switch (ev.type) {
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left) {
			leftClick = true;
		}
		if (ev.mouseButton.button == sf::Mouse::Right) {
			rightClick = true;
		}
		break;
	default:
		break;
	}

	mousePos = mouse.getPosition(window);
}

bool Inventory::Update(float secondsPerUpdate, DungeonScene& dungeonScene) {
	Player* player = static_cast<Player*>(dungeonScene.GetPlayer());
	sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	displayTooltip = false;

	for (size_t i = 0; i < slotIcons.size(); i++) {
		if (!inventorySlots[i].Item.IsNull() && slotIcons[i].getGlobalBounds().contains(mouseF)) {			
			if (rightClick) {
				// equip item
				if (inventorySlots[i].Item.GetItemType() == ItemType::Equipment) {
					bool equipping = true;
					if (inventorySlots[i].Item.IsTwoHanded()) {
						// Can't equip a two-handed weapon if the user is wearing a shield and there isn't inventory space.
						if (!player->IsEquipmentSlotEmpty(1) && !player->IsEquipmentSlotEmpty(0)) {
							equipping = player->Unequip(*this, 1);
						}
						// Unequip shield if unarmed.
						else if (!player->IsEquipmentSlotEmpty(1)) {
							equipping = player->Unequip(*this, 1);
						}
					}
					if (!player->IsEquipmentSlotEmpty(0) && player->GetEquipment()[0].IsTwoHanded()) {
						// Prevent player from equiping shield if wielding a two-handed weapon.
						if (inventorySlots[i].Item.GetEquipType() == EquipType::Shield) {
							equipping = false;
						}
					}
					if (equipping) { // todo: drag and drop, for rings
						player->Equip(inventorySlots[i]);
					}
					updateItemSlot(i);
				}
				// open learn ability window
				else if (inventorySlots[i].Item.GetItemType() == ItemType::Tome) {
					dungeonScene.OpenLearnAbilityWindow(&inventorySlots[i].Item);
				}
				// use item
				else {
					dungeonScene.SetTargettingMode(inventorySlots[i].Item, i);

				}
			}
			else {
				// show tooltip
				displayTooltip = true;
				tooltip.SetTooltip(inventorySlots[i].Item);
				auto size = tooltip.GetSize();
				tooltip.SetPosition(mouseF.x - size.x, mouseF.y - size.y);
			}
		}
	}

	// Equipment
	for (size_t i = 0; i < equipIcons.size(); i++) {
		if (displayEquipIcons[i] = true && equipIcons[i].getGlobalBounds().contains(mouseF)) {			
			// Unequip Item
			if (rightClick) {
				bool unequipped = player->Unequip(*this, i);
				if (unequipped) {
					displayEquipIcons[i] = false;
				}
			}
			else {
				if (!player->GetEquipment()[i].IsNull()) {
					// show tooltip
					displayTooltip = true;
					tooltip.SetTooltip(player->GetEquipment()[i]);
					auto size = tooltip.GetSize();
					tooltip.SetPosition(mouseF.x - size.x, mouseF.y - size.y);
				}
			}
		}
	}

	// Stat Button
	sf::IntRect buttonRect(0, 16, 16, 16);
	if (displayStats) {
		buttonRect.top = 0;
		updateStats(player);
	}
	if (statButton.getGlobalBounds().contains(mouseF)) {
		buttonRect.left = 16;
		if (leftClick) {
			displayStats = !displayStats;
			leftClick = false;
		}
	}
	statButton.setTextureRect(buttonRect);

	// Probably needs a better way to do this than updating every frame.
	if (player != nullptr) {
		auto& equipment = player->GetEquipment();
		for (size_t i = 0; i < equipment.size(); i++) {
			if (!equipment[i].IsNull()) {
				equipIcons[i].setTexture(*assetManager.LoadTexture(equipment[i].GetIconFilePath()));
				equipIcons[i].setColor(RarityColor::GetColor(equipment[i].GetRarity()));
				displayEquipIcons[i] = true;
			}
			else {
				displayEquipIcons[i] = false;
			}
		}
	}

	leftClick = false;
	rightClick = false;

	return true;
}

void Inventory::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);
	window.draw(goldText);

	for (size_t i = 0; i < slotBackgrounds.size(); i++) {
		window.draw(slotBackgrounds[i]);
		if (displaySlotIcons[i]) {
			window.draw(slotIcons[i]);
			if (displayStackText[i]) {
				window.draw(stackText[i]);
			}
		}
	}

	for (size_t i = 0; i < equipBackgrounds.size(); i++) {
		window.draw(equipBackgrounds[i]);
		if (displayEquipIcons[i]) {
			window.draw(equipIcons[i]);
		}
	}

	// stats
	window.draw(statButton);
	if (displayStats) {
		window.draw(statBackground);
		window.draw(statTexts);
		window.draw(statTextsCol2);
	}

	if (displayTooltip) {
		tooltip.Draw(window, timeRatio);
	}
}

void Inventory::Initialize() {
	sf::Vector2f pos(0.f, 0.f);
	pos.x = static_cast<float>(settings.ScreenWidth) - background.getSize().x - 40.f;
	pos.y = static_cast<float>(settings.ScreenHeight) / 2.f - (background.getSize().y / 2.f) - 20.f;
	background.setPosition(pos);

	for (size_t i = 0; i < slotBackgrounds.size(); i++) {
		slotBackgrounds[i].setPosition(pos.x + (margin / 2.f + 1.f) + (i % 10) * (slotSize + margin), pos.y + 200.f + (margin / 2.f + 1.f) + (i / 10) * (slotSize + margin));
		slotIcons[i].setPosition(slotBackgrounds[i].getPosition());
		stackText[i].setPosition(slotBackgrounds[i].getPosition().x + 1.f, slotBackgrounds[i].getPosition().y - 1.f);
		displaySlotIcons[i] = false;
		displayStackText[i] = false;

		if (!inventorySlots[i].Item.IsNull()) {
			slotIcons[i].setTexture(*assetManager.LoadTexture(inventorySlots[i].Item.GetIconFilePath()));
			slotIcons[i].setColor(RarityColor::GetColor(inventorySlots[i].Item.GetRarity()));
			displaySlotIcons[i] = true;
			if (inventorySlots[i].StackCount > 1) {
				stackText[i].setString(std::to_string(inventorySlots[i].StackCount));
				displayStackText[i] = true;
			}
		}
	}

	// Equipment Slots and Icons
	// Set one-by-one has index doesn't match the order they're placed.

	// Main-Hand
	equipBackgrounds[0].setPosition(pos.x + (background.getSize().x / 2.f) - 15.f - slotSize, pos.y + 160.f);
	equipIcons[0].setPosition(pos.x + (background.getSize().x / 2.f) - 15.f - slotSize, pos.y + 160.f);

	// Off-Hand
	equipBackgrounds[1].setPosition(pos.x + (background.getSize().x / 2.f) + 15.f, pos.y + 160.f);
	equipIcons[1].setPosition(pos.x + (background.getSize().x / 2.f) + 15.f, pos.y + 160.f);

	// Helm
	equipBackgrounds[2].setPosition(pos.x + 70.f, pos.y + 10.f);
	equipIcons[2].setPosition(pos.x + 70.f, pos.y + 10.f);

	// Body
	equipBackgrounds[3].setPosition(pos.x + 70.f, pos.y + 55.f);
	equipIcons[3].setPosition(pos.x + 70.f, pos.y + 55.f);

	// Hands
	equipBackgrounds[4].setPosition(pos.x + 70.f, pos.y + 100.f);
	equipIcons[4].setPosition(pos.x + 70.f, pos.y + 100.f);

	// Feet
	equipBackgrounds[5].setPosition(pos.x + 70.f, pos.y + 145.f);
	equipIcons[5].setPosition(pos.x + 70.f, pos.y + 145.f);

	// Neck
	equipBackgrounds[6].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 10.f);
	equipIcons[6].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 10.f);

	// Ring 1
	equipBackgrounds[7].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 55.f);
	equipIcons[7].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 55.f);

	// Ring 2
	equipBackgrounds[8].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 100.f);
	equipIcons[8].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 100.f);

	// Light Source
	equipBackgrounds[9].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 145.f);
	equipIcons[9].setPosition(pos.x + background.getSize().x - 70.f - slotSize, pos.y + 145.f);

	goldText.setOrigin(goldText.getLocalBounds().left, goldText.getLocalBounds().top);
	goldText.setPosition(std::round(pos.x + margin), std::round(pos.y + 7.f + 200.f + (slotSize + margin) * 4));

	// Stat Sheet Button
	statButton.setPosition(pos.x + 8.f, pos.y + 8.f);

	// Stats
	statBackground.setPosition(pos.x - statBackground.getSize().x - 3.f, pos.y);
	auto statPos = statBackground.getPosition();
	statTexts.setPosition(statPos.x + 2.f, statPos.y + 2.f);
	statTextsCol2.setPosition(statPos.x + 202.f, statPos.y + 2.f);
}

int Inventory::GetGold() {
	return gold;
}

std::array<InventorySlot, 40>& Inventory::GetInventory() {
	return inventorySlots;
}

void Inventory::ChangeGold(int amount) {
	gold += amount;
	gold = std::max(0, gold);
	goldText.setString(std::to_string(gold) + " Gold");
}

bool Inventory::AddItem(Item& item) {
	// Check if there are any existing items with stack space first.
	if (item.GetItemType() != ItemType::Equipment) {
		for (size_t i = 0; i < inventorySlots.size(); i++) {
			if (inventorySlots[i].Item.GetItemID() == item.GetItemID() && inventorySlots[i].StackCount < item.GetMaxStackSize()) {
				inventorySlots[i].StackCount++;
				updateItemSlot(i);
				return true;
			}
		}
	}

	// Check for empty inventory slots.
	for (size_t i = 0; i < inventorySlots.size(); i++) {
		if (inventorySlots[i].Item.IsNull()) {
			inventorySlots[i].Item = item;
			inventorySlots[i].StackCount = 1;
			updateItemSlot(i);
			return true;
		}
	}

	return false;
}

void Inventory::ConsumeItem(size_t index) {
	// todo: rods
	inventorySlots[index].StackCount--;
	if (inventorySlots[index].StackCount == 0) {
		inventorySlots[index].Item = Item();
	}
	updateItemSlot(index);
}

Item* Inventory::GetItem(size_t index) {
	if (!inventorySlots[index].Item.IsNull()) {
		return &inventorySlots[index].Item;
	}
	return nullptr;
}

void Inventory::GetDraggableItem(DungeonScene& dungeonScene, sf::Vector2i position, ItemID& id, Item& item, int& stackCount) {
	sf::Vector2f posF(static_cast<float>(position.x), static_cast<float>(position.y));
	for (size_t i = 0; i < inventorySlots.size(); i++) {
		if (!inventorySlots[i].Item.IsNull() && slotBackgrounds[i].getGlobalBounds().contains(posF)) {
			id = inventorySlots[i].Item.GetItemID();
			stackCount = inventorySlots[i].StackCount;
			inventorySlots[i].StackCount = 0;
			item = inventorySlots[i].Item;
			inventorySlots[i].Item = Item();
			updateItemSlot(i);
			return;
		}
	}

	Player* player = static_cast<Player*>(dungeonScene.GetPlayer());
	for (size_t i = 0; i < equipBackgrounds.size(); i++) {
		if (displayEquipIcons[i] && equipBackgrounds[i].getGlobalBounds().contains(posF)) {
			item = player->Unequip(i);
			if (!item.IsNull()) {
				id = item.GetItemID();
				stackCount = 1;
			}
			return;
		}
	}

}

void Inventory::ReleaseDraggableItem(DungeonScene& dungeonScene, sf::Vector2i position, Item& item, int& stackCount) {
	sf::Vector2f posF(static_cast<float>(position.x), static_cast<float>(position.y));

	// Inventory Slots
	for (size_t i = 0; i < inventorySlots.size(); i++) {
		if (slotBackgrounds[i].getGlobalBounds().contains(posF)) {
			// Empty Slot
			if (inventorySlots[i].Item.IsNull()) {
				inventorySlots[i].Item = item;
				inventorySlots[i].StackCount = stackCount;
				item = Item();
				updateItemSlot(i);
				return;
			}
			// Contains Same Item
			if (inventorySlots[i].Item.GetItemID() == item.GetItemID()) {
				// Try to merge stacks.
				int freeStacks = inventorySlots[i].Item.GetMaxStackSize() - inventorySlots[i].StackCount;
				if (freeStacks > 0) {
					int addStacks = std::min(stackCount, freeStacks);
					inventorySlots[i].StackCount += addStacks;
					stackCount -= addStacks;
					if (stackCount == 0) {
						item = Item();
						return;
					}
				}
			}
			// Try to add remaining items automatically.
			int cycles = stackCount;
			for (int i = 0; i < cycles; i++) {
				AddItem(item);
				stackCount--;
			}
			return;
		}
	}

	// Equipment
	if (item.GetItemType() == ItemType::Equipment) {
		Player* player = static_cast<Player*>(dungeonScene.GetPlayer());
		for (size_t i = 0; i < equipBackgrounds.size(); i++) {
			if (equipBackgrounds[i].getGlobalBounds().contains(posF)) {
				bool equipping = true;

				if (item.IsTwoHanded() && !player->IsEquipmentSlotEmpty(1)) {
					equipping = false;
				}

				if (!player->IsEquipmentSlotEmpty(0) && player->GetEquipment()[0].IsTwoHanded() && item.GetEquipType() == EquipType::Shield) {
					equipping = false;
				}

				if (equipping) {
					player->Equip(item, i);
				}
				if (!item.IsNull()) {
					if (AddItem(item)) {
						stackCount = 0;
					}
				}
				return;
			}
		}
	}

	// Item released over inventory but not over slot, try and add to inventory.
	if (background.getGlobalBounds().contains(posF)) {
		int cycles = stackCount;
		for (int i = 0; i < cycles; i++) {
			AddItem(item);
			stackCount--;
		}
	}
}

void Inventory::updateItemSlot(size_t index) {
	if (!inventorySlots[index].Item.IsNull()) {
		slotIcons[index].setTexture(*assetManager.LoadTexture(inventorySlots[index].Item.GetIconFilePath()));
		slotIcons[index].setColor(RarityColor::GetColor(inventorySlots[index].Item.GetRarity()));
		displaySlotIcons[index] = true;
		if (inventorySlots[index].StackCount > 1) {
			stackText[index].setString(std::to_string(inventorySlots[index].StackCount));
			displayStackText[index] = true;
		}
		else {
			displayStackText[index] = false;
		}
	}
	else {
		displaySlotIcons[index] = false;
		displayStackText[index] = false;
	}
}

void Inventory::updateStats(Player* player) {
	std::string stat;
	std::vector<std::string> stats;
	std::string statText;
	int valueOfStat = 0;
	std::string statValue;
	size_t charCount = 0;
	const size_t maxChars = 24;

	auto formatString = [&](std::string statName, std::string statValue) {
		std::string result;

		size_t spaces = maxChars - statName.size() - statValue.size();

		if (statName.size() + statValue.size() > maxChars) {
			spaces = 1;
		}

		result = "#aaaaaa " + statName + "#default ";
		for (size_t i = 0; i < spaces; i++) {
			result += " ";
		}
		result += statValue;

		return result;
	};

	EventOptions eventOptions;

	// Level
	statText = "Level";
	statValue = std::to_string(player->GetLevel());
	stats.push_back(formatString(statText, statValue));

	// EXP
	statText = "EXP";
	statValue = std::to_string(player->GetCurrentEXP()) + "/" + std::to_string(player->GetNextLevelEXP());
	stats.push_back(formatString(statText, statValue));

	// HP
	statText = "HP";
	statValue = std::to_string(player->GetCurrentHP()) + "/" + std::to_string(player->GetMaxHP());
	stats.push_back(formatString(statText, statValue));

	// MP
	statText = "MP";
	statValue = std::to_string(player->GetCurrentMP()) + "/" + std::to_string(player->GetMaxMP());
	stats.push_back(formatString(statText, statValue));

	// SP
	statText = "SP";
	statValue = std::to_string(player->GetCurrentSP()) + "/" + std::to_string(player->GetMaxSP());
	stats.push_back(formatString(statText, statValue));

	stats.push_back("");

	// Strength
	statText = "Strength";
	statValue = std::to_string(player->GetSTR());
	stats.push_back(formatString(statText, statValue));

	// Dexterity
	statText = "Dexterity";
	statValue = std::to_string(player->GetDEX());
	stats.push_back(formatString(statText, statValue));

	// Magic
	statText = "Magic";
	statValue = std::to_string(player->GetMAG());
	stats.push_back(formatString(statText, statValue));

	// Vitality
	statText = "Vitality";
	statValue = std::to_string(player->GetVIT());
	stats.push_back(formatString(statText, statValue));

	// Spirit
	statText = "Spirit";
	statValue = std::to_string(player->GetSPI());
	stats.push_back(formatString(statText, statValue));

	stats.push_back("");

	// Armor
	statText = "Armor";
	statValue = std::to_string(player->GetArmor(false));
	stats.push_back(formatString(statText, statValue));

	// Spell Defense
	statText = "Spell Defense";
	statValue = std::to_string(player->GetMagicArmor(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	// Evasion
	statText = "Evasion";
	statValue = std::to_string(player->GetEvasion(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	stats.push_back("");

	// Arcane Resistance
	statText = "Arcane Resistance";
	eventOptions.Elements = { Element::Arcane };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Fire Resistance
	statText = "Fire Resistance";
	eventOptions.Elements = { Element::Fire };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Ice Resistance
	statText = "Ice Resistance";
	eventOptions.Elements = { Element::Ice };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Lightning Resistance
	statText = "Lightning Resistance";
	eventOptions.Elements = { Element::Lightning };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Water Resistance
	statText = "Water Resistance";
	eventOptions.Elements = { Element::Water };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Poison Resistance
	statText = "Poison Resistance";
	eventOptions.Elements = { Element::Poison };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Light Resistance
	statText = "Light Resistance";
	eventOptions.Elements = { Element::Light };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Dark Resistance
	statText = "Dark Resistance";
	eventOptions.Elements = { Element::Dark };
	valueOfStat = player->GetResistance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "%";
	stats.push_back(formatString(statText, statValue));

	eventOptions.Elements = {};

	for (auto& s : stats) {
		stat += s + "\n";
	}

	statTexts.setString(stat);

	// 2nd Column
	stat = "";
	stats.clear();

	// Attack Power
	statText = "Attack Power";
	statValue = std::to_string(player->GetAttackPower(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	// Spell Power
	statText = "Spell Power";
	statValue = std::to_string(player->GetSpellPower(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	// Accuracy
	statText = "Accuracy";
	statValue = std::to_string(player->GetAccuracy(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	stats.push_back("");

	// Critical Strike Chance
	statText = "Crit Chance";
	valueOfStat = player->GetCritChance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "." + std::to_string(valueOfStat % 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Critical Strike Power
	statText = "Crit Power";
	valueOfStat = player->GetCritPower(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "." + std::to_string(valueOfStat % 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Double Strike Chance
	statText = "Double Strike";
	valueOfStat = player->GetDoubleStrikeChance(eventOptions, false);
	statValue = std::to_string(valueOfStat / 10) + "." + std::to_string(valueOfStat % 10) + "%";
	stats.push_back(formatString(statText, statValue));

	// Haste
	statText = "Haste";
	valueOfStat = player->GetHaste(eventOptions, false) - 1000;
	statValue = std::to_string(valueOfStat / 10) + "." + std::to_string(valueOfStat % 10) + "%";
	stats.push_back(formatString(statText, statValue));

	stats.push_back(""); // blank line

	// HP on Kill
	statText = "HP on Kill";
	statValue = std::to_string(player->GetHPOnKill(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	// MP on Kill
	statText = "MP on Kill";
	statValue = std::to_string(player->GetMPOnKill(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	// SP on Kill
	statText = "SP on Kill";
	statValue = std::to_string(player->GetSPOnKill(eventOptions, false));
	stats.push_back(formatString(statText, statValue));

	for (auto& s : stats) {
		stat += s + "\n";
	}

	statTextsCol2.setString(stat);

}