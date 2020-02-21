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
	ScrollPhaseDoor,
	ScrollTeleport,

	// Rods

	// Tomes
	TomeTesting,
	TomeCombatBasics,
	TomeOneManArmy,
	TomeLearningArchery,
	TomeMagicForBeginners,
	TomeIntroductionToSpirituality,
	TomeArtOfFlame,
	TomeBodyMindAndSoul,

	// Rations
	Rations,

	// Swords
	TravelerBlade,
	IronSword,

	// Artifact Sword
	Flametongue,

	// Axe
	IronAxe,

	// Artifact Axe
	BloodDrinker,

	// Mace
	IronMace,

	// Artifact Mace
	Serenity,

	// Dagger
	IronDagger,

	// Artifact Dagger
	TaintedBlade,

	// Spear
	IronSpear,

	// Artifact Spear
	WindScar,

	// Bow
	Shortbow,

	// Artifact Bow
	LongShot,

	// Wand
	WoodenWand,

	// Artifact Wand
	SpiritfireTorch,

	// Staff
	RunedStick,
	WoodenStaff,

	// Artifact Staff
	StaffOfTheNovice,

	// Shield
	IronShield,

	// Artifact Shield
	LastDefender,

	// Light Head
	SilkHat,

	// Artifact Light Head
	OraclesMonacle,

	// Light Body
	SilkRobes,

	// Artifact Light Body
	BerserkerVest,

	// Light Hands
	SilkGloves,

	// Artifact Light Hands
	ArcanistGloves,

	// Light Feet
	SilkBoots,

	// Artifact Light Feet
	Goldweave,

	// Medium Head
	LeatherHelmet,

	// Artifact Medium Head
	SniperHelmet,

	// Medium Body
	LeatherArmor,

	// Artifact Medium Body
	SurvivalArmor,
		
	// Medium Hands
	LeatherGloves,

	// Artifact Medium Hands
	FrostfireGloves,
		
	// Medium Feet
	LeatherBoots,

	// Artifact Medium Feet
	Windriders,

	// Heavy Head
	IronHelm,

	// Artifact Heavy Head
	HeraldOfVictory,

	// Heavy Body
	IronArmor,

	// Artifact Heavy Body
	GoldenArmor,

	// Heavy Hands
	IronGauntlets,

	// Artifact Heavy Hands
	ArenaGauntlets,
		
	// Heavy Feet
	IronGreaves,

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