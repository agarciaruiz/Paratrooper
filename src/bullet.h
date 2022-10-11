#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include "raylib.h"
#include "helicopter.h"
#include "trooper.h"

class Bullet 
{
private:
	Vector2 _position;
	Vector2 _direction;
	float _speed;
	float _radius;
	bool _helicopterHit = false;
	bool _trooperHit = false;
	int _score = 0;

public:
	bool HelicopterHit() const{ return _helicopterHit; }
	bool TrooperHit() const{ return _trooperHit; }
	int Score() const{ return _score; }
	Vector2 Direction() const{ return _direction; }

	void Bullet::Init(Vector2 position, Vector2 direction)
	{
		_position = position;
		_direction = direction;
		_radius = 1;
		_speed = 5;
	}

	void Bullet::Update(std::vector<Helicopter*> helicopters, std::vector<Trooper*> troopers)
	{
		// if colision con helicoptero -> hit = true
		for(int i = 0; i < helicopters.size(); i++)
		{
			if (helicopters[i]->IsAlive() && CheckCollisionCircleRec(_position, _radius, helicopters[i]->Bounds()))
			{
				_helicopterHit = true;
				_score = 10;
				helicopters[i]->Destroy();
			}
		}

		for (int i = 0; i < troopers.size(); i++)
		{
			if (troopers[i]->IsAlive() && CheckCollisionCircleRec(_position, _radius, troopers[i]->Bounds()))
			{
				_trooperHit = true;
				_score = 5;
				troopers[i]->Destroy();
			}
		}

		_position.x += _direction.x * _speed;
		_position.y -= _direction.y * _speed;
	}

	bool Bullet::IsOutOfScreen()
	{
		if(_position.x >= SCR_WIDTH || _position.x <= 0 || _position.y <= 0)
		{
			return true;
		}
		return false;
	}

	void Bullet::Draw()
	{
		DrawText(".", _position.x, _position.y, 40, WHITE);
	}
};

#endif