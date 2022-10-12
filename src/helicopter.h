#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "global.h"
#include "raylib.h"

class Helicopter
{
private:
	// Helicopter vars
	Rectangle _bounds;
	Vector2 _position;
	Texture2D _texture;
	float _speed;
	bool _leftSided;
	bool _isAlive;
	Sound _explosion;

	float _reloadTextureTimer;
	bool _reloadTexture;

	// Trooper vars
	float _spawnTimeout;
	float _spawnTimer;
	bool _timeOut;
	bool _hasTrooper;

	Rectangle Helicopter::GetBounds();
	void Helicopter::RecenterTexture();

public:
	Rectangle Helicopter::Bounds() const;
	Vector2 Helicopter::Position() const;
	bool Helicopter::IsAlive() const;
	bool Helicopter::HasTrooper() const;
	bool Helicopter::TimeOut() const;
	bool Helicopter::ReloadTexture() const;

	void Helicopter::Init(Vector2 position, float speed, Texture2D texture);
	void Helicopter::Move();
	void Helicopter::DropTrooper();
	void Helicopter::Deactivate();
	bool Helicopter::IsOutOfScreen();
	void Helicopter::Draw();
	void Helicopter::Destroy();
	void Helicopter::UnloadTextures();
};

#endif // !HELICOPTER_H

