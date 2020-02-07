// ================================================================
//
// tooltip.cpp
//
// ================================================================

#include "tooltip.hpp"

#include "wordWrap.hpp"
#include "../core/assetManager.hpp"
#include "../core/records.hpp"
#include "../core/settings.hpp"
#include "../data/ability.hpp"
#include "../data/aura.hpp"
#include "../data/dataString.hpp"
#include "../data/item.hpp"
#include "../data/statMod.hpp"
#include "../data/id/equipType.hpp"
#include "../data/id/rarity.hpp"
#include "../entity/actor.hpp"

Tooltip::Tooltip() {
	background.setFillColor(sf::Color(0, 0, 0, 223));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 223));

	titleText.setFont(*assetManager.LoadFont(settings.Font));
	titleText.setCharacterSize(titleFontSize);
}

void Tooltip::Update(float secondsPerUpdate) {
	
}

void Tooltip::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);
	window.draw(titleText);
	for (auto& t : tooltipText) {
		window.draw(t);
	}
}

void Tooltip::SetPosition(float x, float y, bool worldTooltip) {
	SetPosition(sf::Vector2f(x, y));
}

void Tooltip::SetPosition(sf::Vector2f position, bool worldTooltip) {
	pos = position;
	float titleFontSizeF = static_cast<float>(titleFontSize);
	float textFontSizeF = static_cast<float>(textFontSize);

	// make sure tooltip doesn't get cut off screen
	if (!worldTooltip) {
		pos.x = std::min(pos.x, static_cast<float>(settings.ScreenWidth) - background.getSize().x - 1.f);
		pos.x = std::max(pos.x, 1.f);
		pos.y = std::min(pos.y, static_cast<float>(settings.ScreenHeight) - background.getSize().y - 1.f);
		pos.y = std::max(pos.y, 1.f);
	}

	background.setPosition(pos);
	titleText.setPosition(pos.x + 4.f, pos.y + 2.f);
	for (size_t i = 0; i < tooltipText.size(); i++) {
		tooltipText[i].setPosition(pos.x + 4.f, pos.y + (titleFontSizeF + 7.f) + static_cast<float>(i) * (textFontSizeF + 6.f));
	}
}

sf::Vector2f Tooltip::GetSize() {
	return background.getSize();
}

void Tooltip::SetTooltip(Actor& actor) {
	tooltipText.clear();

	// converts seconds into string
	auto convertToSec = [](int i) {
		std::string s;
		if (i > 999) {
			s = std::to_string(i / 100) + "s";
		}
		else {
			// make sure it always shows two decimals if use time is less than 10s
			std::string remainder = std::to_string(i % 100);
			if (remainder.length() == 1) {
				remainder = "0" + remainder;
			}

			s = std::to_string(i / 100) + "." + remainder + "s";
		}

		return s;
	};

	// name
	std::string name;
	if (actor.IsPlayer()) {
		name = "#player ";
	}
	else {
		name = "#monster ";
	}
	name += actor.GetName();
	titleText.setString(name);

	size_t longest = actor.GetName().size();
	auto auras = actor.GetAuras();
	for (auto& aura : auras) {
		std::string s = "  ";
		s += aura.GetName();
		int duration = aura.GetCurrentDuration();
		if (duration > 0) {
			s += " [" + convertToSec(duration) + "]";
		}
		if (s.size() > longest) {
			longest = s.size();
		}
	}
	size_t charsPerLine = std::max(longest, static_cast<size_t>(15));

	// Level
	std::string level = "Level " + std::to_string(actor.GetLevel());
	sfe::RichText levelText;
	levelText.setString(level);
	tooltipText.push_back(levelText);

	// HP
	std::string hp = "HP";
	std::string hpValue = std::to_string(actor.GetCurrentHP()) + "/" + std::to_string(actor.GetMaxHP());
	for (size_t i = 0; i < charsPerLine - 2 - hpValue.size(); i++) {
		hp += " ";
	}
	hp += "#heal " + hpValue;
	sfe::RichText hpText;
	hpText.setString(hp);
	tooltipText.push_back(hpText);

	// MP and SP
	std::string mp = "MP";
	std::string mpValue = std::to_string(actor.GetCurrentMP());

	for (size_t i = 0; i < charsPerLine / 2 - mpValue.size() - 3 + charsPerLine % 2; i++) {
		mp += " ";
	}

	std::string sp = "SP";
	std::string spValue = std::to_string(actor.GetCurrentSP());

	for (size_t i = 0; i < charsPerLine / 2 - spValue.size() - 2; i++) {
		sp += " ";
	}

	std::string mpsp = mp + "#spell " + mpValue + " #default " + sp + "#skill " + spValue;
	sfe::RichText mpspText;
	mpspText.setString(mpsp);
	tooltipText.push_back(mpspText);

	// Auras
	for (auto& aura : auras) {
		std::string s = "  ";
		if (aura.IsBuff()) {
			s += "#player ";
		}
		else {
			s += "#monster ";
		}
		s += aura.GetName();
		int duration = aura.GetCurrentDuration();
		if (duration > 0) {
			s += " [" + convertToSec(duration) + "]";
		}
		sfe::RichText rs;
		rs.setString(s);
		tooltipText.push_back(rs);
	}

	// set sizes
	setSizes();
}

