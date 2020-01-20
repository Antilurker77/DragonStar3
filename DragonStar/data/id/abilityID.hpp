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
	DragonBreath,
	DragonfireBolt,
	ElementalEnergy,
	FlameBolt,
	Heal,
	Icicle,
	ImpactWave,
	MagicMissile,
	PhoenixRaid,
	PowerStrike,
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

	// Scrolls

	// Misc
	Rest,

	// Passive
	Constitution,
	Focus,
	ManaSpring,
};
