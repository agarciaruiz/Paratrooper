#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#define REUSABLE_COPTERS 8

#include <iostream>
#include <time.h>
#include <vector>
#include "screen.hpp"
#include "player.hpp"
#include "helicopter.h"
#include "bullet.h"
#include "trooper.h"

class GameScreen : public Screen {
private:
	// Game settings
	bool gamePaused;
	float gameSecs;
	int gameMins;
	int gameHours;

	// Player settings
	Player player;
	Vector2 playerPos;

	// Helicopter settings
	std::vector<Helicopter*> helicopters {};
	Texture2D leftCopterTexture {};
	Texture2D rightCopterTexture {};
	float timer;
	float helicopterSpawnTime;

	// Trooper settings
	std::vector<Trooper*> troopers {};
	float trooperTimer;
	int landedTroopers;

	// Private methods
	void GameScreen::ResetScreen();
	float GameScreen::randomSide();
	Texture2D GameScreen::GetTextureFromSide(float side);
	Helicopter* GameScreen::SpawnHelicopter();
	void GameScreen::SpawnTrooper(Helicopter* helicopter);

public:
	void GameScreen::Init() override;
	void GameScreen::Update() override;
	void GameScreen::Draw() override;
	void GameScreen::Unload() override;
};

#endif