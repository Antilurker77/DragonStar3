// ================================================================
//
// fctManager.hpp
// 
// Floating Combat Text manager. Manages FCT for a single actor.
//
// ================================================================

#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "richText.hpp"

enum class AttributeType;
enum class Element;

struct FCTUnit {
	sf::RectangleShape Background;
	sfe::RichText Text;
	std::vector<sf::Sprite> Icons;
	float Lifespan = 0.f;
};

class FCTManager {
public:
	FCTManager();

	// Updates the position of FCTs. Removes expired FCTs.
	void Update(sf::Vector2i actorLocation, float secondsPerUpdate);

	// Draws the FCTs.
	void Draw(sf::RenderTarget& window, float timeRatio);

	// Removes all FCTs.
	void Clear();

	// Adds a damage or healing FCT.
	void AddValueUnit(int value, bool isCrit, std::vector<Element> elements, bool isHeal, AttributeType attribute);

	// Adds a miss FCT.
	void AddMissUnit();

	// Adds an aura FCT.
	void AddAuraUnit(std::string name, bool isBuff, bool isExpired);

private:
	std::vector<FCTUnit> fcts;

	const float maxLifespan = 2.f;
	const float velocity = 10.f;
	const unsigned int fontSize = 16u;
	const float boxHeight = 18.f;
};
