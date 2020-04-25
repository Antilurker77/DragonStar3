// ================================================================
//
// dungeonScene.cpp
//
// ================================================================

#include "dungeonScene.hpp"

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cereal/archives/binary.hpp>
#include "../command/abilityCommand.hpp"
#include "../command/itemCommand.hpp"
#include "../command/moveCommand.hpp"
#include "../command/waitCommand.hpp"
#include "../core/assetManager.hpp"
#include "../core/camera.hpp"
#include "../core/settings.hpp"
#include "../core/random.hpp"
#include "../core/records.hpp"
#include "../data/id/itemID.hpp"
#include "../entity/monster.hpp"
#include "../entity/player.hpp"

#include "../data/id/monsterID.hpp"

DungeonScene::DungeonScene() {
	actors.push_back(std::make_unique<Player>());

	tileset = assetManager.LoadTexture("gfx/" + settings.Tileset + "/dungeon/dungeon_tiles.png");
	visionTexture = assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/vision.png");
	targetTexutre = assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/target_tiles.png");
	
	statButton.setTexture(*assetManager.LoadTexture("gfx/" + settings.Tileset + "/ui/plus.png"));
	statButton.setTextureRect(sf::IntRect(0, 0, 32, 32));

	// test
	/*
	for (int i = 0; i < 5000; i++) {
		actors.push_back(std::make_unique<Monster>(MonsterID::TargetDummy, sf::Vector2i(20, 20)));
	}
	*/
	
	// set up pointer reference
	actors[0]->SetDungeonScene(this);

	statWindow.SetPlayer(static_cast<Player*>(actors[0].get()));
}

void DungeonScene::SetUp(std::string name, RaceID race, StarterID startingGear) {
	actors.clear();
	actors.push_back(std::make_unique<Player>(name, race));
	actors[0]->SetDungeonScene(this);
	inventory.InitStartingGear(startingGear, *this);
	currentFloor = 1;
	playerHUD.ResetShortcuts();
	statWindow.SetPlayer(static_cast<Player*>(actors[0].get()));
}

void DungeonScene::SetPlayerName(std::string name) {
	actors[0]->SetName(name);
}

void DungeonScene::GenerateSeeds(uint64_t seed) {
	masterSeed = seed;
	std::mt19937_64 mt(seed);
	floorSeeds.clear();
	floorSeeds.resize(totalFloors);
	std::generate(floorSeeds.begin(), floorSeeds.end(), [&mt](){return Random::RandomSeed(mt); });
	generateDungeon();
	records.RandomizeIdentities(Random::RandomSeed(mt));
}

bool DungeonScene::LoadGame() {
	if (!std::filesystem::exists("save.sav")) {
		return false;
	}
	
	{
		std::ifstream file("save.sav", std::ios::binary);
		cereal::BinaryInputArchive archive(file);
		archive(saveFile);
	}

	masterSeed = saveFile.Seed;
	currentFloor = saveFile.CurrentFloor;

	records.Load(saveFile.SpawnedArtifacts, saveFile.SlainMonsters, saveFile.SlainMonsterCount);

	GenerateSeeds(masterSeed);

	records.LoadIdentities(saveFile.IdentifiedItems);

	actors.clear();
	// load player
	actors.push_back(std::make_unique<Player>(saveFile.Actors[0], saveFile.Player));

	// load monsters
	for (size_t i = 1; i < saveFile.Actors.size(); i++) {
		actors.push_back(std::make_unique<Monster>(saveFile.Actors[i], i));
	}

	// set aura pointer references
	// must be done after actor list is complete
	for (auto& actor : actors) {
		actor->SetAuraOwnerPointer();
	}

	// load loot
	lootPiles.clear();
	lootPiles.reserve(saveFile.Loot.size());
	for (auto& loot : saveFile.Loot) {
		lootPiles.push_back(Loot(loot));
	}

	// load inventory
	inventory.Load(saveFile.PlayerGold, saveFile.Inventory);

	// load shops
	for (size_t i = 0; i < shops.size(); i++) {
		shops[i].Load(saveFile.ShopItems[i]);
	}

	// load ability bar
	playerHUD.Load(saveFile.ShortcutAbilities);

	// load vision
	for (size_t x = 0; x < saveFile.Vision.size(); x++) {
		for (size_t y = 0; y < saveFile.Vision[x].size(); y++) {
			vision[x][y] = static_cast<VisionState>(saveFile.Vision[x][y]);
		}
	}
	buildVisionVertexArray();

	return true;
}

void DungeonScene::SetCamera(Camera* c) {
	camera = c;
	camera->SetPosition({ actors[0]->GetSpritePosition().x + 16.f, actors[0]->GetSpritePosition().y + 16.f });

	// temp test
	camera->SetZoom(1.f / settings.ScreenMultiplier);
}

void DungeonScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;
	sf::Mouse mouse;
	recalcTargetArray = false;

	leftClick = false;
	rightClick = false;

	sf::Vector2i windowMousePos = mouse.getPosition(window);
	sf::Vector2f worldMousePos = window.mapPixelToCoords(windowMousePos, camera->GetCamera());
	sf::Vector2i worldMousePosInt(static_cast<int>(std::round(worldMousePos.x)), static_cast<int>(std::round(worldMousePos.y)));

	// recalculate target vertex array if mouse moves to a different tile
	if (targeting && (TileMath::PixelToTile(worldMousePosInt) != cursorTileLocation)) {
		recalcTargetArray = true;
	}

	cursorTileLocation = TileMath::PixelToTile(worldMousePosInt);

	command = nullptr;

	while (window.pollEvent(ev)) {
		cursorContainer.GetInput(window, ev);
		
		// Loot window.
		if (displayLootWindow) {
			lootWindow.GetInput(window, ev);
		}
		
		// Inventory.
		if (displayInventory) {
			inventory.GetInput(window, ev);
		}

		// Spellbook.
		if (displaySpellbook) {
			spellbook.GetInput(window, ev);
		}

		// Shop window.
		if (displayShopWindow) {
			shopWindow.GetInput(window, ev);
		}

		// Stat window.
		if (displayStatWindow) {
			statWindow.GetInput(window, ev);
		}

		// Learn ability window.
		if (displayLearnAbilityWindow) {
			learnAbilityWindow.GetInput(window, ev);
		}

		// Inspect window.
		if (displayInspectWindow) {
			inspectWindow.GetInput(window, ev);
		}

		// Ability Bar
		playerHUD.GetInput(window, ev);

		switch (ev.type) {
		case sf::Event::Closed:
			saveGame();
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftClick = true;
				if (targeting) {
					std::vector<sf::Vector2i> range = targetingAbility->GetRange(actors[0].get(), this);
					sf::Vector2i target = TileMath::Closest(cursorTileLocation, range);
					target = GetProjectileImpactTile(actors[0]->GetLocation(), target, true);

					if (usingItem) {
						command = std::make_unique<ItemCommand>(this, &inventory, target, usingItemIndex);
					}
					else {
						command = std::make_unique<AbilityCommand>(this, targetingAbility->GetAbilityID(), target);
					}

					targeting = false;
					usingItem = false;
					targetingAbility = nullptr;
					leftClick = false; // stops inspect window from opening
				}
				if (displayStatButton && statButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(windowMousePos))) {
					statWindow.Initialize();
					displayStatWindow = true;
				}
			}

			if (ev.mouseButton.button == sf::Mouse::Right) {
				rightClick = true;
				targeting = false;
				targetingAbility = nullptr;
				usingItem = false;
			}
			break;

		case sf::Event::KeyReleased:
			//if (ev.key.code == sf::Keyboard::R) {
			//	// test seeds
			//	floorSeeds[currentFloor - 1] = Random::RandomSeed();
			//	generateDungeon();
			//	camera->SetPosition({ actors[0]->GetSpritePosition().x + 16.f, actors[0]->GetSpritePosition().y + 16.f });
			//}
			//// Quit
			//if (ev.key.code == sf::Keyboard::Escape) {
			//	saveGame();
			//	window.close();
			//	break;
			//}
			// Movement / Bump Attack
			sf::Vector2i destination = actors[0]->GetLocation();
			int distance = 0;
			if (ev.key.code == settings.MoveKeybinds.MoveN || ev.key.code == settings.MoveKeybinds.MoveNAlt) {
				destination.y -= 1;
				distance = 100;
			}
			if (ev.key.code == settings.MoveKeybinds.MoveW || ev.key.code == settings.MoveKeybinds.MoveWAlt) {
				destination.x -= 1;
				distance = 100;
			}
			if (ev.key.code == settings.MoveKeybinds.MoveS || ev.key.code == settings.MoveKeybinds.MoveSAlt) {
				destination.y += 1;
				distance = 100;
			}
			if (ev.key.code == settings.MoveKeybinds.MoveE || ev.key.code == settings.MoveKeybinds.MoveEAlt) {
				destination.x += 1;
				distance = 100;
			}
			if (ev.key.code == settings.MoveKeybinds.MoveNW || ev.key.code == settings.MoveKeybinds.MoveNWAlt) {
				destination.x -= 1;
				destination.y -= 1;
				distance = 141;
			}
			if (ev.key.code == settings.MoveKeybinds.MoveNE || ev.key.code == settings.MoveKeybinds.MoveNEAlt) {
				destination.x += 1;
				destination.y -= 1;
				distance = 141;
			}
			if (ev.key.code == settings.MoveKeybinds.MoveSE || ev.key.code == settings.MoveKeybinds.MoveSEAlt) {
				destination.x += 1;
				destination.y += 1;
				distance = 141;
			}
			if (ev.key.code == settings.MoveKeybinds.MoveSW || ev.key.code == settings.MoveKeybinds.MoveSWAlt) {
				destination.x -= 1;
				destination.y += 1;
				distance = 141;
			}
			// Wait.
			if (ev.key.code == settings.MoveKeybinds.Wait || ev.key.code == settings.MoveKeybinds.WaitAlt) {
				command = std::make_unique<WaitCommand>(100);
			}

			// Use stairs.
			if (ev.key.shift && ev.key.code == sf::Keyboard::Period) {
				sf::Vector2i loc = actors[0]->GetLocation();
				Tile* t = &floor[loc.x][loc.y];
				if (t->TileType == TileID::DownStairs) {
					changeFloors = true;
				}
				else {
					messageLog.AddMessage("There are no stairs here.");
				}
				break;
			}

			// Loot items on ground.
			if (ev.key.code == settings.UIKeybinds.Loot) {
				Loot* lp = GetLootAtLocation(actors[0]->GetLocation());
				if (lp != nullptr && !lp->IsEmpty()) {
					lootWindow.Initialize(*lp);
					displayLootWindow = true;
				}
			}

			// Display / Hide Inventory
			if (ev.key.code == settings.UIKeybinds.Inventory) {
				displayInventory = !displayInventory;
			}

			// Display / Hide Spellbook
			if (ev.key.code == settings.UIKeybinds.Spellbook) {
				displaySpellbook = !displaySpellbook;
			}

			// Move Command if tile is empty, attack if an actor is there.
			if (destination != actors[0]->GetLocation()) {
				if (IsOccupiedByActor(destination)) {
					int attackRange = actors[0]->GetAttackRange();
					if (attackRange >= distance) {
						command = std::make_unique<AbilityCommand>(this, static_cast<AbilityID>(1), destination);
						targeting = false;
					}
				}
				else if (IsOccupiedByShop(destination)) {
					displayShopWindow = true;
					shopWindow.Initialize(*GetShopAtLocation(destination));
					targeting = false;
				}
				else {
					command = std::make_unique<MoveCommand>(*this, destination);
					targeting = false;
				}
			}

			break;
		}
	}

	if (statButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(windowMousePos))) {
		statButton.setTextureRect(sf::IntRect(32, 0, 32, 32));
	}
	else {
		statButton.setTextureRect(sf::IntRect(0, 0, 32, 32));
	}

	camera->GetInput(ev);
}

GameState DungeonScene::Update(float secondsPerUpdate) {
	GameState gs = GameState::Dungeon;
	updateWorld(secondsPerUpdate);
	gs = updateUI(secondsPerUpdate);

	if (currentFloor == victoryFloor) {
		gs = GameState::Victory;

		// Delete save file.
		std::remove("save.sav");
	}
	if (!actors[0]->IsAlive()) {
		gs = GameState::Defeat;

		// Delete save file.
		std::remove("save.sav");
	}

	return gs;
}

void DungeonScene::UpdateVision() {
	auto currentLoS = TileMath::AreaOfEffect(actors[0]->GetLocation(), actors[0]->GetSightRadius());
	// [&](const sf::Vector2i& t) {return t.x == loc.x && t.y == loc.y; }
	for (size_t x = 0; x < vision.size(); x++) {
		for (size_t y = 0; y < vision[x].size(); y++) {
			sf::Vector2i loc(static_cast<int>(x), static_cast<int>(y));
			if (std::find(currentLoS.begin(), currentLoS.end(), loc) != currentLoS.end() && InLineOfSight(actors[0]->GetLocation(), loc)) {
				vision[x][y] = VisionState::InSight;
			}
			else if (vision[x][y] == VisionState::InSight){
				vision[x][y] = VisionState::OutOfSight;
			}
		}
	}

	buildVisionVertexArray();
}

