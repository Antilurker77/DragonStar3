// ================================================================
//
// inspectWindow.cpp
//
// ================================================================

#include "inspectWindow.hpp"

#include "../core/assetManager.hpp"
#include "../core/combat.hpp"
#include "../core/settings.hpp"
#include "../data/ability.hpp"
#include "../data/id/element.hpp"
#include "../entity/actor.hpp"

InspectWindow::InspectWindow() {
	background.setSize(sf::Vector2f(600.f, 500.f));
	background.setOutlineThickness(1.f);
	background.setFillColor(sf::Color(0, 0, 0, 191));
	background.setOutlineColor(sf::Color(255, 255, 255, 255));

	nameText.setFont(*assetManager.LoadFont(settings.Font));
	nameText.setCharacterSize(fontSize);

	levelText.setFont(*assetManager.LoadFont(settings.Font));
	levelText.setCharacterSize(fontSize);

	hpmpspText.setFont(*assetManager.LoadFont(settings.Font));
	hpmpspText.setCharacterSize(fontSize);

	powerText.setFont(*assetManager.LoadFont(settings.Font));
	powerText.setCharacterSize(fontSize);

	defenseText.setFont(*assetManager.LoadFont(settings.Font));
	defenseText.setCharacterSize(fontSize);

	critText.setFont(*assetManager.LoadFont(settings.Font));
	critText.setCharacterSize(fontSize);

	hastedsText.setFont(*assetManager.LoadFont(settings.Font));
	hastedsText.setCharacterSize(fontSize);

	resistanceHeaderText.setFont(*assetManager.LoadFont(settings.Font));
	resistanceHeaderText.setCharacterSize(fontSize);

	resistanceFirstText.setFont(*assetManager.LoadFont(settings.Font));
	resistanceFirstText.setCharacterSize(fontSize);

	resistanceSecondText.setFont(*assetManager.LoadFont(settings.Font));
	resistanceSecondText.setCharacterSize(fontSize);

	abilityHeaderText.setFont(*assetManager.LoadFont(settings.Font));
	abilityHeaderText.setCharacterSize(fontSize);

	auraHeaderText.setFont(*assetManager.LoadFont(settings.Font));
	auraHeaderText.setCharacterSize(fontSize);
}

void InspectWindow::GetInput(sf::RenderWindow& window, sf::Event& ev) {
	sf::Mouse mouse;
	mousePos = mouse.getPosition(window);
	leftClick = false;
	rightClick = false;
	wantToClose = false;

	switch (ev.type) {
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Left) {
			leftClick = true;
		}
		if (ev.mouseButton.button == sf::Mouse::Right) {
			rightClick = true;
		}
		break;
	case sf::Event::KeyReleased:
		if (ev.key.code == settings.UIKeybinds.Loot) {
			wantToClose = true;
		}
		// Player Moves
		if (ev.key.code == settings.MoveKeybinds.MoveN || ev.key.code == settings.MoveKeybinds.MoveNAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveW || ev.key.code == settings.MoveKeybinds.MoveWAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveS || ev.key.code == settings.MoveKeybinds.MoveSAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveE || ev.key.code == settings.MoveKeybinds.MoveEAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveNW || ev.key.code == settings.MoveKeybinds.MoveNWAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveNE || ev.key.code == settings.MoveKeybinds.MoveNEAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveSE || ev.key.code == settings.MoveKeybinds.MoveSEAlt) {
			wantToClose = true;
		}
		if (ev.key.code == settings.MoveKeybinds.MoveSW || ev.key.code == settings.MoveKeybinds.MoveSWAlt) {
			wantToClose = true;
		}
		break;
	default:
		break;
	}
}

bool InspectWindow::Update(float secondsPerUpdate) {
	sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	displayTooltip = false;

	if (wantToClose) {
		leftClick = false;
		rightClick = false;
		return false;
	}

	if (leftClick && !background.getGlobalBounds().contains(mouseF)) {
		leftClick = false;
		wantToClose = false;
		return false;
	}
	
	for (size_t i = 0; i < abilityBackgrounds.size(); i++) {
		if (abilityBackgrounds[i].getGlobalBounds().contains(mouseF)) {
			Ability& ability = target->GetAbilities()->at(i);
			displayTooltip = true;
			tooltip.SetTooltip(target, ability);
			auto size = tooltip.GetSize();
			tooltip.SetPosition(mouseF.x, mouseF.y - size.y);
			break;
		}
	}

	if (!displayTooltip) {
		for (size_t i = 0; i < auraIcons.size(); i++) {
			if (auraBackgrounds[i].getGlobalBounds().contains(mouseF)) {
				Aura& aura = target->GetAuras().at(i);
				displayTooltip = true;
				tooltip.SetTooltip(aura);
				auto size = tooltip.GetSize();
				tooltip.SetPosition(mouseF.x, mouseF.y - size.y);
				break;
			}
		}
	}

	return true;
}

