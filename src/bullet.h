#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

class Bullet 
{
private:
	Vector2 _position;
	Vector2 _direction;
	float _speed;
	bool _hit;

public:
	bool Hit() const{ return _hit; }
	Vector2 Direction() const{ return _direction; }

	void Bullet::Init(Vector2 position, Vector2 direction)
	{
		_position = position;
		_direction = direction;
		_speed = 3;
	}

	void Bullet::Update()
	{
		_position.x += _direction.x * _speed;
		_position.y += _direction.y * _speed;
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