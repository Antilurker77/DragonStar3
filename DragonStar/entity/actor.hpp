// ================================================================
//
// actor.hpp
//
// Base class for the player and monster classes. Mostly handles
// stats and actions.
//
// ================================================================

#pragma once

enum class Element;
enum class EventType;
enum class StatModType;
class DungeonScene;

#include <array>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "../core/combat.hpp"
#include "../data/ability.hpp"
#include "../data/aura.hpp"
#include "../data/statMod.hpp"
#include "../ui/actorHUD.hpp"
#include "../ui/fctManager.hpp"

class Actor : public Entity {
public:
	// Sets the aura pointers.
	
	// Updates this actor's HUD element.
	void UpdateHUD(float secondsPerUpdate);

	// Draws this actor's HUD element.
	void DrawHUD(sf::RenderTarget& window, float timeRatio);
	
	// Updates this actor's FCT manager.
	void UpdateFCT(float secondsPerUpdate);

	// Draws this actor's FCTs.
	void DrawFCT(sf::RenderTarget& window, float timeRatio);

	// Clears all floating combat text from this actor.
	void ClearFCT();

	// Adds a miss unit to the FCT manager.
	void AddMissFCT();

	// Adds an aura unit to the FCT manager.
	void AddAuraFCT(std::string name, bool isBuff, bool isExpired);

	// Sets the DungeonScene reference.
	void SetDungeonScene(DungeonScene* ds);
	
	// Returns the DungeonScene reference. Kinda hacky.
	DungeonScene* GetDungeonScene();

	// Returns the index ID of this actor.
	size_t GetIndex();

	// Returns the actor's name.
	std::string GetName();

	// Sets the actor's name. Default is 'Unamed'.
	void SetName(std::string n);

	// Returns the actor's title.
	virtual std::string GetTitle();

	// Returns the actor's location.
	sf::Vector2i GetLocation();

	// Returns the actor's level.
	int GetLevel();

	// Returns the actor's current level of exhaustion.
	int GetExhaustion();

	// Reduces exhaustion by one. This will update auras, cooldowns ect.
	void DecrementExhaustion();

	// Returns true if the user has zero exhaustion and isn't stunned or resting.
	bool IsReadyToAct();

	// Moves the actor to the designated tile position. Should only be used to
	// move the actor to adjacent tiles. Adds exhaustion.
	void Walk(sf::Vector2i destination, int moveMod);

	// Moves the actor to the designated tile position. Travel is instant and does not cause exhaustion.
	void Warp(sf::Vector2i destination);

	// Makes the actor wait (pass their turn) for the specified amount of time.
	void Wait(int waitTime);

	// Makes the actor use the specified ability. Resource costs, exhaustion ect. are handled in Ability class.
	void UseAbility(DungeonScene* dungeonScene, AbilityID id, sf::Vector2i cursor);

	// Inflicts damage to the character, then returns the amount of damage dealt. Damage cannot exceed the character's current health.
	// Creates floating combat text from damage taken.
	int TakeDamage(int damage, bool isCrit, std::vector<Element>& elements);

	// Heals the characters selected attribute by the specified amount. Returns the amount healed, which cannot exceed the character's healt.
	int Heal(int amount, bool isCrit, AttributeType attribute);

	// Character spends the specified amount of resources.
	void SpendResource(int amount, EventOptions& eventOptions, AttributeType attribute);

	// Causes the actor to heal from their OnKill stats. This healing does not scale with any bonuses.
	void HealOnKill(EventOptions& eventOptions);

	// Returns auras the actor has.
	std::vector<Aura>& GetAuras();

	// Returns true if the actor has at least one stack or instance of the specified aura.
	bool HasAura(AuraID id);

	// Adds an aura to this actor. Will increase the stack of an existing aura if possible. Will add to duration if an aura already exists. 
	// Unique auras will be overwritten if the source is different.
	void AddAura(AuraID auraID, int rank, int ssDamage, int ssCritChance, int ssResPen, Actor* source);

