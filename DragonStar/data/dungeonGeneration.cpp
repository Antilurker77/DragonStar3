// ================================================================
//
// dungeonGeneration.cpp
//
// ================================================================

#include "../scene/dungeonScene.hpp"

#include <iomanip>
#include <sstream>
#include <random>
#include "../core/random.hpp"
#include "../core/records.hpp"
#include "../entity/monster.hpp"

void DungeonScene::generateDungeon() {
	sf::Clock clock;
	std::mt19937_64 mt(floorSeeds[currentFloor - 1]);
	messageLog.AddMessage("#aaaaaa Generating Floor " + std::to_string(currentFloor) + "...");
	std::stringstream ss;
	ss << "#aaaaaa Dungeon Seed: " << std::setfill('0') << std::setw(16) << std::hex << floorSeeds[currentFloor - 1] << std::dec;
	messageLog.AddMessage(ss.str());

	floor.clear();
	startingPosition = { -1, -1 };
	actors[0]->Warp(startingPosition);

	actors.resize(1);

	// Pick which generation time to use.
	// More will be added later.
	if (currentFloor == 100) {
		dgStandard(mt);
	}
	else {
		dgStandard(mt);
	}

	// spawn shops
	spawnShops();

	// spawn monsters
	spawnMonsters();

	// spawn random loot
	spawnLoot();

	// player starting position
	bool foundPostition = false;
	while (!foundPostition) {
		sf::Vector2<size_t> randLoc(Random::RandomSizeT(0, floor.size() - 1, mt), Random::RandomSizeT(0, floor[0].size() - 1, mt));
		sf::Vector2i randLocInt(static_cast<int>(randLoc.x), static_cast<int>(randLoc.y));
		if (floor[randLoc.x][randLoc.y].IsPassible && floor[randLoc.x][randLoc.y].TileType != TileID::DownStairs && !IsOccupiedByActor(randLocInt)) {
			foundPostition = true;
			startingPosition = randLocInt;
		}
	}

	buildVertexArray();

	actors[0]->Warp(startingPosition);
	resetVision();

	messageLog.AddMessage("#aaaaaa Dungeon Gen Time: " + std::to_string(clock.getElapsedTime().asSeconds() * 1000.f) + "ms");
}

void DungeonScene::spawnShops() {
	std::mt19937_64 mt(floorSeeds[currentFloor - 1]);

	shops.clear();

	size_t numOfShops = Random::RandomSizeT(1, 2, mt);
	size_t shopsSpawned = 0;

	while (shopsSpawned < numOfShops) {
		sf::Vector2<size_t> randLoc(Random::RandomSizeT(1, floor.size() - 2, mt), Random::RandomSizeT(1, floor[0].size() - 2, mt));
		sf::Vector2i randLocInt(static_cast<int>(randLoc.x), static_cast<int>(randLoc.y));

		// spawn on top of random wall tile
		if (floor[randLoc.x][randLoc.y].TileType == TileID::StoneBrickWall) {
			// check if reachable
			if (floor[randLoc.x + 1][randLoc.y].TileType == TileID::StoneFloor ||
				floor[randLoc.x - 1][randLoc.y].TileType == TileID::StoneFloor ||
				floor[randLoc.x][randLoc.y + 1].TileType == TileID::StoneFloor ||
				floor[randLoc.x][randLoc.y - 1].TileType == TileID::StoneFloor) {
				Shop shop(randLocInt, static_cast<int>(currentFloor), Random::RandomSeed(mt));
				shops.push_back(shop);
				shopsSpawned++;
			}
		}
	}
}

