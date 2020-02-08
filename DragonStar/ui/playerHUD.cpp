// ================================================================
//
// playerHUD.cpp
//
// ================================================================

#include "playerHUD.hpp"

#include "../core/assetManager.hpp"
#include "../core/settings.hpp"
#include "../data/ability.hpp"
#include "../data/aura.hpp"
#include "../entity/actor.hpp"
#include "../scene/dungeonScene.hpp"

PlayerHUD::PlayerHUD() {
	// background
	background.setSize(sf::Vector2f((iconSize + 4.f) * 12.f + 2.f, (iconSize + 4.f) * 2.f + 2.f));
	background.setOutlineThickness(1.f);
	background.setFillColor(sf::Color(0, 0, 0, 191));
	background.setOutlineColor(sf::Color(255, 255, 255, 191));
	
	// shortcut slots
	for (size_t i = 0; i < shortcutSlots.size(); i++) {
		shortcutSlots[i].setSize(sf::Vector2f(iconSize, iconSize));
		shortcutSlots[i].setOutlineThickness(1.f);
		shortcutSlots[i].setFillColor(sf::Color(0, 0, 0, 255));
		shortcutSlots[i].setOutlineColor(sf::Color(255, 255, 255, 255));

		shortcutIcons[i].setScale(2.f, 2.f);
		displayShortcutIcons[i] = false;

		unavailableSquare[i].setFillColor(sf::Color(0, 0, 0, 128));
		unavailableSquare[i].setSize(sf::Vector2f(iconSize, iconSize));
		displayUnavailableSquare[i] = false;

		cooldownText[i].setFont(*assetManager.LoadFont(settings.Font));
		cooldownText[i].setFillColor(sf::Color(255, 127, 127, 255));
		cooldownText[i].setCharacterSize(10u);
		cooldownText[i].setOutlineThickness(1.f);
		displayCooldownText[i] = false;

		chargeText[i].setFont(*assetManager.LoadFont(settings.Font));
		chargeText[i].setFillColor(sf::Color(255, 255, 255, 255));
		chargeText[i].setCharacterSize(14u);
		chargeText[i].setOutlineThickness(1.f);
		displayChargeText[i] = false;
	}

	// hp bar
	hpBarBackground.setSize(sf::Vector2f(240.f, 24.f));
	hpBarBackground.setOutlineThickness(1.f);
	hpBarBackground.setFillColor(sf::Color(0, 0, 0, 191));
	hpBarBackground.setOutlineColor(sf::Color(255, 255, 255, 191));

	hpBar.setSize(hpBarBackground.getSize());
	hpBar.setFillColor(sf::Color(0, 150, 0, 255));

	hpText.setFont(*assetManager.LoadFont(settings.Font));
	hpText.setCharacterSize(barTextFontSize);
	hpText.setOutlineThickness(1.f);

	// mp bar
	//mpBarBackground.setSize(sf::Vector2f(120.f, 24.f));
	mpBarBackground.setSize(sf::Vector2f(240.f, 24.f));
	mpBarBackground.setOutlineThickness(1.f);
	mpBarBackground.setFillColor(sf::Color(0, 0, 0, 191));
	mpBarBackground.setOutlineColor(sf::Color(255, 255, 255, 191));

	mpBar.setSize(mpBarBackground.getSize());
	mpBar.setFillColor(sf::Color(0, 150, 150, 255));

	mpText.setFont(*assetManager.LoadFont(settings.Font));
	mpText.setCharacterSize(barTextFontSize);
	mpText.setOutlineThickness(1.f);

	// sp bar
	//spBarBackground.setSize(sf::Vector2f(120.f, 24.f));
	spBarBackground.setSize(sf::Vector2f(240.f, 24.f));
	spBarBackground.setOutlineThickness(1.f);
	spBarBackground.setFillColor(sf::Color(0, 0, 0, 191));
	spBarBackground.setOutlineColor(sf::Color(255, 255, 255, 191));

	spBar.setSize(spBarBackground.getSize());
	spBar.setFillColor(sf::Color(150, 113, 0, 255));

	spText.setFont(*assetManager.LoadFont(settings.Font));
	spText.setCharacterSize(barTextFontSize);
	spText.setOutlineThickness(1.f);

	// test
	SetShortcut(0, static_cast<AbilityID>(1));

	Initialize();
}