void Tooltip::SetTooltip(Item& item, bool displayCost) {
	tooltipText.clear();
	float titleFontSizeF = static_cast<float>(titleFontSize);
	float textFontSizeF = static_cast<float>(textFontSize);

	const size_t textPerLine = 50u;

	// converts seconds into string
	auto convertToSec = [](int i) {
		std::string s;
		if (i > 999) {
			s = std::to_string(i / 100) + "s";
		}
		else {
			// make sure it always shows two decimals if use time is less than 10s
			std::string remainder = std::to_string(i % 100);
			if (remainder.length() == 1) {
				remainder = "0" + remainder;
			}

			s = std::to_string(i / 100) + "." + remainder + "s";
		}

		return s;
	};

	// text
	std::string s;
	switch (item.GetRarity()) {
		case Rarity::Magical:
			s += "#magical ";
			break;
		case Rarity::Rare:
			s += "#rare ";
			break;
		case Rarity::FixedArtifact:
			s += "#fixedart ";
			break;
		case Rarity::RandomArtifact:
			s += "#randart ";
			break;
		case Rarity::Item:
			s += "#item ";
			break;
		default:
			break;
	}
	s += item.GetName();
	titleText.setString(s);
	s = "#aaaaaa ";

	switch (item.GetItemType()) {
		case ItemType::Potion:
			s += "Potion";
			break;
		case ItemType::Scroll:
			s += "Scroll";
			break;
		case ItemType::Rod:
			s += "Rod";
			break;
		case ItemType::Tome:
			s += "Ability Tome";
			break;
		case ItemType::Consumable:
			s += "Consumable";
			break;
		case ItemType::Equipment:
			s += "Equipment - " + DataString::EquipTypeString(item.GetEquipType());
			break;
		default:
			s += "Unknown Item";
			break;
	}
	sfe::RichText itemTypeText;
	itemTypeText.setString(s);
	tooltipText.push_back(itemTypeText);

	// stat mods
	if (item.GetItemType() == ItemType::Equipment) {
		// attack speed and range
		if (item.IsWeapon()) {
			sfe::RichText speedRange;
			std::string speed = "Attack Speed ";
			speed += convertToSec(item.GetAttackSpeed());
			std::string range = "Range ";
			range += std::to_string(item.GetAttackRange() / 100) + "." + std::to_string(item.GetAttackRange() % 100 / 10);
			std::string complete = speed;
			for (size_t i = 0; i < textPerLine - speed.size() - range.size(); i++) {
				complete += " ";
			}
			complete += range;
			speedRange.setString(complete);
			tooltipText.push_back(speedRange);

			// weapon damage multiplier
			std::string wdm = std::to_string(item.GetWeaponDamageMultiplier() / 10) + "% Weapon Damage Multiplier";
			sfe::RichText wdmText;
			wdmText.setString(wdm);
			tooltipText.push_back(wdmText);
		}
		
		
		// implicit
		auto implicitMods = item.GetImplicitStatMods();
		for (auto& sm : implicitMods) {
			sfe::RichText affix;
			affix.setString(DataString::StatModString(sm));
			tooltipText.push_back(affix);
		}

		// explicit / random
		auto explicitMods = item.GetExplicitStatMods();
		auto randomMods = item.GetRandomStatMods();
		auto bonusStrings = item.GetBonusModStrings();

		// small divider
		// todo: make it look nicer
		if (!explicitMods.empty() || !randomMods.empty()) {
			//sfe::RichText divider;
			//divider.setString("----------------");
			//tooltipText.push_back(divider);
		}

		for (auto& sm : explicitMods) {
			sfe::RichText affix;
			affix.setString("#affix " + DataString::StatModString(sm));
			tooltipText.push_back(affix);
		}

		for (auto& sm : randomMods) {
			sfe::RichText affix;
			affix.setString("#affix " + DataString::StatModString(sm));
			tooltipText.push_back(affix);
		}

		for (auto& bms : bonusStrings) {
			sfe::RichText bonus;
			bonus.setString("#affix >" + bms);
			tooltipText.push_back(bonus);
		}
	}

	// use text
	if (item.GetItemType() == ItemType::Potion || item.GetItemType() == ItemType::Scroll || item.GetItemType() == ItemType::Consumable) {
		if (records.IsIdentified(item.GetItemID()) || item.GetItemType() == ItemType::Consumable) {
			Ability* ability = item.GetInvokedAbility();
			s = ability->GetDescription(nullptr);
			sfe::RichText desc;
			desc.setString(s);
			tooltipText.push_back(desc);
		}
		else {
			s = "Drink me.";
			sfe::RichText desc;
			desc.setString(s);
			tooltipText.push_back(desc);
		}
	}

	// list of abilities
	if (item.GetItemType() == ItemType::Tome) {
		s = "This tome contains knowledge of the following abilities:";
		sfe::RichText desc;
		desc.setString(s);
		tooltipText.push_back(desc);

		auto abilities = item.GetTeachableAbilities();
		for (auto& a : abilities) {
			s = "  " + DataString::AbilityNameString(a);
			sfe::RichText abilityText;
			abilityText.setString(s);
			tooltipText.push_back(abilityText);
		}

	}

	// item value
	if (displayCost) {
		s = "Costs " + std::to_string(item.GetValue()) + " Gold";
		sfe::RichText value;
		value.setString(s);
		tooltipText.push_back(value);
	}

	// set sizes
	setSizes();
}

