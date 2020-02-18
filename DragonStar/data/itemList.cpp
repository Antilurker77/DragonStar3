// ================================================================
//
// itemList.cpp
//
// ================================================================

#include "item.hpp"

#include <iostream>
#include "id/abilityID.hpp"
#include "id/auraID.hpp"
#include "id/category.hpp"
#include "id/element.hpp"
#include "id/equipType.hpp"
#include "id/eventType.hpp"
#include "id/itemID.hpp"
#include "../core/combat.hpp"
#include "../core/random.hpp"
#include "../entity/actor.hpp"

static std::unordered_map<ItemID, ItemData> initList() {
	std::unordered_map<ItemID, ItemData> list;

	// Potions
	list[ItemID::PotionFruitJuice] = [] {
		ItemData itd;

		itd.Name = "Potion of Fruit Juice";
		itd.IconFilePath = "potion.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::PotionFruitJuice;
		itd.ItemType = ItemType::Potion;

		itd.InvokeAbility = AbilityID::PotionFruitJuice;

		itd.MaxStacks = 10;

		itd.BaseValue = 50;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PotionMinorHealing] = [] {
		ItemData itd;

		itd.Name = "Potion of Minor Healing";
		itd.IconFilePath = "potion.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::PotionMinorHealing;
		itd.ItemType = ItemType::Potion;

		itd.InvokeAbility = AbilityID::PotionMinorHealing;

		itd.MaxStacks = 10;

		itd.BaseValue = 50;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PotionSpeed] = [] {
		ItemData itd;

		itd.Name = "Potion of Speed";
		itd.IconFilePath = "potion.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::PotionSpeed;
		itd.ItemType = ItemType::Potion;

		itd.InvokeAbility = AbilityID::PotionSpeed;

		itd.MaxStacks = 10;

		itd.BaseValue = 250;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PotionStamina] = [] {
		ItemData itd;

		itd.Name = "Potion of Stamina";
		itd.IconFilePath = "potion.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::PotionStamina;
		itd.ItemType = ItemType::Potion;

		itd.InvokeAbility = AbilityID::PotionStamina;

		itd.MaxStacks = 10;

		itd.BaseValue = 250;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Scrolls

	// Rods

	// Rations
	list[ItemID::Rations] = [] {
		ItemData itd;

		itd.Name = "Rations";
		itd.IconFilePath = "ration.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::Rations;
		itd.ItemType = ItemType::Consumable;

		itd.InvokeAbility = AbilityID::Rest;

		itd.MaxStacks = 20;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Tomes
	list[ItemID::TomeTesting] = [] {
		ItemData itd;

		itd.Name = "Tome: Test";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeTesting;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 1;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::PhaseDoor,
			AbilityID::Teleport
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeCombatBasics] = [] {
		ItemData itd;

		itd.Name = "Tome: Combat Basics";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeCombatBasics;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::PowerStrike,
			AbilityID::ThunderStrike,
			AbilityID::RendingSlash,
			AbilityID::CrushArmor,
			AbilityID::Disarm,
			AbilityID::ImpactWave,
			AbilityID::Cleave,
			AbilityID::TornadoStrike,
			AbilityID::Constitution,
			AbilityID::Focus
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeLearningArchery] = [] {
		ItemData itd;

		itd.Name = "Tome: Learning Archery";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeLearningArchery;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::PowerShot,
			AbilityID::CriticalShot,
			AbilityID::PoisonArrow,
			AbilityID::Focus,
			AbilityID::DeadlyForce
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeMagicForBeginners] = [] {
		ItemData itd;

		itd.Name = "Tome: Magic for Beginners";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeMagicForBeginners;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::MagicMissile,
			AbilityID::MysticBlast,
			AbilityID::FlameBolt,
			AbilityID::WaterBolt,
			AbilityID::Shock,
			AbilityID::Icicle,
			AbilityID::Venom,
			AbilityID::ElementalEnergy
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeIntroductionToSpirituality] = [] {
		ItemData itd;

		itd.Name = "Tome: Introduction to Spirituality";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeIntroductionToSpirituality;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::BoltOfLight,
			AbilityID::BoltOfDarkness,
			AbilityID::Heal
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeArtOfFlame] = [] {
		ItemData itd;

		itd.Name = "Tome: Art of Flames";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeArtOfFlame;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::FlameBolt,
			AbilityID::DragonfireBolt,
			AbilityID::FieryTouch,
			AbilityID::FlameStrike
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeBodyMindAndSoul] = [] {
		ItemData itd;

		itd.Name = "Tome: Body, Mind, and Soul";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeBodyMindAndSoul;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::ImprovedStrength,
			AbilityID::ImprovedDexterity,
			AbilityID::ImprovedMagic,
			AbilityID::ImprovedVitality,
			AbilityID::ImprovedSpirit
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Swords
	list[ItemID::TravelerBlade] = []{
		ItemData itd;

		itd.Name = "Traveler's Blade";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "starting_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TravelerBlade;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 700;
		itd.AttackRange = 100;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 5)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::IronSword] = [] {
		ItemData itd;

		itd.Name = "Iron Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Sword
	list[ItemID::Flametongue] = [] {
		ItemData itd;

		itd.Name = "Flametongue";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "flametongue.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Flametongue;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 12)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 3),
			StatMod(StatModType::VIT, 2),
			StatMod(StatModType::CritChance, 50),
			StatMod(StatModType::Damage, 100, Element::Fire)
		};
		itd.BonusModStrings = {
			"20% On Attack: Deal 50 bonus fire damage."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						if (Random::RandomInt(1, 100) <= 20) {
							EventOptions proc;
							proc.EventName = "Flametongue";
							proc.Elements = { Element::Fire };
							proc.Categories = { Category::Attack, Category::SingleTarget, Category::Damaging };
							proc.CanDodge = false;

							Combat::FixedDamage(user, target, proc, 50);
						}
					}
				}
			}
		};

		return itd;
	}();

	// Axe
	list[ItemID::IronAxe] = [] {
		ItemData itd;

		itd.Name = "Iron Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Axe
	list[ItemID::BloodDrinker] = [] {
		ItemData itd;

		itd.Name = "Blood Drinker";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::BloodDrinker;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 11)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 1),
			StatMod(StatModType::DEX, 1),
			StatMod(StatModType::OnHitDamage, 3, Category::Direct),
			StatMod(StatModType::HPLeech, 200),
			StatMod(StatModType::Resistance, 300, Element::Dark)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Mace
	list[ItemID::IronMace] = [] {
		ItemData itd;

		itd.Name = "Iron Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Mace
	list[ItemID::Serenity] = [] {
		ItemData itd;

		itd.Name = "Serenity";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_mace.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Serenity;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 1),
			StatMod(StatModType::VIT, 1),
			StatMod(StatModType::SPI, 1),
			StatMod(StatModType::Healing, 200)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Dagger
	list[ItemID::IronDagger] = [] {
		ItemData itd;

		itd.Name = "Iron Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Dagger
	list[ItemID::TaintedBlade] = [] {
		ItemData itd;

		itd.Name = "Tainted Blade";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TaintedBlade;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::DEX, 2),
			StatMod(StatModType::ArmorPen, 150),
			StatMod(StatModType::DoubleStrikeChance, 30),
			StatMod(StatModType::Damage, 200, Element::Poison),
			StatMod(StatModType::Damage, 200, Element::Dark)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Spear
	list[ItemID::IronSpear] = [] {
		ItemData itd;

		itd.Name = "Iron Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Spear
	list[ItemID::WindScar] = [] {
		ItemData itd;

		itd.Name = "Wind Scar";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::WindScar;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 1),
			StatMod(StatModType::DEX, 2),
			StatMod(StatModType::OnHitDamage, 3, Category::Direct),
			StatMod(StatModType::ArmorPen, 450)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Bow
	list[ItemID::Shortbow] = [] {
		ItemData itd;

		itd.Name = "Shortbow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Shortbow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 50;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Bow
	list[ItemID::LongShot] = [] {
		ItemData itd;

		itd.Name = "Long Shot";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::LongShot;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 50;

		itd.Artifact = true;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 450;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 10)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::DEX, 2),
			StatMod(StatModType::Accuracy, 5),
			StatMod(StatModType::CritChance, 40)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Wand
	list[ItemID::WoodenWand] = [] {
		ItemData itd;

		itd.Name = "Wooden Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::WoodenWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 8),
			StatMod(StatModType::SpellPower, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Wand
	list[ItemID::SpiritfireTorch] = [] {
		ItemData itd;

		itd.Name = "Spiritfire Torch";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SpiritfireTorch;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Fire;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 8),
			StatMod(StatModType::SpellPower, 10)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MP, 5),
			StatMod(StatModType::MAG, 2),
			StatMod(StatModType::Damage, 100, Element::Fire),
			StatMod(StatModType::ResistancePen, 1000, Element::Fire)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Staff
	list[ItemID::WoodenStaff] = [] {
		ItemData itd;

		itd.Name = "Wooden Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::WoodenStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 600;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 6),
			StatMod(StatModType::SpellPower, 14)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Staff
	list[ItemID::StaffOfTheNovice] = [] {
		ItemData itd;

		itd.Name = "Staff of the Novice";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::StaffOfTheNovice;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 600;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 6),
			StatMod(StatModType::SpellPower, 14)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 3),
			StatMod(StatModType::MP, 10),
			StatMod(StatModType::Accuracy, 10),
			StatMod(StatModType::SpellPower, 3),
			StatMod(StatModType::Damage, 100, AbilityID::MagicMissile)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Shield
	list[ItemID::IronShield] = [] {
		ItemData itd;

		itd.Name = "Iron Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 5),
			StatMod(StatModType::BlockChance, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Shield
	list[ItemID::LastDefender] = [] {
		ItemData itd;

		itd.Name = "Last Defender";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::LastDefender;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 5),
			StatMod(StatModType::BlockChance, 100)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 12),
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::BlockChance, 30),
			StatMod(StatModType::CritPowerProtection, -500)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Light Head
	list[ItemID::SilkHat] = [] {
		ItemData itd;

		itd.Name = "Silk Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SilkHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 2),
			StatMod(StatModType::MagicArmor, 5)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Light Head
	list[ItemID::OraclesMonacle] = [] {
		ItemData itd;

		itd.Name = "Oracle's Monacle";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::OraclesMonacle;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::MagicArmor, 1),
			StatMod(StatModType::Evasion, 3)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 1),
			StatMod(StatModType::Accuracy, 3),
			StatMod(StatModType::EvasionMulti, 100),
			StatMod(StatModType::BlockChance, 50),
			StatMod(StatModType::Resistance, 300, Element::Light)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Light Body
	list[ItemID::SilkRobes] = [] {
		ItemData itd;

		itd.Name = "Silk Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SilkRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::Evasion, 3),
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Light Body
	list[ItemID::BerserkerVest] = [] {
		ItemData itd;

		itd.Name = "Berserker Vest";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::BerserkerVest;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 5)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 2),
			StatMod(StatModType::DEX, 2),
			StatMod(StatModType::Damage, 50),
			StatMod(StatModType::CritChance, 40),
			StatMod(StatModType::Haste, 40)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Light Hands
	list[ItemID::SilkGloves] = [] {
		ItemData itd;

		itd.Name = "Silk Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SilkGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 1),
			StatMod(StatModType::MagicArmor, 3)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Light Hands
	list[ItemID::ArcanistGloves] = [] {
		ItemData itd;

		itd.Name = "Arcanist Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ArcanistGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 1),
			StatMod(StatModType::MagicArmor, 3)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 1),
			StatMod(StatModType::SPI, 1),
			StatMod(StatModType::CritChance, 60)
		};
		itd.BonusModStrings = {
			"On Direct Spell Crit: Increase magic by 5 for 10s."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Spell) != eventOptions.Categories.end()) {
						if (eventResult.DidCrit) {
							Combat::AddAuraStack(user, user, eventOptions, AuraID::ArcanistGloves, 0);
						}
					}
				}
			}
		};

		return itd;
	}();

	// Light Feet
	list[ItemID::SilkBoots] = [] {
		ItemData itd;

		itd.Name = "Silk Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SilkBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 1),
			StatMod(StatModType::MagicArmor, 3),
			StatMod(StatModType::Evasion, 2)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Light Feet
	list[ItemID::Goldweave] = [] {
		ItemData itd;

		itd.Name = "Goldweave";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Goldweave;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 1),
			StatMod(StatModType::MagicArmor, 3),
			StatMod(StatModType::Evasion, 2)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::VIT, 2),
			StatMod(StatModType::MovementSpeed, 100),
			StatMod(StatModType::GoldFind, 200),
			StatMod(StatModType::Resistance, 300, Element::Lightning)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Medium Head
	list[ItemID::LeatherHelmet] = [] {
		ItemData itd;

		itd.Name = "Leather Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::LeatherHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 3),
			StatMod(StatModType::Evasion, 3)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Medium Head
	list[ItemID::SniperHelmet] = [] {
		ItemData itd;

		itd.Name = "Sniper Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::SniperHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 3),
			StatMod(StatModType::Evasion, 3)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::DEX, 2),
			StatMod(StatModType::Accuracy, 5),
			StatMod(StatModType::CritChance, 25),
			StatMod(StatModType::Range, 50, Category::Bow)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Medium Body
	list[ItemID::LeatherArmor] = [] {
		ItemData itd;

		itd.Name = "Leather Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::LeatherArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 30;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 4),
			StatMod(StatModType::Evasion, 8)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Medium Body
	list[ItemID::SurvivalArmor] = [] {
		ItemData itd;

		itd.Name = "Survival Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SurvivalArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 4),
			StatMod(StatModType::Evasion, 8)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::DEX, 1),
			StatMod(StatModType::VIT, 1),
			StatMod(StatModType::Evasion, 3),
			StatMod(StatModType::HPOnKill, 5),
			StatMod(StatModType::Resistance, 300, Element::Poison)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Medium Hands
	list[ItemID::LeatherGloves] = [] {
		ItemData itd;

		itd.Name = "Leather Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::LeatherGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 2),
			StatMod(StatModType::MagicArmor, 2),
			StatMod(StatModType::Evasion, 1)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Medium Hands
	list[ItemID::FrostfireGloves] = [] {
		ItemData itd;

		itd.Name = "Frostfire Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::FrostfireGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 2),
			StatMod(StatModType::MagicArmor, 2),
			StatMod(StatModType::Evasion, 1)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::Damage, 100, Element::Fire),
			StatMod(StatModType::Damage, 100, Element::Ice),
			StatMod(StatModType::CritChance, 25),
			StatMod(StatModType::Resistance, 300, Element::Fire),
			StatMod(StatModType::Resistance, 300, Element::Ice)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Medium Feet
	list[ItemID::LeatherBoots] = [] {
		ItemData itd;

		itd.Name = "Leather Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::LeatherBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 2),
			StatMod(StatModType::Evasion, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Medium Feet
	list[ItemID::Windriders] = [] {
		ItemData itd;

		itd.Name = "Windriders";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Windriders;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 2),
			StatMod(StatModType::Evasion, 6)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 5),
			StatMod(StatModType::DEX, 1),
			StatMod(StatModType::Evasion, 3),
			StatMod(StatModType::Haste, 50),
			StatMod(StatModType::MovementSpeed, 300)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Heavy Head
	list[ItemID::IronHelm] = [] {
		ItemData itd;

		itd.Name = "Iron Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::IronHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 1)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Heavy Head
	list[ItemID::HeraldOfVictory] = [] {
		ItemData itd;

		itd.Name = "Herald of Victory";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::HeraldOfVictory;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 1)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 7),
			StatMod(StatModType::STR, 1),
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::Damage, 100, Element::Physical),
			StatMod(StatModType::Resistance, 300, Element::Dark)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Heavy Body
	list[ItemID::IronArmor] = [] {
		ItemData itd;

		itd.Name = "Iron Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 17),
			StatMod(StatModType::MagicArmor, 2)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Heavy Body
	list[ItemID::GoldenArmor] = [] {
		ItemData itd;

		itd.Name = "Golden Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::GoldenArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 17),
			StatMod(StatModType::MagicArmor, 2)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 10),
			StatMod(StatModType::VIT, 2),
			StatMod(StatModType::GoldFind, 150),
			StatMod(StatModType::Resistance, 300, Element::Light)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Heavy Hands
	list[ItemID::IronGauntlets] = [] {
		ItemData itd;

		itd.Name = "Iron Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 1)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Heavy Hands
	list[ItemID::ArenaGauntlets] = [] {
		ItemData itd;

		itd.Name = "Arena Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ArenaGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 1)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HPOnKill, 3),
			StatMod(StatModType::STR, 2),
			StatMod(StatModType::AttackPower, 3),
			StatMod(StatModType::Haste, 75, Category::Attack)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Heavy Feet
	list[ItemID::IronGreaves] = [] {
		ItemData itd;

		itd.Name = "Iron Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 1),
			StatMod(StatModType::Evasion, 2)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Heavy Feet
	list[ItemID::LostMountainGreaves] = [] {
		ItemData itd;

		itd.Name = "Lost Mountain Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::LostMountainGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 20;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 1),
			StatMod(StatModType::Evasion, 2)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 1),
			StatMod(StatModType::VIT, 1),
			StatMod(StatModType::SnareResistance, 750),
			StatMod(StatModType::MovementSpeed, 100),
			StatMod(StatModType::Resistance, 300, Element::Ice)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Neck
	list[ItemID::SilverNecklace] = [] {
		ItemData itd;

		itd.Name = "Silver Necklace";
		itd.IconFilePath = "neck.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::SilverNecklace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Neck;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 2),
			StatMod(StatModType::SpellPower, 2)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Neck
	list[ItemID::RubyNecklace] = [] {
		ItemData itd;

		itd.Name = "Ruby Necklace";
		itd.IconFilePath = "neck.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::RubyNecklace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Neck;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 2),
			StatMod(StatModType::SpellPower, 2)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 30),
			StatMod(StatModType::HPOnKill, 5),
			StatMod(StatModType::Resistance, 300, Element::Fire)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Ring
	list[ItemID::IronRing] = [] {
		ItemData itd;

		itd.Name = "Iron Ring";
		itd.IconFilePath = "ring.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronRing;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Ring;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 1),
			StatMod(StatModType::SpellPower, 1)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Ring
	list[ItemID::RingOfVitality] = [] {
		ItemData itd;

		itd.Name = "Ring of Vitality";
		itd.IconFilePath = "ring.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::IronRing;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Ring;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 1),
			StatMod(StatModType::SpellPower, 1)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::VITMulti, 200)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Light Source
	list[ItemID::FloatingLantern] = [] {
		ItemData itd;

		itd.Name = "Floating Latern";
		itd.IconFilePath = "ring.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::FloatingLantern;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightSource;

		itd.ImplicitStatMods = {
			StatMod(StatModType::SightRadius, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Artifact Light Source
	list[ItemID::SpectralLantern] = [] {
		ItemData itd;

		itd.Name = "Spectral Latern";
		itd.IconFilePath = "ring.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::FloatingLantern;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightSource;

		itd.ImplicitStatMods = {
			StatMod(StatModType::SightRadius, 100)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::AllAttributes, 2),
			StatMod(StatModType::Resistance, 300, Element::Light)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	// Misc
	list[ItemID::DebugRing] = [] {
		ItemData itd;

		itd.Name = "Overpowered Developer Ring";
		itd.IconFilePath = "ring.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::DebugRing;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 777;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Ring;

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 8675),
			StatMod(StatModType::MP, 309),
			StatMod(StatModType::AllAttributes, 100),
			StatMod(StatModType::Accuracy, 200)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();

	return list;
}

std::unordered_map<ItemID, ItemData> Item::itemList = initList();