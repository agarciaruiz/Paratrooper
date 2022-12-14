#include "game_screen.hpp"

// Private methods
void GameScreen::ResetScreen()
{
	_gameManager.ResetGame();
}

void GameScreen::Init()
{
	framesCounter = 0;
	finishScreen = 0;
	_gameManager.Init();
}

void GameScreen::Update()
{
	_gameManager.Update();
	// Game end condition
	if (_gameManager.EnemyManager().LandedTroopers() == 7)
			finishScreen = 5;
}

void GameScreen::Draw()
{
	_gameManager.Draw();
}

void GameScreen::Unload()
{
	ResetScreen();
}