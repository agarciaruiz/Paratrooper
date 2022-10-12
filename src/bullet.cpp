#include "bullet.h"

bool Bullet::HelicopterHit() const { return _helicopterHit; }
bool Bullet::TrooperHit() const { return _trooperHit; }
Vector2 Bullet::Direction() const { return _direction; }

void Bullet::Init(Vector2 position, Vector2 direction)
{
	_position = position;
	_direction = direction;
	_radius = 1;
	_speed = 5;
	_helicopterHit = false;
	_trooperHit = false;
}

void Bullet::Update(std::vector<Helicopter*> helicopters, std::vector<Trooper*> troopers)
{
	// if colision con helicoptero -> hit = true
	for (int i = 0; i < helicopters.size(); i++)
	{
		if (helicopters[i]->IsAlive() && CheckCollisionCircleRec(_position, _radius, helicopters[i]->Bounds()))
		{
			_helicopterHit = true;
			helicopters[i]->Destroy();
		}
	}

	for (int i = 0; i < troopers.size(); i++)
	{
		if (troopers[i]->IsAlive() && CheckCollisionCircleRec(_position, _radius, troopers[i]->Bounds()))
		{
			_trooperHit = true;
			troopers[i]->Destroy();
		}
	}

	_position.x += _direction.x * _speed;
	_position.y -= _direction.y * _speed;
}

bool Bullet::IsOutOfScreen()
{
	if (_position.x >= SCR_WIDTH || _position.x <= 0 || _position.y <= 0)
	{
		return true;
	}
	return false;
}

void Bullet::Draw()
{
	DrawText(".", _position.x, _position.y, 40, WHITE);
}