	// Sets the pointer reference for the actor's auras.
	void SetAuraOwnerPointer();

	// Removes a stack of the specified aura, if possible.
	void RemoveAuraStack(AuraID auraID);

	// Removes auras that have expired from the actor.
	void RemoveExpiredAuras();

	// Removes all auras from the actor.
	void ClearAuras();

	// Fires of proc events. Note that amount will be bloated by 1000.
	virtual void OnEvent(EventType eventType, Actor* target, EventOptions& eventOptions, EventResult& eventResult, int64_t& amount);

	// Sets the flag to a specified value (0-15).
	void SetFlag(size_t index, int value);

	// Gets a flag value.
	int GetFlag(size_t index);

	// Sets the monster AI to alert.
	virtual void Alert();

	// === Character Stats ===
	
	// Returns true if the actor is alive.
	bool IsAlive();

	// Returns true if the actor is resting.
	bool IsResting();

	// Returns true if the actor is stunned.
	bool IsStunned();

	// Returns true if the actor is disarmed.
	bool IsDisarmed();

	// Returns the current HP of the actor.
	int GetCurrentHP();

	// Returns the current MP of the actor.
	int GetCurrentMP();

	// Returns the current SP of the actor.
	int GetCurrentSP();

	// Returns the max HP of the actor.
	int GetMaxHP();

	// Returns the HP regen of the actor. 1 HP Regen = 0.1 HP/Sec
	int GetHPRegen();

