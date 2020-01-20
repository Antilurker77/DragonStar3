// ================================================================
//
// fpsWindow.cpp
// 
// ================================================================

#include "fpsWindow.hpp"
#include "../core/assetManager.hpp"
#include "../core/settings.hpp"

FPSWindow::FPSWindow() {
	// text
	fpsText.setFont(*assetManager.LoadFont(settings.Font));
	fpsText.setCharacterSize(fontSize);
	fpsText.setPosition(5.f, 5.f);
	fpsText.setString("FPS: ??????????\nFrame Time: ??????????ms");
	
	// background
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setPosition(2.f, 2.f);
	background.setSize({fpsText.getGlobalBounds().width + 7.f, fpsText.getGlobalBounds().height + 14.f});
}

void FPSWindow::Update(sf::Time& t) {
	fpsUpdateTime += t;
	numberOfFrames += 1.f;

	if (fpsUpdateTime >= sf::seconds(1.f)) {
		fpsText.setString("FPS: " + std::to_string(numberOfFrames) + "\nFrame Time: " + std::to_string(1000.f / numberOfFrames) + "ms");

		numberOfFrames = 0.f;
		fpsUpdateTime -= sf::seconds(1.f);
	}
}

void FPSWindow::Draw(sf::RenderTarget& window) {
	window.draw(background);
	window.draw(fpsText);
}