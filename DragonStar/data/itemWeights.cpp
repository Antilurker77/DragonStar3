// ================================================================
//
// itemWeights.cpp
// 
// Contains weights for generating items.
//
// ================================================================

#include "item.hpp"

#include "id/equipType.hpp"
#include "id/itemID.hpp"
#include "id/rarity.hpp"

static std::vector<std::pair<ItemType, int>> initItemTypeWeights() {
	std::vector<std::pair<ItemType, int>> list;

	list = {
		{ItemType::Equipment,   550},
		{ItemType::Potion,      150},
		{ItemType::Scroll,      150},
		{ItemType::Consumable,  100},
		{ItemType::Tome,         50}
	};

	return list;
}

static std::vector<std::pair<EquipType, int>> initEquipTypeWeights() {
	std::vector<std::pair<EquipType, int>> list;

	list = {
		{EquipType::Sword,        250},
		{EquipType::Axe,          250},
		{EquipType::Mace,         250},
		{EquipType::Dagger,       250},
		{EquipType::Spear,        250},
		{EquipType::Bow,          250},
		{EquipType::Wand,         250},
		{EquipType::Staff,        250},
		{EquipType::Shield,       500},
		{EquipType::LightHead,    333},
		{EquipType::LightBody,    333},
		{EquipType::LightHands,   333},
		{EquipType::LightFeet,    333},
		{EquipType::MediumHead,   334},
		{EquipType::MediumBody,   334},
		{EquipType::MediumHands,  334},
		{EquipType::MediumFeet,   334},
		{EquipType::HeavyHead,    333},
		{EquipType::HeavyBody,    333},
		{EquipType::HeavyHands,   333},
		{EquipType::HeavyFeet,    333},
		{EquipType::Neck,         500},
		{EquipType::Ring,        1000},
		{EquipType::LightSource,  300}
	};

	return list;
}

static std::vector<std::pair<Rarity, int>> initRarityWeights() {
	std::vector<std::pair<Rarity, int>> list;

	list = {
		{Rarity::Common,         550},
		{Rarity::Magical,        300},
		{Rarity::Rare,           100},
		{Rarity::FixedArtifact,   25},
		{Rarity::RandomArtifact,  25}
	};

	return list;
}

