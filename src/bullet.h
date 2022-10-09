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
	bool _hit;

public:
	bool Hit() const{ return _hit; }
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
				_hit = true;
				helicopters[i]->Destroy();
			}
		}

		for (int i = 0; i < troopers.size(); i++)
		{
			if (troopers[i]->IsAlive() && CheckCollisionCircleRec(_position, _radius, troopers[i]->Bounds()))
			{
				_hit = true;
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