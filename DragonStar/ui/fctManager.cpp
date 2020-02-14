// ================================================================
//
// fctManager.cpp
//
// ================================================================

#include "fctManager.hpp"

#include "../core/assetManager.hpp"
#include "../core/combat.hpp"
#include "../core/settings.hpp"
#include "../data/id/element.hpp"

FCTManager::FCTManager() {

}

void FCTManager::Update(sf::Vector2i actorLocation, float secondsPerUpdate) {
	if (!fcts.empty()) {
		sf::Vector2f actorPos;
		actorPos.x = static_cast<float>(actorLocation.x * settings.TileSizeInt);
		actorPos.y = static_cast<float>(actorLocation.y * settings.TileSizeInt);

		// Goes in reverse order.
		float prevY = 0.f;
		for (size_t i = fcts.size(); i-- > 0; ) {
			float xPos = actorPos.x + settings.TileSizeFloat / 2.f - fcts[i].Background.getLocalBounds().width / 2.f;
			float yPos = actorPos.y - boxHeight + 10.f;
			float textWidth = fcts[i].Text.getLocalBounds().width;
			yPos -= fcts[i].Lifespan * velocity;

			// Stops boxes from overlapping.
			if (i != fcts.size() - 1) {
				yPos = std::min(yPos, prevY - boxHeight - 1.f);
			}
			prevY = yPos;

			fcts[i].Background.setPosition(xPos, yPos);
			fcts[i].Text.setPosition(xPos + 1.f, yPos + 1.f);

			for (size_t j = 0; j < fcts[i].Icons.size(); j++) {
				fcts[i].Icons[j].setPosition(xPos + 3.f + textWidth + (static_cast<float>(j) * 17.f), yPos + 3.f);
			}

			fcts[i].Lifespan += secondsPerUpdate;
		}

		// Remove expired units.
		auto expired = [&](FCTUnit& f) {
			return f.Lifespan >= maxLifespan;
		};

		fcts.erase(std::remove_if(fcts.begin(), fcts.end(), expired), fcts.end());
	}
}

void FCTManager::Draw(sf::RenderTarget& window, float timeRatio) {
	for (auto& unit : fcts) {
		if (unit.Lifespan > 0.f) {
			window.draw(unit.Background);
			window.draw(unit.Text);
			for (auto& icon : unit.Icons) {
				window.draw(icon);
			}
		}
	}
}

void FCTManager::Clear() {
	fcts.clear();
}

void FCTManager::AddValueUnit(int value, bool isCrit, std::vector<Element> elements, bool isHeal, AttributeType attribute) {
	FCTUnit unit;

	std::string s;
	if (isHeal) {
		switch (attribute) {
			case AttributeType::HP:
				s += "#heal ";
				break;
			case AttributeType::MP:
				s += "#spell ";
				break;
			case AttributeType::SP:
				s += "#skill ";
				break;
			default:
				break;
		}
	}
	else {
		s += "#damage ";
	}

	if (isCrit) {
		s += "\\*" + std::to_string(value) + "\\*";
	}
	else {
		s += std::to_string(value);
	}

	unit.Icons.reserve(elements.size());
	for (auto& element : elements) {
		sf::Sprite icon;
		std::string filepath = "gfx/icon/element/";
		switch (element) {
			case Element::Physical:
				filepath += "physical.png";
				break;
			case Element::Arcane:
				filepath += "arcane.png";
				break;
			case Element::Fire:
				filepath += "fire.png";
				break;
			case Element::Ice:
				filepath += "ice.png";
				break;
			case Element::Lightning:
				filepath += "lightning.png";
				break;
			case Element::Water:
				filepath += "water.png";
				break;
			case Element::Poison:
				filepath += "poison.png";
				break;
			case Element::Light:
				filepath += "light.png";
				break;
			case Element::Dark:
				filepath += "dark.png";
				break;
			default:
				filepath += "default.png";
				break;
		}

		icon.setTexture(*assetManager.LoadTexture(filepath));
		unit.Icons.push_back(icon);
	}

	unit.Text.setFont(*assetManager.LoadFont(settings.Font));
	unit.Text.setString(s);
	unit.Text.setCharacterSize(fontSize);

	unit.Background.setFillColor(sf::Color(0, 0, 0, 191));
	unit.Background.setSize(sf::Vector2f(unit.Text.getGlobalBounds().width + (unit.Icons.size() * 17.f) + 2.f, boxHeight));

	fcts.push_back(unit);
}

void FCTManager::AddMissUnit() {
	FCTUnit unit;
	
	std::string s = "#aaaaaa Miss";

	unit.Text.setFont(*assetManager.LoadFont(settings.Font));
	unit.Text.setString(s);
	unit.Text.setCharacterSize(fontSize);

	unit.Background.setFillColor(sf::Color(0, 0, 0, 191));
	unit.Background.setSize(sf::Vector2f(unit.Text.getGlobalBounds().width + 2.f, boxHeight));

	fcts.push_back(unit);
}

void FCTManager::AddAuraUnit(std::string auraName, bool isBuff, bool isExpired) {
	FCTUnit unit;

	std::string s;

	if (isBuff) {
		s = "#player ";
	}
	else {
		s = "#monster ";
	}
	
	if (isExpired) {
		s += "-";
	}
	else {
		s += "+";
	}

	s += auraName;

	unit.Text.setFont(*assetManager.LoadFont(settings.Font));
	unit.Text.setString(s);
	unit.Text.setCharacterSize(fontSize);

	unit.Background.setFillColor(sf::Color(0, 0, 0, 191));
	unit.Background.setSize(sf::Vector2f(unit.Text.getGlobalBounds().width + 2.f, boxHeight));

	fcts.push_back(unit);
}