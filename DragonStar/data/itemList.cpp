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
#include "../core/tileMath.hpp"
#include "../entity/actor.hpp"
#include "../scene/dungeonScene.hpp"
#include "../ui/inventory.hpp"

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
	list[ItemID::PotionLesserHealing] = [] {
		ItemData itd;

		itd.Name = "Potion of Lesser Healing";
		itd.IconFilePath = "potion.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::PotionLesserHealing;
		itd.ItemType = ItemType::Potion;

		itd.InvokeAbility = AbilityID::PotionLesserHealing;

		itd.MaxStacks = 10;

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
	list[ItemID::PotionMinorMana] = [] {
		ItemData itd;

		itd.Name = "Potion of Minor Mana";
		itd.IconFilePath = "potion.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::PotionMinorMana;
		itd.ItemType = ItemType::Potion;

		itd.InvokeAbility = AbilityID::PotionMinorMana;

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
	list[ItemID::ScrollIdentify] = [] {
		ItemData itd;

		itd.Name = "Scroll of Identify";
		itd.IconFilePath = "scroll.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::ScrollIdentify;
		itd.ItemType = ItemType::Scroll;

		itd.InvokeAbility = AbilityID::ScrollIdentify;

		itd.MaxStacks = 10;

		itd.BaseValue = 75;

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
	list[ItemID::ScrollLightningStorm] = [] {
		ItemData itd;

		itd.Name = "Scroll of Lightning Storm";
		itd.IconFilePath = "scroll.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::ScrollLightningStorm;
		itd.ItemType = ItemType::Scroll;

		itd.InvokeAbility = AbilityID::ScrollLightningStorm;

		itd.MaxStacks = 10;

		itd.BaseValue = 75;

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
	list[ItemID::ScrollMagicMapping] = [] {
		ItemData itd;

		itd.Name = "Scroll of Magic Mapping";
		itd.IconFilePath = "scroll.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::ScrollMagicMapping;
		itd.ItemType = ItemType::Scroll;

		itd.InvokeAbility = AbilityID::ScrollMagicMapping;

		itd.MaxStacks = 10;

		itd.BaseValue = 75;

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
	list[ItemID::ScrollPhaseDoor] = [] {
		ItemData itd;

		itd.Name = "Scroll of Phase Door";
		itd.IconFilePath = "scroll.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::ScrollPhaseDoor;
		itd.ItemType = ItemType::Scroll;

		itd.InvokeAbility = AbilityID::ScrollPhaseDoor;

		itd.MaxStacks = 10;

		itd.BaseValue = 75;

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
	list[ItemID::ScrollSpellProtection] = [] {
		ItemData itd;

		itd.Name = "Scroll of Spell Protection";
		itd.IconFilePath = "scroll.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::ScrollSpellProtection;
		itd.ItemType = ItemType::Scroll;

		itd.InvokeAbility = AbilityID::ScrollSpellProtection;

		itd.MaxStacks = 10;

		itd.BaseValue = 75;

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
	list[ItemID::ScrollTeleport] = [] {
		ItemData itd;

		itd.Name = "Scroll of Teleport";
		itd.IconFilePath = "scroll.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::ScrollTeleport;
		itd.ItemType = ItemType::Scroll;

		itd.InvokeAbility = AbilityID::ScrollTeleport;

		itd.MaxStacks = 10;

		itd.BaseValue = 75;

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

		itd.BaseValue = 30;

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
			AbilityID::FlameStrike,
			AbilityID::Ignite,
			AbilityID::SpectralSlash
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

		itd.BaseValue = 75;

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
			AbilityID::Constitution
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeOneManArmy] = [] {
		ItemData itd;

		itd.Name = "Tome: One-Man Army";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeOneManArmy;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::Cleave,
			AbilityID::ImpactWave,
			AbilityID::TornadoStrike
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeAxeTechniques] = [] {
		ItemData itd;

		itd.Name = "Tome: Axe Techniques";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeAxeTechniques;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::Chopper,
			AbilityID::RendingSlash,
			AbilityID::Cleave
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeMaceTechniques] = [] {
		ItemData itd;

		itd.Name = "Tome: Mace Techniques";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeMaceTechniques;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::CrushingBlow,
			AbilityID::CrushArmor
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeAdvancedCombat] = [] {
		ItemData itd;

		itd.Name = "Tome: Advanced Combat";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeAdvancedCombat;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::HerosTriumph,
			AbilityID::FuriousStrike,
			AbilityID::Disarm,
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

		itd.BaseValue = 75;

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

		itd.BaseValue = 75;

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
			AbilityID::FlameBolt,
			AbilityID::WaterBolt,
			AbilityID::Shock,
			AbilityID::Icicle,
			AbilityID::Venom
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeArcaneEnergy] = [] {
		ItemData itd;

		itd.Name = "Tome: Arcane Energy";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeArcaneEnergy;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 75;

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
			AbilityID::ArcaneSpear,
			AbilityID::CastingCircle,
			AbilityID::ManaSpring
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeIntermediateMagic] = [] {
		ItemData itd;

		itd.Name = "Tome: Intermediate Magic";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeIntermediateMagic;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::MysticBlast,
			AbilityID::DragonfireBolt,
			AbilityID::Splash,
			AbilityID::ElectricSurge,
			AbilityID::Bonechill,
			AbilityID::Infect,
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

		itd.BaseValue = 75;

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
			AbilityID::ShiningPrism,
			AbilityID::BoltOfDarkness,
			AbilityID::ShadowFlay,
			AbilityID::Heal,
			AbilityID::Regenerate
		};

		itd.ImplicitStatMods = {};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TomeSpaceManipulation] = [] {
		ItemData itd;

		itd.Name = "Tome: Space Manipulation";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeSpaceManipulation;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::MysticBlast,
			AbilityID::PhaseDoor,
			AbilityID::Teleport
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

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::Blaze,
			AbilityID::Ignite,
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
	list[ItemID::TomeBasicsOfHealing] = [] {
		ItemData itd;

		itd.Name = "Tome: Basics of Healing";
		itd.IconFilePath = "tome.png";
		itd.EquipFilePath = "";

		itd.HideHair = false;

		itd.ItemID = ItemID::TomeBasicsOfHealing;
		itd.ItemType = ItemType::Tome;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Undefined;
		itd.AttackElement = Element::Undefined;
		itd.HitChance = 0;
		itd.AttackRange = 0;
		itd.AttackSpeed = 0;
		itd.WeaponDamageMultiplier = 0;

		itd.TeachableAbilities = {
			AbilityID::Heal,
			AbilityID::GrandHeal,
			AbilityID::SwiftHeal,
			AbilityID::Regenerate,
			AbilityID::HealingEfficiency
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

		itd.BaseValue = 125;

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
		itd.HitChance = 750;
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
	list[ItemID::RunedSword] = [] {
		ItemData itd;

		itd.Name = "Runed Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 60;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 16),
			StatMod(StatModType::SpellPower, 12)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SteelSword] = [] {
		ItemData itd;

		itd.Name = "Steel Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 25)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumSword] = [] {
		ItemData itd;

		itd.Name = "Platinum Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 45)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumSword] = [] {
		ItemData itd;

		itd.Name = "Titanium Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 70)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilSword] = [] {
		ItemData itd;

		itd.Name = "Mythril Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalSword] = [] {
		ItemData itd;

		itd.Name = "Crystal Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 135)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteSword] = [] {
		ItemData itd;

		itd.Name = "Adamantite Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 175)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteSword] = [] {
		ItemData itd;

		itd.Name = "Dragonite Sword";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteSword;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 650;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 225)
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
	list[ItemID::DustDevil] = [] {
		ItemData itd;

		itd.Name = "Dust Devil";
		itd.IconFilePath = "sword.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DustDevil;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Sword;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 27)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 4),
			StatMod(StatModType::DEX, 2),
			StatMod(StatModType::Haste, 50),
			StatMod(StatModType::DoubleStrikeChance, 100)
		};
		itd.BonusModStrings = {
			"On Attack: Reduce target's accuracy by 7 for 5s."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						Combat::AddAuraStack(user, target, eventOptions, AuraID::DustDevil, 0);
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
	list[ItemID::JaggedAxe] = [] {
		ItemData itd;

		itd.Name = "Jagged Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::JaggedAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 60;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 16),
			StatMod(StatModType::OnHitDamage, 5, Category::Direct)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SteelAxe] = [] {
		ItemData itd;

		itd.Name = "Steel Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 25)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumAxe] = [] {
		ItemData itd;

		itd.Name = "Platinum Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 45)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumAxe] = [] {
		ItemData itd;

		itd.Name = "Titanium Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 70)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilAxe] = [] {
		ItemData itd;

		itd.Name = "Mythril Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalAxe] = [] {
		ItemData itd;

		itd.Name = "Crystal Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 135)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteAxe] = [] {
		ItemData itd;

		itd.Name = "Adamantite Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 175)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteAxe] = [] {
		ItemData itd;

		itd.Name = "Dragonite Axe";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragoniteAxe;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 650;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 225)
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
			StatMod(StatModType::Resistance, 250, Element::Dark)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::Chaotica] = [] {
		ItemData itd;

		itd.Name = "Chaotica";
		itd.IconFilePath = "axe.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Chaotica;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Axe;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 180;
		itd.WeaponDamageMultiplier = 900;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 27)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 5),
			StatMod(StatModType::Accuracy, 4),
			StatMod(StatModType::Haste, 50),
			StatMod(StatModType::DoubleStrikeChance, 90)
		};
		itd.BonusModStrings = {
			"On Hit: Deals 1 to 20 bonus dark damage."
		};


		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						EventOptions proc;
						proc.EventName = "Chaotica";
						proc.Elements = { Element::Dark };
						proc.Categories = { Category::Attack, Category::SingleTarget, Category::Damaging };
						proc.CanDodge = false;

						int damage = Random::RandomInt(1, 20);

						Combat::FixedDamage(user, target, proc, damage);
					}
				}
			}
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
	list[ItemID::SteelMace] = [] {
		ItemData itd;

		itd.Name = "Steel Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 25)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumMace] = [] {
		ItemData itd;

		itd.Name = "Platinum Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 45)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumMace] = [] {
		ItemData itd;

		itd.Name = "Titanium Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 70)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilMace] = [] {
		ItemData itd;

		itd.Name = "Mythril Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalMace] = [] {
		ItemData itd;

		itd.Name = "Crystal Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 135)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteMace] = [] {
		ItemData itd;

		itd.Name = "Adamantite Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 175)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteMace] = [] {
		ItemData itd;

		itd.Name = "Adamantite Mace";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteMace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 625;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 225)
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
	list[ItemID::SiegeBreaker] = [] {
		ItemData itd;

		itd.Name = "Siege Breaker";
		itd.IconFilePath = "mace.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SiegeBreaker;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Mace;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 220;
		itd.WeaponDamageMultiplier = 1100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 28)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 5),
			StatMod(StatModType::VIT, 2),
			StatMod(StatModType::CritChance, 60),
			StatMod(StatModType::CritPower, 100)
		};
		itd.BonusModStrings = {
			"On Direct Crit: Stuns for 0.5s."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						if (eventResult.DidCrit) {
							Combat::AddAuraStack(user, target, eventOptions, AuraID::SiegeBreaker, 0);
						}
					}
				}
			}
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
	list[ItemID::SteelDagger] = [] {
		ItemData itd;

		itd.Name = "Steel Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 25)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumDagger] = [] {
		ItemData itd;

		itd.Name = "Platinum Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 45)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumDagger] = [] {
		ItemData itd;

		itd.Name = "Titanium Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 70)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilDagger] = [] {
		ItemData itd;

		itd.Name = "Myhtril Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalDagger] = [] {
		ItemData itd;

		itd.Name = "Crystal Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 135)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteDagger] = [] {
		ItemData itd;

		itd.Name = "Adamantite Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 175)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteDagger] = [] {
		ItemData itd;

		itd.Name = "Dragonite Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 625;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 225)
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
	list[ItemID::CrimsonDagger] = [] {
		ItemData itd;

		itd.Name = "Crimson Dagger";
		itd.IconFilePath = "dagger.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrimsonDagger;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Dagger;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 100;
		itd.AttackSpeed = 150;
		itd.WeaponDamageMultiplier = 750;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 27)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 3),
			StatMod(StatModType::DEX, 4),
			StatMod(StatModType::Damage, 250, Category::OverTime, Element::Physical),
			StatMod(StatModType::CooldownReduction, 150)
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
	list[ItemID::SteelSpear] = [] {
		ItemData itd;

		itd.Name = "Steel Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 25)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumSpear] = [] {
		ItemData itd;

		itd.Name = "Platinum Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 45)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumSpear] = [] {
		ItemData itd;

		itd.Name = "Titanium Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 70)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilSpear] = [] {
		ItemData itd;

		itd.Name = "Mythril Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalSpear] = [] {
		ItemData itd;

		itd.Name = "Crystal Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 135)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteSpear] = [] {
		ItemData itd;

		itd.Name = "Adamantite Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 175)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteSpear] = [] {
		ItemData itd;

		itd.Name = "Dragonite Spear";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragoniteSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 625;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 225)
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
	list[ItemID::RagingRiver] = [] {
		ItemData itd;

		itd.Name = "Raging River";
		itd.IconFilePath = "spear.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelSpear;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Spear;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 200;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 26)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 3),
			StatMod(StatModType::DEX, 4),
			StatMod(StatModType::MAG, 3),
			StatMod(StatModType::Haste, 50)
		};
		itd.BonusModStrings = {
			"8% Chance on Direct Attack: Deal 60 water damage and reduce the MP cost of your next spell by 25%."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						if (Random::RandomInt(1, 100) <= 8) {
							EventOptions proc;
							proc.EventName = "Raging River";
							proc.Elements = { Element::Water };
							proc.Categories = { Category::Attack, Category::SingleTarget, Category::Damaging };
							proc.CanDodge = false;

							Combat::FixedDamage(user, target, proc, 60);
							Combat::AddAuraStack(user, user, eventOptions, AuraID::Waterfall, 0);
						}
					}
				}
			}
		};

		return itd;
	}();

	// Bow
	list[ItemID::TrainingBow] = [] {
		ItemData itd;

		itd.Name = "Training Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TrainingBow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 5)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
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
	list[ItemID::Longbow] = [] {
		ItemData itd;

		itd.Name = "Longbow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Longbow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 25)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CompositeBow] = [] {
		ItemData itd;

		itd.Name = "Composite Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CompositeBow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 45)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::ElvenBow] = [] {
		ItemData itd;

		itd.Name = "Elven Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ElvenBow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 70)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MoonBow] = [] {
		ItemData itd;

		itd.Name = "Moon Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MoonBow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythicalBow] = [] {
		ItemData itd;

		itd.Name = "Mythical Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythicalBow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 135)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::ZodiacBow] = [] {
		ItemData itd;

		itd.Name = "Zodiac Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ZodiacBow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 175)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragonBow] = [] {
		ItemData itd;

		itd.Name = "Dragon Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragonBow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 625;

		itd.Artifact = false;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 225)
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
	list[ItemID::HomingBow] = [] {
		ItemData itd;

		itd.Name = "Homing Bow";
		itd.IconFilePath = "longbow.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::Longbow;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.Artifact = true;
		itd.TwoHanded = true;
		itd.EquipType = EquipType::Bow;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 28)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 3),
			StatMod(StatModType::DEX, 5),
			StatMod(StatModType::CritChance, 75),
			StatMod(StatModType::Accuracy, 30)
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
	list[ItemID::ApprenticeWand] = [] {
		ItemData itd;

		itd.Name = "Apprentice's Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ApprenticeWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 20),
			StatMod(StatModType::SpellPower, 25)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::RunedWand] = [] {
		ItemData itd;

		itd.Name = "Runed Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 36),
			StatMod(StatModType::SpellPower, 45)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SpelloakWand] = [] {
		ItemData itd;

		itd.Name = "Spelloak Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SpelloakWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 56),
			StatMod(StatModType::SpellPower, 70)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SageWand] = [] {
		ItemData itd;

		itd.Name = "Sage's Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SageWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 80),
			StatMod(StatModType::SpellPower, 100)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MysticWand] = [] {
		ItemData itd;

		itd.Name = "Mystic Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MysticWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 108),
			StatMod(StatModType::SpellPower, 135)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MasterWand] = [] {
		ItemData itd;

		itd.Name = "Master's Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MasterWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 140),
			StatMod(StatModType::SpellPower, 175)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DraconicWand] = [] {
		ItemData itd;

		itd.Name = "Draconic Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DraconicWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 625;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 180),
			StatMod(StatModType::SpellPower, 225)
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
	list[ItemID::BatteryWand] = [] {
		ItemData itd;

		itd.Name = "Battery Wand";
		itd.IconFilePath = "wand.png";
		itd.EquipFilePath = "iron_sword.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ApprenticeWand;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Wand;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 350;
		itd.AttackSpeed = 200;
		itd.WeaponDamageMultiplier = 1000;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 20),
			StatMod(StatModType::SpellPower, 28)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 4),
			StatMod(StatModType::SPI, 4),
			StatMod(StatModType::MP, 25),
			StatMod(StatModType::MPCostReduction, 150),
			StatMod(StatModType::Damage, 100, Element::Lightning)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	

	// Staff
	list[ItemID::RunedStick] = [] {
		ItemData itd;

		itd.Name = "Runed Stick";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "runed_stick.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedStick;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 30;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 3),
			StatMod(StatModType::SpellPower, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
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
		itd.HitChance = 750;
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
	list[ItemID::ApprenticeStaff] = [] {
		ItemData itd;

		itd.Name = "Apprentice's Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ApprenticeStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 15),
			StatMod(StatModType::SpellPower, 35)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::RunedStaff] = [] {
		ItemData itd;

		itd.Name = "Runed Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 140;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 27),
			StatMod(StatModType::SpellPower, 63)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SpelloakStaff] = [] {
		ItemData itd;

		itd.Name = "Spelloak Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SpelloakStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 42),
			StatMod(StatModType::SpellPower, 98)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SageStaff] = [] {
		ItemData itd;

		itd.Name = "Sage's Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SageStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 60),
			StatMod(StatModType::SpellPower, 140)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MysticStaff] = [] {
		ItemData itd;

		itd.Name = "Mystic Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MysticStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 400;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 81),
			StatMod(StatModType::SpellPower, 189)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MasterStaff] = [] {
		ItemData itd;

		itd.Name = "Master's Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MasterStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 500;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 105),
			StatMod(StatModType::SpellPower, 245)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DraconicStaff] = [] {
		ItemData itd;

		itd.Name = "Draconic Staff";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DraconicStaff;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 625;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 135),
			StatMod(StatModType::SpellPower, 315)
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
	list[ItemID::CalcifiedSnake] = [] {
		ItemData itd;

		itd.Name = "Calcified Snake";
		itd.IconFilePath = "staff.png";
		itd.EquipFilePath = "wooden_staff.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CalcifiedSnake;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 80;

		itd.Artifact = false;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Staff;
		itd.AttackElement = Element::Physical;
		itd.HitChance = 750;
		itd.AttackRange = 150;
		itd.AttackSpeed = 250;
		itd.WeaponDamageMultiplier = 1250;

		itd.ImplicitStatMods = {
			StatMod(StatModType::AttackPower, 15),
			StatMod(StatModType::SpellPower, 38)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 4),
			StatMod(StatModType::VIT, 2),
			StatMod(StatModType::SPI, 3),
			StatMod(StatModType::CooldownReduction, 100),
			StatMod(StatModType::Damage, 300, Category::OverTime, Element::Poison)
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
	list[ItemID::SteelShield] = [] {
		ItemData itd;

		itd.Name = "Steel Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::BlockChance, 120)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumShield] = [] {
		ItemData itd;

		itd.Name = "Platinum Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 70;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 15),
			StatMod(StatModType::MagicArmor, 15),
			StatMod(StatModType::BlockChance, 150)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumShield] = [] {
		ItemData itd;

		itd.Name = "Titanium Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 22),
			StatMod(StatModType::MagicArmor, 22),
			StatMod(StatModType::BlockChance, 180)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilShield] = [] {
		ItemData itd;

		itd.Name = "Mythril Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 150;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 30),
			StatMod(StatModType::MagicArmor, 30),
			StatMod(StatModType::BlockChance, 210)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalShield] = [] {
		ItemData itd;

		itd.Name = "Crystal Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 40),
			StatMod(StatModType::MagicArmor, 40),
			StatMod(StatModType::BlockChance, 250)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteShield] = [] {
		ItemData itd;

		itd.Name = "Adamantite Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 250;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 47),
			StatMod(StatModType::MagicArmor, 47),
			StatMod(StatModType::BlockChance, 300)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteShield] = [] {
		ItemData itd;

		itd.Name = "Dragonite Shield";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragoniteShield;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 325;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 55),
			StatMod(StatModType::MagicArmor, 55),
			StatMod(StatModType::BlockChance, 350)
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
	list[ItemID::ArcanistBulwark] = [] {
		ItemData itd;

		itd.Name = "Arcanist Bulwark";
		itd.IconFilePath = "shield.png";
		itd.EquipFilePath = "iron_shield.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ArcanistBulwark;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::Shield;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::BlockChance, 120)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 3),
			StatMod(StatModType::SPI, 3),
			StatMod(StatModType::MagicArmor, 6),
			StatMod(StatModType::BlockChance, 120, Category::Spell),
			StatMod(StatModType::DamageTaken, -150, { Category::OverTime, Category::Spell })
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
	list[ItemID::ApprenticeHat] = [] {
		ItemData itd;

		itd.Name = "Apprentice Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ApprenticeHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 4),
			StatMod(StatModType::MagicArmor, 9)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::RunedHat] = [] {
		ItemData itd;

		itd.Name = "Runed Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 14)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SpellthreadHat] = [] {
		ItemData itd;

		itd.Name = "Spellthread Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SpellthreadHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 21)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SageHat] = [] {
		ItemData itd;

		itd.Name = "Sage's Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SageHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 12),
			StatMod(StatModType::MagicArmor, 29)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MysticHat] = [] {
		ItemData itd;

		itd.Name = "Mystic Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MysticHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 16),
			StatMod(StatModType::MagicArmor, 38)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MasterHat] = [] {
		ItemData itd;

		itd.Name = "Master's Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MasterHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 19),
			StatMod(StatModType::MagicArmor, 44)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DraconicHat] = [] {
		ItemData itd;

		itd.Name = "Draconic Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DraconicHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 22),
			StatMod(StatModType::MagicArmor, 54)
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
			StatMod(StatModType::Resistance, 250, Element::Light)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DundreHat] = [] {
		ItemData itd;

		itd.Name = "Dundre's Hat";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DundreHat;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 4),
			StatMod(StatModType::MagicArmor, 9)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 10),
			StatMod(StatModType::MAG, 2),
			StatMod(StatModType::SPI, 2),
			StatMod(StatModType::Armor, 4)
		};
		itd.BonusModStrings = {
			"Deal 25% more spell damage to targets at or above 99% of their max HP."
		};


		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::PostCalcDamage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Spell) != eventOptions.Categories.end()) {
					int hpPercent = target->GetCurrentHP() * 1000 / target->GetMaxHP();
					if (hpPercent >= 990) {
						amount = amount * 1250 / 1000;
					}
				}
			}
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
	list[ItemID::ApprenticeRobes] = [] {
		ItemData itd;

		itd.Name = "Apprentice Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ApprenticeRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 60;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 16),
			StatMod(StatModType::Evasion, 6),
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::RunedRobes] = [] {
		ItemData itd;

		itd.Name = "Runed Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 27),
			StatMod(StatModType::Evasion, 9),
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SpellthreadRobes] = [] {
		ItemData itd;

		itd.Name = "Spellthread Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SpellthreadRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 150;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 13),
			StatMod(StatModType::MagicArmor, 40),
			StatMod(StatModType::Evasion, 12),
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SageRobes] = [] {
		ItemData itd;

		itd.Name = "Sage Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SageRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 18),
			StatMod(StatModType::MagicArmor, 55),
			StatMod(StatModType::Evasion, 15),
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MysticRobes] = [] {
		ItemData itd;

		itd.Name = "Mystic Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MysticRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 275;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 24),
			StatMod(StatModType::MagicArmor, 73),
			StatMod(StatModType::Evasion, 18),
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MasterRobes] = [] {
		ItemData itd;

		itd.Name = "Master Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MasterRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 350;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 28),
			StatMod(StatModType::MagicArmor, 85),
			StatMod(StatModType::Evasion, 20),
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DraconicRobes] = [] {
		ItemData itd;

		itd.Name = "Draconic Robes";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DraconicRobes;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 450;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 32),
			StatMod(StatModType::MagicArmor, 98),
			StatMod(StatModType::Evasion, 21),
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
	list[ItemID::SirenEmbrace] = [] {
		ItemData itd;

		itd.Name = "Siren's Embrace";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SirenEmbrace;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 60;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Evasion, 6)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MP, 10),
			StatMod(StatModType::Evasion, 24),
			StatMod(StatModType::MovementSpeed, 50),
			StatMod(StatModType::Resistance, 500, Element::Water)
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
	list[ItemID::ApprenticeGloves] = [] {
		ItemData itd;

		itd.Name = "Apprentice Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ApprenticeGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 2),
			StatMod(StatModType::MagicArmor, 5)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::RunedGloves] = [] {
		ItemData itd;

		itd.Name = "Runed Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 9)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SpellthreadGloves] = [] {
		ItemData itd;

		itd.Name = "Spellthread Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SpellthreadGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 4),
			StatMod(StatModType::MagicArmor, 13)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SageGloves] = [] {
		ItemData itd;

		itd.Name = "Sage's Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SageGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 18)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MysticGloves] = [] {
		ItemData itd;

		itd.Name = "Mystic Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MysticGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 8),
			StatMod(StatModType::MagicArmor, 24)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MasterGloves] = [] {
		ItemData itd;

		itd.Name = "Master's Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MasterGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 28)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DraconicGloves] = [] {
		ItemData itd;

		itd.Name = "Draconic Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DraconicGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 11),
			StatMod(StatModType::MagicArmor, 33)
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
	list[ItemID::TetraGloves] = [] {
		ItemData itd;

		itd.Name = "Tetra Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TetraGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 2),
			StatMod(StatModType::MagicArmor, 5)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 3),
			StatMod(StatModType::SPI, 2),
			StatMod(StatModType::CritChance, 50),
			StatMod(StatModType::Haste, 40),
			StatMod(StatModType::Damage, 150, Element::Fire),
			StatMod(StatModType::Damage, 150, Element::Ice),
			StatMod(StatModType::Damage, 150, Element::Lightning),
			StatMod(StatModType::Damage, 150, Element::Water)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

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
	list[ItemID::ApprenticeBoots] = [] {
		ItemData itd;

		itd.Name = "Apprentice Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ApprenticeBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 2),
			StatMod(StatModType::MagicArmor, 5),
			StatMod(StatModType::Evasion, 4)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::RunedBoots] = [] {
		ItemData itd;

		itd.Name = "Runed Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::RunedBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::Evasion, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SpellthreadBoots] = [] {
		ItemData itd;

		itd.Name = "Spellthread Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SpellthreadBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 4),
			StatMod(StatModType::MagicArmor, 13),
			StatMod(StatModType::Evasion, 8)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::SageBoots] = [] {
		ItemData itd;

		itd.Name = "Sage's Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SageBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 18),
			StatMod(StatModType::Evasion, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MysticBoots] = [] {
		ItemData itd;

		itd.Name = "Mystic Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MysticBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 8),
			StatMod(StatModType::MagicArmor, 24),
			StatMod(StatModType::Evasion, 12)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MasterBoots] = [] {
		ItemData itd;

		itd.Name = "Master's Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MasterBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 28),
			StatMod(StatModType::Evasion, 13)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DraconicBoots] = [] {
		ItemData itd;

		itd.Name = "Draconic Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DraconicBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 11),
			StatMod(StatModType::MagicArmor, 33),
			StatMod(StatModType::Evasion, 14)
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
			StatMod(StatModType::Resistance, 250, Element::Lightning)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::ManaChargers] = [] {
		ItemData itd;

		itd.Name = "Mana Chargers";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ManaChargers;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::LightFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 2),
			StatMod(StatModType::MagicArmor, 5),
			StatMod(StatModType::Evasion, 4)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::MAG, 2),
			StatMod(StatModType::SPI, 2),
			StatMod(StatModType::CritChance, 30),
			StatMod(StatModType::MovementSpeed, 120)
		};
		itd.BonusModStrings = {
			"On Direct Spell Crit: Restore 2 MP."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Spell) != eventOptions.Categories.end()) {
						if (eventResult.DidCrit == true) {
							EventOptions eo;
							eo.EventName = "Mana Chargers";
							eo.Categories = { Category::Healing };
							eo.Elements = { Element::Healing };
							eo.CanCrit = false;
							Combat::FixedHeal(user, user, eo, 2, AttributeType::MP);
						}
					}
				}
			}
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
	list[ItemID::HunterHelmet] = [] {
		ItemData itd;

		itd.Name = "Hunter Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::HunterHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 5),
			StatMod(StatModType::Evasion, 5)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::WildHelmet] = [] {
		ItemData itd;

		itd.Name = "Wild Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::WildHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::Evasion, 7)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DrakescaleHelmet] = [] {
		ItemData itd;

		itd.Name = "Drakescale Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::DrakescaleHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 13),
			StatMod(StatModType::MagicArmor, 13),
			StatMod(StatModType::Evasion, 9)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MoonLeatherHelmet] = [] {
		ItemData itd;

		itd.Name = "Moon Leather Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::MoonLeatherHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 18),
			StatMod(StatModType::MagicArmor, 18),
			StatMod(StatModType::Evasion, 11)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythicalLeatherHelmet] = [] {
		ItemData itd;

		itd.Name = "Mythical Leather Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::MythicalLeatherHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 24),
			StatMod(StatModType::MagicArmor, 24),
			StatMod(StatModType::Evasion, 13)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::ZodiacHelmet] = [] {
		ItemData itd;

		itd.Name = "Zodiac Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::ZodiacHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 28),
			StatMod(StatModType::MagicArmor, 28),
			StatMod(StatModType::Evasion, 14)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragonscaleHelmet] = [] {
		ItemData itd;

		itd.Name = "Dragonscale Helmet";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::DragonscaleHelmet;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 33),
			StatMod(StatModType::MagicArmor, 33),
			StatMod(StatModType::Evasion, 15)
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
	list[ItemID::RoguesPlunder] = [] {
		ItemData itd;

		itd.Name = "Rogue's Plunder";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::RoguesPlunder;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 5),
			StatMod(StatModType::Evasion, 5)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 1),
			StatMod(StatModType::DEX, 3),
			StatMod(StatModType::Resistance, 250, Element::Poison)
		};
		itd.BonusModStrings = {
			"10% On Direct Attack: Loot 1-5 gold."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						int roll = Random::RandomInt(1, 100);
						if (roll <= 10) {
							roll = Random::RandomInt(1, 5);
							Inventory* inventory = user->GetDungeonScene()->GetInventory();
							inventory->ChangeGold(roll);
						}
					}
				}
			}
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
	list[ItemID::HunterArmor] = [] {
		ItemData itd;

		itd.Name = "Hunter Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::HunterArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 60;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 16),
			StatMod(StatModType::MagicArmor, 7),
			StatMod(StatModType::Evasion, 16)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::WildArmor] = [] {
		ItemData itd;

		itd.Name = "Hunter Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::HunterArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 100;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 27),
			StatMod(StatModType::MagicArmor, 12),
			StatMod(StatModType::Evasion, 24)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DrakescaleArmor] = [] {
		ItemData itd;

		itd.Name = "Drakescale Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DrakescaleArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 150;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 40),
			StatMod(StatModType::MagicArmor, 18),
			StatMod(StatModType::Evasion, 32)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MoonLeatherArmor] = [] {
		ItemData itd;

		itd.Name = "Moon Leather Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MoonLeatherArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 200;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 55),
			StatMod(StatModType::MagicArmor, 24),
			StatMod(StatModType::Evasion, 40)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythicalLeatherArmor] = [] {
		ItemData itd;

		itd.Name = "Mythical Leather Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythicalLeatherArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 275;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 73),
			StatMod(StatModType::MagicArmor, 32),
			StatMod(StatModType::Evasion, 48)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::ZodiacArmor] = [] {
		ItemData itd;

		itd.Name = "Zodiac Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ZodiacArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 350;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 85),
			StatMod(StatModType::MagicArmor, 38),
			StatMod(StatModType::Evasion, 52)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragonscaleArmor] = [] {
		ItemData itd;

		itd.Name = "Dragonscale Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragonscaleArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 450;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 98),
			StatMod(StatModType::MagicArmor, 47),
			StatMod(StatModType::Evasion, 56)
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
			StatMod(StatModType::Resistance, 250, Element::Poison)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PrismaticScaleArmor] = [] {
		ItemData itd;

		itd.Name = "Prismatic Scale Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PrismaticScaleArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumBody;

		itd.BaseValue = 60;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 13),
			StatMod(StatModType::MagicArmor, 13),
			StatMod(StatModType::Evasion, 13)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::AllAttributes, 1),
			StatMod(StatModType::Resistance, 250, Element::Arcane),
			StatMod(StatModType::Resistance, 250, Element::Fire),
			StatMod(StatModType::Resistance, 250, Element::Ice),
			StatMod(StatModType::Resistance, 250, Element::Lightning),
			StatMod(StatModType::Resistance, 250, Element::Water),
			StatMod(StatModType::Resistance, 250, Element::Poison),
			StatMod(StatModType::Resistance, 250, Element::Light),
			StatMod(StatModType::Resistance, 250, Element::Dark)
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
	list[ItemID::HunterGloves] = [] {
		ItemData itd;

		itd.Name = "Hunter Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::HunterGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 4),
			StatMod(StatModType::MagicArmor, 4),
			StatMod(StatModType::Evasion, 2)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::WildGloves] = [] {
		ItemData itd;

		itd.Name = "Wild Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::WildGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 6),
			StatMod(StatModType::MagicArmor, 6),
			StatMod(StatModType::Evasion, 3)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DrakescaleGloves] = [] {
		ItemData itd;

		itd.Name = "Drakescale Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DrakescaleGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::Evasion, 4)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MoonLeatherGloves] = [] {
		ItemData itd;

		itd.Name = "Moon Leather Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MoonLeatherGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 12),
			StatMod(StatModType::MagicArmor, 12),
			StatMod(StatModType::Evasion, 5)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythicalLeatherGloves] = [] {
		ItemData itd;

		itd.Name = "Mythical Leather Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythicalLeatherGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 16),
			StatMod(StatModType::MagicArmor, 16),
			StatMod(StatModType::Evasion, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::ZodiacGloves] = [] {
		ItemData itd;

		itd.Name = "Zodiac Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ZodiacGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 19),
			StatMod(StatModType::MagicArmor, 19),
			StatMod(StatModType::Evasion, 7)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragonscaleGloves] = [] {
		ItemData itd;

		itd.Name = "Dragonscale Gloves";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragonscaleGloves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 23),
			StatMod(StatModType::MagicArmor, 23),
			StatMod(StatModType::Evasion, 8)
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
			StatMod(StatModType::Resistance, 250, Element::Fire),
			StatMod(StatModType::Resistance, 250, Element::Ice)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::GlovesOfAcceleration] = [] {
		ItemData itd;

		itd.Name = "Gloves of Acceleration";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::GlovesOfAcceleration;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 3),
			StatMod(StatModType::MagicArmor, 5),
			StatMod(StatModType::Evasion, 2)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::DEX, 3),
			StatMod(StatModType::MAG, 2),
			StatMod(StatModType::Accuracy, 5),
			StatMod(StatModType::CritChance, 50)
		};

		itd.BonusModStrings = {
			"On Direct Crit: Increase haste by 2% for 10s. Stacks up to 3 times."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (eventResult.DidCrit) {
						Combat::AddAuraStack(user, user, eventOptions, AuraID::GlovesOfAcceleration, 0);
					}
				}
			}
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
	list[ItemID::HunterBoots] = [] {
		ItemData itd;

		itd.Name = "Hunter Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::HunterBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 5),
			StatMod(StatModType::MagicArmor, 4),
			StatMod(StatModType::Evasion, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::WildBoots] = [] {
		ItemData itd;

		itd.Name = "Wild Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::WildBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 6),
			StatMod(StatModType::Evasion, 14)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DrakescaleBoots] = [] {
		ItemData itd;

		itd.Name = "Drakescale Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DrakescaleBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 13),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::Evasion, 18)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MoonLeatherBoots] = [] {
		ItemData itd;

		itd.Name = "Moon Leather Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MoonLeatherBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 18),
			StatMod(StatModType::MagicArmor, 12),
			StatMod(StatModType::Evasion, 22)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythicalLeatherBoots] = [] {
		ItemData itd;

		itd.Name = "Mythical Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythicalLeatherBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 24),
			StatMod(StatModType::MagicArmor, 16),
			StatMod(StatModType::Evasion, 26)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::ZodiacBoots] = [] {
		ItemData itd;

		itd.Name = "Zodiac Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::ZodiacBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 28),
			StatMod(StatModType::MagicArmor, 19),
			StatMod(StatModType::Evasion, 30)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragonscaleBoots] = [] {
		ItemData itd;

		itd.Name = "Dragonscale Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragonscaleBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 33),
			StatMod(StatModType::MagicArmor, 23),
			StatMod(StatModType::Evasion, 34)
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
	list[ItemID::TrekkingBoots] = [] {
		ItemData itd;

		itd.Name = "Trekking Boots";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TrekkingBoots;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::MediumFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 7),
			StatMod(StatModType::MagicArmor, 4),
			StatMod(StatModType::Evasion, 8)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 12),
			StatMod(StatModType::SP, 20),
			StatMod(StatModType::DEX, 3),
			StatMod(StatModType::CooldownReduction, 100),
			StatMod(StatModType::MovementSpeed, 150)
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
	list[ItemID::SteelHelm] = [] {
		ItemData itd;

		itd.Name = "Steel Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::SteelHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 11),
			StatMod(StatModType::MagicArmor, 2)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumHelm] = [] {
		ItemData itd;

		itd.Name = "Platinum Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::PlatinumHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 17),
			StatMod(StatModType::MagicArmor, 3)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumHelm] = [] {
		ItemData itd;

		itd.Name = "Titanium Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::TitaniumHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 25),
			StatMod(StatModType::MagicArmor, 4)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilHelm] = [] {
		ItemData itd;

		itd.Name = "Mythril Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::TitaniumHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 35),
			StatMod(StatModType::MagicArmor, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalHelm] = [] {
		ItemData itd;

		itd.Name = "Crystal Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::CrystalHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 46),
			StatMod(StatModType::MagicArmor, 8)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteHelm] = [] {
		ItemData itd;

		itd.Name = "Adamantite Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::AdamantiteHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 57),
			StatMod(StatModType::MagicArmor, 9)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteHelm] = [] {
		ItemData itd;

		itd.Name = "Dragonite Helm";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::DragoniteHelm;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 65),
			StatMod(StatModType::MagicArmor, 11)
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
			StatMod(StatModType::Resistance, 250, Element::Dark)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::HelmOfDevestation] = [] {
		ItemData itd;

		itd.Name = "Helm of Devestation";
		itd.IconFilePath = "head.png";
		itd.EquipFilePath = "silk_hat.png";

		itd.HideHair = true;

		itd.ItemID = ItemID::HelmOfDevestation;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHead;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 11),
			StatMod(StatModType::MagicArmor, 2)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 3),
			StatMod(StatModType::VIT, 2),
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::CritChance, 60),
			StatMod(StatModType::CritPower, 200)
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
	list[ItemID::SteelArmor] = [] {
		ItemData itd;

		itd.Name = "Steel Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 60;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 30),
			StatMod(StatModType::MagicArmor, 4)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumArmor] = [] {
		ItemData itd;

		itd.Name = "Platinum Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 48),
			StatMod(StatModType::MagicArmor, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumArmor] = [] {
		ItemData itd;

		itd.Name = "Titanium Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 150;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 71),
			StatMod(StatModType::MagicArmor, 8)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilArmor] = [] {
		ItemData itd;

		itd.Name = "Mythril Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 200;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 98),
			StatMod(StatModType::MagicArmor, 12)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalArmor] = [] {
		ItemData itd;

		itd.Name = "Crystal Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 275;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 130),
			StatMod(StatModType::MagicArmor, 15)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteArmor] = [] {
		ItemData itd;

		itd.Name = "Adamantite Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 350;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 161),
			StatMod(StatModType::MagicArmor, 19)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteArmor] = [] {
		ItemData itd;

		itd.Name = "Dragonite Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragoniteArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 450;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 185),
			StatMod(StatModType::MagicArmor, 22)
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
			StatMod(StatModType::Resistance, 250, Element::Light)
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CarbonSpikeArmor] = [] {
		ItemData itd;

		itd.Name = "Carbon Spike Armor";
		itd.IconFilePath = "body.png";
		itd.EquipFilePath = "silk_robes.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CarbonSpikeArmor;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 60;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyBody;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 30),
			StatMod(StatModType::MagicArmor, 4)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::HP, 18),
			StatMod(StatModType::STR, 2),
			StatMod(StatModType::Armor, 15)
		};
		itd.BonusModStrings = {
			"When Hit in Melee: Deal 12 physical damage to the attacker."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damaged) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					sf::Vector2i userPos = user->GetLocation();
					sf::Vector2i targetPos = target->GetLocation();
					if (TileMath::Distance(userPos, targetPos) <= 1.41) {
						EventOptions eo;
						eo.EventName = "Carbon Spike Armor";
						eo.Categories = { Category::Damaging, Category::SingleTarget };
						eo.Elements = { Element::Physical };
						eo.CanCrit = true;
						eo.CanBlock = true;

						Combat::FixedDamage(user, target, eo, 12);
					}
				}
			}
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
	list[ItemID::SteelGauntlets] = [] {
		ItemData itd;

		itd.Name = "Steel Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 2)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumGauntlets] = [] {
		ItemData itd;

		itd.Name = "Platinum Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 14),
			StatMod(StatModType::MagicArmor, 3)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumGauntlets] = [] {
		ItemData itd;

		itd.Name = "Titanium Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 21),
			StatMod(StatModType::MagicArmor, 4)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilGauntlets] = [] {
		ItemData itd;

		itd.Name = "Mythril Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 29),
			StatMod(StatModType::MagicArmor, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalGauntlets] = [] {
		ItemData itd;

		itd.Name = "Crystal Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 38),
			StatMod(StatModType::MagicArmor, 8)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteGauntlets] = [] {
		ItemData itd;

		itd.Name = "Adamantite Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 47),
			StatMod(StatModType::MagicArmor, 9)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteGauntlets] = [] {
		ItemData itd;

		itd.Name = "Dragonite Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragoniteGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 54),
			StatMod(StatModType::MagicArmor, 11)
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
	list[ItemID::SwiftGauntlets] = [] {
		ItemData itd;

		itd.Name = "Swift Gauntlets";
		itd.IconFilePath = "hands.png";
		itd.EquipFilePath = "silk_gloves.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SwiftGauntlets;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.Artifact = true;
		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyHands;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 9),
			StatMod(StatModType::MagicArmor, 2)
		};
		itd.ExplicitStatMods = {
			StatMod(StatModType::STR, 3),
			StatMod(StatModType::DEX, 3),
			StatMod(StatModType::Accuracy, 5),
			StatMod(StatModType::Haste, 40)
		};
		itd.BonusModStrings = {
			"5% on Direct Attack Hit: Increase double strike chance by 12% for 10s."
		};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {
			if (eventType == EventType::Damage) {
				if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Direct) != eventOptions.Categories.end()) {
					if (std::find(eventOptions.Categories.begin(), eventOptions.Categories.end(), Category::Attack) != eventOptions.Categories.end()) {
						if (Random::RandomInt(1, 100) <= 5) {
							Combat::AddAuraStack(user, user, eventOptions, AuraID::SwiftGauntlets, 0);
						}
					}
				}
			}
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
	list[ItemID::SteelGreaves] = [] {
		ItemData itd;

		itd.Name = "Steel Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::SteelGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 40;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 11),
			StatMod(StatModType::MagicArmor, 2),
			StatMod(StatModType::Evasion, 4)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::PlatinumGreaves] = [] {
		ItemData itd;

		itd.Name = "Platinum Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::PlatinumGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 65;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 17),
			StatMod(StatModType::MagicArmor, 3),
			StatMod(StatModType::Evasion, 6)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::TitaniumGreaves] = [] {
		ItemData itd;

		itd.Name = "Titanium Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::TitaniumGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 100;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 25),
			StatMod(StatModType::MagicArmor, 4),
			StatMod(StatModType::Evasion, 8)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::MythrilGreaves] = [] {
		ItemData itd;

		itd.Name = "Mythril Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::MythrilGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 130;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 35),
			StatMod(StatModType::MagicArmor, 6),
			StatMod(StatModType::Evasion, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::CrystalGreaves] = [] {
		ItemData itd;

		itd.Name = "Crystal Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::CrystalGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 180;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 46),
			StatMod(StatModType::MagicArmor, 8),
			StatMod(StatModType::Evasion, 10)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::AdamantiteGreaves] = [] {
		ItemData itd;

		itd.Name = "Adamantite Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::AdamantiteGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 230;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 57),
			StatMod(StatModType::MagicArmor, 9),
			StatMod(StatModType::Evasion, 11)
		};
		itd.ExplicitStatMods = {};

		itd.OnEvent = [](EventType eventType, Actor* user, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount) {

		};

		return itd;
	}();
	list[ItemID::DragoniteGreaves] = [] {
		ItemData itd;

		itd.Name = "Dragonite Greaves";
		itd.IconFilePath = "feet.png";
		itd.EquipFilePath = "silk_boots.png";

		itd.HideHair = false;

		itd.ItemID = ItemID::DragoniteGreaves;
		itd.ItemType = ItemType::Equipment;

		itd.InvokeAbility = AbilityID::Undefined;

		itd.MaxStacks = 1;

		itd.BaseValue = 300;

		itd.TwoHanded = false;
		itd.EquipType = EquipType::HeavyFeet;

		itd.ImplicitStatMods = {
			StatMod(StatModType::Armor, 65),
			StatMod(StatModType::MagicArmor, 11),
			StatMod(StatModType::Evasion, 12)
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
			StatMod(StatModType::Resistance, 250, Element::Ice)
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

	// Artifact Neck
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
			StatMod(StatModType::Resistance, 250, Element::Fire)
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
		itd.IconFilePath = "light_source.png";
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
		itd.IconFilePath = "light_source.png";
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
			StatMod(StatModType::Resistance, 250, Element::Light)
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