// ================================================================
//
// spellbook.cpp
//
// ================================================================

#include "spellbook.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/ability.hpp"
#include "../entity/actor.hpp"

Spellbook::Spellbook() {
	// background
	background.setSize(sf::Vector2f(200.f, 400.f));
	background.setFillColor(sf::Color(0, 0, 0, 191));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 191));

	// page buttons
	previousPageButton.setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/arrow.png"));
	previousPageButton.setTextureRect(sf::IntRect(0, 16, 16, 16));

	nextPageButton.setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/arrow.png"));
	nextPageButton.setTextureRect(sf::IntRect(0, 0, 16, 16));

	// page text
	pageText.setFont(*assetManager.LoadFont(settings.Font));
	pageText.setCharacterSize(fontSize);
	pageText.setString("Page 1/1");

	Initialize();
}

void Spellbook::GetInput(sf::RenderWindow& window, sf::Event& ev) {
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

void Spellbook::Update(float secondsPerUpdate, Actor* player) {
	sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	displayTooltip = false;

	// set icons
	abilityIcons.clear();
	abilityText.clear();
	abilityBackgrounds.clear();
	abilityIDs.clear();

	std::vector<Ability>* abilities = player->GetAbilities();
	size_t abilitiesSize = abilities->size();
	//abilityIcons.reserve(abilitiesSize);
	//abilityText.reserve(abilitiesSize);
	//abilityBackgrounds.reserve(abilitiesSize);
	//abilityIDs.reserve(abilitiesSize);

	// for (size_t i = 0; i < abilitiesSize; i++)
	for (size_t i = currentPage * 8; i < abilitiesSize && i < (currentPage + 1) * 8; i++) {
		Ability* ab = &abilities->at(i);
		sf::RectangleShape b;
		b.setSize(sf::Vector2f(iconSize, iconSize));
		b.setFillColor(sf::Color(0, 0, 0, 255));
		b.setOutlineThickness(1.f);
		b.setOutlineColor(sf::Color(255, 255, 255, 255));
		
		sf::Sprite s;
		s.setScale(2.f, 2.f);
		s.setTexture(*assetManager.LoadTexture(ab->GetIcon()));

		sfe::RichText t;
		t.setFont(*assetManager.LoadFont(settings.Font));
		t.setCharacterSize(fontSize);
		t.setString(ab->GetName() + "\nRank: " + std::to_string(ab->GetCurrentRank() + 1) + "/" + std::to_string(ab->GetMaxRank() + 1));

		abilityBackgrounds.push_back(b);
		abilityIcons.push_back(s);
		abilityText.push_back(t);
		abilityIDs.push_back(ab->GetAbilityID());
	}

	// page buttons and text
	maxPage = abilitiesSize / 8;

	if (currentPage > 0) {
		displayPreviousPageButton = true;
		if (previousPageButton.getGlobalBounds().contains(mouseF)) {
			if (leftClick) {
				currentPage--;
			}
			previousPageButton.setTextureRect(sf::IntRect(16, 16, 16, 16));
		}
		else {
			previousPageButton.setTextureRect(sf::IntRect(0, 16, 16, 16));
		}
	}
	else {
		displayPreviousPageButton = false;
	}

	if (currentPage < maxPage) {
		displayNextPageButton = true;
		if (nextPageButton.getGlobalBounds().contains(mouseF)) {
			if (leftClick) {
				currentPage++;
			}
			nextPageButton.setTextureRect(sf::IntRect(16, 0, 16, 16));
		}
		else {
			nextPageButton.setTextureRect(sf::IntRect(0, 0, 16, 16));
		}
	}
	else {
		displayNextPageButton = false;
	}

	pageText.setString("Page " + std::to_string(currentPage + 1) + "/" + std::to_string(maxPage + 1));

	// must set positions before tooltip
	Initialize();

	// tooltip
	for (size_t i = 0; i < abilityBackgrounds.size(); i++) {
		if (abilityBackgrounds[i].getGlobalBounds().contains(mouseF)) {
			tooltip.SetTooltip(player, abilities->at(i + currentPage * 8));
			auto size = tooltip.GetSize();
			tooltip.SetPosition(mouseF.x, mouseF.y - size.y);
			displayTooltip = true;
			break;
		}
	}

	leftClick = false;
	rightClick = false;
}

void Spellbook::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);

	for (auto& abb : abilityBackgrounds) {
		window.draw(abb);
	}

	for (auto& abi : abilityIcons) {
		window.draw(abi);
	}

	for (auto& abt : abilityText) {
		window.draw(abt);
	}

	window.draw(pageText);

	if (displayPreviousPageButton) {
		window.draw(previousPageButton);
	}

	if (displayNextPageButton) {
		window.draw(nextPageButton);
	}

	if (displayTooltip) {
		tooltip.Draw(window, timeRatio);
	}
	
}

void Spellbook::Initialize() {
	sf::Vector2f pos(20.f, static_cast<float>(settings.ScreenHeight) / 2.f - background.getSize().y / 2.f);
	background.setPosition(pos);

	for (size_t i = 0; i < abilityIcons.size(); i++) {
		float iFloat = static_cast<float>(i);
		abilityIcons[i].setPosition(pos.x + 5.f, pos.y + 5.f + (iFloat * (iconSize + 6.f)));
		abilityBackgrounds[i].setPosition(pos.x + 5.f, pos.y + 5.f + (iFloat * (iconSize + 6.f)));
		abilityText[i].setPosition(pos.x + iconSize + 10.f, pos.y + 10.f + (iFloat * (iconSize + 6.f)));
	}

	previousPageButton.setPosition(pos.x + background.getSize().x / 2.f - 50.f - 16.f, pos.y + background.getSize().y - 24.f);
	nextPageButton.setPosition(pos.x + background.getSize().x / 2.f + 50.f, pos.y + background.getSize().y - 24.f);
	pageText.setPosition(pos.x + background.getSize().x / 2.f - std::ceilf(pageText.getLocalBounds().width / 2.f), pos.y + background.getSize().y - 24.f);
}

void Spellbook::GetDraggableAbility(sf::Vector2i location, AbilityID& id) {
	for (size_t i = 0; i < abilityBackgrounds.size(); i++) {
		if (abilityBackgrounds[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(location))) {
			id = abilityIDs[i];
			return;
		}
	}
}