void DungeonScene::DrawWorld(sf::RenderWindow& window, float timeRatio) {
	window.draw(floorArray, tileset);

	//window.draw(visionArray, visionTexture);

	// Draw targeting under everything.
	if (targeting && settings.Tileset != "ascii") {
		window.draw(targetingArray, targetTexutre);
	}

	// Draw loot under actors.
	for (auto& lp : lootPiles) {
		sf::Vector2i loc = lp.GetLocation();
		if (vision[loc.x][loc.y] == VisionState::InSight || vision[loc.x][loc.y] == VisionState::OutOfSight) {
			if (!lp.IsEmpty()) {
				lp.Draw(window, timeRatio);
			}
		}
	}

	// Shops.
	for (auto& s : shops) {
		sf::Vector2i loc = s.GetLocation();
		if (vision[loc.x][loc.y] == VisionState::InSight || vision[loc.x][loc.y] == VisionState::OutOfSight) {
			s.Draw(window, timeRatio);
		}
	}

	for (auto& a : actors) {
		sf::Vector2i loc = a->GetLocation();
		if (a->IsAlive() && vision[loc.x][loc.y] == VisionState::InSight) {
			a->Draw(window, timeRatio);
			a->DrawHUD(window, timeRatio);
		}
	}

	// Draw targeting over everything in ascii mode.
	if (targeting && settings.Tileset == "ascii") {
		window.draw(targetingArray, targetTexutre);
	}

	window.draw(visionArray, visionTexture);

	if (displayTooltip) {
		tooltip.Draw(window, timeRatio);
	}

	for (auto& a : actors) {
		a->DrawFCT(window, timeRatio);
	}

}

void DungeonScene::DrawUI(sf::RenderWindow& window, float timeRatio) {
	messageLog.Draw(window, timeRatio);
	
	playerHUD.Draw(window, timeRatio);

	minimap.Draw(window, timeRatio);

	if (displayInventory) {
		inventory.Draw(window, timeRatio);
	}

	if (displayLootWindow) {
		lootWindow.Draw(window, timeRatio);
	}

	if (displaySpellbook) {
		spellbook.Draw(window, timeRatio);
	}

	if (displayShopWindow) {
		shopWindow.Draw(window, timeRatio);
	}

	if (displayStatWindow) {
		statWindow.Draw(window, timeRatio);
	}

	if (displayStatButton & !displayStatWindow) {
		window.draw(statButton);
	}

	if (displayLearnAbilityWindow) {
		learnAbilityWindow.Draw(window, timeRatio);
	}

	if (displayInspectWindow) {
		inspectWindow.Draw(window, timeRatio);
	}

	cursorContainer.Draw(window, timeRatio);

}

int DungeonScene::GetCurrentFloor() {
	return currentFloor;
}

void DungeonScene::SetTargettingMode(AbilityID id) {
	usingItem = false;
	targetingAbility = actors[0]->GetAbility(id);
	if (targetingAbility != nullptr && targetingAbility->IsUsable(actors[0].get())) {
		targeting = true;
		buildTargetingVertexArray();
	}
	else {
		targeting = false;
	}
}

void DungeonScene::SetTargettingMode(Item& item, size_t index) {
	targeting = true;
	usingItem = true;
	targetingAbility = item.GetInvokedAbility();
	usingItemIndex = index;
	buildTargetingVertexArray();
}

void DungeonScene::OpenLearnAbilityWindow(Item* tome) {
	Player* p = static_cast<Player*>(actors[0].get());

	targeting = false;
	usingItem = false;
	targetingAbility = nullptr;

	displayStatWindow = false;
	displayLootWindow = false;

	displayLearnAbilityWindow = true;
	learnAbilityWindow.Initialize(tome, p);
}

sf::Vector2<size_t> DungeonScene::GetDungeonSize() {
	return { floor.size(), floor[0].size() };
}

std::vector<sf::Vector2i> DungeonScene::Pathfind(sf::Vector2i start, sf::Vector2i end) {
	return Pathfind(start, end, false, false, false);
}

std::vector<sf::Vector2i> DungeonScene::Pathfind(sf::Vector2<size_t> start, sf::Vector2<size_t> end) {
	sf::Vector2i s{ static_cast<int>(start.x), static_cast<int>(start.y) };
	sf::Vector2i e{ static_cast<int>(end.x), static_cast<int>(end.y) };
	return Pathfind(s, e, false, false, false);
}

std::vector<sf::Vector2i> DungeonScene::Pathfind(sf::Vector2i start, sf::Vector2i end, Actor* actor) {
	bool canFly = false; // todo: get actor movement options
	bool canSwim = false;
	bool canTunnel = false;
	return Pathfind(start, end, canFly, canSwim, canTunnel);
}

std::vector<sf::Vector2i> DungeonScene::Pathfind(sf::Vector2i start, sf::Vector2i end, bool canFly, bool canSwim, bool canTunnel) {
	std::vector<sf::Vector2i> path;

	std::vector<std::pair<sf::Vector2i, int>> frontier;
	std::unordered_map<sf::Vector2i, sf::Vector2i> cameFrom;
	std::unordered_map<sf::Vector2i, int>  costSoFar;

	frontier.push_back({ start, 0 });
	cameFrom[start] = start;
	costSoFar[start] = 0;

	while (!frontier.empty()) {
		// Sort frontier by cost for optimization.
		std::sort(frontier.begin(), frontier.end(), [](const std::pair<sf::Vector2i, int>& left, const std::pair<sf::Vector2i, int>& right) {return left.second < right.second; });

		sf::Vector2i current = frontier.front().first;

		if (current == end) {
			break;
		}

		// debug
		//pathRects.clear();
		firstPath = { -1, -1 };
		secondPath = { -1, -1 };

		// Get unoccupied tiles the actor can travel to.
		std::vector<sf::Vector2i> neighboors = TileMath::Neighboors(current);
		std::vector<sf::Vector2i> walkableNeighboors{};
		
		for (auto& t : neighboors) {
			if (!IsOccupiedByActor(t) && IsWalkable(canFly, canSwim, canTunnel, t)) {
				walkableNeighboors.push_back(t);
			}
		}

		// Where the magic happens.
		for (size_t i = 0; i < walkableNeighboors.size(); i++) {
			sf::Vector2i& next = walkableNeighboors[i];
			int cost = costSoFar[current] + std::min(GetHeuristicDistance(current, next, false), GetHeuristicDistance(current, next, true));
			if (costSoFar.find(next) == costSoFar.end() || cost < costSoFar[next]) {
				costSoFar[next] = cost;
				int priority = cost + std::min(GetHeuristicDistance(next, end, false), GetHeuristicDistance(next, end, true));
				cameFrom[next] = current;
				frontier.push_back({ next, priority });
			}
		}

		frontier.erase(frontier.begin());
	}

	// Create the vector and return the path.
	sf::Vector2i current = end;
	path.push_back(current);

	while (current != start) {
		auto i = cameFrom.find(current);
		if (i != cameFrom.end()) { // Prevents the algorithm from adding the end to the path if it's impossible to reach.
			current = i->second;
		}
		else {
			return std::vector<sf::Vector2i>{};
		}
		path.push_back(current);
	}

	// Path needs to be reversed so that it goes start -> end.
	// Also removes starting position from path.
	std::reverse(path.begin(), path.end());
	path.erase(path.begin());

	return path;
}

int DungeonScene::GetPathCost(std::vector<sf::Vector2i>& path) {
	int result = 0;

	for (size_t i = 1; i < path.size(); i++) {
		if (path[i].x != path[i - 1].x && path[i].y != path[i - 1].y) {
			result += floor[path[i].x][path[i].y].MoveMod * 1414 / 1000;
		}
		else {
			result += floor[path[i].x][path[i].y].MoveMod;
		}
	}

	return result;
}