void PlayerHUD::Load(std::array<int, 24> shortcutAbilities) {
	for (size_t i = 0; i < shortcuts.size(); i++) {
		if (shortcutAbilities[i] != 0) {
			AbilityID id = static_cast<AbilityID>(shortcutAbilities[i]);
			shortcuts[i].AbilityID = id;

			// set the icon
			Ability a(id, 0);
			shortcutIcons[i].setTexture(*assetManager.LoadTexture(a.GetIcon()));
			displayShortcutIcons[i] = true;
		}
		else {
			displayShortcutIcons[i] = false;
		}
	}
}

void PlayerHUD::GetInput(sf::RenderWindow& window, sf::Event& ev) {
	sf::Mouse mouse;
	mousePos = mouse.getPosition(window);
	leftClick = false;
	usingShortcut = shortcuts.size();

	switch (ev.type) {
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftClick = true;
			}
			break;
		case sf::Event::KeyReleased:
			// todo: fix this monstrosity
			if (ev.key.shift && ev.key.code == sf::Keyboard::Num1) {
				usingShortcut = 12;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num2) {
				usingShortcut = 13;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num3) {
				usingShortcut = 14;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num4) {
				usingShortcut = 15;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num5) {
				usingShortcut = 16;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num6) {
				usingShortcut = 17;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num7) {
				usingShortcut = 18;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num8) {
				usingShortcut = 19;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num9) {
				usingShortcut = 20;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Num0) {
				usingShortcut = 21;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Dash) {
				usingShortcut = 22;
			}
			else if (ev.key.shift && ev.key.code == sf::Keyboard::Equal) {
				usingShortcut = 23;
			}
			else if (ev.key.code == sf::Keyboard::Num1) {
				usingShortcut = 0;
			}
			else if (ev.key.code == sf::Keyboard::Num2) {
				usingShortcut = 1;
			}
			else if (ev.key.code == sf::Keyboard::Num3) {
				usingShortcut = 2;
			}
			else if (ev.key.code == sf::Keyboard::Num4) {
				usingShortcut = 3;
			}
			else if (ev.key.code == sf::Keyboard::Num5) {
				usingShortcut = 4;
			}
			else if (ev.key.code == sf::Keyboard::Num6) {
				usingShortcut = 5;
			}
			else if (ev.key.code == sf::Keyboard::Num7) {
				usingShortcut = 6;
			}
			else if (ev.key.code == sf::Keyboard::Num8) {
				usingShortcut = 7;
			}
			else if (ev.key.code == sf::Keyboard::Num9) {
				usingShortcut = 8;
			}
			else if (ev.key.code == sf::Keyboard::Num0) {
				usingShortcut = 9;
			}
			else if (ev.key.code == sf::Keyboard::Dash) {
				usingShortcut = 10;
			}
			else if (ev.key.code == sf::Keyboard::Equal) {
				usingShortcut = 11;
			}
			break;
	}
}

