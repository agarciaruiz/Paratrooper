#ifndef TROOPER_H
#define TROOPER_H
#include "raylib.h"

class Trooper
{
private:
	float _speed = 2;
	Vector2 _position;
	Texture2D _texture;
	Rectangle _bounds;
	bool _isFalling = true;
	bool _isGrounded = false;
	bool _isAlive = true;
	float _reloadTextureTimer = 0;

	Rectangle Trooper::GetBounds()
	{
		return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
	}

public:
	bool _previouslyGrounded = false;
	bool IsFalling() const { return _isFalling; }
	bool IsGrounded() const { return _isGrounded; }
	void PreviouslyGrounded(bool value) { _previouslyGrounded = value; }
	bool IsAlive() const { return _isAlive; }
	Texture2D Texture() const { return _texture; }
	Vector2 Position() const { return _position; }
	Rectangle Bounds() const { return _bounds; }

	void Trooper::Init(Vector2 position)
	{
		this->_position = position;
		this->_texture = LoadTexture("resources/Enemies/Soldier.png");
		this->_bounds = GetBounds();
	}

	void Trooper::FollowHelicopter(Vector2 position)
	{
		this->_position = position;
	}

	void Trooper::Update() 
	{
		Fall();
	}

	void Trooper::Fall() 
	{
		if (_position.y < SCR_HEIGHT - _texture.height)
		{
			_position.y += _speed;
			_bounds = GetBounds();
		}
		else
		{
			_isFalling = false;
			_isGrounded = true;
			_position.y = SCR_HEIGHT - _texture.height;
		}
	}

	bool Trooper::ReloadTexture()
	{
		_reloadTextureTimer += GetFrameTime();
		if (_reloadTextureTimer >= 0.5f)
			return true;
		return false;
	}

	void Trooper::Draw()
	{
		DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
	}

	void Trooper::Destroy()
	{
		_texture = LoadTexture("resources/Enemies/Dead.png");
		_isAlive = false;
	}
};

#endif