int DungeonScene::GetHeuristicDistance(sf::Vector2i start, sf::Vector2i end, bool negativeOffset) {
	int result = 0;
	auto line = TileMath::Line(start, end, negativeOffset);
	for (size_t i = 1; i < line.size(); i++) {
		if (line[i].x != line[i - 1].x && line[i].y != line[i - 1].y) {
			result += floor[line[i].x][line[i].y].MoveMod * 1414 / 1000;
		}
		else {
			result += floor[line[i].x][line[i].y].MoveMod;
		}
	}
	
	return result;
}

std::vector<sf::Vector2i> DungeonScene::GetProjectilePath(sf::Vector2i start, sf::Vector2i goal) {
	std::vector<sf::Vector2i> result;
	size_t positive = 0;
	size_t negative = 0;

	// Positive
	std::vector<sf::Vector2i> testLineP = TileMath::Line(start, goal, false);
	for (auto t : testLineP) {
		if (t != start) {
			if (!IsOccupiedByActor(t) && !IsOpeque(t)) {
				positive++;
			}
			else {
				break;
			}
		}
	}

	// Negative
	std::vector<sf::Vector2i> testLineN = TileMath::Line(start, goal, true);
	for (auto t : testLineN) {
		if (t != start) {
			if (!IsOccupiedByActor(t) && !IsOpeque(t)) {
				negative++;
			}
			else {
				break;
			}
		}
	}

	if (positive < negative) {
		result = testLineN;
	}
	else if (positive > negative) {
		result = testLineP;
	}
	// Choose the prettiest line if both work
	else if (positive == negative) {
		int xDist = goal.x - start.x;
		int yDist = goal.y - start.y;
		
		if (xDist < 0 && yDist < 0) {
			result = testLineP;
		}
		else if (yDist < 0 && abs(xDist) > abs(yDist)) {
			result = testLineP;
		}
		else if (xDist < 0 && abs(xDist) < abs(yDist)) {
			result = testLineP;
		}
		else {
			result = testLineN;
		}
	}

	return result;
}

sf::Vector2i DungeonScene::GetProjectileImpactTile(sf::Vector2i start, sf::Vector2i goal, bool isPlayer) {
	std::vector<sf::Vector2i> line = GetProjectilePath(start, goal);
	sf::Vector2i result = line[0];

	for (auto t : line) {
		if (t != start) {
			result = t;
			if (IsOccupiedByActor(t) && isPlayer) {
				break;
			}
			else if (!isPlayer && IsOccupiedByActor(t) && GetActorAtTile(t)->IsPlayer()) {
				break;
			}
		}
	}

	return result;
}

Actor* DungeonScene::GetPlayer() {
	if (!actors.empty()) {
		return actors[0].get();
	}

	return nullptr;
}

Actor* DungeonScene::GetActorAtTile(sf::Vector2i tile) {
	for (auto &a : actors) {
		if (a->IsAlive() && a->GetLocation() == tile) {
			return a.get();
		}
	}

	return nullptr;
}

Actor* DungeonScene::GetActorByIndex(size_t index) {
	return actors[index].get();
}

std::vector<Actor*> DungeonScene::GetActorsInArea(std::vector<sf::Vector2i>& area) {
	std::vector<Actor*> result;
	result.reserve(area.size());

	for (auto loc : area) {
		for (auto &a : actors) {
			if (a->IsAlive() && a->GetLocation() == loc) {
				result.push_back(a.get());
				break;
			}
		}
	}

	return result;
}

Loot* DungeonScene::GetLootAtLocation(sf::Vector2i tile) {
	for (size_t i = 0; i < lootPiles.size(); i++) {
		if (lootPiles[i].GetLocation() == tile) {
			return &lootPiles[i];
		}
	}

	return nullptr;
}

Shop* DungeonScene::GetShopAtLocation(sf::Vector2i tile) {
	for (size_t i = 0; i < shops.size(); i++) {
		if (shops[i].GetLocation() == tile) {
			return &shops[i];
		}
	}

	return nullptr;
}

VisionState DungeonScene::GetTileVisionState(sf::Vector2i tile) {
	return vision[static_cast<size_t>(tile.x)][static_cast<size_t>(tile.y)];
}

VisionState DungeonScene::GetTileVisionState(sf::Vector2<size_t> tile) {
	return vision[tile.x][tile.y];
}

bool DungeonScene::IsOccupiedByActor(sf::Vector2i tile) {
	return std::any_of(actors.begin(), actors.end(), [&](const ActorPtr& a) {
		return a->IsAlive() && a->GetLocation() == tile;
	});
}

bool DungeonScene::IsOccupiedByLoot(sf::Vector2i tile) {
	return std::any_of(lootPiles.begin(), lootPiles.end(), [&](Loot& lp) {
		return lp.GetLocation() == tile;
	});
}

bool DungeonScene::IsOccupiedByShop(sf::Vector2i tile) {
	return std::any_of(shops.begin(), shops.end(), [&](Shop& s) {
		return s.GetLocation() == tile;
	});
}

bool DungeonScene::IsWalkable(Actor* actor, sf::Vector2i tile) {
	try {
		const Tile& t = floor.at(tile.x).at(tile.y);
		return t.IsPassible; // todo: flying/swimming
	}
	catch (const std::out_of_range&) {
		return false;
	}
}

bool DungeonScene::IsWalkable(bool canFly, bool canSwim, bool canTunnel, sf::Vector2i location) {
	// Check out of bounds.
	if (location.x >= 0 && location.x < floor.size() && location.y >= 0 && location.y < floor[location.x].size()) {
		Tile* t = &floor[location.x][location.y];
		if (t->IsPassible || (canFly && t->RequireFlight) || (canFly && t->RequireSwimming) || (canSwim && t->RequireSwimming) || (canTunnel && t->IsOpeque)) {
			return true;
		}
	}

	return false;
}

bool DungeonScene::IsDownStairs(sf::Vector2i tile) {
	return floor[static_cast<int>(tile.x)][static_cast<int>(tile.y)].TileType == TileID::DownStairs;
}

bool DungeonScene::IsOpeque(sf::Vector2i tile) {
	bool result = false;
	if (tile.x < floor.size() && tile.y < floor[0].size()) {
		result = floor[tile.x][tile.y].IsOpeque;
	}

	return result;
}

bool DungeonScene::InLineOfSight(sf::Vector2i start, sf::Vector2i end) {
	std::vector<sf::Vector2i> line = TileMath::Line(start, end, false);
	bool los = true;

	// returns true if line contains an opeque tile
	// ignores start and end of line so that walls are visable
	auto losCheck = [&](const sf::Vector2i t) {
		// oob check
		if (t.x < 0 || t.y < 0) {
			return false;
		}
		if (t.x >= floor.size()) {
			return false;
		}
		if (t.y >= floor[t.x].size()) {
			return false;
		}
		if (t != start && t != end) {
			return floor[t.x][t.y].IsOpeque;
		}
		else {
			return false;
		}
	};

	los = !std::any_of(line.begin(), line.end(), losCheck);

	if (!los) {
		line = TileMath::Line(start, end, true);
		los = !std::any_of(line.begin(), line.end(), losCheck);
	}

	return los;
}