void PlayerHUD::Update(Actor* player, DungeonScene& dungeonScene, float secondsPerUpdate) {
	sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	displayTooltip = false;
	
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

	// HP, MP, and SP Bars
	int currentHP = player->GetCurrentHP();
	int maxHP = player->GetMaxHP();

	int currentMP = player->GetCurrentMP();
	int maxMP = player->GetMaxMP();

	int currentSP = player->GetCurrentSP();
	int maxSP = player->GetMaxSP();

	hpText.setString(std::to_string(currentHP) + "/" + std::to_string(maxHP));
	mpText.setString(std::to_string(currentMP) + "/" + std::to_string(maxMP));
	spText.setString(std::to_string(currentSP) + "/" + std::to_string(maxSP));

	hpBar.setSize(sf::Vector2f(std::round(240.f * currentHP / maxHP), hpBar.getSize().y));
	mpBar.setSize(sf::Vector2f(std::round(240.f * currentMP / maxMP), mpBar.getSize().y));
	spBar.setSize(sf::Vector2f(std::round(240.f * currentSP / maxSP), spBar.getSize().y));

	hpBar.setPosition(hpBarBackground.getPosition().x + (240.f - hpBar.getSize().x), hpBarBackground.getPosition().y);
	mpBar.setPosition(mpBarBackground.getPosition().x + (240.f - mpBar.getSize().x), mpBarBackground.getPosition().y);
	spBar.setPosition(spBarBackground.getPosition().x + (240.f - spBar.getSize().x), spBarBackground.getPosition().y);

	// recenter text
	hpText.setOrigin(hpText.getLocalBounds().left, hpText.getLocalBounds().top);
	hpText.setPosition(std::round(hpBarBackground.getPosition().x + (hpBarBackground.getSize().x / 2.f) - (hpText.getLocalBounds().width / 2.f)), std::round(hpBarBackground.getPosition().y + (hpBarBackground.getSize().y / 2.f) - (hpText.getLocalBounds().height / 2.f)));

	mpText.setOrigin(mpText.getLocalBounds().left, mpText.getLocalBounds().top);
	mpText.setPosition(std::round(mpBarBackground.getPosition().x + (mpBarBackground.getSize().x / 2.f) - (mpText.getLocalBounds().width / 2.f)), std::round(mpBarBackground.getPosition().y + (mpBarBackground.getSize().y / 2.f) - (mpText.getLocalBounds().height / 2.f)));

	spText.setOrigin(spText.getLocalBounds().left, spText.getLocalBounds().top);
	spText.setPosition(std::round(spBarBackground.getPosition().x + (spBarBackground.getSize().x / 2.f) - (spText.getLocalBounds().width / 2.f)), std::round(spBarBackground.getPosition().y + (spBarBackground.getSize().y / 2.f) - (spText.getLocalBounds().height / 2.f)));

	// buffs and debuffs
	// todo: stacks
	buffBackgrounds.clear();
	buffIcons.clear();
	buffDurationText.clear();
	displayBuffDurationText.clear();
	buffStackText.clear();
	displayBuffStackText.clear();

	debuffBackgrounds.clear();
	debuffIcons.clear();
	debuffDurationText.clear();
	displayDebuffDurationText.clear();
	debuffStackText.clear();
	displayDebuffStackText.clear();

	std::vector<Aura>& auras = player->GetAuras();
	size_t index = 0;

	for (auto& aura : auras) {
		sf::RectangleShape background;
		background.setFillColor(sf::Color(0, 0, 0, 255));
		background.setSize(sf::Vector2f(40.f, 40.f));
		background.setOutlineThickness(1.f);

		sf::Sprite sprite;
		sprite.setScale(2.f, 2.f);

		sf::Text durationText;
		durationText.setCharacterSize(12u);
		durationText.setFont(*assetManager.LoadFont(settings.Font));
		durationText.setOutlineThickness(1.f);
		durationText.setOutlineColor(sf::Color(0, 0, 0, 255));

		sf::Text stackText;
		stackText.setCharacterSize(12u);
		stackText.setFont(*assetManager.LoadFont(settings.Font));
		stackText.setOutlineThickness(1.f);
		stackText.setOutlineColor(sf::Color(0, 0, 0, 255));

		bool displayDuration = false;
		bool displayStacks = false;

		if (aura.IsBuff()) {
			background.setOutlineColor(sf::Color(100, 100, 255, 255));
			sprite.setTexture(*assetManager.LoadTexture(aura.GetIcon()));

			if (aura.HasDuration()) {
				displayDuration = true;
				std::string s(convertToSec(aura.GetCurrentDuration()));
				durationText.setString(s);
			}

			buffBackgrounds.push_back(background);
			buffIcons.push_back(sprite);
			buffDurationText.push_back(durationText);
			buffStackText.push_back(stackText);
			buffIndex.push_back(index);
			displayBuffDurationText.push_back(displayDuration);
			displayBuffStackText.push_back(displayStacks);
		}
		else {
			background.setOutlineColor(sf::Color(255, 100, 100, 255));
			sprite.setTexture(*assetManager.LoadTexture(aura.GetIcon()));

			if (aura.HasDuration()) {
				displayDuration = true;
				std::string s(convertToSec(aura.GetCurrentDuration()));
				durationText.setString(s);
			}

			debuffBackgrounds.push_back(background);
			debuffIcons.push_back(sprite);
			debuffDurationText.push_back(durationText);
			debuffStackText.push_back(stackText);
			debuffIndex.push_back(index);
			displayDebuffDurationText.push_back(displayDuration);
			displayDebuffStackText.push_back(displayStacks);
		}
		index++;
	}

	// unavailable square display
	for (size_t i = 0; i < shortcuts.size(); i++) {
		if (shortcuts[i].AbilityID != static_cast<AbilityID>(0)) {
			Ability* ab = player->GetAbility(shortcuts[i].AbilityID);
			if (ab->IsUsable(player)) {
				displayUnavailableSquare[i] = false;
				displayCooldownText[i] = false;
			}
			else {
				displayUnavailableSquare[i] = true;
			}

			int cooldown = ab->GetCurrentCooldown();
			if (cooldown > 0) {
				cooldownText[i].setString(convertToSec(cooldown));
				displayCooldownText[i] = true;
			}
			else {
				displayCooldownText[i] = false;
			}

			int charges = ab->GetCurrentCharges();
			if (charges > 1) {
				chargeText[i].setString(std::to_string(charges));
				displayChargeText[i] = true;
			}
			else {
				displayChargeText[i] = false;
			}
		}
		// todo: items
	}

	// tooltip display
	for (size_t i = 0; i < displayShortcutIcons.size(); i++) {
		if (displayShortcutIcons[i] && shortcutSlots[i].getGlobalBounds().contains(mouseF)) {
			if (shortcuts[i].AbilityID != static_cast<AbilityID>(0)) {
				Ability* ability = player->GetAbility(shortcuts[i].AbilityID);
				tooltip.SetTooltip(player, *ability);
				displayTooltip = true;
				auto size = tooltip.GetSize();
				tooltip.SetPosition(mouseF.x - size.x, mouseF.y - size.y);
				break;
			}
		}
	}

	// actor wants to use an ability
	if (usingShortcut < shortcuts.size()) {
		dungeonScene.SetTargettingMode(shortcuts[usingShortcut].AbilityID);
	}

	Initialize();

	// aura tooltips, must be done after initilization
	if (!displayTooltip) {
		for (size_t i = 0; i < buffBackgrounds.size(); i++) {
			if (buffBackgrounds[i].getGlobalBounds().contains(mouseF)) {
				tooltip.SetTooltip(auras[buffIndex[i]]);
				displayTooltip = true;
				auto size = tooltip.GetSize();
				tooltip.SetPosition(mouseF.x - size.x, mouseF.y - size.y);
				break;
			}
		}
	}

	if (!displayTooltip) {
		for (size_t i = 0; i < debuffBackgrounds.size(); i++) {
			if (debuffBackgrounds[i].getGlobalBounds().contains(mouseF)) {
				tooltip.SetTooltip(auras[debuffIndex[i]]);
				displayTooltip = true;
				auto size = tooltip.GetSize();
				tooltip.SetPosition(mouseF.x - size.x, mouseF.y - size.y);
				break;
			}
		}
	}
}

