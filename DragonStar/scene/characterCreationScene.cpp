// ================================================================
//
// characterCreationScene.cpp
//
// ================================================================

#include "characterCreationScene.hpp"

#include "../core/assetManager.hpp"
#include "../core/gameState.hpp"
#include "../core/settings.hpp"
#include "../data/id/raceID.hpp"
#include "../data/id/starterID.hpp"
#include "../entity/player.hpp"

CharacterCreationScene::CharacterCreationScene() {
	headerText.setString("Character Creation");
	headerText.setCharacterSize(28u);
	headerText.setFillColor(sf::Color(255, 255, 255, 255));
	headerText.setFont(*assetManager.LoadFont(settings.Font));

	nameText.setString("Name");
	nameText.setCharacterSize(14u);
	nameText.setFillColor(sf::Color(255, 255, 255, 255));
	nameText.setFont(*assetManager.LoadFont(settings.Font));

	nameTextBox.SetString("Enter Name Here");

	raceDropdown.AddOption("Human", RaceID::Human);
	raceDropdown.AddOption("Elf", RaceID::Elf);
	raceDropdown.AddOption("Shadow Elf", RaceID::ShadowElf);
	raceDropdown.AddOption("Stone Dwarf", RaceID::StoneDwarf);
	raceDropdown.AddOption("Draconian", RaceID::Draconian);
	raceDropdown.AddOption("Vulpine", RaceID::Vulpine);
	raceDropdown.AddOption("Anubian", RaceID::Anubian);
	raceDropdown.AddOption("Runetouched", RaceID::Runetouched);

	starterDropdown.AddOption("Warrior", StarterID::Warrior);
	starterDropdown.AddOption("Archer", StarterID::Archer);
	starterDropdown.AddOption("Sorcerer", StarterID::Sorcerer);
	starterDropdown.AddOption("Priest", StarterID::Priest);
	starterDropdown.AddOption("Merchant", StarterID::Merchant);

	raceStatText.setCharacterSize(14u);
	raceStatText.setFont(*assetManager.LoadFont(settings.Font));

	startGameButton.SetString("Start Game");
}

void CharacterCreationScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;
	sf::Mouse mouse;

	mousePos = mouse.getPosition(window);

	leftClick = false;
	scrollUp = false;
	scrollDown = false;

	while (window.pollEvent(ev)) {
		nameTextBox.GetInput(window, ev);
		
		switch (ev.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				dragging = true;
				leftClick = false;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftClick = true;
				dragging = false;
			}
			break;
		case sf::Event::MouseWheelScrolled:
			if (ev.mouseWheelScroll.delta == 1) {
				scrollUp = true;
			}
			if (ev.mouseWheelScroll.delta == -1) {
				scrollDown = true;
			}
			break;
		}
	}
}

GameState CharacterCreationScene::Update(float secondsPerUpdate) {
	GameState gs = GameState::CharacterCreation;
	bool dragUpdate = false;

	if (dragging) {
		dragTime += secondsPerUpdate;
		if (dragTime > 0.05f) {
			dragUpdate = true;
		}
	}
	else {
		dragTime = 0.f;
		dragUpdate = false;
	}

	if (!isDropdownOpen) {
		if (startGameButton.Update(secondsPerUpdate, mousePos) && leftClick) {
			gs = GameState::Dungeon;
		}

		nameTextBox.Update(secondsPerUpdate);
	}

	if (!isDropdownOpen || isRaceDropdownOpen) {
		isRaceDropdownOpen = raceDropdown.Update(secondsPerUpdate, mousePos, leftClick, scrollUp, scrollDown, dragUpdate);
		isDropdownOpen = isRaceDropdownOpen;
	}

	if (!isDropdownOpen || isStarterDropdownOpen) {
		isStarterDropdownOpen = starterDropdown.Update(secondsPerUpdate, mousePos, leftClick, scrollUp, scrollDown, dragUpdate);
		isDropdownOpen = isStarterDropdownOpen;
	}

	setRaceStatText();

	return gs;
}

void CharacterCreationScene::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(headerText);
	window.draw(nameText);
	nameTextBox.Draw(window, timeRatio);

	window.draw(raceStatText);

	raceDropdown.Draw(window);
	starterDropdown.Draw(window);

	startGameButton.Render(window);
}

void CharacterCreationScene::InitializePositions() {
	setRaceStatText();
	
	sf::Vector2f pos;
	pos.x = std::roundf(static_cast<float>(settings.ScreenWidth) / 2.f - headerText.getLocalBounds().width / 2.f);
	pos.y = std::roundf(static_cast<float>(settings.ScreenHeight) / 12.f);
	headerText.setPosition(pos);

	pos.x = std::roundf(static_cast<float>(settings.ScreenWidth) / 2.f - nameText.getLocalBounds().width / 2.f);
	pos.y = std::roundf(static_cast<float>(settings.ScreenHeight) * 5.f / 18.f);
	nameText.setPosition(pos);

	nameTextBox.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight * 6 / 18);

	raceDropdown.SetPosition(settings.ScreenWidth / 3, settings.ScreenHeight * 7 / 18);

	pos.x = std::roundf(static_cast<float>(settings.ScreenWidth) / 3.f - raceStatText.getLocalBounds().width / 2.f);
	pos.y = std::roundf(static_cast<float>(settings.ScreenHeight) * 7.5f / 18.f);
	raceStatText.setPosition(pos);

	starterDropdown.SetPosition(settings.ScreenWidth * 2 / 3, settings.ScreenHeight * 7 / 18);

	startGameButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight * 7 / 8);
}

std::string CharacterCreationScene::GetPlayerName() {
	return nameTextBox.GetString();
}

RaceID CharacterCreationScene::GetPlayerRace() {
	return raceDropdown.GetSelectedValue();
}

StarterID CharacterCreationScene::GetPlayerStarter() {
	return starterDropdown.GetSelectedValue();
}

void CharacterCreationScene::setRaceStatText() {
	RaceID race = raceDropdown.GetSelectedValue();
	Player player("Unnamed", race);

	std::string s;
	std::string t;

	// HP
	s = "#aaaaaa HP #default     ";
	t = std::to_string(player.GetMaxHP());
	if (t.size() < 3) {
		s += " ";
	}
	s += t + "\n";

	// MP
	s += "#aaaaaa MP #default     ";
	t = std::to_string(player.GetMaxMP());
	if (t.size() < 3) {
		s += " ";
	}
	s += t + "\n";

	// SP
	s += "#aaaaaa SP #default     ";
	t = std::to_string(player.GetMaxSP());
	if (t.size() < 3) {
		s += " ";
	}
	s += t + "\n";

	s += "\n";

	// STR
	s += "#aaaaaa STR #default     ";
	t = std::to_string(player.GetSTR());
	if (t.size() < 2) {
		s += " ";
	}
	s += t + "\n";

	// DEX
	s += "#aaaaaa DEX #default     ";
	t = std::to_string(player.GetDEX());
	if (t.size() < 2) {
		s += " ";
	}
	s += t + "\n";

	// MAG
	s += "#aaaaaa MAG #default     ";
	t = std::to_string(player.GetMAG());
	if (t.size() < 2) {
		s += " ";
	}
	s += t + "\n";

	// VIT
	s += "#aaaaaa VIT #default     ";
	t = std::to_string(player.GetVIT());
	if (t.size() < 2) {
		s += " ";
	}
	s += t + "\n";

	// SPI
	s += "#aaaaaa SPI #default     ";
	t = std::to_string(player.GetSPI());
	if (t.size() < 2) {
		s += " ";
	}
	s += t + "\n";

	raceStatText.setString(s);
}