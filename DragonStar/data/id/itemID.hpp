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
	PotionLesserHealing,
	PotionMinorHealing,
	PotionMinorMana,
	PotionSpeed,
	PotionStamina,

	// Scrolls
	ScrollIdentify,
	ScrollLightningStorm,
	ScrollMagicMapping,
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
	TomeBasicsOfHealing,
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
	DustDevil,

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
	Chaotica,

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
	SiegeBreaker,

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
	TrainingBow,
	Shortbow,
	Longbow,
	CompositeBow,
	ElvenBow,
	MoonBow,
	MythicalBow,
	ZodiacBow,
	DragonBow,

	// Artifact Bow
	LongShot,

	// Wand
	WoodenWand,
	ApprenticeWand,
	RunedWand,
	SpelloakWand,
	SageWand,
	MysticWand,
	MasterWand,
	DraconicWand,

	// Artifact Wand
	SpiritfireTorch,

	// Staff
	RunedStick,
	WoodenStaff,
	ApprenticeStaff,
	RunedStaff,
	SpelloakStaff,
	SageStaff,
	MysticStaff,
	MasterStaff,
	DraconicStaff,

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
	RunedHat,
	SpellthreadHat,
	SageHat,
	MysticHat,
	MasterHat,
	DraconicHat,

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
	RunedGloves,
	SpellthreadGloves,
	SageGloves,
	MysticGloves,
	MasterGloves,
	DraconicGloves,

	// Artifact Light Hands
	ArcanistGloves,

	// Light Feet
	SilkBoots,
	ApprenticeBoots,
	RunedBoots,
	SpellthreadBoots,
	SageBoots,
	MysticBoots,
	MasterBoots,
	DraconicBoots,

	// Artifact Light Feet
	Goldweave,

	// Medium Head
	LeatherHelmet,
	HunterHelmet,
	WildHelmet,
	DrakescaleHelmet,
	MoonLeatherHelmet,
	MythicalLeatherHelmet,
	ZodiacHelmet,
	DragonscaleHelmet,

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
	WildGloves,
	DrakescaleGloves,
	MoonLeatherGloves,
	MythicalLeatherGloves,
	ZodiacGloves,
	DragonscaleGloves,

	// Artifact Medium Hands
	FrostfireGloves,
		
	// Medium Feet
	LeatherBoots,
	HunterBoots,
	WildBoots,
	DrakescaleBoots,
	MoonLeatherBoots,
	MythicalLeatherBoots,
	ZodiacBoots,
	DragonscaleBoots,

	// Artifact Medium Feet
	Windriders,

	// Heavy Head
	IronHelm,
	SteelHelm,
	PlatinumHelm,
	TitaniumHelm,
	MythrilHelm,
	CrystalHelm,
	AdamantiteHelm,
	DragoniteHelm,

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
	PlatinumGauntlets,
	TitaniumGauntlets,
	MythrilGauntlets,
	CrystalGauntlets,
	AdamantiteGauntlets,
	DragoniteGauntlets,

	// Artifact Heavy Hands
	ArenaGauntlets,
		
	// Heavy Feet
	IronGreaves,
	SteelGreaves,
	PlatinumGreaves,
	TitaniumGreaves,
	MythrilGreaves,
	CrystalGreaves,
	AdamantiteGreaves,
	DragoniteGreaves,

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