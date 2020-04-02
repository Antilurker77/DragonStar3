// ================================================================
//
// defeatScene.cpp
//
// ================================================================

#include "defeatScene.hpp"

#include "../core/assetManager.hpp"
#include "../core/gameState.hpp"
#include "../core/settings.hpp"

DefeatScene::DefeatScene() {
	diedText.setString("You have died.");
	diedText.setCharacterSize(20u);
	diedText.setFont(*assetManager.LoadFont(settings.Font));
	diedText.setFillColor(sf::Color(255, 255, 255, 255));

	sf::Vector2f textPos;
	textPos.x = std::round(static_cast<float>(settings.ScreenWidth) / 2.f - diedText.getLocalBounds().width / 2.f);
	textPos.y = std::round(static_cast<float>(settings.ScreenHeight) / 3.f);
	diedText.setPosition(textPos);

	mainMenuButton.SetString("Return to Main Menu");
	mainMenuButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight * 2 / 3);
}

void DefeatScene::ReadInput(sf::RenderWindow& window) {
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

GameState DefeatScene::Update(float secondsPerUpdate) {
	GameState gs = GameState::Defeat;

	if (mainMenuButton.Update(secondsPerUpdate, mousePos) && leftClick) {
		gs = GameState::MainMenu;
	}

	return gs;
}

void DefeatScene::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(diedText);
	mainMenuButton.Render(window);
}