void Tooltip::SetTooltip(Actor* user, Ability& ability) {
	const size_t charsPerLine = 50;
	
	tooltipText.clear();

	// converts seconds into string
	auto convertToSec = [](int i) {
		std::string s;
		if (i > 999) {
			s = std::to_string(i / 100) + "s";
		}
		else {
			// make sure it always shows two decimals if use time is less than 10s
			std::string remainder = std::to_string(i % 100);
			if (remainder.length() == 1) {
				remainder = "0" + remainder;
			}

			s = std::to_string(i / 100) + "." + remainder + "s";
		}

		return s;
	};

	// spacing
	auto formatString = [&](std::string left, std::string right) {
		std::string result;
		size_t spaces = charsPerLine - left.length() - right.length();
		if (left.length() + right.length() > charsPerLine) {
			spaces = 1;
		}
		result = left;
		for (size_t i = 0; i < spaces; i++) {
			result += " ";
		}
		result += right;

		return result;
	};

	// name
	std::string s;
	if (ability.IsSpell()) {
		s = "#spell ";
	}
	else {
		s = "#skill ";
	}
	s += ability.GetName();
	titleText.setString(s);

	// ability costs and range
	s.clear();

	// Active Ability
	if (!ability.IsPassive()) {
		int mpCost = ability.GetMPCost(user);
		int spCost = ability.GetSPCost(user);

		if (mpCost > 0) {
			s += "#spell " + std::to_string(mpCost) + " MP";
		}
		if (spCost > 0) {
			s += "#skill " + std::to_string(spCost) + " SP";
		}

		if (mpCost == 0 && spCost == 0) {
			s = "#aaaaaa No Cost";
		}

		int range = ability.GetRangeValue(user);
		std::string r;
		size_t spaces = charsPerLine;
		if (range == -1) {
			if (user != nullptr) {
				range = user->GetAttackRange();
			}
			else {
				r = "Attack Range";
				spaces -= r.length();
				if (mpCost > 0) {
					spaces -= (std::to_string(mpCost).length() + 3);
				}
				if (spCost > 0) {
					spaces -= (std::to_string(spCost).length() + 3);
				}
				if (mpCost == 0 && spCost == 0) {
					spaces -= 6;
				}
				r = "#default " + r;

				for (size_t i = 0; i < spaces; i++) {
					s += " ";
				}
				s += r;
			}
		}

		if (range > 0) {
			r = "Range " + std::to_string(range / 100) + "." + std::to_string(range % 100 / 10);
			if (ability.IsProjectile()) {
				r += "P";
			}
			spaces -= r.length();
			if (mpCost > 0) {
				spaces -= (std::to_string(mpCost).length() + 3);
			}
			if (spCost > 0) {
				spaces -= (std::to_string(spCost).length() + 3);
			}
			if (mpCost == 0 && spCost == 0) {
				spaces -= 6;
			}
			r = "#default " + r;

			for (size_t i = 0; i < spaces; i++) {
				s += " ";
			}
			s += r;
		}


		sfe::RichText costRangeText;
		costRangeText.setString(s);
		tooltipText.push_back(costRangeText);

		// use time and cooldown
		int useTime = ability.GetUseTime(user);
		if (useTime < 0) {
			s = std::to_string(useTime * -100) + "% Weapon Speed";
		}
		else {
			s = convertToSec(useTime) + " Recovery Time";
		}

		int cooldown = ability.GetCooldown(user);
		if (cooldown > 0) {
			s = formatString(s, convertToSec(cooldown) + " Cooldown");
		}

		sfe::RichText useTimeCooldownText;
		useTimeCooldownText.setString(s);
		tooltipText.push_back(useTimeCooldownText);
	}
	// Passive Ability
	else {
		s = "#aaaaaa Passive";
		sfe::RichText passiveText;
		passiveText.setString(s);
		tooltipText.push_back(passiveText);
	}


	// description
	s = ability.GetDescription(user);
	auto sv = WordWrap::WrapString(s, charsPerLine);
	for (auto& s : sv) {
		sfe::RichText descText;
		descText.setString(s);
		tooltipText.push_back(descText);
	}

	// set sizes
	setSizes();
}

