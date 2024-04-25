#pragma once


class CharacterAction : public Action
{
protected:
    const string PATH = "ResourcesCA/Textures/Character/";

public:
    enum Compass
    {
        S, N, E, W
    };

public:
    CharacterAction() = default;
    ~CharacterAction() = default;

    void SetTarget(Transform* target) { this->target = target; }
    void SetCompass(Compass compass) { this->compass = compass; SetState(compass); }
    void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }

    Compass GetCompass() { return compass; }

protected:
    float moveSpeed = 120.0f;

    Transform* target;
    Vector2 velocity;

    Compass compass = S;
};