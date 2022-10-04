#ifndef OPTIONSCREEN_H
#define OPTIONSCREEN_H
#include "screen.hpp"
#include <string>

class OptionsScreen : public Screen {
private:
	char* instructions1;
	char* instructions2;
	char* instructions3;

	char* instructions4;
	char* instructions5;
	char* instructions6;

	char* instructions7;
public:
	void InitScreen() override 
	{
		instructions1 = "Do not allow enemy paratroopers to land";
		instructions2 = "on either side of your gun baseself. If seven";
		instructions3 = "paratroopers land on your base you loose";
		instructions4 = "Press space to shoot";
		instructions5 = "Press [A] to move the turret counterclockwise";
		instructions6 = "Press [D] to move the turret clockwise";
		instructions7 = "Press [O] to return to Title Screen";

		framesCounter = 0;
		finishScreen = 0;
	}
	void UpdateScreen() override 
	{
		framesCounter++;

		if (IsKeyPressed(KEY_O))
			finishScreen = 2;
	}

	void DrawScreen() override 
	{
		DrawText(instructions1, GetScreenWidth() / 2 - MeasureText(instructions1, 20) / 2, GetScreenHeight() / 4 - 20, 20, DARKGRAY);
		DrawText(instructions2, GetScreenWidth() / 2 - MeasureText(instructions2, 20) / 2, GetScreenHeight() / 4, 20, DARKGRAY);
		DrawText(instructions3, GetScreenWidth() / 2 - MeasureText(instructions3, 20) / 2, GetScreenHeight() / 4 + 20, 20, DARKGRAY);

		DrawText(instructions4, GetScreenWidth() / 2 - MeasureText(instructions4, 20) / 2, GetScreenHeight() / 4 + 80, 20, DARKGRAY);
		DrawText(instructions5, GetScreenWidth() / 2 - MeasureText(instructions5, 20) / 2, GetScreenHeight() / 4 + 100, 20, DARKGRAY);
		DrawText(instructions6, GetScreenWidth() / 2 - MeasureText(instructions6, 20) / 2, GetScreenHeight() / 4 + 120, 20, DARKGRAY);

		if ((framesCounter / 30) % 2 == 0)
			DrawText(instructions7, GetScreenWidth() / 2 - MeasureText(instructions7, 20) / 2, GetScreenHeight() / 4 + 160, 20, DARKGRAY);
	}

	void UnloadScreen() override {}
};

#endif