void Tooltip::SetTooltip(Aura& aura) {
	const size_t charsPerLine = 50;

	tooltipText.clear();

	// converts seconds into string
	auto convertToSec = [](int i) {
		std::string s;
		if (i > 999) {
			s = std::to_string(i / 100) + "s";
		}
		else {
			// make sure it always shows two decimals if use time is less than 10s
			std::string remainder = std::to_string(i % 100);
			if (remainder.length() == 1) {
				remainder = "0" + remainder;
			}

			s = std::to_string(i / 100) + "." + remainder + "s";
		}

		return s;
	};

	// spacing
	auto formatString = [&](std::string left, std::string right) {
		std::string result;
		size_t spaces = charsPerLine - left.length() - right.length();
		if (left.length() + right.length() > charsPerLine) {
			spaces = 1;
		}
		result = left;
		for (size_t i = 0; i < spaces; i++) {
			result += " ";
		}
		result += right;

		return result;
	};

	// name
	std::string s = aura.GetName();
	titleText.setString(s);

	// duration
	sfe::RichText durationText;
	if (aura.HasDuration()) {
		s = convertToSec(aura.GetCurrentDuration()) + " Remaining";
	}
	else {
		s = "#aaaaaa No Duration";
	}
	durationText.setString(s);
	tooltipText.push_back(durationText);

	// description
	s = aura.GetDescription();
	auto stringVector = WordWrap::WrapString(s, charsPerLine);
	for (auto& line : stringVector) {
		sfe::RichText desc;
		desc.setString(line);
		tooltipText.push_back(desc);
	}

	setSizes();
}

void Tooltip::setSizes() {
	sf::Vector2f size;
	float titleFontSizeF = static_cast<float>(titleFontSize);
	float textFontSizeF = static_cast<float>(textFontSize);

	size.x = std::max(20.f, titleText.getLocalBounds().width + 8.f); // 256
	size.y = (titleFontSizeF + 7.f) + 2.f;

	for (auto& t : tooltipText) {
		t.setFont(*assetManager.LoadFont(settings.Font));
		t.setCharacterSize(textFontSize);
		size.x = std::max(size.x, t.getLocalBounds().width + 8.f);
		size.y += textFontSizeF + 6.f;
	}

	background.setSize(size);
}