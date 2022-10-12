#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <time.h>
#include <vector>
#include "raylib.h"
#include "player.hpp"
#include "helicopter.h"
#include "bullet.h"
#include "trooper.h"

class GameManager {
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
	std::vector<Helicopter*> helicopters{};
	Texture2D leftCopterTexture{};
	Texture2D rightCopterTexture{};
	float timer;
	float helicopterSpawnTime;

	// Trooper settings
	std::vector<Trooper*> troopers{};
	float trooperTimer;
	int _landedTroopers;

	// Private methods
	float GameManager::randomSide();
	Texture2D GameManager::GetTextureFromSide(float side);
	Helicopter* GameManager::SpawnHelicopter();
	void GameManager::SpawnTrooper(Helicopter* helicopter);

public:
	int LandedTroopers() const;

	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::ResetGame();
};

#endif // !GAME_MANAGER_H
