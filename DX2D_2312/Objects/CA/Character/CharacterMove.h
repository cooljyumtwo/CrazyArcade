#pragma once

class CharacterMove : public CharacterAction
{
private:
    int MAX_SPEED = 5;
    float MAX_PUSH_TIME = 1.0f;

public:
    CharacterMove(Transform* target);

    void Update() override;

    void Move();

private:
    RectCollider* frontCollider;
    float playTime;
};