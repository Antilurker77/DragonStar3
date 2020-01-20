// ================================================================
//
// messageLog.cpp
//
// ================================================================

#include "messageLog.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"

MessageLog messageLog;

MessageLog::MessageLog() {
	// background
	background.setFillColor(sf::Color(0, 0, 0, 191));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 191));
	
	float fFontSize = static_cast<float>(fontSize);
	float fMaxMessages = static_cast<float>(maxMessagesDisplayed);

	background.setSize(sf::Vector2f(4.f + fFontSize * 50.f, 4.f + fMaxMessages * (fFontSize + 2.f)));
	background.setPosition(4.f, static_cast<float>(settings.ScreenHeight) - background.getSize().y - 4.f);
}

void MessageLog::Update(float secondsPerUpdate) {
	if (changedMessage) {
		changedMessage = false;
		sf::Vector2f pos = background.getPosition();

		// Newest messages drawn on the bottom.
		size_t last = 0;
		if (maxMessagesDisplayed < messages.size()) {
			last = messages.size() - maxMessagesDisplayed;
		}
		for (size_t i = last; i < messages.size(); i++) {
			float rowsFromTop = static_cast<float>(i) - static_cast<float>(messages.size()) + static_cast<float>(maxMessagesDisplayed);
			float size = static_cast<float>(fontSize) + 2.f;
			messages[i].setPosition(pos.x + 2.f, pos.y + 1.f + (rowsFromTop * size));
		}
	}
}

void MessageLog::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);

	// Newest messages drawn on the bottom.
	size_t last = 0;
	if (maxMessagesDisplayed < messages.size()) {
		last = messages.size() - maxMessagesDisplayed;
	}
	for (size_t i = last; i < messages.size(); i++) {
		window.draw(messages[i]);
	}
}

void MessageLog::AddMessage(std::string message) {
	sfe::RichText rt;
	rt.setFont(*assetManager.LoadFont(settings.Font));
	rt.setString(message);
	rt.setCharacterSize(fontSize);
	messages.push_back(rt);
	changedMessage = true;
}

void MessageLog::ClearMessages() {
	messages.clear();
	changedMessage = true;
}