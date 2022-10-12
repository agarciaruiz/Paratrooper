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
	float timer;
	float helicopterSpawnTime;

	// Trooper settings
	std::vector<Trooper*> troopers{};
	float trooperTimer;
	int _landedTroopers;

	// Private methods
	Helicopter* GameManager::SpawnHelicopter();
	void GameManager::SpawnTrooper(Helicopter* helicopter);
	void GameManager::UpdateTime();
	void GameManager::HelicopterRoutine();
	void GameManager::MoveHelicopters();
	void GameManager::TrooperRoutine();
	void GameManager::DrawHelicopters();
	void GameManager::DrawTroopers();
	void GameManager::DrawUI();

public:
	int LandedTroopers() const;

	void GameManager::Init();
	void GameManager::Update();
	void GameManager::Draw();
	void GameManager::ResetGame();
};

#endif // !GAME_MANAGER_H
