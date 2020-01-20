// ================================================================
//
// cursorContainer.cpp
//
// ================================================================

#include "cursorContainer.hpp"

#include "rarityColor.hpp"
#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../scene/dungeonScene.hpp"

CursorContainer::CursorContainer() {

}

void CursorContainer::GetInput(sf::RenderWindow& window, sf::Event& ev) {
	sf::Mouse mouse;
	mousePos = mouse.getPosition(window);

	switch (ev.type) {
		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				holdingDownMouse = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				holdingDownMouse = false;
			}
			break;
		default:
			break;
	}
}

void CursorContainer::Update(float secondsPerUpdate, DungeonScene& dungeonScene) {
	if (holdingDownMouse) {
		holdingDownTime += secondsPerUpdate;
		if (holdingDownTime >= 0.05f) {
			if (!dragging) {
				draggedItemID = static_cast<ItemID>(0);
				draggedAbilityID = static_cast<AbilityID>(0);
				
				// Check to see if item is under cursor.
				draggedItemID = dungeonScene.GetDraggableItem(mousePos, draggedItem, itemStackSize);
				draggedAbilityID = dungeonScene.GetDraggableAbility(mousePos);
				if (draggedItemID != static_cast<ItemID>(0)) {
					dragging = true;
					Item it(draggedItemID);
					sprite.setTexture(*assetManager.LoadTexture(it.GetIconFilePath()));
					sprite.setColor(RarityColor::GetColor(draggedItem.GetRarity()));
					sprite.setScale(2.f, 2.f);
				}
				else if (draggedAbilityID != static_cast<AbilityID>(0)) {
					dragging = true;
					Ability ab(draggedAbilityID, 0);
					sprite.setTexture(*assetManager.LoadTexture(ab.GetIcon()));
					sprite.setScale(2.f, 2.f);
				}
			}
			if (dragging) {
				float offset = 0.f;
				if (draggedItemID != static_cast<ItemID>(0)) {
					offset = 16.f;
				}
				else {
					offset = 20.f;
				}
				sf::Vector2f spritePos(static_cast<float>(mousePos.x) - offset, static_cast<float>(mousePos.y) - offset);
				sprite.setPosition(spritePos);
			}
		}
	}
	else {
		holdingDownTime = 0.f;
		if (dragging && draggedItemID != static_cast<ItemID>(0)) {
			dungeonScene.ReleaseDraggableItem(mousePos, draggedItemID, draggedItem, itemStackSize);
		}
		else if (dragging && draggedAbilityID != static_cast<AbilityID>(0)) {
			dungeonScene.ReleaseDraggableAbility(mousePos, draggedAbilityID);
		}
		dragging = false;
	}
}

void CursorContainer::Draw(sf::RenderTarget& window, float timeRatio) {
	if (dragging) {
		window.draw(sprite);
	}
}