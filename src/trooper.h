#ifndef TROOPER_H
#define TROOPER_H

class Trooper
{
private:
	float _speed;
	Vector2 _position;
	Texture2D _texture;
	Rectangle _bounds;
	bool _isFalling;
	bool _isGrounded;
	bool _isAlive = true;
	float _reloadTextureTimer = 0;
	bool _reloadTexture = false;

	Rectangle Trooper::GetBounds()
	{
		return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height };
	}

public:
	bool IsFalling() const { return _isFalling; }
	bool IsGrounded() const { return _isGrounded; }
	bool IsAlive() const { return _isAlive; }
	Texture2D Texture() const { return _texture; }
	Vector2 Position() const { return _position; }
	Rectangle Bounds() const { return _bounds; }

	void Trooper::Init(Vector2 position)
	{
		this->_position = position;
		this->_speed = 2;
		this->_texture = LoadTexture("resources/Enemies/Soldier.png");
		this->_isFalling = true;
		this->_isGrounded = false;
		this->_bounds = GetBounds();
	}

	void Trooper::FollowHelicopter(Vector2 position)
	{
		this->_position = position;
	}

	void Trooper::Update() 
	{
		if(_isAlive)
			Fall();
	}

	void Trooper::Fall() 
	{
		if (_isAlive)
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
		else
		{
			_reloadTextureTimer += GetFrameTime();
			if (_reloadTextureTimer >= 0.5f)
				_reloadTexture = true;
		}
	}

	void Trooper::Draw()
	{
		if (_reloadTexture) return;
		DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
	}

	void Trooper::Destroy()
	{
		_texture = LoadTexture("resources/Enemies/Dead.png");
		_isAlive = false;
	}
};

#endif