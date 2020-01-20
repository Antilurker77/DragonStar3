// ================================================================
//
// itemCommand.cpp
//
// ================================================================

#include "itemCommand.hpp"

#include "../core/records.hpp"
#include "../data/item.hpp"
#include "../scene/dungeonScene.hpp"
#include "../ui/inventory.hpp"

ItemCommand::ItemCommand(DungeonScene* ds, Inventory* inv, sf::Vector2i cursor, size_t invIndex) {
	dungeonScene = ds;
	inventory = inv;
	cursorLocation = cursor;
	index = invIndex;
}

void ItemCommand::Execute(Actor* actor) {
	Item* item = inventory->GetItem(index);
	if (item != nullptr) {
		Ability* ability = item->GetInvokedAbility();
		auto area = ability->GetTargetArea(cursorLocation, actor, dungeonScene);
		auto targets = dungeonScene->GetActorsInArea(area);
		item->UseItem(actor, targets, cursorLocation, area);

		// ID an item by use.
		if (!records.IsIdentified(item->GetItemID())) {
			records.Identify(item->GetItemID());
		}

		inventory->ConsumeItem(index);
	}
}