// ================================================================
//
// itemWeights.hpp
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
		{ItemType::Equipment, 550},
		{ItemType::Potion, 150},
		{ItemType::Scroll, 150},
		{ItemType::Consumable, 100},
		{ItemType::Tome, 50}
	};

	return list;
}

static std::vector<std::pair<EquipType, int>> initEquipTypeWeights() {
	std::vector<std::pair<EquipType, int>> list;

	list = {
		{EquipType::Sword, 250},
		{EquipType::Axe, 250},
		{EquipType::Mace, 250},
		{EquipType::Dagger, 250},
		{EquipType::Spear, 250},
		{EquipType::Bow, 250},
		{EquipType::Wand, 250},
		{EquipType::Staff, 250},
		{EquipType::Shield, 500},
		{EquipType::LightHead, 333},
		{EquipType::LightBody, 333},
		{EquipType::LightHands, 333},
		{EquipType::LightFeet, 333},
		{EquipType::MediumHead, 334},
		{EquipType::MediumBody, 334},
		{EquipType::MediumHands, 334},
		{EquipType::MediumFeet, 334},
		{EquipType::HeavyHead, 333},
		{EquipType::HeavyBody, 333},
		{EquipType::HeavyHands, 333},
		{EquipType::HeavyFeet, 333},
		{EquipType::Neck, 500},
		{EquipType::Ring, 1000},
		{EquipType::LightSource, 300}
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
		{ 1,  10, 1000, ItemID::IronSword},
		{ 4,  15,  500, ItemID::RunedSword},
		{ 8,  20, 1000, ItemID::SteelSword},
		{16,  30, 1000, ItemID::PlatinumSword},
		{24,  40, 1000, ItemID::TitaniumSword},
		{32,  50, 1000, ItemID::MythrilSword},
		{40,  60, 1000, ItemID::CrystalSword},
		{48,  70, 1000, ItemID::AdamantiteSword},
		{56, 100, 1000, ItemID::DragoniteSword}
	};

	list[EquipType::Axe] = {
		{ 1,  10, 1000, ItemID::IronAxe},
		{ 4,  15,  500, ItemID::JaggedAxe},
		{ 8,  20, 1000, ItemID::SteelAxe},
		{16,  30, 1000, ItemID::PlatinumAxe},
		{24,  40, 1000, ItemID::TitaniumAxe},
		{32,  50, 1000, ItemID::MythrilAxe},
		{40,  60, 1000, ItemID::CrystalAxe},
		{48,  70, 1000, ItemID::AdamantiteAxe},
		{56, 100, 1000, ItemID::DragoniteAxe}
	};

	list[EquipType::Mace] = {
		{ 1,  10, 1000, ItemID::IronMace},
		{ 8,  20, 1000, ItemID::SteelMace},
		{16,  30, 1000, ItemID::PlatinumMace},
		{24,  40, 1000, ItemID::TitaniumMace},
		{32,  50, 1000, ItemID::MythrilMace},
		{40,  60, 1000, ItemID::CrystalMace},
		{48,  70, 1000, ItemID::AdamantiteMace},
		{56, 100, 1000, ItemID::DragoniteMace}
	};

	list[EquipType::Dagger] = {
		{ 1,  10, 1000, ItemID::IronDagger},
		{ 8,  20, 1000, ItemID::SteelDagger},
		{16,  30, 1000, ItemID::PlatinumDagger},
		{24,  40, 1000, ItemID::TitaniumDagger},
		{32,  50, 1000, ItemID::MythrilDagger},
		{40,  60, 1000, ItemID::CrystalDagger},
		{48,  70, 1000, ItemID::AdamantiteDagger},
		{56, 100, 1000, ItemID::DragoniteDagger}
	};

	list[EquipType::Spear] = {
		{ 1,  10, 1000, ItemID::IronSpear},
		{ 8,  20, 1000, ItemID::SteelSpear},
		{16,  30, 1000, ItemID::PlatinumSpear},
		{24,  40, 1000, ItemID::TitaniumSpear},
		{32,  50, 1000, ItemID::MythrilSpear},
		{40,  60, 1000, ItemID::CrystalSpear},
		{48,  70, 1000, ItemID::AdamantiteSpear},
		{56, 100, 1000, ItemID::DragoniteSpear}
	};

	list[EquipType::Bow] = {
		{ 1,  10, 1000, ItemID::Shortbow},
		{ 8,  20, 1000, ItemID::Longbow},
		{16,  30, 1000, ItemID::CompositeBow},
		{24,  40, 1000, ItemID::ElvenBow},
		{32,  50, 1000, ItemID::MoonBow},
		{40,  60, 1000, ItemID::MythicalBow},
		{48,  70, 1000, ItemID::ZodiacBow},
		{56, 100, 1000, ItemID::DragonBow}
	};

	list[EquipType::Wand] = {
		{ 1,  10, 1000, ItemID::WoodenWand},
		{ 8,  20, 1000, ItemID::ApprenticeWand},
		{16,  30, 1000, ItemID::RunedWand},
		{24,  40, 1000, ItemID::SpelloakWand},
		{32,  50, 1000, ItemID::SageWand},
		{40,  60, 1000, ItemID::MysticWand},
		{48,  70, 1000, ItemID::MasterWand},
		{56, 100, 1000, ItemID::DraconicWand}
	};

	list[EquipType::Staff] = {
		{ 1,   5,  150, ItemID::RunedStick},
		{ 1,  10, 1000, ItemID::WoodenStaff},
		{ 8,  20, 1000, ItemID::ApprenticeStaff},
		{16,  30, 1000, ItemID::RunedStaff},
		{24,  40, 1000, ItemID::SpelloakStaff},
		{32,  50, 1000, ItemID::SageStaff},
		{40,  60, 1000, ItemID::MysticStaff},
		{48,  70, 1000, ItemID::MasterStaff},
		{56, 100, 1000, ItemID::DraconicStaff}
	};

	list[EquipType::Shield] = {
		{ 1,  10, 1000, ItemID::IronShield},
		{ 8,  20, 1000, ItemID::SteelShield},
		{16,  30, 1000, ItemID::PlatinumShield},
		{24,  40, 1000, ItemID::TitaniumShield},
		{32,  50, 1000, ItemID::MythrilShield},
		{40,  60, 1000, ItemID::CrystalShield},
		{48,  70, 1000, ItemID::AdamantiteShield},
		{56, 100, 1000, ItemID::DragoniteShield}
	};

	list[EquipType::LightHead] = {
		{ 1,  10, 1000, ItemID::SilkHat},
		{ 8,  20, 1000, ItemID::ApprenticeHat},
		{16,  30, 1000, ItemID::RunedHat},
		{24,  40, 1000, ItemID::SpellthreadHat},
		{32,  50, 1000, ItemID::SageHat},
		{40,  60, 1000, ItemID::MysticHat},
		{48,  70, 1000, ItemID::MasterHat},
		{56, 100, 1000, ItemID::DraconicHat}
	};

	list[EquipType::LightBody] = {
		{ 1,  10, 1000, ItemID::SilkRobes},
		{ 8,  20, 1000, ItemID::ApprenticeRobes},
		{16,  30, 1000, ItemID::RunedRobes},
		{24,  40, 1000, ItemID::SpellthreadRobes},
		{32,  50, 1000, ItemID::SageRobes},
		{40,  60, 1000, ItemID::MysticRobes},
		{48,  70, 1000, ItemID::MasterRobes},
		{56, 100, 1000, ItemID::DraconicRobes}
	};

	list[EquipType::LightHands] = {
		{ 1,  10, 1000, ItemID::SilkGloves},
		{ 8,  20, 1000, ItemID::ApprenticeGloves}
	};

	list[EquipType::LightFeet] = {
		{ 1,  10, 1000, ItemID::SilkBoots},
		{ 8,  20, 1000, ItemID::ApprenticeBoots}
	};

	list[EquipType::MediumHead] = {
		{ 1,  10, 1000, ItemID::LeatherHelmet},
		{ 8,  20, 1000, ItemID::HunterHelmet}
	};

	list[EquipType::MediumBody] = {
		{ 1,  10, 1000, ItemID::LeatherArmor},
		{ 8,  20, 1000, ItemID::HunterArmor},
		{16,  30, 1000, ItemID::WildArmor},
		{24,  40, 1000, ItemID::DrakescaleArmor},
		{32,  50, 1000, ItemID::MoonLeatherArmor},
		{40,  60, 1000, ItemID::MythicalLeatherArmor},
		{48,  70, 1000, ItemID::ZodiacArmor},
		{56, 100, 1000, ItemID::DragonscaleArmor}
	};

	list[EquipType::MediumHands] = {
		{ 1,  10, 1000, ItemID::LeatherGloves},
		{ 8,  20, 1000, ItemID::HunterGloves}
	};

	list[EquipType::MediumFeet] = {
		{ 1,  10, 1000, ItemID::LeatherBoots},
		{ 8,  20, 1000, ItemID::HunterBoots}
	};

	list[EquipType::HeavyHead] = {
		{ 1,  10, 1000, ItemID::IronHelm},
		{ 8,  20, 1000, ItemID::SteelHelm}
	};

	list[EquipType::HeavyBody] = {
		{ 1,  10, 1000, ItemID::IronArmor},
		{ 8,  20, 1000, ItemID::SteelArmor},
		{16,  30, 1000, ItemID::PlatinumArmor},
		{24,  40, 1000, ItemID::TitaniumArmor},
		{32,  50, 1000, ItemID::MythrilArmor},
		{40,  60, 1000, ItemID::CrystalArmor},
		{48,  70, 1000, ItemID::AdamantiteArmor},
		{56, 100, 1000, ItemID::DragoniteArmor}
	};

	list[EquipType::HeavyHands] = {
		{ 1,  10, 1000, ItemID::IronGauntlets},
		{ 8,  20, 1000, ItemID::SteelGauntlets}
	};

	list[EquipType::HeavyFeet] = {
		{ 1,  10, 1000, ItemID::IronGreaves},
		{ 8,  20, 1000, ItemID::SteelGreaves}
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
		{1, 10, 1000, ItemID::Flametongue}
	};

	list[EquipType::Axe] = {
		{1, 10, 1000, ItemID::BloodDrinker}
	};

	list[EquipType::Mace] = {
		{1, 10, 1000, ItemID::Serenity}
	};

	list[EquipType::Dagger] = {
		{1, 10, 1000, ItemID::TaintedBlade}
	};

	list[EquipType::Spear] = {
		{1, 10, 1000, ItemID::WindScar}
	};

	list[EquipType::Bow] = {
		{1, 10, 1000, ItemID::LongShot}
	};

	list[EquipType::Wand] = {
		{1, 10, 1000, ItemID::SpiritfireTorch}
	};

	list[EquipType::Staff] = {
		{1, 10, 1000, ItemID::StaffOfTheNovice}
	};

	list[EquipType::Shield] = {
		{1, 10, 1000, ItemID::LastDefender}
	};

	list[EquipType::LightHead] = {
		{1, 10, 1000, ItemID::OraclesMonacle}
	};

	list[EquipType::LightBody] = {
		{1, 10, 1000, ItemID::BerserkerVest}
	};

	list[EquipType::LightHands] = {
		{1, 10, 1000, ItemID::ArcanistGloves}
	};

	list[EquipType::LightFeet] = {
		{1, 10, 1000, ItemID::Goldweave}
	};

	list[EquipType::MediumHead] = {
		{1, 10, 1000, ItemID::SniperHelmet}
	};

	list[EquipType::MediumBody] = {
		{1, 10, 1000, ItemID::SurvivalArmor}
	};

	list[EquipType::MediumHands] = {
		{1, 10, 1000, ItemID::FrostfireGloves}
	};

	list[EquipType::MediumFeet] = {
		{1, 10, 1000, ItemID::Windriders}
	};

	list[EquipType::HeavyHead] = {
		{1, 10, 1000, ItemID::HeraldOfVictory}
	};

	list[EquipType::HeavyBody] = {
		{1, 10, 1000, ItemID::GoldenArmor}
	};

	list[EquipType::HeavyHands] = {
		{1, 10, 1000, ItemID::ArenaGauntlets}
	};

	list[EquipType::HeavyFeet] = {
		{1, 10, 1000, ItemID::LostMountainGreaves}
	};

	list[EquipType::Neck] = {
		{1, 100, 1000, ItemID::RubyNecklace}
	};

	list[EquipType::Ring] = {
		{1, 100, 1000, ItemID::RingOfVitality}
	};

	list[EquipType::LightSource] = {
		{1, 100, 1000, ItemID::SpectralLantern}
	};

	return list;
}

