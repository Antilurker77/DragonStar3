// ================================================================
//
// shopWindow.cpp
//
// ================================================================

#include "shopWindow.hpp"

#include "inventory.hpp"
#include "rarityColor.hpp"
#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/item.hpp"

ShopWindow::ShopWindow() {
	background.setSize(sf::Vector2f(36.f * 8.f + 12.f, 36.f * 3.f + 12.f + 20.f));
	background.setOutlineThickness(1.f);
	background.setFillColor(sf::Color(0, 0, 0, 191));
	background.setOutlineColor(sf::Color(255, 255, 255, 191));

	for (size_t i = 0; i < slotBackgrounds.size(); i++) {
		slotBackgrounds[i].setSize(sf::Vector2f(32.f, 32.f));
		slotBackgrounds[i].setOutlineThickness(1.f);
		slotBackgrounds[i].setFillColor(sf::Color(0, 0, 0, 255));
		slotBackgrounds[i].setOutlineColor(sf::Color(255, 255, 255, 255));
	}

	shopText.setString("Dungeon Shop");
	shopText.setCharacterSize(16);
	shopText.setFont(*assetManager.LoadFont(settings.Font));
}

void ShopWindow::GetInput(sf::RenderWindow& window, sf::Event& ev) {
	sf::Mouse mouse;
	leftClick = false;
	rightClick = false;
	wantToClose = false;

	switch (ev.type) {
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left) {
			leftClick = true;
		}
		if (ev.mouseButton.button == sf::Mouse::Right) {
			rightClick = true;
		}
		break;
	case sf::Event::KeyReleased:
		// Player Loots
		if (ev.key.code == settings.UIKeybinds.Loot) {
			wantToClose = true;
		}
		// Player Moves
		if (ev.key.code == settings.MoveKeybinds.MoveN || ev.key.code == settings.MoveKeybinds.MoveNAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveW || ev.key.code == settings.MoveKeybinds.MoveWAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveS || ev.key.code == settings.MoveKeybinds.MoveSAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveE || ev.key.code == settings.MoveKeybinds.MoveEAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveNW || ev.key.code == settings.MoveKeybinds.MoveNWAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveNE || ev.key.code == settings.MoveKeybinds.MoveNEAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveSE || ev.key.code == settings.MoveKeybinds.MoveSEAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveSW || ev.key.code == settings.MoveKeybinds.MoveSWAlt) {
			wantToClose = true;
		}
		break;
	default:
		break;
	}

	mousePos = mouse.getPosition(window);
}

bool ShopWindow::Update(float secondsPerUpdate, Inventory& inventory) {
	bool keepOpen = true;
	displayTooltip = false;
	sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	if (wantToClose) {
		keepOpen = false;
		leftClick = false;
		wantToClose = false;
		return keepOpen;
	}

	if (leftClick && !background.getGlobalBounds().contains(mouseF)) {
		keepOpen = false;
		leftClick = false;
	}

	// tooltip
	std::array<Item, 24> items = shop->GetInventory();
	for (size_t i = 0; i < slotBackgrounds.size(); i++) {
		if (displayIcons[i] && slotBackgrounds[i].getGlobalBounds().contains(mouseF)) {
			itemTooltip.SetTooltip(items[i], true);
			displayTooltip = true;
			auto size = itemTooltip.GetSize();
			itemTooltip.SetPosition(mouseF.x - size.x, mouseF.y - size.y);

			// Buy item.
			if (rightClick) {
				shop->BuyItem(inventory, i);
				rightClick = false;
				Initialize(*shop);
			}

			break;
		}
	}

	return keepOpen;
}

void ShopWindow::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);
	window.draw(shopText);

	for (size_t i = 0; i < slotBackgrounds.size(); i++) {
		window.draw(slotBackgrounds[i]);
		if (displayIcons[i]) {
			window.draw(itemIcons[i]);
		}
	}

	if (displayTooltip) {
		itemTooltip.Draw(window, timeRatio);
	}
}

void ShopWindow::Initialize(Shop& shop) {
	this->shop = &shop;
	std::array<Item, 24> items = shop.GetInventory();
	
	sf::Vector2f pos;
	pos.x = static_cast<float>(settings.ScreenWidth) / 2.f - background.getSize().x;
	pos.y = static_cast<float>(settings.ScreenHeight) / 2.f - background.getSize().y / 2.f;

	background.setPosition(pos);

	auto textSize = shopText.getLocalBounds();
	sf::Vector2f textPos = pos;
	textPos.x += std::roundf(background.getSize().x / 2.f - textSize.width / 2.f);
	textPos.y += 2.f;
	shopText.setPosition(textPos);

	for (size_t i = 0; i < slotBackgrounds.size(); i++) {
		sf::Vector2f slotPos = pos;
		slotPos.x += static_cast<float>(i % 8) * 36.f + 8.f;
		slotPos.y += static_cast<float>(i / 8) * 36.f + 8.f + 20.f;
		slotBackgrounds[i].setPosition(slotPos);
		itemIcons[i].setPosition(slotPos);
		itemIcons[i].setScale(2.f, 2.f);

		if (!items[i].IsNull()) {
			itemIcons[i].setTexture(*assetManager.LoadTexture(items[i].GetIconFilePath()));
			itemIcons[i].setColor(RarityColor::GetColor(items[i].GetRarity()));
			displayIcons[i] = true;
		}
		else {
			displayIcons[i] = false;
		}
	}
}