void DungeonScene::DropLoot(sf::Vector2i location, int gold) {
	for (size_t i = 0; i < lootPiles.size(); i++) {
		if (lootPiles[i].GetLocation() == location) {
			lootPiles[i].AddGold(gold);
			return;
		}
	}

	Loot loot(location, gold);
	lootPiles.push_back(loot);
}

void DungeonScene::DropLoot(sf::Vector2i location, int gold, std::vector<Item> items) {
	for (size_t i = 0; i < lootPiles.size(); i++) {
		if (lootPiles[i].GetLocation() == location) {
			lootPiles[i].AddGold(gold);
			lootPiles[i].AddItems(items);
			return;
		}
	}

	lootPiles.push_back(Loot(location, gold, items));
}

void DungeonScene::DropLoot(sf::Vector2i location, Item item, int stackCount) {
	std::vector<Item> items;
	items.resize(static_cast<size_t>(stackCount));
	std::fill(items.begin(), items.end(), item);

	for (size_t i = 0; i < lootPiles.size(); i++) {
		if (lootPiles[i].GetLocation() == location) {
			lootPiles[i].AddItems(items);
			return;
		}
	}

	lootPiles.push_back(Loot(location, items));
}

ItemID DungeonScene::GetDraggableItem(sf::Vector2i location, Item& item, int& stackCount) {
	ItemID id{};

	// Inventory
	if (displayInventory) {
		inventory.GetDraggableItem(*this, location, id, item, stackCount);
	}

	return id;
}

void DungeonScene::ReleaseDraggableItem(sf::Vector2i location, ItemID& id, Item& item, int stackCount) {
	// Inventory
	if (displayInventory) {
		inventory.ReleaseDraggableItem(*this, location, item, stackCount);
	}

	// No UI element accepted it, so drop it on the ground.
	if (stackCount > 0 && !item.IsNull()) {
		DropLoot(actors[0]->GetLocation(), item, stackCount);
	}
}

AbilityID DungeonScene::GetDraggableAbility(sf::Vector2i location) {
	AbilityID id{};

	// Spellbook
	if (displaySpellbook) {
		spellbook.GetDraggableAbility(location, id);
	}

	// PlayerHUD;
	playerHUD.GetDraggableAbility(location, id);

	return id;
}

void DungeonScene::ReleaseDraggableAbility(sf::Vector2i location, AbilityID& id) {
	// Player HUD
	playerHUD.ReleaseDraggableAbility(location, id);

	// No UI element.
	id = static_cast<AbilityID>(0);
}

void DungeonScene::SetIdentifyMode(bool usingScroll) {
	displayInventory = true;
	inventory.IdentifyMode(usingScroll);
}

void DungeonScene::updateWorld(float secondsPerUpdate) {	
	for (auto& a : actors) {
		a->Update(secondsPerUpdate);
		a->UpdateHUD(secondsPerUpdate);
		a->UpdateFCT(secondsPerUpdate);

		// Remove auras from dead actors.
		if (!a->IsAlive()) {
			a->ClearAuras();
		}
	}

	// Do not spend more than 75% of the total update time calculating monster AI.
	sf::Clock clock;
	sf::Clock testClock;
	sf::Time aiCalcTime = sf::Time::Zero;
	const float maxUpdateTime = secondsPerUpdate * 0.75f;

	// Get the next actor ready to take their turn.
	while (activeActor == nullptr && aiCalcTime.asSeconds() < maxUpdateTime) {
		clock.restart();
		for (auto& a : actors) {
			if (a->IsReadyToAct() && a->IsAlive()) {
				activeActor = a.get();
				break;
			}
		}

		// No actor was found, so decrement exhaustion.
		if (activeActor == nullptr) {
			for (auto& a : actors) {
				if (a->IsAlive()) {
					a->DecrementExhaustion();
				}
			}
			aiCalcTime += clock.restart();
		}
		// There is an actor ready to take their turn.
		else {
			// Actors[0] will always be the player's character, so that means the active actor is a monster.
			if (!activeActor->IsPlayer()) {
				// Process the monster's AI to get a command.
				Monster* monster = static_cast<Monster*>(activeActor);
				command = monster->CalcAI();

				// Record how long it took.
				aiCalcTime += clock.restart();
				//messageLog.AddMessage("AI Calc Time: " + std::to_string(aiCalcTime.asSeconds() * 1000.f) + "ms");

				if (aiCalcTime.asSeconds() > maxUpdateTime) {
					messageLog.AddMessage("Max Update Time exceeded. AI calc time was " + std::to_string(aiCalcTime.asSeconds() * 1000.f) + "ms.");
				}

				if (command != nullptr) {
					command->Execute(activeActor);
					activeActor->UpdateHUD(secondsPerUpdate);
					activeActor = nullptr;
					command = nullptr;

					targeting = false;
					targetingAbility = nullptr;
					usingItem = false;
				}
			}
		}
	}

	if (activeActor != nullptr && activeActor->IsPlayer() && changeFloors) {
		command = nullptr;
		moveFloors(1);
		saveGame();

		targeting = false;
		targetingAbility = nullptr;
		usingItem = false;
		displayLootWindow = false;

		auto playerPos = actors[0]->GetLocation();
		camera->SetPosition(sf::Vector2f(playerPos.x * settings.TileSizeFloat + settings.TileSizeFloat / 2.f, playerPos.y * settings.TileSizeFloat + settings.TileSizeFloat / 2.f));
		activeActor->UpdateHUD(secondsPerUpdate);
	}

	if (activeActor != nullptr && command != nullptr) {
		command->Execute(activeActor);
		activeActor->UpdateHUD(secondsPerUpdate);
		activeActor = nullptr;
		command = nullptr;

		targeting = false;
		targetingAbility = nullptr;
		usingItem = false;

		auto playerPos = actors[0]->GetLocation();
		camera->SetPosition(sf::Vector2f(playerPos.x * settings.TileSizeFloat + settings.TileSizeFloat / 2.f, playerPos.y * settings.TileSizeFloat + settings.TileSizeFloat / 2.f));
	}

	float ms = testClock.restart().asSeconds();
	if (ms > secondsPerUpdate) {
		std::string s = "This frame took " + std::to_string(ms * 1000.f) + "ms. Seconds per update was " + std::to_string(secondsPerUpdate * 1000.f) + "ms.\n";
		messageLog.AddMessage(s);
	}

}

