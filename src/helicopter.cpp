#include "helicopter.h"

Rectangle Helicopter::GetBounds()
{
	return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
}

void Helicopter::RecenterTexture()
{
	_position.x += _bounds.width / 2 - _texture.width / 2;
	_position.x += _bounds.height / 2 - _texture.height / 2;
}

Rectangle Helicopter::Bounds() const { return _bounds; }
Vector2 Helicopter::Position() const { return _position; }
bool Helicopter::IsAlive() const { return _isAlive; }
bool Helicopter::HasTrooper() const { return _hasTrooper; }
bool Helicopter::TimeOut() const { return _timeOut; };
bool Helicopter::ReloadTexture() const { return _reloadTexture; };

void Helicopter::Init(Vector2 position, float speed, Texture2D texture)
{
	this->_position = position;
	this->_speed = speed;
	this->_texture = texture;
	_spawnTimeout = GetRandomValue(1, 3);

	if (position.x == 0)
		_leftSided = true;
	else
		_leftSided = false;

	_isAlive = true;
	_bounds = GetBounds();
	_reloadTextureTimer = 0;
	_reloadTexture = false;

	_spawnTimer = 0;
	_timeOut = false;
	_hasTrooper = true;

	_explosion = LoadSound("resources/Music/explosion.wav");
}

void Helicopter::Move()
{
	if (_isAlive)
	{
		// If is left side, moove right
		if (_leftSided)
			_position.x += _speed;
		else
			_position.x -= _speed;

		// Update bounds
		_bounds = GetBounds();

		// Trooper routine
		_spawnTimer += GetFrameTime();
		if (_hasTrooper && _spawnTimer >= _spawnTimeout)
		{
			_timeOut = true;
		}
	}
	else
	{
		_reloadTextureTimer += GetFrameTime();
		if (_reloadTextureTimer >= 0.5f)
			_reloadTexture = true;
	}
}

void Helicopter::DropTrooper()
{
	_hasTrooper = false;
}

void Helicopter::Deactivate()
{
	_isAlive = false;
}

bool Helicopter::IsOutOfScreen()
{
	if (_leftSided && _position.x >= SCR_WIDTH)
	{
		return true;
	}
	else if (!_leftSided && _position.x <= 0)
	{
		return true;
	}
	return false;
}

void Helicopter::Draw()
{
	if (_reloadTexture) return;
	DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
}

void Helicopter::Destroy()
{
	PlaySound(_explosion);
	_texture = LoadTexture("resources/Enemies/Dead.png");
	RecenterTexture();
	Deactivate();
}

void Helicopter::UnloadTextures()
{
	UnloadTexture(_texture);
}

