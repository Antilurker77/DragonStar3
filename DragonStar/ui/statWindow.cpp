// ================================================================
//
// statWindow.cpp
//
// ================================================================

#include "statWindow.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/id/statModType.hpp"
#include "../entity/player.hpp"

StatWindow::StatWindow() {
	// background
	background.setFillColor(sf::Color(0, 0, 0, 223));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 223));
	background.setSize(sf::Vector2f(800.f, 282.f));

	// buttons
	for (auto& b : statButtons) {
		b.setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/plus.png"));
		b.setTextureRect(sf::IntRect(0, 0, 32, 32));
	}

	const unsigned int fontSize = 16u;

	// text
	for (auto& t : statText) {
		t.setCharacterSize(fontSize);
		t.setFont(*assetManager.LoadFont(settings.Font));
	}

	// strength
	statDescriptions[0] = "#aaaaaa Each point increases attack power by 1 and critial strike power by 1%.";

	// dexterity
	statDescriptions[1] = "#aaaaaa Each point increases accuracy by 1 and critical strike chance by 0.2%.";

	// magic
	statDescriptions[2] = "#aaaaaa Each point increases spell power by 1 and spell defense by 1.";

	// vitality
	statDescriptions[3] = "#aaaaaa Each point increases HP by 5 and HP per kill by 1.";

	// spirit
	statDescriptions[4] = "#aaaaaa Each point increases MP by 2 and MP per kill by 0.5.";
}

void StatWindow::GetInput(sf::RenderWindow& window, sf::Event& ev) {
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

bool StatWindow::Update(float secondsPerUpdate) {
	bool stayOpen = true;
	bool hasStatPoints = player->GetStatPoints() > 0;

	if (hasStatPoints) {
		// set up text
		statText[0].setString("Strength   " + std::to_string(player->GetSTR()) + "\n" + statDescriptions[0]);
		statText[1].setString("Dexterity   " + std::to_string(player->GetDEX()) + "\n" + statDescriptions[1]);
		statText[2].setString("Magic   " + std::to_string(player->GetMAG()) + "\n" + statDescriptions[2]);
		statText[3].setString("Vitality   " + std::to_string(player->GetVIT()) + "\n" + statDescriptions[3]);
		statText[4].setString("Spirit   " + std::to_string(player->GetSPI()) + "\n" + statDescriptions[4]);

		for (size_t i = 0; i < statButtons.size(); i++) {
			if (statButtons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
				statButtons[i].setTextureRect(sf::IntRect(32, 0, 32, 32));
				if (leftClick) {
					StatModType attribute;
					switch (i) {
						case 0:
							attribute = StatModType::STR;
							break;
						case 1:
							attribute = StatModType::DEX;
							break;
						case 2:
							attribute = StatModType::MAG;
							break;
						case 3:
							attribute = StatModType::VIT;
							break;
						case 4:
							attribute = StatModType::SPI;
							break;
						default:
							break;
					}
					player->SpendStatPoint(attribute);
					leftClick = false;
				}
			}
			else {
				statButtons[i].setTextureRect(sf::IntRect(0, 0, 32, 32));
			}
		}
	}
	else {
		stayOpen = false;
	}

	if (leftClick && !background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		stayOpen = false;
	}

	leftClick = false;
	rightClick = false;

	return stayOpen;
}

void StatWindow::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);

	for (size_t i = 0; i < statText.size(); i++) {
		window.draw(statText[i]);
		window.draw(statButtons[i]);
	}
}

void StatWindow::Initialize() {
	sf::Vector2f backgroundSize = background.getSize();
	sf::Vector2f pos(static_cast<float>(settings.ScreenWidth) / 2.f - backgroundSize.x / 2.f, static_cast<float>(settings.ScreenHeight) / 2.f - backgroundSize.y / 2.f);

	background.setPosition(pos);

	for (size_t i = 0; i < statText.size(); i++) {
		float iFloat = static_cast<float>(i);
		statText[i].setPosition(pos.x + 16.f, pos.y + 16.f + iFloat * 50.f);
		statButtons[i].setPosition(pos.x + backgroundSize.x - 48.f, pos.y + 24.f + iFloat * 50.f);
	}
}

void StatWindow::SetPlayer(Player* p) {
	player = p;
}