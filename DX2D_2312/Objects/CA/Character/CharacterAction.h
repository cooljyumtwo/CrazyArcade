#pragma once

class CharacterAction : public Action
{
protected:
    const string PATH = "ResourcesCA/Textures/Character/";
    const float MOVE_SPEED = 100.0f;

    enum Compass
    {
        S, N, E, W
    };

public:
    CharacterAction() = default;
    CharacterAction(string file, bool isLoop, float speed = 1.0f);
    ~CharacterAction() = default;

    void SetTarget(Transform* target) { this->target = target; }
    void SetCompass(Compass compass) { this->compass = compass; curState = compass;}

protected:
    void Update() override;

protected:
    Transform* target;
    Vector2 velocity;

    Compass compass = S;
};