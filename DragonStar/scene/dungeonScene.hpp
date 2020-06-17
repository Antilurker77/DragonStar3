// ================================================================
//
// dungeonScene.hpp
// 
// Scene that controls the dungeon, including players and monsters.
//
// ================================================================

#pragma once

class Actor;
class Camera;

enum class GroundEffectID;
enum class MonsterID;
enum class RaceID;
enum class StarterID;

#include <memory>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../command/moveCommand.hpp"
#include "../core/gameState.hpp"
#include "../core/saveFile.hpp"
#include "../core/tileMath.hpp"
#include "../data/groundEffect.hpp"
#include "../data/tile.hpp"
#include "../entity/actor.hpp"
#include "../entity/loot.hpp"
#include "../entity/shop.hpp"
#include "../ui/cursorContainer.hpp"
#include "../ui/inspectWindow.hpp"
#include "../ui/inventory.hpp"
#include "../ui/learnAbilityWindow.hpp"
#include "../ui/lootWindow.hpp"
#include "../ui/messageLog.hpp"
#include "../ui/minimap.hpp"
#include "../ui/playerHUD.hpp"
#include "../ui/shopWindow.hpp"
#include "../ui/statWindow.hpp"
#include "../ui/spellbook.hpp"
#include "../ui/tooltip.hpp"

typedef std::unique_ptr<Actor> ActorPtr;

enum class VisionState {
	Unexplored,
	OutOfSight,
	InSight
};

struct Encounter {
	int MinDepth = 0;
	int MaxDepth = 0;
	int Weight = 1000;
	std::vector<std::pair<MonsterID, int>> MonsterOdds;
};

class DungeonScene {
public:
	DungeonScene();

	// Sets up the player and their starting inventory.
	void SetUp(std::string name, RaceID race, StarterID startingGear);

	// Sets the name of the player character.
	void SetPlayerName(std::string name);

	// Creates the seeds for all dungeon floors and generates the current dungeon floor.
	void GenerateSeeds(uint64_t seed);

	// Loads the current save file. Returns true if the file was loaded.
	bool LoadGame();

	// Sets the camera reference.
	void SetCamera(Camera* c);

	// Reads input.
	void ReadInput(sf::RenderWindow& window);

	// Updates the game world.
	GameState Update(float secondsPerUpdate);

	// Updates vision based on the player position.
	// Called from move commands.
	void UpdateVision();

	// Draws the dungeon and actors.
	void DrawWorld(sf::RenderWindow& window, float timeRatio);

	// Draws the UI.
	void DrawUI(sf::RenderWindow& window, float timeRatio);

	// Alerts all monsters in an encounter group.
	void AlertGroup(size_t encounterIndex);

	// Returns the current floor the player is on.
	int GetCurrentFloor();

	// Activates targeting mode for an ability.
	void SetTargettingMode(AbilityID id);

	// Activates targeting mode for an item.
	void SetTargettingMode(Item& item, size_t index);

	// Opens the ability learning window.
	void OpenLearnAbilityWindow(Item* tome);

	// Returns the size of the dungeon.
	sf::Vector2<size_t> GetDungeonSize();

	// Returns the optimal path between two points. If no path is found, vector will be empty.
	std::vector<sf::Vector2i> Pathfind(sf::Vector2i start, sf::Vector2i end);

	// Returns the optimal path between two points. If no path is found, vector will be empty.
	std::vector<sf::Vector2i> Pathfind(sf::Vector2<size_t> start, sf::Vector2<size_t> end);

	// Returns the optinal path between two points. If no path is found, vector will be empty.
	std::vector<sf::Vector2i> Pathfind(sf::Vector2i start, sf::Vector2i end, Actor* actor);

	// Returns the optimal path between two points. If no path if found, vector will be empty.
	std::vector<sf::Vector2i> Pathfind(sf::Vector2i start, sf::Vector2i end, bool canFly, bool canSwim, bool canTunnel);

	// Returns the movement cost of a given path.
	int GetPathCost(std::vector<sf::Vector2i>& path);

	// Returns the heuristic distance between two tiles.
	int GetHeuristicDistance(sf::Vector2i start, sf::Vector2i end, bool negativeOffset);

	// Gets a path for the projectile to travel. If the path is blocked, it returns the path that travels the farthest.
	std::vector<sf::Vector2i> GetProjectilePath(sf::Vector2i start, sf::Vector2i goal);

	// Returns the point of impact for a projectile.
	sf::Vector2i GetProjectileImpactTile(sf::Vector2i start, sf::Vector2i goal, bool isPlayer);

	// Returns the player actor, which should always be the first actor in the vector.
	Actor* GetPlayer();

	// Returns the actor at the designated position.
	Actor* GetActorAtTile(sf::Vector2i tile);

	// Returns the actor at the given index.
	Actor* GetActorByIndex(size_t index);

	// Returns all the actors in the designated area.
	std::vector<Actor*> GetActorsInArea(std::vector<sf::Vector2i>& area);

	// Returns the loot pile at the designated location.
	Loot* GetLootAtLocation(sf::Vector2i tile);

	// Returns the shop at the designated location.
	Shop* GetShopAtLocation(sf::Vector2i tile);

	// Returns the vision state of the specified tile.
	VisionState GetTileVisionState(sf::Vector2i tile);

	// Returns the vision state of the specified tile.
	VisionState GetTileVisionState(sf::Vector2<size_t> tile);

	// For the Magic Mapping scroll. Reveals all wall tiles adjacent to floor tiles.
	void MagicMap();

	// Returns true if there is an actor at the designated tile.
	bool IsOccupiedByActor(sf::Vector2i tile);

	// Returns true if there is loot at the designated tile.
	bool IsOccupiedByLoot(sf::Vector2i tile);