static std::unordered_map<EquipType, std::vector<AffixWeight>> initAffixWeights() {
	std::unordered_map<EquipType, std::vector<AffixWeight>> list;

	// MinItemLevel, Weight, StatModType, MinValue, MaxValue
	list[EquipType::Sword] = {
		{1, 1000, StatModType::STR, 1, 20},
		{1, 500, StatModType::DEX, 1, 20},
		{1, 500, StatModType::MAG, 1, 15},
		{10, 600, StatModType::ArmorPen, 100, 400},
		{1, 1000, StatModType::Accuracy, 2, 25},
		{1, 750, StatModType::CritChance, 40, 120},
		{1, 750, StatModType::Haste, 30, 80},
		{1, 750, StatModType::DoubleStrikeChance, 50, 200},
		{1, 750, StatModType::OnHitDamage, 3, 50},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Axe] = {
		{1, 1000, StatModType::STR, 1, 20},
		{1, 500, StatModType::DEX, 1, 20},
		{10, 600, StatModType::ArmorPen, 100, 400},
		{1, 1000, StatModType::Accuracy, 2, 25},
		{1, 750, StatModType::CritChance, 40, 120},
		{1, 750, StatModType::Haste, 30, 80},
		{1, 750, StatModType::DoubleStrikeChance, 50, 300},
		{1, 1000, StatModType::OnHitDamage, 3, 30},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Mace] = {
		{1, 1000, StatModType::STR, 1, 20},
		{1, 500, StatModType::MAG, 1, 15},
		{10, 800, StatModType::ArmorPen, 100, 500},
		{1, 1000, StatModType::Accuracy, 2, 25},
		{1, 750, StatModType::CritChance, 40, 120},
		{1, 750, StatModType::Haste, 20, 50},
		{1, 500, StatModType::DoubleStrikeChance, 50, 100},
		{1, 750, StatModType::OnHitDamage, 3, 30},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Dagger] = {
		{1, 750, StatModType::STR, 1, 20},
		{1, 1000, StatModType::DEX, 1, 20},
		{1, 500, StatModType::MAG, 1, 15},
		{10, 1000, StatModType::ArmorPen, 100, 400},
		{1, 1000, StatModType::Accuracy, 2, 25},
		{1, 750, StatModType::CritChance, 40, 120},
		{1, 750, StatModType::Haste, 40, 100},
		{1, 750, StatModType::DoubleStrikeChance, 50, 200},
		{1, 1000, StatModType::OnHitDamage, 3, 30},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Spear] = {
		{1, 750, StatModType::STR, 1, 20},
		{1, 1000, StatModType::DEX, 1, 20},
		{1, 500, StatModType::MAG, 1, 15},
		{10, 600, StatModType::ArmorPen, 100, 400},
		{1, 1000, StatModType::Accuracy, 2, 25},
		{1, 750, StatModType::CritChance, 40, 120},
		{1, 750, StatModType::Haste, 30, 80},
		{1, 750, StatModType::DoubleStrikeChance, 50, 200},
		{1, 1000, StatModType::OnHitDamage, 4, 35},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Bow] = {
		{1, 1000, StatModType::STR, 1, 30},
		{1, 1000, StatModType::DEX, 1, 30},
		{10, 600, StatModType::ArmorPen, 100, 400},
		{1, 1000, StatModType::Accuracy, 3, 40},
		{1, 750, StatModType::CritChance, 40, 160},
		{1, 750, StatModType::Haste, 30, 80},
		{1, 1000, StatModType::OnHitDamage, 3, 30},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Wand] = {
		{1, 1000, StatModType::MPOnKill, 1, 20},
		{1, 500, StatModType::DEX, 1, 20},
		{1, 1000, StatModType::MAG, 1, 20},
		{1, 1000, StatModType::Accuracy, 2, 25},
		{1, 750, StatModType::CritChance, 40, 120},
		{1, 750, StatModType::Haste, 30, 80},
		{1, 500, StatModType::OnHitDamage, 3, 50},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Staff] = {
		{1, 1000, StatModType::MPOnKill, 1, 20},
		{1, 250, StatModType::STR, 1, 15},
		{1, 500, StatModType::DEX, 1, 20},
		{1, 1000, StatModType::MAG, 1, 20},
		{1, 1000, StatModType::Accuracy, 2, 25},
		{5, 750, StatModType::Healing, 10, 20},
		{1, 750, StatModType::CritChance, 40, 120},
		{1, 750, StatModType::Haste, 30, 80},
		{25, 50, StatModType::EXPBoost, 50, 100}
	};

	list[EquipType::Shield] = {
		{1, 1000, StatModType::HP, 6, 60},
		{1, 500, StatModType::MP, 2, 25},
		{1, 500, StatModType::SP, 1, 5},
		{1, 1000, StatModType::STR, 1, 10},
		{1, 1000, StatModType::MAG, 1, 10},
		{1, 750, StatModType::Accuracy, 2, 12},
		{1, 1000, StatModType::Armor, 8, 80},
		{1, 1000, StatModType::MagicArmor, 6, 60},
		{1, 1000, StatModType::Resistance, 300, 300},
		{1, 750, StatModType::BlockChance, 100, 400}
	};

	list[EquipType::LightHead] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 250, StatModType::STR, 1, 10},
		{1, 500, StatModType::DEX, 1, 10},
		{1, 1000, StatModType::MAG, 1, 10},
		{1, 250, StatModType::VIT, 1, 10},
		{1, 500, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 1000, StatModType::Accuracy, 2, 15},
		{20, 1000, StatModType::CritPower, 100, 250},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::LightBody] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 250, StatModType::STR, 1, 10},
		{1, 500, StatModType::DEX, 1, 10},
		{1, 1000, StatModType::MAG, 1, 10},
		{1, 250, StatModType::VIT, 1, 10},
		{1, 500, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		//{1, 500, StatModType::CooldownReduction, 50, 100},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::LightHands] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 250, StatModType::STR, 1, 10},
		{1, 500, StatModType::DEX, 1, 10},
		{1, 1000, StatModType::MAG, 1, 10},
		{1, 250, StatModType::VIT, 1, 10},
		{1, 500, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		//{15, 500, StatModType::ArmorPen, 50, 200},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 750, StatModType::Accuracy, 2, 15},
		{1, 750, StatModType::CritChance, 30, 100},
		{1, 750, StatModType::Haste, 25, 80},
		{1, 750, StatModType::DoubleStrikeChance, 50, 150},
		//{10, 750, StatModType::CooldownReduction, 50, 100},
		{1, 750, StatModType::OnHitDamage, 1, 25},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::LightFeet] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 250, StatModType::STR, 1, 10},
		{1, 500, StatModType::DEX, 1, 10},
		{1, 1000, StatModType::MAG, 1, 10},
		{1, 250, StatModType::VIT, 1, 10},
		{1, 500, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 1000, StatModType::Resistance, 300, 300},
		{1, 1000, StatModType::MovementSpeed, 100, 250},
	};

	list[EquipType::MediumHead] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 500, StatModType::STR, 1, 10},
		{1, 1000, StatModType::DEX, 1, 10},
		{1, 250, StatModType::MAG, 1, 10},
		{1, 375, StatModType::VIT, 1, 10},
		{1, 375, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 1000, StatModType::Accuracy, 2, 15},
		{20, 1000, StatModType::CritPower, 100, 250},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::MediumBody] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 500, StatModType::STR, 1, 10},
		{1, 1000, StatModType::DEX, 1, 10},
		{1, 250, StatModType::MAG, 1, 10},
		{1, 375, StatModType::VIT, 1, 10},
		{1, 375, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		//{1, 500, StatModType::CooldownReduction, 50, 100},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::MediumHands] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 500, StatModType::STR, 1, 10},
		{1, 1000, StatModType::DEX, 1, 10},
		{1, 250, StatModType::MAG, 1, 10},
		{1, 375, StatModType::VIT, 1, 10},
		{1, 375, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{15, 500, StatModType::ArmorPen, 50, 200},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 750, StatModType::Accuracy, 2, 15},
		{1, 750, StatModType::CritChance, 30, 100},
		{1, 750, StatModType::Haste, 25, 80},
		{1, 750, StatModType::DoubleStrikeChance, 50, 150},
		//{10, 750, StatModType::CooldownReduction, 50, 100},
		{1, 750, StatModType::OnHitDamage, 1, 25},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::MediumFeet] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 500, StatModType::STR, 1, 10},
		{1, 1000, StatModType::DEX, 1, 10},
		{1, 750, StatModType::MAG, 1, 10},
		{1, 375, StatModType::VIT, 1, 10},
		{1, 375, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 1000, StatModType::Resistance, 300, 300},
		{1, 1000, StatModType::MovementSpeed, 100, 250},
	};

	list[EquipType::HeavyHead] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 1000, StatModType::STR, 1, 10},
		{1, 250, StatModType::DEX, 1, 10},
		{1, 500, StatModType::MAG, 1, 10},
		{1, 500, StatModType::VIT, 1, 10},
		{1, 250, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 1000, StatModType::Accuracy, 2, 15},
		{20, 1000, StatModType::CritPower, 100, 250},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::HeavyBody] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 1000, StatModType::STR, 1, 10},
		{1, 250, StatModType::DEX, 1, 10},
		{1, 500, StatModType::MAG, 1, 10},
		{1, 500, StatModType::VIT, 1, 10},
		{1, 250, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		//{1, 500, StatModType::CooldownReduction, 50, 100},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::HeavyHands] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 1000, StatModType::STR, 1, 10},
		{1, 250, StatModType::DEX, 1, 10},
		{1, 500, StatModType::MAG, 1, 10},
		{1, 500, StatModType::VIT, 1, 10},
		{1, 250, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{15, 500, StatModType::ArmorPen, 50, 200},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 750, StatModType::Accuracy, 2, 15},
		{1, 750, StatModType::CritChance, 30, 100},
		{1, 750, StatModType::Haste, 25, 80},
		{1, 750, StatModType::DoubleStrikeChance, 50, 150},
		//{10, 750, StatModType::CooldownReduction, 50, 100},
		{1, 750, StatModType::OnHitDamage, 1, 25},
		{1, 1000, StatModType::Resistance, 300, 300}
	};

	list[EquipType::HeavyFeet] = {
		{1, 1000, StatModType::HP, 6, 75},
		{1, 500, StatModType::MP, 2, 30},
		{1, 500, StatModType::SP, 1, 5},
		{1, 1000, StatModType::STR, 1, 10},
		{1, 250, StatModType::DEX, 1, 10},
		{1, 500, StatModType::MAG, 1, 10},
		{1, 500, StatModType::VIT, 1, 10},
		{1, 250, StatModType::SPI, 1, 10},
		{1, 1000, StatModType::Armor, 2, 40},
		{1, 1000, StatModType::MagicArmor, 5, 50},
		{1, 500, StatModType::Evasion, 1, 10},
		{1, 1000, StatModType::Resistance, 300, 300},
		{1, 1000, StatModType::MovementSpeed, 100, 250},
	};

	list[EquipType::Neck] = {
		{1, 1000, StatModType::HP, 6, 40},
		{1, 500, StatModType::MP, 3, 16},
		{1, 500, StatModType::SP, 1, 6},
		{1, 500, StatModType::STR, 1, 7},
		{1, 500, StatModType::DEX, 1, 7},
		{1, 500, StatModType::MAG, 1, 7},
		{1, 250, StatModType::VIT, 1, 7},
		{1, 250, StatModType::SPI, 1, 7},
		{15, 1000, StatModType::ArmorPen, 50, 200},
		{1, 750, StatModType::MagicArmor, 3, 30},
		{1, 1000, StatModType::Resistance, 300, 300},
		{1, 1000, StatModType::Accuracy, 1, 12},
		{1, 1000, StatModType::CritChance, 40, 120},
		{5, 1000, StatModType::CritPower, 50, 150},
		{1, 1000, StatModType::Haste, 25, 100},
		{1, 1000, StatModType::DoubleStrikeChance, 50, 150}
		//{1, 1000, StatModType::CooldownRecution, 50, 100}
	};

	list[EquipType::Ring] = {
		{1, 1000, StatModType::HP, 6, 30},
		{1, 500, StatModType::MP, 3, 12},
		{1, 500, StatModType::SP, 1, 3},
		{1, 500, StatModType::STR, 1, 5},
		{1, 500, StatModType::DEX, 1, 5},
		{1, 500, StatModType::MAG, 1, 5},
		{1, 250, StatModType::VIT, 1, 5},
		{1, 250, StatModType::SPI, 1, 5},
		{1, 750, StatModType::Armor, 2, 15},
		{15, 750, StatModType::ArmorPen, 30, 100},
		{1, 1000, StatModType::Resistance, 300, 300},
		{1, 1000, StatModType::Accuracy, 1, 7},
		{1, 1000, StatModType::CritChance, 20, 80},
		{1, 1000, StatModType::Haste, 30, 80},
		{1, 1000, StatModType::DoubleStrikeChance, 30, 10},
		//{25, 1000, StatModType::CooldownReduction, 30, 50}
	};

	list[EquipType::LightSource] = {
		{1, 1000, StatModType::HP, 6, 30},
		{1, 500, StatModType::MP, 3, 12},
		{1, 500, StatModType::SP, 1, 3},
		{1, 750, StatModType::STR, 1, 7},
		{1, 750, StatModType::DEX, 1, 7},
		{1, 750, StatModType::MAG, 1, 7},
		{1, 375, StatModType::VIT, 1, 7},
		{1, 375, StatModType::SPI, 1, 7},
		{1, 1000, StatModType::Resistance, 300, 300},
		{1, 750, StatModType::Accuracy, 1, 7},
		{1, 500, StatModType::SightRadius, 100, 200},
		{1, 100, StatModType::GoldFind, 100, 250}
	};

	return list;
}

static std::vector<ItemWeight> initPotionWeights() {
	std::vector<ItemWeight> list;

	// MinItemLevel, MaxItemLevel, Weight, ItemID
	list = {
		{  1,  25, 1000, ItemID::PotionMinorHealing},
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
		{  5, 100,  500, ItemID::TomeBodyMindAndSoul}
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