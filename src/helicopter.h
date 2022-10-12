#ifndef HELICOPTER_H
#define HELICOPTER_H
#include <time.h>
#include <stdlib.h>
#include <list>
#include "global.h"
#include "raylib.h"

class Helicopter
{
private:
	// Helicopter vars
	Rectangle _bounds;
	Vector2 _position;
	Texture2D _texture;
	Texture2D _leftCopterTexture;
	Texture2D _rightCopterTexture;
	float _speed;
	bool _leftSided;
	bool _isAlive;
	Sound _explosion;

	float _reloadTextureTimer;
	bool _reloadTexture;

	// Trooper vars
	float _spawnTimeout;
	float _spawnTimer;
	bool _timeOut;
	bool _hasTrooper;

	Rectangle Helicopter::GetBounds();
	void Helicopter::RecenterTexture();
	float Helicopter::RandomSide();
	Texture2D Helicopter::GetTextureFromSide(float side);
	Vector2 Helicopter::StartingPos();
	void Helicopter::SetSide();

public:
	Rectangle Helicopter::Bounds() const;
	Vector2 Helicopter::Position() const;
	bool Helicopter::IsAlive() const;
	bool Helicopter::HasTrooper() const;
	bool Helicopter::TimeOut() const;
	bool Helicopter::ReloadTexture() const;

	void Helicopter::Init();
	void Helicopter::Move();
	void Helicopter::DropTrooper();
	void Helicopter::Deactivate();
	bool Helicopter::IsOutOfScreen();
	void Helicopter::Draw();
	void Helicopter::Destroy();
	void Helicopter::UnloadTextures();
};

class HelicopterPool 
{
private:
	std::list<Helicopter*> helicopters{};
public:
	Helicopter* HelicopterPool::GetItem()
	{
		if(helicopters.empty())
		{
			Helicopter* helicopter = new Helicopter();
			helicopter->Init();
			return helicopter;
		}
		else
		{
			Helicopter* helicopter = helicopters.front();
			helicopters.pop_front();
			return helicopter;
		}
	}

	void HelicopterPool::ReturnItem(Helicopter* helicopter)
	{
		helicopters.push_back(helicopter);
	}
};

#endif // !HELICOPTER_H

