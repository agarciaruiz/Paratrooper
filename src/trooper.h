#ifndef TROOPER_H
#define TROOPER_H
#include "raylib.h"

class Trooper
{
private:
	float _speed;
	Vector2 _position;
	Texture2D _texture;
	bool _isFalling;
	bool _isGrounded;

public:
	bool IsFalling() const { return _isFalling; }
	bool IsGrounded() const { return _isGrounded; }
	Texture2D Texture() const { return _texture; }
	Vector2 Position() const { return _position; }

	void Trooper::Init(Vector2 position)
	{
		this->_position = position;
		this->_speed = 3;
		this->_texture = LoadTexture("resources/Enemies/Soldier.png");
		this->_isFalling = false;
		this->_isGrounded = false;
	}

	void Trooper::FollowHelicopter(Vector2 position)
	{
		this->_position = position;
	}

	void Trooper::Fall() 
	{
		if (_position.y < SCR_HEIGHT)
			_position.y += _speed;
		else 
		{
			_isFalling = false;
			_isGrounded = true;
			_position.y = SCR_HEIGHT;
		}
	}

	void Trooper::Spawn()
	{
		_isFalling = true;
	}
};

#endif