void DungeonScene::spawnMonsters() {
	std::mt19937_64 mt(floorSeeds[currentFloor - 1]);

	actors.resize(1);
	actors.shrink_to_fit();
	actors.reserve(512);


	size_t numOfWalkableTiles = 0;
	for (auto& v : floor) {
		for (auto& t : v) {
			numOfWalkableTiles += t.IsPassible ? 1 : 0;
		}
	}
	messageLog.AddMessage("#aaaaaa Number of Walkable Tiles: " + std::to_string(numOfWalkableTiles));

	size_t numOfEncounters = numOfWalkableTiles / 35;
	messageLog.AddMessage("#aaaaaa Generating " + std::to_string(numOfEncounters) + " encounters.");
	std::vector<Encounter> choosenEncounters;

	// choosing encounters
	int encounterSum = 0;
	std::vector<Encounter> possibleEncounters;
	possibleEncounters.reserve(encounterTable.size());

	for (auto& encounter : encounterTable) {
		if (currentFloor >= encounter.MinDepth && currentFloor <= encounter.MaxDepth) {
			encounterSum += encounter.Weight;
			possibleEncounters.push_back(encounter);
		}
	}

	for (size_t i = 0; i < numOfEncounters; i++) {
		int encounterRoll = Random::RandomInt(1, encounterSum);

		for (auto& encounter : possibleEncounters) {
			encounterRoll -= encounter.Weight;
			if (encounterRoll <= 0) {
				choosenEncounters.push_back(encounter);
				break;
			}
		}
	}

	// add unique encounters
	size_t pickedUniques = 0;
	size_t numOfUniqueEncounters = 1; // todo: number of uniques per floor
	std::vector<Encounter> possibleUniques;
	int uniqueSum = 0;

	for (auto e : uniqueEncounterTable) {
		if (!records.HasKilled(e.MonsterOdds[0].first) && currentFloor >= e.MinDepth && currentFloor <= e.MaxDepth) {
			possibleUniques.push_back(e);
			uniqueSum += e.Weight;
		}
	}
	numOfUniqueEncounters = std::min(possibleUniques.size(), numOfUniqueEncounters);
	messageLog.AddMessage("#aaaaaa Generating " + std::to_string(numOfUniqueEncounters) + " unique encounters.");

	for (size_t i = 0; i < numOfUniqueEncounters; i++) {
		int uniqueRoll = Random::RandomInt(1, uniqueSum);
		for (auto& unique : possibleUniques) {
			uniqueRoll -= unique.Weight;
			if (uniqueRoll <= 0) {
				choosenEncounters.push_back(unique);
				break;
			}
		}
	}


	int mapWidth = static_cast<int>(floor.size());
	int mapHeight = static_cast<int>(floor[0].size());

	// placement of monsters
	size_t index = 1; // ID tag for monsters, required when loading a game so that auras can find their source actors
	size_t encounterIndex = 1; // ID tag for monster groups
	for (auto& e : choosenEncounters) {
		// determine how many monsters of group spawn
		std::vector<MonsterID> monstersToSpawn;
		for (auto& p : e.MonsterOdds) {
			if (Random::RandomInt(1, 1000, mt) <= p.second) {
				monstersToSpawn.push_back(p.first);
			}
		}

		// pick the location
		std::vector<sf::Vector2i> spawnArea;
		bool foundSpot = false;
		while (!foundSpot) {
			spawnArea.clear();
			sf::Vector2i loc = { Random::RandomInt(0, mapWidth - 1, mt), Random::RandomInt(0, mapHeight - 1, mt) };

			// determine size of area
			int radius = 0;
			size_t groupSize = monstersToSpawn.size();
			if (groupSize == 1) {
				radius = 0;
			}
			else if (groupSize >= 2 && groupSize <= 5) {
				radius = 100;
			}
			else if (groupSize >= 6 && groupSize <= 9) {
				radius = 150;
			}
			else if (groupSize >= 10 && groupSize <= 13) {
				radius = 200;
			}
			else if (groupSize >= 14 && groupSize <= 21) {
				radius = 250;
			}
			else {
				radius = static_cast<int>(groupSize) * 10;
			}

			std::vector<sf::Vector2i> checkArea = TileMath::AreaOfEffect(loc, radius);
			for (auto& t : checkArea) {
				if (t.x < mapWidth && t.x >= 0 && t.y < mapHeight && t.y >= 0) {
					if (floor[t.x][t.y].IsPassible && !IsOccupiedByActor(t)) {
						spawnArea.emplace_back(t);
					}
				}
			}
			if (spawnArea.size() >= monstersToSpawn.size()) {
				foundSpot = true;
			}
		}

		// create the monsters
		std::shuffle(spawnArea.begin(), spawnArea.end(), mt);
		for (size_t i = 0; i < monstersToSpawn.size(); i++) {
			actors.emplace_back(std::make_unique<Monster>(monstersToSpawn[i], spawnArea[i], index, encounterIndex));
			index++;
		}
		encounterIndex++;
	}
}