	// Returns the HP leech of the actor. 1 HP Leech = 0.1% HP Leech
	int GetHPLeech(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the HP restored on hit of the actor.
	int GetHPOnHit(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the HP restored on kill of the actor.
	int GetHPOnKill(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the max MP of the actor.
	int GetMaxMP();

	// Returns the MP regen of the actor. 1 MP Regen = 0.1 MP/Sec
	int GetMPRegen();

	// Returns the MP leech of the actor. 1 MP Leech = 0.1% MP Leech
	int GetMPLeech(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the MP restored on hit of the actor.
	int GetMPOnHit(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the HP restored on kill of the actor.
	int GetMPOnKill(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the max SP of the actor.
	int GetMaxSP();

	// Returns the SP regen of the actor. 1 SP Regen = 0.1 SP/Sec
	int GetSPRegen();

	// Returns the SP leech of the actor. 1 SP Leech = 0.1% SP Leech
	int GetSPLeech(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the SP restored on hit of the actor.
	int GetSPOnHit(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the HP restored on kill of the actor.
	int GetSPOnKill(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the strength of the actor.
	int GetSTR();

	// Returns the dexterity of the actor.
	int GetDEX();

	// Returns the magic of the actor.
	int GetMAG();

	// Returns the vitality of the actor.
	int GetVIT();

	// Returns the spirit of the actor.
	int GetSPI();

	// Returns the armor of the actor.
	int GetArmor(bool consumeBuffs);

	// Returns the armor penetration of the actor. 1 Armor Pen = 0.1% Armor Pen
	int GetArmorPen(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the magic armor of the actor.
	int GetMagicArmor(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the magic armor penetration of the actor. 1 Magic Pen = 0.1% Magic Pen
	int GetMagicArmorPen(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the evasion of the actor.
	int GetEvasion(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the resistance of the actor. 1 Resistance = 0.1% Resistance
	int GetResistance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the resistance penetration of the actor. 1 Resistance Pen = 0.1% Resistance Pen
	int GetResistancePen(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the attack power of the actor.
	int GetAttackPower(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the spell power of the actor.
	int GetSpellPower(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the accuracy of the actor.
	int GetAccuracy(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the block chance of the actor. 1 Block Chance = 0.1% Block Chance
	int GetBlockChance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the bonus range of the actor. 1 Bonus Range = 0.01 Bonus Range
	int GetRange(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the damage multiplier of the actor. 1 Damage = 0.1% Damage
	int GetDamage(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the damage taken multiplier of the actor. 1 Damage Taken = 0.1% Damage Taken
	int GetDamageTaken(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the healing multiplier of the actor. 1 Healing = 0.1% Healing
	int GetHealing(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the healing taken multiplier of the actor. 1 Healing Taken = 0.1% Healing Taken
	int GetHealingTaken(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the critical strike chance of the actor. 1 Crit Chance = 0.1% Crit Chance
	int GetCritChance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the critical strike power of the actor. 1 Crit Power = 0.1% Crit Power
	int GetCritPower(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the critical strike chance protection of the actor. 1 Crit Protection = 0.1% Crit Protection
	int GetCritProtection(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the critical strike power protection of the actor. 1 Crit Power Protection = 0.1% Crit Power Protection
	int GetCritPowerProtection(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the haste of the actor. 1 Haste = 0.1% Haste
	int GetHaste(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the double strike chance of the actor. 1 Double Strike Chance = 0.1% Double Strike Chance
	int GetDoubleStrikeChance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the double strike damage of the actor. 1 Double Strike Damage = 0.1% Double Strike Damage
	int GetDoubleStrikeDamage(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the counter chance of the actor. 1 Counter Chance = 0.1% Counter Chance
	int GetCounterChance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the on-hit damage of the actor.
	int GetOnHitDamage(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the cooldown reduction of the actor. 1 Cooldown Reduction = 0.1% Cooldown Reduction
	int GetCooldownReduction(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the HP cost reduction of the actor. 1 HP Cost Reduction = 0.1% HP Cost Reduction
	int GetHPCostReduction(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the MP cost reduction of the actor. 1 MP Cost Reduction = 0.1% MP Cost Reduction
	int GetMPCostReduction(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the SP cost reduction of the actor. 1 SP Cost Reduction = 0.1% SP Cost Reduction
	int GetSPCostReduction(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the death resistance of the actor. 1 Death Resistance = 0.1% Death Resistance
	int GetDeathResistance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the stun resistance of the actor. 1 Stun Resistance = 0.1% Stun Resistance
	int GetStunResistance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the snare resistance of the actor. 1 Snare Resistance = 0.1% Snare Resistance
	int GetSnareResistance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the disarm resistance of the actor. 1 Disarm Resistance = 0.1% Disarm Resistance
	int GetDisarmResistance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the silence resistance of the actor. 1 Silence Resistance = 0.1% Silence Resistance
	int GetSilenceResistance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the movement speed of the actor. 1 Movement Speed = 0.1% Movement Speed
	int GetMovementSpeed();

	// Returns the line of sight radius of the actor. 1 Sight Radius = 0.01 Sight Radius
	int GetSightRadius();

	// Returns the gold drop multiplier for the current actor. 1 Gold Find = 0.1% Bonus Gold Find
	int GetGoldFind();

	// Returns the EXP multiplier for the current actor. 1 EXP Boost = 0.1% EXP Boost
	int GetEXPBoost();

	// Returns the aura snapshot damage bonus. 1 Damage = 0.1% Damage
	int GetSnapshotDamage(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the aura snapshot critical strike chance bonus. 1 Crit Chance = 0.1% Crit Chance
	int GetSnapshotCritChance(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the aura snapshot resistance penetration bonus. 1 Resistance Pen = 0.1% Resistance Pen
	int GetSnapshotResistancePen(EventOptions& eventOptions, bool consumeBuffs);

	// Returns the base hit chance of the actor's weapon. Unarmed attacks have a hit chance of 500 (50%), monsters have their's set in their data.
	virtual int GetWeaponHitChance() = 0;

	// Returns the attack range of the actor's weapon. Unarmed attacks have a range of 100, monsters have their's set in their data.
	virtual int GetAttackRange() = 0;

	// Returns the attack speed of the actor's weapon. Unarmed attacks have a speed of 100, monsters have their's set in their data.
	virtual int GetAttackSpeed() = 0;

	// Returns the element of the actors weapon. Unarmed attacks are physical, monsters have their's set in their data.
	virtual Element GetAttackElement() = 0;

	// Returns the damage multiplier of the actor's weapon. Unarmed attacks are 1000, monsters have their's set in their data.
	virtual int GetWeaponDamageMultiplier() = 0;

	// Returns the amount of base EXP awarded. Players are worth 0 EXP.
	virtual int GetEXPReward() = 0;

	// Returns loot points. Loot points for players are 0.
	virtual int GetLootPoints() = 0;

	// Returns true if actor is the player.
	bool IsPlayer();

	// Returns the ability with the specified ID.
	Ability* GetAbility(AbilityID id);

	// Returns all of the actor's abilities.
	std::vector<Ability>* GetAbilities();

	// Returns true if the specified ability is usable.
	bool IsAbilityUsable(AbilityID id);

	// Returns true if the specified ability is a projectile.
	bool IsAbilityProjectile(AbilityID id);

	// Returns the range of a given ability.
	std::vector<sf::Vector2i> GetAbilityRange(AbilityID id);

	// Returns the target area of a given ability.
	std::vector<sf::Vector2i> GetTargetArea(AbilityID id, sf::Vector2i cursor);

	// ==== Saving ====

	// Returns the ability cooldowns.
	std::vector<int> GetAbilityCooldowns();

	// Returns the number of charges for each ability.
	std::vector<int> GetAbilityCharges();

	// Returns the IDs of the auras currently on the actor.
	std::vector<int> GetAuraIDs();

	// Returns the ranks of the auras currently on the actor.
	std::vector<int> GetAuraRanks();

	// Returns the aura durations.
	std::vector<int> GetAuraDurations();

	// Returns when the next tick of the auras will happen.
	std::vector<int> GetAuraNextTicks();

	// Returns the aura stacks.
	std::vector<int> GetAuraStacks();

	// Returns the aura snapshot damage values;
	std::vector<int> GetAuraSnapshotDamage();

	// Returns the aura snapshot crit chance values;
	std::vector<int> GetAuraSnapshotCritChance();

	// Returns the aura snapshot resistance penetration values;
	std::vector<int> GetAuraSnapshotResistancePen();

	// Returns the aura source indexes.
	std::vector<size_t> GetAuraSources();

	// Returns the flags.
	std::array<int, 16> GetFlags();

protected:
	// Returns the base stat of a designated StatModType. If no base exists, return 0.
	virtual int getBaseStat(StatModType statModType) = 0;

	// Returns the built in stat mods of the actor.
	virtual std::vector<StatMod>& getBaseStatMods() = 0;
	
	// Queries stat modifiers from gear. Only players have gear, monsters will just return the value.
	virtual int getStatFromEquipment(int base, StatModType statModType, EventOptions& eventOptions);

	// Queries stat modifiers for the stat.
	int getStat(int base, StatModType statModType, bool isMultiplicative, bool consumeBuffs);

	// Queries stat modifiers for the stat.
	int getStat(int base, StatModType statModType, EventOptions& eventOptions, bool isMultiplicative, bool consumeBuffs);

	// ================
	static DungeonScene* dungeonScene;
	size_t index = 0; // internal ID, when loading a game this value is used for auras to find their source actors, player's is always 0
	sf::Vector2i location = { 0, 0 };
	int exhaustion = 0;
	
	std::string name = "Unknown";
	bool isPlayer = false;

	int level = 0;

	int currentHP = 0;
	int currentMP = 0;
	int currentSP = 0;

	double hpRegenOverflow = 0.0;
	double mpRegenOverflow = 0.0;
	double spRegenOverflow = 0.0;

	std::vector<Ability> abilities;
	std::vector<Aura> auras;

	std::array<int, 16> flags{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	size_t encounterIndex = 0;

	// UI
	ActorHUD actorHUD;
	FCTManager fctManager;
};