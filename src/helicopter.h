#ifndef HELICOPTER_H
#define HELICOPTER_H

class Helicopter
{
private:
	// Helicopter vars
	Rectangle _bounds;
	Vector2 _position;
	Texture2D _texture;
	float _speed;
	bool _leftSided = false;
	bool _isAlive;
	int _score = 10;

	float _reloadTextureTimer = 0;
	bool _reloadTexture = false;

	// Trooper vars
	float _spawnTimeout;
	float _spawnTimer = 0;
	bool _timeOut = false;
	bool _hasTrooper = true;

	Rectangle Helicopter::GetBounds()
	{
		return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
	}

	void RecenterTexture()
	{
		_position.x += _bounds.width/2 - _texture.width/2;
		_position.x += _bounds.height/2 - _texture.height/2;
	}

public:
	Rectangle Bounds() const { return _bounds; }
	Vector2 Position() const { return _position; }
	bool IsAlive() const { return _isAlive; }
	bool HasTrooper() const { return _hasTrooper; }
	bool TimeOut() const { return _timeOut; };
	bool ReloadTexture() const { return _reloadTexture; };
	int Score() const { return _score; };

	void Helicopter::Init(Vector2 position, float speed, Texture2D texture)
	{
		this->_position = position;
		this->_speed = speed;
		this->_texture = texture;
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
		_texture = LoadTexture("resources/Enemies/Dead.png");
		RecenterTexture();
		Deactivate();
	}

	void Helicopter::UnloadTextures()
	{
		UnloadTexture(_texture);
	}
};

#endif // !HELICOPTER_H