void DungeonScene::spawnLoot() {
	std::mt19937_64 mt(floorSeeds[currentFloor - 1]);

	lootPiles.clear();
	lootPiles.shrink_to_fit();

	int mapWidth = static_cast<int>(floor.size());
	int mapHeight = static_cast<int>(floor[0].size());
	size_t numOfWalkableTiles = 0;
	for (auto& v : floor) {
		for (auto& t : v) {
			numOfWalkableTiles += t.IsPassible ? 1 : 0;
		}
	}

	size_t numOfLootPiles = numOfWalkableTiles / 40 * (currentFloor + 99) / 100;
	messageLog.AddMessage("#aaaaaa Generating " + std::to_string(numOfLootPiles) + " piles of loot.");
	lootPiles.reserve(numOfLootPiles + actors.size());

	// Generate Loot Piles
	for (size_t i = 0; i < numOfLootPiles; i++) {
		bool foundSpot = false;
		sf::Vector2i loc;
		while (!foundSpot) {
			loc.x = Random::RandomInt(0, mapWidth - 1, mt);
			loc.y = Random::RandomInt(0, mapHeight - 1, mt);
			if (floor[loc.x][loc.y].IsPassible && !IsOccupiedByLoot(loc)) {
				foundSpot = true;
			}
		}

		if (Random::RandomInt(1, 100, mt) >= 50) {
			int gold = Random::RandomInt(1, 5 + currentFloor, mt);
			lootPiles.push_back(Loot(loc, gold));
		}
		else {
			Item item;
			item.InitRandomItem(currentFloor);
			lootPiles.push_back(Loot(loc, { item }));
		}

		
	}
}