GameState DungeonScene::updateUI(float secondsPerUpdate) {
	cursorContainer.Update(secondsPerUpdate, *this);
	
	playerHUD.Update(actors[0].get(), *this, secondsPerUpdate);

	if (displayLootWindow) {
		displayLootWindow = lootWindow.Update(secondsPerUpdate, inventory);
	}

	if (displayInventory) {
		displayInventory = inventory.Update(secondsPerUpdate, *this);
	}

	if (displayShopWindow) {
		displayShopWindow = shopWindow.Update(secondsPerUpdate, inventory);
	}

	if (displaySpellbook) {
		spellbook.Update(secondsPerUpdate, actors[0].get());
	}

	if (recalcTargetArray && targeting) {
		buildTargetingVertexArray();
	}

	if (!displayStatWindow && static_cast<Player*>(GetPlayer())->GetStatPoints() > 0) {
		displayStatButton = true;
		statButton.setPosition(static_cast<float>(settings.ScreenWidth) / 2.f - 16.f, std::roundf(static_cast<float>(settings.ScreenHeight) / 8.f * 7.f));
	}
	else {
		displayStatButton = false;
	}

	if (displayStatWindow) {
		displayStatWindow = statWindow.Update(secondsPerUpdate);
	}

	if (displayLearnAbilityWindow) {
		displayLearnAbilityWindow = learnAbilityWindow.Update(secondsPerUpdate);
	}

	if (displayInspectWindow) {
		displayInspectWindow = inspectWindow.Update(secondsPerUpdate);
	}

	// monster inspect window
	if (!displayInspectWindow && !targeting && leftClick && IsOccupiedByActor(cursorTileLocation)) {
		Actor* actor = GetActorAtTile(cursorTileLocation);
		if (!actor->IsPlayer() && vision[cursorTileLocation.x][cursorTileLocation.y] == VisionState::InSight) {
			displayInspectWindow = true;
			inspectWindow.SetActor(actor);
		}
	}

	// tooltip
	if (IsOccupiedByActor(cursorTileLocation)) {
		Actor& actor = *GetActorAtTile(cursorTileLocation);
		sf::Vector2i loc = actor.GetLocation();
		if (vision[loc.x][loc.y] == VisionState::InSight) {
			tooltip.SetTooltip(actor);
			sf::Vector2f tooltipSize = tooltip.GetSize();
			//sf::Vector2f tooltipPos{static_cast<float>(actor.GetLocation().x) * settings.TileSizeFloat, static_cast<float>(actor.GetLocation().y) * settings.TileSizeFloat };
			sf::Vector2f tooltipPos{ static_cast<float>(cursorTileLocation.x * settings.TileSizeInt), static_cast<float>(cursorTileLocation.y * settings.TileSizeInt) };
			tooltipPos.x -= roundf((tooltipSize.x / 2.f));
			tooltipPos.x += settings.TileSizeFloat / 2.f;
			tooltipPos.y -= roundf(tooltipSize.y);
			tooltip.SetPosition(tooltipPos, true);
			displayTooltip = true;
		}
	}
	else {
		displayTooltip = false;
	}

	minimap.UpdateMinimap(this);

	messageLog.Update(secondsPerUpdate);

	return GameState::Dungeon;
}

