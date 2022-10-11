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
	bool gamePaused = false;
	float gameSecs = 0;
	int gameMins = 0;
	int gameHours = 0;

	// Player settings
	Player player;
	Vector2 playerPos = Vector2{ SCR_WIDTH / 2 , SCR_HEIGHT};

	// Helicopter settings
	std::vector<Helicopter*> helicopters = {};
	Texture2D leftCopterTexture = {0};
	Texture2D rightCopterTexture {0};
	float timer = 0;
	float helicopterSpawnTime = 3;

	// Trooper settings
	std::vector<Trooper*> troopers {};
	float trooperTimer = 0;
	int landedTroopers = 0;

	// Private methods
	void GameScreen::ResetScreen()
	{
		gameSecs = 0;
		gameMins = 0;
		gameHours = 0;
		UnloadFont(font);

		landedTroopers = 0;
		player.Reset();

		for(int i = 0; i < helicopters.size(); i++) 
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

	float GameScreen::randomSide()
	{
		srand(time(NULL));
		int r = rand() % 2;
		if (r == 0)
			return 0;
		else
			return SCR_WIDTH;
	}

	Texture2D GameScreen::GetTextureFromSide(float side)
	{
		if (side == 0)
			return leftCopterTexture;
		else
			return rightCopterTexture;
	}

	Helicopter* GameScreen::SpawnHelicopter() 
	{
		Helicopter *helicopter = new Helicopter();

		float randomHeight = GetRandomValue(SCR_HEIGHT / 3, SCR_HEIGHT / 8);
		float speed = GetRandomValue(3, 4);
		Vector2 spawnPos = Vector2{ randomSide(), randomHeight };
		
		helicopter->Init(spawnPos, speed, GetTextureFromSide(spawnPos.x));

		return helicopter;
	}

	void GameScreen::SpawnTrooper(Helicopter* helicopter)
	{
		Trooper* trooper = new Trooper();
		trooper->Init(helicopter->Position());
		troopers.push_back(trooper);
		helicopter->DropTrooper();
	}

public:
	void GameScreen::Init() override 
	{
		SetRandomSeed(time(NULL));
		framesCounter = 0;
		finishScreen = 0;
		timer = helicopterSpawnTime - 1;

		leftCopterTexture = LoadTexture("resources/Enemies/Helicopter_Left.png");
		rightCopterTexture = LoadTexture("resources/Enemies/Helicopter_Right.png");

		player.Init(playerPos);
	}

	void GameScreen::Update() override
	{
		if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

		// Press enter or tap to change to ENDING screen
		if (!gamePaused)
		{
			if(gameMins >= 60)
			{
				gameHours++;
				gameMins = 0;
			}
			if(gameSecs >= 60)
			{
				gameMins++;
				gameSecs = 0;
			}
			gameSecs += GetFrameTime();
				
			player.Update(helicopters, troopers);

			// Helicopter Spawn
			timer += GetFrameTime();
			if (timer >= helicopterSpawnTime)
			{
				helicopters.push_back(SpawnHelicopter());
				helicopterSpawnTime = GetRandomValue(3, 5);
				timer = 0;
			}

			// Helicopter Move && Delete
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
					if(!helicopters[i]->ReloadTexture())
					{
						delete(helicopters[i]);
						helicopters.erase(std::remove(helicopters.begin(), helicopters.end(), helicopters[i]), helicopters.end());
					}
				}
			}

			// Update && Destroy trooper
			for (int i = 0; i < troopers.size(); i++)
			{
				if(troopers[i]->IsAlive())
				{
					troopers[i]->Update();
					if (troopers[i]->IsGrounded() && !troopers[i]->_previouslyGrounded)
					{
						landedTroopers++;
						troopers[i]->PreviouslyGrounded(true);
					}
				}
				else
				{
					if (troopers[i]->ReloadTexture()) 
					{
						player.SetScore(troopers[i]->Score());
						delete(troopers[i]);
						troopers.erase(std::remove(troopers.begin(), troopers.end(), troopers[i]), troopers.end());
					}
				}
			}

			// Game end condition
			if (landedTroopers == 7)
				finishScreen = 5;
		}
	}

	void GameScreen::Draw() override
	{
		char* time = (char*)TextFormat("TIME: %ih : %im : %is", gameHours, gameMins, (int)gameSecs);
		DrawText(time, 20, 10, 20, GRAY);

		char* numLanded = (char*)TextFormat("LANDED TROOPERS: %i", landedTroopers);
		DrawText(numLanded, 20, 30, 20, GRAY);

		char* score = (char*)TextFormat("SCORE: %i", player.Score());
		DrawText(score, 20, 50, 20, GRAY);

		player.Draw();

		for (int i = 0; i < helicopters.size(); i++)
		{
			helicopters[i]->Draw();
		}

		for (int i = 0; i < troopers.size(); i++)
		{
			troopers[i]->Draw();
		}

		if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);
	}

	void GameScreen::Unload() override 
	{
		ResetScreen();
	}
};

#endif