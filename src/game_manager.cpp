#include "game_manager.h"

EnemyManager GameManager::EnemyManager() const { return _enemyManager; }

void GameManager::Init()
{
	gamePaused = false;
	gameSecs = 0;
	gameMins = 0;
	gameHours = 0;

	playerPos = Vector2{ SCR_WIDTH / 2 , SCR_HEIGHT };
	player.Init(playerPos);
	_enemyManager.Init();
}

void GameManager::Update()
{
	if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

	// Press enter or tap to change to ENDING screen
	if (!gamePaused)
	{
		UpdateTime();
		player.Update(_enemyManager.Helicopters(), _enemyManager.Troopers());
		_enemyManager.Update();
	}
}

void GameManager::Draw()
{
	DrawUI();
	player.Draw();
	_enemyManager.Draw();
}

void GameManager::UpdateTime()
{
	if (gameMins >= 60)
	{
		gameHours++;
		gameMins = 0;
	}
	if (gameSecs >= 60)
	{
		gameMins++;
		gameSecs = 0;
	}
	gameSecs += GetFrameTime();
}

void GameManager::DrawUI()
{
	if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);

	char* time = (char*)TextFormat("TIME: %ih : %im : %is", gameHours, gameMins, (int)gameSecs);
	DrawText(time, 20, 10, 20, GRAY);

	char* numLanded = (char*)TextFormat("LANDED TROOPERS: %i", _enemyManager.LandedTroopers());
	DrawText(numLanded, 20, 30, 20, GRAY);

	char* score = (char*)TextFormat("SCORE: %i", player.Score());
	DrawText(score, 20, 50, 20, GRAY);
}

void GameManager::ResetGame() 
{
	gameSecs = 0;
	gameMins = 0;
	gameHours = 0;

	player.Reset();
	_enemyManager.Reset();
}