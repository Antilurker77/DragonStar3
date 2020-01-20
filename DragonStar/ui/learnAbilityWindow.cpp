// ================================================================
//
// learnAbilityWindow.cpp
//
// ================================================================

#include "learnAbilityWindow.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/ability.hpp"
#include "../data/item.hpp"
#include "../entity/player.hpp"

#include "messageLog.hpp"

LearnAbilityWindow::LearnAbilityWindow() {
	// background
	background.setFillColor(sf::Color(0, 0, 0, 223));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 223));

	// ability point text
	abilityPointText.setFont(*assetManager.LoadFont(settings.Font));
	abilityPointText.setCharacterSize(12u);
}

void LearnAbilityWindow::GetInput(sf::RenderWindow& window, sf::Event& ev) {
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

	mousePos = static_cast<sf::Vector2f>(mouse.getPosition(window));
}

bool LearnAbilityWindow::Update(float secondsPerUpdate) {
	bool keepOpen = true;
	displayTooltip = false;

	if (leftClick && !background.getGlobalBounds().contains(mousePos)) {
		keepOpen = false;
	}

	for (size_t i = 0; i < abilityIcons.size(); i++) {
		// Tooltip
		if (abilityIcons[i].getGlobalBounds().contains(mousePos)) {
			if (player->GetAbility(spellbook->GetTeachableAbilities()[i]) != nullptr) {
				Ability ab(spellbook->GetTeachableAbilities()[i], player->GetAbility(spellbook->GetTeachableAbilities()[i])->GetCurrentRank());
				tooltip.SetTooltip(nullptr, ab);
			}
			else {
				Ability ab(spellbook->GetTeachableAbilities()[i], 0);
				tooltip.SetTooltip(nullptr, ab);
			}
			displayTooltip = true;
			auto size = tooltip.GetSize();
			tooltip.SetPosition(mousePos.x - size.x, mousePos.y - size.y);
		}
		if (drawPlusIcons[i] && plusIcons[i].getGlobalBounds().contains(mousePos)) {
			plusIcons[i].setTextureRect(sf::IntRect(32, 0, 32, 32));

			if (player->GetAbility(spellbook->GetTeachableAbilities()[i]) != nullptr) {
				Ability ab(spellbook->GetTeachableAbilities()[i], player->GetAbility(spellbook->GetTeachableAbilities()[i])->GetCurrentRank() + 1);
				tooltip.SetTooltip(nullptr, ab);
			}
			else {
				Ability ab(spellbook->GetTeachableAbilities()[i], 0);
				tooltip.SetTooltip(nullptr, ab);
			}		
			auto size = tooltip.GetSize();
			tooltip.SetPosition(mousePos.x - size.x, mousePos.y - size.y);
			displayTooltip = true;

			if (leftClick) {
				AbilityID id = spellbook->GetTeachableAbilities()[i];
				player->LearnAbility(id);
				Initialize(spellbook, player);
			}
		}
		else {
			plusIcons[i].setTextureRect(sf::IntRect(0, 0, 32, 32));
		}
	}

	if (displayTooltip) {
		tooltip.Update(secondsPerUpdate);
	}

	leftClick = false;
	rightClick = false;

	return keepOpen;
}

void LearnAbilityWindow::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);
	window.draw(abilityPointText);

	for (size_t i = 0; i < abilityIcons.size(); i++) {
		window.draw(abilityIcons[i]);
		window.draw(abilityText[i]);
		if (drawPlusIcons[i]) {
			window.draw(plusIcons[i]);
		}
	}

	if (displayTooltip) {
		tooltip.Draw(window, timeRatio);
	}
}

void LearnAbilityWindow::Initialize(Item* sb, Player* p) {
	abilityIcons.clear();
	abilityText.clear();
	plusIcons.clear();
	drawPlusIcons.clear();
	
	spellbook = sb;
	player = p;

	std::vector<AbilityID> bookAbilities = spellbook->GetTeachableAbilities();
	float bookSizeF = static_cast<float>(bookAbilities.size());

	// set background size
	background.setSize(sf::Vector2f(240.f, bookSizeF * 46.f + 8.f + 24.f));
	sf::Vector2f size(background.getSize());
	sf::Vector2f pos(static_cast<float>(settings.ScreenWidth) / 2.f - size.x / 2.f, static_cast<float>(settings.ScreenHeight) / 2.f - size.y / 2.f);
	background.setPosition(pos);

	int abilityPoints = p->GetAbilityPoints();
	if (abilityPoints == 1) {
		abilityPointText.setString("You have 1 ability point.");
	}
	else {
		abilityPointText.setString("You have " + std::to_string(abilityPoints) + " ability points.");
	}
	auto apTextSize = abilityPointText.getLocalBounds();
	abilityPointText.setPosition(std::roundf(pos.x + size.x / 2.f - apTextSize.width / 2.f), pos.y + 6.f);

	abilityIcons.reserve(bookAbilities.size());
	abilityText.reserve(bookAbilities.size());
	plusIcons.reserve(bookAbilities.size());
	drawPlusIcons.reserve(bookAbilities.size());

	float index = 0.f;
	const unsigned int fontSize = 12u;
	for (auto& id : bookAbilities) {
		Ability ab;
		ab.Initialize(id);

		// Icon
		sf::Sprite s;
		s.setTexture(*assetManager.LoadTexture(ab.GetIcon()));
		s.setPosition(pos.x + 5.f, pos.y + 5.f + index * 46.f + 24.f);
		s.setScale(2.f, 2.f);
		abilityIcons.push_back(s);

		// Text
		sf::Text t;
		std::string string;
		string = ab.GetName();
		if (player->GetAbility(id) != nullptr) {
			string += "\nRank: " + std::to_string(player->GetAbility(id)->GetCurrentRank() + 1);
		}
		else {
			string += "\nRank: 0";
		}
		string += "/" + std::to_string(ab.GetMaxRank() + 1);

		t.setString(string);
		t.setCharacterSize(fontSize);
		t.setFont(*assetManager.LoadFont(settings.Font));
		t.setPosition(pos.x + 50.f, pos.y + 10.f + index * 46.f + 24.f);
		abilityText.push_back(t);

		// Plus Button
		sf::Sprite plus;
		plus.setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/plus.png"));
		plus.setTextureRect(sf::IntRect(0, 0, 32, 32));
		plus.setPosition(pos.x + size.x - 37.f, pos.y + 10.f + index * 46.f + 24.f);

		bool drawPlus = false;
		if (player->GetAbilityPoints() > 0) {
			if (player->GetAbility(id) != nullptr && player->GetAbility(id)->GetCurrentRank() < ab.GetMaxRank()) {
				drawPlus = true;
			}
			else if (player->GetAbility(id) == nullptr) {
				drawPlus = true;
			}
		}

		plusIcons.push_back(plus);
		drawPlusIcons.push_back(drawPlus);


		index += 1.f;
	}
}