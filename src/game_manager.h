#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <time.h>
#include "raylib.h"
#include "player.hpp"
#include "bullet.h"
#include "enemy_manager.h"

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

	EnemyManager _enemyManager{};

	// Private methods
	void GameManager::UpdateTime();
	void GameManager::DrawUI();

public:
	EnemyManager EnemyManager() const;

	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::ResetGame();
};

#endif // !GAME_MANAGER_H
