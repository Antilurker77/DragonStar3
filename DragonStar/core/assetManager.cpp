// ================================================================
//
// assetManager.cpp
//
// ================================================================

#include "assetManager.hpp"

AssetManager assetManager;

AssetManager::AssetManager() {
	// load default graphics
	//loadDefaultAssets();
}

/*
// adds default assets to all the DungeonMaps
void AssetManager::loadDefaultAssets() {
	sf::Image dImage;
	sf::Texture dTexture;
	sf::Font dFont;
	sf::SoundBuffer dSoundBuffer;

	dTexture.loadFromFile("gfx/dungeon/dungeon_test_hex.png");
	textureMap["gfx/dungeon/dungeon_test_hex.png"] = dTexture;

	dTexture.loadFromFile("gfx/ui/icon/default.png");
	textureMap["gfx/ui/icon/default.png"] = dTexture;

	dTexture.loadFromFile("gfx/ui/icon/small_icon/default.png");
	textureMap["gfx/ui/icon/small_icon/default.png"] = dTexture;
}
*/

/*
// sets the filepath to a defualt resource if the file can't be found
std::string AssetManager::loadDefault(std::string filePath) {
	if (filePath.find("dungeon") != filePath.npos) {
		return "gfx/dungeon/dungeon_test_hex.png";
	}
	if (filePath.find("small_icon") != filePath.npos) {
		return "gfx/ui/icon/small_icon/default.png";
	}
	if (filePath.find("icon") != filePath.npos) {
		return "gfx/ui/icon/default.png";
	}
	return "gfx/ui/icon/default.png";
}
*/

sf::Image* AssetManager::LoadImage(std::string filePath) {
	sf::Image image;

	// check if element doesn't exist
	if (imageMap.find(filePath) == imageMap.end()) {
		if (image.loadFromFile(filePath)) {
			imageMap[filePath] = image;
		}
		// return a default graphic if the filepath is wrong
		else {
			//filePath = loadDefault(filePath);
		}
	}

	return &imageMap.at(filePath);
}

sf::Texture* AssetManager::LoadTexture(std::string filePath) {
	sf::Texture texture;

	// check if element doesn't exist
	if (textureMap.find(filePath) == textureMap.end()) {
		if (texture.loadFromFile(filePath)) {
			textureMap[filePath] = texture;
			texture.setSmooth(true);
		}
		// return a default graphic if the filepath is wrong
		else {
			//filePath = loadDefault(filePath);
		}
	}

	return &textureMap.at(filePath);
}

sf::Font* AssetManager::LoadFont(std::string filePath) {
	sf::Font font;

	// check if element doesn't exist
	if (fontMap.find(filePath) == fontMap.end()) {
		if (font.loadFromFile(filePath)) {
			fontMap[filePath] = font;
		}
		// return a default graphic if the filepath is wrong
		else {
			//filePath = loadDefault(filePath);
		}
	}

	return &fontMap.at(filePath);
}

sf::SoundBuffer* AssetManager::LoadSoundBuffer(std::string filePath) {
	sf::SoundBuffer soundBuffer;

	// check if element doesn't exist
	if (soundBufferMap.find(filePath) == soundBufferMap.end()) {
		if (soundBuffer.loadFromFile(filePath)) {
			soundBufferMap[filePath] = soundBuffer;
		}
		// return a default graphic if the filepath is wrong
		else {
			//filePath = loadDefault(filePath);
		}
	}

	return &soundBufferMap.at(filePath);
}