// ================================================================
//
// itemID.hpp
// 
// List of all items.
//
// ================================================================

#pragma once

enum class ItemID {
	Undefined = 0,

	// Potions
	PotionFruitJuice,
	PotionMinorHealing,
	PotionMinorMana,
	PotionSpeed,
	PotionStamina,

	// Scrolls
	ScrollIdentify,
	ScrollLightningStorm,
	ScrollPhaseDoor,
	ScrollSpellProtection,
	ScrollTeleport,

	// Rods

	// Tomes
	TomeTesting,
	TomeCombatBasics,
	TomeOneManArmy,
	TomeAxeTechniques,
	TomeMaceTechniques,
	TomeAdvancedCombat,
	TomeLearningArchery,
	TomeMagicForBeginners,
	TomeArcaneEnergy,
	TomeIntermediateMagic,
	TomeIntroductionToSpirituality,
	TomeSpaceManipulation,
	TomeArtOfFlame,
	TomeBodyMindAndSoul,

	// Rations
	Rations,

	// Swords
	TravelerBlade,
	IronSword,
	RunedSword,
	SteelSword,
	PlatinumSword,
	TitaniumSword,
	MythrilSword,
	CrystalSword,
	AdamantiteSword,
	DragoniteSword,

	// Artifact Sword
	Flametongue,

	// Axe
	IronAxe,
	JaggedAxe,
	SteelAxe,
	PlatinumAxe,
	TitaniumAxe,
	MythrilAxe,
	CrystalAxe,
	AdamantiteAxe,
	DragoniteAxe,

	// Artifact Axe
	BloodDrinker,

	// Mace
	IronMace,
	SteelMace,
	PlatinumMace,
	TitaniumMace,
	MythrilMace,
	CrystalMace,
	AdamantiteMace,
	DragoniteMace,

	// Artifact Mace
	Serenity,

	// Dagger
	IronDagger,
	SteelDagger,
	PlatinumDagger,
	TitaniumDagger,
	MythrilDagger,
	CrystalDagger,
	AdamantiteDagger,
	DragoniteDagger,

	// Artifact Dagger
	TaintedBlade,

	// Spear
	IronSpear,
	SteelSpear,
	PlatinumSpear,
	TitaniumSpear,
	MythrilSpear,
	CrystalSpear,
	AdamantiteSpear,
	DragoniteSpear,

	// Artifact Spear
	WindScar,

	// Bow
	Shortbow,
	Longbow,

	// Artifact Bow
	LongShot,

	// Wand
	WoodenWand,
	ApprenticeWand,

	// Artifact Wand
	SpiritfireTorch,

	// Staff
	RunedStick,
	WoodenStaff,
	ApprenticeStaff,

	// Artifact Staff
	StaffOfTheNovice,

	// Shield
	IronShield,
	SteelShield,
	PlatinumShield,
	TitaniumShield,
	MythrilShield,
	CrystalShield,
	AdamantiteShield,
	DragoniteShield,

	// Artifact Shield
	LastDefender,

	// Light Head
	SilkHat,
	ApprenticeHat,

	// Artifact Light Head
	OraclesMonacle,

	// Light Body
	SilkRobes,
	ApprenticeRobes,
	RunedRobes,
	SpellthreadRobes,
	SageRobes,
	MysticRobes,
	MasterRobes,
	DraconicRobes,

	// Artifact Light Body
	BerserkerVest,

	// Light Hands
	SilkGloves,
	ApprenticeGloves,

	// Artifact Light Hands
	ArcanistGloves,

	// Light Feet
	SilkBoots,
	ApprenticeBoots,

	// Artifact Light Feet
	Goldweave,

	// Medium Head
	LeatherHelmet,
	HunterHelmet,

	// Artifact Medium Head
	SniperHelmet,

	// Medium Body
	LeatherArmor,
	HunterArmor,
	WildArmor,
	DrakescaleArmor,
	MoonLeatherArmor,
	MythicalLeatherArmor,
	ZodiacArmor,
	DragonscaleArmor,

	// Artifact Medium Body
	SurvivalArmor,
		
	// Medium Hands
	LeatherGloves,
	HunterGloves,

	// Artifact Medium Hands
	FrostfireGloves,
		
	// Medium Feet
	LeatherBoots,
	HunterBoots,

	// Artifact Medium Feet
	Windriders,

	// Heavy Head
	IronHelm,
	SteelHelm,

	// Artifact Heavy Head
	HeraldOfVictory,

	// Heavy Body
	IronArmor,
	SteelArmor,
	PlatinumArmor,
	TitaniumArmor,
	MythrilArmor,
	CrystalArmor,
	AdamantiteArmor,
	DragoniteArmor,

	// Artifact Heavy Body
	GoldenArmor,

	// Heavy Hands
	IronGauntlets,
	SteelGauntlets,

	// Artifact Heavy Hands
	ArenaGauntlets,
		
	// Heavy Feet
	IronGreaves,
	SteelGreaves,

	// Artifact Heavy Feet
	LostMountainGreaves,

	// Neck
	SilverNecklace,

	// Artifact Neck
	RubyNecklace,

	// Ring
	IronRing,

	// Artifact Ring
	RingOfVitality,

	// Light Source
	FloatingLantern,

	// Artifact Light Source
	SpectralLantern,

	// Misc
	DebugRing
};