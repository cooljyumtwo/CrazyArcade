#pragma once


class CharacterAction : public Action
{
protected:
    const string PATH = "ResourcesCA/Textures/Character/";
    const float MOVE_SPEED = 100.0f;

public:
    enum Compass
    {
        S, N, E, W
    };

public:
    CharacterAction() = default;
    ~CharacterAction() = default;

    void SetTarget(Transform* target) { this->target = target; }
    void SetCompass(Compass compass) { this->compass = compass; curState = compass; }

    Compass GetCompass() { return compass; }

protected:
    Transform* target;
    Vector2 velocity;

    static Compass compass;
};