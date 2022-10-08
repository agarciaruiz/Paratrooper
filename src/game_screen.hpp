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

class GameScreen : public Screen {
private:
	bool gamePaused = false;
	Player player;
	std::vector<Helicopter*> helicopters = {};

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

	float randomSide()
	{
		srand(time(NULL));
		int r = rand() % 2;
		if (r == 0)
			return 0;
		else
			return SCR_WIDTH;
	}

	Texture2D GetTextureFromSide(float side)
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

	void GameScreen::MoveHelicopter(Helicopter *helicopter)
	{
		helicopter->Move();
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
	}

	void GameScreen::Update() override
	{
		if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

		// Press enter or tap to change to ENDING screen
		if (!gamePaused)
		{
			player.Update(helicopters);

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
				if (!helicopters[i]->IsOutOfScreen())
					helicopters[i]->Move();
				else
				{
					delete(helicopters[i]);
					helicopters.erase(std::remove(helicopters.begin(), helicopters.end(), helicopters[i]), helicopters.end());
				}
			}
		}
	}

	void GameScreen::Draw() override
	{
		player.Draw();

		for (int i = 0; i < helicopters.size(); i++)
		{
			helicopters[i]->Draw();
		}

		if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);
	}

	void GameScreen::Unload() override 
	{
		UnloadFont(font);
		UnloadTexture(player.BodyTexture());
		UnloadTexture(player.TurretTexture());
	}

	void GameScreen::DeleteTextures()
	{
		//player.DeleteTexture();
	}
};

#endif