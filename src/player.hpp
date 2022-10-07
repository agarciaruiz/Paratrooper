#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_LIFES             5

#include "raylib.h"
#include "screen.hpp"
#include "bullet.h"
#include <vector>
#include <math.h>

class Player {
private:
    Vector2 _basePosition;
    Vector2 _turretPosition;
    float _turretRotation;
    float _rotationSpeed;
    int _lifes;
    float maxAngle = 70;
    float _timeout = 0.2;
    float _shootingTimer;

    Texture2D _bodyTexture;
    Texture2D _turretTexture;
    std::vector<Bullet*> bullets = {};

    Bullet* Player::SpawnBullet()
    {
        Bullet* bullet = new Bullet();
        float radians = _turretRotation * (PI / 180);
        Vector2 direction = { sin(radians), cos(radians)};
        bullet->Init(_turretPosition, direction);
        return bullet;
    }

    void Player::Rotate(int direction)
    {
        if (_turretRotation >= maxAngle)
            _turretRotation = maxAngle;

        if (_turretRotation <= -maxAngle)
            _turretRotation = -maxAngle;

        _turretRotation += direction * _rotationSpeed;
    }

    void Player::Shoot()
    {
        bullets.push_back(SpawnBullet());
    }

public:
    Vector2 BasePosition () const { return _basePosition; }
    Vector2 TurretPosition () const { return _turretPosition; }
    float TurretRotation () const { return _turretRotation; }
    float RotSpeed () const { return _rotationSpeed; }
    int Lifes () const { return _lifes; }

    Texture2D BodyTexture() const { return _bodyTexture; }
    Texture2D TurretTexture() const { return _turretTexture; }

    void Player::Init(Vector2 basePosition, float rotationSpeed, int lifes)
    {
        _bodyTexture = LoadTexture("resources/Player/PlayerBody.png");
        _turretTexture = LoadTexture("resources/Player/Turret.png");

        this->_basePosition = basePosition;
        _basePosition.x -= (float)_bodyTexture.width / 2;
        _basePosition.y -= (float)_bodyTexture.height;

        this->_turretPosition = basePosition;
        _turretPosition.x -= (float)_turretTexture.width / 2;
        _turretPosition.y -= (float)_turretTexture.height + (float)_bodyTexture.height;

        this->_rotationSpeed = rotationSpeed;

        this->_lifes = lifes;
        this->_shootingTimer = 0;
    }

    void Player::Update(std::vector<Helicopter*> helicopters)
    {
        int dir;
        if (IsKeyDown(KEY_A))
            dir = -1;
        else if (IsKeyDown(KEY_D))
            dir = 1;
        else
            dir = 0;
        Rotate(dir);

        _shootingTimer += GetFrameTime();
        if (_shootingTimer >= _timeout && IsKeyPressed(KEY_SPACE))
        {
            _shootingTimer = 0;
            Shoot();
        }

        for (int i = 0; i < bullets.size(); i++) 
        {
            bullets[i]->Update(helicopters);
            if(bullets[i]->IsOutOfScreen() || bullets[i]->Hit())
            {
                delete(bullets[i]);
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[i]), bullets.end());
            }
        }   
    }

    void Player::GetDamage() 
    {
        _lifes--;
    }

    void Player::Draw()
    {
        // Draw turret
        Rectangle turretBbox = Rectangle{ 0, 0, (float)_turretTexture.width, (float)_turretTexture.height };
        Rectangle destination = Rectangle{ SCR_WIDTH / 2, SCR_HEIGHT - (float)_bodyTexture.height + 5, (float)_turretTexture.width, (float)_turretTexture.height };
        Vector2 origin = Vector2{ (float)_turretTexture.width / 2, (float)_turretTexture.height };
        DrawTexturePro(_turretTexture, turretBbox, destination, origin, _turretRotation, WHITE);

        // Draw base
        DrawTextureEx(_bodyTexture, _basePosition, 0.0f, 1.0f, WHITE);

        for(int i = 0; i < bullets.size(); i++)
        {
            bullets[i]->Draw();
            //while(!bullets[i]->IsOutOfScreen() && !bullets[i]->Hit())
        }
    }

    void Player::DeleteTexture() {
        UnloadTexture(_bodyTexture);
        UnloadTexture(_turretTexture);
    }
};
#endif