static std::unordered_map<EquipType, std::vector<ItemWeight>> initBaseTypeWeights() {
	std::unordered_map<EquipType, std::vector<ItemWeight>> list;

	// MinItemLevel, MaxItemLevel, Weight, ItemID

	list[EquipType::Sword] = {
		{ 1,   5,  150, ItemID::TravelerBlade},
		{ 1,  15, 1000, ItemID::IronSword},
		{ 6,  21,  500, ItemID::RunedSword},
		{12,  28, 1000, ItemID::SteelSword},
		{25,  40, 1000, ItemID::PlatinumSword},
		{37,  53, 1000, ItemID::TitaniumSword},
		{50,  65, 1000, ItemID::MythrilSword},
		{62,  78, 1000, ItemID::CrystalSword},
		{75,  90, 1000, ItemID::AdamantiteSword},
		{87, 100, 1000, ItemID::DragoniteSword}
	};

	list[EquipType::Axe] = {
		{ 1,  15, 1000, ItemID::IronAxe},
		{ 6,  21,  500, ItemID::JaggedAxe},
		{12,  28, 1000, ItemID::SteelAxe},
		{25,  40, 1000, ItemID::PlatinumAxe},
		{37,  53, 1000, ItemID::TitaniumAxe},
		{50,  65, 1000, ItemID::MythrilAxe},
		{62,  78, 1000, ItemID::CrystalAxe},
		{75,  90, 1000, ItemID::AdamantiteAxe},
		{87, 100, 1000, ItemID::DragoniteAxe}
	};

	list[EquipType::Mace] = {
		{ 1,  15, 1000, ItemID::IronMace},
		{12,  28, 1000, ItemID::SteelMace},
		{25,  40, 1000, ItemID::PlatinumMace},
		{37,  53, 1000, ItemID::TitaniumMace},
		{50,  65, 1000, ItemID::MythrilMace},
		{62,  78, 1000, ItemID::CrystalMace},
		{75,  90, 1000, ItemID::AdamantiteMace},
		{87, 100, 1000, ItemID::DragoniteMace}
	};

	list[EquipType::Dagger] = {
		{ 1,  15, 1000, ItemID::IronDagger},
		{12,  28, 1000, ItemID::SteelDagger},
		{25,  40, 1000, ItemID::PlatinumDagger},
		{37,  53, 1000, ItemID::TitaniumDagger},
		{50,  65, 1000, ItemID::MythrilDagger},
		{62,  78, 1000, ItemID::CrystalDagger},
		{75,  90, 1000, ItemID::AdamantiteDagger},
		{87, 100, 1000, ItemID::DragoniteDagger}
	};

	list[EquipType::Spear] = {
		{ 1,  15, 1000, ItemID::IronSpear},
		{12,  28, 1000, ItemID::SteelSpear},
		{25,  40, 1000, ItemID::PlatinumSpear},
		{37,  53, 1000, ItemID::TitaniumSpear},
		{50,  65, 1000, ItemID::MythrilSpear},
		{62,  78, 1000, ItemID::CrystalSpear},
		{75,  90, 1000, ItemID::AdamantiteSpear},
		{87, 100, 1000, ItemID::DragoniteSpear}
	};

	list[EquipType::Bow] = {
		{ 1,   5,  150, ItemID::TrainingBow},
		{ 1,  15, 1000, ItemID::Shortbow},
		{12,  28, 1000, ItemID::Longbow},
		{25,  40, 1000, ItemID::CompositeBow},
		{37,  53, 1000, ItemID::ElvenBow},
		{50,  65, 1000, ItemID::MoonBow},
		{62,  78, 1000, ItemID::MythicalBow},
		{75,  90, 1000, ItemID::ZodiacBow},
		{87, 100, 1000, ItemID::DragonBow}
	};

	list[EquipType::Wand] = {
		{ 1,  15, 1000, ItemID::WoodenWand},
		{12,  28, 1000, ItemID::ApprenticeWand},
		{25,  40, 1000, ItemID::RunedWand},
		{37,  53, 1000, ItemID::SpelloakWand},
		{50,  65, 1000, ItemID::SageWand},
		{62,  78, 1000, ItemID::MysticWand},
		{75,  90, 1000, ItemID::MasterWand},
		{87, 100, 1000, ItemID::DraconicWand}
	};

	list[EquipType::Staff] = {
		{ 1,   5,  150, ItemID::RunedStick},
		{ 1,  15, 1000, ItemID::WoodenStaff},
		{12,  28, 1000, ItemID::ApprenticeStaff},
		{25,  40, 1000, ItemID::RunedStaff},
		{37,  53, 1000, ItemID::SpelloakStaff},
		{50,  65, 1000, ItemID::SageStaff},
		{62,  78, 1000, ItemID::MysticStaff},
		{75,  90, 1000, ItemID::MasterStaff},
		{87, 100, 1000, ItemID::DraconicStaff}
	};

	list[EquipType::Shield] = {
		{ 1,  15, 1000, ItemID::IronShield},
		{12,  28, 1000, ItemID::SteelShield},
		{25,  40, 1000, ItemID::PlatinumShield},
		{37,  53, 1000, ItemID::TitaniumShield},
		{50,  65, 1000, ItemID::MythrilShield},
		{62,  78, 1000, ItemID::CrystalShield},
		{75,  90, 1000, ItemID::AdamantiteShield},
		{87, 100, 1000, ItemID::DragoniteShield}
	};

	list[EquipType::LightHead] = {
		{ 1,  15, 1000, ItemID::SilkHat},
		{12,  28, 1000, ItemID::ApprenticeHat},
		{25,  40, 1000, ItemID::RunedHat},
		{37,  53, 1000, ItemID::SpellthreadHat},
		{50,  65, 1000, ItemID::SageHat},
		{62,  78, 1000, ItemID::MysticHat},
		{75,  90, 1000, ItemID::MasterHat},
		{87, 100, 1000, ItemID::DraconicHat}
	};

	list[EquipType::LightBody] = {
		{ 1,  15, 1000, ItemID::SilkRobes},
		{12,  28, 1000, ItemID::ApprenticeRobes},
		{25,  40, 1000, ItemID::RunedRobes},
		{37,  53, 1000, ItemID::SpellthreadRobes},
		{50,  65, 1000, ItemID::SageRobes},
		{62,  78, 1000, ItemID::MysticRobes},
		{75,  90, 1000, ItemID::MasterRobes},
		{87, 100, 1000, ItemID::DraconicRobes}
	};

	list[EquipType::LightHands] = {
		{ 1,  15, 1000, ItemID::SilkGloves},
		{12,  28, 1000, ItemID::ApprenticeGloves},
		{25,  40, 1000, ItemID::RunedGloves},
		{37,  53, 1000, ItemID::SpellthreadGloves},
		{50,  65, 1000, ItemID::SageGloves},
		{63,  78, 1000, ItemID::MysticGloves},
		{75,  90, 1000, ItemID::MasterGloves},
		{87, 100, 1000, ItemID::DraconicGloves}
	};

	list[EquipType::LightFeet] = {
		{ 1,  15, 1000, ItemID::SilkBoots},
		{12,  28, 1000, ItemID::ApprenticeBoots},
		{25,  40, 1000, ItemID::RunedBoots},
		{37,  53, 1000, ItemID::SpellthreadBoots},
		{50,  65, 1000, ItemID::SageBoots},
		{63,  78, 1000, ItemID::MysticBoots},
		{75,  90, 1000, ItemID::MasterBoots},
		{87, 100, 1000, ItemID::DraconicBoots}
	};

	list[EquipType::MediumHead] = {
		{ 1,  15, 1000, ItemID::LeatherHelmet},
		{12,  28, 1000, ItemID::HunterHelmet},
		{25,  40, 1000, ItemID::WildHelmet},
		{37,  53, 1000, ItemID::DrakescaleHelmet},
		{50,  65, 1000, ItemID::MoonLeatherHelmet},
		{62,  78, 1000, ItemID::MythicalLeatherHelmet},
		{75,  90, 1000, ItemID::ZodiacHelmet},
		{87, 100, 1000, ItemID::DragonscaleHelmet}
	};

	list[EquipType::MediumBody] = {
		{ 1,  15, 1000, ItemID::LeatherArmor},
		{12,  28, 1000, ItemID::HunterArmor},
		{25,  40, 1000, ItemID::WildArmor},
		{37,  53, 1000, ItemID::DrakescaleArmor},
		{50,  65, 1000, ItemID::MoonLeatherArmor},
		{62,  78, 1000, ItemID::MythicalLeatherArmor},
		{75,  90, 1000, ItemID::ZodiacArmor},
		{87, 100, 1000, ItemID::DragonscaleArmor}
	};

	list[EquipType::MediumHands] = {
		{ 1,  15, 1000, ItemID::LeatherGloves},
		{12,  28, 1000, ItemID::HunterGloves},
		{25,  40, 1000, ItemID::WildGloves},
		{37,  53, 1000, ItemID::DrakescaleGloves},
		{50,  65, 1000, ItemID::MoonLeatherGloves},
		{62,  78, 1000, ItemID::MythicalLeatherGloves},
		{75,  90, 1000, ItemID::ZodiacGloves},
		{87, 100, 1000, ItemID::DragonscaleGloves}
	};

	list[EquipType::MediumFeet] = {
		{ 1,  15, 1000, ItemID::LeatherBoots},
		{12,  28, 1000, ItemID::HunterBoots},
		{25,  40, 1000, ItemID::WildBoots},
		{37,  53, 1000, ItemID::DrakescaleBoots},
		{50,  65, 1000, ItemID::MoonLeatherBoots},
		{62,  78, 1000, ItemID::MythicalLeatherBoots},
		{75,  90, 1000, ItemID::ZodiacBoots},
		{87, 100, 1000, ItemID::DragonscaleBoots}
	};

	list[EquipType::HeavyHead] = {
		{ 1,  15, 1000, ItemID::IronHelm},
		{12,  28, 1000, ItemID::SteelHelm},
		{25,  40, 1000, ItemID::PlatinumHelm},
		{37,  53, 1000, ItemID::TitaniumHelm},
		{50,  65, 1000, ItemID::MythrilHelm},
		{62,  78, 1000, ItemID::CrystalHelm},
		{75,  90, 1000, ItemID::AdamantiteHelm},
		{87, 100, 1000, ItemID::DragoniteHelm}
	};

	list[EquipType::HeavyBody] = {
		{ 1,  15, 1000, ItemID::IronArmor},
		{12,  28, 1000, ItemID::SteelArmor},
		{25,  40, 1000, ItemID::PlatinumArmor},
		{37,  53, 1000, ItemID::TitaniumArmor},
		{50,  65, 1000, ItemID::MythrilArmor},
		{62,  78, 1000, ItemID::CrystalArmor},
		{75,  90, 1000, ItemID::AdamantiteArmor},
		{87, 100, 1000, ItemID::DragoniteArmor}
	};

	list[EquipType::HeavyHands] = {
		{ 1,  15, 1000, ItemID::IronGauntlets},
		{12,  28, 1000, ItemID::SteelGauntlets},
		{25,  40, 1000, ItemID::PlatinumGauntlets},
		{37,  53, 1000, ItemID::TitaniumGauntlets},
		{50,  65, 1000, ItemID::MythrilGauntlets},
		{62,  78, 1000, ItemID::CrystalGauntlets},
		{75,  90, 1000, ItemID::AdamantiteGauntlets},
		{87, 100, 1000, ItemID::DragoniteGauntlets}
	};

	list[EquipType::HeavyFeet] = {
		{ 1,  15, 1000, ItemID::IronGreaves},
		{12,  28, 1000, ItemID::SteelGreaves},
		{25,  40, 1000, ItemID::PlatinumGreaves},
		{37,  53, 1000, ItemID::TitaniumGreaves},
		{50,  65, 1000, ItemID::MythrilGreaves},
		{62,  78, 1000, ItemID::CrystalGreaves},
		{75,  90, 1000, ItemID::AdamantiteGreaves},
		{87, 100, 1000, ItemID::DragoniteGreaves}
	};

	list[EquipType::Neck] = {
		{ 1, 100, 1000, ItemID::SilverNecklace}
	};

	list[EquipType::Ring] = {
		{ 1, 100, 1000, ItemID::IronRing}
	};

	list[EquipType::LightSource] = {
		{ 1, 100, 1000, ItemID::FloatingLantern}
	};

	return list;
}

