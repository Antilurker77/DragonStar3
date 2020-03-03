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
	Bite,
	BoltOfDarkness,
	BoltOfLight,
	Bonechill,
	Boulder,
	Chopper,
	Cleave,
	CobraBite,
	ConcentratedVenom,
	CriticalShot,
	CrushArmor,
	CrushingBlow,
	DemonBlade,
	Disarm,
	DragonBreath,
	DragonfireBolt,
	ElectricSurge,
	ElementalEnergy,
	FearfulGaze,
	FieryTouch,
	FlameBolt,
	FlameStrike,
	FlashStrike,
	FuriousStrike,
	HasteAllies,
	Heal,
	HerosTriumph,
	Icicle,
	Ignite,
	ImpactWave,
	Infect,
	MagicMissile,
	Maul,
	MysticBlast,
	PhaseDoor,
	PhoenixRaid,
	PoisonArrow,
	PowerShot,
	PowerStrike,
	RendingSlash,
	ShadowEnergy,
	ShadowFlay,
	ShiningPrism,
	Shock,
	SlimeSplash,
	Splash,
	Stalagmite,
	Teleport,
	ThunderStrike,
	TornadoStrike,
	Trample,
	Venom,
	WaterBolt,

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

	// Misc
	Rest,

	// Passive
	Constitution,
	DeadlyForce,
	Focus,
	ImprovedDexterity,
	ImprovedMagic,
	ImprovedSpirit,
	ImprovedStrength,
	ImprovedVitality,
	ManaSpring,
	VenomousWound,
	Vigor
};
