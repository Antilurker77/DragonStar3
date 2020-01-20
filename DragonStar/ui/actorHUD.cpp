// ================================================================
//
// actorHUD.cpp
//
// ================================================================

#include "actorHUD.hpp"

#include "../core/settings.hpp"
#include "../entity/actor.hpp"

ActorHUD::ActorHUD() {
	// exhaustion
	exhaustionBackground.setFillColor(sf::Color(0, 0, 0, 191));
	exhaustionBackground.setOutlineThickness(0.f);

	exhaustionText.setFont(*assetManager.LoadFont(settings.Font));
	exhaustionText.setCharacterSize(18u);
	exhaustionText.setScale(1.f / 3.f, 1.f / 3.f);

	// life bar
	lifeBarBackground.setFillColor(sf::Color(200, 0, 0, 255));
	lifeBarBackground.setOutlineThickness(settings.TileSizeFloat / 32.f);
	lifeBarBackground.setOutlineColor(sf::Color(0, 0, 0, 255));
	lifeBarBackground.setSize(sf::Vector2f(settings.TileSizeFloat / 16.f * 10.f, settings.TileSizeFloat / 16.f));

	lifeBar.setFillColor(sf::Color(0, 200, 0, 255));
	lifeBar.setOutlineThickness(0.f);
	lifeBar.setSize(sf::Vector2f(settings.TileSizeFloat / 16.f * 10.f, settings.TileSizeFloat / 16.f));
}

void ActorHUD::Update(Actor& actor, float secondsPerUpdate) {
	sf::Vector2f pos = actor.GetSpritePosition();

	exhaustionBackground.setPosition(pos.x + 1.f, pos.y + 1.f);
	exhaustionText.setPosition(pos.x + 2.f, pos.y + 2.f);

	sf::Vector2f barSize(settings.TileSizeFloat / 16.f * 10.f, settings.TileSizeFloat / 16.f);
	lifeBarBackground.setPosition(pos.x + settings.TileSizeFloat / 2.f - barSize.x / 2.f, pos.y + settings.TileSizeFloat - 5.f);
	lifeBar.setPosition(pos.x + settings.TileSizeFloat / 2.f - barSize.x / 2.f, pos.y + settings.TileSizeFloat - 5.f);
}

void ActorHUD::UpdateElements(Actor& actor) {
	int exhastion = actor.GetExhaustion();

	// converts seconds into string
	auto convertToSec = [](int i) {
		std::string s;
		if (i > 999) {
			s = std::to_string(i / 100) + "s";
		}
		else {
			// make sure it always shows two decimals if use time is less than 10s
			std::string remainder = std::to_string(i % 100);
			if (remainder.length() == 1) {
				remainder = "0" + remainder;
			}

			s = std::to_string(i / 100) + "." + remainder + "s";
		}

		return s;
	};

	if (exhastion > 0 && !actor.IsPlayer()) {
		// very performance heavy
		//exhaustionText.setString(convertToSec(exhastion));
		//sf::FloatRect textSize = exhaustionText.getGlobalBounds();
		//exhaustionText.setOrigin(exhaustionText.getLocalBounds().left, exhaustionText.getLocalBounds().top);
		//exhaustionBackground.setSize(sf::Vector2f(textSize.width + 2.f, textSize.height + 2.f));
		displayExhastion = true;
	}
	else {
		displayExhastion = false;
	}

	float lifeBarLength = static_cast<float>(actor.GetCurrentHP() * (settings.TileSizeFloat / 16.f * 10.f) / actor.GetMaxHP());
	// If the actor is very close to death, still show a small sliver of the HP bar.
	if (lifeBarLength < 1.f && actor.GetCurrentHP() > 0) {
		lifeBarLength = 1.f;
	}
	lifeBar.setSize(sf::Vector2f(lifeBarLength, settings.TileSizeFloat / 16.f));
}

void ActorHUD::Draw(sf::RenderTarget& window, float timeRatio) {
	// Do not display exhaustion text at 1x zoom, too hard to read.
	if (displayExhastion && window.getView().getSize().x != static_cast<float>(settings.ScreenWidth)) {
		//window.draw(exhaustionBackground);
		//window.draw(exhaustionText);
	}
	
	window.draw(lifeBarBackground);
	window.draw(lifeBar);
}