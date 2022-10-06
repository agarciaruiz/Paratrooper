#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "screen.hpp"
#include "player.hpp"

class GameScreen : public Screen {
private:
	bool gamePaused = false;
	Player player;

	Vector2 playerPos = Vector2{ SCR_WIDTH / 2 , SCR_HEIGHT};
	float rotationSpeed = 5.0f;
	int playerLifes = PLAYER_LIFES;

public:
	void InitScreen() override 
	{
		framesCounter = 0;
		finishScreen = 0;
		player.Init(playerPos, rotationSpeed, playerLifes);
	}

	void UpdateScreen() override
	{
		if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

		// Press enter or tap to change to ENDING screen
		if (!gamePaused)
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
	}

	void DrawScreen() override
	{

		Texture2D turretTexture = player.TurretTexture();
		Rectangle turretBbox = Rectangle{0, 0, (float)turretTexture.width, (float)turretTexture.height};
		Rectangle destination = Rectangle{ SCR_WIDTH / 2, SCR_HEIGHT - (float)player.BodyTexture().height+5, (float)turretTexture.width, (float)turretTexture.height };
		Vector2 origin = Vector2{ (float)turretTexture.width / 2, (float)turretTexture.height};

		DrawTexturePro(turretTexture, turretBbox, destination, origin,player.TurretRotation(), WHITE);
		DrawTextureEx(player.BodyTexture(), player.BasePosition(), 0.0f, 1.0f, WHITE);   // Draw player

		if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);
	}

	void UnloadScreen() override {}

	void DeleteTextures()
	{
		player.DeleteTexture();
	}
};

#endif