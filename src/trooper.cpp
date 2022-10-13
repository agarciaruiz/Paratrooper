#include "trooper.h"

Rectangle Trooper::GetBounds()
{
	return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
}

bool Trooper::IsFalling() const { return _isFalling; }
bool Trooper::IsGrounded() const { return _isGrounded; }
void Trooper::PreviouslyGrounded(bool value) { previouslyGrounded = value; }
bool Trooper::IsAlive() const { return _isAlive; }
Texture2D Trooper::Texture() const { return _texture; }
Vector2 Trooper::Position() const { return _position; }
Rectangle Trooper::Bounds() const { return _bounds; }

void Trooper::Init(Vector2 position)
{
	this->_position = position;
	this->_texture = LoadTexture("resources/Enemies/Soldier.png");
	this->_bounds = GetBounds();
	_speed = 2;
	_isFalling = true;
	_isGrounded = false;
	_isAlive = true;
	_reloadTextureTimer = 0;
	previouslyGrounded = false;
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
	if(_isAlive)
		DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
}

void Trooper::Destroy()
{
	_texture = LoadTexture("resources/Enemies/Dead.png");
	WaitTime(0.5f);
	_isAlive = false;
}

void Trooper::UnloadTextures()
{
	UnloadTexture(_texture);
}