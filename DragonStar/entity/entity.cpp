// ================================================================
//
// entity.cpp
//
// ================================================================

#include "entity.hpp"

#include "../core/settings.hpp"

Entity::Entity() {
	destination = { 0.f, 0.f };
	velocity = { 0.f, 0.f };
	updatePos = { 0.f, 0.f };
}

Entity::Entity(sf::Vector2f spawnPosition, std::vector<std::string> textureFilePaths) {
	sprites.resize(textureFilePaths.size());
	for (size_t i = 0; i < textureFilePaths.size(); i++) {
		sprites[i].setTexture(*assetManager.LoadTexture(textureFilePaths[i]));
		sprites[i].setPosition(spawnPosition);
	}
	destination = spawnPosition;
	updatePos = spawnPosition;
}

Entity::Entity(sf::Vector2i tileSpawnPosition, std::vector<std::string> textureFilePaths) {
	sprites.resize(textureFilePaths.size());
	sf::Vector2f spawnPosition = { static_cast<float>(tileSpawnPosition.x * settings.TileSizeInt), static_cast<float>(tileSpawnPosition.y * settings.TileSizeInt) };

	for (size_t i = 0; i < textureFilePaths.size(); i++) {
		sprites[i].setTexture(*assetManager.LoadTexture(textureFilePaths[i]));
		sprites[i].setPosition(spawnPosition);
	}
	destination = spawnPosition;
	updatePos = spawnPosition;
}

void Entity::Update(float secondsPerUpdate) {
	if (!sprites.empty() && sprites[0].getPosition() != destination) {
		for (size_t i = 0; i < sprites.size(); i++) {
			sprites[i].setPosition(updatePos);
		}	
		
		updatePos = sprites[0].getPosition();
		velocityPerUpdate = { velocity.x * secondsPerUpdate, velocity.y * secondsPerUpdate };

		// Make sure the entity doesn't overshoot it's destination.
		if (abs(destination.x - sprites[0].getPosition().x) < abs(velocityPerUpdate.x)) {
			updatePos.x = destination.x;
		}
		else {
			updatePos.x += velocityPerUpdate.x;
		}

		// Make sure the entity doesn't overshoot it's destination.
		if (abs(destination.y - sprites[0].getPosition().y) < abs(velocityPerUpdate.y)) {
			updatePos.y = destination.y;
		}
		else {
			updatePos.y += velocityPerUpdate.y;
		}
	}
	else {
		velocity = { 0.f, 0.f };
		velocityPerUpdate = { 0.f, 0.f };
		updatePos = destination;
	}
}

void Entity::Draw(sf::RenderTarget& window, float timeRatio) {
	if (!sprites.empty()) {
		if (IsMoving()) {
			sf::Vector2f oldPos = sprites[0].getPosition();
			sf::Vector2f interlopPos = { oldPos.x + velocityPerUpdate.x * timeRatio, oldPos.y + velocityPerUpdate.y * timeRatio };

			// Don't overshoot target destination.
			if (abs(destination.x - oldPos.x) < abs(velocityPerUpdate.x * timeRatio)) {
				interlopPos.x = destination.x;
			}
			if (abs(destination.y - oldPos.y) < abs(velocityPerUpdate.y * timeRatio)) {
				interlopPos.y = destination.y;
			}

			for (size_t i = 0; i < sprites.size(); i++) {
				sprites[i].setPosition(interlopPos);
				if (IsOnScreen(window)) {
					window.draw(sprites[i]);
				}
				sprites[i].setPosition(oldPos);
			}
		}
		else {
			for (size_t i = 0; i < sprites.size(); i++) {
				if (IsOnScreen(window)) {
					window.draw(sprites[i]);
				}
			}
		}
	}
}

void Entity::Draw(sf::RenderTarget& window, float timeRatio, sf::Vector2f pos, float scale) {
	if (!sprites.empty()) {
		for (size_t i = 0; i < sprites.size(); i++) {
			sf::Vector2f oldPos = sprites[i].getPosition();
			auto oldScale = sprites[i].getScale();
			sprites[i].setPosition(pos);
			sprites[i].setScale(scale, scale);
			if (IsOnScreen(window)) {
				window.draw(sprites[i]);
			}
			sprites[i].setPosition(oldPos);
			sprites[i].setScale(oldScale);
		}
	}
}

void Entity::Move(sf::Vector2f target, float unitsPerSecond) {
	if (!sprites.empty()) {
		if (unitsPerSecond == 0.f) {
			destination = target;
			for (size_t i = 0; i < sprites.size(); i++) {
				sprites[i].setPosition(target);
			}
		}
		else {
			destination = target;
			speed = unitsPerSecond;

			float distance = sqrt(powf(target.x - sprites[0].getPosition().x, 2) + powf(target.y - sprites[0].getPosition().y, 2));
			velocity.x = (unitsPerSecond / distance) * (target.x - sprites[0].getPosition().x);
			velocity.y = (unitsPerSecond / distance) * (target.y - sprites[0].getPosition().y);
		}
	}
}

void Entity::MoveToTile(sf::Vector2i target, float unitsPerSecond) {
	sf::Vector2f t = { static_cast<float>(target.x * settings.TileSizeInt), static_cast<float>(target.y * settings.TileSizeInt) };
	Move(t, unitsPerSecond);
}

sf::Vector2f Entity::GetSpritePosition() {
	if (!sprites.empty()) {
		return sprites[0].getPosition();
	}
	else {
		return { 0.f, 0.f };
	}
}

bool Entity::IsMoving() {
	if (!sprites.empty()) {
		return (sprites[0].getPosition() != destination);
	}
	else {
		return false;
	}
}

bool Entity::IsOnScreen(sf::RenderTarget& window) {
	if (!sprites.empty()) {
		sf::View view = window.getView();
		sf::FloatRect screen(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y);
		sf::FloatRect rect = sprites[0].getGlobalBounds();
		if (screen.intersects(rect)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}