#ifndef TROOPER_H
#define TROOPER_H
#include <list>
#include "raylib.h"
#include "global.h"

class Trooper
{
private:
	float _speed;
	Vector2 _position;
	Texture2D _texture;
	Rectangle _bounds;
	bool _isFalling;
	bool _isGrounded;
	bool _isAlive;
	float _reloadTextureTimer;

	Rectangle Trooper::GetBounds();

public:
	bool previouslyGrounded;
	bool Trooper::IsFalling() const;
	bool Trooper::IsGrounded() const;
	void Trooper::PreviouslyGrounded(bool value);
	bool Trooper::IsAlive() const;
	Texture2D Trooper::Texture() const;
	Vector2 Trooper::Position() const;
	Rectangle Trooper::Bounds() const;

	void Trooper::Init(Vector2 position);
	void Trooper::FollowHelicopter(Vector2 position);
	void Trooper::Update();
	void Trooper::Fall();
	bool Trooper::ReloadTexture();
	void Trooper::Draw();
	void Trooper::Destroy();
	void Trooper::UnloadTextures();
};

class TrooperPool
{
private:
	std::list<Trooper*> troopers{};
public:
	Trooper* TrooperPool::GetItem()
	{
		if (troopers.empty())
		{
			Trooper* trooper = new Trooper();
			return trooper;
		}
		else
		{
			Trooper* trooper = troopers.front();
			troopers.pop_front();
			return trooper;
		}
	}

	void TrooperPool::ReturnItem(Trooper* trooper)
	{
		troopers.push_back(trooper);
	}
};

#endif