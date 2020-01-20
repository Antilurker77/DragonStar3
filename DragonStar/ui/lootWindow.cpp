// ================================================================
//
// lootWindow.cpp
//
// ================================================================

#include "lootWindow.hpp"

#include <iostream>
#include "inventory.hpp"
#include "rarityColor.hpp"
#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/id/rarity.hpp"

LootWindow::LootWindow() {
	// background
	background.setFillColor(sf::Color(0, 0, 0, 191));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 191));

	// gold text
	goldText.setFont(*assetManager.LoadFont(settings.Font));
	goldText.setCharacterSize(fontSize);

	// gold highlight
	goldTextHighlight.setFillColor(sf::Color(128, 128, 128, 191));

	// gold icon
	goldIcon.setTexture(*assetManager.LoadTexture("gfx/icon/item/gold.png"));
	goldIcon.setColor(sf::Color(240, 210, 20, 255));
}

void LootWindow::GetInput(sf::RenderWindow& window, sf::Event& ev) {
	sf::Mouse mouse;
	mousePos = mouse.getPosition(window);
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
			if (ev.key.code == sf::Keyboard::G) {
				wantToClose = true;
			}
			// Player Moves
			if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Numpad8) {
				wantToClose = true;
			}
			if (ev.key.code == sf::Keyboard::A || ev.key.code == sf::Keyboard::Numpad4) {
				wantToClose = true;
			}
			if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Numpad2) {
				wantToClose = true;
			}
			if (ev.key.code == sf::Keyboard::D || ev.key.code == sf::Keyboard::Numpad6) {
				wantToClose = true;
			}
			if (ev.key.code == sf::Keyboard::Q || ev.key.code == sf::Keyboard::Numpad7) {
				wantToClose = true;
			}
			if (ev.key.code == sf::Keyboard::E || ev.key.code == sf::Keyboard::Numpad9) {
				wantToClose = true;
			}
			if (ev.key.code == sf::Keyboard::C || ev.key.code == sf::Keyboard::Numpad3) {
				wantToClose = true;
			}
			if (ev.key.code == sf::Keyboard::Z || ev.key.code == sf::Keyboard::Numpad1) {
				wantToClose = true;
			}
			break;
		default:
			break;
	}
}

bool LootWindow::Update(float secondsPerUpdate, Inventory& inventory) {
	drawGoldTextHighlight = false;
	drawItemTextHighlight = false;
	displayTooltip = false;
	sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	
	if (wantToClose) {
		display = false;
		leftClick = false;
		wantToClose = false;
		return display;
	}
	
	if (leftClick && !background.getGlobalBounds().contains(mouseF)) {
		display = false;
		leftClick = false;
		wantToClose = false;
		return display;
	}

	// Loot items.
	if (display) {
		// Highlight display.
		if (hasGold && goldTextHighlight.getGlobalBounds().contains(mouseF)) {
			if (rightClick) {
				lootPile->LootGold(inventory);
				rightClick = false;
				if (lootPile->IsEmpty()) {
					display = false;
				}
				else {
					Initialize(*lootPile);
				}
			}
			else {
				drawGoldTextHighlight = true;
			}
		}
		for (size_t i = 0; i < itemTextHighlight.size(); i++) {
			if (itemTextHighlight[i].getGlobalBounds().contains(mouseF)) {
				if (rightClick) {
					lootPile->LootItem(inventory, i);
					rightClick = false;
					if (lootPile->IsEmpty()) {
						display = false;
					}
					else {
						Initialize(*lootPile);
					}
				}
				else {
					drawItemTextHighlight = true;
					selectedItem = i;
					tooltip.SetTooltip(lootPile->GetItems()[i]);
					auto size = tooltip.GetSize();
					tooltip.SetPosition(mouseF.x, mouseF.y - size.y);
					displayTooltip = true;
				}
				break;
			}
		}
	}

	return display;
}