void DungeonScene::saveGame() {
	saveFile.Seed = masterSeed;
	saveFile.CurrentFloor = currentFloor;

	saveFile.Vision.clear();
	for (size_t x = 0; x < vision.size(); x++) {
		std::vector<int> col;
		for (size_t y = 0; y < vision[x].size(); y++) {
			col.push_back(static_cast<int>(vision[x][y]));
		}
		saveFile.Vision.push_back(col);
	}

	saveFile.Player.PlayerName = actors[0]->GetName();

	Player* player = static_cast<Player*>(actors[0].get());
	saveFile.Player.PlayerLevel = player->GetLevel();
	saveFile.Player.PlayerEXP = player->GetCurrentEXP();
	saveFile.Player.RaceID = static_cast<int>(player->GetRaceID());
	saveFile.Player.StatPoints = player->GetStatPoints();
	saveFile.Player.AbilityPoints = player->GetAbilityPoints();
	saveFile.Player.BonusPoints = player->GetBonusPoints();

	saveFile.Player.Abilities.clear();
	saveFile.Player.AbilityRanks.clear();
	auto playerAbilities = player->GetAbilities();
	saveFile.Player.Abilities.reserve(playerAbilities->size());
	saveFile.Player.AbilityRanks.reserve(playerAbilities->size());
	for (auto& ability : *playerAbilities) {
		saveFile.Player.Abilities.push_back(static_cast<int>(ability.GetAbilityID()));
		saveFile.Player.AbilityRanks.push_back(ability.GetCurrentRank());
	}

	saveFile.Actors.clear();
	saveFile.Actors.reserve(actors.size());
	for (auto& actor : actors) {
		ActorSave actorSave;
		sf::Vector2i loc = actor->GetLocation();

		actorSave.CurrentHP = actor->GetCurrentHP();
		actorSave.CurrentMP = actor->GetCurrentMP();
		actorSave.CurrentSP = actor->GetCurrentSP();
		actorSave.Exhaustion = actor->GetExhaustion();
		actorSave.XLocation = loc.x;
		actorSave.YLocation = loc.y;

		actorSave.AbilityCooldowns = actor->GetAbilityCooldowns();
		actorSave.AbilityCharges = actor->GetAbilityCharges();

		actorSave.AuraIDs = actor->GetAuraIDs();
		actorSave.AuraRanks = actor->GetAuraRanks();
		actorSave.AuraDurations = actor->GetAuraDurations();
		actorSave.AuraNextTicks = actor->GetAuraNextTicks();
		actorSave.AuraStacks = actor->GetAuraStacks();
		actorSave.AuraSource = actor->GetAuraSources();
		actorSave.AuraSSDamage = actor->GetAuraSnapshotDamage();
		actorSave.AuraSSCritChance = actor->GetAuraSnapshotCritChance();
		actorSave.AuraSSResPen = actor->GetAuraSnapshotResistancePen();
		actorSave.Flags = actor->GetFlags();

		if (!actor->IsPlayer()) {
			Monster* monster = static_cast<Monster*>(actor.get());
			actorSave.MonsterID = static_cast<int>(monster->GetMonsterID());
			actorSave.AIState = static_cast<int>(monster->GetAIState());
			actorSave.AIChaseTurns = monster->GetAIChaseTurns();
		}
		else {
			actorSave.MonsterID = 0;
			actorSave.AIState = 0;
			actorSave.AIChaseTurns = 0;
		}

		saveFile.Actors.push_back(actorSave);
	}

	auto spawnedArtifacts = records.GetSpawnedArtifacts();
	saveFile.SpawnedArtifacts.clear();
	saveFile.SpawnedArtifacts.reserve(spawnedArtifacts.size());
	for (auto& id : spawnedArtifacts) {
		saveFile.SpawnedArtifacts.push_back(static_cast<int>(id));
	}

	auto identifiedItems = records.GetIdentifiedItems();
	saveFile.IdentifiedItems.clear();
	saveFile.IdentifiedItems.reserve(identifiedItems.size());
	for (auto& id : identifiedItems) {
		saveFile.IdentifiedItems.push_back(static_cast<int>(id));
	}

	auto killCount = records.GetKillCounts();
	saveFile.SlainMonsters.clear();
	saveFile.SlainMonsters.reserve(killCount.size());
	saveFile.SlainMonsterCount.clear();
	saveFile.SlainMonsterCount.reserve(killCount.size());
	for (auto& kc : killCount) {
		saveFile.SlainMonsters.push_back(static_cast<int>(kc.first));
		saveFile.SlainMonsterCount.push_back(kc.second);
	}

	auto equipment = player->GetEquipment();
	for (size_t i = 0; i < equipment.size(); i++) {
		saveFile.Player.Equipment[i].ItemID = static_cast<int>(equipment[i].GetItemID());
		saveFile.Player.Equipment[i].Rarity = static_cast<int>(equipment[i].GetRarity());
		saveFile.Player.Equipment[i].StackSize = 1;
		auto statMods = equipment[i].GetRandomStatMods();
		saveFile.Player.Equipment[i].StatModTypes.clear();
		saveFile.Player.Equipment[i].StatModValues.clear();
		saveFile.Player.Equipment[i].StatModElements.clear();
		for (size_t j = 0; j < statMods.size(); j++) {
			saveFile.Player.Equipment[i].StatModTypes.push_back(static_cast<int>(statMods[j].statModType));
			saveFile.Player.Equipment[i].StatModValues.push_back(statMods[j].value);
			if (!statMods[j].elements.empty()) {
				saveFile.Player.Equipment[i].StatModElements.push_back(static_cast<int>(statMods[j].elements[0]));
			}
			else {
				saveFile.Player.Equipment[i].StatModElements.push_back(0);
			}
		}
	}

	saveFile.Loot.clear();
	saveFile.Loot.reserve(lootPiles.size());
	for (auto& l : lootPiles) {
		LootSave lootSave;
		sf::Vector2i loc = l.GetLocation();
		lootSave.XLocation = loc.x;
		lootSave.YLocation = loc.y;
		lootSave.Gold = l.GetGold();
		auto items = l.GetItems();
		for (auto& item : items) {
			ItemSave itemSave;
			itemSave.ItemID = static_cast<int>(item.GetItemID());
			itemSave.Rarity = static_cast<int>(item.GetRarity());
			itemSave.StackSize = 1;
			auto statMods = item.GetRandomStatMods();
			for (auto& sm : statMods) {
				itemSave.StatModTypes.push_back(static_cast<int>(sm.statModType));
				itemSave.StatModValues.push_back(sm.value);
				if (!sm.elements.empty()) {
					itemSave.StatModElements.push_back(static_cast<int>(sm.elements[0]));
				}
				else {
					itemSave.StatModElements.push_back(0);
				}
			}
			lootSave.Items.push_back(itemSave);
		}
		saveFile.Loot.push_back(lootSave);
	}

	saveFile.PlayerGold = inventory.GetGold();
	auto slots = inventory.GetInventory();
	for (size_t i = 0; i < slots.size(); i++) {
		saveFile.Inventory[i].StackSize = slots[i].StackCount;
		saveFile.Inventory[i].ItemID = static_cast<int>(slots[i].Item.GetItemID());
		saveFile.Inventory[i].Rarity = static_cast<int>(slots[i].Item.GetRarity());
		saveFile.Inventory[i].StatModTypes.clear();
		saveFile.Inventory[i].StatModValues.clear();
		saveFile.Inventory[i].StatModElements.clear();
		auto statMods = slots[i].Item.GetRandomStatMods();
		for (auto& sm : statMods) {
			saveFile.Inventory[i].StatModTypes.push_back(static_cast<int>(sm.statModType));
			saveFile.Inventory[i].StatModValues.push_back(sm.value);
			if (!sm.elements.empty()) {
				saveFile.Inventory[i].StatModElements.push_back(static_cast<int>(sm.elements[0]));
			}
			else {
				saveFile.Inventory[i].StatModElements.push_back(0);
			}
		}
	}

	saveFile.ShopItems.clear();
	saveFile.ShopItems.reserve(shops.size());
	for (auto& shop : shops) {
		auto items = shop.GetInventory();
		std::array<ItemSave, 24> itemSaves;
		for (size_t i = 0; i < items.size(); i++) {
			itemSaves[i].StackSize = 1;
			itemSaves[i].ItemID = static_cast<int>(items[i].GetItemID());
			itemSaves[i].Rarity = static_cast<int>(items[i].GetRarity());
			auto statMods = items[i].GetRandomStatMods();
			for (auto& sm : statMods) {
				itemSaves[i].StatModTypes.push_back(static_cast<int>(sm.statModType));
				itemSaves[i].StatModValues.push_back(sm.value);
				if (!sm.elements.empty()) {
					itemSaves[i].StatModElements.push_back(static_cast<int>(sm.elements[0]));
				}
				else {
					itemSaves[i].StatModElements.push_back(0);
				}
			}
		}
		saveFile.ShopItems.push_back(itemSaves);
	}

	auto shortcuts = playerHUD.GetShortcuts();
	for (size_t i = 0; i < shortcuts.size(); i++) {
		saveFile.ShortcutAbilities[i] = static_cast<int>(shortcuts[i].AbilityID);
	}

	// create save file
	{
		std::ofstream file("save.sav", std::ios::binary);
		cereal::BinaryOutputArchive archive(file);
		archive(saveFile);
	}
}

void DungeonScene::moveFloors(int floors) {
	currentFloor = std::max(1, currentFloor + floors);
	actors[0]->ClearAuras();
	changeFloors = false;
	generateDungeon();
}

void DungeonScene::buildVertexArray() {
	floorArray.setPrimitiveType(sf::Quads);
	floorArray.resize(floor.size() * floor[0].size() * 4);

	float sizeX = settings.TileSizeFloat;
	float sizeY = settings.TileSizeFloat;

	int i = 0;

	for (size_t x = 0; x < floor.size(); x++) {
		for (size_t y = 0; y < floor[x].size(); y++) {
			sf::Vertex* quad = &floorArray[i * 4];
			auto tile = floor[x][y];
			float texX = tile.SpriteNumber % 16 * sizeX;
			float texY = tile.SpriteNumber / 16 * sizeY;
			float posX = x * sizeX;
			float posY = y * sizeY;

			// quad cords
			// 0  1
			// 3  2
			quad[0].position = sf::Vector2f(posX, posY);
			quad[1].position = sf::Vector2f(posX + sizeX, posY);
			quad[2].position = sf::Vector2f(posX + sizeX, posY + sizeY);
			quad[3].position = sf::Vector2f(posX, posY + sizeY);

			// quad texture cords
			// 0  1
			// 3  2
			quad[0].texCoords = sf::Vector2f(texX, texY);
			quad[1].texCoords = sf::Vector2f(texX + sizeX, texY);
			quad[2].texCoords = sf::Vector2f(texX + sizeX, texY + sizeY);
			quad[3].texCoords = sf::Vector2f(texX, texY + sizeY);
			
			i++;
		}
	}
}