static std::unordered_map<EquipType, std::vector<ItemWeight>> initArtifactWeights() {
	std::unordered_map<EquipType, std::vector<ItemWeight>> list;

	// MinItemLevel, MaxItemLevel, Weight, ItemID

	list[EquipType::Sword] = {
		{  1,  15, 1000, ItemID::Flametongue},
		{ 12,  28, 1000, ItemID::DustDevil}
	};

	list[EquipType::Axe] = {
		{  1,  15, 1000, ItemID::BloodDrinker},
		{ 12,  28, 1000, ItemID::Chaotica}
	};

	list[EquipType::Mace] = {
		{  1,  15, 1000, ItemID::Serenity},
		{ 12,  28, 1000, ItemID::SiegeBreaker}
	};

	list[EquipType::Dagger] = {
		{  1,  15, 1000, ItemID::TaintedBlade},
		{ 12,  28, 1000, ItemID::CrimsonDagger}
	};

	list[EquipType::Spear] = {
		{  1,  15, 1000, ItemID::WindScar},
		{ 12,  28, 1000, ItemID::RagingRiver}
	};

	list[EquipType::Bow] = {
		{  1,  15, 1000, ItemID::LongShot},
		{ 12,  28, 1000, ItemID::HomingBow}
	};

	list[EquipType::Wand] = {
		{  1,  15, 1000, ItemID::SpiritfireTorch},
		{ 12,  28, 1000, ItemID::BatteryWand}
	};

	list[EquipType::Staff] = {
		{  1,  15, 1000, ItemID::StaffOfTheNovice},
		{ 12,  28, 1000, ItemID::CalcifiedSnake}
	};

	list[EquipType::Shield] = {
		{  1,  15, 1000, ItemID::LastDefender},
		{ 12,  28, 1000, ItemID::ArcanistBulwark}
	};

	list[EquipType::LightHead] = {
		{  1,  15, 1000, ItemID::OraclesMonacle},
		{ 12,  28, 1000, ItemID::DundreHat}
	};

	list[EquipType::LightBody] = {
		{  1,  15, 1000, ItemID::BerserkerVest},
		{ 12,  28, 1000, ItemID::SirenEmbrace}
	};

	list[EquipType::LightHands] = {
		{  1,  15, 1000, ItemID::ArcanistGloves},
		{ 12,  28, 1000, ItemID::TetraGloves}
	};

	list[EquipType::LightFeet] = {
		{  1,  15, 1000, ItemID::Goldweave}
	};

	list[EquipType::MediumHead] = {
		{  1,  15, 1000, ItemID::SniperHelmet}
	};

	list[EquipType::MediumBody] = {
		{  1,  15, 1000, ItemID::SurvivalArmor}
	};

	list[EquipType::MediumHands] = {
		{  1,  15, 1000, ItemID::FrostfireGloves}
	};

	list[EquipType::MediumFeet] = {
		{  1,  15, 1000, ItemID::Windriders}
	};

	list[EquipType::HeavyHead] = {
		{  1,  15, 1000, ItemID::HeraldOfVictory}
	};

	list[EquipType::HeavyBody] = {
		{  1,  15, 1000, ItemID::GoldenArmor}
	};

	list[EquipType::HeavyHands] = {
		{  1,  15, 1000, ItemID::ArenaGauntlets}
	};

	list[EquipType::HeavyFeet] = {
		{  1,  15, 1000, ItemID::LostMountainGreaves}
	};

	list[EquipType::Neck] = {
		{  1, 100, 1000, ItemID::RubyNecklace}
	};

	list[EquipType::Ring] = {
		{  1, 100, 1000, ItemID::RingOfVitality}
	};

	list[EquipType::LightSource] = {
		{  1, 100, 1000, ItemID::SpectralLantern}
	};

	return list;
}

