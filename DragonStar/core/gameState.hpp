// ================================================================
//
// gameState.hpp
// 
// Enum used to tell which scene should be updated.
//
// ================================================================

#pragma once

enum class GameState {
	UnknownState = 0,
	MainMenu,
	CharacterCreation,
	Dungeon,
	Victory,
	Defeat
};