	// Returns true if there is a shop at the designated tile.
	bool IsOccupiedByShop(sf::Vector2i tile);

	// Returns true if a given actor can walk on the designated tile.
	bool IsWalkable(Actor* actor, sf::Vector2i tile);

	// Returns true if a tile is walkable.
	bool IsWalkable(bool canFly, bool canSwim, bool canTunnel, sf::Vector2i tile);

	// Returns true if the tile contains down stairs.
	bool IsDownStairs(sf::Vector2i tile);

	// Returns true if the tile is opeque.
	bool IsOpeque(sf::Vector2i tile);

	// Returns true if one tile is within line of sight of the other.
	bool InLineOfSight(sf::Vector2i start, sf::Vector2i end);

	// Creates a ground effect at the given location.
	void CreateGroundEffect(GroundEffectID id, int rank, Actor* user, int ssDamage, int ssCritChance, int ssResPen, sf::Vector2i location);

	// Creates a loot pile with the specified amount of gold. If a loot pile is already in 
	// that location, it is added to the existing pile instead.
	void DropLoot(sf::Vector2i location, int gold);

	// Creates a loot pile with the specified amount of gold and items. If a loot pile is
	// already in that location, it is added to the existing pile instead.
	void DropLoot(sf::Vector2i location, int gold, std::vector<Item> items);

	// Creates a loot pile with the specified item. Stacks drop multiple items. If a loot
	// piles is already in that location, add to the existing pile instead.
	void DropLoot(sf::Vector2i location, Item item, int stackSize);

	// Checks to see if there is a draggable item in a UI element at the cursor location.
	// If so, transfer the item to the cursor container.
	ItemID GetDraggableItem(sf::Vector2i location, Item& item, int& stackCount);

	// Releases the item on the cursor.
	void ReleaseDraggableItem(sf::Vector2i location, ItemID& id, Item& item, int stackCount);

	// Checks to see if there is a draggable ability in a UI element at the cursor location.
	AbilityID GetDraggableAbility(sf::Vector2i location);

	// Releases the ability on the cursor.
	void ReleaseDraggableAbility(sf::Vector2i location, AbilityID& id);

	// Puts the inventory in identification mode.
	void SetIdentifyMode(bool usingScroll);

private:
	void updateWorld(float secondsPerUpdate);
	GameState updateUI(float secondsPerUpdate);

	// Saves the current game state into the save file struct.
	void saveGame();

	// Moves the actor X floors and generates the dungeon.
	// Negative values will move the player up.
	void moveFloors(int floors);

	// Builds a vertex array to display the dungeon.
	void buildVertexArray();

	// Resets exploration.
	void resetVision();

	// Builds the vertex array for exploration.
	void buildVisionVertexArray();

	// Builds the targeting vertex array.
	void buildTargetingVertexArray();

	// Builds the ground effect vertex array.
	void buildGroundEffectVertexArray();

	// =============================
	// === dungeonGeneration.cpp ===
	// =============================

	// Generates the dungeon, including monsters and loot.
	void generateDungeon();

	// Part of dungeon generation. Clears existing shops and spawns new shops.
	void spawnShops();

	// Part of dungeon generation. Clears existing monsters and spawns new monsters.
	void spawnMonsters();

	// Part of dungeon generation. Clears existing loot piles and spawns new random loot piles.
	void spawnLoot();

	// General dungeon type.
	void dgStandard(std::mt19937_64& mt);

	// ============================
	// ============================

	// ==================
	const int totalFloors = 100;
	const int victoryFloor = 101;
	uint64_t masterSeed = 0ull;
	std::vector<uint64_t> floorSeeds;

	int currentFloor = 1;
	std::vector<std::vector<Tile>> floor;
	std::vector<std::vector<VisionState>> vision;
	sf::Vector2i startingPosition;
	sf::VertexArray floorArray;
	sf::VertexArray visionArray;
	sf::VertexArray targetingArray;
	sf::VertexArray groundEffectArray;
	sf::Texture* tileset;
	sf::Texture* visionTexture;
	sf::Texture* targetTexutre;
	sf::Texture* groundEffectTexture;

	std::vector<ActorPtr> actors; // index 0 is always assumed to be the player
	std::vector<GroundEffect> groundEffects;
	std::vector<Loot> lootPiles;
	std::vector<Shop> shops;

	Actor* activeActor = nullptr;
	CommandPtr command = nullptr;

	SaveFile saveFile;

	// ==================
	static std::vector<Encounter> encounterTable;
	static std::vector<Encounter> uniqueEncounterTable;

	// ==== UI Stuff ====
	Camera* camera;

	bool changeFloors = false;

	bool leftClick = false;
	bool rightClick = false;

	sf::Vector2i cursorTileLocation;
	bool targeting = false;
	bool usingItem = false;
	bool recalcTargetArray = false;
	Ability* targetingAbility = nullptr;
	size_t usingItemIndex = 0;

	CursorContainer cursorContainer;

	PlayerHUD playerHUD;

	Minimap minimap;

	Tooltip tooltip;
	bool displayTooltip = false;

	InspectWindow inspectWindow;
	bool displayInspectWindow = false;

	LearnAbilityWindow learnAbilityWindow;
	bool displayLearnAbilityWindow = false;

	Inventory inventory;
	bool displayInventory = false;

	LootWindow lootWindow;
	bool displayLootWindow = false;

	Spellbook spellbook;
	bool displaySpellbook = false;

	ShopWindow shopWindow;
	bool displayShopWindow = false;

	StatWindow statWindow;
	bool displayStatWindow = false;

	sf::Sprite statButton;
	bool displayStatButton = false;

	// === debug
	std::vector<sf::RectangleShape> pathRects;
	sf::Vector2i firstPath;
	sf::Vector2i secondPath;
};