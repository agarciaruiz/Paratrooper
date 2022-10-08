#ifndef TROOPER_H
#define TROOPER_H

class Trooper
{
private:
	float _speed;
	Vector2 _position;
	Texture2D _texture;
	bool _isFalling;
	bool _isGrounded;
	bool _isAlive = true;

public:
	bool IsFalling() const { return _isFalling; }
	bool IsGrounded() const { return _isGrounded; }
	bool IsAlive() const { return _isAlive; }
	Texture2D Texture() const { return _texture; }
	Vector2 Position() const { return _position; }

	void Trooper::Init(Vector2 position)
	{
		this->_position = position;
		this->_speed = 2;
		this->_texture = LoadTexture("resources/Enemies/Soldier.png");
		this->_isFalling = true;
		this->_isGrounded = false;
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
		if (_position.y < SCR_HEIGHT - _texture.height)
			_position.y += _speed;
		else 
		{
			_isFalling = false;
			_isGrounded = true;
			_position.y = SCR_HEIGHT - _texture.height;
		}
	}

	void Trooper::Draw()
	{
		DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
	}
};

#endif