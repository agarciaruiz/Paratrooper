#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#define REUSABLE_COPTERS 8

#include <iostream>
#include <time.h>
#include "screen.hpp"
#include "player.hpp"
#include "helicopter.h"

class GameScreen : public Screen {
private:
	bool gamePaused = false;
	Player player;
	Helicopter helicopters[REUSABLE_COPTERS];

	Vector2 playerPos = Vector2{ SCR_WIDTH / 2 , SCR_HEIGHT};
	float rotationSpeed = 5.0f;
	int playerLifes = PLAYER_LIFES;

	float timer = 0;
	float helicopterSpawnTime = 3;
	float helicopterSide = 0;
	int randIndex = 0;
	bool copterFound = false; 
	int attempts = 0;

	Texture2D leftCopterTexture = {0};
	Texture2D rightCopterTexture {0};

	void GameScreen::RotatePlayer()
	{
		int dir;
		if (IsKeyDown(KEY_A))
			dir = -1;
		else if (IsKeyDown(KEY_D))
			dir = 1;
		else
			dir = 0;
		player.Rotate(dir);
	}

	void GameScreen::SpawnHelicopters() 
	{
		timer += GetFrameTime();
		if (timer >= helicopterSpawnTime)
		{
			copterFound = false;
			FindUnusedCopter();
			helicopterSpawnTime = GetRandomValue(2, 4);
			timer = 0;
		}
	}

	void GameScreen::MoveHelicopters()
	{
		for (int i = 0; i < REUSABLE_COPTERS; i++)
		{
			if (helicopters[i].IsAlive())
			{
				helicopters[i].Move();
			}

			if (helicopters[i].IsOutOfScreen())
			{
				helicopters[i].Deactivate();
			}
		}
	}

	void GameScreen::FindUnusedCopter()
	{
		if (attempts == 2)
			for (int i = 0; i < REUSABLE_COPTERS; i++)
			{
				if (!helicopters[i].IsAlive())
				{
					helicopters[i].Spawn();
					attempts = 0;
					break;
				}
			}

		if (!copterFound)
		{
			attempts++;
			randIndex = rand() % 8;
			if (!helicopters[randIndex].IsAlive())
			{
				helicopters[randIndex].Spawn();
				copterFound = true;
			}
		}
		else
		{
			FindUnusedCopter();
		}
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

		player.Init(playerPos, rotationSpeed, playerLifes);

		for (int i = 0; i < REUSABLE_COPTERS; i++) 
		{
			float randomHeight = GetRandomValue(SCR_HEIGHT / 3, SCR_HEIGHT / 8);
			float speed = GetRandomValue(3, 4);

			if (i<4)
			{
				Vector2 spawnPos = Vector2{ 0, randomHeight };
				helicopters[i].Init(spawnPos, speed, leftCopterTexture);
			}
			else
			{
				Vector2 spawnPos = Vector2{ SCR_WIDTH, randomHeight};
				helicopters[i].Init(spawnPos, speed, rightCopterTexture);
			}
		}
	}

	void GameScreen::Update() override
	{
		if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

		// Press enter or tap to change to ENDING screen
		if (!gamePaused)
		{
			// Player Input
			RotatePlayer();
			if (IsKeyPressed(KEY_SPACE))
				player.Shoot();

			// Helicopter Spawn
			SpawnHelicopters();
			// Helicopter Move && Deactivate
			MoveHelicopters();
		}
	}

	void GameScreen::Draw() override
	{
		player.Draw();

		for (int i = 0; i < REUSABLE_COPTERS; i++) 
		{
			if (helicopters[i].IsAlive())
				helicopters[i].Draw();
		}

		if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);
	}

	void GameScreen::Unload() override 
	{
		UnloadFont(font);
		UnloadTexture(player.BodyTexture());
		UnloadTexture(player.TurretTexture());
		for (int i = 0; i < REUSABLE_COPTERS; i++)
			UnloadTexture(helicopters[i].Texture());
	}

	void GameScreen::DeleteTextures()
	{
		//player.DeleteTexture();
	}
};

#endif