// ================================================================
//
// monsterList.cpp
//
// ================================================================

#include "../entity/monster.hpp"

#include "../core/combat.hpp"
#include "../core/random.hpp"
#include "../core/tileMath.hpp"
#include "id/abilityID.hpp"
#include "id/auraID.hpp"
#include "id/category.hpp"
#include "id/element.hpp"
#include "id/equipType.hpp"
#include "id/eventType.hpp"
#include "id/monsterID.hpp"
#include "../scene/dungeonScene.hpp"

static std::unordered_map<MonsterID, MonsterData> initList() {
	std::unordered_map<MonsterID, MonsterData> list;

	// Test
	list[MonsterID::TargetDummy] = []{
		MonsterData md;

		md.Name = "Target Dummy";
		md.Title = "";
		md.Filename = "target_dummy.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = true;
		md.ChaseTurns = 0;

		md.Level = 1;

		md.BaseHP = 42;
		md.BaseMP = 12;
		md.BaseSP = 100;

		md.BaseSTR = 8;
		md.BaseDEX = 3;
		md.BaseMAG = 5;
		md.BaseVIT = 4;
		md.BaseSPI = 2;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 0;

		md.BaseAttackPower = 2;
		md.BaseSpellPower = 2;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 100;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 100;
		md.BaseMoveCost = 100;

		md.EXPDrop = 20;
		md.GoldDrop = 5;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;

			ai.Ability = AbilityID::Undefined;
			ai.Target = monster->GetLocation();

			return ai;
		};

		return md;
	}();

	// Common
	list[MonsterID::ArcaneSentry] = [] {
		MonsterData md;

		md.Name = "Arcane Sentry";
		md.Title = "";
		md.Filename = "arcane_sentry.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = true;
		md.ChaseTurns = 3;

		md.Level = 3;

		md.BaseHP = 12;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 3;
		md.BaseDEX = 15;
		md.BaseMAG = 15;
		md.BaseVIT = 6;
		md.BaseSPI = 20;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 15;
		md.BaseEvasion = 1;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 10;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 350;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Arcane;
		md.AttackType = EquipType::Wand;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 100;

		md.EXPDrop = 7;
		md.GoldDrop = 0;
		md.LootDrop = 1500;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::MagicMissile, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::MagicMissile)) {
				ai.Ability = AbilityID::MagicMissile;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::BlinkingSentry] = [] {
		MonsterData md;

		md.Name = "Blinking Sentry";
		md.Title = "";
		md.Filename = "blinking_sentry.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = true;
		md.ChaseTurns = 3;

		md.Level = 9;

		md.BaseHP = 125;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 9;
		md.BaseDEX = 25;
		md.BaseMAG = 25;
		md.BaseVIT = 18;
		md.BaseSPI = 30;

		md.BaseArmor = 30;
		md.BaseMagicArmor = 45;
		md.BaseEvasion = 5;

		md.BaseAttackPower = 11;
		md.BaseSpellPower = 18;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 350;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Arcane;
		md.AttackType = EquipType::Wand;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 100;

		md.EXPDrop = 11;
		md.GoldDrop = 0;
		md.LootDrop = 2500;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::MagicMissile, 2},
			{AbilityID::PhaseDoor, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			bool playerInMelee = false;

			std::vector<sf::Vector2i> neighboors = TileMath::Neighboors(monster->GetLocation());
			for (auto& tile : neighboors) {
				if (ai.Target == tile) {
					playerInMelee = true;
					break;
				}
			}

			if (monster->IsAbilityUsable(AbilityID::PhaseDoor) && playerInMelee) {
				ai.Ability = AbilityID::PhaseDoor;
				ai.Target = monster->GetLocation();
			}
			else if (monster->IsAbilityUsable(AbilityID::MagicMissile)) {
				ai.Ability = AbilityID::MagicMissile;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::BlueSlime] = [] {
		MonsterData md;

		md.Name = "Blue Slime";
		md.Title = "";
		md.Filename = "blue_slime.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 5;

		md.BaseHP = 40;
		md.BaseMP = 6;
		md.BaseSP = 100;

		md.BaseSTR = 12;
		md.BaseDEX = 15;
		md.BaseMAG = 1;
		md.BaseVIT = 14;
		md.BaseSPI = 2;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 12;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 225;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 125;

		md.EXPDrop = 8;
		md.GoldDrop = 9;
		md.LootDrop = 2500;

		md.StatMods = {
			StatMod(StatModType::Resistance, 600, Element::Water),
			StatMod(StatModType::Resistance, 300, Element::Poison)
		};
		md.Abilities = {
			{AbilityID::SlimeSplash, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			
			if (monster->IsAbilityUsable(AbilityID::SlimeSplash)) {
				ai.Ability = AbilityID::SlimeSplash;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::BrownBear] = [] {
		MonsterData md;

		md.Name = "Brown Bear";
		md.Title = "";
		md.Filename = "brown_bear.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 6;

		md.BaseHP = 50;
		md.BaseMP = 4;
		md.BaseSP = 100;

		md.BaseSTR = 22;
		md.BaseDEX = 19;
		md.BaseMAG = 5;
		md.BaseVIT = 20;
		md.BaseSPI = 5;

		md.BaseArmor = 25;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 5;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 220;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 100;

		md.EXPDrop = 10;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Maul, 0},
			{AbilityID::CrushingBlow, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Use Crushing Blow on cooldown.
			if (monster->IsAbilityUsable(AbilityID::CrushingBlow)) {
				ai.Ability = AbilityID::CrushingBlow;
			}
			// Has a 50% chance to use Maul.
			else if (monster->IsAbilityUsable(AbilityID::Maul) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Maul;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::BrownSnake] = [] {
		MonsterData md;

		md.Name = "Brown Snake";
		md.Title = "";
		md.Filename = "brown_snake.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 1;

		md.BaseHP = 18;
		md.BaseMP = 3;
		md.BaseSP = 100;

		md.BaseSTR = 5;
		md.BaseDEX = 20;
		md.BaseMAG = 2;
		md.BaseVIT = 3;
		md.BaseSPI = 2;

		md.BaseArmor = 5;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 12;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 150;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 200;
		md.BaseMoveCost = 75;

		md.EXPDrop = 4;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();
	list[MonsterID::CaveBat] = [] {
		MonsterData md;

		md.Name = "Cave Bat";
		md.Title = "";
		md.Filename = "cave_bat.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = true;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 1;

		md.BaseHP = 15;
		md.BaseMP = 6;
		md.BaseSP = 100;

		md.BaseSTR = 5;
		md.BaseDEX = 15;
		md.BaseMAG = 2;
		md.BaseVIT = 2;
		md.BaseSPI = 2;

		md.BaseArmor = 1;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 12;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 450;
		md.BaseMoveCost = 70;

		md.EXPDrop = 5;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();
	list[MonsterID::ClayGolem] = [] {
		MonsterData md;

		md.Name = "Clay Golem";
		md.Title = "";
		md.Filename = "clay_golem.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 8;

		md.BaseHP = 175;
		md.BaseMP = 10;
		md.BaseSP = 100;

		md.BaseSTR = 23;
		md.BaseDEX = 14;
		md.BaseMAG = 10;
		md.BaseVIT = 25;
		md.BaseSPI = 5;

		md.BaseArmor = 55;
		md.BaseMagicArmor = 10;
		md.BaseEvasion = 5;

		md.BaseAttackPower = 18;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 220;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 120;

		md.EXPDrop = 12;
		md.GoldDrop = 15;
		md.LootDrop = 4000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 1000, Element::Poison)
		};
		md.Abilities = {
			{AbilityID::CrushArmor, 0},
			{AbilityID::CrushingBlow, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::CrushArmor)) {
				ai.Ability = AbilityID::CrushArmor;
			}
			else if (monster->IsAbilityUsable(AbilityID::CrushingBlow)) {
				ai.Ability = AbilityID::CrushingBlow;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Cobra] = [] {
		MonsterData md;

		md.Name = "Cobra";
		md.Title = "";
		md.Filename = "cobra.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 4;

		md.BaseHP = 10;
		md.BaseMP = 6;
		md.BaseSP = 120;

		md.BaseSTR = 15;
		md.BaseDEX = 25;
		md.BaseMAG = 5;
		md.BaseVIT = 10;
		md.BaseSPI = 3;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 20;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 150;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 200;
		md.BaseMoveCost = 75;

		md.EXPDrop = 7;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::CobraBite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			
			if (monster->IsAbilityUsable(AbilityID::CobraBite)) {
				ai.Ability = AbilityID::CobraBite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::DemonEye] = [] {
		MonsterData md;

		md.Name = "Demon Eye";
		md.Title = "";
		md.Filename = "demon_eye.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 5;

		md.BaseHP = 50;
		md.BaseMP = 24;
		md.BaseSP = 100;

		md.BaseSTR = 17;
		md.BaseDEX = 20;
		md.BaseMAG = 14;
		md.BaseVIT = 12;
		md.BaseSPI = 8;

		md.BaseArmor = 20;
		md.BaseMagicArmor = 5;
		md.BaseEvasion = 21;

		md.BaseAttackPower = 11;
		md.BaseSpellPower = 9;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 450;
		md.BaseMoveCost = 90;

		md.EXPDrop = 7;
		md.GoldDrop = 6;
		md.LootDrop = 2000;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::FearfulGaze, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Fearful Gaze: Use on Cooldown
			if (monster->IsAbilityUsable(AbilityID::FearfulGaze)) {
				ai.Ability = AbilityID::FearfulGaze;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::FireAnt] = [] {
		MonsterData md;

		md.Name = "Fire Ant";
		md.Title = "";
		md.Filename = "fire_ant.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 5;

		md.BaseHP = 15;
		md.BaseMP = 8;
		md.BaseSP = 100;

		md.BaseSTR = 14;
		md.BaseDEX = 16;
		md.BaseMAG = 14;
		md.BaseVIT = 10;
		md.BaseSPI = 8;

		md.BaseArmor = 15;
		md.BaseMagicArmor = 5;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 11;
		md.BaseSpellPower = 9;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 90;

		md.EXPDrop = 4;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Ignite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Ignite: Use on Cooldown
			if (monster->IsAbilityUsable(AbilityID::Ignite)) {
				ai.Ability = AbilityID::Ignite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::GiantRat] = [] {
		MonsterData md;

		md.Name = "Giant Rat";
		md.Title = "";
		md.Filename = "giant_rat.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 1;

		md.BaseHP = 20;
		md.BaseMP = 1;
		md.BaseSP = 100;

		md.BaseSTR = 5;
		md.BaseDEX = 9;
		md.BaseMAG = 1;
		md.BaseVIT = 4;
		md.BaseSPI = 1;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 3;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 600;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 250;
		md.BaseMoveCost = 80;

		md.EXPDrop = 3;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Bite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Bite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::GoblinWarrior] = [] {
		MonsterData md;

		md.Name = "Goblin Warrior";
		md.Title = "";
		md.Filename = "goblin_warrior.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 5;

		md.BaseHP = 56;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 14;
		md.BaseDEX = 15;
		md.BaseMAG = 10;
		md.BaseVIT = 14;
		md.BaseSPI = 8;

		md.BaseArmor = 30;
		md.BaseMagicArmor = 10;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Sword;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 90;

		md.EXPDrop = 6;
		md.GoldDrop = 8;
		md.LootDrop = 1500;

		md.StatMods = {
			StatMod(StatModType::BlockChance, 200)
		};
		md.Abilities = {
			{AbilityID::PowerStrike, 0},
			{AbilityID::RendingSlash, 2}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::RendingSlash)) {
				ai.Ability = AbilityID::RendingSlash;
			}
			else if (monster->IsAbilityUsable(AbilityID::PowerStrike) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::PowerStrike;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::GoblinWizard] = [] {
		MonsterData md;

		md.Name = "Goblin Wizard";
		md.Title = "";
		md.Filename = "goblin_wizard.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 5;

		md.BaseHP = 40;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 12;
		md.BaseDEX = 15;
		md.BaseMAG = 20;
		md.BaseVIT = 10;
		md.BaseSPI = 15;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 30;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 14;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 240;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Staff;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 100;

		md.EXPDrop = 7;
		md.GoldDrop = 10;
		md.LootDrop = 2250;

		md.StatMods = {
			StatMod(StatModType::Haste, 50),
			StatMod(StatModType::CritChance, 30)
		};
		md.Abilities = {
			{AbilityID::MagicMissile, 1},
			{AbilityID::FlameBolt, 1},
			{AbilityID::WaterBolt, 1},
			{AbilityID::Icicle, 1},
			{AbilityID::Shock, 1}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			std::vector<AbilityID> usable;
			if (monster->IsAbilityUsable(AbilityID::MagicMissile)) {
				usable.push_back(AbilityID::MagicMissile);
			}
			if (monster->IsAbilityUsable(AbilityID::FlameBolt)) {
				usable.push_back(AbilityID::FlameBolt);
			}
			if (monster->IsAbilityUsable(AbilityID::WaterBolt)) {
				usable.push_back(AbilityID::WaterBolt);
			}
			if (monster->IsAbilityUsable(AbilityID::Icicle)) {
				usable.push_back(AbilityID::Icicle);
			}
			if (monster->IsAbilityUsable(AbilityID::Shock)) {
				usable.push_back(AbilityID::Shock);
			}
			// Randomly cast Magic Missile, Flame Bolt, Water Bolt,
			// Icicle, or Shock.
			if (!usable.empty()) {
				ai.Ability = usable[Random::RandomSizeT(0, usable.size() - 1)];
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::GreenSlime] = [] {
		MonsterData md;

		md.Name = "Green Slime";
		md.Title = "";
		md.Filename = "green_slime.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 1;

		md.BaseHP = 35;
		md.BaseMP = 3;
		md.BaseSP = 100;

		md.BaseSTR = 5;
		md.BaseDEX = 10;
		md.BaseMAG = 1;
		md.BaseVIT = 8;
		md.BaseSPI = 1;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 6;

		md.BaseAttackPower = 5;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 225;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 125;

		md.EXPDrop = 5;
		md.GoldDrop = 5;
		md.LootDrop = 2500;

		md.StatMods = {
			StatMod(StatModType::Resistance, 300, Element::Water),
			StatMod(StatModType::Resistance, 300, Element::Poison)
		};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();
	list[MonsterID::IcyStorm] = [] {
		MonsterData md;

		md.Name = "Icy Storm";
		md.Title = "";
		md.Filename = "icy_storm.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 8;

		md.BaseHP = 82;
		md.BaseMP = 30;
		md.BaseSP = 100;

		md.BaseSTR = 17;
		md.BaseDEX = 22;
		md.BaseMAG = 24;
		md.BaseVIT = 18;
		md.BaseSPI = 16;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 40;
		md.BaseEvasion = 20;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 12;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Ice;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 10;
		md.GoldDrop = 15;
		md.LootDrop = 3000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 1000, Element::Ice),
			StatMod(StatModType::Resistance, -300, Element::Fire)
		};
		md.Abilities = {
			{AbilityID::Bonechill, 0},
			{AbilityID::Icicle, 2}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Bonechill: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::Bonechill)) {
				ai.Ability = AbilityID::Bonechill;
			}
			// Icicle: Use as filler.
			else if (monster->IsAbilityUsable(AbilityID::Icicle)) {
				ai.Ability = AbilityID::Icicle;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Iguana] = [] {
		MonsterData md;

		md.Name = "Iguana";
		md.Title = "";
		md.Filename = "iguana.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 7;

		md.BaseHP = 50;
		md.BaseMP = 6;
		md.BaseSP = 100;

		md.BaseSTR = 21;
		md.BaseDEX = 20;
		md.BaseMAG = 10;
		md.BaseVIT = 20;
		md.BaseSPI = 2;

		md.BaseArmor = 30;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 14;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 10;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Bite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Has a 50% chance to use Bite.
			if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Bite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Imp] = [] {
		MonsterData md;

		md.Name = "Imp";
		md.Title = "";
		md.Filename = "imp.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 2;

		md.BaseHP = 24;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 8;
		md.BaseDEX = 9;
		md.BaseMAG = 9;
		md.BaseVIT = 4;
		md.BaseSPI = 5;

		md.BaseArmor = 12;
		md.BaseMagicArmor = 5;
		md.BaseEvasion = 7;

		md.BaseAttackPower = 9;
		md.BaseSpellPower = 8;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 6;
		md.GoldDrop = 3;
		md.LootDrop = 1250;

		md.StatMods = {
			StatMod(StatModType::Resistance, 300, Element::Dark),
			StatMod(StatModType::Resistance, -300, Element::Light)
		};
		md.Abilities = {
			{AbilityID::BoltOfDarkness, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Has a 50% chance to cast Bolt of Darkness.
			if (monster->IsAbilityUsable(AbilityID::BoltOfDarkness) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::BoltOfDarkness;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Jackal] = [] {
		MonsterData md;

		md.Name = "Jackal";
		md.Title = "";
		md.Filename = "jackal.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 1;

		md.BaseHP = 18;
		md.BaseMP = 1;
		md.BaseSP = 100;

		md.BaseSTR = 5;
		md.BaseDEX = 9;
		md.BaseMAG = 1;
		md.BaseVIT = 3;
		md.BaseSPI = 1;

		md.BaseArmor = 5;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 5;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 600;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 250;
		md.BaseMoveCost = 80;

		md.EXPDrop = 4;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Bite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Has a 50% chance to use Bite.
			if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Bite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::KoboldChampion] = [] {
		MonsterData md;

		md.Name = "Kobold Chapion";
		md.Title = "";
		md.Filename = "kobold_champion.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 9;

		md.BaseHP = 110;
		md.BaseMP = 30;
		md.BaseSP = 100;

		md.BaseSTR = 26;
		md.BaseDEX = 20;
		md.BaseMAG = 14;
		md.BaseVIT = 25;
		md.BaseSPI = 20;

		md.BaseArmor = 45;
		md.BaseMagicArmor = 10;
		md.BaseEvasion = 8;

		md.BaseAttackPower = 18;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Sword;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 10;
		md.GoldDrop = 12;
		md.LootDrop = 3500;

		md.StatMods = {
			StatMod(StatModType::BlockChance, 200)
		};
		md.Abilities = {
			{AbilityID::PowerStrike, 2},
			{AbilityID::FuriousStrike, 0},
			{AbilityID::HasteAllies, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::HasteAllies)) {
				ai.Ability = AbilityID::HasteAllies;
				ai.Target = monster->GetLocation();
			}
			else if (monster->IsAbilityUsable(AbilityID::FuriousStrike)) {
				ai.Ability = AbilityID::FuriousStrike;
			}
			else if (monster->IsAbilityUsable(AbilityID::PowerStrike)) {
				ai.Ability = AbilityID::PowerStrike;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::KoboldCrossbowman] = [] {
		MonsterData md;

		md.Name = "Kobold Crossbowman";
		md.Title = "";
		md.Filename = "kobold_crossbowman.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 2;

		md.BaseHP = 25;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 7;
		md.BaseDEX = 18;
		md.BaseMAG = 1;
		md.BaseVIT = 4;
		md.BaseSPI = 5;

		md.BaseArmor = 15;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 15;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 350;
		md.BaseAttackSpeed = 250;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 90;

		md.EXPDrop = 10;
		md.GoldDrop = 4;
		md.LootDrop = 2500;

		md.StatMods = {};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();
	list[MonsterID::KoboldGeomancer] = [] {
		MonsterData md;

		md.Name = "Kobold Geomancer";
		md.Title = "";
		md.Filename = "kobold_geomancer.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 2;

		md.BaseHP = 25;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 5;
		md.BaseDEX = 14;
		md.BaseMAG = 10;
		md.BaseVIT = 3;
		md.BaseSPI = 5;

		md.BaseArmor = 5;
		md.BaseMagicArmor = 3;
		md.BaseEvasion = 3;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 8;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 240;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Staff;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 8;
		md.GoldDrop = 10;
		md.LootDrop = 1750;

		md.StatMods = {
			
		};
		md.Abilities = {
			{AbilityID::Boulder, 0},
			{AbilityID::Stalagmite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Boulder)) {
				ai.Ability = AbilityID::Boulder;
			}
			else if (monster->IsAbilityUsable(AbilityID::Stalagmite) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Stalagmite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::KoboldMiner] = [] {
		MonsterData md;

		md.Name = "Kobold Miner";
		md.Title = "";
		md.Filename = "kobold_miner.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 2;

		md.BaseHP = 30;
		md.BaseMP = 10;
		md.BaseSP = 100;

		md.BaseSTR = 11;
		md.BaseDEX = 10;
		md.BaseMAG = 2;
		md.BaseVIT = 5;
		md.BaseSPI = 3;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 5;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 220;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Axe;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 5;
		md.GoldDrop = 7;
		md.LootDrop = 1500;

		md.StatMods = {
			StatMod(StatModType::DoubleStrikeChance, 100)
		};
		md.Abilities = {
			{AbilityID::Chopper, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Chopper) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Chopper;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::KoboldScout] = [] {
		MonsterData md;

		md.Name = "Kobold Scout";
		md.Title = "";
		md.Filename = "kobold_scout.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 2;

		md.BaseHP = 30;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 14;
		md.BaseDEX = 14;
		md.BaseMAG = 1;
		md.BaseVIT = 6;
		md.BaseSPI = 5;

		md.BaseArmor = 20;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 8;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 650;
		md.BaseAttackRange = 200;
		md.BaseAttackSpeed = 250;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 90;

		md.EXPDrop = 12;
		md.GoldDrop = 5;
		md.LootDrop = 3000;

		md.StatMods = {
			StatMod(StatModType::CritChance, 300)
		};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();
	list[MonsterID::LesserFlameblade] = [] {
		MonsterData md;

		md.Name = "Lesser Flameblade";
		md.Title = "";
		md.Filename = "lesser_flameblade.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 3;

		md.BaseHP = 46;
		md.BaseMP = 8;
		md.BaseSP = 100;

		md.BaseSTR = 12;
		md.BaseDEX = 16;
		md.BaseMAG = 12;
		md.BaseVIT = 12;
		md.BaseSPI = 8;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 1;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 10;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Fire;
		md.AttackType = EquipType::Sword;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 125;

		md.EXPDrop = 8;
		md.GoldDrop = 9;
		md.LootDrop = 3000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 1000, Element::Fire),
			StatMod(StatModType::Resistance, -300, Element::Water)
		};
		md.Abilities = {
			{AbilityID::FlameStrike, 0},
			{AbilityID::FieryTouch, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			
			// Flame Strike as often as possible.
			if (monster->IsAbilityUsable(AbilityID::FlameStrike)) {
				ai.Ability = AbilityID::FlameStrike;
			}
			// Fiery Touch if Flame Strike buff is active.
			else if (monster->IsAbilityUsable(AbilityID::FieryTouch) && monster->HasAura(AuraID::FlameStrike)) {
				ai.Ability = AbilityID::FieryTouch;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::LivingSpark] = [] {
		MonsterData md;

		md.Name = "Living Spark";
		md.Title = "";
		md.Filename = "living_spark.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 7;

		md.BaseHP = 70;
		md.BaseMP = 30;
		md.BaseSP = 100;

		md.BaseSTR = 18;
		md.BaseDEX = 21;
		md.BaseMAG = 19;
		md.BaseVIT = 18;
		md.BaseSPI = 15;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 40;
		md.BaseEvasion = 25;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 6;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Lightning;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 450;
		md.BaseMoveCost = 80;

		md.EXPDrop = 10;
		md.GoldDrop = 14;
		md.LootDrop = 3000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 1000, Element::Lightning),
			StatMod(StatModType::Resistance, -300, Element::Ice)
		};
		md.Abilities = {
			{AbilityID::ElectricSurge, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::ElectricSurge)) {
				ai.Ability = AbilityID::ElectricSurge;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::SnappingTurtle] = [] {
		MonsterData md;

		md.Name = "Snapping Turtle";
		md.Title = "";
		md.Filename = "snapping_turtle.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 7;

		md.BaseHP = 80;
		md.BaseMP = 6;
		md.BaseSP = 100;

		md.BaseSTR = 19;
		md.BaseDEX = 16;
		md.BaseMAG = 10;
		md.BaseVIT = 30;
		md.BaseSPI = 2;

		md.BaseArmor = 120;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 1;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 250;
		md.BaseMoveCost = 120;

		md.EXPDrop = 16;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Bite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Bite: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::Bite)) {
				ai.Ability = AbilityID::Bite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Tiger] = [] {
		MonsterData md;

		md.Name = "Tiger";
		md.Title = "";
		md.Filename = "tiger.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 6;

		md.BaseHP = 68;
		md.BaseMP = 5;
		md.BaseSP = 100;

		md.BaseSTR = 20;
		md.BaseDEX = 24;
		md.BaseMAG = 5;
		md.BaseVIT = 16;
		md.BaseSPI = 5;

		md.BaseArmor = 21;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 18;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 70;

		md.EXPDrop = 10;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {
			StatMod(StatModType::Haste, 150)
		};
		md.Abilities = {
			{AbilityID::Bite, 0},
			{AbilityID::Maul, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Maul: 50% Chance to Use
			if (monster->IsAbilityUsable(AbilityID::Maul) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Maul;
			}
			// Bite: 50% Chance to Use
			else if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Bite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Trickster] = [] {
		MonsterData md;

		md.Name = "Trickster";
		md.Title = "";
		md.Filename = "trickster.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 6;

		md.BaseHP = 70;
		md.BaseMP = 28;
		md.BaseSP = 100;

		md.BaseSTR = 20;
		md.BaseDEX = 19;
		md.BaseMAG = 21;
		md.BaseVIT = 15;
		md.BaseSPI = 16;

		md.BaseArmor = 20;
		md.BaseMagicArmor = 10;
		md.BaseEvasion = 14;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 14;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 11;
		md.GoldDrop = 7;
		md.LootDrop = 3000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 300, Element::Dark),
			StatMod(StatModType::Resistance, -300, Element::Light)
		};
		md.Abilities = {
			{AbilityID::ShadowFlay, 0},
			{AbilityID::Teleport, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Teleport: Under 50% HP, Use Only Once, 25% Chance to Use
			if (monster->GetFlag(0) < 1 && monster->IsAbilityUsable(AbilityID::Teleport) && monster->GetCurrentHP() <= monster->GetMaxHP() / 2 && Random::RandomInt(1, 100) <= 25) {
				ai.Target = monster->GetLocation();
				ai.Ability = AbilityID::Teleport;
				ai.FlagIndex = 0;
				ai.FlagValue = 1;
			}
			// Shadow Flay: 50% Chance to Use
			else if (monster->IsAbilityUsable(AbilityID::ShadowFlay) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::ShadowFlay;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::VampireBat] = [] {
		MonsterData md;

		md.Name = "Vampire Bat";
		md.Title = "";
		md.Filename = "vampire_bat.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = true;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 8;

		md.BaseHP = 103;
		md.BaseMP = 12;
		md.BaseSP = 100;

		md.BaseSTR = 25;
		md.BaseDEX = 25;
		md.BaseMAG = 10;
		md.BaseVIT = 20;
		md.BaseSPI = 10;

		md.BaseArmor = 5;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 28;

		md.BaseAttackPower = 18;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 450;
		md.BaseMoveCost = 70;

		md.EXPDrop = 9;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Bloodsuck, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			
			if (monster->IsAbilityUsable(AbilityID::Bloodsuck) && monster->GetCurrentHP() < monster->GetMaxHP() * 9 / 10) {
				ai.Ability = AbilityID::Bloodsuck;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::VenomousRat] = [] {
		MonsterData md;

		md.Name = "Venomous Rat";
		md.Title = "";
		md.Filename = "venomous_rat.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 5;

		md.BaseHP = 45;
		md.BaseMP = 5;
		md.BaseSP = 100;

		md.BaseSTR = 16;
		md.BaseDEX = 18;
		md.BaseMAG = 5;
		md.BaseVIT = 12;
		md.BaseSPI = 5;

		md.BaseArmor = 20;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 18;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 250;
		md.BaseMoveCost = 80;

		md.EXPDrop = 8;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Bite, 0},
			{AbilityID::VenomousWound, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Bite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::WaterMare] = [] {
		MonsterData md;

		md.Name = "Water Mare";
		md.Title = "";
		md.Filename = "water_mare.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 6;

		md.BaseHP = 63;
		md.BaseMP = 1;
		md.BaseSP = 100;

		md.BaseSTR = 15;
		md.BaseDEX = 20;
		md.BaseMAG = 15;
		md.BaseVIT = 15;
		md.BaseSPI = 10;

		md.BaseArmor = 20;
		md.BaseMagicArmor = 40;
		md.BaseEvasion = 15;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 6;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Water;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 450;
		md.BaseMoveCost = 80;

		md.EXPDrop = 9;
		md.GoldDrop = 12;
		md.LootDrop = 3000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 1000, Element::Water),
			StatMod(StatModType::Resistance, -300, Element::Lightning)
		};
		md.Abilities = {
			{AbilityID::Trample, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Trample) && Random::RandomInt(1, 100) <= 75) {
				ai.Ability = AbilityID::Trample;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Wolf] = [] {
		MonsterData md;

		md.Name = "Wolf";
		md.Title = "";
		md.Filename = "wolf.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 5;

		md.BaseHP = 42;
		md.BaseMP = 5;
		md.BaseSP = 100;

		md.BaseSTR = 14;
		md.BaseDEX = 21;
		md.BaseMAG = 5;
		md.BaseVIT = 15;
		md.BaseSPI = 5;

		md.BaseArmor = 12;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 16;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 250;
		md.BaseMoveCost = 80;

		md.EXPDrop = 8;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::Bite, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Has a 50% chance to use Bite.
			if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.Ability = AbilityID::Bite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::WorkerAnt] = [] {
		MonsterData md;

		md.Name = "Worker Ant";
		md.Title = "";
		md.Filename = "worker_ant.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 1;

		md.BaseHP = 15;
		md.BaseMP = 3;
		md.BaseSP = 100;

		md.BaseSTR = 3;
		md.BaseDEX = 6;
		md.BaseMAG = 1;
		md.BaseVIT = 2;
		md.BaseSPI = 1;

		md.BaseArmor = 5;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 5;

		md.BaseAttackPower = 4;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 200;
		md.BaseMoveCost = 90;

		md.EXPDrop = 2;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();
	list[MonsterID::Worm] = [] {
		MonsterData md;

		md.Name = "Worm";
		md.Title = "";
		md.Filename = "worm.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 1;

		md.BaseHP = 5;
		md.BaseMP = 3;
		md.BaseSP = 100;

		md.BaseSTR = 1;
		md.BaseDEX = 1;
		md.BaseMAG = 1;
		md.BaseVIT = 1;
		md.BaseSPI = 1;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 3;

		md.BaseAttackPower = 3;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 150;
		md.BaseMoveCost = 100;

		md.EXPDrop = 1;
		md.GoldDrop = 0;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();
	list[MonsterID::WormBeast] = [] {
		MonsterData md;

		md.Name = "Worm Beast";
		md.Title = "";
		md.Filename = "worm_beast.png";

		md.IsUnique = false;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 3;

		md.Level = 7;

		md.BaseHP = 75;
		md.BaseMP = 10;
		md.BaseSP = 100;

		md.BaseSTR = 14;
		md.BaseDEX = 16;
		md.BaseMAG = 12;
		md.BaseVIT = 20;
		md.BaseSPI = 10;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 1;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 100;

		md.EXPDrop = 12;
		md.GoldDrop = 0;
		md.LootDrop = 1000;

		md.StatMods = {};
		md.Abilities = {
			{ AbilityID::Vigor, 0 }
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();
			ai.Ability = AbilityID::Attack;

			return ai;
		};

		return md;
	}();

	// Unique
	list[MonsterID::Fenrok] = [] {
		MonsterData md;

		md.Name = "Fenrok";
		md.Title = "The Unhunted";
		md.Filename = "fenrok.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 2;

		md.BaseHP = 200;
		md.BaseMP = 10;
		md.BaseSP = 100;

		md.BaseSTR = 12;
		md.BaseDEX = 14;
		md.BaseMAG = 8;
		md.BaseVIT = 10;
		md.BaseSPI = 10;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 5;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 5;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 30;
		md.GoldDrop = 25;
		md.LootDrop = 4000;

		md.StatMods = {};
		md.Abilities = {
			{ AbilityID::ShadowEnergy, 0 }
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;

			// Shadow Energy: Use when half HP, cast only once per encounter.
			if (monster->GetFlag(0) == 0 && monster->IsAbilityUsable(AbilityID::ShadowEnergy)) {
				if (monster->GetCurrentHP() < monster->GetMaxHP() / 2) {
					ai.Target = monster->GetLocation();
					ai.Ability = AbilityID::ShadowEnergy;
					ai.FlagIndex = 0;
					ai.FlagValue = 1;
				}
				else {
					ai.Target = dungeonScene->GetPlayer()->GetLocation();
					ai.Ability = AbilityID::Attack;
				}
			}
			else {
				ai.Target = dungeonScene->GetPlayer()->GetLocation();
				ai.Ability = AbilityID::Attack;
			}
			return ai;
		};

		return md;
	}();
	list[MonsterID::Galahan] = [] {
		MonsterData md;

		md.Name = "Galahan";
		md.Title = "The Golden Knight";
		md.Filename = "galahan.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 9;

		md.BaseHP = 550;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 30;
		md.BaseDEX = 21;
		md.BaseMAG = 22;
		md.BaseVIT = 40;
		md.BaseSPI = 19;

		md.BaseArmor = 75;
		md.BaseMagicArmor = 16;
		md.BaseEvasion = 8;

		md.BaseAttackPower = 25;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Sword;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 100;

		md.EXPDrop = 80;
		md.GoldDrop = 92;
		md.LootDrop = 6000;

		md.StatMods = {
			StatMod(StatModType::BlockChance, 150)
		};
		md.Abilities = {
			{ AbilityID::HerosTriumph, 0 },
			{ AbilityID::PowerStrike, 2 },
			{ AbilityID::RendingSlash, 4 }
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Hero's Triumph: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::HerosTriumph)) {
				ai.Ability = AbilityID::HerosTriumph;
			}
			// Rending Slash: Use on cooldown.
			else if (monster->IsAbilityUsable(AbilityID::RendingSlash)) {
				ai.Ability = AbilityID::RendingSlash;
			}
			// Power Strike: Use on cooldown.
			else if (monster->IsAbilityUsable(AbilityID::PowerStrike)) {
				ai.Ability = AbilityID::PowerStrike;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Glykon] = [] {
		MonsterData md;

		md.Name = "Glykon";
		md.Title = "Legendary Cobra";
		md.Filename = "glykon.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 6;

		md.BaseHP = 210;
		md.BaseMP = 20;
		md.BaseSP = 120;

		md.BaseSTR = 20;
		md.BaseDEX = 30;
		md.BaseMAG = 12;
		md.BaseVIT = 20;
		md.BaseSPI = 12;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 30;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 150;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 250;
		md.BaseMoveCost = 75;

		md.EXPDrop = 60;
		md.GoldDrop = 40;
		md.LootDrop = 0;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::CobraBite, 0},
			{AbilityID::ConcentratedVenom, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::ConcentratedVenom)) {
				ai.Ability = AbilityID::ConcentratedVenom;
			}
			else if (monster->IsAbilityUsable(AbilityID::CobraBite)) {
				ai.Ability = AbilityID::CobraBite;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Incindia] = [] {
		MonsterData md;

		md.Name = "Incindia";
		md.Title = "The Flame Sorceress";
		md.Filename = "incindia.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 5;

		md.BaseHP = 300;
		md.BaseMP = 120;
		md.BaseSP = 100;

		md.BaseSTR = 8;
		md.BaseDEX = 15;
		md.BaseMAG = 16;
		md.BaseVIT = 10;
		md.BaseSPI = 15;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 5;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 14;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 250;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Staff;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 50;
		md.GoldDrop = 40;
		md.LootDrop = 5000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 300, Element::Fire)
		};
		md.Abilities = {
			{ AbilityID::FlameBolt, 1 },
			{ AbilityID::DragonfireBolt, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Dragonfire Bolt: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::DragonfireBolt)) {
				ai.Ability = AbilityID::DragonfireBolt;
			}
			// Flame Bolt: Use as filler.
			else if (monster->IsAbilityUsable(AbilityID::FlameBolt)) {
				ai.Ability = AbilityID::FlameBolt;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Luther] = [] {
		MonsterData md;

		md.Name = "Luther";
		md.Title = "Mercenary Archer";
		md.Filename = "luther.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 4;

		md.BaseHP = 325;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 15;
		md.BaseDEX = 21;
		md.BaseMAG = 16;
		md.BaseVIT = 15;
		md.BaseSPI = 14;

		md.BaseArmor = 25;
		md.BaseMagicArmor = 5;
		md.BaseEvasion = 16;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 350;
		md.BaseAttackSpeed = 250;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Bow;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 55;
		md.GoldDrop = 50;
		md.LootDrop = 6000;

		md.StatMods = {
			StatMod(StatModType::Haste, 30)
		};
		md.Abilities = {
			{ AbilityID::PowerShot, 0 },
			{ AbilityID::CriticalShot, 0 },
			{ AbilityID::DeadlyForce, 4 },
			{ AbilityID::Focus, 4 }
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Critical Shot: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::CriticalShot)) {
				ai.Ability = AbilityID::CriticalShot;
			}
			// Power Shot: Use on cooldown while Deadly Force buff is active.
			else if (monster->IsAbilityUsable(AbilityID::PowerShot) && monster->HasAura(AuraID::DeadlyForce)) {
				ai.Ability = AbilityID::PowerShot;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Marbix] = [] {
		MonsterData md;

		md.Name = "Marbix";
		md.Title = "Goblin Lieutenant";
		md.Filename = "marbix.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 7;

		md.BaseHP = 400;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 25;
		md.BaseDEX = 21;
		md.BaseMAG = 15;
		md.BaseVIT = 20;
		md.BaseSPI = 15;

		md.BaseArmor = 48;
		md.BaseMagicArmor = 15;
		md.BaseEvasion = 12;

		md.BaseAttackPower = 14;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Sword;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 62;
		md.GoldDrop = 40;
		md.LootDrop = 5000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 300, Element::Dark),
			StatMod(StatModType::Resistance, -300, Element::Light),
			StatMod(StatModType::BlockChance, 200),
			StatMod(StatModType::Haste, 50)
		};
		md.Abilities = {
			{ AbilityID::DemonBlade, 0 },
			{ AbilityID::PowerStrike, 0},
			{ AbilityID::RendingSlash, 3}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Demon Blade: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::DemonBlade)) {
				ai.Ability = AbilityID::DemonBlade;
			}
			// Rending Slash: Use on cooldown.
			else if (monster->IsAbilityUsable(AbilityID::RendingSlash)) {
				ai.Ability = AbilityID::RendingSlash;
			}
			// Power Strike: Use on cooldown.
			else if (monster->IsAbilityUsable(AbilityID::PowerStrike)) {
				ai.Ability = AbilityID::PowerStrike;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Norgash] = [] {
		MonsterData md;

		md.Name = "Norgash";
		md.Title = "Kobold Chief";
		md.Filename = "norgash.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 3;

		md.BaseHP = 150;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 12;
		md.BaseDEX = 15;
		md.BaseMAG = 10;
		md.BaseVIT = 10;
		md.BaseSPI = 10;

		md.BaseArmor = 25;
		md.BaseMagicArmor = 10;
		md.BaseEvasion = 10;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 10;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 180;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Axe;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 45;
		md.GoldDrop = 32;
		md.LootDrop = 4000;

		md.StatMods = {};
		md.Abilities = {
			{ AbilityID::Chopper, 2}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Chopper: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::Chopper)) {
				ai.Ability = AbilityID::Chopper;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::RatKing] = [] {
		MonsterData md;

		md.Name = "The Rat King";
		md.Title = "";
		md.Filename = "rat_king.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 7;

		md.BaseHP = 325;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 20;
		md.BaseDEX = 20;
		md.BaseMAG = 15;
		md.BaseVIT = 15;
		md.BaseSPI = 15;

		md.BaseArmor = 40;
		md.BaseMagicArmor = 20;
		md.BaseEvasion = 14;

		md.BaseAttackPower = 12;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 700;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Undefined;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 80;

		md.EXPDrop = 60;
		md.GoldDrop = 45;
		md.LootDrop = 6000;

		md.StatMods = {
			StatMod(StatModType::Resistance, 300, Element::Poison)
		};
		md.Abilities = {
			{ AbilityID::HasteAllies, 0 }
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			// Haste Allies: Use on cooldown.
			if (monster->IsAbilityUsable(AbilityID::HasteAllies)) {
				ai.Ability = AbilityID::HasteAllies;
				ai.Target = monster->GetLocation();
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();
	list[MonsterID::Tergar] = [] {
		MonsterData md;

		md.Name = "Tergar";
		md.Title = "Exiled Kobold";
		md.Filename = "tergar.png";

		md.IsUnique = true;
		md.IsBoss = false;
		md.CanFly = false;
		md.CanSwim = false;
		md.CanTunnel = false;

		md.IsStationary = false;
		md.ChaseTurns = 5;

		md.Level = 3;

		md.BaseHP = 175;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 12;
		md.BaseDEX = 17;
		md.BaseMAG = 12;
		md.BaseVIT = 18;
		md.BaseSPI = 12;

		md.BaseArmor = 15;
		md.BaseMagicArmor = 10;
		md.BaseEvasion = 12;

		md.BaseAttackPower = 10;
		md.BaseSpellPower = 0;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 100;
		md.BaseAttackSpeed = 150;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Physical;
		md.AttackType = EquipType::Dagger;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 75;

		md.EXPDrop = 50;
		md.GoldDrop = 41;
		md.LootDrop = 5000;

		md.StatMods = {};
		md.Abilities = {
			{ AbilityID::FlashStrike, 0 }
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			AIAction ai;
			ai.Target = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::FlashStrike)) {
				ai.Ability = AbilityID::FlashStrike;
			}
			else {
				ai.Ability = AbilityID::Attack;
			}

			return ai;
		};

		return md;
	}();

	return list;
}

std::unordered_map<MonsterID, MonsterData> Monster::monsterList = initList();