static std::unordered_map<EquipType, std::vector<AffixWeight>> initAffixWeights() {
	std::unordered_map<EquipType, std::vector<AffixWeight>> list;

	// MinItemLevel, Weight, StatModType, MinValue, MaxValue
	list[EquipType::Sword] = {
		{  1, 1000, StatModType::STR, 1, 20},
		{  1,  500, StatModType::DEX, 1, 20},
		{  1,  500, StatModType::MAG, 1, 15},
		{ 10,  600, StatModType::ArmorPen, 100, 400},
		{  1, 1000, StatModType::Accuracy, 2, 25},
		{  1,  750, StatModType::CritChance, 40, 120},
		{  1,  750, StatModType::Haste, 30, 80},
		{  1,  750, StatModType::DoubleStrikeChance, 50, 200},
		{  1,  750, StatModType::OnHitDamage, 3, 50},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Axe] = {
		{  1, 1000, StatModType::STR, 1, 20},
		{  1,  500, StatModType::DEX, 1, 20},
		{ 10,  600, StatModType::ArmorPen, 100, 400},
		{  1, 1000, StatModType::Accuracy, 2, 25},
		{  1,  750, StatModType::CritChance, 40, 120},
		{  1,  750, StatModType::Haste, 30, 80},
		{  1,  750, StatModType::DoubleStrikeChance, 50, 300},
		{  1, 1000, StatModType::OnHitDamage, 3, 30},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Mace] = {
		{  1, 1000, StatModType::STR, 1, 20},
		{  1,  500, StatModType::MAG, 1, 15},
		{ 10,  800, StatModType::ArmorPen, 100, 500},
		{  1, 1000, StatModType::Accuracy, 2, 25},
		{  1,  750, StatModType::CritChance, 40, 120},
		{  1,  750, StatModType::Haste, 20, 50},
		{  1,  500, StatModType::DoubleStrikeChance, 50, 100},
		{  1,  750, StatModType::OnHitDamage, 3, 30},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Dagger] = {
		{  1,  750, StatModType::STR, 1, 20},
		{  1, 1000, StatModType::DEX, 1, 20},
		{  1,  500, StatModType::MAG, 1, 15},
		{ 10, 1000, StatModType::ArmorPen, 100, 400},
		{  1, 1000, StatModType::Accuracy, 2, 25},
		{  1,  750, StatModType::CritChance, 40, 120},
		{  1,  750, StatModType::Haste, 40, 100},
		{  1,  750, StatModType::DoubleStrikeChance, 50, 200},
		{  1, 1000, StatModType::OnHitDamage, 3, 30},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Spear] = {
		{  1,  750, StatModType::STR, 1, 20},
		{  1, 1000, StatModType::DEX, 1, 20},
		{  1,  500, StatModType::MAG, 1, 15},
		{ 10,  600, StatModType::ArmorPen, 100, 400},
		{  1, 1000, StatModType::Accuracy, 2, 25},
		{  1,  750, StatModType::CritChance, 40, 120},
		{  1,  750, StatModType::Haste, 30, 80},
		{  1,  750, StatModType::DoubleStrikeChance, 50, 200},
		{  1, 1000, StatModType::OnHitDamage, 4, 35},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Bow] = {
		{  1, 1000, StatModType::STR, 1, 30},
		{  1, 1000, StatModType::DEX, 1, 30},
		{ 10,  600, StatModType::ArmorPen, 100, 400},
		{  1, 1000, StatModType::Accuracy, 3, 40},
		{  1,  750, StatModType::CritChance, 40, 160},
		{  1,  750, StatModType::Haste, 30, 80},
		{  1, 1000, StatModType::OnHitDamage, 3, 30},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Wand] = {
		{  1, 1000, StatModType::MPOnKill, 1, 20},
		{  1,  500, StatModType::DEX, 1, 20},
		{  1, 1000, StatModType::MAG, 1, 20},
		{  1, 1000, StatModType::Accuracy, 2, 25},
		{  1,  750, StatModType::CritChance, 40, 120},
		{  1,  750, StatModType::Haste, 30, 80},
		{  1,  500, StatModType::OnHitDamage, 3, 50},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Staff] = {
		{  1, 1000, StatModType::MPOnKill, 1, 20},
		{  1,  250, StatModType::STR, 1, 15},
		{  1,  500, StatModType::DEX, 1, 20},
		{  1, 1000, StatModType::MAG, 1, 20},
		{  1, 1000, StatModType::Accuracy, 2, 25},
		{  5,  750, StatModType::Healing, 10, 20},
		{  1,  750, StatModType::CritChance, 40, 120},
		{  1,  750, StatModType::Haste, 30, 80},
		{ 25,   50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Shield] = {
		{  1, 1000, StatModType::HP, 6, 60},
		{  1,  500, StatModType::MP, 2, 25},
		{  1,  500, StatModType::SP, 1, 5},
		{  1, 1000, StatModType::STR, 1, 10},
		{  1, 1000, StatModType::MAG, 1, 10},
		{  1,  750, StatModType::Accuracy, 2, 12},
		{  1, 1000, StatModType::Armor, 8, 80},
		{  1, 1000, StatModType::MagicArmor, 6, 60},
		{  1, 1000, StatModType::Resistance, 250, 250},
		{  1,  750, StatModType::BlockChance, 100, 400}
	};

	list[EquipType::LightHead] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  250, StatModType::STR, 1, 10},
		{  1,  500, StatModType::DEX, 1, 10},
		{  1, 1000, StatModType::MAG, 1, 10},
		{  1,  250, StatModType::VIT, 1, 10},
		{  1,  500, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1, 1000, StatModType::Accuracy, 2, 15},
		{ 20, 1000, StatModType::CritPower, 100, 250},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::LightBody] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  250, StatModType::STR, 1, 10},
		{  1,  500, StatModType::DEX, 1, 10},
		{  1, 1000, StatModType::MAG, 1, 10},
		{  1,  250, StatModType::VIT, 1, 10},
		{  1,  500, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1,  500, StatModType::CooldownReduction, 50, 100},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::LightHands] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  250, StatModType::STR, 1, 10},
		{  1,  500, StatModType::DEX, 1, 10},
		{  1, 1000, StatModType::MAG, 1, 10},
		{  1,  250, StatModType::VIT, 1, 10},
		{  1,  500, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		//{ 15,  500, StatModType::ArmorPen, 50, 200},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1,  750, StatModType::Accuracy, 2, 15},
		{  1,  750, StatModType::CritChance, 30, 100},
		{  1,  750, StatModType::Haste, 25, 80},
		{  1,  750, StatModType::DoubleStrikeChance, 50, 150},
		{ 10,  750, StatModType::CooldownReduction, 50, 100},
		{  1,  750, StatModType::OnHitDamage, 1, 25},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::LightFeet] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  250, StatModType::STR, 1, 10},
		{  1,  500, StatModType::DEX, 1, 10},
		{  1, 1000, StatModType::MAG, 1, 10},
		{  1,  250, StatModType::VIT, 1, 10},
		{  1,  500, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1, 1000, StatModType::Resistance, 250, 250},
		{  1, 1000, StatModType::MovementSpeed, 100, 250},
	};

	list[EquipType::MediumHead] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  500, StatModType::STR, 1, 10},
		{  1, 1000, StatModType::DEX, 1, 10},
		{  1,  250, StatModType::MAG, 1, 10},
		{  1,  375, StatModType::VIT, 1, 10},
		{  1,  375, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1, 1000, StatModType::Accuracy, 2, 15},
		{ 20, 1000, StatModType::CritPower, 100, 250},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::MediumBody] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  500, StatModType::STR, 1, 10},
		{  1, 1000, StatModType::DEX, 1, 10},
		{  1,  250, StatModType::MAG, 1, 10},
		{  1,  375, StatModType::VIT, 1, 10},
		{  1,  375, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1,  500, StatModType::CooldownReduction, 50, 100},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::MediumHands] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  500, StatModType::STR, 1, 10},
		{  1, 1000, StatModType::DEX, 1, 10},
		{  1,  250, StatModType::MAG, 1, 10},
		{  1,  375, StatModType::VIT, 1, 10},
		{  1,  375, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{ 15,  500, StatModType::ArmorPen, 50, 200},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1,  750, StatModType::Accuracy, 2, 15},
		{  1,  750, StatModType::CritChance, 30, 100},
		{  1,  750, StatModType::Haste, 25, 80},
		{  1,  750, StatModType::DoubleStrikeChance, 50, 150},
		{ 10,  750, StatModType::CooldownReduction, 50, 100},
		{  1,  750, StatModType::OnHitDamage, 1, 25},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::MediumFeet] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1,  500, StatModType::STR, 1, 10},
		{  1, 1000, StatModType::DEX, 1, 10},
		{  1,  750, StatModType::MAG, 1, 10},
		{  1,  375, StatModType::VIT, 1, 10},
		{  1,  375, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1, 1000, StatModType::Resistance, 250, 250},
		{  1, 1000, StatModType::MovementSpeed, 100, 250},
	};

	list[EquipType::HeavyHead] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1, 1000, StatModType::STR, 1, 10},
		{  1,  250, StatModType::DEX, 1, 10},
		{  1,  500, StatModType::MAG, 1, 10},
		{  1,  500, StatModType::VIT, 1, 10},
		{  1,  250, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1, 1000, StatModType::Accuracy, 2, 15},
		{ 20, 1000, StatModType::CritPower, 100, 250},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::HeavyBody] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1, 1000, StatModType::STR, 1, 10},
		{  1,  250, StatModType::DEX, 1, 10},
		{  1,  500, StatModType::MAG, 1, 10},
		{  1,  500, StatModType::VIT, 1, 10},
		{  1,  250, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1,  500, StatModType::CooldownReduction, 50, 100},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::HeavyHands] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1, 1000, StatModType::STR, 1, 10},
		{  1,  250, StatModType::DEX, 1, 10},
		{  1,  500, StatModType::MAG, 1, 10},
		{  1,  500, StatModType::VIT, 1, 10},
		{  1,  250, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{ 15,  500, StatModType::ArmorPen, 50, 200},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1,  750, StatModType::Accuracy, 2, 15},
		{  1,  750, StatModType::CritChance, 30, 100},
		{  1,  750, StatModType::Haste, 25, 80},
		{  1,  750, StatModType::DoubleStrikeChance, 50, 150},
		{ 10,  750, StatModType::CooldownReduction, 50, 100},
		{  1,  750, StatModType::OnHitDamage, 1, 25},
		{  1, 1000, StatModType::Resistance, 250, 250}
	};

	list[EquipType::HeavyFeet] = {
		{  1, 1000, StatModType::HP, 6, 75},
		{  1,  500, StatModType::MP, 2, 30},
		{  1,  500, StatModType::SP, 1, 5},
		{  1, 1000, StatModType::STR, 1, 10},
		{  1,  250, StatModType::DEX, 1, 10},
		{  1,  500, StatModType::MAG, 1, 10},
		{  1,  500, StatModType::VIT, 1, 10},
		{  1,  250, StatModType::SPI, 1, 10},
		{  1, 1000, StatModType::Armor, 2, 40},
		{  1, 1000, StatModType::MagicArmor, 5, 50},
		{  1,  500, StatModType::Evasion, 1, 10},
		{  1, 1000, StatModType::Resistance, 250, 250},
		{  1, 1000, StatModType::MovementSpeed, 100, 250},
	};

	list[EquipType::Neck] = {
		{  1, 1000, StatModType::HP, 6, 40},
		{  1,  500, StatModType::MP, 3, 16},
		{  1,  500, StatModType::SP, 1, 6},
		{  1,  500, StatModType::STR, 1, 7},
		{  1,  500, StatModType::DEX, 1, 7},
		{  1,  500, StatModType::MAG, 1, 7},
		{  1,  250, StatModType::VIT, 1, 7},
		{  1,  250, StatModType::SPI, 1, 7},
		{ 15, 1000, StatModType::ArmorPen, 50, 200},
		{  1,  750, StatModType::MagicArmor, 3, 30},
		{  1, 1000, StatModType::Resistance, 250, 250},
		{  1, 1000, StatModType::Accuracy, 1, 12},
		{  1, 1000, StatModType::CritChance, 40, 120},
		{  5, 1000, StatModType::CritPower, 50, 150},
		{  1, 1000, StatModType::Haste, 25, 100},
		{  1, 1000, StatModType::DoubleStrikeChance, 50, 150},
		{  1, 1000, StatModType::CooldownReduction, 50, 100}
	};

	list[EquipType::Ring] = {
		{  1, 1000, StatModType::HP, 6, 30},
		{  1,  500, StatModType::MP, 3, 12},
		{  1,  500, StatModType::SP, 1, 3},
		{  1,  500, StatModType::STR, 1, 5},
		{  1,  500, StatModType::DEX, 1, 5},
		{  1,  500, StatModType::MAG, 1, 5},
		{  1,  250, StatModType::VIT, 1, 5},
		{  1,  250, StatModType::SPI, 1, 5},
		{  1,  750, StatModType::Armor, 2, 15},
		{ 15,  750, StatModType::ArmorPen, 30, 100},
		{  1, 1000, StatModType::Resistance, 250, 250},
		{  1, 1000, StatModType::Accuracy, 1, 7},
		{  1, 1000, StatModType::CritChance, 20, 80},
		{  1, 1000, StatModType::Haste, 30, 80},
		{  1, 1000, StatModType::DoubleStrikeChance, 30, 10},
		{ 25, 1000, StatModType::CooldownReduction, 30, 50}
	};

	list[EquipType::LightSource] = {
		{  1, 1000, StatModType::HP, 6, 30},
		{  1,  500, StatModType::MP, 3, 12},
		{  1,  500, StatModType::SP, 1, 3},
		{  1,  750, StatModType::STR, 1, 7},
		{  1,  750, StatModType::DEX, 1, 7},
		{  1,  750, StatModType::MAG, 1, 7},
		{  1,  375, StatModType::VIT, 1, 7},
		{  1,  375, StatModType::SPI, 1, 7},
		{  1, 1000, StatModType::Resistance, 250, 250},
		{  1,  750, StatModType::Accuracy, 1, 7},
		{  1,  500, StatModType::SightRadius, 100, 200},
		{  1,  100, StatModType::GoldFind, 100, 250}
	};

	return list;
}

