// ================================================================
//
// abilityID.hpp
// 
// List of all abilities.
//
// ================================================================

#pragma once

enum class AbilityID {
	Undefined = 0,
	Attack = 1,
	ArcaneSpear,
	Bite,
	Blaze,
	Bloodsuck,
	BoltOfDarkness,
	BoltOfLight,
	Bonechill,
	Boulder,
	CastingCircle,
	Chopper,
	Cleave,
	CobraBite,
	ConcentratedVenom,
	CriticalShot,
	CrushArmor,
	CrushingBlow,
	DemonBlade,
	Disarm,
	DivineStrike,
	DragonBreath,
	DragonfireBolt,
	ElectricSurge,
	ElementalEnergy,
	FearfulGaze,
	FieryTouch,
	FlameBolt,
	FlameStrike,
	FlashStrike,
	Freeze,
	FuriousStrike,
	GrandHeal,
	HasteAllies,
	Heal,
	HerosTriumph,
	Icicle,
	Ignite,
	ImpactWave,
	Infect,
	MagicMissile,
	Maul,
	Multithrust,
	MysticBlast,
	PhaseDoor,
	PhoenixRaid,
	PoisonArrow,
	PowerShot,
	PowerStrike,
	Regenerate,
	RendingSlash,
	ShadowEnergy,
	ShadowFlay,
	ShiningPrism,
	Shock,
	SlimeSplash,
	SpectralSlash,
	Splash,
	Sprint,
	Stalagmite,
	SwiftHeal,
	Teleport,
	ThunderStrike,
	TornadoStrike,
	Trample,
	Venom,
	WaterBolt,
	Waterfall,

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

	// Misc
	Rest,

	// Passive
	Constitution,
	DeadlyForce,
	Focus,
	HealingEfficiency,
	ImprovedDexterity,
	ImprovedMagic,
	ImprovedSpirit,
	ImprovedStrength,
	ImprovedVitality,
	MagicWeapon,
	ManaSpring,
	Quickness,
	VenomousWound,
	Vigor
};
