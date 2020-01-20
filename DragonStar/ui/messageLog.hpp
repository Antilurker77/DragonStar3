// ================================================================
//
// messageLog.hpp
// 
// UI element that displays log messages in the bottom-right
// corner. This is a global because it needs to be accessed by
// many classes and is easier for debugging.
//
// ================================================================

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "richText.hpp"

class MessageLog {
public:
	MessageLog();

	// Updates the message log. Recalcs only if there are changes.
	void Update(float secondsPerUpdate);

	// Draws the message log.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Adds a message to the log.
	void AddMessage(std::string message);

	// Clears the log.
	void ClearMessages();

private:
	bool changedMessage = false;
	sf::RectangleShape background;
	std::vector<sfe::RichText> messages;

	const unsigned int fontSize = 12u;
	const int maxMessagesDisplayed = 12u;
};

extern MessageLog messageLog;
