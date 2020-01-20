// ================================================================
//
// mainMenuScene.cpp
//
// ================================================================

#include "mainMenuScene.hpp"

#include "../core/assetManager.hpp"
#include "../core/gameState.hpp"
#include "../core/settings.hpp"

MainMenuScene::MainMenuScene() {
	titleText.setString("Dragon Star");
	titleText.setCharacterSize(60);
	titleText.setFont(*assetManager.LoadFont(settings.Font));

	newGameButton.SetString("New Game");
	quitButton.SetString("Quit Game");
}

void MainMenuScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;
	sf::Mouse mouse;

	leftClick = false;
	rightClick = false;
	mousePos = mouse.getPosition(window);

	while (window.pollEvent(ev)) {
		switch (ev.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (ev.mouseButton.button == sf::Mouse::Left) {
					leftClick = true;
				}
				else if (ev.mouseButton.button == sf::Mouse::Right) {
					rightClick = true;
				}
				break;
			default:
				break;
		}
	}

}

GameState MainMenuScene::Update(float secondsPerUpdate, sf::RenderWindow& window) {
	GameState gs = GameState::MainMenu;

	if (newGameButton.Update(secondsPerUpdate, mousePos)) {
		if (leftClick) {
			gs = GameState::Dungeon;
		}
	}

	if (quitButton.Update(secondsPerUpdate, mousePos)) {
		if (leftClick) {
			window.close();
		}
	}

	return gs;
}

void MainMenuScene::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(titleText);
	newGameButton.Render(window);
	quitButton.Render(window);
}

void MainMenuScene::SetPositions() {
	auto titleTextSize = titleText.getLocalBounds();
	sf::Vector2f pos;
	pos.x = settings.ScreenWidth / 2.f - titleTextSize.width / 2.f;
	pos.y = settings.ScreenHeight / 2.f - 200.f;
	titleText.setPosition(pos);

	pos.x = settings.ScreenWidth / 2.f;
	pos.y = settings.ScreenHeight / 2.f + 50.f;
	newGameButton.SetPosition(static_cast<int>(pos.x), static_cast<int>(pos.y));

	pos.x = settings.ScreenWidth / 2.f;
	pos.y = settings.ScreenHeight / 2.f + 100.f;
	quitButton.SetPosition(static_cast<int>(pos.x), static_cast<int>(pos.y));
}