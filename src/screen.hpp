#ifndef SCREENS_H
#define SCREENS_H

#define SCR_WIDTH 800
#define SCR_HEIGHT 450

#include "raylib.h"

class Screen {
protected:
	int framesCounter = 0;
	int finishScreen = 0;
	Font font = { 0 };

public:
	int FinishScreen() const { return finishScreen; }

	virtual void Screen::Init()
	{    
		framesCounter = 0;
		finishScreen = 0;
		font = LoadFont("resources/mecha.png");
	}

	virtual void Screen::Update(){}
	virtual void Screen::Draw(){}

	virtual void Screen::Unload()
	{
		UnloadFont(font);
	}
};
#endif // SCREENS_H