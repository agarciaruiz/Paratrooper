#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_LIFES             5

#include <vector>
#include <math.h>
#include "raylib.h"
#include "screen.hpp"
#include "bullet.h"
#include "helicopter.h"

class Player {
private:
    Vector2 _basePosition;
    Vector2 _turretPosition;
    float _turretRotation;
    float _rotationSpeed;
    float maxAngle;
    float _timeout;
    float _shootingTimer;
    int _score;

    Texture2D _bodyTexture;
    Texture2D _turretTexture;
    std::vector<Bullet*> bullets {};
    Sound _laserSound;

    Bullet* Player::SpawnBullet();
    void Player::Rotate(int direction);
    void Player::Shoot();

public:
    Vector2 Player::BasePosition() const;
    Vector2 Player::TurretPosition() const;
    float Player::TurretRotation() const;
    float Player::RotSpeed() const;
    int Player::Score() const;
    Texture2D Player::BodyTexture() const;
    Texture2D Player::TurretTexture() const;

    void Player::Init(Vector2 basePosition);
    void Player::Update(std::vector<Helicopter*> helicopters, std::vector<Trooper*> troopers);
    void Player::SetScore(int score);
    void Player::Draw();
    void Player::Reset();
    void Player::UnloadTextures();
};
#endif