void LootWindow::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);

	if (drawGoldTextHighlight && hasGold) {
		window.draw(goldTextHighlight);
	}

	if (hasGold) {
		window.draw(goldIcon);
		window.draw(goldText);
	}

	if (drawItemTextHighlight) {
		window.draw(itemTextHighlight[selectedItem]);
	}

	for (auto& t : itemText) {
		window.draw(t);
	}

	for (auto& s : itemIcons) {
		window.draw(s);
	}

	if (displayTooltip) {
		tooltip.Draw(window, timeRatio);
	}
}

void LootWindow::Initialize(Loot& loot) {
	display = true;
	lootPile = &loot;
	hasGold = false;

	// gold text
	if (loot.GetGold() > 0) {
		hasGold = true;
		goldText.setString(std::to_string(loot.GetGold()) + " Gold");
	}

	// item text
	itemText.clear();
	itemTextHighlight.clear();
	itemIcons.clear();

	auto items = loot.GetItems();
	for (auto &item : items) {
		sfe::RichText t;
		std::string name;
		t.setFont(*assetManager.LoadFont(settings.Font));
		t.setCharacterSize(fontSize);

		switch (item.GetRarity()) {
			case Rarity::Magical:
				name += "#magical ";
				break;
			case Rarity::Rare:
				name += "#rare ";
				break;
			case Rarity::FixedArtifact:
				name += "#fixedart ";
				break;
			case Rarity::RandomArtifact:
				name += "#randart ";
				break;
			case Rarity::Item:
				name += "#item ";
				break;
			default:
				break;
		}

		name += item.GetName();
		t.setString(name);

		sf::RectangleShape h;
		h.setFillColor(sf::Color(128, 128, 128, 191));

		sf::Sprite s;
		s.setTexture(*assetManager.LoadTexture(item.GetIconFilePath()));
		s.setColor(RarityColor::GetColor(item.GetRarity()));

		itemText.push_back(t);
		itemTextHighlight.push_back(h);
		itemIcons.push_back(s);
	}

	// set sizes
	float longest = 200.f;
	longest = std::max(goldText.getLocalBounds().width + 29.f, longest);
	for (auto it : itemText) {
		longest = std::max(it.getLocalBounds().width + 29.f, longest);
	}

	sf::Vector2f size;
	size.x = longest;
	size.y = (21.f * (1.f + static_cast<float>(itemText.size()))) + 4.f;
	if (!hasGold) {
		size.y -= 21.f;
	}

	goldTextHighlight.setSize(sf::Vector2f(size.x - 4.f, 14.f + 7.f));

	for (size_t i = 0; i < itemTextHighlight.size(); i++) {
		itemTextHighlight[i].setSize(goldTextHighlight.getSize());
	}

	background.setSize(size);

	// set positions
	sf::Vector2f pos;
	pos.x = std::round(static_cast<float>(settings.ScreenWidth / 2) - background.getSize().x / 2.f);
	pos.y = std::round(static_cast<float>(settings.ScreenHeight / 2) - background.getSize().y / 2.f);
	background.setPosition(pos);

	goldText.setPosition(pos.x + 6.f + 18.f, pos.y + 3.f);
	goldTextHighlight.setPosition(pos.x + 2.f, pos.y + 2.f);
	goldIcon.setPosition(pos.x + 3.f, pos.y + 4.f);

	sf::Vector2f itemPos = pos;
	if (hasGold) {
		itemPos.y += goldTextHighlight.getSize().y;
	}

	for (size_t i = 0; i < itemTextHighlight.size(); i++) {
		itemText[i].setPosition(itemPos.x + 6.f + 18.f, itemPos.y + (i * 21.f) + 3.f);
		itemTextHighlight[i].setPosition(itemPos.x + 2.f, itemPos.y + (i * 21.f) + 2.f);
		itemIcons[i].setPosition(itemPos.x + 3.f, itemPos.y + (i * 21.f) + 4.f);
	}
}