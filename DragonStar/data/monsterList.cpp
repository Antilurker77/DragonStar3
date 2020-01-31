// ================================================================
//
// monsterList.cpp
//
// ================================================================

#include "../entity/monster.hpp"

#include "../core/random.hpp"
#include "id/abilityID.hpp"
#include "id/auraID.hpp"
#include "id/element.hpp"
#include "id/equipType.hpp"
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
			std::pair<AbilityID, sf::Vector2i> ai;

			ai.first = AbilityID::Undefined;
			ai.second = monster->GetLocation();

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

		md.Level = 1;

		md.BaseHP = 12;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 3;
		md.BaseDEX = 2;
		md.BaseMAG = 10;
		md.BaseVIT = 6;
		md.BaseSPI = 10;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 15;
		md.BaseEvasion = 1;

		md.BaseAttackPower = 4;
		md.BaseSpellPower = 5;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 350;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Arcane;
		md.AttackType = EquipType::Wand;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 100;

		md.EXPDrop = 15;
		md.GoldDrop = 0;
		md.LootDrop = 1500;

		md.StatMods = {};
		md.Abilities = {
			{AbilityID::MagicMissile, 0}
		};

		md.AI = [](Actor* monster, DungeonScene* dungeonScene) {
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::MagicMissile)) {
				ai.first = AbilityID::MagicMissile;
			}
			else {
				ai.first = AbilityID::Attack;
			}

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
		md.BaseDEX = 8;
		md.BaseMAG = 2;
		md.BaseVIT = 2;
		md.BaseSPI = 2;

		md.BaseArmor = 1;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 15;

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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();
			ai.first = AbilityID::Attack;

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
		md.BaseDEX = 6;
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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.first = AbilityID::Bite;
			}
			else {
				ai.first = AbilityID::Attack;
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
		md.BaseDEX = 7;
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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();
			ai.first = AbilityID::Attack;

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

		md.Level = 1;

		md.BaseHP = 24;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 4;
		md.BaseDEX = 4;
		md.BaseMAG = 5;
		md.BaseVIT = 4;
		md.BaseSPI = 5;

		md.BaseArmor = 12;
		md.BaseMagicArmor = 5;
		md.BaseEvasion = 7;

		md.BaseAttackPower = 6;
		md.BaseSpellPower = 5;

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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();

			// Has a 50% chance to cast Bolt of Darkness.
			if (monster->IsAbilityUsable(AbilityID::BoltOfDarkness) && Random::RandomInt(1, 100) <= 50) {
				ai.first = AbilityID::BoltOfDarkness;
			}
			else {
				ai.first = AbilityID::Attack;
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
		md.BaseDEX = 6;
		md.BaseMAG = 1;
		md.BaseVIT = 3;
		md.BaseSPI = 1;

		md.BaseArmor = 5;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 12;

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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();

			// Has a 50% chance to use Bite.
			if (monster->IsAbilityUsable(AbilityID::Bite) && Random::RandomInt(1, 100) <= 50) {
				ai.first = AbilityID::Bite;
			}
			else {
				ai.first = AbilityID::Attack;
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

		md.Level = 1;

		md.BaseHP = 25;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 4;
		md.BaseDEX = 8;
		md.BaseMAG = 1;
		md.BaseVIT = 4;
		md.BaseSPI = 5;

		md.BaseArmor = 15;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 15;

		md.BaseAttackPower = 8;
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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();
			ai.first = AbilityID::Attack;

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

		md.Level = 1;

		md.BaseHP = 25;
		md.BaseMP = 40;
		md.BaseSP = 100;

		md.BaseSTR = 2;
		md.BaseDEX = 4;
		md.BaseMAG = 6;
		md.BaseVIT = 3;
		md.BaseSPI = 5;

		md.BaseArmor = 5;
		md.BaseMagicArmor = 3;
		md.BaseEvasion = 3;

		md.BaseAttackPower = 3;
		md.BaseSpellPower = 5;

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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Boulder)) {
				ai.first = AbilityID::Boulder;
			}
			else if (monster->IsAbilityUsable(AbilityID::Stalagmite) && Random::RandomInt(1, 100) <= 50) {
				ai.first = AbilityID::Stalagmite;
			}
			else {
				ai.first = AbilityID::Attack;
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

		md.Level = 1;

		md.BaseHP = 30;
		md.BaseMP = 10;
		md.BaseSP = 100;

		md.BaseSTR = 6;
		md.BaseDEX = 6;
		md.BaseMAG = 2;
		md.BaseVIT = 5;
		md.BaseSPI = 3;

		md.BaseArmor = 10;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 5;

		md.BaseAttackPower = 6;
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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();

			if (monster->IsAbilityUsable(AbilityID::Chopper) && Random::RandomInt(1, 100) <= 50) {
				ai.first = AbilityID::Chopper;
			}
			else {
				ai.first = AbilityID::Attack;
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

		md.Level = 1;

		md.BaseHP = 30;
		md.BaseMP = 20;
		md.BaseSP = 100;

		md.BaseSTR = 7;
		md.BaseDEX = 7;
		md.BaseMAG = 1;
		md.BaseVIT = 6;
		md.BaseSPI = 5;

		md.BaseArmor = 20;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 8;

		md.BaseAttackPower = 8;
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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();
			ai.first = AbilityID::Attack;

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

		md.Level = 2;

		md.BaseHP = 46;
		md.BaseMP = 8;
		md.BaseSP = 100;

		md.BaseSTR = 8;
		md.BaseDEX = 6;
		md.BaseMAG = 8;
		md.BaseVIT = 8;
		md.BaseSPI = 4;

		md.BaseArmor = 0;
		md.BaseMagicArmor = 0;
		md.BaseEvasion = 1;

		md.BaseAttackPower = 7;
		md.BaseSpellPower = 7;

		md.BaseHitChance = 750;
		md.BaseAttackRange = 150;
		md.BaseAttackSpeed = 200;
		md.BaseWeaponDamageMultiplier = 1000;
		md.AttackElement = Element::Fire;
		md.AttackType = EquipType::Sword;

		md.BaseLineOfSight = 350;
		md.BaseMoveCost = 125;

		md.EXPDrop = 20;
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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();
			
			// Flame Strike as often as possible.
			if (monster->IsAbilityUsable(AbilityID::FlameStrike)) {
				ai.first = AbilityID::FlameStrike;
			}
			// Fiery Touch if Flame Strike buff is active.
			else if (monster->IsAbilityUsable(AbilityID::FieryTouch) && monster->HasAura(AuraID::FlameStrike)) {
				ai.first = AbilityID::FieryTouch;
			}
			else {
				ai.first = AbilityID::Attack;
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
		md.BaseDEX = 3;
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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();
			ai.first = AbilityID::Attack;

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
			std::pair<AbilityID, sf::Vector2i> ai;
			ai.second = dungeonScene->GetPlayer()->GetLocation();
			ai.first = AbilityID::Attack;

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

		md.Level = 1;

		md.BaseHP = 200;
		md.BaseMP = 10;
		md.BaseSP = 100;

		md.BaseSTR = 8;
		md.BaseDEX = 12;
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
			std::pair<AbilityID, sf::Vector2i> ai;

			// Shadow Energy: Use when half HP, cast only once per encounter.
			if (monster->GetFlag(0) == 0 && monster->IsAbilityUsable(AbilityID::ShadowEnergy)) {
				if (monster->GetCurrentHP() < monster->GetMaxHP() / 2) {
					ai.second = monster->GetLocation();
					ai.first = AbilityID::ShadowEnergy;
					monster->SetFlag(0, 1);
				}
				else {
					ai.second = dungeonScene->GetPlayer()->GetLocation();
					ai.first = AbilityID::Attack;
				}
			}
			else {
				ai.second = dungeonScene->GetPlayer()->GetLocation();
				ai.first = AbilityID::Attack;
			}
			return ai;
		};

		return md;
	}();

	return list;
}

std::unordered_map<MonsterID, MonsterData> Monster::monsterList = initList();