static std::vector<ItemWeight> initPotionWeights() {
	std::vector<ItemWeight> list;

	// MinItemLevel, MaxItemLevel, Weight, ItemID
	list = {
		{  1,  25, 1000, ItemID::PotionMinorHealing},
		{ 10,  50, 1000, ItemID::PotionLesserHealing},
		{  1,  25,  250, ItemID::PotionMinorMana},
		{  5, 100,  100, ItemID::PotionStamina},
		{  1, 100,  100, ItemID::PotionFruitJuice},
		{  1, 100,   50, ItemID::PotionSpeed}
	};

	return list;
}

static std::vector<ItemWeight> initScrollWeights() {
	std::vector<ItemWeight> list;

	// MinItemLevel, MaxItemLevel, Weight, ItemID
	list = {
		{  1, 100, 1000, ItemID::ScrollIdentify},
		{  1, 100,  500, ItemID::ScrollLightningStorm},
		{  1, 100,  500, ItemID::ScrollMagicMapping},
		{  1, 100, 1000, ItemID::ScrollPhaseDoor},
		{  2, 100,  500, ItemID::ScrollSpellProtection},
		{  1, 100,  500, ItemID::ScrollTeleport}
	};

	return list;
}

static std::vector<ItemWeight> initTomeWeights() {
	std::vector<ItemWeight> list;

	// MinItemLevel, MaxItemLevel, Weight, ItemID
	list = {
		{  1, 100,  500, ItemID::TomeCombatBasics},
		{  2, 100, 1000, ItemID::TomeOneManArmy},
		{  1, 100,  750, ItemID::TomeAxeTechniques},
		{  1, 100,  750, ItemID::TomeMaceTechniques},
		{  6, 100, 1000, ItemID::TomeAdvancedCombat},
		{  1, 100,  500, ItemID::TomeLearningArchery},
		{  1, 100,  500, ItemID::TomeMagicForBeginners},
		{  1, 100, 1000, ItemID::TomeArcaneEnergy},
		{  3, 100, 1000, ItemID::TomeIntermediateMagic},
		{  1, 100, 1000, ItemID::TomeIntroductionToSpirituality},
		{  5, 100,  750, ItemID::TomeSpaceManipulation},
		{  1, 100,  750, ItemID::TomeArtOfFlame},
		{  1, 100,  750, ItemID::TomeBasicsOfHealing},
		{  5, 100,  500, ItemID::TomeBodyMindAndSoul}
	};

	return list;
}

