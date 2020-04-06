// ================================================================
//
// game.hpp
// 
// Handles the core game loop and window management.
//
// ================================================================

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "camera.hpp"
#include "gameState.hpp"
#include "../scene/defeatScene.hpp"
#include "../scene/dungeonScene.hpp"
#include "../scene/mainMenuScene.hpp"
#include "../scene/victoryScene.hpp"
#include "../ui/fpsWindow.hpp"

class Game {
public:
	Game();

	// Runs the game.
	void Run();

private:
	void processInput();
	void update(float secondsPerUpdate);
	void draw(float timeRatio);

	// ------------------------
	sf::RenderWindow window;

	Camera camera;
	sf::View uiView;

	FPSWindow fpsWindow;

	GameState gameState;
	MainMenuScene mainMenuScene;
	DungeonScene dungeonScene;
	VictoryScene victoryScene;
	DefeatScene defeatScene;
};