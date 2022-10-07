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
	bool IsAlive() const { return _isAlive; }

	virtual void Init(Vector2 position, float speed, Texture2D texture)
	{
		this->_position = position;
		this->_speed = speed;
		this->_texture = texture;
	}

	virtual void Spawn()
	{
		_isAlive = true;
	}

	virtual void Move(){}

	virtual void Destroy()
	{
		_isAlive = false;
	}

};

#endif // !ENEMY_H
