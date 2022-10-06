#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_LIFES             5

#include "raylib.h"
#include "screen.hpp"
#include "rlgl.h"

class Player {
private:
    Vector2 _basePosition;
    Vector2 _turretPosition;
    float _turretRotation;
    float _rotationSpeed;
    int _lifes;
    float maxAngle = 70;

    Texture2D _bodyTexture;
    Texture2D _turretTexture;

public:
    Vector2 BasePosition () const { return _basePosition; }
    Vector2 TurretPosition () const { return _turretPosition; }
    float TurretRotation () const { return _turretRotation; }
    float RotSpeed () const { return _rotationSpeed; }
    int Lifes () const { return _lifes; }

    Texture2D BodyTexture() const { return _bodyTexture; }
    Texture2D TurretTexture() const { return _turretTexture; }


    void Init(Vector2 basePosition, float rotationSpeed, int lifes)
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
    }

    void Rotate(int direction) 
    {
        if (_turretRotation >= maxAngle)
            _turretRotation = maxAngle;

        if (_turretRotation <= -maxAngle)
            _turretRotation = -maxAngle;

        _turretRotation += direction * _rotationSpeed;
    }

    void GetDamage() 
    {
        _lifes--;
    }

    void ResetLifes()
    {
        _lifes = 5;
    }

    void DeleteTexture() {
        UnloadTexture(_bodyTexture);
        UnloadTexture(_turretTexture);
    }
};

#endif