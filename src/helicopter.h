#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "enemy.h"
#include "trooper.h"

class Helicopter : public Enemy 
{
private:
	Rectangle _bounds;
	bool _isLeftSide = false;
	//Trooper _trooper;
	float _timer = 0;
	float _dropTime = 0;

	Rectangle Helicopter::GetBounds()
	{
		return Rectangle{ _position.x, _position.y, (float)_texture.width, (float)_texture.height }
	}
public:
	bool IsLeftSide() const { return _isLeftSide; }
	
	void Helicopter::Init(Vector2 position, float speed, Texture2D texture) override
	{
		this->_position = position;
		this->_speed = speed;
		this->_texture = texture;
		//_trooper.Init(_position);
		//_dropTime = GetRandomValue(1, 3);
		if (position.x == 0)
			_isLeftSide = true;
		_isAlive = true;
		_bounds = GetBounds();
	}

	void Helicopter::Move() override
	{
		if (_isLeftSide)
			_position.x += _speed;
		else
			_position.x -= _speed;

		_bounds = GetBounds();

		/*if (!_trooper.IsFalling() && !_trooper.IsGrounded())
			_trooper.FollowHelicopter(_position);
		else if(!_trooper.IsGrounded())
			_trooper.Fall();

		_timer += GetFrameTime();
		Vector2 newPos;
		if (_timer >= _dropTime) 
		{
			_trooper.Spawn();
			_timer = 0;
			_dropTime = GetRandomValue(1, 3);
		}*/

	}

	void Helicopter::Deactivate()
	{
		_isAlive = false;
	}

	bool Helicopter::IsOutOfScreen()
	{
		if (_isLeftSide && _position.x >= SCR_WIDTH)
		{
			return true;
		}
		else if (!_isLeftSide && _position.x <= 0)
		{
			return true;
		}
		return false;
	}

	void Helicopter::Draw()
	{
		// MUST FIND PLACE TO UNLOAD THIS TEXTURE
		/*if (_trooper.IsFalling() || _trooper.IsGrounded())
			DrawTextureEx(_trooper.Texture(), _trooper.Position(), 0.0f, 1.0f, WHITE);*/
		DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
	}
};

#endif // !HELICOPTER_H