static std::vector<std::string> initRandArtSyllables() {
	std::vector<std::string> list;

	list = {
		"aba",
		"ade",
		"adi",
		"aki",
		"aj",
		"al",
		"eth",
		"en",
		"ette"
		"eko",
		"eco",
		"eld",
		"elm",
		"em",
		"ith",
		"ion",
		"ik",
		"ig",
		"id",
		"oah",
		"ore",
		"ort",
		"orth",
		"occ",
		"ol",
		"on",
		"om",
		"ul",
		"uth",
		"uk",
		"un",
		"um",
		"tre",
		"tros",
		"trok",
		"trad",
		"pon",
		"pen",
		"piou",
		"ba",
		"be",
		"ben",
		"ceth",
		"dorn",
		"do",
		"di"
	};

	return list;
}

static std::vector<std::string> initRandArtTitles() {
	std::vector<std::string> list;

	list = {
		"the Lost",
		"the Forgotten",
		"the Legendary",
		"the Magnificent",
		"the Exceptional",
		"the Mythical",
		"the Well-crafted"
	};

	return list;
}

std::vector<std::pair<ItemType, int>> Item::itemTypeWeights = initItemTypeWeights();
std::vector<std::pair<EquipType, int>> Item::equipTypeWeights = initEquipTypeWeights();
std::vector<std::pair<Rarity, int>> Item::rarityWeights = initRarityWeights();
std::unordered_map<EquipType, std::vector<ItemWeight>> Item::baseTypeWeights = initBaseTypeWeights();
std::unordered_map<EquipType, std::vector<ItemWeight>> Item::artifactWeights = initArtifactWeights();
std::unordered_map<EquipType, std::vector<AffixWeight>> Item::affixWeights = initAffixWeights();

std::vector<ItemWeight> Item::potionWeights = initPotionWeights();
std::vector<ItemWeight> Item::scrollWeights = initScrollWeights();
std::vector<ItemWeight> Item::tomeWeights = initTomeWeights();

std::vector<std::string> Item::randArtSyllables = initRandArtSyllables();
std::vector<std::string> Item::randArtTitles = initRandArtTitles();