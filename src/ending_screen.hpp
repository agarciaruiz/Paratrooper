#ifndef ENDINGSCREEN_H
#define ENDING_H
#include "screen.hpp"

class EndingScreen : public Screen {
private:
public:
	void EndingScreen::Update() override 
	{
		framesCounter++;

		// Press enter or tap to return to TITLE screen
		if (IsKeyPressed(KEY_ENTER))
			finishScreen = 2;

		if (IsKeyPressed(KEY_O))
			finishScreen = 3;
	}

	void EndingScreen::Draw() override
	{
		DrawText("YOU LOOSE :(", SCR_WIDTH / 2 - MeasureText("YOU LOOSE :(", 50) / 2, GetScreenHeight() / 2, 50, PINK);

		if ((framesCounter / 30) % 2 == 0) 
		{
			DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 + 80, 20, GRAY);
			DrawText("PRESS [0] for INSTRUCTIONS", GetScreenWidth() / 2 - MeasureText("PRESS [0] for INSTRUCTIONS", 20) / 2, GetScreenHeight() / 2 + 100, 20, DARKGRAY);
		}
	}
};

#endif