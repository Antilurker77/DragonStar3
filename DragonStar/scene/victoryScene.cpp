// ================================================================
//
// victoryScene.cpp
//
// ================================================================

#include "victoryScene.hpp"

#include "../core/assetManager.hpp"
#include "../core/gameState.hpp"
#include "../core/settings.hpp"

VictoryScene::VictoryScene() {
	victoryText.setString("Congradulations! You have won!");
	victoryText.setCharacterSize(20u);
	victoryText.setFillColor(sf::Color(255, 255, 255, 255));
	victoryText.setFont(*assetManager.LoadFont(settings.Font));

	flavorText.setString("The full version will feature 100 floors of content and hopefully are more satisfying ending.");
	flavorText.setCharacterSize(14u);
	flavorText.setFillColor(sf::Color(255, 255, 255, 255));
	flavorText.setFont(*assetManager.LoadFont(settings.Font));

	mainMenuButton.SetString("Return to Main Menu");
}

void VictoryScene::ReadInput(sf::RenderWindow& window) {
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

GameState VictoryScene::Update(float secondsPerUpdate) {
	GameState gs = GameState::Victory;

	if (mainMenuButton.Update(secondsPerUpdate, mousePos) && leftClick) {
		gs = GameState::MainMenu;
	}

	return gs;
}

void VictoryScene::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(victoryText);
	window.draw(flavorText);
	mainMenuButton.Render(window);
}

void VictoryScene::InitializePositions() {
	sf::Vector2f textPos;
	textPos.x = std::roundf(static_cast<float>(settings.ScreenWidth) / 2.f - victoryText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(static_cast<float>(settings.ScreenHeight) / 3.f);
	victoryText.setPosition(textPos);

	textPos.x = std::roundf(static_cast<float>(settings.ScreenWidth) / 2.f - flavorText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(static_cast<float>(settings.ScreenHeight) / 3.f + 2.f + victoryText.getLocalBounds().height);
	flavorText.setPosition(textPos);

	sf::Vector2i buttonPos;
	buttonPos.x = settings.ScreenWidth / 2;
	buttonPos.y = settings.ScreenHeight * 2 / 3;
	mainMenuButton.SetPosition(buttonPos);
}