void PlayerHUD::Draw(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);

	for (auto& s : shortcutSlots) {
		window.draw(s);
	}
	for (size_t i = 0; i < shortcutIcons.size(); i++) {
		if (displayShortcutIcons[i]) {
			window.draw(shortcutIcons[i]);
			if (displayUnavailableSquare[i]) {
				window.draw(unavailableSquare[i]);
			}
			if (displayCooldownText[i]) {
				window.draw(cooldownText[i]);
			}
			if (displayChargeText[i]) {
				window.draw(chargeText[i]);
			}
		}
	}

	window.draw(hpBarBackground);
	window.draw(hpBar);
	window.draw(hpText);

	window.draw(mpBarBackground);
	window.draw(mpBar);
	window.draw(mpText);

	window.draw(spBarBackground);
	window.draw(spBar);
	window.draw(spText);

	for (size_t i = 0; i < buffBackgrounds.size(); i++) {
		window.draw(buffBackgrounds[i]);
		window.draw(buffIcons[i]);
		if (displayBuffDurationText[i]) {
			window.draw(buffDurationText[i]);
		}
		if (displayBuffStackText[i]) {
			window.draw(buffStackText[i]);
		}
	}

	for (size_t i = 0; i < debuffBackgrounds.size(); i++) {
		window.draw(debuffBackgrounds[i]);
		window.draw(debuffIcons[i]);
		if (displayDebuffDurationText[i]) {
			window.draw(debuffDurationText[i]);
		}
		if (displayDebuffStackText[i]) {
			window.draw(debuffStackText[i]);
		}
	}

	if (displayTooltip) {
		tooltip.Draw(window, timeRatio);
	}
}