void DungeonScene::dgStandard(std::mt19937_64& mt) {
	sf::Vector2i bounds(48, 48); // 64 x 36
	std::vector<std::vector<TileID>> tiles;

	// Set up map size and fill with wall tiles.
	floor.resize(bounds.x);
	for (auto& v : floor) {
		v.resize(bounds.y);
	}

	tiles.resize(bounds.x);
	for (auto& v : tiles) {
		v.resize(bounds.y);
		std::fill(v.begin(), v.end(), TileID::StoneBrickWall);
	}

	// Number of rooms.
	size_t numberOfRooms = Random::RandomSizeT(12, 16, mt);
	std::vector<sf::Rect<size_t>> rooms;
	rooms.reserve(numberOfRooms);

	// Room placement, try to not overlapp.
	for (size_t i = 0; i < numberOfRooms; i++) {
		bool trying = true;
		size_t attempts = 0;
		while (trying && attempts < 10000) {
			attempts++;
			sf::Vector2<size_t> size(Random::RandomSizeT(3, 13, mt), Random::RandomSizeT(3, 13, mt));
			sf::Vector2<size_t> pos(Random::RandomSizeT(1, bounds.x - size.x - 1, mt), Random::RandomSizeT(1, bounds.y - size.y - 1, mt));
			sf::Rect<size_t> room(pos.x, pos.y, size.x, size.y);
			bool failed = false;
			// Try to not overlap with existing tiles.
			for (size_t x = 0; x < tiles.size(); x++) {
				for (size_t y = 0; y < tiles[x].size(); y++) {
					if (tiles[x][y] == TileID::StoneFloor) {
						if (room.contains(x, y) || room.contains(x + 1, y) || room.contains(x - 1, y) || room.contains(x, y + 1) || room.contains(x, y - 1) || room.contains(x + 1, y + 1) || room.contains(x + 1, y - 1) || room.contains(x - 1, y - 1)) {
							failed = true;
							break;
						}
					}
				}

				if (failed) {
					break;
				}
			}

			if (failed) {
				continue;
			}

			// No overlap, add tiles.
			for (size_t i = pos.x; i < pos.x + size.x; i++) {
				for (size_t j = pos.y; j < pos.y + size.y; j++) {
					tiles[i][j] = TileID::StoneFloor;
				}
			}
			rooms.emplace_back(room);
			//messageLog.AddMessage("Room " + std::to_string(i) + ": " + std::to_string(room.left) + ", " + std::to_string(room.top) + ", " + std::to_string(room.width) + ", " + std::to_string(room.height));
			trying = false;
		}
	}

	// Hallways.
	// Connect rooms to a nearby room.
	std::vector<std::pair<size_t, size_t>> connections;

	for (size_t i = 0; i < rooms.size(); i++) {
		sf::Vector2i center(static_cast<int>(rooms[i].left + rooms[i].width / 2), static_cast<int>(rooms[i].top + rooms[i].height / 2));
		size_t connectTo = 0;
		double shortestDistance = std::numeric_limits<double>::max();
		// Find the closest room. Comparing by centers.
		for (size_t j = 0; j < rooms.size(); j++) {
			if (i != j) {
				sf::Vector2i testCenter(static_cast<int>(rooms[j].left + rooms[j].width / 2), static_cast<int>(rooms[j].top + rooms[j].height / 2));
				double testDistance = TileMath::Distance(center, testCenter);
				std::pair<size_t, size_t> testPair{ std::min(i, j), std::max(i, j) };
				if (testDistance < shortestDistance && std::find(connections.begin(), connections.end(), testPair) == connections.end()) {
					shortestDistance = testDistance;
					connectTo = j;
				}
			}
		}

		connections.push_back({ std::min(i, connectTo), std::max(i, connectTo) });

		// Create the corridor.
		sf::Vector2<size_t> start(Random::RandomSizeT(rooms[i].left, rooms[i].left + rooms[i].width - 1, mt), Random::RandomSizeT(rooms[i].top, rooms[i].top + rooms[i].height - 1, mt));
		sf::Vector2<size_t> end(Random::RandomSizeT(rooms[connectTo].left, rooms[connectTo].left + rooms[connectTo].width - 1, mt), Random::RandomSizeT(rooms[connectTo].top, rooms[connectTo].top + rooms[connectTo].height - 1, mt));

		
		int dir = Random::RandomInt(0, 1, mt);
		if (dir == 0) {
			for (size_t x = std::min(start.x, end.x); x <= std::max(start.x, end.x); x++) {
				tiles[x][start.y] = TileID::StoneFloor;
			}

			for (size_t y = std::min(start.y, end.y); y <= std::max(start.y, end.y); y++) {
				tiles[end.x][y] = TileID::StoneFloor;
			}
		}
		else {
			for (size_t x = std::min(start.x, end.x); x <= std::max(start.x, end.x); x++) {
				tiles[x][end.y] = TileID::StoneFloor;
			}

			for (size_t y = std::min(start.y, end.y); y <= std::max(start.y, end.y); y++) {
				tiles[start.x][y] = TileID::StoneFloor;
			}
		}
		
	}

	// Place stairs
	bool placingStairs = true;
	sf::Vector2<size_t> stairLocation{};
	while (placingStairs) {
		sf::Vector2<size_t> randPos(Random::RandomSizeT(1, bounds.x - 1, mt), Random::RandomSizeT(1, bounds.y - 1, mt));
		if (tiles[randPos.x][randPos.y] == TileID::StoneFloor) {
			tiles[randPos.x][randPos.y] = TileID::DownStairs;
			stairLocation = randPos;
			placingStairs = false;
		}
	}

	// Put tiles into floor.
	for (size_t x = 0; x < tiles.size(); x++) {
		for (size_t y = 0; y < tiles[x].size(); y++) {
			floor[x][y] = TileInfo::GetTile(tiles[x][y]);
		}
	}

	// Check for orphaned rooms.
	// This is done after the floor assignment because Pathfind() requires the floor to compute.
	for (size_t i = 0; i < rooms.size(); i++) {
		sf::Vector2<size_t> start{ rooms[i].left, rooms[i].top };
		if (start != stairLocation) {
			auto path = Pathfind(start, stairLocation);
			if (path.empty()) {
				// Find the closest room it can't path too.
				sf::Vector2i center(static_cast<int>(rooms[i].left + rooms[i].width / 2), static_cast<int>(rooms[i].top + rooms[i].height / 2));
				size_t connectTo = 0;
				double shortestDistance = std::numeric_limits<double>::max();
				for (size_t j = 0; j < rooms.size(); j++) {
					if (i != j) {
						sf::Vector2i testCenter(static_cast<int>(rooms[j].left + rooms[j].width / 2), static_cast<int>(rooms[j].top + rooms[j].height / 2));
						// want to connect it to rooms it can't reach
						auto testPath = Pathfind(center, testCenter);
						if (testPath.empty()) {
							double checkDistance = TileMath::Distance(center, testCenter);
							if (checkDistance < shortestDistance) {
								shortestDistance = checkDistance;
								connectTo = j;
							}
						}
					}
				}


				connections.push_back({ std::min(i, connectTo), std::max(i, connectTo) });

				// Create the corridor.
				sf::Vector2<size_t> start(Random::RandomSizeT(rooms[i].left, rooms[i].left + rooms[i].width - 1, mt), Random::RandomSizeT(rooms[i].top, rooms[i].top + rooms[i].height - 1, mt));
				sf::Vector2<size_t> end(Random::RandomSizeT(rooms[connectTo].left, rooms[connectTo].left + rooms[connectTo].width - 1, mt), Random::RandomSizeT(rooms[connectTo].top, rooms[connectTo].top + rooms[connectTo].height - 1, mt));


				int dir = Random::RandomInt(0, 1, mt);
				if (dir == 0) {
					for (size_t x = std::min(start.x, end.x); x <= std::max(start.x, end.x); x++) {
						floor[x][start.y] = TileInfo::GetTile(TileID::StoneFloor);
					}

					for (size_t y = std::min(start.y, end.y); y <= std::max(start.y, end.y); y++) {
						floor[end.x][y] = TileInfo::GetTile(TileID::StoneFloor);
					}
				}
				else {
					for (size_t x = std::min(start.x, end.x); x <= std::max(start.x, end.x); x++) {
						floor[x][end.y] = TileInfo::GetTile(TileID::StoneFloor);
					}

					for (size_t y = std::min(start.y, end.y); y <= std::max(start.y, end.y); y++) {
						floor[start.x][y] = TileInfo::GetTile(TileID::StoneFloor);
					}
				}

				i = 0; // Start loop from beginning again, as room can still be oprhaned if it connected to another orphaned room.

			}
		}

	}

	// Add additional corridors to break up the linearity of the dungeon.
	size_t numberOfExtraCorridors = Random::RandomSizeT(3, 5, mt);

	size_t attempts = 0;
	size_t corridorsAdded = 0;

	while (corridorsAdded < numberOfExtraCorridors && attempts < 10000) {
		size_t startingRoom = Random::RandomSizeT(0, rooms.size() - 1, mt);
		size_t endingRoom = Random::RandomSizeT(0, rooms.size() - 1, mt);
		if (startingRoom != endingRoom) {
			// Make sure the rooms aren't already connected.
			std::pair<size_t, size_t> connection = { std::min(startingRoom, endingRoom), std::max(startingRoom, endingRoom) };
			if (std::find(connections.begin(), connections.end(), connection) == connections.end()) {
				connections.push_back(connection);

				// Create the corridor.
				sf::Vector2<size_t> start(Random::RandomSizeT(rooms[startingRoom].left, rooms[startingRoom].left + rooms[startingRoom].width - 1, mt), Random::RandomSizeT(rooms[startingRoom].top, rooms[startingRoom].top + rooms[startingRoom].height - 1, mt));
				sf::Vector2<size_t> end(Random::RandomSizeT(rooms[endingRoom].left, rooms[endingRoom].left + rooms[endingRoom].width - 1, mt), Random::RandomSizeT(rooms[endingRoom].top, rooms[endingRoom].top + rooms[endingRoom].height - 1, mt));


				int dir = Random::RandomInt(0, 1, mt);
				if (dir == 0) {
					for (size_t x = std::min(start.x, end.x); x <= std::max(start.x, end.x); x++) {
						floor[x][start.y] = TileInfo::GetTile(TileID::StoneFloor);
					}

					for (size_t y = std::min(start.y, end.y); y <= std::max(start.y, end.y); y++) {
						floor[end.x][y] = TileInfo::GetTile(TileID::StoneFloor);
					}
				}
				else {
					for (size_t x = std::min(start.x, end.x); x <= std::max(start.x, end.x); x++) {
						floor[x][end.y] = TileInfo::GetTile(TileID::StoneFloor);
					}

					for (size_t y = std::min(start.y, end.y); y <= std::max(start.y, end.y); y++) {
						floor[start.x][y] = TileInfo::GetTile(TileID::StoneFloor);
					}
				}

				corridorsAdded++;
				continue;
			}
		}

		attempts++;
	}
}