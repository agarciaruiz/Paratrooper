#include "game_manager.h"

int GameManager::LandedTroopers() const { return _landedTroopers; }

void GameManager::Init()
{
	gamePaused = false;
	gameSecs = 0;
	gameMins = 0;
	gameHours = 0;

	SetRandomSeed(time(NULL));
	helicopterSpawnTime = 3;
	timer = helicopterSpawnTime - 1;

	playerPos = Vector2{ SCR_WIDTH / 2 , SCR_HEIGHT };
	player.Init(playerPos);

	trooperTimer = 0;
	_landedTroopers = 0;
}

void GameManager::Update()
{
	if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

	// Press enter or tap to change to ENDING screen
	if (!gamePaused)
	{
		UpdateTime();
		player.Update(helicopters, troopers);
		// Helicopter spawn, move and destroy
		HelicopterRoutine();
		// Update && Destroy trooper
		TrooperRoutine();
	}
}

void GameManager::Draw()
{
	DrawUI();
	player.Draw();
	DrawHelicopters();
	DrawTroopers();
}

Helicopter* GameManager::SpawnHelicopter()
{
	Helicopter* helicopter = new Helicopter();
	helicopter->Init();
	return helicopter;
}

void GameManager::SpawnTrooper(Helicopter* helicopter)
{
	Trooper* trooper = new Trooper();
	trooper->Init(helicopter->Position());
	troopers.push_back(trooper);
	helicopter->DropTrooper();
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

void GameManager::HelicopterRoutine()
{
	timer += GetFrameTime();
	if (timer >= helicopterSpawnTime)
	{
		helicopters.push_back(SpawnHelicopter());
		helicopterSpawnTime = GetRandomValue(3, 5);
		timer = 0;
	}
	MoveHelicopters();
}

void GameManager::MoveHelicopters()
{
	for (int i = 0; i < helicopters.size(); i++)
	{
		if (helicopters[i]->IsAlive() || !helicopters[i]->IsOutOfScreen())
		{
			if (helicopters[i]->HasTrooper() && helicopters[i]->TimeOut())
			{
				SpawnTrooper(helicopters[i]);
			}
			helicopters[i]->Move();
		}
		else
		{
			if (!helicopters[i]->ReloadTexture())
			{
				delete(helicopters[i]);
				helicopters.erase(std::remove(helicopters.begin(), helicopters.end(), helicopters[i]), helicopters.end());
			}
		}
	}
}

void GameManager::TrooperRoutine()
{
	for (int i = 0; i < troopers.size(); i++)
	{
		if (troopers[i]->IsAlive())
		{
			troopers[i]->Update();
			if (troopers[i]->IsGrounded() && !troopers[i]->previouslyGrounded)
			{
				_landedTroopers++;
				troopers[i]->PreviouslyGrounded(true);
			}
		}
		else
		{
			if (troopers[i]->ReloadTexture())
			{
				delete(troopers[i]);
				troopers.erase(std::remove(troopers.begin(), troopers.end(), troopers[i]), troopers.end());
			}
		}
	}
}

void GameManager::DrawHelicopters()
{
	for (int i = 0; i < helicopters.size(); i++)
	{
		helicopters[i]->Draw();
	}
}

void GameManager::DrawTroopers()
{
	for (int i = 0; i < troopers.size(); i++)
	{
		troopers[i]->Draw();
	}
}

void GameManager::DrawUI()
{
	if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);

	char* time = (char*)TextFormat("TIME: %ih : %im : %is", gameHours, gameMins, (int)gameSecs);
	DrawText(time, 20, 10, 20, GRAY);

	char* numLanded = (char*)TextFormat("LANDED TROOPERS: %i", _landedTroopers);
	DrawText(numLanded, 20, 30, 20, GRAY);

	char* score = (char*)TextFormat("SCORE: %i", player.Score());
	DrawText(score, 20, 50, 20, GRAY);
}

void GameManager::ResetGame() 
{
	gameSecs = 0;
	gameMins = 0;
	gameHours = 0;

	_landedTroopers = 0;
	player.Reset();

	for (int i = 0; i < helicopters.size(); i++)
	{
		helicopters[i]->UnloadTextures();
		delete(helicopters[i]);
	}
	helicopters.clear();

	for (int i = 0; i < troopers.size(); i++)
	{
		troopers[i]->UnloadTextures();
		delete(troopers[i]);
	}
	troopers.clear();
}