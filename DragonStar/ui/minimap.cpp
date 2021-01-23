// ================================================================
//
// minimap.cpp
//
// ================================================================

#include "minimap.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../scene/dungeonScene.hpp"

Minimap::Minimap() {
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));

	minimapTexture = assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/minimap.png");
}

void Minimap::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);
	window.draw(minimap, minimapTexture);
}

void Minimap::UpdateMinimap(DungeonScene* dungeonScene) {
	auto dungeonSize = dungeonScene->GetDungeonSize();
	sf::Vector2f minimapSize{ static_cast<float>(dungeonSize.x) * tileSize, static_cast<float>(dungeonSize.y) * tileSize };
	sf::Vector2f pos{ static_cast<float>(settings.ScreenWidth) - minimapSize.x - 4.f, 4.f };

	background.setSize(minimapSize);
	background.setPosition(pos);

	minimap.setPrimitiveType(sf::Quads);
	minimap.resize(dungeonSize.x * dungeonSize.y * 8);

	size_t i = 0;

	// Dungeon Features
	for (size_t x = 0; x < dungeonSize.x; x++) {
		for (size_t y = 0; y < dungeonSize.y; y++) {
			sf::Vertex* quad = &minimap[i * 4];

			float texX = 0.f;
			float texY = 0.f;
			float posX = static_cast<float>(x) * tileSize + pos.x;
			float posY = static_cast<float>(y) * tileSize + pos.y;

			// Determine square color.
			sf::Vector2i tile(static_cast<int>(x), static_cast<int>(y));
			if (dungeonScene->IsOccupiedByActor(tile)) {
				if (dungeonScene->GetActorAtTile(tile)->IsPlayer()) {
					texX = 0.f;
					texY = 4.f;
				}
				else {
					texX = 4.f;
					texY = 4.f;
				}
			}
			else if (dungeonScene->IsOccupiedByShop(tile)) {
				texX = 8.f;
				texY = 4.f;
			}
			else if (dungeonScene->IsOpeque(tile)) {
				texX = 8.f;
				texY = 0.f;
			}
			else if (dungeonScene->IsDownStairs(tile)) {
				texX = 12.f;
				texY = 0.f;
			}
			else {
				texX = 4.f;
				texY = 0.f;
			}

			// quad cords
			// 0  1
			// 3  2
			quad[0].position = sf::Vector2f(posX, posY);
			quad[1].position = sf::Vector2f(posX + tileSize, posY);
			quad[2].position = sf::Vector2f(posX + tileSize, posY + tileSize);
			quad[3].position = sf::Vector2f(posX, posY + tileSize);

			// quad texture cords
			// 0  1
			// 3  2
			quad[0].texCoords = sf::Vector2f(texX, texY);
			quad[1].texCoords = sf::Vector2f(texX + tileSize, texY);
			quad[2].texCoords = sf::Vector2f(texX + tileSize, texY + tileSize);
			quad[3].texCoords = sf::Vector2f(texX, texY + tileSize);

			i++;
		}
	}

	// Vision
	for (size_t x = 0; x < dungeonSize.x; x++) {
		for (size_t y = 0; y < dungeonSize.y; y++) {
			sf::Vertex* quad = &minimap[i * 4];
			
			float texX = 0.f;
			float texY = 0.f;
			float posX = static_cast<float>(x) * tileSize + pos.x;
			float posY = static_cast<float>(y) * tileSize + pos.y;

			switch (dungeonScene->GetTileVisionState(sf::Vector2<size_t>(x, y))) {
				case VisionState::Unexplored: // 255
					quad[0].color = sf::Color(0, 0, 0, 127);
					quad[1].color = sf::Color(0, 0, 0, 127);
					quad[2].color = sf::Color(0, 0, 0, 127);
					quad[3].color = sf::Color(0, 0, 0, 127);
					break;
				case VisionState::OutOfSight: // 127
					quad[0].color = sf::Color(0, 0, 0, 127);
					quad[1].color = sf::Color(0, 0, 0, 127);
					quad[2].color = sf::Color(0, 0, 0, 127);
					quad[3].color = sf::Color(0, 0, 0, 127);
					break;
				default:
					quad[0].color = sf::Color(0, 0, 0, 0);
					quad[1].color = sf::Color(0, 0, 0, 0);
					quad[2].color = sf::Color(0, 0, 0, 0);
					quad[3].color = sf::Color(0, 0, 0, 0);
					break;
			}

			// quad cords
			// 0  1
			// 3  2
			quad[0].position = sf::Vector2f(posX, posY);
			quad[1].position = sf::Vector2f(posX + tileSize, posY);
			quad[2].position = sf::Vector2f(posX + tileSize, posY + tileSize);
			quad[3].position = sf::Vector2f(posX, posY + tileSize);

			// quad texture cords
			// 0  1
			// 3  2
			quad[0].texCoords = sf::Vector2f(texX, texY);
			quad[1].texCoords = sf::Vector2f(texX + tileSize, texY);
			quad[2].texCoords = sf::Vector2f(texX + tileSize, texY + tileSize);
			quad[3].texCoords = sf::Vector2f(texX, texY + tileSize);

			i++;
		}
	}

}