void PlayerHUD::Initialize() {
	// background position
	sf::Vector2f backgroundPos;
	//backgroundPos.x = static_cast<float>(settings.ScreenWidth) / 2.f - (background.getSize().x / 2.f);
	//backgroundPos.y = static_cast<float>(settings.ScreenHeight) - background.getSize().y - 10.f;
	backgroundPos.x = static_cast<float>(settings.ScreenWidth) - background.getSize().x - 10.f;
	backgroundPos.y = static_cast<float>(settings.ScreenHeight) - background.getSize().y - 10.f;

	background.setPosition(backgroundPos);

	// shortcut slots
	for (size_t i = 0; i < shortcutSlots.size(); i++) {
		sf::Vector2f pos(backgroundPos.x + 3.f + (i % 12) * (iconSize + 4.f), backgroundPos.y + (i / 12) * (iconSize + 4.f) + 3.f);
		shortcutSlots[i].setPosition(pos);
		shortcutIcons[i].setPosition(pos);
		unavailableSquare[i].setPosition(pos);
		cooldownText[i].setPosition(pos.x + 2.f, pos.y + 28.f);
		chargeText[i].setPosition(pos.x + 2.f, pos.y + 2.f);
	}

	// hp bar
	//hpBarBackground.setPosition(backgroundPos.x + (background.getSize().x / 2.f) - hpBarBackground.getSize().x - 2.f, backgroundPos.y - hpBarBackground.getSize().y - 4.f);
	hpBarBackground.setPosition(settings.ScreenWidth - hpBarBackground.getSize().x - 10.f, backgroundPos.y - (hpBarBackground.getSize().y + 4.f) * 3.f);
	hpBar.setPosition(hpBarBackground.getPosition());

	// mp bar
	//mpBarBackground.setPosition(backgroundPos.x + (background.getSize().x / 2.f) + 1.f, backgroundPos.y - mpBarBackground.getSize().y - 4.f);
	mpBarBackground.setPosition(settings.ScreenWidth - mpBarBackground.getSize().x - 10.f, backgroundPos.y - (mpBarBackground.getSize().y + 4.f) * 2.f);
	mpBar.setPosition(mpBarBackground.getPosition());

	// sp bar
	//spBarBackground.setPosition(backgroundPos.x + (background.getSize().x / 2.f) + 4.f + mpBarBackground.getSize().x, backgroundPos.y - spBarBackground.getSize().y - 4.f);
	spBarBackground.setPosition(settings.ScreenWidth - spBarBackground.getSize().x - 10.f, backgroundPos.y - (spBarBackground.getSize().y + 4.f));
	spBar.setPosition(spBarBackground.getPosition());

	// buffs and debuffs
	sf::Vector2f buffPos = hpBarBackground.getPosition();

	for (size_t i = 0; i < buffBackgrounds.size(); i++) {
		float iFloat = static_cast<float>(i + 1);
		sf::Vector2f localPos(buffPos);
		localPos.x = localPos.x - 3.f - iFloat * 42.f;
		localPos.y = localPos.y - 2.f;
		buffBackgrounds[i].setPosition(localPos);
		buffIcons[i].setPosition(localPos);

		if (displayBuffDurationText[i]) {
			buffDurationText[i].setPosition(localPos.x + 1.f, localPos.y + 26.f);
		}
	}

	for (size_t i = 0; i < debuffBackgrounds.size(); i++) {
		float iFloat = static_cast<float>(i + 1);
		sf::Vector2f localPos(buffPos);
		localPos.x = localPos.x - 3.f - iFloat * 42.f;
		localPos.y = localPos.y + 40.f;
		debuffBackgrounds[i].setPosition(localPos);
		debuffIcons[i].setPosition(localPos);

		if (displayDebuffDurationText[i]) {
			debuffDurationText[i].setPosition(localPos.x + 1.f, localPos.y + 26.f);
		}
	}
}

void PlayerHUD::SetShortcut(size_t index, AbilityID id) {
	shortcuts[index].AbilityID = id;
	shortcuts[index].ItemID = static_cast<ItemID>(0);

	// set the icon
	Ability a(id, 0);
	shortcutIcons[index].setTexture(*assetManager.LoadTexture(a.GetIcon()));
	displayShortcutIcons[index] = true;
}

std::array<Shortcut, 24> PlayerHUD::GetShortcuts() {
	return shortcuts;
}

void PlayerHUD::GetDraggableAbility(sf::Vector2i location, AbilityID& id) {
	sf::Vector2f pos(static_cast<sf::Vector2f>(location));
	for (size_t i = 0; i < shortcutSlots.size(); i++) {
		if (displayShortcutIcons[i] && shortcutSlots[i].getGlobalBounds().contains(pos)) {
			if (shortcuts[i].AbilityID != static_cast<AbilityID>(0)) {
				id = shortcuts[i].AbilityID;
				shortcuts[i].AbilityID = static_cast<AbilityID>(0);
				displayShortcutIcons[i] = false;
				return;
			}
		}
	}
}

void PlayerHUD::ReleaseDraggableAbility(sf::Vector2i location, AbilityID& id) {
	sf::Vector2f pos(static_cast<sf::Vector2f>(location));
	for (size_t i = 0; i < shortcutSlots.size(); i++) {
		if (shortcutSlots[i].getGlobalBounds().contains(pos)) {
			std::swap(id, shortcuts[i].AbilityID);
			SetShortcut(i, shortcuts[i].AbilityID);
			return;
		}
	}
}