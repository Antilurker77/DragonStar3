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
	CrushArmor,
	DragonBreath,
	DragonfireBolt,
	ElementalEnergy,
	FieryTouch,
	FlameBolt,
	FlameStrike,
	Heal,
	Icicle,
	ImpactWave,
	MagicMissile,
	PhoenixRaid,
	PowerStrike,
	RendingSlash,
	ShadowEnergy,
	Shock,
	Stalagmite,
	ThunderStrike,
	TornadoStrike,
	Venom,
	WaterBolt,

	// Potions
	PotionFruitJuice,
	PotionMinorHealing,
	PotionSpeed,

	// Scrolls

	// Misc
	Rest,

	// Passive
	Constitution,
	Focus,
	ImprovedDexterity,
	ImprovedMagic,
	ImprovedSpirit,
	ImprovedStrength,
	ImprovedVitality,
	ManaSpring,
};
