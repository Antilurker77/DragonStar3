// ================================================================
//
// game.cpp
//
// ================================================================

#include "game.hpp"

#include "settings.hpp"
#include "random.hpp"

// Frames Per Second
const sf::Time timePerUpdate = sf::seconds(1.f / 60.f);

// Game Title
const std::string gameTitle = "Dragon Star v0.3.1";

Game::Game() :
	window(sf::VideoMode(settings.ScreenWidth, settings.ScreenHeight), gameTitle),
	camera(sf::Vector2f(0, 0), sf::Vector2f(static_cast<float>(settings.ScreenWidth), static_cast<float>(settings.ScreenHeight))),
	uiView(sf::Vector2f(static_cast<float>(settings.ScreenWidth) / 2.f, static_cast<float>(settings.ScreenHeight) / 2.f), sf::Vector2f(static_cast<float>(settings.ScreenWidth), static_cast<float>(settings.ScreenHeight)))
{
	// Fullscreen
	if (settings.EnableFullscreen) {
		window.create(sf::VideoMode(settings.ScreenWidth, settings.ScreenHeight), gameTitle, sf::Style::Fullscreen);
	}

	// VSync
	window.setVerticalSyncEnabled(settings.EnableVSync);

	gameState = GameState::MainMenu;

	mainMenuScene.SetPositions();
	dungeonScene.SetCamera(&camera);
}

void Game::Run() {
	sf::Clock clock;
	sf::Time timeSinceUpdate = sf::Time::Zero;
	float timeRatio = 0.f;
	float secondsPerUpdate = timePerUpdate.asSeconds();

	while (window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceUpdate += elapsedTime;
		timeRatio = 0.f;

		while (timeSinceUpdate > timePerUpdate) {
			timeSinceUpdate -= timePerUpdate;
			processInput();
			update(secondsPerUpdate);
		}

		timeRatio = timeSinceUpdate.asSeconds() / timePerUpdate.asSeconds();
		draw(timeRatio);
		fpsWindow.Update(elapsedTime);
	}
}

void Game::processInput() {
	//dungeonScene.ReadInput(window);

	switch (gameState) {
		case GameState::MainMenu:
			mainMenuScene.ReadInput(window);
			break;
		case GameState::Dungeon:
			dungeonScene.ReadInput(window);
			break;
		default:
			break;
	}
}

void Game::update(float secondsPerUpdate) {
	//dungeonScene.Update(secondsPerUpdate);
	
	switch (gameState) {
		case GameState::MainMenu:
			gameState = mainMenuScene.Update(secondsPerUpdate, window);

			// Transition from Main Menu to Dungeon, load game.
			if (gameState == GameState::Dungeon) {
				dungeonScene.LoadGame();
				dungeonScene.SetCamera(&camera);
			}

			break;
		case GameState::CharacterCreation:
			gameState = GameState::Dungeon; // todo: character creation
			// Transition from Character Creation to Dungeon, generate dungeon.
			if (gameState == GameState::Dungeon) {
				dungeonScene.GenerateSeeds(Random::RandomSeed());
				dungeonScene.SetCamera(&camera);
			}		
			break;
		case GameState::Dungeon:
			gameState = dungeonScene.Update(secondsPerUpdate);
			break;
		default:
			break;
	}

	camera.Update(secondsPerUpdate);
}

void Game::draw(float timeRatio) {
	window.clear();
	
	camera.Interpolate(timeRatio);
	window.setView(camera.GetCamera());

	switch (gameState) {
		case GameState::Dungeon:
			dungeonScene.DrawWorld(window, timeRatio);
			break;
		default:
			break;
	}

	// UI
	window.setView(uiView);

	switch (gameState) {
		case GameState::MainMenu:
			mainMenuScene.Draw(window, timeRatio);
			break;
		case GameState::Dungeon:
			dungeonScene.DrawUI(window, timeRatio);
			break;
		default:
			break;
	}

	fpsWindow.Draw(window);

	window.display();
}