#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"

class Enemy 
{
protected:
	float _speed;
	Vector2 _position;
	Texture2D _texture;
	bool _isAlive;
public:
	Vector2 Position() const{ return _position; }
	Texture2D Texture() const { return _texture; }
	bool IsAlive() const { return _isAlive; }

	virtual void Enemy::Init(Vector2 position, float speed, Texture2D texture)
	{
		this->_position = position;
		this->_speed = speed;
		this->_texture = texture;
	}

	virtual void Enemy::Spawn()
	{
		_isAlive = true;
	}

	virtual void Enemy::Move(){}

	virtual void Enemy::Destroy()
	{
		_isAlive = false;
	}

};

#endif // !ENEMY_H