void InspectWindow::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);

	window.draw(nameText);
	window.draw(levelText);
	window.draw(hpmpspText);
	window.draw(powerText);
	window.draw(defenseText);
	window.draw(critText);
	window.draw(hastedsText);
	window.draw(resistanceHeaderText);
	window.draw(resistanceFirstText);
	window.draw(resistanceSecondText);
	window.draw(abilityHeaderText);

	for (size_t i = 0; i < abilityBackgrounds.size(); i++) {
		window.draw(abilityBackgrounds[i]);
		window.draw(abilityIcons[i]);
	}

	window.draw(auraHeaderText);

	for (size_t i = 0; i < auraBackgrounds.size(); i++) {
		window.draw(auraBackgrounds[i]);
		window.draw(auraIcons[i]);
	}

	if (displayTooltip) {
		tooltip.Draw(window, timeRatio);
	}
}

void InspectWindow::SetActor(Actor* actor) {
	EventOptions eo;
	sf::Vector2f pos;
	sf::Vector2f textPos;
	sf::Vector2f size = background.getSize();
	pos.x = static_cast<float>(settings.ScreenWidth) / 2.f - size.x / 2.f;
	pos.y = static_cast<float>(settings.ScreenHeight) / 2.f - size.y / 2.f;

	float fontSizeFloat = static_cast<float>(fontSize);
	float margin = 2.f;

	target = actor;

	background.setPosition(pos);

	std::string name = "#monster " + actor->GetName();
	std::string title = actor->GetTitle();
	if (!title.empty()) {
		name += ", " + title;
	}
	nameText.setString(name);
	textPos.x = std::roundf(pos.x + size.x / 2.f - nameText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin);
	nameText.setPosition(textPos);

	std::string level = "#aaaaaa Level #default " + std::to_string(actor->GetLevel());
	levelText.setString(level);
	textPos.x = std::roundf(pos.x + size.x / 2.f - levelText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin));
	levelText.setPosition(textPos);

	std::string hpmpsp = "#aaaaaa HP  #heal " + std::to_string(actor->GetCurrentHP()) + "/" + std::to_string(actor->GetMaxHP());
	hpmpsp += "    #aaaaaa MP  #spell " + std::to_string(actor->GetCurrentMP()) + "/" + std::to_string(actor->GetMaxMP());
	hpmpsp += "    #aaaaaa SP  #skill " + std::to_string(actor->GetCurrentSP()) + "/" + std::to_string(actor->GetMaxSP());
	hpmpspText.setString(hpmpsp);
	textPos.x = std::roundf(pos.x + size.x / 2.f - hpmpspText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 3.f);
	hpmpspText.setPosition(textPos);

	std::string power = "#aaaaaa Attack Power  #skill " + std::to_string(actor->GetAttackPower(eo, false));
	power += "    #aaaaaa Spell Power  #spell " + std::to_string(actor->GetSpellPower(eo, false));
	power += "    #aaaaaa Accuracy  #default " + std::to_string(actor->GetAccuracy(eo, false));
	powerText.setString(power);
	textPos.x = std::roundf(pos.x + size.x / 2.f - powerText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 5.f);
	powerText.setPosition(textPos);

	std::string defense = "#aaaaaa Armor  #skill " + std::to_string(actor->GetArmor(false));
	defense += "    #aaaaaa Spell Defense  #spell " + std::to_string(actor->GetMagicArmor(eo, false));
	defense += "    #aaaaaa Evasion  #default " + std::to_string(actor->GetEvasion(eo, false));
	defenseText.setString(defense);
	textPos.x = std::roundf(pos.x + size.x / 2.f - defenseText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 6.f);
	defenseText.setPosition(textPos);

	int critChance = actor->GetCritChance(eo, false);
	int critPower = actor->GetCritPower(eo, false);
	std::string crit = "#aaaaaa Crit Chance  #default " + std::to_string(critChance / 10) + "." + std::to_string(std::abs(critChance % 10)) + "%";
	crit += "    #aaaaaa Crit Power  #default " + std::to_string(critPower / 10) + "." + std::to_string(std::abs(critPower % 10)) + "%";
	critText.setString(crit);
	textPos.x = std::roundf(pos.x + size.x / 2.f - critText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 8.f);
	critText.setPosition(textPos);

	int haste = actor->GetHaste(eo, false) - 1000;
	int ds = actor->GetDoubleStrikeChance(eo, false);
	std::string hasteds = "#aaaaaa Haste  #default " + std::to_string(haste / 10) + "." + std::to_string(std::abs(haste % 10)) + "%";
	hasteds += "    #aaaaaa Double Strike Chance  #default " + std::to_string(ds / 10) + "." + std::to_string(std::abs(ds % 10)) + "%";
	hastedsText.setString(hasteds);
	textPos.x = std::roundf(pos.x + size.x / 2.f - hastedsText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 9.f);
	hastedsText.setPosition(textPos);

	std::string resistanceHeader = "#aaaaaa Resistance";
	resistanceHeaderText.setString(resistanceHeader);
	textPos.x = std::roundf(pos.x + size.x / 2.f - resistanceHeaderText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 11.f);
	resistanceHeaderText.setPosition(textPos);

	std::string resistanceFirst = "#aaaaaa Fire  #default ";
	eo.Elements = { Element::Fire };
	resistanceFirst += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceFirst += "    #aaaaaa Water  #default ";
	eo.Elements = { Element::Water };
	resistanceFirst += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceFirst += "    #aaaaaa Lightning  #default ";
	eo.Elements = { Element::Lightning };
	resistanceFirst += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceFirst += "    #aaaaaa Ice  #default ";
	eo.Elements = { Element::Ice };
	resistanceFirst += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceFirstText.setString(resistanceFirst);
	textPos.x = std::roundf(pos.x + size.x / 2.f - resistanceFirstText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 12.f);
	resistanceFirstText.setPosition(textPos);

	std::string resistanceSecond = "#aaaaaa Arcane  #default ";
	eo.Elements = { Element::Arcane };
	resistanceSecond += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceSecond += "    #aaaaaa Poison  #default ";
	eo.Elements = { Element::Poison };
	resistanceSecond += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceSecond += "    #aaaaaa Light  #default ";
	eo.Elements = { Element::Light };
	resistanceSecond += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceSecond += "    #aaaaaa Dark  #default ";
	eo.Elements = { Element::Dark };
	resistanceSecond += std::to_string(actor->GetResistance(eo, false) / 10) + "%";
	resistanceSecondText.setString(resistanceSecond);
	textPos.x = std::roundf(pos.x + size.x / 2.f - resistanceSecondText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 13.f);
	resistanceSecondText.setPosition(textPos);

	std::string abilityHeader = "#aaaaaa Abilities";
	abilityHeaderText.setString(abilityHeader);
	textPos.x = std::roundf(pos.x + size.x / 2.f - abilityHeaderText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 15.f);
	abilityHeaderText.setPosition(textPos);

	auto abilities = actor->GetAbilities();
	sf::Vector2f iconPos;
	iconPos.x = std::roundf(pos.x + margin + 22.f);
	iconPos.y = std::roundf(pos.y + margin + 12.f + (fontSizeFloat + margin) * 16.f);
	abilityBackgrounds.reserve(abilities->size());
	abilityIcons.reserve(abilities->size());
	for (size_t i = 0; i < abilities->size(); i++) {
		Ability* ability = &abilities->at(i);
		float iFloat = static_cast<float>(i);
		sf::RectangleShape background;
		background.setSize(sf::Vector2f(40.f, 40.f));
		background.setFillColor(sf::Color(0, 0, 0, 255));
		background.setOutlineThickness(1.f);
		background.setOutlineColor(sf::Color(255, 255, 255, 255));
		background.setPosition(iconPos.x + iFloat * 42.f, iconPos.y);
		abilityBackgrounds.push_back(background);

		sf::Sprite icon;
		icon.setTexture(*assetManager.LoadTexture(ability->GetIcon()));
		icon.setPosition(iconPos.x + iFloat * 42.f, iconPos.y);
		icon.setScale(2.f, 2.f);
		abilityIcons.push_back(icon);
	}

	std::string auraHeader = "#aaaaaa Status Effects";
	auraHeaderText.setString(auraHeader);
	textPos.x = std::roundf(pos.x + size.x / 2.f - auraHeaderText.getLocalBounds().width / 2.f);
	textPos.y = std::roundf(pos.y + margin + (fontSizeFloat + margin) * 22.f);
	auraHeaderText.setPosition(textPos);

	auto auras = actor->GetAuras();
	iconPos.x = std::roundf(pos.x + margin + 22.f);
	iconPos.y = std::roundf(pos.y + margin + 12.f + (fontSizeFloat + margin) * 23.f);
	auraBackgrounds.reserve(auras.size());
	auraIcons.reserve(auras.size());
	for (size_t i = 0; i < auras.size(); i++) {
		Aura& aura = auras[i];
		float iFloat = static_cast<float>(i);
		sf::RectangleShape background;
		background.setSize(sf::Vector2f(40.f, 40.f));
		background.setFillColor(sf::Color(0, 0, 0, 255));
		background.setOutlineThickness(1.f);
		if (aura.IsBuff()) {
			background.setOutlineColor(sf::Color(100, 100, 255, 255));
		}
		else {
			background.setOutlineColor(sf::Color(255, 100, 100, 255));
		}
		background.setPosition(iconPos.x + iFloat * 42.f, iconPos.y);
		auraBackgrounds.push_back(background);

		sf::Sprite icon;
		icon.setTexture(*assetManager.LoadTexture(aura.GetIcon()));
		icon.setPosition(iconPos.x + iFloat * 42.f, iconPos.y);
		icon.setScale(2.f, 2.f);
		auraIcons.push_back(icon);
	}
}