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
	Boulder,
	Chopper,
	Cleave,
	CobraBite,
	CriticalShot,
	CrushArmor,
	CrushingBlow,
	Disarm,
	DragonBreath,
	DragonfireBolt,
	ElementalEnergy,
	FearfulGaze,
	FieryTouch,
	FlameBolt,
	FlameStrike,
	Heal,
	Icicle,
	Ignite,
	ImpactWave,
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
	Shock,
	SlimeSplash,
	Splash,
	Stalagmite,
	Teleport,
	ThunderStrike,
	TornadoStrike,
	Venom,
	WaterBolt,

	// Potions
	PotionFruitJuice,
	PotionMinorHealing,
	PotionMinorMana,
	PotionSpeed,
	PotionStamina,

	// Scrolls
	ScrollPhaseDoor,
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
};
