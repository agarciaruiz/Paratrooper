#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "enemy.h"

class Helicopter : public Enemy 
{
private:
	bool _isLeftSide = false;
public:
	bool IsLeftSide() const { return _isLeftSide; }
	
	void Helicopter::Init(Vector2 position, float speed, Texture2D texture) override
	{
		this->_position = position;
		this->_speed = speed;
		this->_texture = texture;

		if (position.x == 0)
			_isLeftSide = true;
	}

	void Helicopter::Move() override
	{
		if(_isLeftSide)
			this->_position.x += this->_speed;
		else
			this->_position.x -= this->_speed;
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
		DrawTextureEx(_texture, _position, 0.0f, 1.0f, WHITE);
	}
};

#endif // !HELICOPTER_H

