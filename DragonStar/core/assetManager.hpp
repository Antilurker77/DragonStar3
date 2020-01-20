// ================================================================
//
// assetManager.hpp
// 
// Manages all loaded art assets so that assets aren't loaded
// multiple times. Must be cleared manually.
//
// ================================================================

#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager {
public:
	AssetManager();

	// Loads an image into the asset manager and returns a pointer to the image.
	// If it has already been loaded the asset manager will just return the pointer.
	sf::Image* LoadImage(std::string filepath);

	// Loads a texture into the asset manager and returns a pointer to the texture.
	// If it has already been loaded the asset manager will just return the pointer.
	sf::Texture* LoadTexture(std::string filePath);

	// Loads a font into the asset manager and returns a pointer to the font.
	// If it has already been loaded the asset manager will just return the pointer.
	sf::Font* LoadFont(std::string filePath);

	// Loads a sound buffer into the asset manager and returns a pointer to the buffer.
	// If it has already been loaded the asset manager will just return the pointer.
	sf::SoundBuffer* LoadSoundBuffer(std::string filePath);

private:
	std::map<std::string, sf::Image> imageMap;
	std::map<std::string, sf::Texture> textureMap;
	std::map<std::string, sf::Font> fontMap;
	std::map<std::string, sf::SoundBuffer> soundBufferMap;
};

extern AssetManager assetManager;