// ================================================================
//
// settings.hpp
// 
// Global struct that stores setting information.
//
// ================================================================

#pragma once

#include <string>
#include <SFML/Window.hpp>

struct CameraKeys {
	sf::Keyboard::Key CameraUp = sf::Keyboard::Up;
	sf::Keyboard::Key CameraDown = sf::Keyboard::Down;
	sf::Keyboard::Key CameraLeft = sf::Keyboard::Left;
	sf::Keyboard::Key CameraRight = sf::Keyboard::Right;
	sf::Keyboard::Key ResetZoom = sf::Keyboard::F;
};

struct Settings {
	float ScreenMultiplier = 1.f;
	//uint32_t ScreenWidth = static_cast<uint32_t>(640.f * ScreenMultiplier);
	//uint32_t ScreenHeight = static_cast<uint32_t>(360.f * ScreenMultiplier);

	uint32_t ScreenWidth = static_cast<uint32_t>(1280u);
	uint32_t ScreenHeight = static_cast<uint32_t>(720u);

	bool EnableVSync = true;
	bool EnableFullscreen = false;

	std::string Tileset = "ascii";
	int TileSizeInt = 32;
	float TileSizeFloat = 32.f;

	std::string Font = "gfx/font/B612Mono-Regular.ttf";
	//std::string Font = "gfx/font/Bitstream Vera Sans Mono Roman.ttf";

	CameraKeys CameraKeybinds;
};

extern Settings settings;