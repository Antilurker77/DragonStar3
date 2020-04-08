// ================================================================
//
// characterCreationScene.cpp
//
// ================================================================

#include "characterCreationScene.hpp"

#include "../core/assetManager.hpp"
#include "../core/gameState.hpp"
#include "../core/settings.hpp"

CharacterCreationScene::CharacterCreationScene() {
	headerText.setString("Character Creation");
	headerText.setCharacterSize(28u);
	headerText.setFillColor(sf::Color(255, 255, 255, 255));
	headerText.setFont(*assetManager.LoadFont(settings.Font));

	nameText.setString("Name");
	nameText.setCharacterSize(14u);
	nameText.setFillColor(sf::Color(255, 255, 255, 255));
	nameText.setFont(*assetManager.LoadFont(settings.Font));

	startGameButton.SetString("Start Game");
}

void CharacterCreationScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;
	sf::Mouse mouse;

	mousePos = mouse.getPosition(window);

	leftClick = false;

	while (window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftClick = true;
			}
			break;
		}
	}
}

GameState CharacterCreationScene::Update(float secondsPerUpdate) {
	GameState gs = GameState::CharacterCreation;

	if (startGameButton.Update(secondsPerUpdate, mousePos) && leftClick) {
		gs = GameState::Dungeon;
	}

	return gs;
}

void CharacterCreationScene::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(headerText);
	window.draw(nameText);

	startGameButton.Render(window);
}

void CharacterCreationScene::InitializePositions() {
	sf::Vector2f pos;
	pos.x = std::roundf(static_cast<float>(settings.ScreenWidth) / 2.f - headerText.getLocalBounds().width / 2.f);
	pos.y = std::roundf(static_cast<float>(settings.ScreenHeight) / 8.f);
	headerText.setPosition(pos);

	pos.x = std::roundf(static_cast<float>(settings.ScreenWidth) / 2.f - nameText.getLocalBounds().width / 2.f);
	pos.y = std::roundf(static_cast<float>(settings.ScreenHeight) * 4.f / 9.f);
	nameText.setPosition(pos);

	startGameButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight * 7 / 8);
}