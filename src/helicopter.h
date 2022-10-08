#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "trooper.h"

class Helicopter
{
private:
	// Helicopter vars
	Rectangle _bounds;
	Vector2 _position;
	Texture2D _texture;
	float _speed;
	bool _leftSided = false;
	float _reloadTextureTimer = 0;
	bool _reloadTexture = false;
	bool _isAlive;

	// Trooper vars
	float _spawnTimeout = 0;
	float _spawnTimer = 0;

	Rectangle Helicopter::GetBounds()
	{
		return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
	}

	void RecenterTexture()
	{
		_position.x += _bounds.width/2 - _texture.width/2;
		_position.x += _bounds.height/2 - _texture.height/2;
	}

	void SpawnTrooper()
	{
		_spawnTimer += GetFrameTime();
		Vector2 newPos;
		if (_spawnTimer >= _spawnTimeout)
		{
			//_trooper->Spawn();
			_spawnTimer = 0;
			_spawnTimeout = GetRandomValue(1, 3);
		}
	}

public:
	Rectangle Bounds() const { return _bounds; }
	Vector2 Position() const { return _position; }
	bool IsAlive() const { return _isAlive; }
	bool _hasTrooper = true;
	float SpawnTimeOut() const { return _spawnTimeout; };
	//Trooper* _trooper = new Trooper();

	void Helicopter::Init(Vector2 position, float speed, Texture2D texture)
	{
		this->_position = position;
		this->_speed = speed;
		this->_texture = texture;
		//_trooper->Init(_position);
		_spawnTimeout = GetRandomValue(1, 3);
		if (position.x == 0)
			_leftSided = true;
		_isAlive = true;
		_bounds = GetBounds();
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
			/*_spawnTimer += GetFrameTime();
			if (_hasTrooper && _spawnTimer >= _spawnTimeout)
			{
				_hasTrooper = false;
				_spawnTimer = 0;
				_spawnTimeout = GetRandomValue(1, 3);
			}*/
		}
		else
		{
			_reloadTextureTimer += GetFrameTime();
			if (_reloadTextureTimer >= 0.5f)
				_reloadTexture = true;
		}
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
		_texture = LoadTexture("resources/Enemies/Dead.png");
		RecenterTexture();
		Deactivate();
	}
};

#endif // !HELICOPTER_H