void DungeonScene::resetVision() {
	vision.clear();
	vision.resize(floor.size());
	for (size_t i = 0; i < vision.size(); i++) {
		vision[i].resize(floor[i].size());
	}
	auto test = TileMath::AreaOfEffect(startingPosition, actors[0]->GetSightRadius());

	for (size_t x = 0; x < vision.size(); x++) {
		for (size_t y = 0; y < vision[x].size(); y++) {
			if (std::find(test.begin(), test.end(), sf::Vector2i(static_cast<int>(x), static_cast<int>(y))) != test.end() && InLineOfSight(startingPosition, { static_cast<int>(x), static_cast<int>(y) })) {
				vision[x][y] = VisionState::InSight;
			}
			else {
				vision[x][y] = VisionState::Unexplored;
			}
		}
	}

	buildVisionVertexArray();
}

void DungeonScene::buildVisionVertexArray() {
	visionArray.setPrimitiveType(sf::Quads);
	visionArray.resize(vision.size() * vision[0].size() * 4);

	float sizeX = settings.TileSizeFloat;
	float sizeY = settings.TileSizeFloat;

	int i = 0;

	for (size_t x = 0; x < vision.size(); x++) {
		for (size_t y = 0; y < vision[x].size(); y++) {
			sf::Vertex* quad = &visionArray[i * 4];
			float texX = 0.f;
			float texY = 0.f;
			float posX = x * sizeX;
			float posY = y * sizeY;

			// quad cords
			// 0  1
			// 3  2
			quad[0].position = sf::Vector2f(posX, posY);
			quad[1].position = sf::Vector2f(posX + sizeX, posY);
			quad[2].position = sf::Vector2f(posX + sizeX, posY + sizeY);
			quad[3].position = sf::Vector2f(posX, posY + sizeY);

			// quad texture cords
			// 0  1
			// 3  2
			quad[0].texCoords = sf::Vector2f(texX, texY);
			quad[1].texCoords = sf::Vector2f(texX + sizeX, texY);
			quad[2].texCoords = sf::Vector2f(texX + sizeX, texY + sizeY);
			quad[3].texCoords = sf::Vector2f(texX, texY + sizeY);

			
			if (vision[x][y] == VisionState::Unexplored) {
				quad[0].color = sf::Color(0, 0, 0, 255);
				quad[1].color = sf::Color(0, 0, 0, 255);
				quad[2].color = sf::Color(0, 0, 0, 255);
				quad[3].color = sf::Color(0, 0, 0, 255);
			}
			else if (vision[x][y] == VisionState::OutOfSight) {
				quad[0].color = sf::Color(0, 0, 0, 127);
				quad[1].color = sf::Color(0, 0, 0, 127);
				quad[2].color = sf::Color(0, 0, 0, 127);
				quad[3].color = sf::Color(0, 0, 0, 127);
			}
			else {
				quad[0].color = sf::Color(0, 0, 0, 0);
				quad[1].color = sf::Color(0, 0, 0, 0);
				quad[2].color = sf::Color(0, 0, 0, 0);
				quad[3].color = sf::Color(0, 0, 0, 0);
			}

			i++;
		}
	}
}

void DungeonScene::buildTargetingVertexArray() {
	targetingArray.setPrimitiveType(sf::Quads);

	// determines color of tile
	enum class TargetType {
		Undefined = 0,
		Range = 1,
		Area = 2,
		ExtraArea = 3,
		ProjectilePath = 4,
	};

	std::vector<std::pair<sf::Vector2i, TargetType>> allAreas;
	sf::Vector2i targetTile = cursorTileLocation;
	std::vector<sf::Vector2i> range = targetingAbility->GetRange(actors[0].get(), this);

	// if the cursor isn't in the targeting area, find the closest tile in range
	targetTile = TileMath::Closest(targetTile, range);

	std::vector<sf::Vector2i> area = targetingAbility->GetTargetArea(targetTile, actors[0].get(), this);
	std::vector<sf::Vector2i> extraArea; // todo
	std::vector<sf::Vector2i> projectilePath; // todo

	if (targetingAbility->IsProjectile()) {
		projectilePath = GetProjectilePath(actors[0]->GetLocation(), targetTile);
	}

	allAreas.reserve(range.size() + area.size() + extraArea.size() + projectilePath.size());

	for (auto t : area) {
		allAreas.push_back({ t, TargetType::Area });
	}

	if (targetingAbility->IsProjectile()) {
		projectilePath.erase(projectilePath.begin()); // remove tile under actor for looks
		for (auto t : projectilePath) {
			// do not allow range tiles to overlap with target area tiles
			if (std::find_if(allAreas.begin(), allAreas.end(), [tile = t](std::pair<sf::Vector2i, TargetType>& p) {return p.first == tile; }) == allAreas.end()) {
				allAreas.push_back({ t, TargetType::ProjectilePath });
			}
		}
	}

	for (auto t : range) {
		// do not allow range tiles to overlap with target area tiles
		if (std::find_if(allAreas.begin(), allAreas.end(), [tile = t](std::pair<sf::Vector2i, TargetType>& p) {return p.first == tile; }) == allAreas.end()) {
			allAreas.push_back({ t, TargetType::Range });
		}
	}
	allAreas.shrink_to_fit();

	// Building of the vertex.
	size_t i = 0;
	targetingArray.resize(allAreas.size() * 4);

	float tileSize = settings.TileSizeFloat;

	for (const auto& tile : allAreas) {
		float texX = 0.f;
		float texY = 0.f;

		sf::Vertex* quad = &targetingArray[i * 4];

		float posX = static_cast<float>(tile.first.x) * tileSize;
		float posY = static_cast<float>(tile.first.y) * tileSize;

		// quad cords
		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(posX, posY);
		quad[1].position = sf::Vector2f(posX + tileSize, posY);
		quad[2].position = sf::Vector2f(posX + tileSize, posY + tileSize);
		quad[3].position = sf::Vector2f(posX, posY + tileSize);

		// tile color
		switch (tile.second) {
		case TargetType::Range:
			texX = 3.f * tileSize;
			texY = 0.f;
			break;
		case TargetType::Area:
			texX = 0.f;
			texY = 0.f;
			break;
		case TargetType::ProjectilePath:
			texX = 0.f;
			texY = tileSize;
			break;
		default:
			break;
		}

		// quad texture cords
		// 0  1
		// 3  2
		quad[0].texCoords = sf::Vector2f(texX, texY);
		quad[1].texCoords = sf::Vector2f(texX + tileSize, texY);
		quad[2].texCoords = sf::Vector2f(texX + tileSize, texY + tileSize);
		quad[3].texCoords = sf::Vector2f(texX, texY + tileSize);

		// quad colors
		// 0  1
		// 3  2
		if (settings.Tileset == "ascii") {
			quad[0].color = sf::Color(255, 255, 255, 255);
			quad[1].color = sf::Color(255, 255, 255, 255);
			quad[2].color = sf::Color(255, 255, 255, 255);
			quad[3].color = sf::Color(255, 255, 255, 255);
		}
		else {
			quad[0].color = sf::Color(255, 255, 255, 127);
			quad[1].color = sf::Color(255, 255, 255, 127);
			quad[2].color = sf::Color(255, 255, 255, 127);
			quad[3].color = sf::Color(255, 255, 255, 127);
		}
		i++;
	}
}